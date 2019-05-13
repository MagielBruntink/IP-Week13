#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>

//                                                     
using namespace std;

struct position {
    int col, row;
};
struct puzzle {
    vector< vector<char> > board;
    position character;
};

struct candidate {
    puzzle candidate;
    int parent_candidate;
};

position north {
    -1, 0
};
position south {
    1, 0
};
position east {
    0, 1
};
position west {
    0, -1
};

void display_puzzle(vector< vector<char> > puzzle) {
    //             
    assert (true);
    //                                                                  
    for (int i = 0; i < puzzle.size() - 1; i++) {
        for (int j = 0; j < puzzle[0].size(); j++) {
            cout << puzzle[i][j];
        }
        cout << endl;
    }
}

void get_character_position(puzzle& start) {
    //             
    assert (true);
    //                                                                                                                                               
    for(int i = 0; i < start.board.size() - 1; i++) {
        for (int j = 0; j < start.board[0].size() - 1; j++){
            if (start.board[i][j] == 'w' || start.board[i][j] == 'W'){

                start.character.col = i;
                start.character.row = j;

            }
        }
    }
}

bool readfile(ifstream& input_file, puzzle& start) {
    //            
    assert (input_file.is_open());
    //                                                                

    char a;
    vector <char> row;
    while (input_file) {
        input_file.get(a);
        if (a ==  '\n') {
            start.board.push_back(row);
            row.clear();
        } else {
            row.push_back(a);
        }
    }

    get_character_position(start);

}
bool puzzle_ready(puzzle candidate) {
   //             
   assert (true);
   //                                                                                                                                 
    for (int i = 0; i < candidate.board.size() - 1; i++) {
        for (int j = 0; j < candidate.board[0].size(); j++) {
            if (candidate.board[i][j] == 'b') {

                return false;
            }
        }
    }
    return true;
}

bool can_go_north(puzzle p) {
    //            
    assert (true);
    //                                                                                                                                                                                   
    int posx = p.character.col;
    int posy = p.character.row;

    if (p.board[posx - 1][posy ] != '*' ) {
        if((p.board[posx - 1][posy ] == 'b' || p.board[posx - 1][posy ] == 'B') && ( p.board[posx - 2][posy] == '*'  || p.board[posx - 2][posy] == 'b' || p.board[posx - 2][posy] == 'B')) {
            return false;
        }
        return true;
    }
}

bool can_go_south(puzzle p) {
    //            
    assert (true);
    //                                                                                                                                                                                   
    int posx = p.character.col;
    int posy = p.character.row;

    if (p.board[posx + 1][posy] != '*' ) {
        if((p.board[posx + 1][posy] == 'b' || p.board[posx + 1][posy ] == 'B') && ( p.board[posx + 2][posy ] == '*'  || p.board[posx + 2][posy ] == 'b' || p.board[posx + 2][posy] == 'B')) {
            return false;
        }
        return true;
    }
}
bool can_go_east(puzzle p) {
    //            
    assert (true);
    //                                                                                                                                                                                       
    int posx = p.character.col;
    int posy = p.character.row;

    if (p.board[posx][posy + 1] != '*' ) {
        if((p.board[posx ][posy + 1] == 'b' || p.board[posx][posy + 1] == 'B') && ( p.board[posx ][posy + 2] == '*'  || p.board[posx ][posy + 2] == 'b' || p.board[posx ][posy + 2] == 'B')) {
            return false;
        }
        return true;
    }
}
bool can_go_west(puzzle p) {
    //            
    assert (true);
    //                                                                                                                                                                                         

    int posx = p.character.col;
    int posy = p.character.row;

    if (p.board[posx ][posy - 1] != '*' ) {
        if((p.board[posx ][posy - 1] == 'b' || p.board[posx][posy - 1] == 'B') && ( p.board[posx ][posy -2 ] == '*'  || p.board[posx ][posy - 2] == 'b' || p.board[posx ][posy - 2] == 'B')) {
            return false;
        }
        return true;
    }
}

puzzle move(puzzle p, position next) {
    //             
    assert (true);
    //                                                                                                         
    cout << "made a move" << endl;
    //               
    //                               
    if (p.board[p.character.col + next.col][p.character.row + next.row] == 'b' ||p.board[p.character.col + next.col][p.character.row + next.row] == 'B' ) {
        //          
        if (p.board[p.character.col + 2 * next.col][p.character.row + 2 * next.row] == '.'){
            p.board[p.character.col + 2 * next.col][p.character.row + 2 * next.row] = 'B';
        } else {
            p.board[p.character.col + 2 * next.col][p.character.row + 2 * next.row] = 'b';
        }
        //                
        if (p.board[p.character.col + next.col][p.character.row + next.row] == 'b') {
            p.board[p.character.col + next.col][p.character.row + next.row] = ' ';
        } else {
            p.board[p.character.col + next.col][p.character.row + next.row] = '.';
        }
    }
    //                                     

    if (p.board[p.character.col + next.col][p.character.row + next.row] == '.' ) {
        p.board[p.character.col + next.col][p.character.row + next.row] = 'W';
    } else {
        p.board[p.character.col + next.col][p.character.row + next.row] = 'w';
    }
    //                        
    if(p.board[p.character.col][p.character.row] == 'W' ) {
        p.board[p.character.col][p.character.row] = '.';
    } else {
        p.board[p.character.col][p.character.row] = ' ';
    }

    get_character_position(p);

    return p;

}
void showpath (vector <candidate> c, int i) {
    //             
    assert (true);
    //                                                             
    vector<candidate> solution;
    int counter = -1;

    while(i != -1) {
        solution.push_back(c[i]);
        counter++;
        i = c[i].parent_candidate;
    }

    cout << "there are : " << counter << " steps to the goal" << endl;
    for (int i = solution.size() -1; i >= 0 ; i = i -1) {
        display_puzzle(solution[i].candidate.board);
    }
}

bool puzzle_present(vector <candidate> c, puzzle p) {
    //              
    assert (true);
    //                                                                                                       
    for(int i = 0; i < c.size(); i++) {
        if (c[i].candidate.board == p.board) {

            return true;
        }
    }
    return false;
}

void tries(vector <candidate>& c, int i, position next) {
    puzzle p = c[i].candidate;
    puzzle newp = move(p, next);
    candidate newc = {newp, i};
    if (!puzzle_present(c, newp)) {

        c.push_back(newc);
    }

}

int breadth_first(puzzle start) {
    //             
    assert (true);
    //                                                                                                                                                     

        vector <candidate> c = {{start, -1}};
        int i = 0;
        while (i < c.size() && !puzzle_ready(c[i].candidate)) {

            puzzle p  = c[i].candidate;
            if (can_go_north (p)) {
                tries(c, i, north);
            }
            if (can_go_south(p)) {
                tries(c, i, south);
            }
            if (can_go_east(p)) {
                tries(c, i, east);
            }
            if (can_go_west(p)) {
                tries(c, i, west);
            }
            i++;
        }
        if (i < c.size()) {
            showpath(c, i);
        }

}
void show_solution(vector<puzzle> shortest) {
    //             
    assert (true);
    //                                                             
    cout << "the solution is: " << shortest.size() - 1 << "long" << endl;
    for (int i = 0; i < shortest.size() ; i ++) {
        display_puzzle(shortest[i].board);
    }
}

bool puzzle_present2 (puzzle p, vector <puzzle> c) {
    //             
    assert (true);
    //                                                                                                
    for (int i = 0; i < c.size() - 1; i ++) {
        if (c[i].board == p.board) {
            return true;
        }
    }
    return false;
}

void depth_first (vector<puzzle>& attempt, vector<puzzle>& shortest, int max_depth);

void tries2 (vector <puzzle>& attempt, position next, vector <puzzle>&  shortest, int max_depth) {
    puzzle p = attempt[attempt.size() -  1];
    puzzle newp = move(p, next);
    if (!puzzle_present2(newp, attempt)) {
        attempt.push_back(newp);
        depth_first(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void depth_first (vector<puzzle>& attempt, vector<puzzle>& shortest, int max_depth) {
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    puzzle p = attempt[CURRENT - 1] ;
    if (BEST > 0 && CURRENT >= BEST) {
        return ;
    } else if (CURRENT > max_depth + 1) {
        return ;
    } else if (puzzle_ready(p)) {
        shortest = attempt;
        return ;
    }

    if (can_go_north(p)) {
        tries2(attempt, north, shortest, max_depth);
    }
    if (can_go_south(p)) {
        tries2(attempt, south, shortest, max_depth);
    }

    if (can_go_east(p)) {
        tries2(attempt, east, shortest, max_depth);
    }

    if (can_go_west(p)) {
        tries2(attempt, west, shortest, max_depth);
    }
}

int main() {
    string filename;
    string search;
    puzzle start;
    cout << "Enter filename of puzzle you want to solve: " << endl;
    cin >> filename;

    ifstream input_file (filename);
    if (input_file.is_open()) {
        cout << "File opened succesfully" << endl;
    } else {
        cout << "File failed to open" << endl;
    }

    readfile(input_file, start);
    cout << start.character.col << " " << start.character.row << endl;
    breadth_first(start);
    vector <puzzle> attempt = {start};
    vector <puzzle> shortest;
    //                                  
   //                         

}

