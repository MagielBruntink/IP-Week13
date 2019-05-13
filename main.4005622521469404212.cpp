#include <iostream>
#include <vector>
#include <assert.h>

//                       
//                     

using namespace std;

enum Cell {WALL = 42, EMPTY = 32, DESTINATION = 46,WORKER = 119 ,WORKER_DESTINATION = 87,BOX = 98, BOX_DESTINATION = 66};
enum Direction {NORTH, EAST, SOUTH, WEST};

struct Pos {
    int x,y;
};

struct Puzzle{
    vector<vector<Cell>> board;
    Pos worker;
};

struct Candidate{
    Puzzle candidate;
    int parentCandidate;
};

bool can_go_north(Puzzle p){
    //             
    assert(true);
    /*               
                                                                                                
    */

    if(p.worker.y == 0) return false;
    if(p.board[p.worker.y-1][p.worker.x] == WALL) return false;
    if(p.board[p.worker.y-1][p.worker.x] == BOX || p.board[p.worker.y-1][p.worker.x] == BOX_DESTINATION){
        if(p.worker.y-1 == 0) return false;
        if(p.board[p.worker.y-2][p.worker.x] == BOX || p.board[p.worker.y-2][p.worker.x] == BOX_DESTINATION || p.board[p.worker.y-2][p.worker.x] == WALL)return false;
    }
    return true;
}

bool can_go_south(Puzzle p){
    //             
    assert(true);
    /*               
                                                                                                
    */
    if(p.worker.y == p.board.size()) return false;
    if(p.board[p.worker.y+1][p.worker.x] == WALL) return false;
    if(p.board[p.worker.y+1][p.worker.x] == BOX || p.board[p.worker.y+1][p.worker.x] == BOX_DESTINATION){
        if(p.worker.y+1 == p.board.size()) return false;
        if(p.board[p.worker.y+2][p.worker.x] == BOX || p.board[p.worker.y+2][p.worker.x] == BOX_DESTINATION || p.board[p.worker.y+2][p.worker.x] == WALL)return false;
    }
    return true;
}

bool can_go_east(Puzzle p){
    //             
    assert(true);
    /*               
                                                                                               
    */
    if(p.worker.x == p.board[0].size()) return false;
    if(p.board[p.worker.y][p.worker.x+1] == WALL) return false;
    if(p.board[p.worker.y][p.worker.x+1] == BOX || p.board[p.worker.y][p.worker.x+1] == BOX_DESTINATION){
        if(p.worker.x+1 == p.board.size()) return false;
        if(p.board[p.worker.y][p.worker.x+2] == BOX || p.board[p.worker.y][p.worker.x+2] == BOX_DESTINATION || p.board[p.worker.y][p.worker.x+2] == WALL)return false;
    }
    return true;
}

bool can_go_west(Puzzle p){
    //             
    assert(true);
    /*               
                                                                                               
    */
    if(p.worker.x == 0) return false;
    if(p.board[p.worker.y][p.worker.x-1] == WALL) return false;
    if(p.board[p.worker.y][p.worker.x-1] == BOX || p.board[p.worker.y][p.worker.x-1] == BOX_DESTINATION){
        if(p.worker.x-1 == 0) return false;
        if(p.board[p.worker.y][p.worker.x-2] == BOX || p.board[p.worker.y][p.worker.x-2] == BOX_DESTINATION || p.board[p.worker.y][p.worker.x-2] == WALL)return false;
    }
    return true;
}

void showPuzzle(Puzzle puzzle){
    //             
    assert(true);
    /*               
                          
    */
    for(int i=0;i<puzzle.board.size(); i++){
        for(int j=0;j<puzzle.board[0].size(); j++){
            cout<< static_cast<char>(puzzle.board[i][j]);
        }
        cout<<endl;
    }
}

Puzzle north(Puzzle p){
    //             
    assert(true);
    /*               
                                                                 
    */
    if(p.board[p.worker.y-1][p.worker.x]==BOX || p.board[p.worker.y-1][p.worker.x]==BOX_DESTINATION){
        if(p.board[p.worker.y-2][p.worker.x]==DESTINATION){p.board[p.worker.y-2][p.worker.x] = BOX_DESTINATION;}
        else {p.board[p.worker.y-2][p.worker.x] = BOX;}
    }
    if(p.board[p.worker.y-1][p.worker.x]==DESTINATION){ p.board[p.worker.y-1][p.worker.x] = WORKER_DESTINATION;}
    else{ p.board[p.worker.y-1][p.worker.x] = WORKER;}

    if(p.board[p.worker.y][p.worker.x] == WORKER_DESTINATION) {p.board[p.worker.y][p.worker.x] = DESTINATION;}
    else{p.board[p.worker.y][p.worker.x] = EMPTY;}
    p.worker.y-=1;
    return p;
}

Puzzle south(Puzzle p){
    //             
    assert(true);
    /*               
                                                                 
    */
    if(p.board[p.worker.y+1][p.worker.x]==BOX || p.board[p.worker.y+1][p.worker.x]==BOX_DESTINATION){
        if(p.board[p.worker.y+2][p.worker.x]==DESTINATION){p.board[p.worker.y+2][p.worker.x] = BOX_DESTINATION;}
        else {p.board[p.worker.y+2][p.worker.x] = BOX;}
    }
    if(p.board[p.worker.y+1][p.worker.x]==DESTINATION){ p.board[p.worker.y+1][p.worker.x] = WORKER_DESTINATION;}
    else{ p.board[p.worker.y+1][p.worker.x] = WORKER;}

    if(p.board[p.worker.y][p.worker.x] == WORKER_DESTINATION) {p.board[p.worker.y][p.worker.x] = DESTINATION;}
    else{p.board[p.worker.y][p.worker.x] = EMPTY;}
    p.worker.y+=1;
    return p;
}

Puzzle east(Puzzle p){
    //             
    assert(true);
    /*               
                                                                
    */
    if(p.board[p.worker.y][p.worker.x+1]==BOX || p.board[p.worker.y][p.worker.x+1]==BOX_DESTINATION){
        if(p.board[p.worker.y][p.worker.x+2]==DESTINATION){p.board[p.worker.y][p.worker.x+2] = BOX_DESTINATION;}
        else {p.board[p.worker.y][p.worker.x+2] = BOX;}
    }
    if(p.board[p.worker.y][p.worker.x+1]==DESTINATION){ p.board[p.worker.y][p.worker.x+1] = WORKER_DESTINATION;}
    else{ p.board[p.worker.y][p.worker.x+1] = WORKER;}

    if(p.board[p.worker.y][p.worker.x] == WORKER_DESTINATION) {p.board[p.worker.y][p.worker.x] = DESTINATION;}
    else{p.board[p.worker.y][p.worker.x] = EMPTY;}
    p.worker.x+=1;
    return p;
}

Puzzle west(Puzzle p){
    //             
    assert(true);
    /*               
                                                                
    */
    if(p.board[p.worker.y][p.worker.x-1]==BOX || p.board[p.worker.y][p.worker.x-1]==BOX_DESTINATION){
        if(p.board[p.worker.y][p.worker.x-2]==DESTINATION){p.board[p.worker.y][p.worker.x-2] = BOX_DESTINATION;}
        else {p.board[p.worker.y][p.worker.x-2] = BOX;}
    }
    if(p.board[p.worker.y][p.worker.x-1]==DESTINATION){ p.board[p.worker.y][p.worker.x-1] = WORKER_DESTINATION;}
    else{ p.board[p.worker.y][p.worker.x-1] = WORKER;}

    if(p.board[p.worker.y][p.worker.x] == WORKER_DESTINATION) {p.board[p.worker.y][p.worker.x] = DESTINATION;}
    else{p.board[p.worker.y][p.worker.x] = EMPTY;}
    p.worker.x-=1;
    return p;
}

bool operator==(const Puzzle& a, const Puzzle& b){
    //             
    assert(true);
    /*               
                                                                                                    
    */
    for(int x=0;x<a.board.size();x++){
        for(int y=0;y<b.board.size();y++){
            if(a.board[y][x] != b.board[y][x]){return false;}
        }
    }
    return true;
}

bool puzzle_present(vector<Candidate> c, int i, Puzzle newp){
     //             
    assert(true);
    /*               
                                                                                                
    */
    if(newp==c[i].candidate) return true;
    return false;
}

bool puzzle_ready(Puzzle p){
     //             
    assert(true);
    /*               
                                                                          
    */
    for(int a=0;a<p.board.size(); a++){
        for(int b=0;b<p.board[0].size(); b++){
            if(p.board[a][b] == DESTINATION || p.board[a][b] == WORKER_DESTINATION) return false;
        }
    }
    return true;
}

void tries(vector<Candidate>& c, int i, Direction next){
     //             
    assert(true);
    /*               
                                                           
    */
    Puzzle p =c[i].candidate;
    Puzzle newp;
    if(next==NORTH){newp = north(p);}
    else if(next==EAST){newp = east(p);}
    else if(next==SOUTH){newp = south(p);}
    else if(next==WEST){newp = west(p);}
    Candidate newc = {newp, i};
    if(!puzzle_present(c,i,newp)) c.push_back(newc);
}

void show_path(vector<Candidate> c, int i){
     //             
    assert(true);
    /*               
                                   
    */
    for(int x=0; x< c.size(); x++){
        showPuzzle(c[x].candidate);
        cout<<endl;
    }
    cout<<endl;
}

void breadth_first(Puzzle start){
    //             
    assert(true);
    /*               
                                                     
    */
    vector<Candidate> c = {{start,-1}};
    int i =0;
    while(i<c.size() && !puzzle_ready(c[i].candidate)){
        Puzzle p = c[i].candidate;
        if(can_go_south(p)) tries(c,i,SOUTH);
        if(can_go_east(p)) tries(c,i,EAST);
        if(can_go_west(p)) tries(c,i,WEST);
        if(can_go_north(p)) tries(c,i,NORTH);
        i++;
    }
    show_path(c,i);
}

bool puzzlePresent2(Puzzle p, vector<Puzzle>&c){
    //             
    assert(true);
    /*               
                                                
    */
    for(int f=0;f<c.size();f++){
        if(c[f]==p) return true;
    }
    return false;
}

void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int maxDepth);

void tries2(vector<Puzzle>& attempt, Direction next, vector<Puzzle>& shortest, int maxDepth){
    //             
    assert(true);
    /*               
                                                         
    */
    Puzzle p = attempt[attempt.size()-1];
    Puzzle newp;
    if(next==NORTH){newp = north(p);}
    else if(next==EAST){newp = east(p);}
    else if(next==SOUTH){newp = south(p);}
    else if(next==WEST){newp = west(p);}

    if(!puzzlePresent2(newp, attempt)){
        attempt.push_back(newp);
        depth_first(attempt, shortest, maxDepth);
        attempt.pop_back();
    }

}

void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int maxDepth){
    //             
    assert(true);
    /*               
                                                 
    */
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle p = attempt[CURRENT-1];
    if(BEST > 0 && CURRENT>= BEST){ return; }
    else if(CURRENT> maxDepth+1){ return; }
    else if(puzzle_ready(p)) { shortest = attempt; return; }
    if(can_go_north(p)) tries2(attempt,NORTH, shortest, maxDepth);
    if(can_go_east(p)) tries2(attempt,EAST, shortest, maxDepth);
    if(can_go_south(p)) tries2(attempt,SOUTH, shortest, maxDepth);
    if(can_go_west(p)) tries2(attempt,WEST, shortest, maxDepth);
}

void showSolution(vector<Puzzle>& c){
    //             
    assert(true);
    /*               
                                            
    */
    for(int i=0;i<c.size();i++){
        showPuzzle(c[i]);
    }
}

int main()
{
    Puzzle p = {{{WALL,WALL,WALL},
                {WALL,WORKER, WALL},
                {WALL,BOX,WALL},
                {WALL,EMPTY,WALL},
                {WALL,DESTINATION,WALL},
                {WALL,WALL,WALL}
                }, 0,1};

    depth_first(p);
    return 0;
}

