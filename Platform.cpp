#include "Platform.h"

Platform::Platform(sf::Vector2f size,sf::Vector2f position,std::string Type)
{
    std::string loc = "Wall/";
    
    texture.loadFromFile(loc + Type + ".png");
    sf::Vector2f scale;
    scale.x = size.x/texture.getSize().x;
    scale.y = size.y/texture.getSize().y;    
    texture.setRepeated(true);
    this->body.setScale(scale);
    this->body.setOrigin(size/2.0f);
    this->body.setPosition(position);
    //this->body.setColor(sf::Color(255,255,255));
    this->body.setTexture(texture);
    //this->body.setColor(sf::Color::White);

}

void Platform::draw(sf::RenderWindow &window)
{
    window.draw(body);
}