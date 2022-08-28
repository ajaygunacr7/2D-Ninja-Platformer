#include<iostream>
#include<SFML/Graphics.hpp>
#include "Collider.h"
#include "Character.h"
#include "Platform.h"

static const float Window_Width = 1280;
static const float Window_Height = 720;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(Window_Height*aspectRatio,Window_Height);

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(Window_Width,Window_Height), "2D Ninja Platfomer", sf::Style::Close | sf::Style::Resize);
    Character player("Player/",0.05f, 10, 100);
    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::View view;
    Platform platform(sf::Vector2f(500.0f, 100.0f),sf::Vector2f(100.0f, 575.0f),"BrickWall");

    while(window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized: 
                ResizeView(window, view);
                break;
            default:
                break;
            }
        }
        player.update(deltaTime);
        view.setCenter(player.getPoisition());
        //platform.getCollision().CheckCollision(player.getCollision(),0.0f);
        window.clear();
        window.setView(view);
        platform.draw(window);
        player.draw(window);
        window.display();
    }

}