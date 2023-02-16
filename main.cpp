
#include "TileEditor.h"
#include "WindowEditor.h"

using namespace std;

int main()
{
    //creates window, board size
    WindowEditor::createBoard();
    unordered_map<string, int> board = WindowEditor::board;
    unsigned int width = board["width"];
    unsigned int height = board["height"];

    //white background
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(board["width"],board["height"] + 100));

    sf::RenderWindow window(sf::VideoMode(board["width"], board["height"] + 100), "SFML Application");

    //loads textures
    unordered_map<string, sf::Texture>& textures = TileEditor::textures;
    TileEditor::LoadTextures();

    //loads revealed tiles
    WindowEditor currentGame;
    vector<vector<TileEditor>>& tiles = currentGame.tiles;
    unordered_map<string, sf::Sprite>& buttons = WindowEditor::buttons;
    vector<sf::Sprite>& minesRemaining = currentGame.minesRemaining;

    currentGame.startNewGame();


    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);


        for(int i = 0; i < height/32; i++){
            for(int j = 0; j < width/32; j++) {
                for(int k = 0; k < tiles[i][j].sprites.size(); k++) {
                    window.draw(tiles[i][j].sprites[k]);
                }
            }
        }

        for(auto iter = buttons.begin(); iter != buttons.end(); ++iter)
            window.draw(iter->second);

        for(auto iter = minesRemaining.begin(); iter != minesRemaining.end(); ++iter)
            window.draw(*iter);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);
                currentGame.LeftSettings(mousePos);

            }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);
            currentGame.RightSettings(mousePos);
        }


        window.display();
    }
    return 0;
}
