#include "Capsule.h"
using namespace GEOMETRY;
using namespace MATH;

void Capsule::generateVerticesAndNormals()
{
	const float deltaTheta = 1.0f;
	const float deltaPhi = 360.0f / 15.0f;
	Vec3 V = sphereCentrePosA - sphereCentrePosB;
	const float capsuleLength = VMath::mag(V);
	Vec3 axis = VMath::normalize(V);
	const Vec3 nudgeAxis = axis + Vec3(1.0f, 1.0f, 1.0f);
	const Vec3 radialVector = r * VMath::normalize(VMath::cross(axis, nudgeAxis));

	for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta)
	{
		//rings around cylindical portion
		for (float stepsAlongAxis = 0; stepsAlongAxis <= capsuleLength; stepsAlongAxis += 0.2f)
		{
			Vec3 circle = sphereCentrePosB + radialVector + axis * stepsAlongAxis;
			Matrix3 rotationMatrix = MMath::rotate(thetaDeg, axis);
			circle = rotationMatrix * circle;
			vertices.push_back(circle);
			normals.push_back(circle);
		}

		//half spheres on each end of capsule
		Vec3 circleA(r * sin(thetaDeg * DEGREES_TO_RADIANS), r * cos(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
		circleA += sphereCentrePosA.y * axis;
		Vec3 circleB(-r * sin(thetaDeg * DEGREES_TO_RADIANS), -r * cos(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
		circleB += sphereCentrePosB.y * axis;
		for (float phiDeg = 0.0f; phiDeg <= 360.0f; phiDeg += deltaPhi) {
			MATH::Matrix3 rotationMatrix;
			rotationMatrix = MATH::MMath::rotate(deltaPhi, axis);
			circleA = rotationMatrix * circleA;
			circleB = rotationMatrix * circleB;

			if (thetaDeg <= 90.0f) {
				vertices.push_back(circleA);
				normals.push_back(circleA);
				vertices.push_back(circleB);
				normals.push_back(circleB);
			}

			//lines on side of cylindrical portion
			for (float stepsAlongAxis = 0; stepsAlongAxis <= capsuleLength; stepsAlongAxis += 0.025f) {
				Vec3 circle = sphereCentrePosB + radialVector + axis * stepsAlongAxis;
				rotationMatrix = MMath::rotate(phiDeg, axis);
				circle = rotationMatrix * circle;
				vertices.push_back(circle);
				normals.push_back(circle);
			}
		}
	}
}

RayIntersectionInfo GEOMETRY::Capsule::rayIntersectionInfo(MATH::Ray& ray)
{
	RayIntersectionInfo rayInfo;

	const float a = VMath::dot(ray.dir, ray.dir) - VMath::dot(ray.dir, VMath::normalize(sphereCentrePosB - sphereCentrePosA)) * VMath::dot(ray.dir, VMath::normalize(sphereCentrePosB - sphereCentrePosA));
	const float b = 2.0f * (VMath::dot(ray.start - sphereCentrePosA, ray.dir) - (VMath::dot(ray.dir, VMath::normalize(sphereCentrePosB - sphereCentrePosA)) * VMath::dot(ray.start - sphereCentrePosA, VMath::normalize(sphereCentrePosB - sphereCentrePosA))));
	const float c = VMath::dot(ray.start - sphereCentrePosA, ray.start - sphereCentrePosA) - (VMath::dot(ray.start - sphereCentrePosA, VMath::normalize(sphereCentrePosB - sphereCentrePosA)) * VMath::dot(ray.start - sphereCentrePosA, VMath::normalize(sphereCentrePosB - sphereCentrePosA))) - r * r;
	QuadraticSolution soln = solveQuadratic(a, b, c);

	if (soln.numSolutions == NumSolutions::oneRoot) {
		if (soln.firstRoot >= 0.0f) {
			rayInfo = checkEndSphere(ray, soln.firstRoot);
			if (rayInfo.isIntersected == false && rayInfo.intersectionPoint.x != INFINITY) {
				rayInfo.isIntersected = true;
				rayInfo.t = soln.firstRoot;
				rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
			}
		}
	}

	else if (soln.numSolutions == NumSolutions::twoRoots) {
		//Outside sphere in direction of ray. Returns first intersection point.
		if (soln.firstRoot < 0 && soln.secondRoot < 0) {
			if (soln.firstRoot < soln.secondRoot) {
				rayInfo = checkEndSphere(ray, soln.secondRoot);
				if (rayInfo.isIntersected == false && rayInfo.intersectionPoint.x != INFINITY) {
					rayInfo.isIntersected = true;
					rayInfo.t = soln.secondRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.secondRoot);
				}
			}
		}
		if (soln.firstRoot > 0 && soln.secondRoot > 0) {
			if (soln.firstRoot < soln.secondRoot) {
				rayInfo = checkEndSphere(ray, soln.firstRoot);
				if (rayInfo.isIntersected == false && rayInfo.intersectionPoint.x != INFINITY) {
					rayInfo.isIntersected = true;
					rayInfo.t = soln.firstRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
				}
			}
		}
		//Inside sphere in direction of ray. 
		if (soln.firstRoot < 0 && soln.secondRoot > 0) {
			rayInfo = checkEndSphere(ray, soln.secondRoot);
			if (rayInfo.isIntersected == false && rayInfo.intersectionPoint.x != INFINITY) {
				rayInfo.isIntersected = true;
				rayInfo.t = soln.secondRoot;
				rayInfo.intersectionPoint = ray.currentPos(soln.secondRoot);
			}
		}
		if (soln.firstRoot > 0 && soln.secondRoot < 0) {
			rayInfo = checkEndSphere(ray, soln.firstRoot);
			if (rayInfo.isIntersected == false && rayInfo.intersectionPoint.x != INFINITY) {
				rayInfo.isIntersected = true;
				rayInfo.t = soln.firstRoot;
				rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
			}
		}
		//Ray starts at intersection with sphere. 
		if (soln.firstRoot == 0) {
			rayInfo = checkEndSphere(ray, soln.firstRoot);
			if (rayInfo.isIntersected == false && rayInfo.intersectionPoint.x != INFINITY) {
				rayInfo.isIntersected = true;
				rayInfo.t = soln.firstRoot;
				rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
			}
		}
		if (soln.secondRoot == 0) {
			rayInfo = checkEndSphere(ray, soln.secondRoot);
			if (rayInfo.isIntersected == false && rayInfo.intersectionPoint.x != INFINITY) {
				rayInfo.isIntersected = true;
				rayInfo.t = soln.secondRoot;
				rayInfo.intersectionPoint = ray.currentPos(soln.secondRoot);
			}
		}
	}
	else {
		rayInfo.isIntersected = false;
	}

	return rayInfo;
}

RayIntersectionInfo GEOMETRY::Capsule::checkEndSphere(MATH::Ray& ray, float t)
{
	RayIntersectionInfo rayInfo;

	if (VMath::dot(ray.currentPos(t) - sphereCentrePosA, sphereCentrePosB - sphereCentrePosA) <= 0
		&& VMath::dot(ray.currentPos(t) - sphereCentrePosB, sphereCentrePosA - sphereCentrePosB) <= 0) {
		return rayInfo;
	}
	else if (VMath::dot(ray.currentPos(t) - sphereCentrePosA, sphereCentrePosB - sphereCentrePosA) < 0) {
		const Vec3 sphereToRayStart = ray.start - sphereCentrePosA;

		const float a = VMath::dot(ray.dir, ray.dir);
		const float b = 2.0f * VMath::dot(sphereToRayStart, ray.dir);
		const float c = VMath::dot(sphereToRayStart, sphereToRayStart) - r * r;
		QuadraticSolution soln = solveQuadratic(a, b, c);

		if (soln.numSolutions != NumSolutions::zeroRoots) {
			if (soln.numSolutions == NumSolutions::oneRoot) {
				if (soln.firstRoot >= 0.0f) {
					rayInfo.isIntersected = true;
					rayInfo.t = soln.firstRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
				}
			}

			else if (soln.numSolutions == NumSolutions::twoRoots) {
				rayInfo.isIntersected = true;
				//Outside sphere in direction of ray. Returns first intersection point.
				if (soln.firstRoot < soln.secondRoot) {
					rayInfo.t = soln.firstRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
				}
				//Inside sphere in direction of ray. 
				if (soln.firstRoot < 0 && soln.secondRoot > 0) {
					rayInfo.t = soln.secondRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.secondRoot);
				}
				if (soln.firstRoot > 0 && soln.secondRoot < 0) {
					rayInfo.t = soln.firstRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
				}
				//Ray starts at intersection with sphere. 
				if (soln.firstRoot == 0) {
					rayInfo.t = soln.firstRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
				}
				if (soln.secondRoot == 0) {
					rayInfo.t = soln.secondRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.secondRoot);
				}
			}
			return rayInfo;
		}
		rayInfo.intersectionPoint = Vec3(INFINITY, INFINITY, INFINITY);
		return rayInfo;
	}
	else if (VMath::dot(ray.currentPos(t) - sphereCentrePosB, sphereCentrePosA - sphereCentrePosB) < 0) {
		const Vec3 sphereToRayStart = ray.start - sphereCentrePosB;

		const float a = VMath::dot(ray.dir, ray.dir);
		const float b = 2.0f * VMath::dot(sphereToRayStart, ray.dir);
		const float c = VMath::dot(sphereToRayStart, sphereToRayStart) - r * r;
		QuadraticSolution soln = solveQuadratic(a, b, c);

		if (soln.numSolutions != NumSolutions::zeroRoots) {
			if (soln.numSolutions == NumSolutions::oneRoot) {
				if (soln.firstRoot >= 0.0f) {
					rayInfo.isIntersected = true;
					rayInfo.t = soln.firstRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
				}
			}

			else if (soln.numSolutions == NumSolutions::twoRoots) {
				rayInfo.isIntersected = true;
				//Outside sphere in direction of ray. Returns first intersection point.
				if (soln.firstRoot < soln.secondRoot) {
					rayInfo.t = soln.firstRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
				}
				//Inside sphere in direction of ray. 
				if (soln.firstRoot < 0 && soln.secondRoot > 0) {
					rayInfo.t = soln.secondRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.secondRoot);
				}
				if (soln.firstRoot > 0 && soln.secondRoot < 0) {
					rayInfo.t = soln.firstRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
				}
				//Ray starts at intersection with sphere. 
				if (soln.firstRoot == 0) {
					rayInfo.t = soln.firstRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.firstRoot);
				}
				if (soln.secondRoot == 0) {
					rayInfo.t = soln.secondRoot;
					rayInfo.intersectionPoint = ray.currentPos(soln.secondRoot);
				}
			}
			return rayInfo;
		}
		rayInfo.intersectionPoint = Vec3(INFINITY, INFINITY, INFINITY);
		return rayInfo;
	}

	return rayInfo;
}
