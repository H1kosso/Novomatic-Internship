#pragma once

struct vec2 {
  float x, y;
};

/*
   Computes the direction of the three given points
   Returns a positive value if they form a counter-clockwise orientation,
   a negative value if they form a clockwise orientation,
   and zero if they are collinear
*/
float direction(const vec2 &p1, const vec2 &p2, const vec2 &p3);

// Checks if two line segments are collinear and overlapping
bool areCollinearAndOverlapping(const vec2 &a1, const vec2 &b1, const vec2 &a2,
                                const vec2 &b2);

// Checks if two line segments intersect
bool isIntersection(const vec2 &a1, const vec2 &b1, const vec2 &a2,
                    const vec2 &b2);
