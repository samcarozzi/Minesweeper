//
// Created by Sam Carozzi on 11/30/22.
//

#include "WindowEditor.h"


unordered_map<string, int> WindowEditor::board;
unordered_map<string, sf::Sprite> WindowEditor::buttons;
vector<sf::Sprite> WindowEditor::minesRemainingDisplay;
unsigned int WindowEditor::width;
unsigned int WindowEditor::height;



void WindowEditor::createBoard() {
//board creation
    int width;
    int height;
    int mineCount;
    int tileCount;

    ifstream file("config.cfg");
    if(file.is_open()) {

        file >> width;
        file >> height;
        file >> mineCount;
        file >> tileCount;

        tileCount = width * height;
        width *= 32;
        height *= 32;
    }
    else{
        cout << "error";
    }

    board = {{"width",width},{"height",height},{"mineCount",mineCount},{"tileCount",tileCount}};
    WindowEditor::width = board["width"];
    WindowEditor::height = board["height"];
}

void WindowEditor::startNewGame() {
    tiles.clear();
    gameWon = false;
    gameLost = false;
    loadBoxes("revealedTile");
    loadButtons();
    generateMines();
    calcMinesRemaining();

    loadTiles("hiddenTile");
}

void WindowEditor::loadBoxes(string name) {

    mineCount = board["mineCount"];

    for (unsigned int i = 0; i < height/32; i++) {
        vector<TileEditor> row;

        for (unsigned int j = 0; j < width/32; j++) {
            sf::Sprite s;
            s.setTexture(TileEditor::textures[name]);
            s.setPosition(j*32,i*32);

            TileEditor t;
            t.addSprite(s);

            row.push_back(t);
        }
        tiles.push_back(row);
    }
}

void WindowEditor::generateMines() {


    for(unsigned int iter = 0; iter < board["mineCount"]; iter++){
        int xPos = Random::Int(0,width);
        int yPos = Random::Int(0,height);

        xPos -= xPos % 32;
        yPos -= yPos % 32;

        sf::Sprite mine;
        sf::Vector2f mineCoords(xPos,yPos);
        mine.setTexture(TileEditor::textures["mine"]);
        mine.setPosition(mineCoords);

        for (unsigned int i = 0; i < height/32; i++) {
            for (unsigned int j = 0; j < width/32; j++) {
                if(tiles[i][j].sprites[0].getPosition() == mineCoords) {
                    if(tiles[i][j].containsMine()){
                        iter--;
                    }
                    else {
                        tiles[i][j].addSprite(mine);
                    }
                }
            }
        }
    }

    for (unsigned int i = 0; i < height/32; i++) {
        for (unsigned int j = 0; j < width/32; j++) {
            if(minesSurrounding(j,i) == -1 || minesSurrounding(j,i) == 0)
                continue;
            else{
                sf::Sprite s;
                s.setTexture(TileEditor::textures["images/number_" + to_string(minesSurrounding(j,i))]);
                s.setPosition(j*32,i*32);

                tiles[i][j].addSprite(s);
            }
        }
    }

}

void WindowEditor::loadTiles(string name) {

    for (unsigned int i = 0; i < height/32; i++) {
        for (unsigned int j = 0; j < width/32; j++) {
            sf::Sprite s;
            s.setTexture(TileEditor::textures[name]);
            s.setPosition(j*32,i*32);

            tiles[i][j].addSprite(s);
        }
    }
}


void WindowEditor::Debug() {
    if(debugOn){
        for(int i = 0; i < height/32; i++){
            for(int j = 0; j < width/32; j++) {
                if(tiles[i][j].containsMine()){
                    tiles[i][j].sprites.erase(tiles[i][j].sprites.end()-1);
                }
            }
        }
        debugOn = false;
    }
    else {
        for (int i = 0; i < height / 32; i++) {
            for (int j = 0; j < width / 32; j++) {
                if (tiles[i][j].containsMine()) {
                    sf::Sprite s;
                    s.setTexture(TileEditor::textures["mine"]);
                    s.setPosition(j * 32, i * 32);
                    tiles[i][j].addSprite(s);
                }
            }
        }
        debugOn = true;
    }
}



void WindowEditor::loadButtons(){
    //smiley face
    sf::Sprite smiley;
    smiley.setTexture(TileEditor::textures["face_happy"]);
    smiley.setPosition(width/2-32,height);
    buttons["smiley"] = smiley;

    //debug
    sf::Sprite debug;
    debug.setTexture(TileEditor::textures["debug"]);
    debug.setPosition(width/2+96,height);
    buttons["debug"] = debug;

    //tests
    sf::Sprite test1;
    test1.setTexture(TileEditor::textures["images/test_1"]);
    test1.setPosition(width/2+160,height);
    buttons["test1"] = test1;

    sf::Sprite test2;
    test2.setTexture(TileEditor::textures["images/test_2"]);
    test2.setPosition(width/2+224,height);
    buttons["test2"] = test2;

    sf::Sprite test3;
    test3.setTexture(TileEditor::textures["images/test_3"]);
    test3.setPosition(width/2+288,height);
    buttons["test3"] = test3;

}

int WindowEditor::minesSurrounding(int xIndex, int yIndex) {

    int minesSurrounding = 0;

    //if it is a mine, we don't need to worry about numbering
    if(tiles[yIndex][xIndex].containsMine())
        return -1;

    if(xIndex > 0){
        if(tiles[yIndex][xIndex-1].containsMine()) {
            minesSurrounding++;
        }
        if(yIndex > 0){
            if(tiles[yIndex-1][xIndex-1].containsMine()) {
                minesSurrounding++;
            }
        }
        if(yIndex < (height/32-1)){
            if(tiles[yIndex+1][xIndex-1].containsMine()) {
                minesSurrounding++;
            }
        }
    }
    if(yIndex > 0){
        if(tiles[yIndex-1][xIndex].containsMine()) {
            minesSurrounding++;
        }
        if(xIndex < (width/32-1)){
            if(tiles[yIndex-1][xIndex+1].containsMine()) {
                minesSurrounding++;
            }
        }
    }
    if(xIndex < (width/32-1)){
        if(tiles[yIndex][xIndex+1].containsMine()) {
            minesSurrounding++;
        }
        if(yIndex < (height/32-1)){
            if(tiles[yIndex+1][xIndex+1].containsMine()) {
                minesSurrounding++;
            }
        }
    }
    if(yIndex < (height/32-1)){
        if(tiles[yIndex+1][xIndex].containsMine()) {
            minesSurrounding++;
        }
    }
    return minesSurrounding;
}

void WindowEditor::LeftSettings(sf::Vector2<int>& mousePos) {
        int xPos = mousePos.x;
        int yPos = mousePos.y;
        if (yPos <= height) {
            xPos -= xPos % 32;
            yPos -= yPos % 32;

            for (unsigned int i = 0; i < height / 32; i++) {
                for (unsigned int j = 0; j < width / 32; j++) {
                    if ((int) tiles[i][j].sprites[0].getPosition().x == xPos &&
                        (int) tiles[i][j].sprites[0].getPosition().y == yPos) {
                        if (tiles[i][j].findSprite("flag") == tiles[i][j].sprites.end()
                            && tiles[i][j].findSprite("hiddenTile") != tiles[i][j].sprites.end()) {
                                if(tiles[i][j].containsMine()) {
                                    gameLost = true;
                                    LossActions();
                                }
                                if(!gameLost) {
                                    if (tiles[i][j].isEmptyTile()) {
                                        spacesSurrounding(j, i);
                                    } else {
                                        tiles[i][j].sprites.erase(tiles[i][j].findSprite("hiddenTile"));
                                    }
                                }
                                Victory();
                                if (gameWon) {
                                    VictoryActions();
                                }
                        }
                        break;
                    }
                }
            }
        } else {
            if (width / 2 - 32 <= xPos && xPos <= width / 2 + 32) {
                startNewGame();
            } else if (width / 2 + 96 <= xPos && xPos <= width / 2 + 160) {
                Debug();

            } else if (width / 2 + 160 <= xPos && xPos <= width / 2 + 224) {
                TestFile("boards/testboard1.brd");
            } else if (width / 2 + 224 <= xPos && xPos <= width / 2 + 288) {
                TestFile("boards/testboard2.brd");
            } else if (width / 2 + 288 <= xPos && xPos <= width / 2 + 352) {
                TestFile("boards/testboard3.brd");
            }

        }


    }

void WindowEditor::RightSettings(sf::Vector2<int>& mousePos) {
    //if mouse click is in regions of game board
    int xPos = mousePos.x;
    int yPos = mousePos.y;


        xPos -= xPos % 32;
        yPos -= yPos % 32;

        for (unsigned int i = 0; i < height / 32; i++) {
            for (unsigned int j = 0; j < width / 32; j++) {

                if ((int) tiles[i][j].sprites[0].getPosition().x == xPos &&
                    (int) tiles[i][j].sprites[0].getPosition().y == yPos) {
                    if(!gameLost && !gameWon) {
                        if ((tiles[i][j].findSprite("flag") == tiles[i][j].sprites.end())) {
                            sf::Sprite s;
                            s.setTexture(TileEditor::textures["flag"]);
                            s.setPosition(j * 32, i * 32);
                            tiles[i][j].addSprite(s);
                            mineCount--;
                            calcMinesRemaining();
                        } else if ((tiles[i][j].findSprite("flag") != tiles[i][j].sprites.end())) {
                            tiles[i][j].sprites.erase(tiles[i][j].findSprite("flag"));
                            mineCount++;
                            calcMinesRemaining();
                        }
                    }
                    break;

                }
            }
        }
}

void WindowEditor::spacesSurrounding(int xIndex, int yIndex) {

    if(!tiles[yIndex][xIndex].isEmptyTile()){
        if (tiles[yIndex][xIndex].findSprite("hiddenTile") != tiles[yIndex][xIndex].sprites.end()) {
            tiles[yIndex][xIndex].sprites.erase(tiles[yIndex][xIndex].findSprite("hiddenTile"));
        }
    }
    else if(tiles[yIndex][xIndex].findSprite("hiddenTile") == tiles[yIndex][xIndex].sprites.end()){

    }
    else {
        if (tiles[yIndex][xIndex].findSprite("hiddenTile") != tiles[yIndex][xIndex].sprites.end()) {
            tiles[yIndex][xIndex].sprites.erase(tiles[yIndex][xIndex].findSprite("hiddenTile"));
        }
        if (xIndex > 0) {
            if (yIndex > 0) {
                spacesSurrounding(xIndex - 1, yIndex-1);
            }

            if (yIndex < (height / 32 - 1)) {
                spacesSurrounding(xIndex - 1, yIndex+1);
            }
            spacesSurrounding(xIndex - 1, yIndex);
        }

        if(yIndex > 0){

            if(xIndex < (width/32-1)){
                spacesSurrounding(xIndex+1, yIndex-1);
            }
            spacesSurrounding(xIndex, yIndex-1);
        }


        if(xIndex < (width/32-1)){

            if(yIndex < (height/32-1)){
                spacesSurrounding(xIndex+1, yIndex+1);
            }
            spacesSurrounding(xIndex+1, yIndex);
        }

        if(yIndex < (height/32-1)){
            spacesSurrounding(xIndex, yIndex+1);
        }
    }
}

void WindowEditor::TestFile(string filename) {
    tiles.clear();
    gameWon = false;
    gameLost = false;

    loadBoxes("revealedTile");
    loadButtons();

    ifstream file(filename);
    vector<vector<int>> fileData;
    if (file.is_open()) {
        string singleLine;
        char num;
        int numConvert;
        while (getline(file,singleLine)) {
            istringstream stream(singleLine);
            vector<int> row;
            while(stream){
                stream >> num;
                numConvert = num - 48;
                row.push_back(numConvert);
            }
            fileData.push_back(row);
        }
    }

    mineCount = 0;

    for (unsigned int i = 0; i < height / 32; i++) {
        for (unsigned int j = 0; j < width / 32; j++) {
            if(fileData[i][j] == 1) {
                sf::Sprite s;
                s.setTexture(TileEditor::textures["mine"]);
                s.setPosition(j * 32, i * 32);
                tiles[i][j].addSprite(s);
                mineCount++;
            }
        }
    }

    for (unsigned int i = 0; i < height/32; i++) {
        for (unsigned int j = 0; j < width/32; j++) {
            if(minesSurrounding(j,i) == -1 || minesSurrounding(j,i) == 0)
                continue;
            else{
                sf::Sprite s;
                s.setTexture(TileEditor::textures["images/number_" + to_string(minesSurrounding(j,i))]);
                s.setPosition(j*32,i*32);

                tiles[i][j].addSprite(s);
            }
        }
    }

    calcMinesRemaining();

    loadTiles("hiddenTile");
}

int WindowEditor::calcMinesRemaining() {

    for(int i = 0; i<11; i++){
        sf::Sprite s;
        s.setTexture(TileEditor::textures["digits"]);
        s.setTextureRect(sf::IntRect(21*i, 0, 21, 32));
        minesRemainingDisplay.push_back(s);
    }


    int num1 = abs(mineCount) / 100 % 10;
    int num2 = abs(mineCount) / 10 % 10;
    int num3 = abs(mineCount) % 10;

    if(mineCount<0){
        sf::Sprite negative = minesRemainingDisplay[10];
        negative.setPosition(0,height);
        minesRemaining.push_back(negative);
    }
    sf::Sprite s = minesRemainingDisplay[num1];
    s.setPosition(21,height);
    minesRemaining.push_back(s);

    s = minesRemainingDisplay[num2];
    s.setPosition(42,height);
    minesRemaining.push_back(s);

    s = minesRemainingDisplay[num3];
    s.setPosition(63,height);
    minesRemaining.push_back(s);

    return mineCount;

}

void WindowEditor::Victory() {
    bool temp = true;
    for (unsigned int i = 0; i < height / 32; i++) {
        for (unsigned int j = 0; j < width / 32; j++) {
            if(tiles[i][j].containsMine()) {
                continue;
            }
            else if(tiles[i][j].findSprite("hiddenTile") != tiles[i][j].sprites.end())
                temp = false;
        }
    }
    gameWon = temp;

}


void WindowEditor::LossActions() {
    for (int i = 0; i < height / 32; i++) {
        for (int j = 0; j < width / 32; j++) {
            if (tiles[i][j].containsMine()) {
                sf::Sprite s;
                s.setTexture(TileEditor::textures["mine"]);
                s.setPosition(j * 32, i * 32);
                tiles[i][j].addSprite(s);
                if(tiles[i][j].findSprite("hiddenTile") != tiles[i][j].sprites.end()) {
                    tiles[i][j].sprites.erase(tiles[i][j].findSprite("hiddenTile"));
                }
            }
        }
    }
    sf::Sprite smiley;
    smiley.setTexture(TileEditor::textures["face_lose"]);
    smiley.setPosition(width / 2 - 32, height);
    buttons["smiley"] = smiley;
}

void WindowEditor::VictoryActions() {
    for (unsigned int i = 0; i < height / 32; i++) {
        for (unsigned int j = 0; j < width / 32; j++) {
            if (tiles[i][j].containsMine()) {
                if (tiles[i][j].findSprite("flag") == tiles[i][j].sprites.end()) {
                    sf::Sprite s;
                    s.setTexture(TileEditor::textures["flag"]);
                    s.setPosition(j * 32, i * 32);
                    tiles[i][j].addSprite(s);
                    mineCount--;
                    calcMinesRemaining();
                }
            }
        }
    }
    sf::Sprite smiley;
    smiley.setTexture(TileEditor::textures["face_win"]);
    smiley.setPosition(width/2-32,height);
    buttons["smiley"] = smiley;
}










