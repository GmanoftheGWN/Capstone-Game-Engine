#pragma once

#include "Vector.h"
#include "Quaternion.h"

struct TransformEnTT
{
	MATH::Vec4 position;
	MATH::Quaternion orientation;
	MATH::Vec4 scale;
};

