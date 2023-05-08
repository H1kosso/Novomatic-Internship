#include <array>
#include <iostream>

#include "../Intersection.h"


float direction(const vec2 &p1, const vec2 &p2, const vec2 &p3) {
  return (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
}


bool areCollinearAndOverlapping(const vec2 &a1, const vec2 &b1, const vec2 &a2,
                                const vec2 &b2) {
  // Check if the line segments are collinear
  if (direction(a1, b1, a2) == 0) {
    // Check if the line segments overlap
    if (a2.x <= std::max(a1.x, b1.x) && a2.x >= std::min(a1.x, b1.x) &&
        a2.y <= std::max(a1.y, b1.y) && a2.y >= std::min(a1.y, b1.y)) {
      return true;
    }
  }
  return false;
}

bool isIntersection(const vec2 &a1, const vec2 &b1, const vec2 &a2,
                    const vec2 &b2) {
  // Compute the directions of the four line segments
  float d1 = direction(a1, b1, a2);
  float d2 = direction(a1, b1, b2);
  float d3 = direction(a2, b2, a1);
  float d4 = direction(a2, b2, b1);

  // Check if the two line segments intersect
  if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
      ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
    return true;
  }
  // Check if the line segments are collinear and overlapping
  if (areCollinearAndOverlapping(a1, b1, a2, b2) ||
      areCollinearAndOverlapping(a2, b2, a1, b1)) {
    return true;
  }
  return false;
}
