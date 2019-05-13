#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>

using namespace std;
//                                                  
const int WIDTH = 10 ;
const int HEIGHT = 6 ;
typedef int Cell ;
const Cell Empty = WIDTH * HEIGHT;

enum Direction {north, east, south, west};

struct Pos
{
    int col;
    int row;
};
struct Puzzle
{
    Cell board [WIDTH][HEIGHT];
    Pos open ;
};
 struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

bool puzzle_ready(Puzzle puzzle)
{
//               
assert(true);
//                                                                      
    for ( int i = 0; i < WIDTH; i++ )
    {
        for ( int j = 0; j < HEIGHT; j++)
        {
            if (puzzle.board[i][j] == '.' || puzzle.board[i][j] == 'W')
                return false;
            else
                return true;
        }
    }
}

void find_w (Puzzle puzzle, int& i, int& j)
{
//               
assert(true);
//                                                                         
//                        
    for ( i =0 ; i < WIDTH; i++ )
    {
        for ( j=0 ; j < HEIGHT; j++)
        {
            if (puzzle.board[i][j] == 'w' || puzzle.board[i][j] == 'W')
                return ;
        }
    }
}

bool can_walk ( Puzzle puzzle,Direction direction)
{
//               
assert(true);
//                                                                        
//                                        
    int i,j;
    find_w(puzzle, i, j);
    if ( direction == north)
    {
        if ( puzzle.board[i-1][j] == '*' )
            return false;
        else if ( puzzle.board[i-1][j] == 'b')
        {
            if ( puzzle.board[i-2][j] == '*')
                return false;
        }
    }
    else if ( direction == east)
    {
        if ( puzzle.board[i][j+1] == '*' )
            return false;
        else if ( puzzle.board[i][j+1] == 'b')
        {
            if ( puzzle.board[i][j+2] == '*')
                return false;
        }
    }
    else if ( direction == south)
    {
        if ( puzzle.board[i+1][j] == '*' )
            return false;
        else if ( puzzle.board[i+1][j] == 'b')
        {
            if ( puzzle.board[i+2][j] == '*')
                return false;
        }
    }
    else if ( direction == west)
    {
        if ( puzzle.board[i][j-1] == '*' )
            return false;
        else if ( puzzle.board[i][j-1] == 'b')
        {
            if ( puzzle.board[i][j-2] == '*')
                return false;
        }
    }
    return true;
}

bool same (Puzzle c, Puzzle p)
{
//              
assert(true);
//                                                             
    for ( int i = 0; i < WIDTH; i++)
    {
        for ( int j = 0; j < HEIGHT; j++)
        {
            if ( c.board[i][j] != p.board[i][j] )
                return false;
        }
    }
    return true;
}

bool puzzle_present ( vector<Candidate>& c, int i, Puzzle p)
{
//               
assert(true);
//                                                                         
    for ( i = 0 ; i < c.size(); i++)
    {
       if (same(c[i].candidate, p))
       {
           return true ;
       }
    }
    return false ;
}

void move_empty(Puzzle& p, Direction direction)
{
//              
assert(true);
//                                                                            
    int i,j,nexti,nextii,nextj,nextjj;
    find_w(p, i, j);
    if ( direction == north)
    {
        nexti = i - 1;
        nextii = i - 2;
        nextj = j;
        nextjj = j;
    }
    if ( direction == east)
    {
        nexti = i;
        nextii = i;
        nextj = j + 1;
        nextjj = j + 2;
    }
    if ( direction == south)
    {
        nexti = i + 1;
        nextii = i + 2;
        nextj = j;
        nextjj= j;
    }
    if ( direction == west)
    {
        nexti = i;
        nextii = i;
        nextj = j - 1;
        nextjj = j - 2;
    }

    if ( p.board[nexti][nextj] == '.')
    {
        p.board[nexti][nextj] = 'W' ;
    }
    else if ( p.board[nexti][nextj] == 'b' )
    {
        if (p.board[nextii][nextjj] == '.')
        {
            p.board[nextii][nextjj] = 'B';
        }
        else
        {
            p.board[nextii][nextjj] = 'b';
        }
        p.board[nexti][nextj] = 'w';
    }

    if (p.board[i][j] == 'W' )
    {
        p.board[i][j] = '.';
    }
    else
    {
        p.board[i][j] = ' ';
    }
}

void tries(vector<Candidate> &c, int i, Direction direction)
{
//               
assert(true);
//                                                                            
//                                                                            
//        
    Puzzle p = c[i].candidate ;
    move_empty (p, direction);
    Puzzle newp = p;
    Candidate newc = {newp, i};
    if (!puzzle_present (c, i, newp))
        c.push_back(newc);
}

void show_path (vector<Candidate>& c, int i)
{
//               
assert(true);
//                                                                         
    if (i < 0)
        return;
    for ( int a = 0; a < 6; a++)
    {
        for (int b = 0; b < 10; b++)
        {
            cout << c[i].candidate.board[a][b];
        }
        cout << endl;
    }
    show_path(c,c[i].parent_candidate);
}

void solve (Puzzle start)
{
//               
assert(true);
//                                                                            

    vector<Candidate> c = {{start, -1}};
    int i =0;
    while ( i < c.size() && !puzzle_ready (c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if (can_walk(p, north))
            tries(c, i, north);
        if (can_walk(p, east))
            tries(c, i, east);
        if (can_walk(p, south))
            tries(c, i, south);
        if (can_walk(p, west))
            tries(c, i, west);
        i=i+1;
    }
    if ( i < c.size())
        show_path(c, i);
}

int main()
{
    vector<Puzzle> puzzle = {{'*', '*', '*', '*', '*', '*', '*', '*', '*','*'},
        {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','*'},
        {'*', 'B', ' ', ' ', ' ', ' ', ' ', ' ', 'w','*'},
        {'*', ' ', ' ', '*', '*', '*', '*', ' ', ' ','*'},
        {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','*'},
        {'*', '*', '*', '*', '*', '*', '*', '*', '*','*'}
    };

     solve(puzzle);
}

