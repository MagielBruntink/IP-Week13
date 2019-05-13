/*
                         
                          
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

enum CellValue {WALL = '*', EMPTY = ' ', EMPTY_DEST = '.', WORKER = 'w', WORKER_DEST = 'w', BOX = 'b', BOX_DEST = 'B'};
enum Direction {UP, DOWN, LEFT, RIGHT};

struct Cell {
    CellValue value;
};

struct Coordinate {
    int row;
    int column;
};

struct Candidate {
    vector<vector<Cell>> cells;
    int depth;
    int nodenum;
    string parent;
};

struct Solution {
    Candidate solution;
    vector<Candidate> path;
};

typedef vector<vector<Cell>> Puzzle;

Puzzle puzzle;

ostream& operator<<(ostream& stream, Cell& cell) {
    stream << static_cast<char>(cell.value);
}

void printPuzzle(Puzzle& pz) {
    //             
    assert(true);
    //              
    //                                                           

    for (int i = 0; i < pz.size(); i++) {
        vector<Cell> row = pz[i];
        for (int j = 0; j < row.size(); j++) {
            cout << row[j];
        }
        cout << endl;
    }
}

bool cellAvailable(Cell cell) {
    //             
    assert(true);
    //              
    //                                                    
    return cell.value == EMPTY || cell.value == EMPTY_DEST;
}

bool cellIsDestination (Cell cell) {
    //             
    assert(true);
    //              
    //                                                         
    return cell.value == EMPTY_DEST;
}

bool boxAtCell(Cell cell) {
    //             
    assert(true);
    //              
    //                                          
    return cell.value == BOX;
}

bool boxPushable(int col, int row, Puzzle state, Direction direction) {
    //             
    assert(col >= 0 && row >= 0 && row < state.size() && col < state[row].size());
    //              
    //                                                                                                                
    switch (direction) {
        case LEFT:
            return !boxAtCell(state[row][col-1]) && cellAvailable(state[row][col-1]);
        case RIGHT:
            return !boxAtCell(state[row][col+1]) && cellAvailable(state[row][col+1]);
        case UP:
            return !boxAtCell(state[row-1][col]) && cellAvailable(state[row-1][col]);
        case DOWN:
            return !boxAtCell(state[row+1][col]) && cellAvailable(state[row+1][col]);
    }
    return false;
}

Coordinate findWorker(Puzzle &state) {
    //             
    assert(true);
    //              
    //                                                          
    for (int i = 0; i < state.size(); i++) {
        vector<Cell> row = state[i];
        for (int j = 0; j < row.size(); j++) {
            if (row[j].value == WORKER || row[j].value == WORKER_DEST) {
                return {i, j};
            }
        }
    }
}

Puzzle moveItem(Puzzle oldstate, Cell newcell, CellValue newvalue, Coordinate from, Coordinate to) {
    //              
    assert(from.row >= 0 && from.column >= 0 && to.row >= 0 && to.column >= 0 && from.row < oldstate.size() && to.row < oldstate.size() && from.column < oldstate[from.row].size() && to.column < oldstate[to.row].size());
    //              
    //                                                                                                                                   
    //                                                                
    Puzzle newstate = oldstate;
    if (cellIsDestination(newcell)) {
        newvalue = static_cast<CellValue>(toupper(static_cast<int>(newvalue)));
        newstate[to.row][to.column].value = newvalue;
    } else {
        newstate[to.row][to.column].value = newvalue;
    }
    Cell oldcell = newstate[from.row][from.column];
    if (cellIsDestination(oldcell)) {
        newstate[from.row][from.column].value = EMPTY_DEST;
    } else {
        newstate[from.row][from.column].value = EMPTY;
    }
    return newstate;
}

vector<Puzzle> findMoves(Puzzle &state, Coordinate worker) {
    //             
    assert(worker.column >= 0 && worker.row >= 0 && worker.row < state.size() && worker.column < state[worker.row].size());
    //              
    //                                                                                                    
    int col = worker.column;
    int row = worker.row;
    Cell oldcell = state[row][col];
    Coordinate wfrom = {row, col};
    vector<Puzzle> result;
    //                                                                                        
    Cell cell = state[row][col-1];

    if (cellAvailable(cell)) {
        result.push_back(moveItem(state, cell, WORKER, wfrom, {row,col-1}));
    } else if (boxAtCell(cell) && boxPushable(col-1,row,state,LEFT)) {
        Cell newcell = state[row][col-2];
        Puzzle movedbox = moveItem(state, newcell, BOX, {row,col-1}, {row,col-2});
        result.push_back(moveItem(movedbox, cell, WORKER, wfrom, {row,col-1}));
    }

    cell = state[row][col+1];
    if (cellAvailable(cell)) {
        result.push_back(moveItem(state, cell, WORKER, wfrom, {row,col+1}));
    } else if (boxAtCell(cell) && boxPushable(col+1,row,state,RIGHT)) {
        Cell newcell = state[row][col+1];
        Puzzle movedbox = moveItem(state, newcell, BOX, {row,col+1}, {row,col+2});
        result.push_back(moveItem(movedbox, cell, WORKER, wfrom, {row,col+1}));
    }

    cell = state[row-1][col];
    if (cellAvailable(cell)) {
        result.push_back(moveItem(state, cell, WORKER, wfrom, {row-1,col}));
    } else if (boxAtCell(cell) && boxPushable(col,row-1,state, DOWN)) {
        Cell newcell = state[row-2][col];
        Puzzle movedbox = moveItem(state, newcell, BOX, {row-1,col}, {row-2,col});
        result.push_back(moveItem(movedbox, cell, WORKER, wfrom, {row-1,col}));
    }

    cell = state[row+1][col];
    if (cellAvailable(cell)) {
        result.push_back(moveItem(state, cell, WORKER, wfrom, {row+1,col}));
    } else if (boxAtCell(cell) && boxPushable(col,row+1,state,UP)) {
        Cell newcell = state[row+2][col];
        Puzzle movedbox = moveItem(state, newcell, BOX, {row+1, col}, {row+2, col});
        result.push_back(moveItem(movedbox, cell, WORKER, wfrom, {row+1, col}));
    }

    return result;
}

bool isSolution(vector<vector<Cell>> state) {
    //             
    assert(true);
    //              
    //                                                                                                                       
    for (int i = 0; i < state.size(); i++) {
        vector<Cell> row = state[i];
        for (int j = 0; j < row.size(); j++) {
            if (row[j].value == BOX) {
                return false;
            }
        }
    }
    return true;
}

bool nodeExplored(Candidate node, vector<Candidate> &explored) {
    //             
    assert(true);
    //              
    //                                                  
    for (int i = 0; i < explored.size(); i++) {
        if (explored[i].nodenum == node.nodenum && explored[i].depth == node.depth) {
            return true;
        }
    }
    return false;
}

Solution solve_breadth_first(Puzzle state) {
    //             
    assert(true);
    //              
    //                                                             
    vector<Candidate> frontier;
    frontier.push_back({state, 0, 0, ""});
    vector<Candidate> explored;
    while (!frontier.empty()) {
        Candidate current = frontier[0];
        frontier.erase(frontier.begin());
        if (isSolution(current.cells)) {
            return {current, explored};
        } else {
            if (!nodeExplored(current, explored)) {
                explored.push_back(current);
                Coordinate worker = findWorker(current.cells);
                vector<Puzzle> moves = findMoves(current.cells, worker);
                for (int i = 0; i < moves.size(); i++) {
                    Candidate candidate = {};
                    candidate.cells = moves[i];
                    printPuzzle(candidate.cells);
                    candidate.depth = current.depth + 1;
                    candidate.nodenum = i + 1;
                    candidate.parent = to_string(current.depth) + to_string(current.nodenum);
                    frontier.push_back(candidate);
                }
            }
        }
    }
    return {{state, 0, 0, ""}, explored};
}

void solve_depth_first(vector<Candidate>& explored, vector<Candidate>& frontier, Candidate& shortest, int depthbound) {
    //             
    assert(depthbound > 0);
    //              
    //                                                         
    if (frontier.empty()) {
        return;
    }
    Candidate current = frontier[0];
    frontier.erase(frontier.begin());
    if (current.depth > depthbound) {
        solve_depth_first(explored, frontier, shortest, depthbound);
    }
    if (shortest.depth > 0 && current.depth >= shortest.depth) {
        return;
    }
    if (isSolution(current.cells)) {
        shortest = current;
        return;
    }
    if (!nodeExplored(current, explored)) {
        explored.push_back(current);
        Coordinate worker = findWorker(current.cells);
        vector<Puzzle> moves = findMoves(current.cells, worker);
        for (int i = 0; i < moves.size(); i++) {
            Candidate candidate = {};
            candidate.cells = moves[i];
            printPuzzle(candidate.cells);
            candidate.depth = current.depth + 1;
            candidate.nodenum = i + 1;
            candidate.parent = to_string(current.depth) + to_string(current.nodenum);
            frontier.insert(frontier.begin(), candidate);
        }
        printPuzzle(current.cells);
        solve_depth_first(explored, frontier, shortest, depthbound);
    }
}

int main() {
    cout << "Enter filename for challenge:";
    string path;
    cin >> path;
    ifstream challenge = ifstream(path.c_str());
    if (challenge.is_open()) {
        string line;
        while (getline(challenge, line)) {
            vector<Cell> row;
            for (int i = 0; i < line.length(); i++) {
                Cell c = {static_cast<CellValue>(line[i])};
                row.push_back(c);
            }
            puzzle.push_back(row);
        }
        printPuzzle(puzzle);
//                                             
//
//                                                   
//                                          
//                                        

        vector<Candidate> explored;
        vector<Candidate> frontier;
        frontier.push_back({puzzle, 0, 0, ""});
        Candidate shortest = frontier[0];
        int depthbound = 10;
        solve_depth_first(explored, frontier, shortest, depthbound);
        cout << "Solution found:" << endl;
        printPuzzle(shortest.cells);
    } else {
        cout << "not opened!";
        return 0;
    }
}
