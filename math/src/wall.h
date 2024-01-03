#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

class Wall
{
	private:
		[[maybe_unused]]double x1, y1, x2, y2;
		[[maybe_unused]]sf::Vector2f p1, p2;
		sf::VertexArray line;
	public:
		Wall();
		
		Wall(sf::Vector2f p1, sf::Vector2f p2);

		void draw(sf::RenderWindow *window);
};
#endif
