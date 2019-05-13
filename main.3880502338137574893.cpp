#include <iostream>
#include <fstream>
#include <vector>

//                        

using namespace std;

const int HEIGHT = 6;
const int WIDTH = 7;

typedef char Cell;
const Cell EMPTY = WIDTH * HEIGHT;

vector <vector <Cell> > Puzzle  = {{'*','*','*','*','*','*','*'},
                                        {'*','w',' ',' ',' ','*','*'},
                                        {'*',' ','b','b',' ',' ','*'},
                                        {'*',' ','*','.',' ','.','*'},
                                        {'*',' ',' ',' ',' ',' ','*'},
                                        {'*','*','*','*','*','*','*'}};

struct pos {
    int row;
    int col;
};

struct puzzle {
    vector <vector <Cell>> board;
};

struct Candidate {
    puzzle Candidate;
    int parent_candidate;
};

vector <Candidate> candidate;

bool puzzle_ready (puzzle k){
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            if (k.board[i][j] == 'b')
                return false;
        }
    }
    return true;
}

bool north (puzzle q, puzzle werker, vector <Candidate>& l, int p){
    int i = 0;
    int j = 0;
    q = werker;
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            if (werker.board[i][j] == 'w'){
                q.board[i][j] = werker.board[i][j];
            }
        }
    }

            if (q.board[i][j] == 'w' && ((i-1) > 0) && q.board[i-1][j] == (' ' || '.')){
                if (q.board[i-1][j] == '.'){
                    q.board[i-1][j] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }

                else if (q.board[i-1][j] == ' '){
                    q.board[i-1][j] = 'w';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

            else if (q.board[i][j] == 'w' && ((i-2) > 0) && q.board[i-1][j] == 'b'){
                if (((i-2) > 0) && q.board[i-2][j] == ' '){
                    q.board[i-2][j] = 'b';
                    q.board[i-1][j] = 'w';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
                if (((i-2) > 0) && q.board[i-2][j] == '.'){
                    q.board[i-2][j] = 'b';
                    q.board[i-1][j] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

            else if (q.board[i][j] == 'w' && ((i-2) > 0) && q.board[i-1][j] == 'B'){
                if (((i-2) > 0) && q.board[i-2][j] == ' '){
                    q.board[i-2][j] = 'b';
                    q.board[i-1][j] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
                if (((i-2) > 0) && q.board[i-2][j] == '.'){
                    q.board[i-2][j] = 'B';
                    q.board[i-1][j] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

    return false;
}

bool east (puzzle q, puzzle werker, vector <Candidate>& l, int p){
    int i = 0;
    int j = 0;
    q = werker;

    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            if (werker.board[i][j] == 'w'){
                q.board[i][j] = werker.board[i][j];
            }
        }
    }
            if (q.board[i][j] == 'w' && ((j+1) < WIDTH) && q.board[i][j+1] == (' ' || '.')){
                if (q.board[i][j+1] == '.'){
                    q.board[i][j+1] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }

                else if (q.board[i][j+1] == ' '){
                    q.board[i][j+1] = 'w';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

            else if (q.board[i][j] == 'w' && ((j+2) < WIDTH) && q.board[i][j+1] == 'b'){
                if (((j+2) < WIDTH) && q.board[i][j+2] == ' '){
                    q.board[i][j+2] = 'b';
                    q.board[i][j+1] = 'w';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
                if (((j+2) < WIDTH) && q.board[i][j+2] == '.'){
                    q.board[i][j+2] = 'b';
                    q.board[i][j+1] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

            else if (q.board[i][j] == 'w' && ((j+2) > 0) && q.board[i][j+1] == 'B'){
                if (((j+2) < WIDTH) && q.board[i][j+2] == ' '){
                    q.board[i][j+2] = 'b';
                    q.board[i][j+1] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
                if (((j+2) < WIDTH) && q.board[i][j+2] == '.'){
                    q.board[i][j+2] = 'B';
                    q.board[i][j+1] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

    return false;
}

bool south (puzzle q, puzzle werker, vector <Candidate>& l, int p){
    int i = 0;
    int j = 0;
    q = werker;

    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            if (werker.board[i][j] == 'w'){
                q.board[i][j] = werker.board[i][j];
            }
        }
    }
            if (q.board[i][j] == 'w' && ((i+1) < HEIGHT) && q.board[i+1][j] == (' ' || '.')){
                if (q.board[i+1][j] == '.'){
                    q.board[i+1][j] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }

                else if (q.board[i+1][j] == ' '){
                    q.board[i+1][j] = 'w';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

            else if (q.board[i][j] == 'w' && ((i+2) < HEIGHT) && q.board[i+1][j] == 'b'){
                if (((i+2) < HEIGHT) && q.board[i+2][j] == ' '){
                    q.board[i+2][j] = 'b';
                    q.board[i+1][j] = 'w';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
                if (((i+2) < HEIGHT) && q.board[i+2][j] == '.'){
                    q.board[i+2][j] = 'b';
                    q.board[i+1][j] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

            else if (q.board[i][j] == 'w' && ((i+2) < HEIGHT) && q.board[i+1][j] == 'B'){
                if (((i+2) < HEIGHT) && q.board[i+2][j] == ' '){
                    q.board[i+2][j] = 'b';
                    q.board[i+1][j] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
                if (((i+2) < HEIGHT) && q.board[i+2][j] == '.'){
                    q.board[i+2][j] = 'B';
                    q.board[i+1][j] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

    return false;
}

bool west (puzzle q, puzzle werker, vector <Candidate>& l, int p){
    int i = 0;
    int j = 0;
    q = werker;

    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            if (werker.board[i][j] == 'w'){
                q.board[i][j] = werker.board[i][j];
            }
        }
    }

            if (q.board[i][j] == 'w' && ((j-1) > 0) && q.board[i][j-1] == (' ' || '.')){
                if (q.board[i][j-1] == '.'){
                    q.board[i][j-1] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }

                else if (q.board[i][j-1] == ' '){
                    q.board[i][j-1] = 'w';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

            else if (q.board[i][j] == 'w' && ((j-2) > 0) && q.board[i][j-1] == 'b'){
                if (((j-1) > 0) && q.board[i][j-2] == ' '){
                    q.board[i][j-2] = 'b';
                    q.board[i][j-1] = 'w';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
                if (((j-2) > 0) && q.board[i][j-2] == '.'){
                    q.board[i][j-2] = 'b';
                    q.board[i][j-1] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

            else if (q.board[i][j] == 'w' && ((j-2) > 0) && q.board[i][j-1] == 'B'){
                if (((j-2) > 0) && q.board[i][j-2] == ' '){
                    q.board[i][j-2] = 'b';
                    q.board[i][j-1] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
                if (((j-2) > 0) && q.board[i][j-2] == '.'){
                    q.board[i][j-2] = 'B';
                    q.board[i][j-1] = 'W';
                    q.board[i][j] = ' ';
                    l.push_back({q, p});
                    return true;
                }
            }

    return false;
}

void show_path (vector <Candidate> c, int i){
    for (int x = 0; x < c.size(); x++){
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){
                cout << c[x].Candidate.board[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

}

void solve (puzzle start_puzzle){
    vector <Candidate> c = {{start_puzzle, -1}};
    puzzle werker;
    int p = 0;
    int i = 0;

    while (i < c.size() && !puzzle_ready (c[i].Candidate)){
        puzzle l = c[i].Candidate;
        if (north(werker, l, c, p));
        if (east(werker, l, c, p));
        if (south(werker, l, c, p));
        if (west(werker, l, c, p));
        i++;
    }

    if (i < c.size())
        show_path (c, i);
}

puzzle recursive (vector <puzzle>& attempt, vector <puzzle>& shortest, int MAX_DEPTH){
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    puzzle p = attempt[CURRENT-1];
    int INDEX;

    if (shortest.size() > 0 && attempt.size() >= shortest.size()){
        return shortest[INDEX];
    }

    if (attempt.size() > MAX_DEPTH+1){
        return shortest[INDEX];
    }

    if (puzzle_ready(attempt[INDEX])){
        shortest = attempt;
        return shortest[INDEX];
    }

    else if (puzzle_ready(p)){
        if (north(attempt.back(), recursive(attempt, shortest, MAX_DEPTH), candidate, MAX_DEPTH));
        if (east(attempt.back(), recursive(attempt, shortest, MAX_DEPTH), candidate, MAX_DEPTH));
        if (south(attempt.back(), recursive(attempt, shortest, MAX_DEPTH), candidate, MAX_DEPTH));
        if (west(attempt.back(), recursive(attempt, shortest, MAX_DEPTH), candidate, MAX_DEPTH));
        INDEX++;
    }
}

int main() {
    puzzle start_puzzle = {Puzzle};
    solve(start_puzzle);
    return 0;
}

