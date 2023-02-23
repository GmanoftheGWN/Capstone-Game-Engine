#pragma once

#include "External/EnTT/entt.hpp"
#include "Matrix.h"
#include "Vector.h"

MATH::Matrix4 CreateProjectionMatrix(const float fovy, const float aspectRatio, const float near, const float far);
MATH::Matrix4 CreateViewMatrix(const MATH::Vec3& eye, const MATH::Vec3& at, const MATH::Vec3& up);

void UpdateCameras(entt::registry& registry_);


