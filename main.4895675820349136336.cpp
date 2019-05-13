#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

//                                                                             
//                                                                             
//                                                                              
//                                                                             
//                                                                             

const int WIDTH= 10 ;
const int HEIGHT= 6;
enum legenda {Wall=0, Empty, Box, Person, Goal, Box_ongoal};
typedef int Cell;
struct Pos
{ int row, col ;} ;

struct Puzzle{legenda board [HEIGHT][WIDTH]={{Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall},
                                          {Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall},
                                          {Wall,Empty,Goal,Box,Person,Empty,Empty,Empty,Empty,Wall},
                                          {Wall, Empty, Empty, Wall, Wall, Wall, Wall, Empty, Empty, Wall},
                                          {Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall},
                                          {Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall}};
    Pos worker = {2,4};
} ;

bool can_go_north(Puzzle puzzle)
{
    //              
    assert(true);
    //                                                                                
    if(puzzle.board[puzzle.worker.row-1][puzzle.worker.col]==Empty){
        return true;
    }
    else if(puzzle.board[puzzle.worker.row-1][puzzle.worker.col]==Box){
        if(puzzle.board[puzzle.worker.row-1][puzzle.worker.col]==Empty || puzzle.board[puzzle.worker.row-1][puzzle.worker.col]==Goal){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }

}
bool can_go_south(Puzzle puzzle)
{
    //              
    assert(true);
    //                                                                                
    if(puzzle.board[puzzle.worker.row+1][puzzle.worker.col]==Empty){
        return true;
    }
    else if(puzzle.board[puzzle.worker.row+1][puzzle.worker.col]==Box){
        if(puzzle.board[puzzle.worker.row+2][puzzle.worker.col]==Empty || puzzle.board[puzzle.worker.row+2][puzzle.worker.col]==Goal){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }
}

bool can_go_west(Puzzle puzzle)
{
    //              
    assert(true);
    //                                                                               
    if(puzzle.board[puzzle.worker.row][puzzle.worker.col-1]==Empty){
        return true;
    }
    else if(puzzle.board[puzzle.worker.row][puzzle.worker.col-1]==Box){
        if(puzzle.board[puzzle.worker.row][puzzle.worker.col-2]==Empty || puzzle.board[puzzle.worker.row][puzzle.worker.col-2]==Goal){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }
}

bool can_go_east(Puzzle puzzle)
{
    //              
    assert(true);
    //                                                                               
    if(puzzle.board[puzzle.worker.row][puzzle.worker.col+1]==Empty){
        return true;
    }
    else if(puzzle.board[puzzle.worker.row][puzzle.worker.col+1]==Box){
        if(puzzle.board[puzzle.worker.row][puzzle.worker.col+2]==Empty || puzzle.board[puzzle.worker.row][puzzle.worker.col+2]==Goal){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }
}

Pos north(Puzzle p){
    //              
    assert(true);
    //                                                                                                                   
    return {p.worker.row-1,p.worker.col};
}

Pos south(Puzzle p){
    //              
    assert(true);
    //                                                                                                                   
    return {p.worker.row+1,p.worker.col};
}

Pos east(Puzzle p){
    //              
    assert(true);
    //                                                                                                                  
    return {p.worker.row,p.worker.col+1};
}

Pos west(Puzzle p){
    //              
    assert(true);
    //                                                                                                                  
    return {p.worker.row,p.worker.col-1};
}

Puzzle move_worker(Puzzle p, Pos next){
    //              
    assert(next.row <= HEIGHT && next.row >= 0 && next.col >=0 && next.col<=WIDTH);
    //                                                                                                                                                     
    if(p.board[next.row][next.col]==Box){
        if(p.board[next.row+(next.row-p.worker.row)][next.col+(next.col-p.worker.col)]==Goal){
            p.board[next.row+(next.row-p.worker.row)][next.col+(next.col-p.worker.col)]=Box_ongoal;
        }
        else{
            p.board[next.row+(next.row-p.worker.row)][next.col+(next.col-p.worker.col)]=Box;
        }
    }
    p.board[p.worker.row][p.worker.col]=Empty;
    p.board[next.row][next.col]=Person;

    p.worker.row=next.row;
    p.worker.col=next.col;
}

struct Candidate{
    Puzzle candidate;
    int parent_candidate;}  ;

bool puzzle_present(vector<Candidate>& c, int i, Puzzle p){
    //              
    assert(i > 0);
    //                                                                                                                                        

    for (int j = 0; j < c.size() ; ++j) {
        for (int l = 0; l < HEIGHT ; ++l) {
            for (int k = 0; k < WIDTH; ++k) {

                if (p.board[l][k]!=c[j].candidate.board[l][k]){
                    return false;
                }
            }
        }
    }
    return true;
}

int no_of_goals(Puzzle p){
    //              
    assert(true);
    //                                                        
    int No=0;

    for (int i = 0; i < HEIGHT ; ++i) {
        for (int j = 0; j < WIDTH ; ++j) {
            if (p.board[i][j]==Goal){
                No++;
            }
        }
    }
    return No;
}

int no_of_box_goals(Puzzle p){
    //              
    assert(true);
    //                                                                 

    int No=0;

    for (int i = 0; i < HEIGHT ; ++i) {
        for (int j = 0; j < WIDTH ; ++j) {
            if (p.board[i][j]==Box_ongoal){
                No++;
            }
        }
    }
    return No;
}

bool puzzle_ready(Puzzle p, int no_goals){
    //              
    assert(true);
    //                                                              
    int no_box_goals = no_of_box_goals(p);

    return no_goals==no_box_goals;
}

void tries(vector<Candidate>&  c, int i, Pos next){
    //              
    assert(i > 0 && next.row <= HEIGHT && next.row >= 0 && next.col >=0 && next.col<=WIDTH);
    //                                                                                                                                                                

    Puzzle p = c[i].candidate ;
    Puzzle newp= move_worker(p, next);
    Candidate newc= {newp,i}  ;
    if (!puzzle_present(c,i,newp))
        c.push_back(newc) ;
}

void solve_breath(Puzzle start) {
    //              
    assert(true);
    //                                                                       
    int no_goals = no_of_goals(start);
    vector<Candidate> c = {{start, -1}};
    int i = 0;
    while (i < c.size() && !puzzle_ready(c[i].candidate, no_goals)) {
        Puzzle p = c[i].candidate;
        if (can_go_north(p)) tries(c, i, north(p));
        if (can_go_south(p)) tries(c, i, south(p));
        if (can_go_west(p)) tries(c, i, west(p));
        if (can_go_east(p)) tries(c, i, east(p));
        i++;
    }
    }

void solve_depth();

void tries_depth( vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depth){
    //              
    assert(next.row <= HEIGHT && next.row >= 0 && next.col >=0 && next.col<=WIDTH && max_depth > 0);
    //                                                                                                                                                               

    Puzzle p = attempt[attempt.size()-1] ;
    Puzzle newp= move_worker(p, next);
    if (!puzzle_present(newp, attempt)){
        attempt.push_back(newp) ;
        solve_depth(attempt, shortest, max_depth) ;
        attempt.pop_back() ; }
}

void solve_depth(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth){

    //              
    assert(max_depth>=0);
    //                                                                      

    const int CURRENT = attempt.size()) ;
    const int BEST = shortest.size() ;
    Puzzle p = attempt[CURRENT-1]  ;
    if(BEST > 0 && CURRENT>= BEST){
        return ; }
    else if(CURRENT> max_depth+1){
        return ;
    }

        else if(puzzle_ready(p)) {
        shortest= attempt;
        return;
    }
    if(can_go_north(p)) {
        tries_depth(attempt, north(p), shortest,  max_depth)
    }
    if(can_go_south(p)){
        tries_depth(attempt, south(p), shortest,  max_depth) ;
    }
    if(can_go_west(p)){
        tries_depth(attempt, west  (p), shortest,  max_depth);
    }
    if(can_go_east(p)){
        tries_depth(attempt, east(p), shortest,  max_depth)
    }
}

    int main() {
        Puzzle puzzle;
        vector<Pos> goal_locations;
        vector<Puzzle> attempt;
        vector<Puzzle> shortest;
        int max_depth= 2^30;

        solve_breath(puzzle);
        solve_depth(attempt ,shortest, max_depth);

        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (puzzle.board[i][j] == 0) {
                    cout << "*";
                } else if (puzzle.board[i][j] == 1) {
                    cout << " ";
                } else if (puzzle.board[i][j] == 2) {
                    cout << "b";
                } else if (puzzle.board[i][j] == 3) {
                    cout << "w";
                } else if (puzzle.board[i][j] == 4) {
                    cout << ".";
                } else if (puzzle.board[i][j] == 5) {
                    cout << "B";
                } else if (puzzle.board[i][j] == 6) {
                    cout << "'";
                }
            }
            cout << "\n";
        }
    }

