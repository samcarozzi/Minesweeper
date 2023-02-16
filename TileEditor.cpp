//
// Created by Sam Carozzi on 12/3/22.
//

#include "TileEditor.h"

unordered_map<string, sf::Texture> TileEditor::textures;

void TileEditor::addSprite(sf::Sprite s) {
    sprites.push_back(s);
}

void TileEditor::LoadTexture(string textureName, string filename) {

    textures[textureName];
    textures[textureName].loadFromFile(filename);

}

void TileEditor::LoadTextures() {
    LoadTexture("mine","images/mine.png");
    LoadTexture("hiddenTile","images/tile_hidden.png");
    for(int i = 1; i<9; i++){
        string name = "images/number_" + to_string(i);
        string numFile = name + ".png";
        LoadTexture(name, numFile);
    }
    LoadTexture("flag","images/flag.png");
    LoadTexture("revealedTile","images/tile_revealed.png");
    LoadTexture("face_happy","images/face_happy.png");
    LoadTexture("face_win","images/face_win.png");
    LoadTexture("face_lose","images/face_lose.png");
    LoadTexture("digits","images/digits.png");
    LoadTexture("debug","images/debug.png");
    for(int i = 1; i<4; i++){
        string name = "images/test_" + to_string(i);
        string numFile = name + ".png";
        LoadTexture(name, numFile);
    }
}

bool TileEditor::containsMine() {
    if(&textures["mine"] == sprites[1].getTexture())
        return true;
    else
        return false;
}

vector<sf::Sprite>::iterator TileEditor::findSprite(string spriteName) {
    for(auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
        if (&textures[spriteName] == iter->getTexture())
            return iter;
    }
    //else
    return sprites.end();
}

void TileEditor::removeSprite(string spriteName) {
    for(auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
        if (&textures[spriteName] == iter->getTexture())
            sprites.erase(iter);
    }
}

bool TileEditor::isEmptyTile() {
    for(auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
        if(iter->getTexture() == &textures["revealedTile"] || iter->getTexture() == &textures["hiddenTile"]) {
            continue;
        }
        else{
            for(auto ir = textures.begin(); ir != textures.end(); ++ir) {
                if (iter->getTexture() == &ir->second) {
                    return false;
                }
            }
        }
    }
    return true;
}


