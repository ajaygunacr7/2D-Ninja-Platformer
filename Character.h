#pragma once
#include "Animation.h"
#include "Collider.h"

class Character
{
    std::vector<std::string> SActions{"Idle__00","Jump__00","Run__00","Glide_00","Slide__00"};
    
public:

    Character(std::string Location, float switchTime,int imgCount,float speed);
    ~Character();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    sf::Vector2f getPosition() {return body.getPosition();}

    Collider getCollision(){return PC;}


    void setVerticalSpeed(float v ){verticalSpeed = v;}  

    void move(sf::Vector2f& movement){
        body.move(movement);
    }

    void setGrounded(bool grounded){
        this->grounded = grounded;
    }

private:
    Animation animation;
    
    sf::Vector2f scale;
    sf::Sprite body;
    std::string location;

    sf::Vector2i BodySize;

    sf::Texture texture;

    int CurrAct;

    int imageCount;

    float switchTime;
    bool faceRight;
    int falling;
    float speed, verticalSpeed;
    int maxGlideSpeed,maxSpeed; 
    bool canJump;
    bool grounded;

    Collider PC;

};