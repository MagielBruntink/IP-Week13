//
//          
//                     
//
//                                 
//                                                 
//

#include <cstring>
#include <string>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

const int height = 6;
const int width = 5;

struct position
{
    int col, row;
};

struct Puzzle
{
    char world[height][width] =
    {
        {'*','*','*','*','\n'},
        {'*','w',' ','*','\n'},
        {'*',' ','b','*','\n'},
        {'*',' ',' ','*','\n'},
        {'*',' ','.','*','\n'},
        {'*','*','*','*','\n'}
    };
    position worker;
    position box;
    position destination;
};

Puzzle p;

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

int size(vector<Candidate> c)
{
    int sizec = static_cast<int>(c.size());
    return sizec;
}

int size(vector<Puzzle> c)
{
    int sizec = static_cast<int>(c.size());
    return sizec;
}

void show_world()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << p.world[i][j];
        }
    }
}

bool puzzle_ready (Puzzle p)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (p.world[i][j] == 'b')
                return false;
        }
    }
    return true;
}

bool puzzle_present_breadth(vector<Candidate>& c, int i, Puzzle p)
{
    for (int j=0; j < c.size(); j++)
    {
        if (c[j].candidate.world == p.world)
            return true;
    }
    return false;
}

bool puzzle_present_depth(Puzzle p, vector<Puzzle>& c)
{
    for (int j=0; j < size(c); j++)
    {
        if (c[j].world == p.world)
            return true;
    }
    return false;
}

void show_path(vector<Candidate>& c, int i)
{
    for (int a = 0; a<=i; a++)
    cout<<"("<<c[i].candidate.worker.col<<", "<<c[i].candidate.worker.row<<")"<<endl;
}

Puzzle move_worker (Puzzle p, position next)
{
    Puzzle p1 = p;
    int new_n, new_m;
    int counter = 0, position_worker = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (!(p.world[i][j] == 'w' || p.world[i][j] == 'W'))
            {
                counter++;
            }
            else
            {
                position_worker = counter; //                           
                if (p.world[i][j] == 'w')
                {
                    p1.world[i][j] = ' '; //                                
                }
                else
                {
                    p1.world[i][j] = '.'; //                                      
                }
            }
        }
    }
    
    int n, m;
    n = next.col;
    m = next.row;
    if (p.world[n][m] == ' ')
    {
        p1.world[n][m] = 'w';
    }
    else if (p.world[n][m] == '.')
    {
        p1.world[n][m] = 'W';
    }
    else if (p.world [n][m] == 'b')
    {
        p1.world[n][m] = 'w';
        position tempnew = next;
        new_n=tempnew.col;
        new_m=tempnew.row;
        
        if (p.world[new_n][new_m] == '.')
        {
            p1.world [new_n][new_m] = 'B';
        }
        else p1.world[new_n][new_m] = 'b';
    }
    else if (p.world [n][m] == 'B')
    {
        p1.world[n][m] = 'W';
        position tempnew = next;
        new_n = tempnew.col;
        new_m = tempnew.row;
        if (p.world[new_n][new_m] == '.')
        {
            p1.world [new_n][new_m] = 'B';
        }
        else (p1.world[new_n][new_m] = 'b');
    }
    return p1;
}

position north (Puzzle p)
{
    int posworker = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (p.world[i][j] != 'w' || p.world[i][j] != 'W')
                posworker++; //                                        
        }
    }
    position pnorth;
    pnorth.col = posworker % 5;
    pnorth.row = posworker / 6; //                                  
    return pnorth;
}

bool can_go_north (Puzzle p)
{
    int row, col;
    position tempn = north(p);
    col = tempn.col;
    row = tempn.row;
    if (p.world[col][row] == ' ' || p.world[col][row] == '.' || (p.world[col][row] == 'b' && (p.world [col][row - 1] == ' ' || p.world [col][row - 1] == '.')) || (p.world[col][row] == 'B' && (p.world [col][row - 1] == ' ' || p.world [col][row - 1] == '.'))) //                                                                                                         
    {
        return true;
    }
    else
        return false;
}

position south (Puzzle p)
{
    int posworker = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (p.world[i][j] != 'w' || p.world[i][j] != 'W')
                posworker++; //                                        
        }
    }
    position psouth;
    psouth.col = posworker % 5;
    psouth.row = (posworker + 12) / 6; //                                  
    return psouth;
}

bool can_go_south (Puzzle p)
{
    int row, col;
    position temps = south(p);
    col = temps.col;
    row = temps.row;
    if (p.world[col][row] == ' ' || p.world[col][row] == '.' || (p.world[col][row] == 'b' && (p.world [col][row + 1] == ' ' || p.world [col][row + 1] == '.')) || (p.world[col][row] == 'B' && (p.world [col][row + 1] == ' ' || p.world [col][row + 1] == '.'))) //                                                                                                         
    {
        return true;
    }
    else
        return false;
}

position west (Puzzle p)
{
    int posworker = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (p.world[i][j] != 'w' || p.world[i][j] != 'W')
                posworker++; //                                        
        }
    }
    position pwest;
    pwest.col = (posworker % 5) - 1;
    pwest.row = (posworker + 6) / 6; //                                  
    return pwest;
}

bool can_go_west (Puzzle p)
{
    int row, col;
    position tempw = west(p);
    col = tempw.col;
    row = tempw.row;
    if (p.world[col][row] == ' ' || p.world[col][row] == '.' || (p.world[col][row] == 'b' && (p.world [col - 1][row] == ' ' || p.world [col - 1][row] == '.')) || (p.world[col][row] == 'B' && (p.world [col - 1][row] == ' ' || p.world [col - 1][row] == '.'))) //                                                                                                        
    {
        return true;
    }
    else
        return false;
}

position east (Puzzle p)
{
    int posworker = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (p.world[i][j] != 'w' || p.world[i][j] != 'W')
                posworker++; //                                        
        }
    }
    position peast;
    peast.col = (posworker % 5) + 1;
    peast.row = (posworker + 6) / 6; //                                  
    return peast;
}

bool can_go_east (Puzzle p)
{
    int row, col;
    position tempe = east(p);
    col = tempe.col;
    row = tempe.row;
    if (p.world[col][row] == ' ' || p.world[col][row] == '.' || (p.world[col][row] == 'b' && (p.world [col + 1][row] == ' ' || p.world [col + 1][row] == '.')) || (p.world[col][row] == 'B' && (p.world [col + 1][row] == ' ' || p.world [col + 1][row] == '.'))) //                                                                                                        
    {
        return true;
    }
    else
        return false;
}

Puzzle move_empty (Puzzle p, position next)
{
    Puzzle p1 = p;
    int oldcol = p1.worker.col;
    int oldrow = p1.worker.row;
    p1.world[oldcol][oldrow] = ' ';
    p1.world[next.col][next.row] = 'w';
    return p1;
}

void tries_breadth_first (vector<Candidate>& c, int i, position next)
{
    Puzzle p = c[i].candidate;
    Puzzle newp = move_empty(p, next);
    Candidate newc = {newp, i};
    if (!puzzle_present_breadth (c, i, newp))
        c.push_back (newc) ;
}

void solve_breadth_first (Puzzle start)
{
    vector <Candidate> c = {{start, -1}};
    int i = 0;
    while((i < size(c)) && !puzzle_ready (c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if (can_go_north(p)) tries_breadth_first (c, i, north (p));
        if (can_go_south(p)) tries_breadth_first (c, i, south (p));
        if (can_go_east(p)) tries_breadth_first (c, i, east (p));
        if (can_go_west(p)) tries_breadth_first (c, i, west (p));
        i = i + 1;
    }
    if (i < size(c))
        show_path (c,i);
}

void solve (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);
void tries_depth_first (vector<Puzzle>& attempt, position next, vector<Puzzle>& shortest, int max_depth)
{
    Puzzle p = attempt[size(attempt)-1];
    Puzzle newp = move_empty (p, next);
    if (!puzzle_present_depth(newp, attempt))
    {
        attempt.push_back(newp);
        solve (attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void solve (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    const int CURRENT = size(attempt);
    const int BEST = size (shortest);
    Puzzle p = attempt[CURRENT-1];
    if (BEST > 0 && CURRENT >= BEST) { return ; }
        else if ( CURRENT > max_depth+1) {return ; }
            else if (puzzle_ready(p)) { shortest = attempt ; return ; }
        if (can_go_north(p)) tries_depth_first (attempt, north(p), shortest, max_depth);
        if (can_go_south(p)) tries_depth_first (attempt, south(p), shortest, max_depth);
        if (can_go_west(p)) tries_depth_first (attempt, west(p), shortest, max_depth);
        if (can_go_east(p)) tries_depth_first (attempt, east(p), shortest, max_depth);
}

int main()
{
    show_world();
    int answer;
    cout << "Solve this puzzle using:" << endl;
    cout << "1. Breadth-first search" << endl << "2. Depth-first search" << endl;
    cin >> answer;
    switch(answer)
    {
        case 1: solve_breadth_first (p);
            break;
        case 2:
            vector<Puzzle> attempt;
            vector<Puzzle> shortest;
            solve(attempt,shortest,9);
    }
}
/*
                                               
                                         
 */

