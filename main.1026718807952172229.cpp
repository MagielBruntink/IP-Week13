#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
//                                                          
/*
                                                                                                                           
  
*/
using namespace std;

vector <vector <char>> Puzzle = {{'*','*','*','*','*','*','*','*','*','*', '\n'},
{'*',' ',' ',' ',' ',' ','w',' ',' ','*', '\n'},
{'*','.','b',' ',' ',' ',' ',' ',' ','*', '\n'},
{'*',' ',' ','*','*','*','*',' ',' ','*', '\n'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ','*', '\n'},
{'*','*','*','*','*','*','*','*','*','*', '\n'}}
 ;
 struct Candidate {
vector <vector <char>> Posibility;
int parent_p;
 };

ifstream in_0 ("challenge.0.txt");
ifstream in_1a ("challenge.1.a.txt");
ifstream in_1b ("challenge.1.b.txt");
ifstream in_23 ("challenge.23.txt");
ifstream in_25 ("challenge.25.txt");
ifstream in_31 ("challenge.31.txt");
ifstream in_34 ("challenge.34.txt");

enum Cell {wall = '*', cell = ' ', dest = '.', worker = 'w', worker_dest = 'W', box = 'b', box_dest = 'B'};
struct Pos {int row, col;};

/*
                                                             
                  
                            
                 
                                 
     
                   
                    
               
                               
     
                                                           
 
*/
bool puzzle_ready (vector <vector <char>>  Puzzle)
{//               
    assert (true);
//                                                              
    for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
    {
        if(Puzzle[i][j] == box)
           return false;
    }

}
    return true;
}

bool puzzle_present (vector<Candidate>& c, int i, vector <vector <char>>  Puzzle )
{//              
    assert(i>= 0);
//                                                                   
    for (int j; j< static_cast<int>(c[i].Posibility.size()) ; j++)
        for (int k; k< static_cast<int> (c[i].Posibility.size()); k++)
        if(c[i].Posibility[j][k] != Puzzle[j][k])
             Puzzle[j][k] = c[i].Posibility[j][k];
}

void show_puzzle(vector <vector <char>>  Puzzle)
{//               
    assert (true);
//                                       
    for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        cout << Puzzle[i][j];
}

}

bool can_go_up (vector<vector<char>> p)
{//              
    assert(true);
//                                           
     for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        if(p[i][j] == worker || p[i][j]== worker_dest)
            return p[i-1][j] != wall;
}
}

Pos up (vector<vector<char>> p)
{//              
    assert(true);
//                                                     

     for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        if(p[i][j] == worker || p[i][j]== worker_dest)
           {
            Pos up = {i-1,j};
            return up;
           }
}
}

bool can_go_down (vector<vector<char>> p)
{//              
    assert(true);
//                                             
     for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        if(p[i][j] == worker || p[i][j]== worker_dest)
            return p[i+1][j] != wall;
}
}

Pos down (vector<vector<char>> p)
{//              
    assert(true);
//                                                     
     for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        if(p[i][j] == worker || p[i][j]== worker_dest)
            {
            Pos down = {i+1,j};
            return down;
           }
}
}

bool can_go_left (vector<vector<char>> p)
{//              
    assert(true);
//                                             
     for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        if(p[i][j] == worker || p[i][j]== worker_dest)
            return p[i][j-1] != wall;
}
}

Pos left (vector<vector<char>> p)
{//              
    assert(true);
//                                                     
     for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        if(p[i][j] == worker || p[i][j]== worker_dest)
            {
            Pos l = {i,j-1};
            return l;
           }
}
}

bool can_go_right (vector<vector<char>> p)
{//              
    assert(true);
//                                              
     for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        if(p[i][j] == worker || p[i][j]== worker_dest)
            return p[i][j+1] != wall;
}
}

Pos right (vector<vector<char>> p)
{//              
    assert(true);
//                                                     
     for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
{
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        if(p[i][j] == worker || p[i][j]== worker_dest)
            {
            Pos r = {i,j+1};
            return r;
           }
}
}

Pos working (vector<vector<char>> p)
{//              
    assert(true);
//                                          
    for (int  i = 0 ; i < static_cast<int> (Puzzle.size()) ; i++)
    for (int  j = 0 ; j < static_cast<int> (Puzzle[i].size()) ; j++)
        if(p[i][j] == worker || p[i][j]== worker_dest)
            {
            Pos r = {i,j};
            return r;
           }
}

bool swap_box(vector<vector<char>>& p, Pos next)
{//             
    assert(true);
//                                                                               
   Pos work = working(p);
   if (p[next.row+1][next.col] == box || p[next.row-1][next.col] == box || p[next.row][next.col+1] == box || p[next.row][next.col-1] == box )
        return false;
   else if (p[next.row+1][next.col] == wall || p[next.row-1][next.col] == wall || p[next.row][next.col+1] == wall || p[next.row][next.col-1] == wall )
        return false;
   else
   {
        if (next.row > work.row )
        {
            if(p[next.row+1][next.col] == dest)
                p[next.row+1][next.col] = box_dest;
            else
                p[next.row+1][next.col] = box;
        }
        else if (next.row < work.row )
            {
            if(p[next.row-1][next.col] == dest)
                p[next.row-1][next.col] = box_dest;
            else
                p[next.row-1][next.col] = box;
            }
        else if(next.col > work.col )
             {
            if(p[next.row][next.col+1] == dest)
                p[next.row][next.col+1] = box_dest;
            else
                p[next.row][next.col+1] = box;
            }
        else if(next.col < work.col )
            {
            if(p[next.row][next.col-1] == dest)
                p[next.row][next.col-1] = box_dest;
            else
                p[next.row][next.col-1] = box;
            }
        p[next.row][next.col] = p[work.row][work.col];
        p[work.row][work.col] = cell;
   }
}

vector<vector<char>> move_empty(vector<vector<char>>& p, Pos next)
{//              
    assert(true);
//                                                                  
    if (p[next.row][next.col] == cell)
    {
        Pos work = working(p);
        p[next.row][next.col] = p[work.row][work.col];
        p[work.row][work.col] = cell;

    }
    else if(p[next.row][next.col] == dest)
    {
        Pos work = working(p);
        p[next.row][next.col] = p[work.row][work.col];
        p[work.row][work.col] = dest;
    }
    else if(p[next.row][next.col] == box || p[next.row][next.col] == box_dest )
        swap_box(p, next);

    return p;
}

void show_path(vector <Candidate> c, int i)
{//               
    assert (true);
//                                       
    for (int j = 0; j < c.size(); j++)
    {
        show_puzzle(c[i].Posibility);
    }
}

void tries(vector<Candidate>& c, int i, Pos next)
{//              
    assert(true);
//                                                                                                
    vector<vector<char>> p = c[i].Posibility;
    vector<vector<char>> new_p = move_empty(p,next);
    Candidate new_c = {new_p, i};
    if(!puzzle_present(c,i,new_p))
        c.push_back(new_c);
}

void breadth_solve(vector<vector<char>> Puzzle)
{//              
    assert(true);
//                                                                     
    vector <Candidate> c = {{Puzzle,-1}} ;
    int  i=0;
    while(i< static_cast<int>(c.size())&& !puzzle_ready(c[i].Posibility))
    {
        vector<vector<char>> p = c[i].Posibility;
        if (can_go_up (p))
            tries(c,i, up(p));
        if (can_go_down (p))
            tries(c,i, down(p));
        if (can_go_left (p))
            tries(c,i, left(p));
        if (can_go_right (p))
            tries(c,i, right(p));
        i++;
    }

    if(i < static_cast<int>(c[i].Posibility.size()) && puzzle_ready(c[i].Posibility))
        show_path(c,i);
        show_puzzle(c[i].Posibility);

}

void depth_solve(vector<Candidate> attempt, vector<Candidate> shorty, int depth);

void try_again(vector<Candidate> attempt, vector<Candidate> shorty,int depth, Pos next)
{//              
    assert(true);
//                                                                                      
    vector<vector<char>> p = attempt [static_cast<int>(attempt.size())-1].Posibility;
    vector<vector<char>> new_p = move_empty(p,next);
    if(!puzzle_present(attempt, depth, new_p))
    {
        for (int  i = 0 ; i < static_cast<int> (attempt.size()) ; i++)
            attempt [i].Posibility = new_p;

        depth_solve (attempt, shorty, depth);
        for (int  i = 0 ; i < static_cast<int> (attempt.size()) ; i++)
            attempt [i].Posibility = {};
    }
}

void depth_solve(vector<Candidate> attempt, vector<Candidate> shorty, int depth)
{//              
    assert(true);
//                                                                                      
   const int CURRENT = static_cast<int>(attempt.size());
   const int BEST = static_cast<int>(shorty.size());
   vector<vector<char>> p = Puzzle;
   if(BEST > 0 && CURRENT >= BEST)
        return ;
    else if(CURRENT > depth +1)
        return;
    else if(puzzle_ready (p))
    {
        shorty = attempt;
        show_puzzle(shorty[0].Posibility);
        return;
    }
    if (can_go_up (p))
        try_again(attempt, shorty, depth, up(p));
    if (can_go_down (p))
        try_again(attempt, shorty, depth, down(p));
    if (can_go_left (p))
        try_again(attempt, shorty, depth, left(p));
    if (can_go_right (p))
        try_again(attempt, shorty, depth, right(p));

}

int main()
{
    vector<Candidate> attempt;
    vector<Candidate> shorty;
    int depth = 15;
   show_puzzle(Puzzle);

   breadth_solve(Puzzle);
   //                                  

    return 0;
}

