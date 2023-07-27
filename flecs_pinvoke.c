#include "flecs.h"

// Roles
FLECS_API ecs_id_t pinvoke_ECS_PAIR()
{
    return ECS_PAIR;
}

FLECS_API ecs_id_t pinvoke_ECS_OVERRIDE()
{
    return ECS_OVERRIDE;
}

// Relationships
FLECS_API ecs_entity_t pinvoke_EcsIsA()
{
    return EcsIsA;
}

FLECS_API ecs_entity_t pinvoke_EcsDependsOn()
{
    return EcsDependsOn;
}

FLECS_API ecs_entity_t pinvoke_EcsChildOf()
{
    return EcsChildOf;
}

FLECS_API ecs_entity_t pinvoke_EcsSlotOf()
{
    return EcsSlotOf;
}

// Entity tags
FLECS_API ecs_entity_t pinvoke_EcsPrefab()
{
    return EcsPrefab;
}

// System tags
FLECS_API ecs_entity_t pinvoke_EcsPreFrame()
{
    return EcsPreFrame;
}

FLECS_API ecs_entity_t pinvoke_EcsOnLoad()
{
    return EcsOnLoad;
}

FLECS_API ecs_entity_t pinvoke_EcsPostLoad()
{
    return EcsPostLoad;
}

FLECS_API ecs_entity_t pinvoke_EcsPreUpdate()
{
    return EcsPreUpdate;
}

FLECS_API ecs_entity_t pinvoke_EcsOnUpdate()
{
    return EcsOnUpdate;
}

FLECS_API ecs_entity_t pinvoke_EcsOnValidate()
{
    return EcsOnValidate;
}

FLECS_API ecs_entity_t pinvoke_EcsPostUpdate()
{
    return EcsPostUpdate;
}

FLECS_API ecs_entity_t pinvoke_EcsPreStore()
{
    return EcsPreStore;
}

FLECS_API ecs_entity_t pinvoke_EcsOnStore()
{
    return EcsOnStore;
}

FLECS_API ecs_entity_t pinvoke_EcsPostFrame()
{
    return EcsPostFrame;
}

FLECS_API ecs_entity_t pinvoke_EcsPhase()
{
    return EcsPhase;
}
