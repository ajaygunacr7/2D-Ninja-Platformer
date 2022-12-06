#pragma once
#include"Headers.h"

class Collider
{
public:
    // Collider(){body = nullptr;}
    Collider(sf::Sprite& body);
    ~Collider();

    void MakeCollider(sf::Sprite& body)
    {
        this->body = body;
    }


    sf::Vector2f CheckCollision(Collider&, float);


    void move(sf::Vector2f movement){body.move(movement);}

private:
    sf::Sprite& body;
};