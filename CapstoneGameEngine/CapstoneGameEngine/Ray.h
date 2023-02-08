#ifndef RAY_H
#define RAY_H

#include "Vector.h"

namespace MATH {
	class Ray {
	public:
		Vec3 start;
		Vec3 dir;

		Ray(); 
		Ray(Vec3 start_, Vec3 dir_);

		Vec3 currentPos(float t);
	};
}
namespace GEOMETRY {
	struct RayIntersectionInfo {
		bool isIntersected = false;
		MATH::Vec3 intersectionPoint;
		float t = 0.0f;

		void print() {
			if (isIntersected) {
				std::cout << "Ray intersection with t value " << t << " at position ";
				intersectionPoint.print();
			}
			else {
				std::cout << "No ray intersection\n";
			}
		}
	};
}

#endif //RAY_H
