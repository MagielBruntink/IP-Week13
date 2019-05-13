#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                       
//                            

struct Pos{
    int col;
    int row;
};

typedef Pos Dir;

const Dir north = {0, -1}, east = {1, 0}, south = {0, 1}, west = {-1, 0};

struct Puzzle{
    vector<vector<char>> board;
    Pos wKeeperPosition;
};

Pos operator+(Pos a, Pos b){

    /*              */
    assert (true);

    /*               
                            */

    Pos sum;
    sum.col = a.col + b.col;
    sum.row = a.row + b.row;

    return sum;
}

bool operator==(Puzzle pa, Puzzle pb){

    /*              */
    assert (true);

    /*               
                                        */

    vector<vector<char>> a = pa.board;
    vector<vector<char>> b = pb.board;

    if((a.size() != b.size()) || (a[0].size() != b[0].size()))
        return false;

    for(int x = 0; x < a.size(); x++){
        for(int y = 0; y < a[0].size(); y++){
            if(a[x][y] != b[x][y])
                return false;
        }
    }

    return true;
}

bool puzzle_ready(vector<vector<char>>& board){

    /*              */
    assert (true);

    /*               
                                 */

    for(int x = 0; x < board.size(); x++){
        for(int y = 0; y < board[0].size(); y++){
            if(board[x][y] == 'b')
                return false;
        }
    }

    cout << "PUZZLE DONE" << endl;
    return true;
}

bool direction(Dir dir, Pos& boxPos, Puzzle puzzle){

    /*              */
    assert (true);

    /*               
                                                 */

    Pos keeperPos = puzzle.wKeeperPosition;

    char current = puzzle.board[keeperPos.row + dir.row][keeperPos.col + dir.col];
    char next = ' ';

    if((keeperPos.row + (dir.row * 2)) < puzzle.board.size() && (keeperPos.col + (dir.col * 2)) < puzzle.board[0].size())
        next = puzzle.board[keeperPos.row + (dir.row * 2)][keeperPos.col + (dir.col * 2)];

    if((current == 'b' || current == 'B') && (next == ' ' || next == '.')){
        boxPos = {keeperPos.col + (dir.col * 2), keeperPos.row + (dir.row * 2)};
        return true;
    }
    else if(current == ' ' || current == '.'){
        return true;
    }

    return false;
}

void move_direction(Dir dir, Pos& box, Puzzle& puzzle){

    /*              */
    assert (true);

    /*               
                                                */

    char lastKeeperChar = puzzle.board[puzzle.wKeeperPosition.row][puzzle.wKeeperPosition.col];
    puzzle.board[puzzle.wKeeperPosition.row][puzzle.wKeeperPosition.col] = lastKeeperChar == 'w' ? ' ' : '.';

    if(box.col == 0 && box.row == 0){
        char nextKeeperChar = puzzle.board[puzzle.wKeeperPosition.row + dir.row][puzzle.wKeeperPosition.col + dir.col];
        puzzle.board[puzzle.wKeeperPosition.row + dir.row][puzzle.wKeeperPosition.col + dir.col] = nextKeeperChar == '.' ? 'W' : 'w';
    }
    else{
        char nextKeeperChar = puzzle.board[puzzle.wKeeperPosition.row + dir.row][puzzle.wKeeperPosition.col + dir.col];
        puzzle.board[puzzle.wKeeperPosition.row + dir.row][puzzle.wKeeperPosition.col + dir.col] = nextKeeperChar == 'b' ? 'w' : 'W';

        char boxChar = puzzle.board[box.row][box.col];
        puzzle.board[box.row][box.col] = boxChar == '.' ? 'B' : 'b';
    }

    puzzle.wKeeperPosition = {puzzle.wKeeperPosition.col + dir.col, puzzle.wKeeperPosition.row + dir.row};
    box = {0, 0};
}

bool new_config(vector<Puzzle> configurations, Puzzle puzzle){
    /*              */
    assert (true);

    /*               
                                                                          */

    for(int i = 0; i < configurations.size(); i++){
        if(configurations[i] == puzzle)
            return false;
    }

    return true;
}

void solve(Puzzle& puzzle, int& moves){

    /*              */
    assert (true);

    /*               
                                   */

    vector<Puzzle> existingConfigs;
    vector<Puzzle> lastQueue;

    //                                                        
    lastQueue.push_back(puzzle);

    Pos box = {0, 0};
    Dir directions[4] = {north, east, south, west};

    while(!puzzle_ready(puzzle.board)){
        vector<Puzzle> lastQueueTemp = lastQueue;
        lastQueue.clear();

        for(int k = 0; k < lastQueueTemp.size(); k++){
            for(int i = 0; i < 4; i++){
                Dir currentDirection = directions[i];

                if(direction(currentDirection, box, lastQueueTemp[k])){
                    moves++;

                    Puzzle original = lastQueueTemp[k];
                    move_direction(currentDirection, box, lastQueueTemp[k]);

                    if(new_config(existingConfigs, lastQueueTemp[k])){
                        existingConfigs.push_back(lastQueueTemp[k]);
                        lastQueue.push_back(lastQueueTemp[k]);

                        if(puzzle_ready(lastQueueTemp[k].board)){
                            puzzle = lastQueueTemp[k];
                            return;
                        }
                    }

                    lastQueueTemp[k] = original;
                }
            }
        }
    }
}

void get_board(vector<vector<char>>& board, Pos& keeperPos){
    /*              */
    assert (true);

    /*               
                                                                   
                                         */

    ifstream stream;

    string fileName = "challenge.31.txt";
    stream.open(fileName.c_str());

    if(!stream.is_open()){
        cout << "Could not open file" << endl;
        return;
    }

    char a;
    stream.get(a);

    vector<char> subVector;

    while(stream){
        if(a != '\n'){
            if(a == 'w' || a == 'W')
                keeperPos = {subVector.size(), board.size()};

            subVector.push_back(a);
        }
        else{
            board.push_back(subVector);
            subVector.clear();
        }

        stream.get(a);
    }

    stream.close();
}

int depth = 0;
int depth_counter = 0;

int solve_depth(Puzzle& p){

    /*              */
    assert (true);

    /*               
                                                                                           */

    if(puzzle_ready(p.board))
        return 1;

    Pos box = {0, 0};
    Dir directions[4] = {north, east, south, west};

    for(int i = 0; i < 4; i++){
        Dir currentDirection = directions[i];

        if(direction(currentDirection, box, p)){
            depth_counter = depth;

            while(depth_counter >= 0){
                Dir nextDirection = i == 3 ? directions[0] : directions[i];

                if(direction(currentDirection, box, p)){
                    move_direction(currentDirection, box, p);
                }
                else if(direction(nextDirection, box, p) && i != 0){
                    move_direction(nextDirection, box, p);
                }

                depth_counter--;
            }
        }
    }

    depth++;
    solve_depth(p);
}

int main(){
    Puzzle puzzle;
    get_board(puzzle.board, puzzle.wKeeperPosition);

    cout << "Solving puzzle... this may take a while" << endl;

    int moves = 0;
    solve(puzzle, moves);

    cout << "program stopped, solving took " << moves << " moves. Result:" << endl;

    for(int x = 0; x < puzzle.board.size(); x++){
        for(int y = 0; y < puzzle.board[0].size(); y++){
            cout << puzzle.board[x][y];
        }

        cout << endl;
    }

    return 0;
}

