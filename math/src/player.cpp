#include "player.h"
#include <iostream>

Player::Player(sf::Vector2f pos)
{
	this->playerPos = pos;
	if (!this->playerTexture.loadFromFile("asset/img/player.png"))
	{
	  std::cout << "problem loading player image from file" << std::endl; 
	}
	this->playerSprite.setTexture(playerTexture);
	this->playerSprite.setPosition(playerPos);

	this->playerSpeed = 2;
	this->playerAngle = 90;
	this->playerRotSpeed = 5;
};

void Player::update()
{
	this->movement();
};

void Player::movement()
{
	double sin_a = std::sin(this->playerAngle);
	double cos_a = std::cos(this->playerAngle);
	double dx = 0;
	double dy = 0;
	double speed_sin = this->playerSpeed * sin_a;
	double speed_cos = this->playerSpeed * cos_a;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dx += speed_cos;
		dy += speed_sin;
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dx += -speed_cos;
		dy += -speed_sin;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dx += -speed_sin;
		dy += speed_cos;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dx += speed_sin;
		dy += -speed_cos;
	}
	
	this->playerPos.x += dx;
	this->playerPos.y += dy;
	this->playerSprite.setPosition(this->playerPos);
	this->playerSprite.setRotation(this->playerAngle);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->playerAngle -= this->playerRotSpeed;
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->playerAngle += this->playerRotSpeed;
	}
	playerAngle %= M_PI*2;
};

sf::Vector2f Player::get_pos()
{
	return this->playerPos;
};

double Player::get_angle()
{
	return this->playerAngle;
}

void Player::draw(sf::RenderWindow *window)
{
	window->draw(this->playerSprite);
};
