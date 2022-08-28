#include "Collider.h"

Collider::Collider(sf::RectangleShape& body):body(body)
{
}

Collider::~Collider(){}

sf::Vector2f Collider::CheckCollision(Collider other, float restitution)
{
    sf::Vector2f otherMovement(0.0f, 0.0f);
    sf::Vector2f thisPosition = this->body.getPosition();
    sf::Vector2f otherPosition = other.body.getPosition();
    sf::Vector2f thisHalfSize = this->body.getSize()/2.0f;
    sf::Vector2f otherHalfSize = other.body.getSize()/2.0f;

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