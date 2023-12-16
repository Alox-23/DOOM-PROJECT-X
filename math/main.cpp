#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>

/*
debug notes:
fix player position

implement debug text:
	make different functions for different debug text outputs
	for example:
	if i need to set the fps, then:

	void set_debug_text(std::string in_text1, std::string in_text2, std::string text, std::string end_val)
	{
	  text << in_text1 << in_text2 << end_val;
	};
	
	and make text a pointer too.
*/
sf::Text debug_text_display;
std::string debug_text;

void add_debug_text(std::string in_text1, std::string in_text2, std::string end_val)
{
	debug_text += in_text1 + in_text2 + end_val;
};

class Player
{
	private:
		sf::Texture playerTexture;
		sf::Sprite playerSprite;
		sf::Vector2f playerPos;

	public:
		Player(sf::Vector2f pos)
		{
			playerPos = pos;
			if (!playerTexture.loadFromFile("img/player.png"))
			{
			  std::cout << "problem loading player image from file" << std::endl; 
			}
			playerSprite.setTexture(playerTexture);
			playerSprite.setPosition(playerPos);
		};

		void update()
		{
			playerSprite.setPosition(playerPos);
			add_debug_text("player pos: ", std::to_string(playerPos.x) + ", " + std::to_string(playerPos.y), "\n");
		};

		void draw(sf::RenderWindow *window)
		{
			window->draw(playerSprite);
		};
};

class Wall
{
	private:
		[[maybe_unused]]double x1, y1, x2, y2;
		[[maybe_unused]]sf::Vector2f p1, p2;
		sf::VertexArray line;
	public:
		Wall()
		{
			std::cout << "Wall created" << std::endl;
		}
		Wall(sf::Vector2f p1, sf::Vector2f p2) 
		{
		  this->p1.x = p1.x;
		  this->p2.x = p2.x;
		  this->p1.y = p1.y;
		  this->p2.y = p2.y;  
		  line = sf::VertexArray(sf::Lines, 2);
		  line[0].position = this->p1;
		  line[1].position = this->p2;
		}

		void draw(sf::RenderWindow *window)
		{
		  window->draw(line);
		}
};


class Sector
{
	private:
		sf::Vector2f (*vertices);
		int vertices_length;
		Wall (* walls);

	public:
		Sector(int num_vertices, int sector_dat[][2]) : vertices(new sf::Vector2f[num_vertices]), vertices_length(num_vertices), walls(new Wall[num_vertices])
		{
			set_vertices(num_vertices, sector_dat);
			set_walls();
		}

		void set_vertices(int num_vertices, int sector_dat[][2])
		{
			walls = new Wall[num_vertices];
			for(int i = 0; i < num_vertices; i++) {
				vertices[i].x = sector_dat[i][0];
				vertices[i].y = sector_dat[i][1];
			}
		}

		sf::Vector2f (* get_vertices())
		{
			return vertices;
		}

		void set_walls()
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
		
		void draw_walls(sf::RenderWindow *window)
		{
		  for (int i = 0; i < vertices_length; i++)
		  {
			walls[i].draw(window);
		  }
		}

		Wall (* get_walls())
		{
			return walls;
		}

		~Sector()
		{
			delete[] vertices;
			delete[] walls;
		}
};

int main ()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Math lol");
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(2000);

	sf::Time deltaTime;
	sf::Clock clock;

	int sector_dat[6][2] = 
	{
		{100,100},
		{300,50},
		{500,80},
		{700,400},
		{300,600},
		{30, 300}
 	};
	
  	Sector sector(6, sector_dat);
	
  	Player p(sf::Vector2f(400, 300)); 

	sf::Font font;
   	if (!font.loadFromFile("Arial.ttf"))
	{
		std::cout << "please check that there is a font file" << std::endl;
	}
	
	debug_text_display.setFont(font);
	debug_text_display.setCharacterSize(10);
	debug_text_display.setFillColor(sf::Color::Green);

  	// run the program as long as the window is open
  	while (window.isOpen())
 	{
		deltaTime = clock.restart();

		//update
		//text
		debug_text = "";
		add_debug_text("fps: ",std::to_string(std::round(1.f / deltaTime.asSeconds())), "\n");	
	  	
		//player
		p.update();  

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
		  // "close requested" event: we close the window
		  if (event.type == sf::Event::Closed) window.close();
		}
		window.clear(sf::Color(100, 100, 100, 255));
	
		//sectors
		sector.draw_walls(&window);
	
		//player  
		p.draw(&window);

		//text
		debug_text_display.setString(debug_text);
		window.draw(debug_text_display); 
		  
		window.display();
	}
}

