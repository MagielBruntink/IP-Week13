#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

//             
//                       
//                       

const char WALL = '*' ;
const char EMPTY_CELL = ' ' ;
const char EMPTY_DEST = '.' ;
const char WORKER_EMPTY = 'w' ;
const char WORKER_DEST = 'W' ;
const char BOX_EMPTY = 'b' ;
const char BOX_DEST = 'B' ;

typedef char Cell;

Cell challenge0 [6][10] =
{{'*','*','*','*','*','*','*','*','*','*'},
 {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
 {'*','B',' ',' ',' ',' ',' ',' ','w','*'},
 {'*',' ',' ','*','*','*','*',' ',' ','*'},
 {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
 {'*','*','*','*','*','*','*','*','*','*'}};

Cell challenge1a [6][10] =
{{'*','*','*','*','*','*','*','*','*','*'},
 {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
 {'*','.','b','w',' ',' ',' ',' ',' ','*'},
 {'*',' ',' ','*','*','*','*',' ',' ','*'},
 {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
 {'*','*','*','*','*','*','*','*','*','*'}};

Cell challenge1b [7][10] =
{{'*','*','*','*','*','*','*','*','*','*'},
 {'*','w',' ',' ',' ',' ',' ',' ',' ','*'},
 {'*','b',' ',' ',' ',' ',' ',' ',' ','*'},
 {'*','.',' ',' ',' ',' ',' ',' ',' ','*'},
 {'*',' ',' ','*','*','*','*',' ',' ','*'},
 {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
 {'*','*','*','*','*','*','*','*','*','*'}};

Cell challenge23 [6][7] =
{{'*','*','*','*','*','*','*'},
 {'*','w',' ',' ',' ',' ','*'},
 {'*',' ','b','b',' ',' ','*'},
 {'*',' ','*','.',' ','.','*'},
 {'*',' ',' ',' ',' ',' ','*'},
 {'*','*','*','*','*','*','*'}};

Cell challenge25 [7][7] =
{{'*','*','*','*','*','*','*'},
 {'*','*','w',' ',' ','*','*'},
 {'*',' ',' ','*',' ',' ','*'},
 {'*',' ','b','B','b',' ','*'},
 {'*',' ',' ','.',' ',' ','*'},
 {'*','*',' ','.',' ','*','*'},
 {'*','*','*','*','*','*','*'}};

Cell challenge31 [7][7] =
{{'*','*','*','*','*','*','*'},
 {'*','*','*',' ',' ','*','*'},
 {'*','w',' ','.','b','*','*'},
 {'*',' ',' ',' ','b',' ','*'},
 {'*',' ','*','.',' ',' ','*'},
 {'*',' ',' ',' ',' ',' ','*'},
 {'*','*','*','*','*','*','*'}};

Cell challenge34 [9][8] =
{
    {'*','*','*','*','*','*','*','*',},
    {'*','*','*',' ',' ',' ','*','*'},
    {'*','.','w','b',' ',' ','*','*'},
    {'*','*','*',' ','b','.','*','*'},
    {'*','.','*','*','b',' ','*','*'},
    {'*',' ','*',' ','.',' ','*','*'},
    {'*','b',' ','B','b','b','.','*'},
    {'*',' ',' ',' ','.',' ',' ','*'},
    {'*','*','*','*','*','*','*','*',}
};

const int MAX_HEIGHT = 6;    //                                  
const int MAX_WIDTH = 10;  //          

void display_configuration(Cell cell[MAX_HEIGHT][MAX_WIDTH]){
    //              
    assert(true);
    //               
    //                                               
    for (int i=0; i < MAX_HEIGHT; i++){
        for (int n=0; n < MAX_WIDTH; n++)
            cout << cell[i][n];
        cout << '\n';
    }
}

//       
struct Pos
{
    int row, col;
};

struct Puzzle
{
    Cell board[MAX_HEIGHT][MAX_WIDTH];
    Pos guard;
    int no_config;
};

bool can_go_north(Puzzle P){
    //              
    assert(true);
    //               
    //                                                                            
    if (P.board[P.guard.row-1][P.guard.col] == WALL)
        return false;
    else if (P.board[P.guard.row-1][P.guard.col] == BOX_EMPTY||BOX_DEST){
        if (P.board[P.guard.row-2][P.guard.col] == BOX_EMPTY||BOX_DEST||WALL)
            return false;
        return true;
    }
    return true;
}

Pos north(Puzzle P){
    //              
    assert(true);
    //               
    //                                                                                
    return {P.guard.row-1, P.guard.col};
}

bool can_go_south (Puzzle P){
    //              
    assert(true);
    //               
    //                                                                            
    if (P.board[P.guard.row+1][P.guard.col] == WALL)
        return false;
    else if (P.board[P.guard.row+1][P.guard.col] == BOX_EMPTY||BOX_DEST){
        if (P.board[P.guard.row+2][P.guard.col] == BOX_EMPTY||BOX_DEST||WALL)
            return false;
        return true;
    }
    return true;
}

Pos south(Puzzle P){
    //              
    assert(true);
    //               
    //                                                                                
    return {P.guard.row+1, P.guard.col};
}

bool can_go_west(Puzzle P){
    //              
    assert(true);
    //               
    //                                                                           
    if (P.board[P.guard.row][P.guard.col-1] == WALL)
        return false;
    else if (P.board[P.guard.row][P.guard.col-1] == BOX_EMPTY||BOX_DEST){
        if (P.board[P.guard.row][P.guard.col-2] == BOX_EMPTY||BOX_DEST||WALL)
            return false;
        return true;
    }
    return true;
}

Pos west(Puzzle P){
    //              
    assert(true);
    //               
    //                                                                               
    return {P.guard.row, P.guard.col-1};
}

bool can_go_east(Puzzle P){
    //              
    assert(true);
    //               
    //                                                                           
    if (P.board[P.guard.row][P.guard.col+1] == WALL)
        return false;
    else if (P.board[P.guard.row][P.guard.col+1] == BOX_EMPTY||BOX_DEST){
        if (P.board[P.guard.row][P.guard.col+2] == BOX_EMPTY||BOX_DEST||WALL)
            return false;
        return true;
    }
    return true;
}

Pos east(Puzzle P){
    //              
    assert(true);
    //               
    //                                                                               
    return {P.guard.row, P.guard.col+1};
}

Pos start_guard(Cell cell[MAX_HEIGHT][MAX_WIDTH]){
    //              
    assert(true);
    //               
    //                                                                          
    //                              
    for (int i =0; i<MAX_HEIGHT; i++){
        for (int n=0; n<MAX_WIDTH; n++){
            if (cell[i][n]== WORKER_EMPTY||WORKER_DEST)
                return {i, n};
        }
    }
}

void copy_array ( Cell board[MAX_HEIGHT][MAX_WIDTH], Cell board2[MAX_HEIGHT][MAX_WIDTH]){
    //               
    assert (true) ;
    //                
    //                                                          
    for (int i=0; i< MAX_HEIGHT; i++){
        for(int n=0; n<MAX_WIDTH; n++)
            board2[i][n]=board[i][n];
    }
}

struct Candidate{
    Puzzle candidate;
    int parent_candidate;
};

bool end_game(Puzzle puzzz)
{
    //              
    assert(true);
    //               
    //                                                                                      
    for (int i=0; i<MAX_HEIGHT; i++){
        for (int n=0; n<MAX_WIDTH; n++){
            if (puzzz.board[i][n]=='b')
                return false;
        }
    }
    return true;
}

vector<Candidate> c;

bool operator == (const Puzzle& p1, const Puzzle& p2){
    //              
    assert(true);
    //               
    //                                                      
    for (int i=0; i<MAX_HEIGHT; i++){
        for (int n=0; n<MAX_WIDTH; n++){
            if(!p1.board[i][n]==p2.board[i][n])
                return false;
        }
    }
    return true;
}

Cell board[MAX_HEIGHT][MAX_WIDTH];

bool puzzle_present (vector<Candidate>& c, int i, Puzzle p){
    //              
    assert(i>=0);
    //               
    //                                                                                       
    //                                    
    for (int n=0; n< i; n++){
        if(p == c[i].candidate)
            return true;
    }
    return false;
}

Puzzle move_guard (Puzzle p, Pos next, char direction){
    //              
    assert(direction=='n'||direction=='s'||direction=='q'||direction=='e');
    //               
    //                                                                          
    //                                                                          
    //                                      
    if (p.board[next.row][next.col]==EMPTY_CELL){
        if (p.board[p.guard.row][p.guard.col]==WORKER_EMPTY){
            p.board[next.row][next.col]=WORKER_EMPTY;
            p.board[p.guard.row][p.guard.col]=EMPTY_CELL;
        }
        else if (p.board[p.guard.row][p.guard.col]==WORKER_DEST){
            p.board[next.row][next.col]=WORKER_EMPTY;
            p.board[p.guard.row][p.guard.col]=EMPTY_DEST;
        }
    }
    else if (p.board[next.row][next.col]==EMPTY_DEST){
        if (p.board[p.guard.row][p.guard.col]==WORKER_EMPTY){
            p.board[next.row][next.col]=WORKER_DEST;
            p.board[p.guard.row][p.guard.col]=EMPTY_CELL;
        }
        else if (p.board[p.guard.row][p.guard.col]==WORKER_DEST){
                p.board[next.row][next.col]=WORKER_DEST;
                p.board[p.guard.row][p.guard.col]=EMPTY_DEST;
            }
        }

    else{
        Pos behind_box;
        if (direction=='n'){
            behind_box.row=next.row-1;
            behind_box.col=next.col;
        }
        else if (direction=='s'){
            behind_box.row=next.row+1;
            behind_box.col=next.col;
        }
        else if (direction=='q'){
            behind_box.row=next.row;
            behind_box.col=next.col-1;
        }
        else if (direction=='e'){
            behind_box.row=next.row;
            behind_box.col=next.col+1;
        }

        if (p.board[next.row][next.col]==BOX_EMPTY){
            if (p.board[p.guard.row][p.guard.col]==WORKER_EMPTY){
                p.board[next.row][next.col]=WORKER_EMPTY;
                p.board[p.guard.row][p.guard.col]=EMPTY_CELL;
                if(p.board[behind_box.row][behind_box.col]==EMPTY_CELL)
                    p.board[behind_box.row][behind_box.col]==BOX_EMPTY;
                else
                   p.board[behind_box.row][behind_box.col]==BOX_DEST;
            }

            else if (p.board[p.guard.row][p.guard.col]==WORKER_DEST){
                p.board[next.row][next.col]=WORKER_EMPTY;
                p.board[p.guard.row][p.guard.col]=EMPTY_DEST;
                if(p.board[behind_box.row][behind_box.col]==EMPTY_CELL)
                    p.board[behind_box.row][behind_box.col]==BOX_EMPTY;
                else
                    p.board[behind_box.row][behind_box.col]==BOX_DEST;
            }

        }
        else if (p.board[next.row][next.col]==BOX_DEST){
            if (p.board[p.guard.row][p.guard.col]==WORKER_EMPTY){
                p.board[next.row][next.col]=WORKER_DEST;
                p.board[p.guard.row][p.guard.col]=EMPTY_CELL;
                if(p.board[behind_box.row][behind_box.col]==EMPTY_CELL)
                    p.board[behind_box.row][behind_box.col]==BOX_EMPTY;
                else
                   p.board[behind_box.row][behind_box.col]==BOX_DEST;
            }

            else if (p.board[p.guard.row][p.guard.col]==WORKER_DEST){
                p.board[next.row][next.col]=WORKER_DEST;
                p.board[p.guard.row][p.guard.col]=EMPTY_DEST;
                if(p.board[behind_box.row][behind_box.col]==EMPTY_CELL)
                    p.board[behind_box.row][behind_box.col]==BOX_EMPTY;
                else
                    p.board[behind_box.row][behind_box.col]==BOX_DEST;
            }
        }

    }
    p.guard=next;
    p.no_config++;
    return p;
}

void tries(vector<Candidate>& c, int i, Pos next, char direction){
    //              
    assert(i>=0 && direction=='n'||direction=='s'||direction=='q'||direction=='e');
    //               
    //                                                            
    Puzzle p = c[i].candidate ;
    Puzzle newp = move_guard (p, next, direction);
    Candidate newc = {newp, i} ;
    if (!puzzle_present (c, i, newp))
        c.push_back (newc);
}

void show_path (vector<Candidate>& c, int i){
    //              
    assert(i>=0);
    //               
    //                                               
    cout << challenge1a;
}

void solve_BFS(Puzzle initial){
    //              
    assert(true);
    //               
    //                                                                         
    vector<Candidate> c = {{initial,-1}} ;
    int i = 0 ;
        while (i < c.size() && !end_game(c[i].candidate)){
            Puzzle p = c[i].candidate;
            if (can_go_north (p))
                tries(c, i, north(p),'n');
            if (can_go_south (p))
                tries(c, i, south(p), 's');
            if (can_go_west (p))
                tries(c, i, west(p), 'q');
            if (can_go_east (p))
                tries(c, i, east(p), 'e');
            i = i+1 ;
        }
    if (i < c.size())
        show_path (c, i) ;
}

int main()
{
//                     
//                                         
//                                   
    display_configuration (challenge1a);
    //                      
    Puzzle initial;
    copy_array (challenge1a, initial.board);
    initial.guard = start_guard(challenge1a);
    initial.no_config = 0;
    cout << initial.board;
    /*                              
                      
                                             
                          */
    /*                               
                                                   
                           
    */
    return 0;
}

