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

class Wall
{
    private:
        [[maybe_unused]]double x1, y1, x2, y2;
        sf::VertexArray line;;
    public:
        Wall()
        {
            std::cout << "Wall created" << std::endl;
        };
        Wall(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2)
        {
          line = sf::VertexArray(sf::Lines, 2);
          line[0].position = sf::Vector2f(x1, y1);
          line[1].position = sf::Vector2f(x2, y2);
        }

        void draw(sf::RenderWindow *window)
        {
          window->draw(line);
        }
};


class Sector
{
    private:
        int (*vertices)[2];
        int vertices_length;
        Wall (* walls);

    public:
        Sector(int num_vertices, int sector_dat[][2]) : vertices(new int[num_vertices][2]), vertices_length(num_vertices), walls(new Wall[num_vertices])
        {
            set_vertices(num_vertices, sector_dat);
            set_walls();
        }

        void set_vertices(int num_vertices, int sector_dat[][2])
        {
            walls = new Wall[num_vertices];
            for(int i = 0; i < num_vertices; i++) {
                vertices[i][0] = sector_dat[i][0];
                vertices[i][1] = sector_dat[i][1];
            }
        }

        int (* get_vertices())[2]
        {
            return vertices;
        }

        void set_walls()
        {
            for (int i = 0; i < vertices_length; i++)
            {
                if (i == vertices_length - 1)
                {
                    walls[i] = Wall(vertices[i][0], vertices[i][1], vertices[0][0], vertices[0][1]);   
                }
                else
                {
                    walls[i] = Wall(vertices[i][0], vertices[i][1], vertices[i + 1][0], vertices[i + 1][1]);
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

  sf::Time deltaTime;
  sf::Clock clock;

  sf::Texture pTexture;
  if (!pTexture.loadFromFile("img/player.png"))
  {
    std::cout << "problem loading player image from file" << std::endl; 
  }
  
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
  int (*vertices)[2] = sector.get_vertices();

  sf::Sprite p;
  p.setTexture(pTexture);

  double px = 300;
  double py = 200;

  // run the program as long as the window is open
  while (window.isOpen())
  {
    deltaTime = clock.restart();

    p.setPosition(px, py);

    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear(sf::Color(100, 100, 100, 255));
    
    sector.draw_walls(&window);
    window.draw(p);

    window.display();
  }
}
