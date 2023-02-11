#include "EntityBuilder.h"

entt::entity makeCamera(entt::registry& registry_)
{
	const entt::entity entity = registry_.create();
	registry_.emplace<TransformEnTT>(entity);
	return entity;
}

entt::entity makePlayer(entt::registry& registry_)
{
	const entt::entity entity = registry_.create();
	registry_.emplace<TransformEnTT>(entity);
	registry_.emplace<RenderEnTT>(entity);
	return entity;
}

entt::entity makeNPC(entt::registry& registry_)
{
	const entt::entity entity = registry_.create();
	registry_.emplace<TransformEnTT>(entity);
	registry_.emplace<RenderEnTT>(entity);
	return entity;
}

entt::entity makeLight(entt::registry& registry_)
{
	const entt::entity entity = registry_.create();
	registry_.emplace<TransformEnTT>(entity);
	return entity;
}

entt::entity makeObject(entt::registry& registry_)
{
	const entt::entity entity = registry_.create();
	registry_.emplace<TransformEnTT>(entity);
	registry_.emplace<RenderEnTT>(entity);
	return entity;
}
