//
// Created by Sam Carozzi on 12/3/22.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>


#ifndef PROJECT3_TILEEDITOR_H
#define PROJECT3_TILEEDITOR_H



using namespace std;

struct TileEditor{

    vector<sf::Sprite> sprites;
    static unordered_map<string, sf::Texture> textures;


    static void LoadTextures();
    static void LoadTexture(string textureName, string filename);
    void addSprite(sf::Sprite s);

    bool isEmptyTile();
    bool containsMine();
    vector<sf::Sprite>::iterator findSprite(string spriteName);
    void removeSprite(string spriteName);

};

#endif //PROJECT3_TILEEDITOR_H