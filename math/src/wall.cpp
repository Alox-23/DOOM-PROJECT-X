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
	line = sf::VertexArray(sf::Lines, 2);
	line[0].position = this->p1;
 	line[1].position = this->p2;
}

void Wall::draw(sf::RenderWindow *window)
{
	window->draw(line);
}
