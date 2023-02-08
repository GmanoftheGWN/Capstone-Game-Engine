#ifndef BOX_H
#define BOX_H
#include "Shape.h"
#include "Vector.h"
#include <vector>
#include "Matrix.h"
#include "VMath.h"
#include "MMath.h"
#include "Quaternion.h"

namespace GEOMETRY {

	struct Slab {
		MATH::Vec3 normal;
		float distNear;
		float distFar;
	};

	struct Box : public MATH::Vec3, public Shape {

		MATH::Vec3 centre;
		MATH::Vec3 halfExtents;
		MATH::Quaternion orientation;

		Box() {
			centre.set(0.0f, 0.0f, 0.0f);
			halfExtents.set(1.0f, 1.0f, 1.0f);
			orientation.set(1.0f, 0.0f, 0.0f, 0.0f);
			generateVerticesAndNormals();
			StoreMeshData(GL_TRIANGLES);

		}

		void set(MATH::Vec3 centre_, MATH::Vec3 halfExtents_, MATH::Quaternion orientation_) {
			centre = centre_;
			halfExtents = halfExtents_;
			orientation = orientation_;
			generateVerticesAndNormals();
			StoreMeshData(GL_TRIANGLES);
		}

		Box(MATH::Vec3 centre_, MATH::Vec3 halfExtents_, MATH::Quaternion orientation_) {
			set(centre_, halfExtents_, orientation_);

		}

		// RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override; (TO DO)
		void generateVerticesAndNormals() override;

		RayIntersectionInfo rayIntersectionInfo(MATH::Ray& ray) override;
	};
}
#endif
