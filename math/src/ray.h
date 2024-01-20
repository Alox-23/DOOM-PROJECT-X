#ifndef RAY_H
#define RAY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "wall.h"

class Ray {
    private:
        double x1, y1, x2, y2;
        double slope, intercept;
    
    public:
        Ray(double x1, double y1, double deg);
    
        void calculateEquation(double deg);

        double getSlope();

        double getIntercept();
    
        void printEquation();
    
        sf::Vector2f findIntersectionWall(Wall& wall);
};
#endif