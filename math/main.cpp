#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <fstream>
/*
#define width = 800
#define height = 600

class Wall
{
  public:
    sf::VertexArray line;

    Wall(sf::Vector2f start, sf::Vector2f end)
    {
      line = sf::VertexArray(sf::Lines, 2);
      line[0].position = start;
      line[1].position = end;
    }
    void draw(sf::RenderWindow window)
    {
      window.draw(line);
    }
};

class Sector
{
  public:
    Sector(sf::Vector2f sector_dat[])
    {
      Wall walls[] = {};
      for (int i = 0; i < 4; i++)
      {
        walls[i] = Wall(sector_dat[i], sector_dat[i+1]);
      }
    }
};

sf::Vector2f sector_dat[] = {
        sf::Vector2f(2.f, 1.f),
        sf::Vector2f(3.f, 2.f),
        sf::Vector2f(2.f, 3.f),
        sf::Vector2f(1.f, 2.f),
        sf::Vector2f(2.f, 1.f)
      };
  Sector sector = Sector(sector_dat);
*/

void draw_sector_dots (sf::CircleShape dots[4], sf::RenderWindow *window)
{
  for (int i = 0; i < 4; i++)
  {
    window->draw(dots[i]);
  }
}

int main ()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Math lol");
  window.setVerticalSyncEnabled(true);

  sf::Time deltaTime;
  sf::Clock clock;

  sf::Texture pTexture;
  if (!pTexture.loadFromFile("img/player.png"))
  {
    std::cout << "problem loading player image from file line:12" << std::endl; 
  }

  sf::Sprite p;
  p.setTexture(pTexture);


  int const num_walls = 4;
  sf::Vector2f vertices[num_walls] = 
  {
        sf::Vector2f(2.f*100, 1.f*100),
        sf::Vector2f(3.f*100, 2.f*100),
        sf::Vector2f(2.f*100, 3.f*100),
        sf::Vector2f(1.f*100, 2.f*100),
  };
  sf::CircleShape dots[4];
  
  for (int i = 0; i < 4; i++)
  {
    dots[i] = sf::CircleShape(3);
    dots[i].setPosition(vertices[i]);
  }


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
    
    window.draw(p);
    draw_sector_dots(dots, &window);

    window.display();
  }
}
