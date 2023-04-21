#ifndef ENTITY_BUILDER_H
#define ENTITY_BUILDER_H

#include "External/EnTT/entt.hpp"
#include "TransformEnTT.h"
#include "RenderEnTT.h"
#include "PhysxIDEnTT.h"

entt::entity makeCamera(entt::registry& registry_);
entt::entity makePlayer(entt::registry& registry_);
entt::entity makeNPC(entt::registry& registry_);
entt::entity makeLight(entt::registry& registry_);
entt::entity makeObject(entt::registry& registry_);

#endif