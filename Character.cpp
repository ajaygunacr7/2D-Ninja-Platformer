#include "Character.h"

enum Actions {
    Idle = 0,
    Jump,
    Run,
    Glide,
    Slide
};

std::vector<std::string> SActions{"Idle__00","Jump__00","Run__00","Glide_00","Slide__00"};

Character::Character(std::string Location, float switchTime,int imgCount,float speed): animation(Location, switchTime,imgCount),PC(body)
{
    BodySize = sf::Vector2i(30,44);
    this->location = Location;
    CurrAct = Idle;
    texture.loadFromFile(Location+SActions[Idle]+"0.png");
    this->falling = false;
    this->grounded = false;
    
    scale.x = (float) BodySize.x/(texture.getSize().x);
    scale.y = (float) BodySize.y/(texture.getSize().y);

    this->switchTime = switchTime;
    this->speed = speed;
    this->imageCount = imgCount;

    maxSpeed = 200;
    maxGlideSpeed = 80;

    faceRight = true;

    this->body.setScale(scale);
    this->body.setOrigin(sf::Vector2f(BodySize.x/2,BodySize.y/2));
    this->body.setTexture(texture);
    this->body.setPosition(80.0f, 400.0f);

}

Character::~Character()
{}

void Character::update(float deltaTime)
{

    if(grounded == true)
    {
        verticalSpeed = 0.0f;
        falling = 0;
        CurrAct = Idle;
    }
    else 
        verticalSpeed += 200*deltaTime;
    
    if(verticalSpeed > 0)
    {
        falling = 1;
        CurrAct = Jump;
    }
    else if (verticalSpeed < 0)
    {
        falling = -1;
        CurrAct = Jump;
    }
        
    sf::Vector2f movement(0.0f, 0.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            movement.x = speed*deltaTime;
            if(verticalSpeed==0)
                CurrAct = Run;
            faceRight = true;

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            movement.x = -speed*deltaTime;
            if(verticalSpeed==0)
                CurrAct = Run;
            faceRight = false;
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            
            verticalSpeed = -200;
            falling = 1;
            grounded = false;
            CurrAct = Jump;

            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            movement.y = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
        {
            if(CurrAct!=Glide)
                verticalSpeed /= 1.01;
            if(falling != 0)
            {
                verticalSpeed -= 100*deltaTime;     
                CurrAct = Glide;
            }
        }
        if(verticalSpeed > 0)
            falling = -1;

        verticalSpeed = verticalSpeed > maxSpeed ? maxSpeed : verticalSpeed;
        movement.y += verticalSpeed*deltaTime;
        animation.update(CurrAct,faceRight,deltaTime,texture,falling);
        body.move(movement);
        
        
        // sf::Vector2f scaled((float)BodySize.x/texture.getSize().x,(float)BodySize.x/texture.getSize().y);

        // body.setScale(scaled);

        body.setTextureRect(animation.rect);
        // body.setOrigin((float)(texture.getSize().x*body.getScale().x/2),(float)(texture.getSize().y*body.getScale().y/2));
}

void Character::draw(sf::RenderWindow &window)
{
    window.draw(body);
}