#ifndef SECTOR_H
#define SECTOR_H

#include "SFML/Graphics.hpp"
#include "wall.h"
#include "iostream"

class Sector
{
	private:
		sf::Vector2f (*vertices);
		int vertices_length;
		Wall (* walls);

	public:
		Sector(int num_vertices, int sector_dat[][2]);
		void set_vertices(int num_vertices, int sector_dat[][2]);

		sf::Vector2f (* get_vertices());

		void set_walls();
		
		void draw_walls(sf::RenderWindow *window);

		Wall (* get_walls());

		~Sector();
};
#endif
