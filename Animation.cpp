#include "Animation.h"
#include<iostream>
#include<cmath>
enum Actions {
    Idle = 0,
    Jump,
    Run,
    Glide,
    Slide
};



Animation::Animation(std::string Location, float switchTime,int imageCount)
{
    this->location = Location;
    AnimAct = Idle;
    sf::Texture texture;
    texture.loadFromFile(Location + SActions[Idle] + "0.png");


    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    CurrentImage = 0;
    rect.width = texture.getSize().x; // static_cast<float>(imageCount.x);
    rect.height = texture.getSize().y; // static_cast<float>(imageCount.y);
}

Animation::~Animation()
{}

void Animation::update(int& CurrAct,bool faceRight, float deltaTime,sf::Texture &texture,int falling=0)
{    
    this->totalTime += deltaTime;

    if(AnimAct != CurrAct)
    {
        CurrentImage = 0;
        AnimAct = CurrAct;
    }
    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        if(CurrAct == Jump)
        {
            if(falling == -1 && CurrentImage != 9)
            {
                CurrentImage++;
            }
            else if(falling == 1 && CurrentImage != 4)
            {
                CurrentImage++;
            }
        }
        else
            CurrentImage++;
        if(CurrentImage == imageCount)
            CurrentImage = 0;
    }

    

    std::string file;
    file = location + SActions[CurrAct] + std::to_string(CurrentImage) +".png";
    texture.loadFromFile(file);
    if(faceRight == true)
    {
        rect.left= 0;
        rect.width = texture.getSize().x;
    }
   else
   {
        rect.left = texture.getSize().x;
        rect.width = -texture.getSize().x;

   }
}
