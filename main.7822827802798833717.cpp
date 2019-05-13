/*  
                          
                 
                     
            
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
using namespace std;

typedef char Cell;

struct Pos
{ int col, row;
};

struct Puzzle
{
    vector<vector<Cell>> board;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

void load_puzzle(ifstream& infile, Puzzle& p, string f)
{ //             
    assert(true);
  //                                          
    infile.open(f.c_str());

    while(infile && !infile.eof())
    {
        string s;
        getline(infile, s, '\n');
        if(s == "") break;
        vector<Cell> row(s.begin(), s.end());
        p.board.push_back(row);
    }
    infile.close();
}

void print_puzzle(Puzzle p)
{ //             
    assert(true);
  //                               
    for (int i = 0; i < p.board.size(); i++)
    {
        for (int j = 0; j < p.board[0].size(); j++)
        {
            cout << p.board[i][j];
        }
        cout << endl;
    }
}

bool puzzle_ready (Puzzle p)
{ //             
    assert(true);
  //                                                                                  
    for (int i = 0; i < p.board.size(); i++)
    {
        for (int j = 0; j < p.board[0].size(); j++)
        {
            if (p.board[i][j] == '.' || p.board[i][j] == 'b' || p.board[i][j] == 'W')
                return false;
        }
    }
    return true;
}

bool same_puzzle(Puzzle p1, Puzzle p2)
{ //             
    assert(true);
  //                                                                      
    if ( (p1.board.size() != p2.board.size()) || p1.board[0].size() != p2.board[0].size() )
        return false;
    else{
        for (int i = 0; i < p1.board.size(); i++)
        {
            for (int j = 0; j < p1.board[0].size(); j++)
            {
                if (p1.board[i][j] != p2.board[i][j])
                    return false;
            }
        }
    }
    return true;
}

//                              
bool puzzle_present(vector<Candidate>& cs, int i, Puzzle p)
{ //             
    assert(true);
  //                                                                   
    for (int j = 0; j < cs.size(); j++)
    {
        if(same_puzzle(cs[j].candidate, p)) //                               
        {
            return true;
        }
    }
    return false;
}

//                              
bool puzzle_present(Puzzle p, vector<Puzzle>& c)
{ //             
    assert(true);
  //                                                            
    for (int i = 0; i < c.size(); i++)
    {
        if (same_puzzle(c[i], p)){
            return true;
        }
    }
    return false;
}

Pos find_worker(Puzzle p)
{ //             
    assert(true);
  //                                                  
    Pos w_pos;
    for (int i = 0; i < p.board.size(); i++)
    {
        for (int j = 0; j < p.board[0].size(); j++)
        {
            if (p.board[i][j] == 'w' || p.board[i][j] == 'W' )
            {
                w_pos.row = i;
                w_pos.col = j;
            }
        }
    }
    return w_pos;
}

Puzzle move_empty (Puzzle p, Pos next)
{ //             
    assert(true);
  //                                                                      
    Puzzle puzzle = p;
    Pos w_pos = find_worker(puzzle);

    //                                           
    if (puzzle.board[w_pos.row][w_pos.col] == 'W')
    {
        //                                   
        puzzle.board[w_pos.row][w_pos.col] = '.';
        //                             
        puzzle.board[next.row][next.col] = 'w';
    }
    else
    {
        //                                    

        //                             
        //                              
        if (puzzle.board[next.row][next.col] == '.')
        {
            puzzle.board[next.row][next.col] = 'W';
        }
        else if (puzzle.board[next.row][next.col] == 'B')
        {
            if (next.row < w_pos.row && next.col == w_pos.col)
            { //      
                if (puzzle.board[next.row-1][next.col] == '.')
                {
                     puzzle.board[next.row-1][next.col] = 'B';
                }
                else{
                    puzzle.board[next.row-1][next.col] = 'b';
                }
                puzzle.board[next.row][next.col] = 'W';
            }
            else if (next.row > w_pos.row && next.col == w_pos.col)
            { //      
                if (puzzle.board[next.row+1][next.col] == '.')
                {
                     puzzle.board[next.row+1][next.col] = 'B';
                }
                else{
                    puzzle.board[next.row+1][next.col] = 'b';
                }
                puzzle.board[next.row][next.col] = 'W';
            }
            else if (next.row == w_pos.row && next.col < w_pos.col)
            { //     
                if (puzzle.board[next.row][next.col-1] == '.')
                {
                     puzzle.board[next.row][next.col-1] = 'B';
                }
                else{
                    puzzle.board[next.row][next.col-1] = 'b';
                }
                puzzle.board[next.row][next.col] = 'W';
            }
            else if (next.row == w_pos.row && next.col > w_pos.col)
            { //     
                if (puzzle.board[next.row][next.col+1] == '.')
                {
                     puzzle.board[next.row][next.col+1] = 'B';
                }
                else{
                    puzzle.board[next.row][next.col+1] = 'b';
                }
                puzzle.board[next.row][next.col] = 'W';
            }
        }
        else if (puzzle.board[next.row][next.col] == 'b')
        {
            //             

            if (next.row < w_pos.row && next.col == w_pos.col)
            { //      
                if (puzzle.board[next.row-1][next.col] == '.')
                {
                     puzzle.board[next.row-1][next.col] = 'B';
                }
                else{
                    puzzle.board[next.row-1][next.col] = 'b';
                }
                puzzle.board[next.row][next.col] = 'w';
            }
            else if (next.row > w_pos.row && next.col == w_pos.col)
            { //      
                if (puzzle.board[next.row+1][next.col] == '.')
                {
                     puzzle.board[next.row+1][next.col] = 'B';
                }
                else{
                    puzzle.board[next.row+1][next.col] = 'b';
                }
                puzzle.board[next.row][next.col] = 'w';
            }
            else if (next.row == w_pos.row && next.col < w_pos.col)
            { //     
                if (puzzle.board[next.row][next.col-1] == '.')
                {
                     puzzle.board[next.row][next.col-1] = 'B';
                }
                else{
                    puzzle.board[next.row][next.col-1] = 'b';
                }
                puzzle.board[next.row][next.col] = 'w';
            }
            else if (next.row == w_pos.row && next.col > w_pos.col)
            { //     
                if (puzzle.board[next.row][next.col+1] == '.')
                {
                     puzzle.board[next.row][next.col+1] = 'B';
                }
                else{
                    puzzle.board[next.row][next.col+1] = 'b';
                }
                puzzle.board[next.row][next.col] = 'w';
            }
        }
        else
        {
            puzzle.board[next.row][next.col] = 'w';
        }

    }
    if (puzzle.board[w_pos.row][w_pos.col] != '.')
            puzzle.board[w_pos.row][w_pos.col] = ' ';
    return puzzle;
}

bool can_go_north (Puzzle p)
{ //             
    assert(true);
  //                                                                              
    Pos w_pos = find_worker(p);
    if (p.board[w_pos.row-1][w_pos.col] == '*'
        || (p.board[w_pos.row-1][w_pos.col] == 'b' && p.board[w_pos.row-2][w_pos.col] == '*')
        || (p.board[w_pos.row-1][w_pos.col] == 'b' && p.board[w_pos.row-2][w_pos.col] == 'b')
        || (p.board[w_pos.row-1][w_pos.col] == 'B' && p.board[w_pos.row-2][w_pos.col] == '*')
        || (p.board[w_pos.row-1][w_pos.col] == 'B' && p.board[w_pos.row-2][w_pos.col] == 'B')
        || (p.board[w_pos.row-1][w_pos.col] == 'b' && p.board[w_pos.row-2][w_pos.col] == 'B'))
        return false;
    else
        return true;
}

bool can_go_south (Puzzle p)
{ //             
    assert(true);
  //                                                                              
    Pos w_pos = find_worker(p);
    if (p.board[w_pos.row+1][w_pos.col] == '*'
        || (p.board[w_pos.row+1][w_pos.col] == 'b' && p.board[w_pos.row+2][w_pos.col] == '*')
        || (p.board[w_pos.row+1][w_pos.col] == 'b' && p.board[w_pos.row+2][w_pos.col] == 'b')
        || (p.board[w_pos.row+1][w_pos.col] == 'B' && p.board[w_pos.row+2][w_pos.col] == '*')
        || (p.board[w_pos.row+1][w_pos.col] == 'B' && p.board[w_pos.row+2][w_pos.col] == 'B')
        || (p.board[w_pos.row+1][w_pos.col] == 'b' && p.board[w_pos.row+2][w_pos.col] == 'B'))
        return false;
    else
        return true;
}

bool can_go_west (Puzzle p)
{ //             
    assert(true);
  //                                                                             
    Pos w_pos = find_worker(p);
    if (p.board[w_pos.row][w_pos.col-1] == '*'
        || (p.board[w_pos.row][w_pos.col-1] == 'b' && p.board[w_pos.row][w_pos.col-2] == '*')
        || (p.board[w_pos.row][w_pos.col-1] == 'b' && p.board[w_pos.row][w_pos.col-2] == 'b')
        || (p.board[w_pos.row][w_pos.col-1] == 'B' && p.board[w_pos.row][w_pos.col-2] == '*')
        || (p.board[w_pos.row][w_pos.col-1] == 'B' && p.board[w_pos.row][w_pos.col-2] == 'B')
        || (p.board[w_pos.row][w_pos.col-1] == 'b' && p.board[w_pos.row][w_pos.col-2] == 'B'))
        return false;
    else
        return true;
}

bool can_go_east (Puzzle p)
{ //             
    assert(true);
  //                                                                             
    Pos w_pos = find_worker(p);
    if (p.board[w_pos.row][w_pos.col+1] == '*'
        || (p.board[w_pos.row][w_pos.col+1] == 'b' && p.board[w_pos.row][w_pos.col+2] == '*')
        || (p.board[w_pos.row][w_pos.col+1] == 'b' && p.board[w_pos.row][w_pos.col+2] == 'b')
        || (p.board[w_pos.row][w_pos.col+1] == 'B' && p.board[w_pos.row][w_pos.col+2] == '*')
        || (p.board[w_pos.row][w_pos.col+1] == 'B' && p.board[w_pos.row][w_pos.col+2] == 'B')
        || (p.board[w_pos.row][w_pos.col+1] == 'b' && p.board[w_pos.row][w_pos.col+2] == 'B'))
        return false;
    else
        return true;
}

Pos north (Puzzle p)
{ //             
    assert(true);
  //                                                                        
    Pos w_pos = find_worker(p);
    w_pos.row = w_pos.row - 1;
    return w_pos;
}

Pos south (Puzzle p)
{ //             
    assert(true);
  //                                                                        
    Pos w_pos = find_worker(p);
    w_pos.row = w_pos.row + 1;
    return w_pos;
}

Pos west (Puzzle p)
{ //             
    assert(true);
  //                                                                       
    Pos w_pos = find_worker(p);
    w_pos.col = w_pos.col - 1;
    return w_pos;
}

Pos east (Puzzle p)
{ //             
    assert(true);
  //                                                                       
    Pos w_pos = find_worker(p);
    w_pos.col = w_pos.col + 1;
    return w_pos;
}

void show_path(vector<Candidate>& c, int i)
{ //             
    assert(true);
  //                                                                             
    if (i >= 0)
    {
        show_path(c, c[i].parent_candidate);
        print_puzzle(c[i].candidate);
    }
}

void show_solution(vector<Puzzle>& c)
{ //             
    assert(true);
  //                                                                             
    for (int i = 0; i < c.size(); i++)
    {
        print_puzzle(c[i]);
    }
}

void tries_bfs (vector<Candidate>& c, int i, Pos next)
{ //             
    assert(true);
  //                                                                       
 //                                                              
    Puzzle p = c[i].candidate;
    Puzzle newp = move_empty(p, next);
    Candidate newc = {newp, i};
    if (!puzzle_present(c, i, newp))
        c.push_back(newc);
}

void solve_bfs (Puzzle start)
{ //             
    assert(true);
  //                                           
    vector<Candidate> c = {{start, -1}};
    int i = 0;
    while (i < c.size() && !puzzle_ready (c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        //                
        cout << ".";
        if (can_go_north(p)) tries_bfs (c, i, north(p));
        if (can_go_south(p)) tries_bfs (c, i, south(p));
        if (can_go_west(p)) tries_bfs(c, i, west(p));
        if (can_go_east(p)) tries_bfs (c, i, east(p));
        i = i + 1;
    }
    if (i < c.size())
        show_path(c, i);
}

void solve_dfs (vector<Puzzle>&, vector<Puzzle>&, int);

void tries_dfs ( vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth )
{ //             
    assert(true);
  //                                                       
    Puzzle p = attempt[attempt.size()-1] ;
    Puzzle newp = move_empty (p, next) ;
    if (!puzzle_present (newp, attempt))
    {   attempt.push_back (newp) ;
        solve_dfs (attempt, shortest, max_depth) ;
        attempt.pop_back() ;
    }
}

void solve_dfs (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{ //             
    assert(!attempt.empty() && max_depth >= 0);
  //                                                                        
  //                                                                          
    const int CURRENT = attempt.size() ;
    const int BEST = shortest.size() ;
    Puzzle p = attempt[CURRENT-1] ;
    if (BEST > 0 && CURRENT >= BEST) { return ; }
    else if (CURRENT > max_depth+1) { return ; }
    else if (puzzle_ready (p)) { shortest = attempt ; return ; }

    if (can_go_north (p)) tries_dfs (attempt, north(p), shortest, max_depth) ;
    else if (can_go_south (p)) tries_dfs (attempt, south (p), shortest, max_depth) ;
    else if (can_go_west (p)) tries_dfs (attempt, west (p), shortest, max_depth) ;
    else if (can_go_east (p)) tries_dfs (attempt, east (p), shortest, max_depth) ;

}

int main()
{
    ifstream infile;
    string filename;
    cout << "Enter the file you want to open:\n" << endl;
    cin >> filename;

    Puzzle p;
    load_puzzle(infile, p, filename);

    while(true)
    {
        int choice;
        cout << "Choose what you want to do:\n";
        cout << "    1) Use Breadth-First Search (BFS)\n";
        cout << "    2) Use Depth-First Search (BFS)\n";
        cin >> choice;
        switch(choice)
        {
            case 1: solve_bfs(p);break;
            case 2:
                {
                    int depth;
                    cout << "Enter the value for max_depth:\n";
                    cin >> depth;
                    vector<Puzzle> shortest;
                    vector<Puzzle> attempt{p};
                    solve_dfs(attempt, shortest, depth);
                    show_solution(shortest);
                }
            default: break;
        }
    }

    return 0;
}

