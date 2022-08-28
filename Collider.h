#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
    Collider(sf::RectangleShape& body);
    ~Collider();

    sf::Vector2f CheckCollision(Collider, float);
    void move(sf::Vector2f movement){body.move(movement);}

private:
    sf::RectangleShape& body;
};