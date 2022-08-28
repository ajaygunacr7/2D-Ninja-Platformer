#pragma once

#include<SFML/Graphics.hpp>
#include <string.h>

class Animation
{
public:
    Animation(std::string Location, float switchTime,int imageCount);
    ~Animation();
    sf::IntRect rect;
    void update(std::string,bool, float,sf::Texture &);
private:
    int imageCount;
    int CurrentImage;
    float switchTime;
    std::string location,action;
    float totalTime;
    bool faceTop = false;
    bool faceRight = true;
};