/*
             
                      
              
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstring>
#include <cmath>
using namespace std;

const int WIDTH = 7;
const int HEIGHT = 7;
const int SEARCH_DEPTH = 26;
const string filename = "challenge.25.txt";

typedef char Cell;

struct Pos
{
    int col,row;
};

struct Puzzle
{
    Cell board [WIDTH][HEIGHT];
    Pos position; //                          
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

int size (vector<Candidate>& array)
{//               
    assert (true) ;
//                                                                     
    return static_cast<int> (array.size()) ;
}

int size (vector<Puzzle>& array)
{//               
    assert (true) ;
//                                                                     
    return static_cast<int> (array.size()) ;
}

void show_puzzle (Puzzle& puzzle)
{
    //             
    assert(true);
    //                                                     
    for(int i = 0 ; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            cout << puzzle.board[j][i];
        }
        cout << endl;
    }
}

void read_puzzle (Puzzle& puzzle)
{
    //             
    assert(true);
    //                                                              
    ifstream infile (filename);
    char cell;
    Pos pos = {0,0};

    while(infile)
    {
        infile.get(cell);
        if(cell != '\n')
        {
            puzzle.board [pos.col][pos.row] = cell;
            if(cell =='w' || cell=='W')
                puzzle.position = pos; //                   
            pos.col++;
        }
        else //              
        {
            pos.row++;
            pos.col = 0;
        }
    }
}

bool puzzle_ready(Puzzle p)
{//             
    assert(true);
    //                                                                               
    for(int i = 0 ; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
        {
            if(p.board[j][i] == 'b') //                                                             
                return false;
        }
    return true;
}

bool operator==(const Puzzle& a, const Puzzle& b)
{
    //             
    assert(true);
    //                                              
    for(int i = 0 ; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
        {
            if(a.board[j][i] != b.board[j][i])
                return false;
        }
    return true;
}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle p)
{//             
    assert(i < size(c));
    //                                                                                     
    for(int j = 0; j <= i; j++)
        if(c[j].candidate == p) //               
            return true;
    return false;
}

bool find_puzzle(vector<Puzzle>& puzzles, int i, Puzzle p)
{//             
    assert(i < size(puzzles));
    //                                                                                  
    for(int j = 0; j <= i; j++)
        if(puzzles[j] == p)
            return true;
    return false;
}

Pos new_box_pos(Pos old, Pos next)
{//             
    assert(true);
    //                                                                                            
    return {2*next.col-old.col,2*next.row-old.row};
}

Puzzle move_worker(Puzzle p, Pos next)
{//             
    assert(true);
    //                                                                     
    Pos old = p.position;
    bool push_box = false;
    Pos box_next = new_box_pos(old,next);
    Puzzle newp = p;

    newp.position=next;

    switch(p.board[next.col][next.row]) //           
    {
        case ' ': newp.board[next.col][next.row]='w';break;
        case 'b': newp.board[next.col][next.row]='w'; push_box=true; break;
        case 'B': newp.board[next.col][next.row]='W'; push_box=true; break;
        case '.': newp.board[next.col][next.row]='W';break;
    }
    if(p.board[old.col][old.row] =='W') //                              
        newp.board[old.col][old.row]='.';
    else //                          
        newp.board[old.col][old.row]=' ';

    if(push_box) //                    
    {
        switch(p.board[box_next.col][box_next.row]) //        
        {
            case '.': newp.board[box_next.col][box_next.row] = 'B';break;
            case ' ': newp.board[box_next.col][box_next.row] = 'b';break;
        }
    }
    return newp;
}

bool can_go_north(Puzzle puzzle)
{//             
    assert(true);
    //                                                            
    int width = puzzle.position.col;
    int height = puzzle.position.row;

    switch(puzzle.board[width][height-1])
    {
        case ' ': return true;
        case '.': return true;
        case '*': return false;
        case 'b': return (puzzle.board[width][height-2] == ' ' || puzzle.board[width][height-2] =='.'); //                             
        case 'B': return (puzzle.board[width][height-2] == ' ' || puzzle.board[width][height-2] =='.');
    }
}

Pos north(Puzzle p)
{//             
    assert(true);
    //                                                        
    return {p.position.col,p.position.row-1};
}

bool can_go_south(Puzzle puzzle)
{//             
    assert(true);
    //                                                            
    int width = puzzle.position.col;
    int height = puzzle.position.row;

    switch(puzzle.board[width][height+1])
    {
        case ' ': return true;
        case '.': return true;
        case '*': return false;
        case 'b': return (puzzle.board[width][height+2] == ' ' || puzzle.board[width][height+2] =='.');
        case 'B': return (puzzle.board[width][height+2] == ' ' || puzzle.board[width][height+2] =='.');
    }
}

Pos south(Puzzle p)
{//             
    assert(true);
    //                                                        
    return {p.position.col,p.position.row+1};
}

bool can_go_east(Puzzle puzzle)
{//             
    assert(true);
    //                                                            
    int width = puzzle.position.col;
    int height = puzzle.position.row;

    switch(puzzle.board[width+1][height])
    {
        case ' ': return true;
        case '.': return true;
        case '*': return false;
        case 'b': return (puzzle.board[width+2][height] == ' ' || puzzle.board[width+2][height] =='.');
        case 'B': return (puzzle.board[width+2][height] == ' ' || puzzle.board[width+2][height] =='.');
    }
}

Pos east(Puzzle p)
{//             
    assert(true);
    //                                                        
    return {p.position.col+1,p.position.row};
}

bool can_go_west(Puzzle puzzle)
{//             
    assert(true);
    //                                                            
    int width = puzzle.position.col;
    int height = puzzle.position.row;

    switch(puzzle.board[width-1][height])
    {
        case ' ': return true;
        case '.': return true;
        case '*': return false;
        case 'b': return (puzzle.board[width-2][height] == ' ' || puzzle.board[width-2][height] =='.');
        case 'B': return (puzzle.board[width-2][height] == ' ' || puzzle.board[width-2][height] =='.');
    }
}

Pos west(Puzzle p)
{//             
    assert(true);
    //                                                        
    return {p.position.col-1,p.position.row};
}

int parents(vector<Candidate>& c, int i)
{//             
    assert(true);
    //                                                                      
    int parents = 0;
    int index = i;
    while(c[index].parent_candidate != -1) //                                      
    {
        index=c[index].parent_candidate;
        parents++;
    }
    return parents;
}

//                          
void tries_breadth(vector<Candidate>&  c, int i, Pos next)
{//             
    assert(i < size(c));
    //                                                                             
    Puzzle p = c[i].candidate ;
    Puzzle newp= move_worker(p, next);
    Candidate newc=  {newp,  i} ;
    if (!puzzle_present(c,  i,  newp))
        c.push_back(newc);
}

void solve_breadth(Puzzle start)
{//             
    assert(true);
    //                                                                                   
    vector<Candidate> c = {{start,-1}} ;
    int i = 0 ;

    while(i < size(c) && !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if(can_go_north(p)) //                                                
            tries_breadth(c, i, north(p));
        if(can_go_south(p ))
            tries_breadth(c, i, south(p));
        if(can_go_west(p ))
            tries_breadth(c, i, west(p)) ;
        if(can_go_east(p))
            tries_breadth(c, i, east(p)) ;
        i = i+1 ;
    }
    if(i < size(c)) //              
    {
        cout << "Solution in " << parents(c,i)<< " moves:"<<endl;
        show_puzzle(c[i].candidate) ;
    }

}

//                        
void print_depth_sol(vector<Puzzle>& shortest)
{//             
    assert(true);
    //                                                                                   
    int i = size(shortest)-1;
    if(i >= 0 && puzzle_ready(shortest[i]))
       {
            cout << "Solution in " << i << " moves:"<<endl;
            show_puzzle(shortest[i]);
       }
    else
    {
        cout << "Solution not found!" << endl;
    }
}

void tries_depth(vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depth);
void solve_depth(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void tries_depth( vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depth)
{//             
    assert(true);
    //                                                                                                          
    Puzzle p = attempt[size(attempt)-1];
    Puzzle newp= move_worker(p, next) ;
    if (!find_puzzle(attempt,size(attempt)-1,newp))
    {
        attempt.push_back(newp);   //        
        solve_depth(attempt, shortest, max_depth);
        attempt.pop_back();        //       
    }
}

void solve_depth(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{//             
    assert(true);
    //                                                                                 
      const int CURRENT = size(attempt) ;
      const int BEST    = size(shortest) ;

      Puzzle p = attempt[CURRENT-1]  ;
      if(BEST > 0 && CURRENT>= BEST) {return;} //                                                                    
      else if(CURRENT> max_depth+1) { return;} //                           
      else if(puzzle_ready(p)) { shortest = attempt; return;} //                                              

      if(can_go_north(p)) //                            
            tries_depth(attempt, north(p), shortest,  max_depth);
      if(can_go_south(p))
            tries_depth(attempt, south(p), shortest,  max_depth);
      if(can_go_west(p))
            tries_depth(attempt, west(p), shortest,  max_depth);
      if(can_go_east(p))
            tries_depth(attempt, east(p), shortest,  max_depth);
}

int main()
{
    Puzzle init_puzzle;
    read_puzzle(init_puzzle);
    show_puzzle(init_puzzle);

    cout << "Solve with Breadth First:" << endl;
    solve_breadth(init_puzzle);

    vector<Puzzle> attempt = {init_puzzle} ;
    vector<Puzzle> shortest;

    cout << "Solve with Depth First:" << endl;
    solve_depth(attempt,shortest,SEARCH_DEPTH);
    print_depth_sol(shortest);

    return 0;
}
/*
                                                                                              
                                                                                
*/

