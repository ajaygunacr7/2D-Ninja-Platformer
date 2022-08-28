#pragma once
#include "Animation.h"
#include "Collider.h"

class Character
{
public:
    Character(std::string Location, float switchTime,int imgCount,float speed);
    ~Character();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    sf::Vector2f getPoisition() {return body.getPosition();}

    //Collider getCollision(){return Collider(body);}

    void move(sf::Vector2f movement){body.move(movement);}


private:
    Animation animation;
    sf::Vector2f scaleRect;
    sf::Sprite body;
    std::string location;
    std::string action;
    sf::Texture texture;
    int imageCount;
    float switchTime;
    bool faceRight;
    float speed;

};