/*
                              
                          
                            
*/

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

const char WALL_C = '*';
const char ECELL_C = ' ';
const char DCELL_C = '.';
const char EWORKER_C = 'w';
const char DWORKER_C = 'W';
const char EBOX_C = 'b';
const char DBOX_C = 'B';

int ROWS = 0;
int COLUMNS = 0;
int* EMPTY_DIST;

enum Cell {
    WALL, ECELL, DCELL, EWORKER, DWORKER, EBOX, DBOX
};

const char CELL_CHARS[] = { '*', ' ', '.', 'w', 'W', 'b', 'B' };

struct Pos {
    int row, column;

    //                                                                                                                                
    //                    
    operator int() const {
        return row * COLUMNS + column;
    }
};

//                          
bool operator==(const Pos& a, const Pos& b) {
    return a.row == b.row && a.column == b.column;
}

bool operator!=(const Pos& a, const Pos& b) {
    return a.row != b.row || a.column != b.column;
}

Pos operator+(const Pos &a, const Pos &b) {
    return {a.row + b.row, a.column + b.column};
}

Pos operator-(const Pos &a, const Pos &b) {
    return {a.row - b.row, a.column - b.column};
}

struct Move {
    Cell* world = nullptr;
    vector<Pos> steps;
};

struct Push {
    Pos box, position;
};

struct State {
    Cell* world = nullptr;
    Pos position {0, 0};
};

typedef vector<Move> MoveList;

void determineDimensions(ifstream &infile) {
    //               
    assert(infile.is_open());
    //                
    //                                                                                                           

    string line;
    getline(infile, line);

    COLUMNS = static_cast<int>(line.length());

    do {
        ++ROWS;
    } while (getline(infile, line));

    infile.clear();
    infile.seekg(0, ios::beg);
}

int index(int row, int column) {
    return row * COLUMNS + column;
}

void writeToArray(Cell *world, ifstream &infile) {
    //               
    assert(infile.is_open());
    //                
    //                                                                 

    char c;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            infile.get(c);

            switch (c) {
                case WALL_C:
                    world[index(row, col)] = WALL;
                    break;
                case ECELL_C :
                    world[index(row, col)] = ECELL;
                    break;
                case DCELL_C :
                    world[index(row, col)] = DCELL;
                    break;
                case EWORKER_C :
                    world[index(row, col)] = EWORKER;
                    break;
                case DWORKER_C :
                    world[index(row, col)] = DWORKER;
                    break;
                case EBOX_C :
                    world[index(row, col)] = EBOX;
                    break;
                case DBOX_C :
                    world[index(row, col)] = DBOX;
                    break;
                default:
                    throw "ERROR IN FILE";
            }
        }
        infile.get(); //                           
    }
}

void showWorld(const Cell *world) {
    //               
    assert(true);
    //                
    //                                                                              

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            cout << CELL_CHARS[world[index(row, col)]];
        }
        cout << '\n';
    }
}

bool canStandOn(const Cell* world, int row, int column) {
    //               
    assert(row >= 0 && row < ROWS);
    assert(column >= 0 && column < COLUMNS);
    //                
    //                                                        

    switch (world[index(row, column)]) {
        case ECELL: case DCELL: case EWORKER: case DWORKER:
            return true;
        default:
            return false;
    }
}

vector<Push> posToPush(const Cell *world) {
    //               
    assert(true);
    //                
    //                                                                                                            

    vector<Push> pushList;
    Cell c;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if ((c = world[index(row, col)]) == EBOX || c == DBOX) {
                //                                  
                //                                           
                if (canStandOn(world, row - 1, col) && canStandOn(world, row + 1, col)) {
                    pushList.push_back({{row, col}, {row - 1, col}});
                    pushList.push_back({{row, col}, {row + 1, col}});
                }
                //                    
                if (canStandOn(world, row, col - 1) && canStandOn(world, row, col + 1)) {
                    pushList.push_back({{row, col}, {row, col - 1}});
                    pushList.push_back({{row, col}, {row, col + 1}});
                }
            }
        }
    }
    return pushList;
}

Pos currentPos(const Cell* world) {
    //               
    assert(true);
    //                
    //                                                                    

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if (world[index(row, col)] == DWORKER || world[index(row, col)] == EWORKER) {
                return {row, col};
            }
        }
    }
    throw "ERROR, NO POSITION FOUND MAN NOT HOME,HE'S COMING FOR YOU NEXT, SOMEONE IS AT THE DOOR...........*person gets murderd by a man with a box*";
}

//                   
bool inWorld(const Pos& p) {
    return p.row >= 0 && p.row < ROWS && p.column >= 0 && p.column < COLUMNS;
}

//                                                                                             
//                                                                                                                          
vector<Pos> aStar(const Cell *world, Pos p, Pos t) {
    //               
    assert(inWorld(p));
    assert(inWorld(t));
    //                
    //                                                                                                   

    int dist[ROWS * COLUMNS];
    memcpy(dist, EMPTY_DIST, sizeof (dist)); //                                                                              

    dist[p] = 1;

    vector<Pos> queue;
    queue.push_back(p); //                                    

    bool found = false;

    while (!found && !queue.empty()) {
        Pos position = queue[0];

        if (position == t) {
            found = true;
        } else {
            queue.erase(queue.begin());

            //                                                                           
            //                                                                        
            //                                                                                             

            Pos nextPosition = {position.row - 1, position.column};
            Cell cell = world[nextPosition];
            if ((cell == ECELL || cell == DCELL) && dist[nextPosition] == 0) {
                dist[nextPosition] = dist[position] + 1;
                queue.push_back(nextPosition);
            }

            nextPosition = {position.row + 1, position.column};
            cell = world[nextPosition];
            if ((cell == ECELL || cell == DCELL) && dist[nextPosition] == 0) {
                dist[nextPosition] = dist[position] + 1;
                queue.push_back(nextPosition);
            }

            nextPosition = {position.row, position.column + 1};
            cell = world[nextPosition];
            if ((cell == ECELL || cell == DCELL) && dist[nextPosition] == 0) {
                dist[nextPosition] = dist[position] + 1;
                queue.push_back(nextPosition);
            }

            nextPosition = {position.row, position.column - 1};
            cell = world[nextPosition];
            if ((cell == ECELL || cell == DCELL) && dist[nextPosition] == 0) {
                dist[nextPosition] = dist[position] + 1;
                queue.push_back(nextPosition);
            }
        }
    }

    //                                          
    queue.clear();

    if (found) {
        //                                                                                         
        //                         
        while (t != p) {
            queue.insert(queue.begin(), t);
            Pos nextPosition = {t.row - 1, t.column};
            if (dist[nextPosition] == dist[t] - 1) {
                t = nextPosition;
            } else if (dist[nextPosition = {t.row + 1, t.column}] == dist[t] - 1) {
                t = nextPosition;
            } else if (dist[nextPosition = {t.row, t.column - 1}] == dist[t] - 1) {
                t = nextPosition;
            } else {
                t = {t.row, t.column + 1};
            }
        }
        //                                            
        //                                                                                                                                     
        queue.insert(queue.begin(), p);
    }

    return queue;
}

bool isSolved(const Cell *world) {
    //               
    assert(true);
    //                
    //                                                                                             

    bool solved = true;
    for (int i = 0; solved && i < ROWS * COLUMNS; ++i) {
        if (world[i] == EBOX) {
            solved = false;
        }
    }
    return solved;
}

MoveList solve(Cell* world) {
    //               
    assert(true);
    //                
    //                                                                          

    vector<State> states;
    vector<MoveList> queue;

    //                   
    MoveList first;
    Move firstMove;
    firstMove.world = world;
    first.push_back(firstMove);

    queue.push_back(first);
    states.push_back({ world, currentPos(world) });

    MoveList result;

    while (!queue.empty()) {
        MoveList list = queue[0];
        Move last = list[list.size() - 1];

        if (isSolved(last.world)) {
            result = list;
            queue.clear(); //                                       
        } else {
            //                                                                               
            //              
            //                       

            //                                                                        
            queue.erase(queue.begin());
            vector<Push> pushList = posToPush(last.world);

            Pos position = currentPos(last.world);

            for (Push push : pushList) {
                //                                                    
                vector<Pos> path = aStar(last.world, position, push.position);

                if (!path.empty()) {
                    Cell *copyWorld = new Cell[ROWS * COLUMNS];
                    for (int i = 0; i < ROWS * COLUMNS; ++i)
                        copyWorld[i] = last.world[i];

                    Pos nextBox = push.box + (push.box - push.position);

                    //                                                                                                                           
                    copyWorld[position] = last.world[position] == DWORKER ? DCELL : ECELL;
                    copyWorld[nextBox] = last.world[nextBox] == DCELL ? DBOX : EBOX;
                    copyWorld[push.box] = last.world[push.box] == DBOX ? DWORKER : EWORKER;

                    //                                              
                    bool match = false;
                    for (auto it = states.begin(); !match && it != states.end(); ++it) {
                        State &state = *it;

                        match = push.box == state.position;
                        for (int j = 0; match && j < ROWS * COLUMNS; ++j) {
                            match = copyWorld[j] == state.world[j];
                        }
                    }

                    if (!match) {
                        MoveList copy = list;

                        copy.push_back({copyWorld, path}); //                              

                        queue.push_back(copy);

                        states.push_back({copyWorld, push.box});
                    }
                }
            }
        }
    }

    return result;
}

MoveList solveRec(Cell* world, int depth, int& maxDepth, vector<State>& states) {
    bool found = false;
    MoveList shortest;

    if (!isSolved(world) && (maxDepth == 0 || depth < maxDepth)) {
        vector<Push> pushList = posToPush(world);

        Pos position = currentPos(world);

        states.push_back({world, position});

        for (Push push : pushList) {
            vector<Pos> path = aStar(world, position, push.position);

            if (!path.empty()) {
                Cell *copyWorld = new Cell[ROWS * COLUMNS];
                for (int i = 0; i < ROWS * COLUMNS; ++i)
                    copyWorld[i] = world[i];

                Pos nextBox = push.box + (push.box - push.position);

                //                                                                                                                           
                copyWorld[position] = world[position] == DWORKER ? DCELL : ECELL;
                copyWorld[nextBox] = world[nextBox] == DCELL ? DBOX : EBOX;
                copyWorld[push.box] = world[push.box] == DBOX ? DWORKER : EWORKER;

                //                                              
                bool match = false;
                for (auto it = states.begin(); !match && it != states.end(); ++it) {
                    State &state = *it;

                    match = push.box == state.position;
                    for (int j = 0; match && j < ROWS * COLUMNS; ++j) {
                        match = copyWorld[j] == state.world[j];
                    }
                }

                if (!match) {
                    MoveList copy = solveRec(copyWorld, depth + 1, maxDepth, states);

                    if (!copy.empty() || isSolved(copyWorld)) {
                        maxDepth = depth + static_cast<int>(copy.size());

                        copy.insert(copy.begin(), { copyWorld, path });
                        shortest = copy;
                        found = true;
                    }
                }
            }
        }
    }

    return found ? shortest : MoveList();
}

MoveList solve(Cell* world, int maxDepth) {
    //               
    assert(maxDepth >= 0);
    //                
    //                                                                            

    vector<State> states;

    return solveRec(world, 0, maxDepth, states);
}

int main() {
    cout << "Please specify the level file: " << endl;
    string filename;
    getline(cin, filename);
    ifstream infile;
    infile.open(filename);

    determineDimensions(infile);

    //                                                                                  
    EMPTY_DIST = new int[ROWS * COLUMNS];
    for (int i = 0; i < ROWS * COLUMNS; ++i)
        EMPTY_DIST[i] = 0;

    Cell* world = new Cell[ROWS * COLUMNS];

    writeToArray(world, infile);
    showWorld(world);

    cout << "What is the maximum depth you want to search? (-1 = breadth-first)" << endl;

    string input;
    getline(cin, input);

    int maxDepth = stoi(input);

    MoveList result;

    if (maxDepth < 0) {
        result = solve(world);
    } else {
        result = solve(world, maxDepth);
    }

    cout << "Done!" << endl;
    //                                                                                                                                 
    for (Move& move : result) {
        cout << endl;
        showWorld(move.world);
    }

    return 0;
}

