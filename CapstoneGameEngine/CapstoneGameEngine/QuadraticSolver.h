#pragma once
#include <vector>
#include "Vector.h"

namespace GEOMETRY {
	enum class NumSolutions { zeroRoots = 0, oneRoot, twoRoots };

	struct QuadraticSolution {
		NumSolutions numSolutions{ NumSolutions::zeroRoots };// I'll use first root as the smallest of the two. Set them both to zero to begin with
		float firstRoot = 0.0f;
		float secondRoot = 0.0f;

		//void print(); // handy method that prints out the number of solutions and their value(s)
	};

	QuadraticSolution solveQuadratic(float a, float b, float c);
}
