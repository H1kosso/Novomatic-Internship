#include "../Triangle.h"


//Checks if two given triangle collide with eachother
bool isColliding(const triangle& triangle1, const triangle& triangle2) {

    if (
        //first side of triangle1 with triangle2
        isIntersection(triangle1.points[0], triangle1.points[1], triangle2.points[0], triangle2.points[1]) ||
        isIntersection(triangle1.points[0], triangle1.points[1], triangle2.points[1], triangle2.points[2]) ||
        isIntersection(triangle1.points[0], triangle1.points[1], triangle2.points[2], triangle2.points[0]) ||
        //second side of triangle1 with triangle2
        isIntersection(triangle1.points[1], triangle1.points[2], triangle2.points[0], triangle2.points[1]) ||
        isIntersection(triangle1.points[1], triangle1.points[2], triangle2.points[1], triangle2.points[2]) ||
        isIntersection(triangle1.points[1], triangle1.points[2], triangle2.points[2], triangle2.points[0]) ||
        //third side of triangle1 with triangle2
        isIntersection(triangle1.points[2], triangle1.points[0], triangle2.points[0], triangle2.points[1]) ||
        isIntersection(triangle1.points[2], triangle1.points[0], triangle2.points[1], triangle2.points[2]) ||
        isIntersection(triangle1.points[2], triangle1.points[0], triangle2.points[2], triangle2.points[0])
        ) return true;

    else return false;
}
