#ifndef CAPSULE_H
#define CAPSULE_H
#include "Shape.h"
#include "Vector.h"
#include <vector>
#include "Matrix.h"
#include "VMath.h"
#include "MMath.h"

namespace GEOMETRY {
	struct Capsule : public MATH::Vec3, public Shape {

		float r = 1.0f;
		MATH::Vec3 sphereCentrePosA;
		MATH::Vec3 sphereCentrePosB;

		Capsule() {
			sphereCentrePosA.set(0.0f, 0.0f, 0.0f);
			sphereCentrePosB.set(0.0f, 1.0f, 0.0f);
			generateVerticesAndNormals();
			StoreMeshData(GL_POINTS);

		}

		void set(float r_, MATH::Vec3 sphereCentrePosA_, MATH::Vec3 sphereCentrePosB_) {
			r = r_;
			sphereCentrePosA = sphereCentrePosA_;
			sphereCentrePosB = sphereCentrePosB_;
			generateVerticesAndNormals();
			StoreMeshData(GL_POINTS);
		}

		Capsule(float r_, MATH::Vec3 sphereCentrePosA_, MATH::Vec3 sphereCentrePosB_) {
			set(r_, sphereCentrePosA_, sphereCentrePosB_);

		}

		// RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override; (TO DO)
		void generateVerticesAndNormals() override;

		RayIntersectionInfo rayIntersectionInfo(MATH::Ray& ray) override;
		RayIntersectionInfo checkEndSphere(MATH::Ray& ray, float t);
	};
}
#endif
