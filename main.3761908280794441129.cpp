#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

/*
                         
                  

                     
                  
*/

using namespace std;

enum CellType {Wall, Empty, EmptyDest, WorkerEmpty, WorkerDest, BoxEmpty, BoxDest};
enum Direction {North, South, West, East};
struct Cell {
    CellType type;
    int row;
    int col;
    char val;
};
const int MAX_ROWS = 10;
const int MAX_COLS = 20;
struct Puzzle {
    Cell board[MAX_ROWS][MAX_COLS];
};
struct Candidate {
    Puzzle candidate;
    int parent_candidate;
};
Puzzle puzzle;

int size(vector<Candidate>& c) {
    //               
    assert(true);
    //                
    //                                                
    return static_cast<int>(c.size());
}

int size(vector<Puzzle>& p) {
    //               
    assert(true);
    //                
    //                                             
    return static_cast<int>(p.size());
}

void enter_chall(string& chall_name, int& rows, int& cols) {
    //               
    assert(true);
    //                
    //                                                     
    cout << "Please specify a challenge file: ";
    getline(cin, chall_name);
    cout << "Please specify the number of rows: ";
    cin >> rows;
    cout << "Please specify the number columns: ";
    cin >> cols;
}

bool open_chall(ifstream& chall_file, string chall_name) {
    //               
    assert(true);
    //                
    //                                                                           
    chall_file.open(chall_name.c_str());
    return chall_file.is_open();
}

CellType cell_type(char c) {
    //               
    assert(true);
    //                
    //                                                     
    if(c == '*') return Wall;
    if(c == ' ') return Empty;
    if(c == '.') return EmptyDest;
    if(c == 'w') return WorkerEmpty;
    if(c == 'W') return WorkerDest;
    if(c == 'b') return BoxEmpty;
    if(c == 'B') return BoxDest;
}

void read_chall(ifstream& chall_file, Cell board[MAX_ROWS][MAX_COLS], const int rows, const int cols) {
    //               
    assert(rows > 0 && rows < MAX_ROWS && cols > 0 && cols < MAX_COLS);
    //                
    //                                                         
    //                                                                         
    Cell cell;
    char c = ' ';
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            chall_file.get(c);
            cell.type = cell_type(c);
            cell.row = row;
            cell.col = col;
            cell.val = c;
            board[row][col] = cell;
        }
        chall_file.get(c);
    }
}

void display_chall(Cell board[MAX_ROWS][MAX_COLS], const int rows, const int cols) {
    //               
    assert(rows > 0 && rows < MAX_ROWS && cols > 0 && cols < MAX_COLS);
    //                
    //                                          
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) cout << board[row][col].val;
        cout << endl;
    }
}

int north(Cell c) {
    //               
    assert(true);
    //                
    //                                             
    return c.row-1;
}

int south(Cell c) {
    //               
    assert(true);
    //                
    //                                             
    return c.row+1;
}

int west(Cell c) {
    //               
    assert(true);
    //                
    //                                               
    return c.col-1;
}

int east(Cell c) {
    //               
    assert(true);
    //                
    //                                               
    return c.col+1;
}

Puzzle copy_puzzle(Puzzle original, const int rows, const int cols) {
    //                
    assert(rows > 0 && rows < MAX_ROWS && cols > 0 && cols < MAX_COLS);
    //                
    //                                            
    Puzzle new_puzzle;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            new_puzzle.board[row][col] = original.board[row][col];
        }
    }
    return new_puzzle;
}

bool can_go_direction(Cell board[MAX_ROWS][MAX_COLS], Cell worker, Direction direction, const int rows, const int cols) {
    //               
    assert(worker.row >= 0 && worker.row < MAX_ROWS && worker.col >= 0 && worker.col < MAX_COLS);
    //                
    //                                                             
    if(direction == North) {
            if(north(worker) > 0) return board[north(worker)][worker.col].type == Empty || board[north(worker)][worker.col].type == EmptyDest;
            else return false;
    }
    else if(direction == South) {
            if(south(worker) < rows) return board[south(worker)][worker.col].type == Empty || board[south(worker)][worker.col].type == EmptyDest;
            else return false;
    }
    else if(direction == West) {
            if(west(worker) > 0) return board[worker.row][west(worker)].type == Empty || board[worker.row][west(worker)].type == EmptyDest;
            else return false;
    }
    else if(direction == East) {
            if(east(worker) < cols) return board[worker.row][east(worker)].type == Empty || board[worker.row][east(worker)].type == EmptyDest;
            else return false;
    }
}

bool puzzle_ready(Puzzle puzzle, const int rows, const int cols) {
    //               
    assert(rows > 0 && rows < MAX_ROWS && cols > 0 && cols < MAX_COLS);
    //                
    //                                                        
    for(int row = 0; row < rows; row++)
        for(int col = 0; col < cols; col++)
            if(puzzle.board[row][col].type == BoxEmpty) return false;
    return true;
}

Cell find_worker(Puzzle puzzle, const int rows, const int cols) {
    //               
    assert(rows > 0 && rows < MAX_COLS && cols > 0 && cols < MAX_COLS);
    //                
    //                                             
    Cell worker;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(puzzle.board[row][col].type == WorkerEmpty || puzzle.board[row][col].type == WorkerDest) {
                worker.row = row;
                worker.col = col;
                worker.type = puzzle.board[row][col].type;
                return worker;
            }
        }
    }
}

bool in_front_of_wall(Puzzle puzzle, Cell c, Direction direction, const int rows, const int cols) {
    //               
    assert(rows > 0 && rows < MAX_ROWS && cols > 0 && cols < MAX_COLS);
    //                
    //                                                             
    if(c.row-1 > 0 && direction == North) return puzzle.board[north(c)][c.col].type == Wall;
    if(c.row+1 < rows && direction == South) return puzzle.board[south(c)][c.col].type == Wall;
    if(c.col-1 > 0 && direction == West) return puzzle.board[c.row][west(c)].type == Wall;
    if(c.col+1 < cols && direction == East) return puzzle.board[c.row][east(c)].type == Wall;
    else if (c.row-1 == 0) return true;
}

Puzzle move_empty(Puzzle p, Cell worker, Direction next, const int rows, const int cols) {
    //               
    assert(worker.row > 0 && worker.row < MAX_ROWS && worker.col > 0 && worker.col < MAX_COLS);
    //                
    //                                                      
    if(in_front_of_wall(puzzle,worker,next,rows,cols)) return p;
    if(p.board[worker.row][worker.col].type == WorkerDest) {
        p.board[worker.row][worker.col].val = '.';
        p.board[worker.row][worker.col].type = EmptyDest;
    }
    if(p.board[worker.row][worker.col].type == WorkerEmpty) {
        p.board[worker.row][worker.col].val = ' ';
        p.board[worker.row][worker.col].type = Empty;
    }
    if(next == North && p.board[north(worker)][worker.col].type == Empty) {
        p.board[north(worker)][worker.col].type = WorkerEmpty;
        p.board[north(worker)][worker.col].val = 'w';
    }
    else if(next == North && p.board[north(worker)][worker.col].type == EmptyDest) {
        p.board[north(worker)][worker.col].type = WorkerDest;
        p.board[north(worker)][worker.col].val = 'W';
    }
    if(next == South && p.board[south(worker)][worker.col].type == Empty) {
        p.board[south(worker)][worker.col].type = WorkerEmpty;
        p.board[south(worker)][worker.col].val = 'w';
    }
    else if(next == South && p.board[south(worker)][worker.col].type == EmptyDest) {
        p.board[south(worker)][worker.col].type = WorkerDest;
        p.board[south(worker)][worker.col].val = 'W';
    }
    if(next == West && p.board[worker.row][west(worker)].type == Empty) {
        p.board[worker.row][west(worker)].type = WorkerEmpty;
        p.board[worker.col][west(worker)].val = 'w';
    }
    else if(next == West && p.board[worker.row][west(worker)].type == EmptyDest) {
        p.board[worker.row][west(worker)].type = WorkerDest;
        p.board[worker.col][west(worker)].val = 'W';
    }
    if(next == East && p.board[worker.row][east(worker)].type == Empty) {
        p.board[worker.row][east(worker)].type = WorkerEmpty;
        p.board[worker.col][east(worker)].val = 'w';
    }
    else if(next == East && p.board[worker.row][east(worker)].type == EmptyDest) {
        p.board[worker.row][east(worker)].type = WorkerDest;
        p.board[worker.col][east(worker)].val = 'W';
    }
    return p;
}

void show_path(vector<Candidate>& c, int i, const int rows, const int cols) {
    //               
    assert(i >= 0 && i < size(c));
    //                
    //                                     
    display_chall(c[i].candidate.board, rows, cols);
}

bool puzzle_present_bfs(vector<Candidate>& c, int i, Puzzle newp) {
    for(int i = 0; i < size(c); i++) if(c[i].candidate.board == newp.board) return true;
    return false;
}

void tries_bfs(vector<Candidate>& c, int i, Cell worker, Direction next, const int rows, const int cols) {
    //               
    assert(i >= 0 && i < size(c));
    //                
    //                                             
    Puzzle p = c[i].candidate;
    Puzzle newp = move_empty(p, worker, next, rows, cols);
    Candidate newc = {newp, i};
    if(!puzzle_present_bfs(c,i,newp)) c.push_back(newc);
}

bool puzzle_present_dfs(Puzzle puzzle, vector<Puzzle>& attempt) {
    //               
    assert(true);
    //                
    //                                                  
    for(int i = 0; i < size(attempt); i++)
        if(attempt[i].board == puzzle.board) return true;
    return false;
}

bool in_front_of_box(Puzzle puzzle, Cell c, Direction direction, const int rows, const int cols) {
    //               
    assert(rows > 0 && rows < MAX_ROWS && cols > 0 && cols < MAX_COLS);
    //                
    //                                                                                                         
    if(c.row-1 > 0 && direction == North) {
        if(puzzle.board[north(c)][c.col].type == BoxEmpty || puzzle.board[north(c)][c.col].type == BoxDest) return true;
    }
    if(c.row+1 < rows && direction == South) {
        if(puzzle.board[south(c)][c.col].type == BoxEmpty || puzzle.board[south(c)][c.col].type == BoxDest) return true;
    }
    if(c.col-1 > 0 && direction == West) {
        if(puzzle.board[c.row][west(c)].type == BoxEmpty || puzzle.board[c.row][west(c)].type) return true;
    }
    if(c.col+1 < cols && direction == East) {
        if(puzzle.board[c.row][east(c)].type == BoxEmpty || puzzle.board[c.row][east(c)].type) return true;
    }
    return false;
}

void push_box(Puzzle p, Cell worker, Cell box, vector<Candidate>& c, int i, Direction direction, const int rows, const int cols) {
    //               
    assert(rows > 0 && rows < MAX_ROWS && cols > 0 && cols < MAX_COLS && i >= 0);
    //                
    //                                                                                          
    Puzzle new_puzzle = copy_puzzle(p, rows, cols);
    if(new_puzzle.board[worker.row][worker.col].type == WorkerDest) {
        new_puzzle.board[worker.row][worker.col].val = '.';
        new_puzzle.board[worker.row][worker.col].type = EmptyDest;
    }
    if(new_puzzle.board[worker.row][worker.col].type == WorkerEmpty) {
        new_puzzle.board[worker.row][worker.col].val = ' ';
        new_puzzle.board[worker.row][worker.col].type = Empty;
    }
    if(new_puzzle.board[box.row][box.col].type == BoxDest) {
        new_puzzle.board[box.row][box.col].val = 'W';
        new_puzzle.board[box.row][box.col].type = WorkerDest;
    }
    if(new_puzzle.board[box.row][box.col].type == BoxEmpty) {
        new_puzzle.board[box.row][box.col].val = 'w';
        new_puzzle.board[box.row][box.col].type = WorkerEmpty;
    }
    if(direction == North) {
        box.row -= 1;
        worker.row -= 1;
    }
    if(direction == South) {
        box.row += 1;
        worker.row += 1;
    }
    if(direction == West) {
        box.col -= 1;
        worker.col -= 1;
    }
    if(direction == East) {
        box.col += 1;
        worker.col += 1;
    }
    if(puzzle.board[box.row][box.col].type == EmptyDest) {
        box.type = BoxDest;
        box.val = 'B';
    }
    if(puzzle.board[worker.row][worker.col].type == BoxDest) {
        worker.type = WorkerDest;
        worker.val = 'W';
    }
    if(puzzle.board[worker.row][worker.col].type == BoxEmpty) {
        worker.type = WorkerEmpty;
        worker.val = 'w';
    }
    new_puzzle.board[box.row][box.col] = box;
    new_puzzle.board[worker.row][worker.col] = worker;
    Candidate newc = {new_puzzle,i};
    if(!puzzle_present_bfs(c, i, new_puzzle)) c.push_back(newc);
}

int sokoban_bfs(Puzzle start, const int rows, const int cols) {
    //               
    assert(rows > 0 && rows < MAX_ROWS && cols > 0 && cols < MAX_COLS);
    //                
    //                                                                      
    vector<Candidate> c = {{start,-1}};
    int i = 0;
    Cell worker = find_worker(puzzle, rows, cols);
    while(i < size(c) && !puzzle_ready(c[i].candidate, rows, cols)) {
        Puzzle p = c[i].candidate;
        Cell box;
        if(in_front_of_box(puzzle,worker,North,rows,cols) && !in_front_of_box(p, box, North, rows, cols)) {
            box.row = north(worker);
            box.col = worker.col;
            box.type = p.board[box.row][box.col].type;
            box.val = p.board[box.row][box.col].val;
            if(!in_front_of_wall(p,box,North,rows,cols) && box.type != BoxDest) push_box(p, worker, box, c, i, North, rows, cols);
        }
        if(in_front_of_box(puzzle,worker,South,rows,cols) && !in_front_of_box(p, box, South, rows, cols)) {
            box.row = south(worker);
            box.col = worker.col;
            box.type = p.board[box.row][box.col].type;
            box.val = p.board[box.row][box.col].val;
            if(!in_front_of_wall(p,box,South,rows,cols) && box.type != BoxDest) push_box(p, worker, box, c, i, South, rows, cols);
        }
        if(in_front_of_box(puzzle,worker,West,rows,cols) && !in_front_of_box(p, box, West, rows, cols)) {
            box.row = worker.row;
            box.col = west(worker);
            box.type = p.board[box.row][box.col].type;
            box.val = p.board[box.row][box.col].val;
            if(!in_front_of_wall(p,box,West,rows,cols) && box.type != BoxDest) push_box(p, worker, box, c, i, West, rows, cols);
        }
        if(in_front_of_box(puzzle,worker,East,rows,cols) && !in_front_of_box(p, box, East, rows, cols)) {
            box.row = worker.row;
            box.col = east(worker);
            box.type = p.board[box.row][box.col].type;
            box.val = p.board[box.row][box.col].val;
            if(!in_front_of_wall(p,box,East,rows,cols) && box.type != BoxDest) push_box(p, worker, box, c, i, East, rows, cols);
        }
        if(can_go_direction(p.board, worker, North, rows, cols)) tries_bfs(c, i, worker, North, rows, cols);
        if(can_go_direction(p.board, worker, South, rows, cols)) tries_bfs(c, i, worker, South, rows, cols);
        if(can_go_direction(p.board, worker, West, rows, cols)) tries_bfs(c, i, worker, West, rows, cols);
        if(can_go_direction(p.board, worker, East, rows, cols)) tries_bfs(c, i, worker, East, rows, cols);
        for(int i = 0; i < size(c); i++) {
            for(int j = 0; j < rows; j++) {
                for(int k = 0; k < cols; k++) {
                    cout << c[i].candidate.board[j][k].val;
                }
            cout << endl;
            }
        }
        i++;
    }
    if(i < size(c)) show_path(c, i, rows, cols);
    return i;
}

int sokoban_dfs(vector<Puzzle> attempt, vector<Puzzle>& shortest, int max_depth, const int rows, const int cols);

void tries_dfs(vector<Puzzle>& attempt, Direction next, Cell worker, vector<Puzzle>& shortest, int max_depth, const int rows, const int cols) {
    //               
    assert(max_depth > 0);
    //                
    //                                                               
    Puzzle p = attempt[size(attempt)-1];
    Puzzle newp = move_empty(p, worker, next, rows, cols);
    if(!puzzle_present_dfs(newp, attempt)) {
        attempt.push_back(newp);
        sokoban_dfs(attempt, shortest, max_depth, rows, cols);
        attempt.pop_back();
    }
}

int sokoban_dfs(vector<Puzzle> attempt, vector<Puzzle>& shortest, const int MAX_DEPTH, const int rows, const int cols) {
    //               
    assert(MAX_DEPTH > 0 && rows > 0 && rows < MAX_ROWS && cols > 0 && cols < MAX_COLS);
    //                
    //                                                          
    const int CURRENT = size(attempt);
    const int BEST = size(shortest);
    Puzzle p = attempt[CURRENT-1];
    Cell worker = find_worker(puzzle, rows, cols);
    if(BEST > 0 && CURRENT >= BEST) { return CURRENT; }
    else if (CURRENT > MAX_DEPTH+1) { return CURRENT; }
    else if (puzzle_ready(puzzle, rows, cols)) {shortest = attempt; return BEST; }
    if(can_go_direction(p.board,worker,North,rows,cols)) { tries_dfs(attempt, North, worker, shortest, MAX_DEPTH, rows, cols); return CURRENT; }
    if(can_go_direction(p.board,worker,South,rows,cols)) { tries_dfs(attempt, South, worker, shortest, MAX_DEPTH, rows, cols); return CURRENT; }
    if(can_go_direction(p.board,worker,West,rows,cols)) { tries_dfs(attempt, West, worker, shortest, MAX_DEPTH, rows, cols); return CURRENT; }
    if(can_go_direction(p.board,worker,East,rows,cols)) { tries_dfs(attempt, East, worker, shortest, MAX_DEPTH, rows, cols); return CURRENT; }
}

int main()
{
    ifstream chall_file;
    string chall_name = " ";
    int rows = 0;
    int cols = 0;
    vector<Puzzle> attempt;
    vector<Puzzle> shortest;
    const int MAX_DEPTH = 80;
    enter_chall(chall_name, rows, cols);
    if(open_chall(chall_file, chall_name)) {
            read_chall(chall_file, puzzle.board, rows, cols);
            display_chall(puzzle.board, rows, cols);
            sokoban_bfs(puzzle, rows, cols);
            //                                                      
    }
    else cout << "Failed to read file." << endl;
    return 0;
}

