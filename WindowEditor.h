//
// Created by Sam Carozzi on 11/30/22.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <cstdlib>
#include "TileEditor.h"
#include "Random.h"


#ifndef PROJECT3_TEXTURES_H
#define PROJECT3_TEXTURES_H


using namespace std;

struct WindowEditor{

    vector<vector<TileEditor>> tiles;
    static unordered_map<string, int> board;
    static unordered_map<string, sf::Sprite> buttons;
    static unsigned int width;
    static unsigned int height;
    static vector<sf::Sprite> minesRemainingDisplay;
    vector<sf::Sprite> minesRemaining;
    bool debugOn = false;
    int mineCount;
    bool gameWon = false;
    bool gameLost = false;


    static void createBoard();
    void startNewGame();

    void loadBoxes(string name);
    void generateMines();
    void loadTiles(string name);
    void loadButtons();

    int minesSurrounding(int xIndex, int yIndex);
    void spacesSurrounding(int xIndex, int yIndex);
    void Debug();
    int calcMinesRemaining();


    void LeftSettings(sf::Vector2<int>& mousePos);
    void RightSettings(sf::Vector2<int>& mousePos);
    void TestFile(string filename);

    void Victory();
    void VictoryActions();
    void LossActions();



};
#endif //PROJECT3_TEXTURES_H