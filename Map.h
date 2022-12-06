#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<SFML/Graphics.hpp>
#include<fstream>
#include "Collider.h"
#include "Character.h"

enum Canvas { Delete=-1, LTop=0, MTop, RTop, LMid, MMid, RMid, LBot, MBot, RBot,LPfrm, MPfrm, RPfrm};

class Map
{
    private:
        
        sf::IntRect Value[13];

        int MapLength;
        int MapHeight;
        int Pixel;
        std::vector<std::vector<int>> Tiles;
        std::string FileLoc;

        sf::Texture TileTex;
        sf::Sprite Tile,CTile;

        Canvas TileType;

        Collider C;

    public:

        Map(std::string& FileLoc);

        Collider getCollider() { return Collider(Tile);}

        void WriteMap();
        void ReadMap();
        void MapEditor(bool Read, bool Write);
        
        void draw(sf::RenderWindow& window,sf::Vector2f);

        void CollisionTest(Character& Player);
};
