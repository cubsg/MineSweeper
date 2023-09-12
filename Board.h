#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

using namespace  std;

class Board
        {

    class Tile
            {
        ///is it a mine, number, or empty?
        bool Mine = false;
        bool Number = false;
        int Num = 0;
        bool Empty = true;

        ///Has it been flagged, revealed, or still hidden?
        bool Flagged = false;
        bool Revealed = false;
        bool Hidden = false;

            public:
                 bool Is_Mine(Board &Game_Board, int x, int y);
                 void Set_Mine(Board &Game_Board, int x, int y);

                 bool Is_Number(Board &Game_Board, int x, int y);
                 void Set_Number(Board &Game_Board, int x, int y);
                 void Add_Number(Board &Game_Board, int x, int y);
                 int Number_Value(Board &Game_Board, int x, int y);

                 void Reveal(Board &Game_Board, int x, int y);
                 void Hide(Board &Game_Board, int x, int y);
                 bool Is_Revealed(Board &Game_Board, int x, int y);

                void Flag(Board &Game_Board, int x, int y);
                void Un_Flag(Board &Game_Board, int x, int y);
                bool Is_Flagged(Board &Game_Board, int x, int y);

                void Reset(Board &Game_Board, int x, int y);
                bool Is_Empty(Board &Game_Board, int x, int y);

                void UnCamo(Board &Game_Board, int x, int y);
                void Camo(Board &Game_Board, int x, int y);
                bool Is_Camo(Board &Game_Board, int x, int y);

                void Set_Neighbor(Board &Game_Board, int x, int y, int xn, int yn);
                void Recursion();


        //Neighbors
        vector<Tile*> adjacent_tiles;
    };

public:
    vector<vector<Tile>> Tiles;
    map<string, string> Scores;

    int width = 800;
    int height = 600;
    int num_mines;
    int current_mines;
    int columns;
    int rows;
    int num_flagged = 0;
    bool Debug = false;
    bool Paused = false;
    bool Game = true;
    bool Game_Won = false;
    bool Game_Lost = false;
    bool Reset = false;
    string time = "";
    int seconds = 0;
    int minutes = 0;
    string name = "";


    bool timer = true;

    Board(int columns, int rows, int num_mines);
    ~Board();

    class Timer{
    std::chrono::system_clock::time_point start_time, current_time;
    std::chrono::duration<float> delta_time;


public:
    Timer();
    void Reset();
    float Time_Elapsed();

};
};

///Tile
bool Board::Tile::Is_Mine(Board &Game_Board, int x, int y) {
    if (Game_Board.Tiles[x][y].Mine){
        return true;
    }
    else{
        return false;
    }
}
void Board::Tile::Set_Mine(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Mine = true;
    Game_Board.Tiles[x][y].Empty = false;
}
void Board::Tile::Set_Number(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Number = true;
    Game_Board.Tiles[x][y].Empty = false;
}
bool Board::Tile::Is_Number(Board &Game_Board, int x, int y){
    if (Game_Board.Tiles[x][y].Number){
        return true;
    }
    else{
        return false;
    }
}
void Board::Tile::Add_Number(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Num += 1;
}
int Board::Tile::Number_Value(Board &Game_Board, int x, int y){
    return Game_Board.Tiles[x][y].Num;
}
void Board::Tile::Reveal(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Revealed = true;
}
void Board::Tile::Hide(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Revealed = false;
}
void Board::Tile::UnCamo(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Hidden = false;
}
void Board::Tile::Camo(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Hidden = true;
}
bool Board::Tile::Is_Camo(Board &Game_Board, int x, int y){
    if (Game_Board.Tiles[x][y].Hidden){
        return true;
    }
    else{
        return false;
    }
}
bool Board::Tile::Is_Revealed(Board &Game_Board, int x, int y){
    if (Game_Board.Tiles[x][y].Revealed){
        return true;
    }
    else{
        return false;
    }
}
void Board::Tile::Flag(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Flagged = true;
}
void Board::Tile::Un_Flag(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Flagged = false;
}
bool Board::Tile::Is_Flagged(Board &Game_Board, int x, int y){
    if (Game_Board.Tiles[x][y].Flagged){
        return true;
    }
    else{
        return false;
    }
}
void Board::Tile::Reset(Board &Game_Board, int x, int y){
    Game_Board.Tiles[x][y].Mine = false;
    Game_Board.Tiles[x][y].Number = false;
    Game_Board.Tiles[x][y].Num = 0;
    Game_Board.Tiles[x][y].Empty = true;
    Game_Board.Tiles[x][y].Flagged = false;
    Game_Board.Tiles[x][y].Revealed = false;
}
void Board::Tile::Recursion() {
    if (Flagged or Revealed){
        return;
    }

    Revealed = true;

    if (Mine) {
        return;
    }

    if (Num == 0){
        for (Tile* neighbor : adjacent_tiles) {
            neighbor->Recursion();
        }
    }
}
void Board::Tile::Set_Neighbor(Board &Game_Board, int x, int y, int xn, int yn){
    Game_Board.Tiles[x][y].adjacent_tiles.push_back(&Game_Board.Tiles.at(xn).at(yn));
}

///Timer
Board::Timer::Timer(){
    start_time = std::chrono::system_clock::now();
    current_time = std::chrono::system_clock::now();
    delta_time = std::chrono::duration<double>(0);
}
void Board::Timer::Reset(){
    start_time = std::chrono::system_clock::now();
}
float Board::Timer::Time_Elapsed(){
    current_time = std::chrono::system_clock::now();
    delta_time = current_time - start_time;
    return delta_time.count();
}

///Declarations
void setText(sf::Text &text, float x, float y, float z);
void Welcome_Window(sf::RenderWindow &window, Board &Game_Board, float columns, float rows, int num_mines);
void Draw_Tiles(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines);
void Generate_Mines(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines);
void Generate_Numbers(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines);
void Mouse_Flagging(sf::RenderWindow &window, Board &Game_Board, int x, int y);
void Reset_Button(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines);
void Debug_Button(sf::RenderWindow &window, Board &Game_Board, int columns, int rows);
void Leader_Button(sf::RenderWindow &window, Board &Game_Board, int columns, int rows);
void Draw_LB(sf::RenderWindow &window, Board &Game_Board, int x, int y);
void Check_If_Mine(sf::RenderWindow &window, Board &Game_Board, int x, int y, int columns, int rows);
void Draw_Face(sf::RenderWindow &window, Board &Game_Board, int x, int y);
void Check_If_Won(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines);
void Recursive_Check(sf::RenderWindow &window, Board &Game_Board, int x, int y, int columns, int rows);
void Draw_Counter(sf::RenderWindow &window, Board &Game_Board, int x, int y);
void Draw_Camo(sf::RenderWindow &window, Board &Game_Board, int columns, int rows);
void Camo_UnCamo(sf::RenderWindow &window, Board &Game_Board, int columns, int rows);
void Add_Second(sf::RenderWindow &window, Board &Game_Board, Board::Timer Time);
void Stop_Timer(sf::RenderWindow &window, Board &Game_Board, Board::Timer Time);
void Draw_Timer(sf::RenderWindow &window, Board &Game_Board, Board::Timer Time, int columns, int rows);
void Check_LB(Board &Game_Board);

///Definitions
Board::Board(int columns, int rows, int num_mines){
    this -> columns = columns;
    this -> rows = rows;
    this -> num_mines = num_mines;
    this -> current_mines = 0;
    Board::Tile newTile;
    for (unsigned int i = 0; i < rows; i++){
        vector<Tile> row;
        for (unsigned int j = 0; j < columns; j++){
            //push back all tiles into row
            row.push_back(newTile);
        }
        //push back row into board
        Tiles.push_back(row);
    }

    ///Reading info
    ifstream F("files/leaderboard.txt");
    if (!F.is_open()) {
        cout << "Failed to load leaderboard file!" << endl;
    }
    string name;
    string total_time;

    for (unsigned int i = 0; i < 5; i++) {
        //add map
        getline(F, total_time, ',');
        getline(F, name);
        this -> Scores[total_time] = name;
    }

}

Board::~Board() {
}

void setText(sf::Text &text, float x, float y, float z){
    sf::FloatRect textRect = text.getGlobalBounds();
    text.setOrigin(-205, -300 + z);
    text.setPosition(sf::Vector2f(x, y));
    }

void Welcome_Window(sf::RenderWindow &window, Board &Game_Board, float columns, float rows, int num_mines) {
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "Failed to load text file!" << endl;
    }

    ///title
    sf::Text title;
    title.setFont(font);
    title.setString("WELCOME TO MINESWEEPER!");
    setText(title, columns, rows, 150);
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);


    ///input text prompt
    sf::Text prompt;
    prompt.setFont(font);
    prompt.setString("Enter your name:");
    setText(prompt, columns, rows, 75);
    prompt.setCharacterSize(20);
    prompt.setFillColor(sf::Color::White);
    prompt.setStyle(sf::Text::Bold);

    ///input
    string Name;
    sf::String Player_Input;
    sf::Text input;
    input.setFont(font);
    input.setString("|");
    setText(input, columns, rows, 45);
    input.setCharacterSize(18);
    input.setFillColor(sf::Color::Yellow);
    input.setStyle(sf::Text::Bold);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                ///Typing in letters
                if (event.text.unicode >= 65 and event.text.unicode <= 122 and Player_Input.getSize() <= 10) {
                    //if only |
                    if (Player_Input.getSize() <= 0) {
                        Player_Input += event.text.unicode;
                        Player_Input += "|";
                        Name += std::tolower(char(event.text.unicode));
                        //Name += std::toupper(char(event.text.unicode));
                        input.setString(Player_Input);
                    }

                    else {
                    Player_Input.erase(Player_Input.getSize() - 1, 1);
                    Player_Input += event.text.unicode;
                    Name += std::tolower(char(event.text.unicode));
                    Player_Input += "|";
                    input.setString(Player_Input);
                }
                }

                ///Using Backspace
                if (event.text.unicode == 8) {
                    if (Player_Input.getSize() <= 0) {
                        input.setString("|");
                    }

                    else if (Player_Input.getSize() > 1) {
                        string new_name;
                        Player_Input.erase(Player_Input.getSize() - 1, 1);
                        Player_Input.erase(Player_Input.getSize() - 1, 1);
                        Name.erase(Name.size() - 1, 1);
                        Player_Input += "|";
                        input.setString(Player_Input);
                    }
                }

                ///Enter Key after inputting a name
                if(event.text.unicode == 13 and Name.size() > 0) {
                    //Keep player named stored (Name)
                    Name[0] = std::toupper(Name[0]);
                    cout << "Welcome Done" << endl;
                    //call main
                    Game_Board.name = Name;
                    return;
                }

            }
            }
            window.clear(sf::Color::Blue);
            window.draw(title);
            window.draw(prompt);
            window.draw(input);
            window.display();
        }
    }

void Generate_Mines(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines){
    int current_mines = 0;
    static std::mt19937 i;

    while (current_mines < num_mines){
        uniform_int_distribution<int> row(0, (rows - 1));
        uniform_int_distribution<int> col(0, (columns - 1));

        int x = row(i);
        int y = col(i);

        if (!Game_Board.Tiles.at(x).at(y).Is_Mine(Game_Board, x, y)) {
            Game_Board.Tiles.at(x).at(y).Set_Mine(Game_Board, x, y);
            current_mines += 1;
        }
    }
}

void Setup_Neighbors(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines){
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            ///Corners
            //Left Top Corner
            if (i == 0 and j == 0){
                //4,5,6
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i,j+1);
            }
            //Left Bottom Corner
            if (i == (rows - 1) and j == 0){
                //6,7,8
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i-1,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i-1,j);
            }
            //Right Top Corner
            if (i == 0 and j == (columns - 1)){
                //2,3,4
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j);
            }
            //Right Bottom Corner
            if (i == (rows - 1) and j == (columns - 1)){
                //1,2,8
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i-1,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i-1,j);
            }

            ///Horizontal and Vertical Sides
            //Horizontal 1
            if (i == 0 and j != 0 and j != (columns - 1)){
                //2,3,4,5,6
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i,j+1);
            }
            //Horizontal 2
            if (i == (rows - 1) and j != 0 and j != (columns - 1)){
                //1,2,6,7,8
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i-1,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j,i,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i-1,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i-1,j);
            }
            //Vertical 1
            if(i != 0 and i != (rows - 1) and j == 0){
                //4,5,6,7,8
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i-1,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i-1,j);
            }
            //Vertical 2
            if(i != 0 and i != (rows - 1) and j == (columns - 1)){
                //1,2,3,4,8
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i-1,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i-1,j);
            }

            ///Everything Else
            if (i != 0 and i != (rows - 1) and j != 0 and j != (columns - 1)){
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i-1,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j-1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i, j, i+1,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i-1,j+1);
                Game_Board.Tiles.at(i).at(j).Set_Neighbor(Game_Board, i,j,i-1,j);
            }
        }}



}

void Generate_Numbers(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines){
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            if (Game_Board.Tiles.at(i).at(j).Is_Mine(Game_Board, i, j)) {
                //Set the 3x3 square around it to be numbers
/*
1 Game_Board.Tiles.at(i-1).at(j-1).Set_Number(Game_Board, i-1,j-1);
2 Game_Board.Tiles.at(i).at(j-1).Set_Number(Game_Board, i,j-1);
3 Game_Board.Tiles.at(i+1).at(j-1).Set_Number(Game_Board, i+1,j-1);
4 Game_Board.Tiles.at(i+1).at(j).Set_Number(Game_Board, i+1,j);
5 Game_Board.Tiles.at(i+1).at(j+1).Set_Number(Game_Board, i+1,j+1);
6 Game_Board.Tiles.at(i).at(j+1).Set_Number(Game_Board, i,j+1);
7 Game_Board.Tiles.at(i-1).at(j+1).Set_Number(Game_Board, i-1,j+1);
8 Game_Board.Tiles.at(i-1).at(j).Set_Number(Game_Board, i-1,j);
*/

/*
1 Game_Board.Tiles.at(i-1).at(j-1).Add_Number(Game_Board, i-1,j-1);
2 Game_Board.Tiles.at(i).at(j-1).Add_Number(Game_Board, i,j-1);
3 Game_Board.Tiles.at(i+1).at(j-1).Add_Number(Game_Board, i+1,j-1);
4 Game_Board.Tiles.at(i+1).at(j).Add_Number(Game_Board, i+1,j);
5 Game_Board.Tiles.at(i+1).at(j+1).Add_Number(Game_Board, i+1,j+1);
6 Game_Board.Tiles.at(i).at(j+1).Add_Number(Game_Board, i,j+1);
7 Game_Board.Tiles.at(i-1).at(j+1).Add_Number(Game_Board, i-1,j+1);
8 Game_Board.Tiles.at(i-1).at(j).Add_Number(Game_Board, i-1,j);
*/

                ///Corners
                //Left Top Corner
                if (i == 0 and j == 0){
                    //4,5,6
                    Game_Board.Tiles.at(i+1).at(j).Set_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i+1).at(j+1).Set_Number(Game_Board, i+1,j+1);
                    Game_Board.Tiles.at(i).at(j+1).Set_Number(Game_Board, i,j+1);

                    Game_Board.Tiles.at(i+1).at(j).Add_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i+1).at(j+1).Add_Number(Game_Board, i+1,j+1);
                    Game_Board.Tiles.at(i).at(j+1).Add_Number(Game_Board, i,j+1);
                }
                //Left Bottom Corner
                if (i == (rows - 1) and j == 0){
                    //6,7,8
                    Game_Board.Tiles.at(i).at(j+1).Set_Number(Game_Board, i,j+1);
                    Game_Board.Tiles.at(i-1).at(j+1).Set_Number(Game_Board, i-1,j+1);
                    Game_Board.Tiles.at(i-1).at(j).Set_Number(Game_Board, i-1,j);

                    Game_Board.Tiles.at(i).at(j+1).Add_Number(Game_Board, i,j+1);
                    Game_Board.Tiles.at(i-1).at(j+1).Add_Number(Game_Board, i-1,j+1);
                    Game_Board.Tiles.at(i-1).at(j).Add_Number(Game_Board, i-1,j);
                }
                //Right Top Corner
                if (i == 0 and j == (columns - 1)){
                    //2,3,4
                    Game_Board.Tiles.at(i).at(j-1).Set_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i+1).at(j-1).Set_Number(Game_Board, i+1,j-1);
                    Game_Board.Tiles.at(i+1).at(j).Set_Number(Game_Board, i+1,j);

                    Game_Board.Tiles.at(i).at(j-1).Add_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i+1).at(j-1).Add_Number(Game_Board, i+1,j-1);
                    Game_Board.Tiles.at(i+1).at(j).Add_Number(Game_Board, i+1,j);
                }
                //Right Bottom Corner
                if (i == (rows - 1) and j == (columns - 1)){
                    //1,2,8
                    Game_Board.Tiles.at(i-1).at(j-1).Set_Number(Game_Board, i-1,j-1);
                    Game_Board.Tiles.at(i).at(j-1).Set_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i-1).at(j).Set_Number(Game_Board, i-1,j);

                    Game_Board.Tiles.at(i-1).at(j-1).Add_Number(Game_Board, i-1,j-1);
                    Game_Board.Tiles.at(i).at(j-1).Add_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i-1).at(j).Add_Number(Game_Board, i-1,j);
               }

                ///Horizontal and Vertical Sides
                //Horizontal 1
                if (i == 0 and j != 0 and j != (columns - 1)){
                    //2,3,4,5,6
                    Game_Board.Tiles.at(i).at(j-1).Set_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i+1).at(j-1).Set_Number(Game_Board, i+1,j-1);
                    Game_Board.Tiles.at(i+1).at(j).Set_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i+1).at(j+1).Set_Number(Game_Board, i+1,j+1);
                    Game_Board.Tiles.at(i).at(j+1).Set_Number(Game_Board, i,j+1);

                    Game_Board.Tiles.at(i).at(j-1).Add_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i+1).at(j-1).Add_Number(Game_Board, i+1,j-1);
                    Game_Board.Tiles.at(i+1).at(j).Add_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i+1).at(j+1).Add_Number(Game_Board, i+1,j+1);
                    Game_Board.Tiles.at(i).at(j+1).Add_Number(Game_Board, i,j+1);
                }
                //Horizontal 2
                if (i == (rows - 1) and j != 0 and j != (columns - 1)){
                    //1,2,6,7,8
                    Game_Board.Tiles.at(i-1).at(j-1).Set_Number(Game_Board, i-1,j-1);
                    Game_Board.Tiles.at(i).at(j-1).Set_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i).at(j+1).Set_Number(Game_Board, i,j+1);
                    Game_Board.Tiles.at(i-1).at(j+1).Set_Number(Game_Board, i-1,j+1);
                    Game_Board.Tiles.at(i-1).at(j).Set_Number(Game_Board, i-1,j);

                    Game_Board.Tiles.at(i-1).at(j-1).Add_Number(Game_Board, i-1,j-1);
                    Game_Board.Tiles.at(i).at(j-1).Add_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i).at(j+1).Add_Number(Game_Board, i,j+1);
                    Game_Board.Tiles.at(i-1).at(j+1).Add_Number(Game_Board, i-1,j+1);
                    Game_Board.Tiles.at(i-1).at(j).Add_Number(Game_Board, i-1,j);
                }
                //Vertical 1
                if(i != 0 and i != (rows - 1) and j == 0){
                    //4,5,6,7,8
                    Game_Board.Tiles.at(i+1).at(j).Set_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i+1).at(j+1).Set_Number(Game_Board, i+1,j+1);
                    Game_Board.Tiles.at(i).at(j+1).Set_Number(Game_Board, i,j+1);
                    Game_Board.Tiles.at(i-1).at(j+1).Set_Number(Game_Board, i-1,j+1);
                    Game_Board.Tiles.at(i-1).at(j).Set_Number(Game_Board, i-1,j);

                    Game_Board.Tiles.at(i+1).at(j).Add_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i+1).at(j+1).Add_Number(Game_Board, i+1,j+1);
                    Game_Board.Tiles.at(i).at(j+1).Add_Number(Game_Board, i,j+1);
                    Game_Board.Tiles.at(i-1).at(j+1).Add_Number(Game_Board, i-1,j+1);
                    Game_Board.Tiles.at(i-1).at(j).Add_Number(Game_Board, i-1,j);
                }
                //Vertical 2
                if(i != 0 and i != (rows - 1) and j == (columns - 1)){
                    //1,2,3,4,8
                    Game_Board.Tiles.at(i-1).at(j-1).Set_Number(Game_Board, i-1,j-1);
                    Game_Board.Tiles.at(i).at(j-1).Set_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i+1).at(j-1).Set_Number(Game_Board, i+1,j-1);
                    Game_Board.Tiles.at(i+1).at(j).Set_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i-1).at(j).Set_Number(Game_Board, i-1,j);

                    Game_Board.Tiles.at(i-1).at(j-1).Add_Number(Game_Board, i-1,j-1);
                    Game_Board.Tiles.at(i).at(j-1).Add_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i+1).at(j-1).Add_Number(Game_Board, i+1,j-1);
                    Game_Board.Tiles.at(i+1).at(j).Add_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i-1).at(j).Add_Number(Game_Board, i-1,j);
                }

                ///Everything Else
                if (i != 0 and i != (rows - 1) and j != 0 and j != (columns - 1)){
                    Game_Board.Tiles.at(i-1).at(j-1).Set_Number(Game_Board, i-1,j-1);
                    Game_Board.Tiles.at(i).at(j-1).Set_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i+1).at(j-1).Set_Number(Game_Board, i+1,j-1);
                    Game_Board.Tiles.at(i+1).at(j).Set_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i+1).at(j+1).Set_Number(Game_Board, i+1,j+1);
                    Game_Board.Tiles.at(i).at(j+1).Set_Number(Game_Board, i,j+1);
                    Game_Board.Tiles.at(i-1).at(j+1).Set_Number(Game_Board, i-1,j+1);
                    Game_Board.Tiles.at(i-1).at(j).Set_Number(Game_Board, i-1,j);

                    Game_Board.Tiles.at(i-1).at(j-1).Add_Number(Game_Board, i-1,j-1);
                    Game_Board.Tiles.at(i).at(j-1).Add_Number(Game_Board, i,j-1);
                    Game_Board.Tiles.at(i+1).at(j-1).Add_Number(Game_Board, i+1,j-1);
                    Game_Board.Tiles.at(i+1).at(j).Add_Number(Game_Board, i+1,j);
                    Game_Board.Tiles.at(i+1).at(j+1).Add_Number(Game_Board, i+1,j+1);
                    Game_Board.Tiles.at(i).at(j+1).Add_Number(Game_Board, i,j+1);
                    Game_Board.Tiles.at(i-1).at(j+1).Add_Number(Game_Board, i-1,j+1);
                    Game_Board.Tiles.at(i-1).at(j).Add_Number(Game_Board, i-1,j);
                }
            }
        }
        }
    Setup_Neighbors(window, Game_Board,columns,rows, num_mines);
}

void Draw_Tiles(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines){
    for (unsigned int i = 0; i < rows; i++) {
        ///Print out the tile onto the board regardless if its a bomb, num, or empty
        for (unsigned int j = 0; j < columns; j++) {
            //Draw Mines
            if (Game_Board.Tiles.at(i).at(j).Is_Mine(Game_Board, i, j)) {
                sf::Texture bomb_texture;
                if(!bomb_texture.loadFromFile("files/images/mine.png")){
                    cout << "Failed" << endl;
                }

                sf::Sprite bomb_sprite;
                bomb_sprite.setTexture(bomb_texture);
                bomb_sprite.setTextureRect(sf::IntRect(0, 0, columns * 32, rows * 32));
                bomb_sprite.setPosition(j * 32, i * 32);
                window.draw(bomb_sprite);
            }
            //Draw Numbers
            if (Game_Board.Tiles.at(i).at(j).Is_Number(Game_Board, i, j) && !Game_Board.Tiles.at(i).at(j).Is_Mine(Game_Board, i, j)) {
                sf::Texture num_texture;

                int value = Game_Board.Tiles.at(i).at(j).Number_Value(Game_Board, i, j);
                //Number between 1 and 8
                if (value == 1){
                    if (!num_texture.loadFromFile("files/images/number_1.png")) {
                        cout << "Failed" << endl;
                    }
                }
                if (value == 2){
                    if (!num_texture.loadFromFile("files/images/number_2.png")) {
                        cout << "Failed" << endl;
                    }
                }
                if (value == 3){
                    if (!num_texture.loadFromFile("files/images/number_3.png")) {
                        cout << "Failed" << endl;
                    }
                }
                if (value == 4){
                    if (!num_texture.loadFromFile("files/images/number_4.png")) {
                        cout << "Failed" << endl;
                    }
                }
                if (value == 5){
                    if (!num_texture.loadFromFile("files/images/number_5.png")) {
                        cout << "Failed" << endl;
                    }
                }
                if (value == 6){
                    if (!num_texture.loadFromFile("files/images/number_6.png")) {
                        cout << "Failed" << endl;
                    }
                }
                if (value == 7){
                    if (!num_texture.loadFromFile("files/images/number_7.png")) {
                        cout << "Failed" << endl;
                    }
                }
                if (value == 8){
                    if (!num_texture.loadFromFile("files/images/number_8.png")) {
                        cout << "Failed" << endl;
                    }
                }

                sf::Sprite num_sprite;
                num_sprite.setTexture(num_texture);
                num_sprite.setTextureRect(sf::IntRect(0, 0, columns * 32, rows * 32));
                num_sprite.setPosition(j * 32, i * 32);
                window.draw(num_sprite);
            }

            if (!Game_Board.Tiles.at(i).at(j).Is_Revealed(Game_Board, i, j)){
                sf::Texture hidden_texture;
                if(!hidden_texture.loadFromFile("files/images/tile_hidden.png")){
                    cout << "Failed" << endl;
                }

                sf::Sprite hidden_sprite;
                hidden_sprite.setTexture(hidden_texture);
                hidden_sprite.setPosition(j * 32, i * 32);
                window.draw(hidden_sprite);
            }

            if (Game_Board.Tiles.at(i).at(j).Is_Flagged(Game_Board, i, j) && !Game_Board.Tiles.at(i).at(j).Is_Revealed(Game_Board, i, j)){
                sf::Texture flag_texture;
                if(!flag_texture.loadFromFile("files/images/flag.png")){
                    cout << "Failed" << endl;
                }

                sf::Sprite flag_sprite;
                flag_sprite.setTexture(flag_texture);
                //hidden_sprite.setTextureRect(sf::IntRect(0, 0, columns * 32, rows * 32));
                flag_sprite.setPosition(j * 32, i * 32);
                window.draw(flag_sprite);
            }

        }
    }
}

void Mouse_Flagging(sf::RenderWindow &window, Board &Game_Board, int x, int y){
    float i = x/32 + 0.5f;
    float j = y/32 + 0.5f;

    if (Game_Board.Tiles.at(i).at(j).Is_Flagged(Game_Board, i, j)){
        Game_Board.Tiles.at(i).at(j).Un_Flag(Game_Board, i, j);
        Game_Board.num_flagged -= 1;
    }
    else{
        Game_Board.Tiles.at(i).at(j).Flag(Game_Board, i, j);
        Game_Board.num_flagged += 1;
    }
}

void Debug_Button(sf::RenderWindow &window, Board &Game_Board, int columns, int rows) {
    if (!Game_Board.Debug) {
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < columns; j++) {
                //Draw Mines
                if (Game_Board.Tiles.at(i).at(j).Is_Mine(Game_Board, i, j)) {
                    Game_Board.Tiles.at(i).at(j).Reveal(Game_Board, i, j);
                }

            }
        }
        Game_Board.Debug = true;
    }

    else {
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < columns; j++) {
                //Draw Mines
                if (Game_Board.Tiles.at(i).at(j).Is_Mine(Game_Board, i, j)) {
                    Game_Board.Tiles.at(i).at(j).Hide(Game_Board, i, j);
                }
            }
        }
        Game_Board.Debug = false;
    }


}

void Reset_Button(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines){
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            Game_Board.Tiles.at(i).at(j).Reset(Game_Board, i, j);
        }
        }
    Game_Board.Paused = true;
    Game_Board.Reset = true;


    Game_Board.Debug = false;
    Game_Board.Paused = false;
    Game_Board.Game_Won = false;
    Game_Board.Game = true;
    Game_Board.num_flagged = 0;
    Game_Board.Paused = false;


    Generate_Mines(window, Game_Board, columns, rows, num_mines);
    Generate_Numbers(window, Game_Board, columns, rows, num_mines);
}

void Camo_UnCamo(sf::RenderWindow &window, Board &Game_Board, int columns, int rows){
    if (!Game_Board.Paused and !Game_Board.Game_Won) {
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < columns; j++) {
                Game_Board.Tiles.at(i).at(j).UnCamo(Game_Board, i,j);
            }}

        }
    if (Game_Board.Paused and !Game_Board.Game_Won) {
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < columns; j++) {
                Game_Board.Tiles.at(i).at(j).Camo(Game_Board, i,j);
            }}

    }


}
void Draw_Camo(sf::RenderWindow &window, Board &Game_Board, int columns, int rows){
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            if(!Game_Board.Tiles.at(i).at(j).Is_Camo(Game_Board, i,j) and Game_Board.Paused){
                sf::Texture texture;
                if(!texture.loadFromFile("files/images/tile_revealed.png")){
                    cout << "Failed" << endl;
                }
                sf::Sprite sprite;
                sprite.setTexture(texture);
                sprite.setPosition(j * 32, i * 32);
                window.draw(sprite);
            }
        }
    }

}

void Pause_Button(sf::RenderWindow &window, Board &Game_Board, int i, int j){
    if (!Game_Board.Paused){
        //Pause the game and timer
        Camo_UnCamo(window, Game_Board, i, j);
        Game_Board.Paused = true;
        //cout << "Time:" << Game_Board.time << endl;

        return;
    }

    if (Game_Board.Paused){
        //Unpause the game and timer
        Camo_UnCamo(window, Game_Board, i, j);
        Game_Board.Paused = false;
        //cout << "Time:" << Game_Board.time << endl;
        return;
    }


}

void Draw_PB(sf::RenderWindow &window, Board &Game_Board, int i, int j){
    sf::Texture pause_texture;

    if (Game_Board.Paused){
        if(!pause_texture.loadFromFile("files/images/play.png")){
            cout << "Failed" << endl;
        }
    }

    if (!Game_Board.Paused){
        if(!pause_texture.loadFromFile("files/images/pause.png")){
            cout << "Failed" << endl;
        }
    }

    sf::Sprite pause_sprite;
    pause_sprite.setTexture(pause_texture);
    pause_sprite.setPosition(i, j);
    window.draw(pause_sprite);
}

void Leader_Button(sf::RenderWindow &window, Board &Game_Board, int columns, int rows){
    ///Window Creation
    int x, y;
    x = 16*columns;
    y = (rows * 16) + 50;

    sf::RenderWindow w(sf::VideoMode(x, y), "Leaderboard", sf::Style::Close);

    while (w.isOpen()) {
        sf::Event wevent;
        while (w.pollEvent(wevent)) {
            if (wevent.type == sf::Event::Closed) {
                w.close();
            }
            }
        w.clear(sf::Color::Blue);
        ///draw ranks
        Draw_LB(w, Game_Board, y, x);
        w.display();
    }
}

void Draw_LB(sf::RenderWindow &window, Board &Game_Board, int x, int y){
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "Failed to load text file!" << endl;
    }

    ///Title
    sf::Text Title;
    Title.setFont(font);
    Title.setString("LEADERBOARD");
    sf::FloatRect textRect = Title.getGlobalBounds();
    Title.setOrigin(175, y/2.0f + 180);
    Title.setPosition(sf::Vector2f(x, y));
    Title.setCharacterSize(20);
    Title.setFillColor(sf::Color::White);
    Title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    window.draw(Title);
    int i = 0;

    for (auto iter = Game_Board.Scores.begin(); iter != Game_Board.Scores.end(); iter++){
        //create texture and sprite for each rank
        sf::Text rank;
        string Rank;
        rank.setFont(font);

        if (i == 0){
            Rank +=  "1.\t";
        }
        if (i == 1){
            Rank +=  "2.\t";
        }
        if (i == 2){
            Rank +=  "3.\t";
        }
        if (i== 3){
            Rank +=  "4.\t";
        }
        if (i == 4){
            Rank +=  "5.\t";
        }

        Rank += iter -> first;
        Rank += "\t";
        Rank += iter -> second;

        rank.setString(Rank);

        if (i == 0){
            rank.setOrigin(210, y/2.0f + 130);
        }
        if (i == 1){
            rank.setOrigin(210, y/2.0f + 100);
        }
        if (i == 2){
            rank.setOrigin(210, y/2.0f + 70);
        }
        if (i== 3){
            rank.setOrigin(210, y/2.0f + 40);
        }
        if (i == 4){
            rank.setOrigin(210, y/2.0f + 10);
        }

        i += 1;
        rank.setPosition(sf::Vector2f(x, y));
        rank.setCharacterSize(18);
        rank.setFillColor(sf::Color::White);
        rank.setStyle(sf::Text::Bold);
        window.draw(rank);
    }
}

void Check_If_Mine(sf::RenderWindow &window, Board &Game_Board, int x, int y, int columns, int rows){
    float i = x/32 + 0.5f;
    float j = y/32 + 0.5f;

    if (Game_Board.Tiles.at(i).at(j).Is_Mine(Game_Board, i, j)) {
        Game_Board.Game = false;
        Game_Board.Game_Lost = true;
        Game_Board.timer = false;
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < columns; j++) {
                //Draw Mines
                if (Game_Board.Tiles.at(i).at(j).Is_Mine(Game_Board, i, j)) {
                    Game_Board.Tiles.at(i).at(j).Reveal(Game_Board, i, j);
                }
            }
        }
    }
}

void Check_If_Won(sf::RenderWindow &window, Board &Game_Board, int columns, int rows, int num_mines) {
    int tiles_needed;
    tiles_needed = (columns * rows) - num_mines;

    int tiles_revealed = 0;

    for (unsigned int i = 0; i < rows; i++) {
        ///Print out the tile onto the board regardless if its a bomb, num, or empty
        for (unsigned int j = 0; j < columns; j++) {
            if (Game_Board.Tiles.at(i).at(j).Is_Revealed(Game_Board, i, j) and
                !Game_Board.Tiles.at(i).at(j).Is_Mine(Game_Board, i, j)) {
                tiles_revealed += 1;
            }
        }
    }
    if (tiles_needed == tiles_revealed) {
        Game_Board.Game_Won = true;
        Game_Board.timer = false;
        Game_Board.Game = false;
        ///Flag all Mines
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < columns; j++) {
                //Draw Mines
                if (Game_Board.Tiles.at(i).at(j).Is_Mine(Game_Board, i, j)) {
                    Game_Board.Tiles.at(i).at(j).Flag(Game_Board, i, j);
                    Game_Board.num_flagged += 1;
                }
            }
        }

        ///Check if new high score
        Check_LB(Game_Board);
    }
}

void Check_LB(Board &Game_Board){
    string minutes = to_string(Game_Board.minutes);
    string seconds = to_string(Game_Board.seconds);
    string name = Game_Board.name;

    ///Check if minutes is single digit
    if (minutes == "0"){
        minutes = "00";
    }
    if (minutes == "1"){
        minutes = "01";
    }
    if (minutes == "2"){
        minutes = "02";
    }
    if (minutes == "3"){
        minutes = "03";
    }
    if (minutes == "4"){
        minutes = "04";
    }
    if (minutes == "5"){
        minutes = "05";
    }
    if (minutes == "6"){
        minutes = "06";
    }
    if (minutes == "7"){
        minutes = "07";
    }
    if (minutes == "8"){
        minutes = "08";
    }
    if (minutes == "9"){
        minutes = "09";
    }
    ///Check if seconds is single digit
    if (seconds == "0"){
        seconds = "00";
    }
    if (seconds == "1"){
        seconds = "01";
    }
    if (seconds == "2"){
        seconds = "02";
    }
    if (seconds == "3"){
        seconds = "03";
    }
    if (seconds == "4"){
        seconds = "04";
    }
    if (seconds == "5"){
        seconds = "05";
    }
    if (seconds == "6"){
        seconds = "06";
    }
    if (seconds == "7"){
        seconds = "07";
    }
    if (seconds == "8"){
        seconds = "08";
    }
    if (seconds == "9"){
        seconds = "09";
    }

    string total_time = minutes + ":" + seconds;

    //convert to map
    Game_Board.Scores[total_time] = name;

    ///Write scores to file
    fstream F("files/leaderboard.txt", ios_base::out);
    if (!F.is_open()) {
        cout << "Failed to load leaderboard file!" << endl;
    }

    //writing to file
    int ranks = 1;
    for (auto iter = Game_Board.Scores.begin(); iter != Game_Board.Scores.end(); iter++){
        if (ranks < 6){
            //cout << "Time: " << iter -> first << "  " << "Name: " << iter -> second << endl;
            F << iter -> first << "," << iter -> second << endl;
        }
        ranks ++;
    }
}
void Draw_Face(sf::RenderWindow &window, Board &Game_Board, int x, int y){
    sf::Texture face_texture;
    if (!Game_Board.Game and !Game_Board.Game_Won and Game_Board.Game_Lost) {
        if(!face_texture.loadFromFile("files/images/face_lose.png")){
            cout << "Failed" << endl;
        }
    }

    if (!Game_Board.Game and Game_Board.Game_Won) {
        if(!face_texture.loadFromFile("files/images/face_win.png")){
            cout << "Failed" << endl;
        }
    }
    if (Game_Board.Game and !Game_Board.Game_Won){
        if(!face_texture.loadFromFile("files/images/face_happy.png")){
            cout << "Failed" << endl;
        }
    }

    sf::Sprite face_sprite;
    face_sprite.setTexture(face_texture);
    face_sprite.setPosition(x, y);
    window.draw(face_sprite);

}

void Recursive_Check(sf::RenderWindow &window, Board &Game_Board, int x, int y, int columns, int rows) {
    //Mouse Position
    int i = x;
    int j = y;

    Game_Board.Tiles.at(i).at(j).Recursion();
}

void Draw_Counter(sf::RenderWindow &window, Board &Game_Board, int columns, int rows){
    sf::Texture counter_texture;
    if(!counter_texture.loadFromFile("files/images/digits.png")){
        cout << "Failed" << endl;
    }
    sf::Sprite counter_sprite;
    counter_sprite.setTexture(counter_texture);

    int n = Game_Board.num_mines - Game_Board.num_flagged;
    int i = 0;
    int num = 2;

    if (n < 0){
        //set negative
        counter_sprite.setPosition(12, (32 * (rows + 0.5f) + 16));
        counter_sprite.setTextureRect(sf::IntRect(210,0,21,32));
        window.draw(counter_sprite);
        n = n * -1;
    }

    while (n != 0) {
        i = (n % 10);
        n /= 10;
        if (i == 0){
            counter_sprite.setTextureRect(sf::IntRect(0,0,21,32));
        }
        if (i == 1){
            counter_sprite.setTextureRect(sf::IntRect(21,0,21,32));
        }
        if (i == 2){
            counter_sprite.setTextureRect(sf::IntRect(42,0,21,32));
        }
        if (i == 3){
            counter_sprite.setTextureRect(sf::IntRect(63,0,21,32));
        }
        if (i == 4){
            counter_sprite.setTextureRect(sf::IntRect(84,0,21,32));
        }
        if (i == 5){
            counter_sprite.setTextureRect(sf::IntRect(105,0,21,32));
        }
        if (i == 6){
            counter_sprite.setTextureRect(sf::IntRect(126,0,21,32));
        }
        if (i == 7){
            counter_sprite.setTextureRect(sf::IntRect(147,0,21,32));
        }
        if (i == 8){
            counter_sprite.setTextureRect(sf::IntRect(168,0,21,32));
        }
        if (i == 9){
            counter_sprite.setTextureRect(sf::IntRect(189,0,21,32));
        }

        if (num == 0){
            counter_sprite.setPosition(33, (32 * (rows + 0.5f) + 16));
        }
        if (num == 1){
            counter_sprite.setPosition(54, (32 * (rows + 0.5f) + 16));
        }
        if (num == 2){
            counter_sprite.setPosition(75, (32 * (rows + 0.5f) + 16));
        }

        window.draw(counter_sprite);
        num--;
    }
}

void Add_Second(sf::RenderWindow &window, Board &Game_Board, Board::Timer Time){
    float stop = 1.f;
    bool second = true;
    int count = 0;
    while (second){
        if (Time.Time_Elapsed() > stop){
            Time.Reset();
            count ++;
        }

        if (count > 1){
        second = false;
    }}

    ///Add second
    Game_Board.seconds += 1;

    if (Game_Board.seconds == 60){
        Game_Board.minutes += 1;
        Game_Board.seconds = 0;
    }
}

void Stop_Timer(sf::RenderWindow &window, Board &Game_Board, Board::Timer Time){
    if (Game_Board.Paused and Game_Board.timer){
        Time.Reset();
   }
}

void Draw_Timer(sf::RenderWindow &window, Board &Game_Board, Board::Timer Time, int columns, int rows) {
    sf::Texture counter_texture;
    if(!counter_texture.loadFromFile("files/images/digits.png")){
        cout << "Failed" << endl;
    }
    if (!Game_Board.Paused and !Game_Board.Reset and Game_Board.timer){
        //fixme takes up alot of memory, so commented out
        //Add_Second(window, Game_Board, Time);
        //fixme remove these 2 lines to fix the timer
        Game_Board.minutes = 5;
        Game_Board.seconds = 30;
    }
    string minutes = to_string(Game_Board.minutes);
    string seconds = to_string(Game_Board.seconds);

    if(Game_Board.Reset){
        Game_Board.timer = true;
        Game_Board.Reset = false;
        Game_Board.time = "";
        Game_Board.minutes = 0;
        Game_Board.seconds = 0;
        Stop_Timer(window, Game_Board, Time);
        //cout <<"Time " << Game_Board.time << endl;
    }
///Check if minutes is single digit
    if (minutes == "0"){
        minutes = "00";
    }
    if (minutes == "1"){
        minutes = "01";
    }
    if (minutes == "2"){
        minutes = "02";
    }
    if (minutes == "3"){
        minutes = "03";
    }
    if (minutes == "4"){
        minutes = "04";
    }
    if (minutes == "5"){
        minutes = "05";
    }
    if (minutes == "6"){
        minutes = "06";
    }
    if (minutes == "7"){
        minutes = "07";
    }
    if (minutes == "8"){
        minutes = "08";
    }
    if (minutes == "9"){
        minutes = "09";
    }
    ///Check if seconds is single digit
    if (seconds == "0"){
        seconds = "00";
    }
    if (seconds == "1"){
        seconds = "01";
    }
    if (seconds == "2"){
        seconds = "02";
    }
    if (seconds == "3"){
        seconds = "03";
    }
    if (seconds == "4"){
        seconds = "04";
    }
    if (seconds == "5"){
        seconds = "05";
    }
    if (seconds == "6"){
        seconds = "06";
    }
    if (seconds == "7"){
        seconds = "07";
    }
    if (seconds == "8"){
        seconds = "08";
    }
    if (seconds == "9"){
        seconds = "09";
    }

    Game_Board.time = minutes + seconds;

    int n = stoi(Game_Board.time);
    int i = 0;
    int num = 3;

    sf::Sprite timer_sprite;
    timer_sprite.setTexture(counter_texture);

    while (n != 0) {
        i = (n % 10);
        n /= 10;
        if (i == 0) {
            timer_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
        }
        if (i == 1) {
            timer_sprite.setTextureRect(sf::IntRect(21, 0, 21, 32));
        }
        if (i == 2) {
            timer_sprite.setTextureRect(sf::IntRect(42, 0, 21, 32));
        }
        if (i == 3) {
            timer_sprite.setTextureRect(sf::IntRect(63, 0, 21, 32));
        }
        if (i == 4) {
            timer_sprite.setTextureRect(sf::IntRect(84, 0, 21, 32));
        }
        if (i == 5) {
            timer_sprite.setTextureRect(sf::IntRect(105, 0, 21, 32));
        }
        if (i == 6) {
            timer_sprite.setTextureRect(sf::IntRect(126, 0, 21, 32));
        }
        if (i == 7 and (num == 3 or num == 1)) {
            timer_sprite.setTextureRect(sf::IntRect(147, 0, 21, 32));
        }
        if (i == 8 and (num == 3 or num == 1)) {
            timer_sprite.setTextureRect(sf::IntRect(168, 0, 21, 32));
        }
        if (i == 9 and (num == 3 or num == 1)) {
            timer_sprite.setTextureRect(sf::IntRect(189, 0, 21, 32));
        }

        if (num == 0) {
            timer_sprite.setPosition((columns * 32) - 97, (32 * (rows + 0.5f) + 16));
        }
        if (num == 1) {
            timer_sprite.setPosition((columns * 32) - 76, (32 * (rows + 0.5f) + 16));
        }
        if (num == 2) {
            timer_sprite.setPosition((columns * 32) - 54, (32 * (rows + 0.5f) + 16));
        }
        if (num == 3) {
            timer_sprite.setPosition((columns * 32) - 33, (32 * (rows + 0.5f) + 16));
        }

        window.draw(timer_sprite);
        num--;
    }
}
