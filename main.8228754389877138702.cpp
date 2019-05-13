#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>

/*
                    
                           

                                                                                                                     
                                                                  
             
*/

using namespace std;

vector<vector<char> > test = {{'*','*','*','*','*','*','*','*','*','*'},
                            {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                            {'*',' ','.','b','w',' ',' ',' ',' ','*'},
                            {'*',' ',' ','*','*','*','*',' ',' ','*'},
                            {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                            {'*','*','*','*','*','*','*','*','*','*'}};

struct Pos
{
    int col;
    int row;
};

struct Candidate
{
    vector<vector<char> > candidate;
    int parent_candidate;
};

Pos find_worker (vector<vector<char> >& p)
{
    //               
    assert (true);
    //                                                           
    Pos result;
    for (int i=0; i<p.size(); i++)
    {
        for (int j=0; j<p[i].size(); j++)
            if (p[i][j] == 'w' || p[i][j] == 'W')
                {
                    result.row = i;
                    result.col = j;
                    return result;
                }
    }
}

Pos north (vector<vector<char> > p)
{
    //               
    assert (true);
    //                                                                       
    Pos pos = find_worker(p);
    pos.col = pos.col;
    pos.row -= 1;
    return pos;
}

Pos south (vector<vector<char> > p)
{
    //               
    assert (true);
    //                                                                       
    Pos pos = find_worker(p);
    pos.col = pos.col;
    pos.row = pos.row+1;

    return pos;
}

Pos west (vector<vector<char> > p)
{
    //               
    assert (true);
    //                                                                      
    Pos pos = find_worker(p);
    pos.col = pos.col-1;
    pos.row = pos.row;
    return pos;
}

Pos east (vector<vector<char> > p)
{
    //               
    assert (true);
    //                                                                      
    Pos pos = find_worker(p);
    pos.col = pos.col+1;
    pos.row = pos.row;
    return pos;
}

bool can_go_north (vector<vector<char> >& p)
{
    //               
    assert (true);
    //                                                        
    int i,j;
    Pos pos = find_worker(p);
    i = pos.row;
    j = pos.col;
    if (p[i-1][j] == '*')
        return false;
    if (p[i-1][j] == 'b' || p[i-1][j] == 'B')
        if (p[i-2][j] == '*' || p[i-2][j] == 'b' || p[i-2][j] == 'B')
            return false;
    return true;
}

bool can_go_south (vector<vector<char> >& p)
{
    //               
    assert (true);
    //                                                        
    int i,j;
    Pos pos = find_worker(p);
    i = pos.row;
    j = pos.col;
    if (p[i+1][j] == '*')
        return false;
    if (p[i+1][j] == 'b' || p[i+1][j] == 'B')
        if (p[i+2][j] == '*' || p[i+2][j] == 'b' || p[i+2][j] == 'B')
            return false;
    return true;
}

bool can_go_west (vector<vector<char> >& p)
{
    //               
    assert (true);
    //                                                       
    int i,j;
    Pos pos = find_worker(p);
    i = pos.row;
    j = pos.col;
    if (p[i][j-1] == '*')
        return false;
    if (p[i][j-1] == 'b' || p[i][j-1] == 'B')
        if (p[i][j-2] == '*' || p[i][j-2] == 'b' || p[i][j-2] == 'B')
            return false;
    return true;
}

bool can_go_east (vector<vector<char> >& p)
{
    //               
    assert (true);
    //                                                       
    int i,j;
    Pos pos = find_worker(p);
    i = pos.row;
    j = pos.col;
    if (p[i][j+1] == '*')
        return false;
    if (p[i][j+1] == 'b' || p[i][j+1] == 'B')
        if (p[i][j+2] == '*' || p[i][j+2] == 'b' || p[i][j+2] == 'B')
            return false;
    return true;
}

bool puzzle_ready (vector<vector<char> >& p)
{
    //               
    assert (true);
    //                                                    
    for (int i=0; i<p.size(); i++)
    {
        for (int j=0; j<p[i].size(); j++)
            if (p[i][j] == '.' || p[i][j] == 'b' || p[i][j] == 'W')
                return false;
    }
    return true;
}

bool matches (vector<vector<char> >&p, vector<vector<char> >& c)
{
    //               
    assert (true);
    //                                                                      
    for (int i = 0; i<c.size(); i++)
    {
        for (int j = 0; j<c[i].size(); j++)
            if (!p[i][j] == c[i][j])
                return true;
    }
    return false;
}

bool puzzle_present(vector<vector<char> >&p, vector<Candidate>& c)
{
    //               
    assert (true);
    //                                                                         
    for (int i = 0; i<c.size(); i++)
    {
        if(matches(p, c[i].candidate))
           return true;
    }
    return false;
}

void next_move(vector<vector<char> >& p, Pos next)
{
    //              
    assert (!puzzle_ready(p));
    //                                                                                
    Pos work = find_worker(p);
    int x = next.row-work.row;
    int y = next.col-work.col;
    p[work.row][work.col] = ' ';
    if (p[next.row][next.col] == 'b' || p[next.row][next.col] == 'B')
        if (p[next.row+x][next.col+y] == '.')
             p[next.row+x][next.col+y] = 'B';
        else p[next.row+x][next.col+y] = 'b';
    if (p[next.row][next.col] == '.')
        p[next.row][next.col] = 'W';
    else p[next.row][next.col] = 'w';
}

void tries (vector<Candidate>& c, int i, Pos next)
{
    //               
    assert (true);
    //                                  
    vector<vector<char> > p = c[i].candidate ;
    next_move(p, next);
    Candidate newc = {p, i};
    if (!puzzle_present(p, c))
        c.push_back(newc);
}

void print_puzzle (vector<vector<char> > c)
{
    //               
    assert (true);
    //                                   
    for (int i = 0; i < c.size(); i++)
    {
        for (int j = 0; j < c[i].size(); j++)
            cout << c[i][j];
        cout << endl;
    }
}

void show_path (vector<Candidate>& c, int i) {
    //               
    assert (true);
    //                                              
    if (i < 0)
        return;
    else {
        show_path(c, c[i].parent_candidate);
        print_puzzle(c[i].candidate);
    }
}

void solve (vector<vector<char> >& start)
{
    //               
    assert (true);
    //                                  
    vector<Candidate> c = {{start, -1}} ;
    int i = 0;
    while (i < c.size() && !puzzle_ready (c[i].candidate))
    {
        vector<vector<char> > p = c[i].candidate;
        if (can_go_north (p)) tries (c, i, north (p));
        if (can_go_south (p)) tries (c, i, south (p));
        if (can_go_east (p)) tries (c, i, east (p));
        if (can_go_west (p)) tries (c, i, west (p));
        i = i+1;
    }
    if (i < c.size())
        show_path (c, i);
}

void tries_depthfirst ( vector<vector<char> >& attempt,  Pos next, vector<vector<char> >& shortest, int max_depth )
{
    vector<vector<char> > p = attempt[attempt.size()-1] ;
    next_move(p, next);
    newp =
    Puzzle newp = move_empty (p, next) ;
    if (!puzzle_present (newp, attempt))
    {
        attempt.push_back (newp) ;   //        
        solve (attempt, shortest, max_depth) ;
        attempt.pop_back () ;        //       
    }
}

void solve_depthfirst (vector<vector<char> >& attempt, vector<vector<char> >& best, int max_depth)
{
    //               
    assert (max_depth>=0);
    //                                                                           
    const int CURRENT = attempt.size();
    const int BEST = best.size();
    vector<vector<char> > p = attempt[CURRENT-1];
    if (BEST > 0 && CURRENT >= BEST)      { return ; }
    else if (CURRENT > max_depth+1)       { return ; }
    else if (puzzle_ready (p)) { shortest= attempt ; return ; }
    if (can_go_north (p)) tries (attempt, north (p), shortest, max_depth) ;
    if (can_go_south (p)) tries (attempt, south (p), shortest, max_depth) ;
    if (can_go_west  (p)) tries (attempt, west  (p), shortest, max_depth) ;
    if (can_go_east  (p)) tries (attempt, east  (p), shortest, max_depth) ;
}

int main()
{
    solve(test);
    cout << "Hello world!" << endl;
    return 0;
}

