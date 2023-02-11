#include "TransformSystemEnTT.h"
#include "RenderEnTT.h"

void UpdateEnTT(entt::registry& registry_, float deltaTime_)
{
    auto view = registry_.view<TransformEnTT, RenderEnTT>();
    for (const entt::entity e : view) {
        view.get<TransformEnTT>(e).position.y = sin(deltaTime_);
        printf("%d  %f\n", e, view.get<TransformEnTT>(e).position.y);
    }
}