#include "Character.h"

Character::Character(std::string Location, float switchTime,int imgCount,float speed): animation(Location, switchTime,imgCount)
{
    float bodySizeX = 0.2f, bodySizeY =0.2f;
    this->location = Location;
    this->action = "Idle__00";
    texture.loadFromFile(Location+action+"0.png");
    
    scaleRect.x = bodySizeX;//(texture.getSize().x);
    scaleRect.y =  bodySizeY;//(texture.getSize().y);
    this->switchTime = switchTime;
    this->speed = speed;
    this->imageCount = imgCount;
    faceRight = true;
    this->body.setScale(scaleRect);
    this->body.setOrigin(sf::Vector2f(bodySizeX/2,bodySizeY/2));
    this->body.setTexture(texture);
    this->body.setPosition(500.0f, 600.0f);
}

Character::~Character()
{}

void Character::update(float deltaTime)
{
    action = "Idle__00";
    sf::Vector2f movement(0.0f, 0.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            movement.x = speed*deltaTime;
            action = "Run__00";
            faceRight = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            movement.x = -speed*deltaTime;
            action = "Run__00";
            faceRight = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            movement.y = 0;
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            movement.y = 0;
        }
        animation.update(action,faceRight,deltaTime,texture);
        body.move(movement);
        sf::Vector2f scaled(texture.getSize().x*scaleRect.x,texture.getSize().y*scaleRect.y);
        //body.setScale(scaled);
        body.setTextureRect(animation.rect);
        //body.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
}

void Character::draw(sf::RenderWindow &window)
{
    window.draw(body);
}