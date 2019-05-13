#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>

/* 
                                                          

                                                                                              
                                                                 
 */

using namespace std;

const int WIDTH = 10 ;
const int HEIGHT = 6 ;

struct Pos
{
    int col, row , pluscol, plusrow;
    char type ;
};

struct Candidate
{
    vector<vector<char>> candidate ;
    int parent_candidate ;
};

bool puzzle_ready (vector<vector<char>> p)
{
//              
    assert (true) ;
//               
//                                                                                        
//                                            
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++) {
            if (p[i][j] == 'b') {
                return false;
            }
        }
    }
    return true ;
}

vector<vector<char>> move_empty (vector<vector<char>> p, Pos next)
{
//              
    assert(true) ;
//               
//                                                                  
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++)
         {
            if (p[i][j] == 'w')
                p[i][j] = ' ' ;
            if (p[i][j] == 'W')
                p[i][j] = '.' ;
         }
    }
    if (p[next.col][next.row] == ' ')
            p[next.col][next.row] = 'w' ;

    else if (p[next.col][next.row] == '.')
            p[next.col][next.row] = 'W' ;

    else if (p[next.col][next.row] == 'b')
        {
            p[next.col][next.row] = 'w' ;
            if (p[next.pluscol][next.plusrow] == '.')
                p[next.pluscol][next.plusrow] = 'B' ;
            else
                p[next.pluscol][next.plusrow] = 'b' ;
        }
    else if (p[next.col][next.row] == 'B')
        {
            p[next.col][next.row] = 'W' ;
            if (p[next.pluscol][next.plusrow] == '.')
                p[next.pluscol][next.plusrow] = 'B' ;
            else
                p[next.pluscol][next.plusrow] = 'b' ;
        }
    return p;

}

bool can_go_north (vector<vector<char>> p)
{
//              
    assert (true);
//               
//                                                                                 
//                                       
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++)
            if (p[i][j] == 'w' || p[i][j] == 'W')
            {
                if (p[i-1][j] != '*' && p[i-1][j] != 'b' && p[i-1][j] != 'B' )
                    return true;
                else if (p[i-1][j] == 'b' || p[i-1][j] == 'B')
                {
                    if (p[i-2][j]!= '*' && p[i-2][j] != 'b' && p[i-2][j] != 'B' )
                        return true ;
                }
                return false ;
            }
    }
}

bool can_go_south (vector<vector<char>> p)
{
//              
    assert (true);
//               
//                                                                                 
//                                       
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++) {
            if (p[i][j] == 'w' || p[i][j] == 'W')
            {
                if (p[i+1][j] != '*' && p[i+1][j] != 'b' && p[i+1][j] != 'B' )
                    return true;
                else if (p[i+1][j] == 'b' || p[i+1][j] == 'B')
                {
                    if (p[i+2][j]!= '*' && p[i+2][j] != 'b' && p[i+2][j] != 'B' )
                        return true ;
                }
                return false ;
            }
        }
    }
}

bool can_go_east (vector<vector<char>> p)
{
//              
    assert (true);
//               
//                                                                                
//                                       
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++)
            if (p[i][j] == 'w' || p[i][j] == 'W')
            {
                if (p[i][j+1] != '*' && p[i][j+1] != 'b' && p[i][j+1] != 'B' )
                    return true;
                else if (p[i][j+1] == 'b' || p[i][j+1] == 'B')
                {
                    if (p[i][j+2]!= '*' && p[i][j+2] != 'b' && p[i][j+2] != 'B' )
                        return true ;
                }
                return false ;
            }
    }
}

bool can_go_west (vector<vector<char>> p)
{
//              
    assert (true);
//               
//                                                                                
//                                       
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++)
            if (p[i][j] == 'w' || p[i][j] == 'W')
            {
                if (p[i][j-1] != '*' && p[i][j-1] != 'b' && p[i][j-1] != 'B' )
                    return true;
                else if (p[i][j-1] == 'b' || p[i][j-1] == 'B')
                {
                    if (p[i][j-2]!= '*' && p[i][j-2] != 'b' && p[i][j-2] != 'B' )
                        return true ;
                }
                return false ;
            }
    }
}

Pos north (vector<vector<char>> p)
{
//              
    assert (true);
//               
//                                              
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++)
            if (p[i][j] == 'w' || p[i][j] == 'W')
            {
                Pos pos ;
                pos.col = i -1 ;
                pos.row = j ;
                pos.pluscol = i-2;
                pos.plusrow = j;
                if (p[i-1][j] == '.')
                    pos.type = 'W' ;
                else
                    pos.type = 'w' ;
                return pos ;
            }
    }
}

Pos south (vector<vector<char>> p)
{
//              
    assert (true);
//               
//                                              
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++)
            if (p[i][j] == 'w' || p[i][j] == 'W')
            {
                Pos pos ;
                pos.col = i + 1 ;
                pos.row = j ;
                pos.pluscol = i+2;
                pos.plusrow = j;
                if (p[i+1][j] == '.')
                    pos.type = 'W' ;
                else
                    pos.type = 'w' ;
                return pos ;
            }
    }
}

Pos east (vector<vector<char>> p)
{
//              
    assert (true);
//               
//                                              
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++)
            if (p[i][j] == 'w' || p[i][j] == 'W')
            {
                Pos pos ;
                pos.col = i ;
                pos.row = j + 1 ;
                pos.pluscol = i;
                pos.plusrow = j + 2;
                if (p[i][j+1] == '.')
                    pos.type = 'W' ;
                else
                    pos.type = 'w' ;
                return pos ;
            }
    }
}

Pos west (vector<vector<char>> p)
{//              
    assert (true);
//               
//                                              
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++)
            if (p[i][j] == 'w' || p[i][j] == 'W')
            {
                Pos pos ;
                pos.col = i ;
                pos.row = j - 1 ;
                pos.pluscol = i;
                pos.plusrow = j - 2;
                if (p[i][j-1] == '.')
                    pos.type = 'W' ;
                else
                    pos.type = 'w' ;
                return pos ;
            }
    }
}

void tries (vector<Candidate>& c, int i, Pos next)
{//              
    assert (true);
//               
//                                                                                  
    vector<vector<char>> p = c[i].candidate ;
    vector<vector<char>> newp = move_empty (p, next);
    Candidate newc = {newp, i} ;
    c.push_back (newc) ;
}

void least_number_breadth (vector<Candidate>& c, int i)
{//              
    assert (true);
//               
//                                                                                      
    cout << "least number of steps: "<< c[i].parent_candidate + 1 << endl;
}

void solve_breadth (vector<vector<char>> start)
{//              
    assert (true);
//               
//                                                                                                                    
    vector<Candidate> c = {{start,-1}} ;
    int i = 0 ;
    while (i < c.size() && !puzzle_ready (c[i].candidate))
    {
        vector<vector<char>> p = c[i].candidate ;
        if (can_go_north (p)) tries (c, i, north (p));
        if (can_go_south (p)) tries (c, i, south (p));
        if (can_go_west (p)) tries (c, i, west (p));
        if (can_go_east (p)) tries (c, i, east (p));
        i = i + 1 ;
    }
    if (i<c.size())
        least_number_breadth(c, i);
}

void tries2 (vector<vector<vector<char>>>& attempt, Pos next, vector<vector<vector<char>>> shortest, int max_depth)
{
//              
    assert (true);
//               
//                                                                                  
    vector<vector<char>> p = attempt[attempt.size() - 1] ;
    vector<vector<char>> newp = move_empty(p, next) ;
    attempt.push_back(newp);
    solve_depth(attempt, shortest, max_depth) ;
    attempt.pop_back();
}

void solve_depth (vector<vector<vector<char>>>& attempt, vector<vector<vector<char>>>& shortest, int max_depth)
{
//              
    assert (true);
//               
//                                    
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    vector<vector<char>> p = attempt[CURRENT-1] ;
    if (BEST > 0 && CURRENT >= BEST)
        return;
    else if (CURRENT > max_depth + 1)
        return;
    else if (puzzle_ready(p))
    {
        shortest = attempt;
        return ;
    }
    if (can_go_north(p)) tries2 (attempt,north(p), shortest, max_depth);
    if (can_go_south(p)) tries2 (attempt,south(p), shortest, max_depth);
    if (can_go_west(p)) tries2 (attempt,west(p), shortest, max_depth);
    if (can_go_east(p)) tries2 (attempt,east(p), shortest, max_depth);
}

int main()
{
    vector<vector<char>> puzzle = {{'*','*','*','*','*','*','*','*','*','*'},
                                   {'*',' ','.',' ',' ',' ',' ',' ',' ','*'},
                                   {'*',' ','b',' ',' ',' ',' ',' ',' ','*'},
                                   {'*',' ','w','*','*','*','*',' ',' ','*'},
                                   {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                                   {'*','*','*','*','*','*','*','*','*','*'}};
    for (int i = 0 ; i < HEIGHT; i++)
    {
        for (int j = 0 ; j < WIDTH; j++)
            cout << puzzle[i][j];
        cout << '\n' ;
    }
    solve_breadth (puzzle) ;
    return 0;
}

