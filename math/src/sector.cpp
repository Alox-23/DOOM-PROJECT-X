#include "sector.h"


Sector::Sector(int num_vertices, int sector_dat[][2]) : vertices(new sf::Vector2f[num_vertices]), vertices_length(num_vertices), walls(new Wall[num_vertices])
{
	set_vertices(num_vertices, sector_dat);
	set_walls();
}

void Sector::set_vertices(int num_vertices, int sector_dat[][2])
{
	walls = new Wall[num_vertices];
	for(int i = 0; i < num_vertices; i++) 
	{
		vertices[i].x = sector_dat[i][0];
		vertices[i].y = sector_dat[i][1];
	}
}

sf::Vector2f (* Sector::get_vertices())
{
	std::cout << "memory adress of vertices in sector: " << vertices << std::endl; 
	return vertices;
}

void Sector::set_walls()
{
	for (int i = 0; i < vertices_length; i++)
	{
		if (i == vertices_length - 1)
		{	
			walls[i] = Wall(vertices[i], vertices[0]);   
		}
		else
		{
			walls[i] = Wall(vertices[i], vertices[i + 1]);
		}
	}
}
		
void Sector::draw_walls(sf::RenderWindow *window)
{
 	for (int i = 0; i < vertices_length; i++)
 	{
		walls[i].draw(window);
	}
}

Wall (* Sector::get_walls())
{
	return walls;
}

Sector::~Sector()
{
	delete[] vertices;
	delete[] walls;
}
