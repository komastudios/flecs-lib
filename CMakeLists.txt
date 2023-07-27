cmake_minimum_required(VERSION 3.15)

project(flecs LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(FLECS_PIC "Compile with position independent code" ON)
option(BUILD_SHARED "Build shared library" ON)

option(USE_MSVC_STATIC_RUNTIME "Use MSVC static runtime" OFF)

set(FLECS_ADDONS "" CACHE STRING "Semicolon-separated list of addons to include in the build. Leave empty to build all addons")

if (${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Oz -g -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Oz -g -DNDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "-Oz -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-Oz -DNDEBUG")

    add_compile_options(-fsigned-char)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    set(BUILD_SHARED OFF)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "MSVC")
    if(USE_MSVC_STATIC_RUNTIME)
        message(STATUS "Using MSVC static runtime")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
        message(STATUS "Using MSVC dynamic runtime")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif()
endif()

set(LIB_PUBLIC_HEADERS flecs/flecs.h)

file(GLOB_RECURSE INC flecs/include/*.h flecs/include/*.hpp)
file(GLOB_RECURSE SRC flecs/src/*.c)

set(LIB_SOURCE_FILES 
    ${SRC} 
    ${INC}
    flecs_pinvoke.c)
set(LIB_ADDON_FLAGS "")

if (FLECS_ADDONS)
    set(ALL_ADDONS "Cpp;Module;System;Pipeline;Timer;Meta;Meta_C;Units;Expr;JSON;Doc;Coredoc;Http;Rest;Parser;Plecs;Rules;Snapshot;Stats;Monitor;Metrics;Log;Journal;App;OS_API_IMPL")

    foreach(ADDON IN LISTS FLECS_ADDONS)
        list(FIND ALL_ADDONS ${ADDON} ADDON_INDEX)
        if(${ADDON_INDEX} EQUAL -1)
            message(FATAL_ERROR "Unknown flecs addon: ${ADDON}")
        endif()
        string(TOUPPER "FLECS_${ADDON}" ADDON_FLAG)
        list(APPEND LIB_ADDON_FLAGS ${ADDON_FLAG})
    endforeach()

    message(STATUS "Compiling flecs with custom set of addons: ${FLECS_ADDONS}")
else()
    message(STATUS "Compiling flecs with all addons")
endif()

function(add_flecs_library TARGET_NAME LIB_TYPE)
    add_library(${TARGET_NAME} ${LIB_TYPE} ${LIB_SOURCE_FILES})
    set_property(TARGET ${TARGET_NAME} PROPERTY C_VISIBILITY_PRESET hidden)
    
    target_include_directories(${TARGET_NAME} PRIVATE flecs/include)
    
    if (LIB_ADDON_FLAGS)
        target_compile_definitions(${TARGET_NAME} PUBLIC FLECS_CUSTOM_BUILD ${LIB_ADDON_FLAGS})
    endif()

    if(FLECS_PIC)
        set_property(TARGET ${TARGET_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
    endif()

    if (LIB_TYPE STREQUAL "STATIC")
        target_compile_definitions(${TARGET_NAME} PRIVATE flecs_STATIC)
    endif()

    if(WIN32)
        target_link_libraries(${TARGET_NAME} PRIVATE wsock32 ws2_32)
    endif()
    if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
        target_link_libraries(${TARGET_NAME} PRIVATE pthread)
    endif()

    install(TARGETS ${TARGET_NAME} 
            ARCHIVE DESTINATION lib
            LIBRARY DESTINATION lib
            RUNTIME DESTINATION bin)
endfunction()

add_flecs_library(flecs-static STATIC)

install(FILES
    ${LIB_PUBLIC_HEADERS}
    DESTINATION include)

if(BUILD_SHARED)
    add_flecs_library(flecs SHARED)
endif()
