#include "Box.h"
#include <array>
#include <algorithm>
using namespace GEOMETRY;
using namespace MATH;

void Box::generateVerticesAndNormals()
{
	std::vector<Vec3> uniqueVertices;
	const int top_right_front = 0;
	const int top_left_front = 1;
	const int bottom_left_front = 2;
	const int bottom_right_front = 3;
	const int top_right_back = 4;
	const int top_left_back = 5;
	const int bottom_left_back = 6;
	const int bottom_right_back = 7;

	uniqueVertices.push_back(orientation * (centre + MATH::Vec3(halfExtents.x, halfExtents.y, halfExtents.z)));
	uniqueVertices.push_back(orientation * (centre + MATH::Vec3(0.0f, halfExtents.y, halfExtents.z)));
	uniqueVertices.push_back(orientation * (centre + MATH::Vec3(0.0f, 0.0f, halfExtents.z)));
	uniqueVertices.push_back(orientation * (centre + MATH::Vec3(halfExtents.x, 0.0f, halfExtents.z)));
	uniqueVertices.push_back(orientation * (centre + MATH::Vec3(halfExtents.x, halfExtents.y, 0.0f)));
	uniqueVertices.push_back(orientation * (centre + MATH::Vec3(0.0f, halfExtents.y, 0.0f)));
	uniqueVertices.push_back(orientation * (centre + MATH::Vec3(0.0f, 0.0f, 0.0f)));
	uniqueVertices.push_back(orientation * (centre + MATH::Vec3(halfExtents.x, 0.0f, 0.0f)));

	//top face
	vertices.push_back(uniqueVertices[top_right_front]);
	vertices.push_back(uniqueVertices[top_right_back]);
	vertices.push_back(uniqueVertices[top_left_front]);
	vertices.push_back(uniqueVertices[top_left_front]);
	vertices.push_back(uniqueVertices[top_right_back]);
	vertices.push_back(uniqueVertices[top_left_back]);
	//front face
	vertices.push_back(uniqueVertices[bottom_right_front]);
	vertices.push_back(uniqueVertices[top_right_front]);
	vertices.push_back(uniqueVertices[bottom_left_front]);
	vertices.push_back(uniqueVertices[bottom_left_front]);
	vertices.push_back(uniqueVertices[top_right_front]);
	vertices.push_back(uniqueVertices[top_left_front]);
	//bottom face
	vertices.push_back(uniqueVertices[bottom_right_back]);
	vertices.push_back(uniqueVertices[bottom_right_front]);
	vertices.push_back(uniqueVertices[bottom_left_back]);
	vertices.push_back(uniqueVertices[bottom_left_back]);
	vertices.push_back(uniqueVertices[bottom_right_front]);
	vertices.push_back(uniqueVertices[bottom_left_front]);
	//back face
	vertices.push_back(uniqueVertices[bottom_left_back]);
	vertices.push_back(uniqueVertices[top_left_back]);
	vertices.push_back(uniqueVertices[bottom_right_back]);
	vertices.push_back(uniqueVertices[bottom_right_back]);
	vertices.push_back(uniqueVertices[top_left_back]);
	vertices.push_back(uniqueVertices[top_right_back]);
	//left face
	vertices.push_back(uniqueVertices[bottom_left_front]);
	vertices.push_back(uniqueVertices[top_left_front]);
	vertices.push_back(uniqueVertices[bottom_left_back]);
	vertices.push_back(uniqueVertices[bottom_left_back]);
	vertices.push_back(uniqueVertices[top_left_front]);
	vertices.push_back(uniqueVertices[top_left_back]);
	//right face
	vertices.push_back(uniqueVertices[bottom_right_back]);
	vertices.push_back(uniqueVertices[top_right_back]);
	vertices.push_back(uniqueVertices[bottom_right_front]);
	vertices.push_back(uniqueVertices[bottom_right_front]);
	vertices.push_back(uniqueVertices[top_right_back]);
	vertices.push_back(uniqueVertices[top_right_front]);

	//normals
	//top face
	normals.push_back(uniqueVertices[top_right_front]);
	normals.push_back(uniqueVertices[top_right_back]);
	normals.push_back(uniqueVertices[top_left_front]);
	normals.push_back(uniqueVertices[top_left_front]);
	normals.push_back(uniqueVertices[top_right_back]);
	normals.push_back(uniqueVertices[top_left_back]);
	//front face
	normals.push_back(uniqueVertices[bottom_right_front]);
	normals.push_back(uniqueVertices[top_right_front]);
	normals.push_back(uniqueVertices[bottom_left_front]);
	normals.push_back(uniqueVertices[bottom_left_front]);
	normals.push_back(uniqueVertices[top_right_front]);
	normals.push_back(uniqueVertices[top_left_front]);
	//bottom face
	normals.push_back(uniqueVertices[bottom_right_back]);
	normals.push_back(uniqueVertices[bottom_right_front]);
	normals.push_back(uniqueVertices[bottom_left_back]);
	normals.push_back(uniqueVertices[bottom_left_back]);
	normals.push_back(uniqueVertices[bottom_right_front]);
	normals.push_back(uniqueVertices[bottom_left_front]);
	//back face
	normals.push_back(uniqueVertices[bottom_left_back]);
	normals.push_back(uniqueVertices[top_left_back]);
	normals.push_back(uniqueVertices[bottom_right_back]);
	normals.push_back(uniqueVertices[bottom_right_back]);
	normals.push_back(uniqueVertices[top_left_back]);
	normals.push_back(uniqueVertices[top_right_back]);
	//left face
	normals.push_back(uniqueVertices[bottom_left_front]);
	normals.push_back(uniqueVertices[top_left_front]);
	normals.push_back(uniqueVertices[bottom_left_back]);
	normals.push_back(uniqueVertices[bottom_left_back]);
	normals.push_back(uniqueVertices[top_left_front]);
	normals.push_back(uniqueVertices[top_left_back]);
	//right face
	normals.push_back(uniqueVertices[bottom_right_back]);
	normals.push_back(uniqueVertices[top_right_back]);
	normals.push_back(uniqueVertices[bottom_right_front]);
	normals.push_back(uniqueVertices[bottom_right_front]);
	normals.push_back(uniqueVertices[top_right_back]);
	normals.push_back(uniqueVertices[top_right_front]);
}

RayIntersectionInfo GEOMETRY::Box::rayIntersectionInfo(MATH::Ray& ray)
{
	RayIntersectionInfo rayInfo;

	Slab slabX;
	slabX.normal = Vec3(1.0f, 0.0f, 0.0f);
	slabX.distNear = -halfExtents.x;
	slabX.distFar = halfExtents.x;

	Slab slabY;
	slabY.normal = Vec3(0.0f, 1.0f, 0.0f);
	slabY.distNear = -halfExtents.y;
	slabY.distFar = halfExtents.y;

	Slab slabZ;
	slabZ.normal = Vec3(0.0f, 0.0f, 1.0f);
	slabZ.distNear = -halfExtents.z;
	slabZ.distFar = halfExtents.z;

	std::array<Slab, 3> slabs = {slabX, slabY, slabZ};

	float tMin = 0.0f;
	float tMax = FLT_MAX;

	for (int i = 0; i < slabs.size(); i++) {
		float t1 = (slabs[i].distNear - ray.start[i]) / ray.dir[i];
		float t2 = (slabs[i].distFar - ray.start[i]) / ray.dir[i];

		if (t1 > t2) {
			std::swap(t1, t2);
		}
		tMin = std::max(tMin, t1);
		tMax = std::min(tMax, t2);

		if (tMin > tMax) {
			return rayInfo;
		}
	}
	rayInfo.isIntersected = true;
	rayInfo.t = tMin;
	rayInfo.intersectionPoint = ray.currentPos(tMin);
	return rayInfo;
}
