#pragma once

#include"Headers.h"


class Animation
{

public:
    std::vector<std::string> SActions{"Idle__00","Jump__00","Run__00","Glide_00","Slide__00"};

    Animation(std::string Location, float switchTime,int imageCount);
    ~Animation();
    sf::IntRect rect;
    void update(int&, bool , float,sf::Texture &, int);
private:
    int imageCount;
    int CurrentImage;
    float switchTime;
    std::string location;
    int AnimAct;
    float totalTime;
    bool faceTop = false;
    bool faceRight = true;
};