#include "Headers.h"
#include "Collider.h"
#include "Character.h"
// #include "Platform.h"
#include "Map.h"

static const float Window_Width = 800;
static const float Window_Height = 600;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(Window_Height*aspectRatio,Window_Height);

}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(Window_Width,Window_Height),
         "2D Ninja Platfomer",
          sf::Style::Close | sf::Style::Resize
    );

    std::string FileLoc = "Map/Level1";
    Map map(FileLoc);

    map.ReadMap();

    Character player("Player/",0.05f, 10, 100);
    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::View view;
    
    sf::Vector2f movement;
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

        sf::Vector2f PPos = player.getPosition();

        view.setCenter(PPos);
        
        // movement = platform.getCollision().CheckCollision(player.getCollision(),1.0f);
        // if(movement.y != 0.0f)
        //     player.setGrounded(true);

        map.CollisionTest(player);

        window.clear();
        
        window.setView(view);

        map.draw(window,player.getPosition());

        player.draw(window);

        window.display();
    }

}
