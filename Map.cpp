#include "Map.h"

Map::Map(std::string& FileLoc): C(CTile), FileLoc(FileLoc) // Collider(Tile), C(Tile)
{
    ReadMap();

    TileTex.loadFromFile("Wall/pngegg.png");
    Tile.setTexture(TileTex);
    Tile.setScale(sf::Vector2f(0.5263,0.5263)); 
    
    CTile = Tile;
    TileType = MTop;

    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            Value[i*3 + j].height = 76;
            Value[i*3 + j].width = 78;
            switch(i)
            {
                case 0: Value[i*3+j].top = 18;
                        break;
                case 1: Value[i*3+j].top = 102;
                        break;
                case 2: Value[i*3+j].top = 188;
                        break;
                case 3: Value[i*3+j].top = 272;
                        break;
            }
            switch(j)
            {
                case 0: Value[i*3+j].left = 97;
                        break;
                case 1: Value[i*3+j].left = 184;
                        break;
                case 2: Value[i*3+j].left = 268;
                        break;
            }
        
            if((i == 1 && j == 1) || i+j == 1 || i+j == 3)
            {
                Value[i*3 + j].width = 76;
            }
        }
    }
    Value[Canvas::Delete] = Value[Canvas::MMid];
}


void Map::MapEditor(bool Read, bool Write)
{

    if(Read)
    {
        std::fstream File;
        File.open(FileLoc,std::ios::in);
        ReadMap();
    }

    
    sf::RenderWindow window(sf::VideoMode(800,600),
        "Map Builder",
        sf::Style::Close
        // sf::Style::Fullscreen
    );



    window.setMouseCursorVisible(false);


    sf::View Camera;
    Tile.setPosition(100,100);


    Camera.setSize(sf::Vector2f(1080,720));
    Camera.setCenter(540,360);

    Tile.setOrigin(38,38);

    sf::Vector2i CPos = sf::Vector2i(0,0);


    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
            TileType = LTop;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
            TileType = MTop;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
            TileType = RTop;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
            TileType = LMid;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
            TileType = MMid;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6))
            TileType = RMid;
            
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7))
            TileType = LBot;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8))
            TileType = MBot;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9))
            TileType = RBot;
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            TileType = LPfrm;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            TileType = MPfrm;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            TileType = RPfrm;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            TileType = Delete;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i RPos = (sf::Vector2i) window.mapPixelToCoords(sf::Mouse::getPosition(window));
            RPos.x/= Pixel;
            RPos.y/= Pixel;
            Tiles[RPos.x][RPos.y] = TileType;
        }

        auto CurrentPos = Camera.getCenter();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {    
            if(CurrentPos.x > 540)
                Camera.move( sf::Vector2f(-2,0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {    
            if(MapLength - CurrentPos.x > 540)
                Camera.move( sf::Vector2f(2,0));
        }

        window.clear(sf::Color(135,206,235));


        Tile.setColor(sf::Color::White);
        

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            window.close();


        Tile.setTextureRect(Value[TileType]);
        
        if(TileType == Canvas::Delete)
        {
            Tile.setTextureRect(Value[Canvas::MMid]);
            Tile.setColor(sf::Color(255,13,26));
        }

        // Getting Position of Mouse as Grid
        sf::Vector2f MPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        MPos.x  = (int)(MPos.x/Pixel) * Pixel; 
        MPos.y  = (int)(MPos.y/Pixel) * Pixel;
        // Considering Offset of Mouse     
        MPos.x-= 20;
        MPos.y -=20;


        Tile.setPosition((sf::Vector2f)MPos);
        window.setView(Camera);
        window.draw(Tile);
        window.display();

    }

    if(Write)
    {
        WriteMap();
    }
}

void Map::WriteMap()
{
    std::fstream File(FileLoc,std::ios::out);

    File << Pixel << " " << MapLength << " " << MapHeight << std::endl;

    for(int i = 0; i < Tiles.size(); ++i)
    {
        for(int j = 0; j < Tiles[0].size()-1; ++j)
        {
            File << Tiles[i][j] << " ";
        }
        File << Tiles[i][Tiles[0].size()-1];
        File << std::endl;
    }
}

void Map::ReadMap()
{
    std::fstream File(FileLoc,std::ios::in);

    File >> Pixel >> MapLength >> MapHeight;

    Tiles.resize(MapLength/Pixel, std::vector<int>(MapHeight/Pixel,-1));
    
    for(int i = 0; i < Tiles.size(); ++i)
    {
        for(int j = 0; j < Tiles[0].size(); ++j)
        {
            File >> Tiles[i][j];
        }
    }
}

void Map::draw(sf::RenderWindow& window, sf::Vector2f CurrentPos)
{
        int Start = CurrentPos.x - 540 >= 0 ? (CurrentPos.x-540)/Pixel : 0;
        int End = MapLength - CurrentPos.x > 540? (MapLength - CurrentPos.x)/Pixel: Tiles.size();
        
        for(int i = Start; i < End; ++i)
        {
            for(int j = 0; j < Tiles[0].size(); ++j)
            {
                if(Tiles[i][j] >= 0)
                {
                    Tile.setPosition(sf::Vector2f(Pixel*i - 20,Pixel*j-20));
                    // std::cout << Tile.getPosition().x << ", " << Tile.getPosition().y << std::endl;
                    Tile.setTextureRect(Value[Tiles[i][j]]);
                    window.draw(Tile);
                }
            }
        }
}
void Map::CollisionTest(Character& Player)
{
    Collider PC = Player.getCollision();
    

    sf::Vector2f Pos;
    // Pos = window.mapPixelToCoords((sf::Vector2i)Player.getPosition());
    Pos = Player.getPosition();
    Pos.x  = (int)(Pos.x/Pixel); 
    Pos.y  = (int)(Pos.y/Pixel);


    Pos.x = Pos.x == 0? 0 : Pos.x-1;
    Pos.y = Pos.y == 0? 0 : Pos.y-1;

    if(Tiles[Pos.x-1][Pos.y] != -1)
        Player.setGrounded(true);
    else
        Player.setGrounded(false);

    Pos.x *= Pixel;
    Pos.y *= Pixel;



    for(int itr = 0; itr<2; ++itr){
    // std::cout<< Pos.x << ", " << Pos.y <<  ".  " << Pixel << std::endl;
    // CTile = Tile;
    for(int i = 0; i < 3; ++i )
    {
        for(int j = 0; j < 3; ++j )
        {

            if(Tiles[Pos.x/Pixel+i][Pos.y/Pixel+j] != -1)
            { 

                CTile = Tile;
                sf::Vector2f Offset(20.0f,20.0f);
                
                // if(Tiles[Pos.x/Pixel+i][Pos.y/Pixel+j+1] != -1 && Tiles[Pos.x/Pixel+i][Pos.y/Pixel+j-1] != -1)
                // { 
                //     auto S = Tile.getScale();
                //     S.y*=3;
                //     CTile.setScale(S);
                //     CTile.setOrigin(Offset);
                //     Offset.x = 60;
                // }
                // else if(Tiles[Pos.x/Pixel+i][Pos.y/Pixel+j+1] != -1 || Tiles[Pos.x/Pixel+i][Pos.y/Pixel+j-1] != -1)
                // {
                //     auto S = Tile.getScale();
                //     S.y*=2;
                //     CTile.setScale(S);
                //     CTile.setOrigin(Offset);
                //     Offset.x = 60;

                // }

                CTile.setPosition(sf::Vector2f(Pos.x + i*Pixel - Offset.x, Pos.y + j*Pixel-Offset.y));
                auto move = C.CheckCollision(PC,1.0f);

                if(move.x!=0.0f && (Tiles[Pos.x/Pixel+i][Pos.y/Pixel+j+1] != -1 || Tiles[Pos.x/Pixel+i][Pos.y/Pixel+j-1] != -1))
                    move.x = 0.0f;

                // if(move.y > 0.0f && Tiles[Pos.x/Pixel+i+1][Pos.y/Pixel+j] != -1)
                // {
                //     Player.setVerticalSpeed(0.0f);
                //     move.y = (float)(Pos.y - Player.getPosition().y)/2;
                //     Player.setGrounded(true);
                // }

                    


                Player.move(move);

                if(move.y != 0.0f)
                {
                    Player.setVerticalSpeed(0.0f);
                    Player.setGrounded(true);
                }
                // Player.move(getCollider().CheckCollision(PC,1.0f));
           }
        }
    }
    }

}