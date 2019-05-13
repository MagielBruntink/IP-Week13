#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
using namespace std;

//                           
//                           

const int WIDTH  = 20;
const int HEIGHT = 20;

//               
enum cell {EMPTY = 0, WALL, AIR, DEST, WORKER, WORKER_DEST, BOX, BOX_DEST};

struct Pos {
    unsigned int x;
    unsigned int y;
};

struct Puzzle {
    cell board[WIDTH][HEIGHT];
    Pos worker;
};

struct Candidate {
    Puzzle candidate;
    int parent_candidate;    
};

//                    
template <typename El>
int size (vector<El>& vec);
bool read_puzzle(const string filename, cell board[WIDTH][HEIGHT]);
void display_puzzle(const cell board[WIDTH][HEIGHT]);
void show_path(vector<Candidate>& c, int i);
Pos north(Puzzle p); Pos south(Puzzle p); Pos east(Puzzle p); Pos west(Puzzle p);
bool can_go_north(Puzzle p); bool can_go_south(Puzzle p); bool can_go_east(Puzzle p); bool can_go_west(Puzzle p);
bool puzzle_ready(Puzzle p);
bool puzzle_present(Puzzle p, vector<Puzzle>& c);
bool candidate_present(Candidate state, vector<Candidate>& c);
Pos find_worker(const cell board[WIDTH][HEIGHT]);
void tries_depth(vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest);
void solve_depth(vector<Puzzle>& attempt, vector<Puzzle>& shortest);
void tries_breadth(vector<Candidate>& c, int i, Pos next);
void solve_breadth(Puzzle start);
Puzzle move_worker(Puzzle level, Pos next);

//              
int main() {
    vector<Puzzle> attempt;
    vector<Puzzle> shortest;
    string filename;
    char method;
    Puzzle challenge;
    //                 
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            challenge.board[j][i] = EMPTY;
        }
    }
    cout << "Enter filename: ";
    cin >> filename;
    if(!read_puzzle(filename, challenge.board)) {
        cout << "invalid filename." << endl;
        return -1;
    }
    challenge.worker = find_worker(challenge.board);
    attempt.push_back(challenge);

    cout << "Enter method ('B' for breadth-first and 'D' for depth-first): ";
    cin >> method;
    if(method == 'B' || method == 'b') {
        solve_breadth(attempt[0]);
    } else if(method == 'D' || method == 'd') {
        display_puzzle(attempt[0].board);
        solve_depth(attempt,shortest);
        display_puzzle(shortest[size(shortest)-1].board);
    } else {
        cout << "invalid method." << endl;
    }
    return 0;
}

bool read_puzzle(const string filename, cell board[WIDTH][HEIGHT]) {
    //               
    assert (true) ;
    //                  
    //                                                                        
    ifstream infile;
    infile.open(filename);
    if(!infile.is_open()) {
        return false;
    }
    char c;
    int x = 0, y = 0;    
    while(infile) {
        do {
            infile.get(c);
            switch(c) {
                case '*': board[x][y] = WALL; break;
                case ' ': board[x][y] = AIR; break;
                case '.': board[x][y] = DEST; break;
                case 'w': board[x][y] = WORKER; break;
                case 'W': board[x][y] = WORKER_DEST; break;
                case 'b': board[x][y] = BOX; break;
                case 'B': board[x][y] = BOX_DEST; break;
            }
            x++;
        } while(c != '\n');
        x = 0;
        y++;
    }
    infile.clear();
    infile.close();
    return true;
}

void display_puzzle(const cell board[WIDTH][HEIGHT]) {
    //               
    assert (true) ;
    //                  
    //                                                              
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch(board[j][i]) {
                case 1: cout << '*'; break;
                case 2: cout << ' '; break;
                case 3: cout << '.'; break;
                case 4: cout << 'w'; break;
                case 5: cout << 'W'; break;
                case 6: cout << 'b'; break;
                case 7: cout << 'B'; break;
            }
        }
        if(board[0][i] != EMPTY) {
            cout << endl;
        }
    }
}

void show_path(vector<Candidate>& c, int i) {
    //              
    assert (true) ;
    //                                                                          
    while (i >= 0) {
        display_puzzle(c[i].candidate.board);
        i = c[i].parent_candidate;
    }
    cout << "Read from bottom to top" << endl;
}

Pos find_worker(const cell board[WIDTH][HEIGHT]) {
    //               
    assert(board[0][0] == WALL);
    //                                                   
    Pos worker;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[j][i] == WORKER) {
                worker.x = j;
                worker.y = i;
                return worker;
            }
        }
    }    
    return worker;
}

template <typename El>
int size (vector<El>& vec) {
//               
    assert (true) ;
//                                                                
    return static_cast<int> (vec.size());
}

Pos north(Puzzle p) {
    //               
    assert (true) ;
    //                                                                 
   return {p.worker.x, p.worker.y - 1};
}

Pos south(Puzzle p) {
    //               
    assert (true) ;
    //                                                             
    return {p.worker.x, p.worker.y + 1};
}

Pos east(Puzzle p) {
    //               
    assert (true) ;
    //                                                        
    return {p.worker.x + 1, p.worker.y};
}

Pos west(Puzzle p) {
    //               
    assert (true) ;
    //                                                        
    return {p.worker.x - 1, p.worker.y};
}

bool can_go_north(Puzzle p) {
    //               
    assert (true) ;
    //                                                                                             
    if(p.board[north(p).x][north(p).y] == BOX)
        return p.board[north(p).x][north(p).y-1] != BOX && p.board[north(p).x][north(p).y-1] != BOX_DEST && p.board[north(p).x][north(p).y-1] != WALL;
    return p.board[north(p).x][north(p).y] == AIR || p.board[north(p).x][north(p).y] == DEST;
}

bool can_go_south(Puzzle p) {
    //               
    assert (true) ;
    //                                                                                             
    if(p.board[south(p).x][south(p).y] == BOX)
        return p.board[south(p).x][south(p).y+1] != BOX && p.board[south(p).x][south(p).y+1] != BOX_DEST && p.board[south(p).x][south(p).y+1] != WALL;
    return p.board[south(p).x][south(p).y] == AIR || p.board[south(p).x][south(p).y] == DEST;
}

bool can_go_east(Puzzle p) {
    //               
    assert (true) ;
    //                                                                                            
    if(p.board[east(p).x][east(p).y] == BOX)
        return p.board[east(p).x+1][east(p).y] != BOX && p.board[east(p).x+1][east(p).y] != BOX_DEST && p.board[east(p).x+1][east(p).y] != WALL;
    return p.board[east(p).x][east(p).y] == AIR || p.board[east(p).x][east(p).y] == DEST;
}

bool can_go_west(Puzzle p) {
    //               
    assert (true) ;
    //                                                                                            
    if(p.board[west(p).x][west(p).y] == BOX)
        return p.board[west(p).x-1][west(p).y] != BOX && p.board[west(p).x-1][west(p).y] != BOX_DEST && p.board[west(p).x-1][west(p).y] != WALL;
    return p.board[west(p).x][west(p).y] == AIR || p.board[west(p).x][west(p).y] == DEST;
}

bool puzzle_ready(Puzzle p) {
    //               
    assert (true) ;
    //                                                                                
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (p.board[j][i] == BOX) {
                return false;
            }
        }
    }
    return true;
}

Puzzle move_worker(Puzzle level, Pos next) {
    //               
    assert(true);
    //                                                         
    //                       
    if(level.board[level.worker.x][level.worker.y] == WORKER_DEST) {
        level.board[level.worker.x][level.worker.y] = DEST;
    } else {
        level.board[level.worker.x][level.worker.y] = AIR;
    }
    //                       
    switch(level.board[next.x][next.y]) {
        case AIR: level.board[next.x][next.y] = WORKER; break;
        case DEST: level.board[next.x][next.y] = WORKER_DEST; break;
        case BOX:
            int next_to_box_x = next.x - level.worker.x + next.x;
            int next_to_box_y = next.y - level.worker.y + next.y;
            switch(level.board[next_to_box_x][next_to_box_y]) {
                case AIR: 
                    level.board[next.x][next.y] = WORKER;
                    level.board[next_to_box_x][next_to_box_y] = BOX;
                break;
                case DEST:
                    level.board[next.x][next.y] = WORKER;
                    level.board[next_to_box_x][next_to_box_y] = BOX_DEST;
                break;
            }
        break;
    }
    level.worker = find_worker(level.board);
    return level;
}

bool puzzle_present(Puzzle p, vector<Puzzle>& c) {
    //               
    assert (true) ;
    //                                                                            
    for (int x = 0; x < size(c); x++) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (p.board[j][i] != c[x].board[j][i]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void tries_depth (vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest) {
    //               
    assert (true) ;
    //                                                                   
    Puzzle p = attempt[size(attempt)-1];
    Puzzle newp = move_worker(p,next);
    if (!puzzle_present(newp, attempt)) {
        attempt.push_back(newp);
        solve_depth(attempt, shortest);
        attempt.pop_back();
    }
}

void solve_depth (vector<Puzzle>& attempt, vector<Puzzle>& shortest) {
    //               
    assert (true) ;
    //                                                                                                              
    const int current = size(attempt);
    const int best = size(shortest);
    Puzzle p = attempt[current-1];
    if(best > 0 && current >= best) {
        return;
    } else if (current > 38) {
        return;
    } else if (puzzle_ready(p)) {
        shortest = attempt;
        return;
    } if (can_go_north(p)) {
        tries_depth(attempt, north(p), shortest);
    } if (can_go_south(p)) {
        tries_depth(attempt, south(p), shortest);
    } if (can_go_west(p)) {
        tries_depth(attempt, west(p), shortest);
    } if (can_go_east(p)) {
        tries_depth(attempt, east(p), shortest);
    }
}

bool candidate_present(Candidate state, vector<Candidate>& c) {
    //               
    assert (true) ;
    //                                                                            
    for (int x = 0; x < size(c); x++) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (state.candidate.board[j][i] != c[x].candidate.board[j][i]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void tries_breadth(vector<Candidate>& c, int i, Pos next) {
    //              
    assert (true) ;
    //                                                                 
    Puzzle p = c[i].candidate;
    Puzzle newp = move_worker(p,next);
    Candidate newc = {newp, i};
    //                                
        c.push_back(newc);
    // 
}

void solve_breadth(Puzzle start) {
    //              
    assert (true) ;
    //                                                                                                            
    vector<Candidate> c = {{start,-1}};
    int i = 0;
    while (i < size(c) && !puzzle_ready(c[i].candidate)) {
        Puzzle p = c[i].candidate;
        if (can_go_north(p)) {
            tries_breadth(c,i,north(p));
        }
        if (can_go_south(p)) {
            tries_breadth(c,i,south(p));
        }
        if (can_go_east(p)) {
            tries_breadth(c,i,east(p));
        }
        if (can_go_west(p)) {
            tries_breadth(c,i,west(p));
        }
        i++;                
    }
    if (i < size(c)) {
        show_path(c,i);
    }
}
