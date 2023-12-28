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
chat gpt vertex intersection c++ code:
#include <iostream>
#include <SFML/Graphics.hpp>

class Line {
private:
    double x1, y1, x2, y2;
    double slope, intercept;

public:
    Line(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {
        calculateEquation();
    }

    void calculateEquation() {
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
    }

    void printEquation() {
        if (!std::isnan(slope)) {
            std::cout << "y = " << slope << "x + " << intercept << std::endl;
        } else {
            std::cout << "x = " << intercept << std::endl;
        }
    }

    sf::Vector2f findIntersection(const Line& otherLine) {
        if (!std::isnan(slope) && !std::isnan(otherLine.slope)) {
            // General lines - solve for intersection point
            double xIntersection = (otherLine.intercept - intercept) / (slope - otherLine.slope);
            double yIntersection = slope * xIntersection + intercept;
            return sf::Vector2f(static_cast<float>(xIntersection), static_cast<float>(yIntersection));
        } else if (std::isnan(slope)) {
            // Vertical line and general line
            double xIntersection = intercept;
            double yIntersection = otherLine.slope * xIntersection + otherLine.intercept;
            return sf::Vector2f(static_cast<float>(xIntersection), static_cast<float>(yIntersection));
        } else if (std::isnan(otherLine.slope)) {
            // General line and vertical line
            double xIntersection = otherLine.intercept;
            double yIntersection = slope * xIntersection + intercept;
            return sf::Vector2f(static_cast<float>(xIntersection), static_cast<float>(yIntersection));
        } else {
            // Both lines are vertical, no intersection
            return sf::Vector2f(NAN, NAN);
        }
    }
};

int main() {
    // Example usage:
    Line line(2, 3, 5, 9);
    Line verticalLine(4, 2, 4, 8);

    std::cout << "Equation of the line: ";
    line.printEquation();

    std::cout << "Equation of the vertical line: ";
    verticalLine.printEquation();

    sf::Vector2f intersection = line.findIntersection(verticalLine);

    if (!std::isnan(intersection.x)) {
        std::cout << "Intersection Point: (" << intersection.x << ", " << intersection.y << ")" << std::endl;
    } else {
        std::cout << "Lines are parallel and do not intersect." << std::endl;
    }

    return 0;
}
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
		sf::Vector2f playerDir;

	public:
		Player(sf::Vector2f pos)
		{
			playerPos = pos;
			if (!playerTexture.loadFromFile("asset/img/player.png"))
			{
			  std::cout << "problem loading player image from file" << std::endl; 
			}
			playerSprite.setTexture(playerTexture);
			playerSprite.setPosition(playerPos);
		};

		void update()
		{
			this->get_input();
			playerSprite.setPosition(playerPos);
			add_debug_text("player dir: ", std::to_string(this->get_dir().x) + ", " + std::to_string(this->get_dir().y), "\n");
			playerDir.x = 0;
			playerDir.y = 0;
		};

		void get_input()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				playerDir.y = 1;	
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				playerDir.x = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				playerDir.y = -1;	
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				playerDir.x = 1;
			}
		};

		sf::Vector2f get_pos()
		{
			return playerPos;
		};
		sf::Vector2f get_dir()
		{
			return playerDir;
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
			(void)0;
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
			std::cout << "memory adress of vertices in sector: " << vertices << std::endl; 
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
	sf::VideoMode full_screen = sf::VideoMode(1920, 1080);
	sf::RenderWindow window(full_screen, "Math lol", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(2000);

	sf::Time deltaTime;
	sf::Clock clock;

	int sector_dat[8][2] = 
	{
		{200, 400},
		{500, 100},
		{1400, 100},
		{1700, 400},
		{1700, 700},
		{1400, 1000},
		{500, 1000},
		{200, 700}
 	};
	
  	Sector sector(8, sector_dat);
	
  	Player p(sf::Vector2f(400, 300)); 

	sf::Font font;
   	if (!font.loadFromFile("asset/fonts/Pixelify_Sans/font.ttf"))
	{
		std::cout << "please check that there is a font file" << std::endl;
	}
	
	debug_text_display.setFont(font);
	debug_text_display.setCharacterSize(20);
	debug_text_display.setFillColor(sf::Color::Green);

  	// run the program as long as the window is open
	sf::Vector2f (*sector_vertices) = sector.get_vertices();
	std::cout << "memory adress of vertices in sector: " << sector_vertices << std::endl; 
  	while (window.isOpen())
 	{
		deltaTime = clock.restart();

		//update
		//text
		debug_text = "--DEBUG TEXT--\n";
		add_debug_text("SECTOR VERTICES: ", "", "\n");	
		for (int i = 1; i < 8; i++)
		{
			add_debug_text("vector" + std::to_string(i) + ": ", std::to_string(sector_vertices[i].x) + ", " + std::to_string(sector_vertices[i].y), "\n");
		}
		add_debug_text("STATS:", "", "\n");
		add_debug_text("fps: ",std::to_string(std::round(1.f / deltaTime.asSeconds())), "\n");
		add_debug_text("video mode: ", std::to_string(window.getSize().x) + ", " + std::to_string(window.getSize().y), "\n");
		add_debug_text("player pos: ", std::to_string(p.get_pos().x) + ", " + std::to_string(p.get_pos().y), "\n");
	
	  	
		//player
		p.update();  

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
		 		window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}
			}
		}
		window.clear(sf::Color(50, 50, 50, 255));
	
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
