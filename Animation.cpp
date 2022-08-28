#include "Animation.h"

Animation::Animation(std::string Location, float switchTime,int imageCount)
{
    this->location = Location;
    this->action = "Idle__00";
    sf::Texture texture;
    texture.loadFromFile(Location + action + "0.png");


    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    CurrentImage = 0;
    rect.width = texture.getSize().x; // static_cast<float>(imageCount.x);
    rect.height = texture.getSize().y; // static_cast<float>(imageCount.y);
}

Animation::~Animation()
{}

void Animation::update(std::string action,bool faceRight, float deltaTime,sf::Texture &texture)
{    
    this->totalTime += deltaTime;
    if(this->action.compare(action)!=0)
    {
        CurrentImage = 0;
        this->action = action;
    }
    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        CurrentImage++;
        if(CurrentImage == imageCount)
            CurrentImage = 0;
    }
    std::string file;
    file = location + action + std::to_string(CurrentImage) +".png";
    texture.loadFromFile(file);
    if(faceRight == true)
    {
        rect.left= 0;
        rect.width = abs(texture.getSize().x);
    }
   else
   {
        rect.left = abs(texture.getSize().x);
        rect.width = -abs(texture.getSize().x);

   }
}