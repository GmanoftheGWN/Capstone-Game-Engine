#include "CameraSystemEnTT.h"
#include "MMath.h"
#include "QMath.h"
#include "CameraEnTT.h"
#include "TransformEnTT.h"

MATH::Matrix4 CreateProjectionMatrix(const float fovy, const float aspectRatio, const float near, const float far)
{
    return MATH::MMath::perspective(fovy, aspectRatio, near, far);
}

MATH::Matrix4 CreateViewMatrix(const MATH::Vec3& eye, const MATH::Vec3& at, const MATH::Vec3& up)
{
    return MATH::MMath::lookAt(eye, at, up);
}

void UpdateCameras(entt::registry& registry_)
{
    auto view = registry_.view<CameraEnTT, TransformEnTT>();
    for (const entt::entity e : view) {
        CameraEnTT camera = view.get<CameraEnTT>(e);
        TransformEnTT transform = view.get<TransformEnTT>(e);

        camera.viewMatrix = MATH::MMath::translate(transform.position) * MATH::QMath::toMatrix4(transform.orientation);
    }
}
