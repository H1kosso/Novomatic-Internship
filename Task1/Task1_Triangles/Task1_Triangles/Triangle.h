#pragma once
#include <array>
#include <iostream>

#include "Intersection.h"

struct triangle {
  std::array<vec2, 3> points;
};


// Checks if two passed triangles collide:
// It includes side intersection, overlapping and collinearity
bool isColliding(const triangle &triangle1, const triangle &triangle2);
