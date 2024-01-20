#include "player.h"
#include <iostream>

Player::Player(sf::Vector2f pos)
{
	this->playerPos = pos;

    if (!this->playerTexture.loadFromFile("asset/img/player.png"))
        {
          std::cout << "problem loading player image from file" << std::endl; 
        }
    this->playerShape.setTexture(playerTexture);
    this->playerShape.setPosition(playerPos);
    
	this->playerSpeed = 0.2;
	this->playerAngle = 90;
	this->playerRotSpeed = 5;
};

void Player::update()
{
	this->movement();
};

void Player::movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->playerDir.x = std::cos(this->playerAngle * M_PI/180) * 180/M_PI;
        this->playerDir.y = std::sin(this->playerAngle * M_PI/180) * 180/M_PI;
    }  
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->playerDir.x = -std::cos(this->playerAngle * M_PI/180) * 180/M_PI;
        this->playerDir.y = -std::sin(this->playerAngle * M_PI/180) * 180/M_PI;
    } 
    else 
    {
        this->playerDir.x = 0;
        this->playerDir.y = 0; 
    }

    this->playerPos.x += this->playerDir.x * this->playerSpeed;
    this->playerPos.y += this->playerDir.y * this->playerSpeed;

	this->playerShape.setPosition(this->playerPos);
    this->playerShape.setRotation(this->playerAngle);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->playerAngle -= this->playerRotSpeed;
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->playerAngle += this->playerRotSpeed;
	}

    /*
    if (this->playerAngle > 360)
    {
        this->playerAngle = this->playerAngle - 360;
    }
    if (this->playerAngle < 0)
    {
        this->playerAngle = 360 - this->playerAngle;
    }
    */
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
	window->draw(this->playerShape);
};
