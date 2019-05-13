#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std ;

//                      
//                          

const int width = 10;
const int height =  6;
typedef char cell;
struct pos{
    int row;
    int column;
};
struct puzzle{
    cell board [height][width];
    pos worker;
};

ostream&operator<<(ostream&out, const puzzle& p){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            cout << p.board [i][j];
        }
        cout << endl;
    }
}

bool operator== (const puzzle&p1,const puzzle&p2){
    puzzle yeet = p1;
    puzzle yeet2 = p2;
    for(int i= 0; i<height; i++){
        for(int j= 0; j<width; j++){
            if(yeet.board[i][j] != yeet2.board[i][j]){
                return false;
            }
        }
    }
      return true;
}
struct candidate{
    puzzle candidate;
    int parent_candidate;
};
cell start[height][width] = {{'*','*','*','*','*','*','*','*','*','*'},
                              {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                              {'*',' ','.','b','w',' ',' ',' ',' ','*'},
                              {'*',' ',' ','*','*','*','*',' ',' ','*'},
                              {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                              {'*','*','*','*','*','*','*','*','*','*'}};

//            
//                                                                               
//             
//                                                                                                                              
//                                                                                             

bool can_north (puzzle p){
    pos workerpos;
    workerpos = p.worker;
    if (p.board [workerpos.row-1] [workerpos.column] == '*')
        return false;
    if (p.board [workerpos.row-1] [workerpos.column] == 'b' || p.board [workerpos.row+1] [workerpos.column] == 'B'){
        if (p.board [workerpos.row-2] [workerpos.column] == 'b' || p.board [workerpos.row+2] [workerpos.column] == 'B')
            return false;
        if (p.board [workerpos.row-2] [workerpos.column] == '*')
            return false;
    }
    return true;
}
bool can_south (puzzle p){
    pos workerpos;
    workerpos = p.worker;
    if (p.board [workerpos.row+1] [workerpos.column] == '*')
        return false;
    if (p.board [workerpos.row+1] [workerpos.column] == 'b' || p.board [workerpos.row-1] [workerpos.column] == 'B'){
        if (p.board [workerpos.row+2] [workerpos.column] == 'b' || p.board [workerpos.row-2] [workerpos.column] == 'B')
            return false;
        if (p.board [workerpos.row+2] [workerpos.column] == '*')
            return false;
    }
    return true;
}
bool can_west (puzzle p){
    pos workerpos;
    workerpos = p.worker;
    if (p.board [workerpos.row] [workerpos.column-1] == '*')
        return false;
    if (p.board [workerpos.row] [workerpos.column-1] == 'b' || p.board [workerpos.row] [workerpos.column-1] == 'B'){
        if (p.board [workerpos.row] [workerpos.column-2] == 'b' || p.board [workerpos.row] [workerpos.column-2] == 'B')
            return false;
        if (p.board [workerpos.row] [workerpos.column-2] == '*')
            return false;
    }
    return true;
}
bool can_east (puzzle p){
    pos workerpos;
    workerpos = p.worker;
    if (p.board [workerpos.row] [workerpos.column+1] == '*')
        return false;
    if (p.board [workerpos.row] [workerpos.column+1] == 'b' || p.board [workerpos.row] [workerpos.column+1] == 'B'){
        if (p.board [workerpos.row] [workerpos.column+2] == 'b' || p.board [workerpos.row] [workerpos.column+2] == 'B')
            return false;
        if (p.board [workerpos.row] [workerpos.column+2] == '*')
            return false;
    }
    return true;
}
bool puzzle_ready (puzzle p){
    for (int i = 0; i<height; i++){
        for (int j = 0; j<width; j++){
            if  (p.board [i][j] == '.' || p.board [i][j] == 'b')
                return false;
        }
    }
    return true;
}
bool puzzle_present (vector<candidate>& breadth, int i, puzzle p){
    for (int j = 0; j<=i; j++){
        if (p == breadth[j].candidate){
            return true;}
    }
return false;
}
//            
//                                                            
//             
//                                                                                            
pos north (puzzle p){
    pos next = p.worker;
    next.row--;
    return next;
}
pos south (puzzle p){
    pos next = p.worker;
    next.row++;
    return next;
}
pos east (puzzle p){
    pos next = p.worker;
    next.column++;
    return next;
}
pos west (puzzle p){
    pos next = p.worker;
    next.column--;
    return next;
}
puzzle move_worker(puzzle p, pos next) {
    //            
    assert(true);
    //             
    //                                                                                                             
    //                                                                             
    pos current = p.worker;
    int rowchange = next.row - current.row;
    int columnchange = next.column - current.column;

if (p.board [next.row][next.column] == ' '){
    p.board [next.row][next.column] = 'w';}
else if (p.board [next.row][next.column] == '.')
    p.board [next.row][next.column] = 'W';
else if (p.board [next.row][next.column] == 'b') {
    if (p.board[next.row + rowchange][next.column + columnchange] == ' ') {
        p.board[next.row + rowchange][next.column + columnchange] = 'b';
        p.board[next.row][next.column] = 'w';
    } else if (p.board[next.row + rowchange][next.column + columnchange] == '.') {
        p.board[next.row + rowchange][next.column + columnchange] = 'B';
        p.board[next.row][next.column] = 'w';
    }
}
else if (p.board [next.row][next.column] == 'B') {
    if (p.board[next.row + rowchange][next.column + columnchange] == ' ') {
        p.board[next.row + rowchange][next.column + columnchange] = 'b';
        p.board[next.row][next.column] = 'W';
    } else if (p.board[next.row + rowchange][next.column + columnchange] == '.') {
        p.board[next.row + rowchange][next.column + columnchange] = 'B';
        p.board[next.row][next.column] = 'W';
    }
}
if (p.board[current.row][current.column] == 'w')
    p.board[current.row][current.column] = ' ';
else if (p.board[current.row][current.column] == 'W')
    p.board[current.row][current.column]= '.';

    return p;

}

void show_path_breadth(vector<candidate>& breadth, int i){
    //            
    assert(breadth.size() >= 0);
    //             
    //                                                                                                           
    while (i != -1){
        i=breadth[i].parent_candidate;
    }

}

void tries_breadth (vector<candidate>& breadth, int i, pos next){
    //            
    assert(i >= 0 && breadth.size() >= 0);
    //             
    //                                                                                                           
    //                                                          
    puzzle p = breadth[i].candidate;
    puzzle newp = move_worker (p, next);
    candidate newc = {newp, i};
    if (!puzzle_present (breadth, i, newp)){
        breadth.push_back(newc);
    }

}
void solve_breadth (puzzle start){
    //            
    assert(true);
    //             
    //                                                                                                       
    //                                                                                                                       
    vector <candidate> breadth  = {{start, -1}};

    int i = 0;
    while (!puzzle_ready(breadth[i].candidate)){
        puzzle p = breadth[i].candidate;
        if (can_north(p) ) tries_breadth(breadth, i, north(p));
        if (can_south(p) ) tries_breadth(breadth, i, south(p));
        if (can_east(p) ) tries_breadth(breadth, i, east(p));
        if (can_west(p) ) tries_breadth(breadth, i, west(p));
      i++;

    }
    if (i<= breadth.size()){
        show_path_breadth(breadth, i);
    }

}
bool puzzle_present_depth(puzzle p, vector<puzzle>& attempt){
    //            
    assert(attempt.size() >= 0);
    //             
    //                                                                                                    
    for (int j = 0; j<attempt.size(); j++){
        if (p  == attempt[j])
            return true;
    }
    return false;
}

void tries_depth (vector<puzzle>& attempt, pos next, vector<puzzle>& shortest, int max_depth);
void solve_depth (vector<puzzle>& attempt, vector<puzzle>& shortest, int max_depth){
    //            
    assert(attempt.size() >= 0);
    //             
    //                                                                                                           
    //                                                                            
    const int current = attempt.size();
    const int best = shortest.size();
    puzzle p = attempt[current-1];
    if(best > 0 && current >= best){ return;}
    else if (current > max_depth+1) {return;}
    else if (puzzle_ready(p)){ shortest = attempt; return;}
    if (can_north(p)) tries_depth(attempt, north(p), shortest, max_depth);
    if (can_south(p)) tries_depth(attempt, south(p), shortest, max_depth);
    if (can_east(p)) tries_depth(attempt, east(p), shortest, max_depth);
    if (can_west(p)) tries_depth(attempt, west(p), shortest, max_depth);

}

void tries_depth (vector<puzzle>& attempt, pos next, vector<puzzle>& shortest, int max_depth){
    //            
    assert(attempt.size() >= 0);
    //             
    //                                                                                                
    //                                                                                                 
    puzzle p = attempt[attempt.size()-1];
    puzzle newp = move_worker(p, next);
    if (!puzzle_present_depth(newp, attempt)){

        attempt.push_back(newp);
        solve_depth (attempt, shortest, max_depth);
        attempt.pop_back();

    }

}
int main() {
    pos worker = {2,4};
    puzzle first = {{{'*','*','*','*','*','*','*','*','*','*'},
                          {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                          {'*',' ','.','b','w',' ',' ',' ',' ','*'},
                          {'*',' ',' ','*','*','*','*',' ',' ','*'},
                          {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                          {'*','*','*','*','*','*','*','*','*','*'}}, worker};

vector<puzzle> attempt ={};
vector<puzzle> shortest = {};
attempt.push_back(first);
solve_depth(attempt, shortest, 100);
for(int i = 0; i<shortest.size(); i++){
    cout << shortest[i];}
  //                       
    return 0;

}
