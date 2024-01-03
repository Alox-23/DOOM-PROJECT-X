#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Player
{
	private:
		sf::Texture playerTexture;
		sf::Sprite playerSprite;
		sf::Vector2f playerPos;
		double playerRotSpeed;
		double playerSpeed;
		double playerAngle;

	public:
		Player(sf::Vector2f pos);

		void update();
		
		void reset_var();

		void movement();

		sf::Vector2f get_pos();

		double get_angle();

		sf::Vector2f get_dir();

		void draw(sf::RenderWindow *window);
};
#endif
