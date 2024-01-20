#include "wall.h"

Wall::Wall()
{
	(void)0;
}
Wall::Wall(sf::Vector2f p1, sf::Vector2f p2) 
{
	this->p1.x = p1.x;
	this->p2.x = p2.x;
	this->p1.y = p1.y;
	this->p2.y = p2.y;  
	this->line = sf::VertexArray(sf::Lines, 2);
    this->line[0].position = this->p1;
    this->line[1].position = this->p2;
    this->calculateEquation();
}

double Wall::getSlope() 
{
   return this->slope;
};

double Wall::getIntercept() 
{
   return this->intercept;
};

void Wall::calculateEquation() {
    // Check if the line is vertical
    if (x1 != x2) {
        // Calculate the slope (m) and y-intercept (b)
        slope = (y2 - y1) / (x2 - x1);
        intercept = y1 - slope * x1;
    } else {
        // If the line is vertical, store slope as NaN and x-intercept
        slope = NAN;
        intercept = x1;
    }
};

void Wall::printEquation() {
    if (!std::isnan(slope)) {
        std::cout << "y = " << slope << "x + " << intercept << std::endl;
    } else {
        std::cout << "x = " << intercept << std::endl;
    }
};

void Wall::draw(sf::RenderWindow *window)
{
	window->draw(this->line);
}
