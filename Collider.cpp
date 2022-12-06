#include "Collider.h"
#include<iostream>


Collider::Collider(sf::Sprite& body): body(body)
{
}

Collider::~Collider(){}

sf::Vector2f Collider::CheckCollision(Collider& other, float restitution = 1.0f)
{
    sf::Vector2f otherMovement(0.0f, 0.0f);
    
    sf::Vector2f thisPosition = this->body.getPosition();
    sf::Vector2f otherPosition = other.body.getPosition();
    // std::cout<<"Hello";

    sf::Vector2f otherScale = other.body.getScale();
    sf::Vector2f thisScale = this->body.getScale();


    sf::Vector2f thisHalfSize;
    thisHalfSize.x = (float) (this->body.getTextureRect().width*thisScale.x)/2.f;
    thisHalfSize.y = (float) (this->body.getTextureRect().height*thisScale.y)/2.f;

    sf::Vector2f otherHalfSize;
    otherHalfSize.x = other.body.getTexture()->getSize().x*otherScale.x/2.f;
    otherHalfSize.y = other.body.getTexture()->getSize().y*otherScale.y/2.f;
    // otherHalfSize.x = 20;
    // otherHalfSize.y = 20;
    // otherHalfSize =     thisHalfSize ;


    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);


    if(intersectX < 0.0f && intersectY < 0.0f)
    {   
        sf::Vector2f thisMovement(0.0f, 0.0f);
        if(intersectX > intersectY)
        {
            if(deltaX > 0.0f)
            {
                thisMovement.x = intersectX*(1.0f - restitution);
                otherMovement.x = -intersectX*restitution;
            }
            else
            {
                thisMovement.x = -intersectX*(1.0f -restitution);
                otherMovement.x = intersectX*restitution;
            }
        }
        else
        {
            if(deltaY > 0.0f)
            {
                thisMovement.y = intersectY*(1.0f -restitution);
                otherMovement.y = -intersectY*restitution;
            }
            else
            {
                thisMovement.y = -intersectY*(1.0f -restitution);
                otherMovement.y = intersectY*restitution;
            }
        }
        this->body.move(thisMovement);
        //other.move(otherMovement);
       
    }

    return otherMovement;
}