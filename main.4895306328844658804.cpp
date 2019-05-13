//                          
//                         

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
using namespace std;

const int MAX_PUZZLE_WIDTH = 10;
const int MAX_PUZZLE_HEIGHT = 10;

int current_puzzle_width;
int current_puzzle_height;

enum Direction {
    Up = 0, Right, Down, Left
};

enum CellType {
    Wall = 0, Empty, EmptyDest, Worker, WorkerDest, Box, BoxDest
};

struct State {
    CellType cells[MAX_PUZZLE_WIDTH][MAX_PUZZLE_HEIGHT];
};

struct Candidate{
    State candidate ;
    int parent_candidate ;
} ;

template <typename El>
int size (vector<El>& vec) {
//               
    assert (true) ;
//                                                                
    return static_cast<int> (vec.size());
}

bool check_goal_state (State state){
    //              
    assert(true);
    //               
    //                                                   
    bool foundBox = false;
    for (int y = 0; y < current_puzzle_height && !foundBox; y++) {
        for (int x = 0; x < current_puzzle_width && !foundBox; x++) {
            foundBox = (state.cells[x][y] == 'b');
        }
    }
    return !foundBox;
}

bool fill_state_from_file(string filename, State &state) {
    //              
    assert(true);
    //               
    //                                                                            
    char c;
    int x = 0;
    int y = 0;
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open()) {
        return false;
    }
    while(infile.get(c) && !infile.eof()) {
        switch (c) {

            case '*': state.cells[x][y] = Wall;
                break;
            case ' ': state.cells[x][y] = Empty;
                break;
            case '.': state.cells[x][y] = EmptyDest;
                break;
            case 'w': state.cells[x][y] = Worker;
                break;
            case 'W': state.cells[x][y] = WorkerDest;
                break;
            case 'b': state.cells[x][y] = Box;
                break;
            case 'B': state.cells[x][y] = BoxDest;
                break;
        }
        if (c == '\n') {
            if (current_puzzle_width < x) {
                current_puzzle_width = x;
            }
            x = 0;
            y++;
        } else {
            x++;
        }
    }
    current_puzzle_height = y;
}

void output_state(State &state) {
    //              
    assert(true);
    //               
    //                                 
    for (int y = 0; y < current_puzzle_height; y++) {
        for (int x = 0; x < current_puzzle_width; x++) {
            switch (state.cells[x][y]) {
            case Wall:
                cout << '*';
                break;
            case Empty:
                cout << ' ';
                break;
            case EmptyDest:
                cout << '.';
                break;
            case Worker:
                cout << 'w';
                break;
            case WorkerDest:
                cout << 'W';
                break;
            case Box:
                cout << 'b';
                break;
            case BoxDest:
                cout << 'B';
                break;
            }
        }
        cout << endl;
    }
}

void moveInDirection(int &x, int &y, Direction dir) {
    //              
    assert(true);
    //               
    //                                       
    switch (dir) {
    case Up:
        y -= 1;
        break;
    case Right:
        x += 1;
        break;
    case Down:
        y += 1;
        break;
    case Left:
        x -= 1;
        break;
    }
}

void getWorkerCoordinates(State state, int &x, int &y) {
    //              
    assert(true);
    //               
    //                                     
    bool foundWorker = false;
    for (x = 0; x < current_puzzle_width && !foundWorker; x++) {
        for (y = 0; y < current_puzzle_height && !foundWorker; y++) {
            foundWorker = (state.cells[x][y] == 'w' || state.cells[x][y] == 'W');
        }
    }
    if (!foundWorker) {
        x = -1;
        y = -1;
    }
}

bool puzzle_present(State p, vector<State>& c) {
    //               
    assert (true) ;
    //                                                                           
    for (int x = 0; x < size(c); x++) {
        for (int i = 0; i < MAX_PUZZLE_HEIGHT; i++) {
            for (int j = 0; j < MAX_PUZZLE_WIDTH; j++) {
                if (p.cells[j][i] != c[x].cells[j][i]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool canGoInDirection(State state, Direction dir) {
    //              
    assert(true);
    //               
    //                                                                       
    int px;
    int py;
    getWorkerCoordinates(state, px, py);
    int targetx = px;
    int targety = py;
    moveInDirection(targetx, targety, dir);
    switch(state.cells[targetx][targety]) {
    case Empty:
    case EmptyDest:
        return true;
        break;
    case Wall:
        return false;
        break;
    case Box:
    case BoxDest:
        //                                       
        int boxtargetx = px;
        int boxtargety = py;
        moveInDirection(boxtargetx, boxtargety, dir);
        switch (state.cells[boxtargetx][boxtargety]) {
        case Empty:
        case EmptyDest:
            return true;
            break;
        case Wall:
        case Box:
        case BoxDest:
            return false;
            break;
        }
    }
}

void getNextState(State state, Direction dir) {
    //              
    assert(true);
    //               
    //                                            
    int px;
    int py;
    getWorkerCoordinates(state, px, py);
    int targetx = px;
    int targety = py;
    moveInDirection(targetx, targety, dir);
    State stateCopy = state;
    switch(state.cells[targetx][targety]) {
    case Empty:
        stateCopy[px][py] = ' ';
        stateCopy[targetx][targety] = 'w';
    case EmptyDest:
        stateCopy[px][py] = ' ';
        stateCopy[targetx][targety] = 'W';
        break;
    case Box:
    case BoxDest:
        //                                       

        int boxtargetx = px;
        int boxtargety = py;
        moveInDirection(boxtargetx, boxtargety, dir);
        bool targetIsDest = (state.cells[targetx][targety] == BoxDest);
        switch (state.cells[boxtargetx][boxtargety]) {

        case Empty:
            stateCopy[px][py] = ' ';
            if (targetIsDest) {
                stateCopy[targetx][targety] = 'W';
            } else {
                stateCopy[targetx][targety] = 'w';
            }
            stateCopy[boxtargetx][boxtargety] = 'b';
            break;
        case EmptyDest:
            stateCopy[px][py] = ' '
            if (targetIsDest) {
                stateCopy[targetx][targety] = 'W';
            } else {
                stateCopy[targetx][targety] = 'w';
            }
            stateCopy[boxtargetx][boxtargety] = 'B';
            break;
        }
    }
    if (state[px][py] == 'W') {
        stateCopy[px][py] = '.';
    }
    return stateCopy;
}

void solve_depth(vector<State> &attempt, vector<State> &best){
    if check_goal_state(attempt){
        best = attempt;
    }
    if canGoInDirection(){
        getNextState();
    }
}

void tries_breadth(vector<Candidate>& c, int i, Direction dir) {
    //              
    assert (true) ;
    //                                                                 
    State p = c[i].candidate;
    State newp = getNextState(p,dir);
    Candidate newc = {newp, i};
    //                                
        c.push_back(newc);
    // 
}

void solve_breadth(State start) {
    //              
    assert (true) ;
    //                                                                                                           
    vector<Candidate> c = {{start,-1}};
    int i = 0;
    while (i < size(c) && !check_goal_state(c[i].candidate)) {
        State p = c[i].candidate;
        if (canGoInDirection(p, Up)) {
            tries_breadth(c,i,Up);
        }
        if (canGoInDirection(p, Up)) {
            tries_breadth(c,i,Right);
        }
        if (canGoInDirection(p, Up)) {
            tries_breadth(c,i,Down);
        }
        if (canGoInDirection(p, Up)) {
            tries_breadth(c,i,Left);
        }
        i++;
    }
    if (i < size(c)) {
        output_state(c.candidate);
    }
}

int main()
{
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    cout << endl;
    State state;
    fill_state_from_file(filename, state);
    output_state(state);
    return 0;
}

