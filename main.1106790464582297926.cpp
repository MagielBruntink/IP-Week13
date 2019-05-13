#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

//                              
//                          

/*
            
           
                       
                        
                         
                     
                           
*/

//               
const int max_width = 20;
const int max_depth = 20;
char world[max_width][max_depth];
int width;
int depth;
typedef char Cell;
Cell EMPTY = width*depth;

struct Pos
{
    int col;
    int row;
};

struct Puzzle
{
    Cell board [max_width][max_depth];
    Pos open;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

int size (vector<Candidate>& c)
{
//              
    assert(true);
//               
    //                        
    return static_cast<int> (c.size ()) ;
}

int size (vector<Puzzle>& c)
{
//              
    assert(true);
//               
    //                        
    return static_cast<int> (c.size ()) ;
}

bool puzzle_ready(Puzzle p)
{
//              
    assert(true);
//               
    //                                                       
    for (int i = 0; i < max_width; i++)
    {
        for (int j = 0; j < max_depth; j++)
        {
            //                                                            
            if (p.board[i][j] == 'b')
                return false;
        }
    }
    return true;
}

bool operator== (const Puzzle& a, const Puzzle& b)
{//              
    assert (true) ;
/*                
                                 
*/
    for (int i = 0; i < max_width; i++)
    {
        for (int j = 0; j < max_depth; j++)
        {
            if (a.board[i][j] != b.board[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle p)
{
//              
    assert(i >= 0);
//               
    //                                                 
    for (int j = 0; j < size(c); j++)
        {
            if (p == c[j].candidate)
                return true;
        }
    return false;
}

Puzzle move_empty(Puzzle& p, Pos next)
{
//              
    assert(true);
//               
    //                                                      
    if(p.board[p.open.row][p.open.col] == 'w')
        p.board[p.open.row][p.open.col] = ' ';

    else if(p.board[p.open.row][p.open.col] == 'W')
        p.board[p.open.row][p.open.col] = '.';

    if(p.board[next.row][next.col] == '.')
        p.board[next.row][next.col] = 'W';

    else if(p.board[next.row][next.col] == ' ')
        p.board[next.row][next.col] = 'w';

    if(p.board[next.row][next.col] == 'b' || p.board[next.row][next.col] == 'B')
    {
        if(p.board[next.row][next.col] == 'b')
            p.board[next.row][next.col] = 'w';

        else if(p.board[next.row][next.col] == 'B')
            p.board[next.row][next.col] = 'W';

        int a = p.open.row - next.row;
        int b = p.open.col - next.col;

        if (p.board[next.row-a][next.col-b] == ' ')
            p.board[next.row-a][next.col-b] = 'b';
        else
            p.board[next.row-a][next.col-b] = 'B';
    }
    p.open.col = next.col;
    p.open.row = next.row;
    return p;
}

void show_state(int a, int b, char world[max_width][max_depth])
{
//               
    assert (true) ;
/*                 
                     
*/
    cout << endl;
	for (int p=0; p < a; p++)
	{
		for (int k=0; k < b; k++)
		{
            cout << world[p][k];
		}
		if (world[p][0] == '*')
            cout << endl;
	}
}

void show_path(vector<Candidate>& c, int i)
{
//              
    assert(true);
//               
    //                               
    vector<int> path;
    while(i != 0)
    {
        path.push_back(c[i].parent_candidate);
        i = c[i].parent_candidate;
    }

    for(int j = 0; j < path.size(); j++)
    {
        show_state(max_width, max_depth, c[path[j]].candidate.board);
    }
}

bool can_go_north(Puzzle p)
{
//              
    assert(true);
//               
   //                                                    
    if (p.board[p.open.row-1][p.open.col] == '*')
        return false;
    if (p.board[p.open.row-1][p.open.col] == ' ' || p.board[p.open.row-1][p.open.col] == '.')
        return true;
    if (p.board[p.open.row-1][p.open.col] == 'b' || p.board[p.open.row-1][p.open.col] == 'B')
    {
        if (p.board[p.open.row-2][p.open.col] == 'b' || p.board[p.open.row-2][p.open.col] == 'B'|| p.board[p.open.row-2][p.open.col] == '*')
            return false;
        return true;
    }
    return false;
}

Pos north(Puzzle p)
{
//              
    assert(true);
//               
    //                                                     
    p.open.row--;
    return p.open;
}

bool can_go_south(Puzzle p)
{
//              
    assert(true);
//               
    //                                                           
    if (p.board[p.open.row+1][p.open.col] == '*')
        return false;
    if (p.board[p.open.row+1][p.open.col] == ' ' || p.board[p.open.row+1][p.open.col] == '.')
        return true;
    if (p.board[p.open.row+1][p.open.col] == 'b' || p.board[p.open.row+1][p.open.col] == 'B')
    {
        if (p.board[p.open.row+2][p.open.col] == 'b' || p.board[p.open.row+2][p.open.col] == 'B'|| p.board[p.open.row+2][p.open.col] == '*')
            return false;
        return true;
    }
    return false;
}

Pos south(Puzzle p)
{
//              
    assert(true);
//               
    //                                                     
    p.open.row++;
    return p.open;
}

bool can_go_west(Puzzle p)
{
//              
    assert(true);
//               
    //                                                          
    if (p.board[p.open.row][p.open.col-1] == '*')
        return false;
    if (p.board[p.open.row][p.open.col-1] == ' ' || p.board[p.open.row][p.open.col-1] == '.')
        return true;
    if (p.board[p.open.row][p.open.col-1] == 'b' || p.board[p.open.row][p.open.col-1] == 'B')
    {
        if (p.board[p.open.row][p.open.col-2] == 'b' || p.board[p.open.row][p.open.col-2] == 'B'|| p.board[p.open.row][p.open.col-2] == '*')
            return false;
        return true;
    }
    return false;
}

Pos west (Puzzle p)
{
//              
    assert(true);
//               
    //                                                    
    p.open.col--;
    return p.open;
}

bool can_go_east(Puzzle p)
{
//              
    assert(true);
//               
    //                                                          
    if (p.board[p.open.row][p.open.col+1] == '*')
        return false;
    if (p.board[p.open.row][p.open.col+1] == ' ' || p.board[p.open.row][p.open.col+1] == '.')
        return true;
    if (p.board[p.open.row][p.open.col+1] == 'b' || p.board[p.open.row][p.open.col+1] == 'B')
    {
        if (p.board[p.open.row][p.open.col+2] == 'b' || p.board[p.open.row][p.open.col+2] == 'B'|| p.board[p.open.row][p.open.col+2] == '*')
            return false;
        return true;
    }
    return false;
}

Pos east (Puzzle p)
{
//              
    assert(true);
//               
    //                                                    
    p.open.col++;
    return p.open;
}

//                        

bool puzzle_present(Puzzle p, vector<Puzzle>& c)
{
//              
    assert(true);
//               
    //                                                 

    for (int j = 0; j < size(c); j++)
        {
            if (c[j] == p)
                return true;
        }
    return false;
}

void show_solution(vector<Puzzle>& c)
{
//              
    assert(true);
//               
    //                               
    for (int i = 0; i < size(c); i++)
    {
        show_state(width, depth, c[i].board);
    }
}

void position_worker(char world[max_width][max_depth], int& a, int& b)
{
    for(a = 0; a < max_width; a++)
    {
        for(b = 0; b < max_depth; b++)
        {
            if (world[a][b] == 'w' || world[a][b] == 'W')
                return;
        }
    }
}

void tries(vector<Candidate>&  c, int& i, Pos next) //                    
{
//              
    assert(i >= 0);
//               
    //
    Puzzle p = c[i].candidate ;
    Puzzle newp = move_empty(p, next);
    //                                             
    Candidate newc = {newp, i}  ;
    cout << "present = " << puzzle_present(c, i, newp) << endl;
    if (!puzzle_present(c, i, newp))
    {
        //                                                
        c.push_back(newc) ;
        cout << "New" << endl;
        i++;
        show_state(max_width, max_depth, newp.board);
    }
}

void solve(Puzzle start)    //                    
{
//              
    assert(true);
//               
    //                   
    vector<Candidate> c = {{start,-1}} ;
    int i = 0 ;
    //                                     
    //                                                       
    while(i < c.size() && !puzzle_ready(c[i].candidate))
        {
            cout << "start while loop "<< i << endl;
            Puzzle p = c[i].candidate;
            cout << "current" << endl;
            show_state(max_width, max_depth, c[i].candidate.board);
            int v = i;
            if(can_go_north(p))
                tries (c, i, north (p));
            if(can_go_south(p ) && i == v)
                tries (c, i, south (p));
            if(can_go_west(p ) && i == v)
                tries (c, i, west (p));
            if(can_go_east(p) && i == v)
                tries (c, i, east (p));
            //        
            show_state(max_width, max_depth, c[i].candidate.board);

            cout << "Size = " << size(c) << endl;
        }
        if(i < c.size())
        {
            cout << "Solution found" << endl;
            show_path(c, i) ;
        }
        else
            cout << "whut";

}

void solve_d(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depthy);

void tries_d( vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depthy) //                  
{
    Puzzle p = attempt[size(attempt)-1];
    Puzzle newp= move_empty(p, next);
    if (!puzzle_present(newp, attempt))
    {
        attempt.push_back(newp);   //        
        solve_d(attempt, shortest, max_depthy);
        attempt.pop_back();        //       
    }
}

void solve_d( vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depthy) //                  
{
    const int CURRENT = size(attempt);
    const int BEST = size(shortest);
    Puzzle p = attempt[CURRENT-1] ;
    if(BEST > 0 && CURRENT>= BEST)
    {
        return;
    }
    else if(CURRENT> max_depthy+1)
    {
        return;
    }
    else if(puzzle_ready(p))
    {
        shortest= attempt;
        return;
    }
    if(can_go_north(p))
        tries_d(attempt, north(p), shortest,  max_depthy);
    if(can_go_south(p))
        tries_d(attempt, south(p), shortest,  max_depthy);
    if(can_go_west(p))
        tries_d(attempt, west  (p), shortest,  max_depthy);
    if(can_go_east(p))
        tries_d(attempt, east(p), shortest,  max_depthy);
}

int read_file(int& x, int& y, char world[max_width][max_depth])
{
//               
    assert (true) ;
/*                 
                                                                              
                                                                                                 
                                        
*/
    string filename = "challenge.25.txt";
    ifstream file (filename.c_str());
    if (!file)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    char c;
    int a = 0;
    while (file)
    {
        file.get(c);
        if (c == '\n')
        {
            y++;
            a = 0;
        }
        else
        {
            world[a][y] = c;
            a++;
            x = a;
        }
    }
    file.close();
    return x;
}

int main()
{
    int x = 0;
    int y = 0;
    read_file(x, y, world);
    const int width = x;
    const int depth = y;
    show_state(width, depth, world);
    Puzzle p;
    memcpy(p.board, world, max_width*max_depth);
    int a;
    int b;
    position_worker(world, a, b);
    p.open.col = a;
    p.open.row = b;
    solve(p);
    return 0;
}

