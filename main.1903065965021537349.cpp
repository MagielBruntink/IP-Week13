//                      
//                     

#define NDEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

/*                         
                          

                                             

                
             
  

              
                    
  

                                                                                     
                                  
                                       
     
                                          
         
                   
                          
                      
                     
             
                                                    
                                                           
                                                      
                                                   
             
         
                 
     
 */

typedef vector<vector<char>> field;

field zero = {{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
              {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
              {'*', 'B', ' ', ' ', ' ', ' ', ' ', ' ', 'W', '*'},
              {'*', ' ', ' ', '*', '*', '*', '*', ' ', ' ', '*'},
              {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
              {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}};

field oneA = {{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
              {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
              {'*', ' ', '.', 'b', 'w', ' ', ' ', ' ', ' ', '*'},
              {'*', ' ', ' ', '*', '*', '*', '*', ' ', ' ', '*'},
              {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
              {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}};

field oneB = {{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
              {'*', ' ', 'w', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
              {'*', ' ', 'b', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
              {'*', ' ', '.', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
              {'*', ' ', '*', '*', '*', '*', '*', ' ', ' ', '*'},
              {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
              {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}};

field TwentyThree = {{'*', '*', '*', '*', '*', '*', '*'},
                    {'*', 'w', ' ', ' ', ' ', ' ', '*'},
                    {'*', ' ', 'b', 'b', ' ', ' ', '*'},
                    {'*', ' ', '*', '.', ' ', '.', '*'},
                    {'*', ' ', ' ', ' ', ' ', ' ', '*'},
                    {'*', '*', '*', '*', '*', '*', '*'}};

field TwentyFive = {{'*', '*', '*', '*', '*', '*', '*'},
                    {'*', '*', 'w', ' ', ' ', '*', '*'},
                    {'*', ' ', ' ', '*', ' ', ' ', '*'},
                    {'*', ' ', 'b', 'B', 'b', ' ', '*'},
                    {'*', ' ', ' ', '.', ' ', ' ', '*'},
                    {'*', '*', ' ', '.', ' ', '*', '*'},
                    {'*', '*', '*', '*', '*', '*', '*'}};

field ThirtyOne ={    {'*', '*', '*', '*', '*', '*', '*'},
                      {'*', '*', '*', ' ', ' ', '*', '*'},
                      {'*', 'w', ' ', '.', 'b', '*', '*'},
                      {'*', ' ', ' ', ' ', 'b', ' ', '*'},
                      {'*', ' ', '*', '.', ' ', ' ', '*'},
                      {'*', ' ', ' ', ' ', ' ', ' ', '*'},
                      {'*', '*', '*', '*', '*', '*', '*'}
                      };

field ThirtyFour =  {  {'*', '*', '*', '*', '*', '*', '*', '*'},
                       {'*', '*', '*', ' ', ' ', ' ', '*', '*'},
                       {'*', '.', 'w', 'b', ' ', ' ', '*', '*'},
                       {'*', '*', '*', ' ', 'b', '.', '*', '*'},
                       {'*', '.', '*', '*', 'b', ' ', '*', '*'},
                       {'*', ' ', '*', ' ', '.', ' ', '*', '*'},
                       {'*', 'b', ' ', 'B', 'b', 'b', '.', '*'},
                       {'*', ' ', ' ', ' ', '.', ' ', ' ', '*'},
                       {'*', '*', '*', '*', '*', '*', '*', '*'}};

void PrintVector(field e)
{
    assert(true);
    //                 
    for(int i = 0; i < e.size(); i++)
    {
        for(int j = 0; j < e[i].size(); j++)
        {
            cout << e[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

enum Cell {wall, empty_cell, destination, worker, box};

struct Pos {
    int col, row;
};

struct Puzzle {
    field board;
    Pos worker;
    Pos box;
    Pos destination;
};

struct Candidate {
    Puzzle candidate;
    int parent_candidate;
};

bool can_go_north(Puzzle p) {
    assert (true);
    //                                                            
    if (p.board[p.worker.row- 1][p.worker.col] == '*' ||
        ((p.board[p.box.row - 2][p.box.col] == '*' || p.board[p.box.row - 2][p.box.col] == 'b' ||
          p.board[p.box.row - 2][p.box.col] == 'B') && p.board[p.box.row - 1][p.box.col] == 'b')) {
        return false;
    }
    else {
        return true;
         }
}

bool can_go_south(Puzzle p) {
    assert (true);
    //                                                                               
    if (p.board[p.worker.row + 1][p.worker.col] == '*' ||
        ((p.board[p.box.row + 2][p.box.col] == '*' || p.board[p.box.row + 2][p.box.col] == 'b' ||
          p.board[p.box.row + 2][p.box.col] == 'B') && p.board[p.box.row + 1][p.box.col] == 'b')) {
        return false;
    }
    else {
        return true;
    }
}

bool can_go_east(Puzzle p) {
    assert (true);
    //                                                                              
    if (p.board[p.worker.row][p.worker.col + 1] == '*' ||
        ((p.board[p.box.row][p.box.col + 2] == '*' || p.board[p.box.row][p.box.col + 2] == 'b' ||
          p.board[p.box.row][p.box.col + 2] == 'B') && p.board[p.box.row][p.box.col + 1] == 'b')) {
        return false;
    }
    else {
        return true;
    }
}

bool can_go_west(Puzzle p) {
    assert (true);
    //                                                                              
    if (p.board[p.worker.row][p.worker.col - 1] == '*' ||
        ((p.board[p.box.row][p.box.col - 2] == '*' || p.board[p.box.row][p.box.col - 2] == 'b' ||
          p.board[p.box.row][p.box.col - 2] == 'B') && p.board[p.box.row][p.box.col - 1] == 'b')) {
        return false;
    }
    else {
        return true;
    }
}

Puzzle move_worker (Puzzle p, string next) {
    assert (can_go_north(Puzzle p) || can_go_south(Puzzle p) || can_go_west(Puzzle p) || can_go_east(Puzzle p));
    //                                                 
    if (p.board[p.worker.row][p.worker.col] == 'W') {
        p.board[p.worker.row][p.worker.col] = '.';
    }
    else {
        p.board[p.worker.row][p.worker.col] = ' ';
    }
    if (next == "north"){
        p.worker = {p.worker.col, p.worker.row - 1};
        if (p.worker.col == p.box.col && p.worker.row == p.box.row) {
            if (p.board[p.box.row][p.box.col] == 'B') {
                p.board[p.box.row][p.box.col] = '.';
            }
            p.box = {p.box.col, p.box.row - 1};
            if (p.board[p.box.row][p.box.col] == '.') {
                p.board[p.box.row][p.box.col] = 'B';
            }
        }
    }
    else if (next == "south"){
        p.worker = {p.worker.col, p.worker.row + 1};
        if (p.worker.col == p.box.col && p.worker.row == p.box.row) {
            if (p.board[p.box.row][p.box.col] == 'B') {
                p.board[p.box.row][p.box.col] = '.';
            }
            cout << "heylya";
            p.box = {p.box.col, p.box.row + 1};
            if (p.board[p.box.row][p.box.col] == '.') {
                p.board[p.box.row][p.box.col] = 'B';
            }
            else {
                p.board[p.box.row][p.box.col] = 'b';
            }
        }
    }
    else if (next == "east"){
        p.worker = {p.worker.col - 1, p.worker.row};
        if (p.worker.col == p.box.col && p.worker.row == p.box.row) {
            if (p.board[p.box.row][p.box.col] == 'B') {
                p.board[p.box.row][p.box.col] = 'W';
            }
            p.box = {p.box.col - 1, p.box.row};
            if (p.board[p.box.row][p.box.col] == '.') {
                p.board[p.box.row][p.box.col] = 'B';
            }
        }
    }
    else if (next == "west"){
        p.worker = {p.worker.col + 1, p.worker.row};
        if (p.worker.col == p.box.col && p.worker.row == p.box.row) {
            if (p.board[p.box.row][p.box.col] == 'B') {
                p.board[p.box.row][p.box.col] = '.';
            }
            p.box = {p.box.col + 1, p.box.row};
            if (p.board[p.box.row][p.box.col] == '.') {
                p.board[p.box.row][p.box.col] = 'B';
            }
        }
    }
    if (p.board[p.worker.row][p.worker.col] == '.') {
        p.board[p.box.row][p.box.col] = 'W';
    }
    else {
        p.board[p.worker.row][p.worker.col] = 'w';
    }
    cout << "test2 " << endl;
    PrintVector(p.board);
    return p;
}

void tries (vector<Candidate>& c, int i, string next){
    assert (i => 0 && (next == "north" || next == "south" || next == "west" || next == "east"));
    //                                                                           
    Puzzle p = c[i].candidate;
    Puzzle newp = move_worker(p, next);
    cout << "test5 ";
    Candidate newc = {newp, i};
    c.push_back(newc);
}

int size(vector<Candidate>& c){
    assert (true);
    //                                             
    return static_cast<int> (c.size());
}

bool puzzle_ready(Puzzle p) {
    assert(true);
    //                                                      
    for (int k = 0; k < p.board.size(); k++) {
        for (int l = 0; l < p.board[k].size(); l++) {
            if (p.board[k][l] == 'b'){
                cout << "test3 ";
                return false;
            }
        }
    }
    return true;
}

void solve (Puzzle start) {
    assert (start.worker.row => 0 && start.worker.row =< start.board.size() &&
            start.worker.col => 0 && start.worker.col =< start.board.size() &&
            start.box.row => 0 && start.box.row =< start.board.size() &&
            start.box.col => 0 && start.box.col =< start.board.size() &&
            start.destination.row => 0 && start.destination.row =< start.board.size() &&
            start.destination.col => 0 && start.destination.col =< start.board.size());
    //                                                                   
    int i = 0;
    vector<Candidate> c = {{start, -1}};

    while (i < c.size() && !puzzle_ready(c[i].candidate)) {
        Puzzle p = c[i].candidate;
        cout << "test1 ";
        if (can_go_north(p)) tries(c, i, "north");
        if (can_go_south(p)) tries(c, i, "south");
        if (can_go_west(p)) tries(c, i, "west");
        if (can_go_east(p)) tries(c, i, "east");
        cout << "test4 " << endl;
        i++;

    }
    cout << "solution:\n";
    int itteration=0;
    while (i != -1){
        PrintVector(c[i].candidate.board);
        i = c[i].parent_candidate;
        itteration++;
    }
    cout<< itteration-1;
}
/*                                                                      
                                                                                                
                        
                                       
                               
 

                                                                             
 
                                       
                                     
                                  
                                 
     
              
     
                                  
     
                       
     
                            
     
                           
              
     
                                                                    
                                                                    
                                                                  
                                                                  
 
*/
int main(){
    PrintVector(oneB);
    Puzzle b {oneB, {2, 1}, {2, 2}, {2, 3}};
    solve (b);
    return 0;
}

