#include "ray.h"

Ray::Ray(double x1, double y1, double deg) : x1(x1), y1(y1)
{
    this->calculateEquation(deg);
}

void Ray::calculateEquation(double deg) {
    // Check if the line is vertical
    if (deg != 90 && deg != 270) {
        // Calculate the slope (m) and y-intercept (b)
        slope = std::tan(deg * M_PI/180) * 180/M_PI;
        intercept = y1 - slope * x1;
    } else {
        // If the line is vertical, store slope as NaN and x-intercept
        slope = NAN;
        intercept = x1;
    }
};

void Ray::printEquation() {
    if (!std::isnan(slope)) {
        std::cout << "y = " << slope << "x + " << intercept << std::endl;
    } else {
        std::cout << "x = " << intercept << std::endl;
    }
};

double Ray::getSlope() 
{
   return this->slope;
};

double Ray::getIntercept() 
{
   return this->intercept;
};

sf::Vector2f Ray::findIntersectionWall(Wall& wall)
{
    if (!std::isnan(slope) && !std::isnan(wall.getSlope())) {
        // General lines - solve for intersection point
        double xIntersection = (wall.getIntercept() - intercept) / (slope - wall.getSlope());
        double yIntersection = slope * xIntersection + intercept;
        return sf::Vector2f(static_cast<float>(xIntersection), static_cast<float>(yIntersection));
    } else if (std::isnan(slope)) {
        // Vertical line and general line
        double xIntersection = intercept;
        double yIntersection = wall.getSlope() * xIntersection + wall.getIntercept();
        return sf::Vector2f(static_cast<float>(xIntersection), static_cast<float>(yIntersection));
    } else if (std::isnan(wall.getSlope())) {
        // General line and vertical line
        double xIntersection = wall.getIntercept();
        double yIntersection = slope * xIntersection + intercept;
        return sf::Vector2f(static_cast<float>(xIntersection), static_cast<float>(yIntersection));
    } else {
        // Both lines are vertical, no intersection
        return sf::Vector2f(NAN, NAN);
    }
};