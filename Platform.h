#pragma once
#include<SFML/Graphics.hpp>
#include <string.h>
#include "Collider.h"

class Platform
{
public:
    Platform(sf::Vector2f size,sf::Vector2f position,std::string type);
    ~Platform() {}

    void draw(sf::RenderWindow& window);
    //Collider getCollision(){return Collider(body);}
private:
    sf::Sprite body;
    sf::Texture texture;
};