#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

//                
//                 

//                                                                                                                

struct Pos{
    int col, row;
};
struct Puzzle{
    vector<vector<char>> map;
    vector<Pos> box;
    Pos worker;
};
struct Candidate{
    Puzzle candidate;
    int parent_candidate;
};
Puzzle puzzle_1 =   {
        {{'*','*','*','*','*','*','*'}
        ,{'*','w',' ',' ',' ','*','*'}
        ,{'*',' ','b','b',' ',' ','*'}
        ,{'*',' ','*','.',' ','.','*'}
        ,{'*',' ',' ',' ',' ',' ','*'}
        ,{'*','*','*','*','*','*','*'}
        },
        {{2,2},{3,2}},
        {1,1}};

bool operator== (const Pos& a,const Pos& b){
    return a.row==b.row && a.col==b.col;
}

bool operator== (const Puzzle& a,const Puzzle& b){
    return a.map==b.map && a.box == b.box && a.worker == b.worker;
}

ostream& operator<<(ostream& out,Candidate c){
    for(int i=0; i < c.candidate.map.size(); i++){
        for(int j=0; j< c.candidate.map[0].size(); j++){
            out << c.candidate.map[i][j];
        }
    }
    out << ' ' << c.parent_candidate;

}

//                                                                                                                

//       

void show_map(Puzzle p){
    //               
    assert(true);
    //                
    //                                   
    const int ROWS = p.map.size();
    const int COLS = p.map[0].size();
    for (int i = 0; i < ROWS ; ++i) {
        for (int j = 0; j <  COLS; ++j) {
            cout << p.map[i][j];
        }
        cout << '\n';
    }
}

bool open_file (ifstream& infile){
    //              
    assert(true);
    //               
    //                                                                                                      
    char filename[100];
    cout << "Please enter a filename\n";
    cin >> filename;
    infile.open(filename);
    if(!infile.is_open()) {
        cout << "The file could not be opened\n";
        return false;
    }
    if(infile.is_open()){
        return true;
    }
}

void read_file(ifstream& infile, vector<vector<char>>& map){
    //               
    assert(open_file(infile));
    //                
    //                                                                     

    infile.close();
}

void read_to_structure(vector<vector<char>>& map, Puzzle p){
    //              
    assert(true);
    //                
    //                                                          
    const int ROWS = p.map.size();
    const int COLS = p.map[0].size();
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            map[i][j]=p.map[i][j];                      //                                
            if(p.map[i][j]=='b'||p.map[i][j]=='B'){     //                                       
                Pos box_pos;
                box_pos.row = i;
                box_pos.col = j;
                p.box.push_back(box_pos);
            }
            if(p.map[i][j]=='w'||p.map[i][j]=='W'){     //                                       
                p.worker.row = i;
                p.worker.col = j;
            }
        }
    }
}

//                                                                                                                

//      

bool puzzle_ready (Puzzle p){
    //              
    assert(true);
    //               
    //                                    
    const int ROWS = p.map.size();
    const int COLS = p.map[0].size();
    for (int i = 0; i < ROWS ; ++i) {
        for (int j = 0; j <  COLS; ++j) {
            if(p.map[i][j]=='.'||p.map[i][j]=='W')
                return false;
        }
    }
    return true;
}

bool can_move_north(Puzzle p){
    if (p.worker.row-1 == ' '|| p.worker.row-1 == '.')
        return true;
    return false;
}
bool can_move_south(Puzzle p){
    if (p.worker.row+1 == ' '|| p.worker.row+1 == '.')
        return true;
    return false;
}
bool can_move_east(Puzzle p){
    if (p.worker.col+1 == ' '|| p.worker.col+1 == '.')
        return true;
    return false;
}
bool can_move_west(Puzzle p){
    if (p.worker.col-1 == ' '|| p.worker.col-1 == '.') {
        return true;
    }
    return false;
}
Pos North (Puzzle p){
    int row, col;
    row = p.worker.row-1;
    col = p.worker.col;
    return {row, col};
}
Pos South (Puzzle p){
    int row, col;
    row = p.worker.row+1;
    col = p.worker.col;
    return {row, col};
}
Pos East (Puzzle p){
    int row, col;
    row = p.worker.row;
    col = p.worker.col+1;
    return {row, col};
}
Pos West (Puzzle p){
    int row, col;
    row = p.worker.row;
    col = p.worker.col-1;
    return {row, col};
}

Puzzle move_worker (Puzzle& p, Pos next){
    //              
    assert(can_move_north(p)||can_move_east(p)||can_move_west(p)||can_move_south(p));
    //               
    //                                                                              
    char from = p.map[p.worker.row][p.worker.col];
    char to = p.map[next.row][next.col];
    if (from=='W'){
        p.map[p.worker.row][p.worker.col]='.';
    }
    else if (from == 'w'){
        p.map[p.worker.row][p.worker.col]=' ';
    }
    if(to=='.'){
        p.map[next.row][next.col]='W';
    }
    else if(to==' '){
        p.map[next.row][next.col]='w';
    }
    else if(to =='b'||to == 'B'){                                       //                  
        if(next.row == p.worker.row && next.col==p.worker.col+1) {      //                 
            if (next.col + 1 == ' ') {
                p.map[next.row][next.col + 1] = 'b';
            } else if (next.col + 1 == '.') {
                p.map[next.row][next.col + 1] = 'B';
            }
        }
        if(next.row == p.worker.row && next.col==p.worker.col-1) {      //                 
            if (next.col + 1 == ' ') {
                p.map[next.row][next.col - 1] = 'b';
            } else if (next.col + 1 == '.') {
                p.map[next.row][next.col - 1] = 'B';
            }
        }
        if(next.row == p.worker.row+1 && next.col==p.worker.col) {      //                  
            if (next.row + 1 == ' ') {
                p.map[next.row][next.col] = 'b';
            } else if (next.row + 1 == '.') {
                p.map[next.row][next.col + 1] = 'B';
            }
        }
        if(next.row == p.worker.row-1 && next.col==p.worker.row) {      //                  
            if (next.row-1 == ' ') {
                p.map[next.row-1][next.col] = 'b';
            } else if (next.row-1 == '.') {
                p.map[next.row-1][next.col] = 'B';
            }
        }
    }
    p.worker = next;
}

//                                                                                                                

bool puzzle_present_breadth (vector<Candidate>& c,const Puzzle newp){
    //              
    assert(true);
    //                                                                 
    for (int k = 0; k < c.size(); k++){
        if(c[k].candidate == newp){
            return true;
        }
    }
    return false;
}

void tries_breadth (vector<Candidate>& c, int i, Pos next){
    //              
    assert(true);
    //               
    //                                                                                      
    Puzzle p = c[i].candidate;
    Puzzle newp = move_worker (p,next);
    Candidate newc = {newp, i};
    if(!puzzle_present_breadth(c, newp))
        c.push_back(newc);
}

void show_path_breadth(vector<Candidate>& c, int i){

}

void solve_breadth(Puzzle start){
    //              
    assert(true);
    //               
    //                                                                               
    vector<Candidate> c = {{start,-1}};
    int i = 0;
    while (i < c.size() && !puzzle_ready(c[i].candidate)){
        Puzzle p = c[i].candidate;
        if (can_move_north(p)) tries_breadth(c, i, North(p));
        if (can_move_south(p)) tries_breadth(c, i, South(p));
        if (can_move_east(p)) tries_breadth(c, i, East(p));
        if (can_move_west(p)) tries_breadth(c, i, West(p));
        i=i+1;
    }
    if (i < c.size())
        show_path_breadth(c,i);
}

//                                                                                                                

//       

void tries_depth (vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depth );

void solve_depth( vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth ){
    //              
    assert(max_depth >= 0 && !attempt.empty());
    //               
    //                                                                                                   
    const int Current = attempt.size();
    const int Best = shortest.size();
    Puzzle p = attempt[Current-1];
    if(Best> 0 && Current >= Best)      {return ;}
    else if (Current > max_depth+1)     {return ;}
    else if (puzzle_ready(p))           {shortest=attempt; return ;}
    if (can_move_north(p)) tries_depth(attempt, North(p), shortest, max_depth);
    if (can_move_south(p)) tries_depth(attempt, South(p), shortest, max_depth);
    if (can_move_west(p)) tries_depth(attempt, West(p), shortest, max_depth);
    if (can_move_east(p)) tries_depth(attempt, East(p), shortest, max_depth);
}

bool puzzle_present_depth(Puzzle p, vector<Puzzle>& attempt){
    //              
    assert(true);
    //               
    //                               
    for(int i=0; i<attempt.size(); i++){
        if (p == attempt[i]){
            return true;
        }
    }
    return false;
}

void tries_depth (vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depth ){
    //              
    assert(true);
    //               
    //                                                                                      
    Puzzle p = attempt[attempt.size()-1];
    Puzzle newp = move_worker(p, next);
    if (!puzzle_present_depth(newp, attempt)){
        attempt.push_back(newp);
        solve_depth(attempt, shortest , max_depth);
        attempt.pop_back();
    }
}

int main() {
//                      
//                      
    vector<Candidate> c;
    show_map(puzzle_1);
    solve_breadth(puzzle_1);

    return 0;
}
