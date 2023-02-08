#include "Ray.h"
#include "VMath.h"

using namespace MATH;

//Ray 0 Constructor
Ray::Ray()
{
	start = Vec3(0.0f, 0.0f, 0.0f);
	dir = Vec3(0.0f, 0.0f, 0.0f);
}

//Ray Constructor
Ray::Ray(Vec3 start_, Vec3 dir_)
{
	start = start_;
	dir = VMath::normalize(dir_);
}

//Find Current Position Along Ray
Vec3 Ray::currentPos(float t)
{
	Vec3 pos = start + dir * t;

	return pos;
}
