#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

//                       
//                     
//                   

struct Pos{
    int x, y;
};

struct Puzzle{
    vector<vector<char> > board;
    Pos worker = {-1, -1}; //                                                           
};

struct Candidate {
    Puzzle puzzle;
    int parent;
};

void read_file(Puzzle& puzzle, string fname) {
    //             
    assert(true);
    //              
    //                                                                    
    ifstream file;
    file.open(fname.c_str());
    string s;
    int line_number = 0;
    while(file){
        getline(file, s);
        if(file){
            vector<char> current_line;
            for(int i = 0; i < s.size(); i++) {
                current_line.push_back(s.at(i));
                if(s.at(i) == 'w' || s.at(i) == 'W') {
                    puzzle.worker = {i, line_number};
                }
            }
            puzzle.board.push_back(current_line);
            line_number++;
        }
    }
}

void print_puzzle(Puzzle& puzzle) {
    //             
    assert(true);
    //              
    //                                                     
    for(int i = 0; i < puzzle.board.size(); i++) {
        for(int j = 0; j < puzzle.board[i].size(); j++) {
            cout << puzzle.board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void tail_recursive_print(vector<Candidate>& log, int index, int& counter){
    //             
    assert(true);
    //              
    //                                                                        
    if (index == -1){
        counter--;
        return;
    }
    else{
        counter++;
        tail_recursive_print(log, log[index].parent, counter);
        print_puzzle(log[index].puzzle);
    }
}

bool solution_found(vector<Candidate>& log, int index){
    //            
    assert(0 <= index && index < log.size());
    //             
    //                                                                   
    for(int i = 0; i < log.at(index).puzzle.board.size(); i++) {
        for(int j = 0; j < log.at(index).puzzle.board.at(i).size(); j++) {
            char c = log.at(index).puzzle.board.at(i).at(j);
            if (c == '.' || c == 'W' || c == 'b') //                                                              
                return false;
        }
    }
    cout << "This is the solution:" << endl;
    //                                
    int steps = 0;
    tail_recursive_print(log, index, steps);
    cout << steps << " steps required" << endl;

    return true;
}

//                       
bool can_move_direction(Puzzle& puzzle, Pos pos){
    //             
    assert(true);
    //              
    //                                                                     
    char new_pos = puzzle.board.at(puzzle.worker.y + pos.y).at(puzzle.worker.x + pos.x);
    char beyond_new_pos;
    if(puzzle.worker.y + 2 * pos.y < 0 || puzzle.worker.y + 2 * pos.y >= puzzle.board.size() || puzzle.worker.x + 2 * pos.x < 0 || puzzle.worker.x + 2 * pos.x >= puzzle.board[0].size()) {
        beyond_new_pos = '*';
    } else {
        beyond_new_pos = puzzle.board.at(puzzle.worker.y + 2 * pos.y).at(puzzle.worker.x + 2 * pos.x);
    }
    //                        
    if(new_pos == '*') {
        return false;
    } else if((beyond_new_pos == '.' || beyond_new_pos == ' ') && (new_pos == 'b' || new_pos == 'B')) {
        return true;
    } else if(new_pos == ' ' || new_pos == '.') {
        return true;
    }
}

bool state_exists(vector<Candidate>& log, Puzzle p) {
    //             
    assert(true);
    //              
    //                                                                              
    for(int i = 0; i < log.size(); i++) {
        if(log[i].puzzle.board == p.board) {
            return true;
        }
    }
    return false;
}

Puzzle make_move(Puzzle p, Pos next){
    //             
    assert(true);
    //              
    //                                                    
    Pos new_pos = {p.worker.y + next.y, p.worker.x + next.x};
    Pos beyond_new_pos = {p.worker.y + 2 * next.y, p.worker.x + 2 * next.x};
    if(p.board[new_pos.x][new_pos.y] == 'b') {
        p.board[new_pos.x][new_pos.y] = 'w';
        if(p.board[beyond_new_pos.x][beyond_new_pos.y] == '.')
            p.board[beyond_new_pos.x][beyond_new_pos.y] = 'B';
        else
            p.board[beyond_new_pos.x][beyond_new_pos.y] = 'b';
    } else if(p.board[new_pos.x][new_pos.y] == 'B') {
        p.board[new_pos.x][new_pos.y] = 'W';
        if(p.board[beyond_new_pos.x][beyond_new_pos.y] == '.')
            p.board[beyond_new_pos.x][beyond_new_pos.y] = 'B';
        else
            p.board[beyond_new_pos.x][beyond_new_pos.y] = 'b';
    } else if(p.board[new_pos.x][new_pos.y] == ' '){
        p.board[new_pos.x][new_pos.y] = 'w';
    }
    else if(p.board[new_pos.x][new_pos.y] == '.'){
        p.board[new_pos.x][new_pos.y] = 'W';
    }
    if (p.board[p.worker.y][p.worker.x] == 'w'){
        p.board[p.worker.y][p.worker.x] = ' ';
    }
    else if (p.board[p.worker.y][p.worker.x] == 'W'){
        p.board[p.worker.y][p.worker.x] = '.';
    }
    p.worker = {new_pos.y, new_pos.x};
    return p;
}

void tries(vector<Candidate>& log, int i, Pos next) {
    //             
    assert(i >= 0 && i < log.size());
    //              
    //                                                           
    Puzzle p = log[i].puzzle;
    Puzzle next_p = make_move(p, next);
    if (!state_exists(log, next_p))
        log.push_back({next_p, i});
}

void breadth_first(Puzzle& start) {
    //             
    assert(true);
    //              
    //                                                                                                  
    vector<Candidate> log = {{start, -1}};
    int i = 0;
    while(i < log.size() && !solution_found(log, i)) {
        Puzzle p = log.at(i).puzzle;
        vector<Pos> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
        for(int j = 0; j < 4; j++){
            if(can_move_direction(p, directions.at(j))){
                tries(log, i, directions.at(j));
            }
        }
        i++;
    }
}

bool puzzle_ready(Puzzle puzzle){
    //             
    assert(true);
    //              
    //                                                                   
    for(int i = 0; i < puzzle.board.size(); i++) {
        for(int j = 0; j < puzzle.board.at(i).size(); j++) {
            char c = puzzle.board.at(i).at(j);
            if (c == '.' || c == 'W' || c == 'b') //                                                              
                return false;
        }
    }
    return true;
}

bool puzzle_present(Puzzle puzzle, vector<Puzzle>& attempt) {
    //             
    assert(true);
    //              
    //                                                       
    for(int i = 0; i < attempt.size(); i++) {
        if(attempt[i].board == puzzle.board) {
            return true;
        }
    }
    return false;
}

void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void depth_tries(vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth) {
    //             
    assert(true);
    //              
    //                                                                                 
    Puzzle p = attempt[attempt.size() - 1];
    Puzzle new_p = make_move(p, next);
    if(!puzzle_present(new_p, attempt)) {
        attempt.push_back(new_p);
        depth_first(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth) {
    //             
    assert(max_depth >= 0);
    //              
    //                                                                         
    Puzzle state = attempt[attempt.size() - 1];
    if(attempt.size() > max_depth) {
        return;
    }
    if(shortest.size() > 0 && attempt.size() >= shortest.size()) {
        return;
    }
    if(puzzle_ready(state)) {
        shortest = attempt;
        return;
    }
    vector<Pos> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    for(int j = 0; j < 4; j++){
        if(can_move_direction(state, directions.at(j))){
            depth_tries(attempt, directions.at(j), shortest, max_depth);
        }
    }
}

int main()
{
    Puzzle puzzle = Puzzle();
    string fname = "challenge.23.txt";
    read_file(puzzle, fname);
    //                      
    vector<Puzzle> attempt = {puzzle};
    vector<Puzzle> shortest;
    int max_depth = 30;
    depth_first(attempt, shortest, max_depth);
    cout << "This is the solution:" << endl;
    for(int j = 0; j < shortest.size(); j++) {
        print_puzzle(shortest[j]);
    }
    cout << shortest.size() - 1 << " steps required" << endl;
    return 0;
}

