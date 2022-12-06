#include<iostream>
#include<string>
#include<algorithm>
#include<SFML/Graphics.hpp>
#include<fstream>


enum Canvas { Delete=-1, LTop=0, MTop, RTop, LMid, MMid, RMid, LBot, MBot, RBot,LPfrm, MPfrm, RPfrm};

void WriteMap(std::fstream& File, std::vector<std::vector<int>>& Tiles, int MapLength, int MapHeight, int Pixel);
void ReadMap(std::fstream& File, std::vector<std::vector<int>>& Tiles, int& MapLength, int& MapHeight, int &Pixel);


void MapEditor(std::string& FileLoc, bool Read, bool Write)
{

    sf::IntRect Value[13];


    int MapLength = 6*1080;
    int MapHeight = 720;
    int Pixel = 40;
    std::vector<std::vector<int>> Tiles (MapLength/Pixel,std::vector<int>(MapHeight/Pixel,-1));
    
    if(Read)
    {
        std::fstream File;
        File.open(FileLoc,std::ios::in);
        ReadMap(File,Tiles,MapLength,MapHeight,Pixel);
    }

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

    
    sf::RenderWindow window(sf::VideoMode(800,600),
        "Map Builder",
        sf::Style::Close
        // sf::Style::Fullscreen
    );



    window.setMouseCursorVisible(false);

    sf::Texture TileTex;

    TileTex.loadFromFile("Wall/pngegg.png");

    sf::Sprite Tile;
    Tile.setTexture(TileTex);
    Tile.setScale(sf::Vector2f(0.5263,0.5263)); 
    
    Canvas TileType = MTop;
    sf::IntRect rkt = Value[TileType];


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
        
        int Start = CurrentPos.x - 540 >= 0 ? (CurrentPos.x-540)/Pixel : 0;
        int End = MapLength - CurrentPos.x > 540? (MapLength - CurrentPos.x)/Pixel: Tiles.size();
        
        for(int i = Start; i < End; ++i)
        {
            for(int j = 0; j < Tiles[0].size(); ++j)
            {
                if(Tiles[i][j] >= 0)
                {
                    Tile.setPosition(sf::Vector2f(Pixel*i - 20,Pixel*j-20));
                    Tile.setTextureRect(Value[Tiles[i][j]]);
                    window.draw(Tile);
                }
            }
        }
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
        std::fstream File;
        File.open(FileLoc,std::ios::out);
        WriteMap(File,Tiles,MapLength, MapHeight,Pixel);
    }
}

void WriteMap(std::fstream& File, std::vector<std::vector<int>>& Tiles, int MapLength, int MapHeight, int Pixel)
{
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

void ReadMap(std::fstream& File, std::vector<std::vector<int>>& Tiles, int& MapLength, int& MapHeight,int& Pixel)
{
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

int main()
{
    std::string Loc = "Map/Level1";
    MapEditor(Loc,true,true);
}
