#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
using namespace std;

//                       
//                   

//       

const char WALL_CELL            = '*';
const char EMPTY_CELL           = ' ';
const char EMPTY_D_CELL         = '.';
const char W_EMPTY_CELL         = 'w';
const char W_EMPTY_D_CELL       = 'W';
const char B_EMPTY_CELL         = 'b';
const char B_EMPTY_D_CELL       = 'B';

struct Pos
{
    int col;
    int row;
};
struct Puzzle
{
    vector<vector<char>> puzzle;
    Pos worker;
};
struct Candidate
{
    vector<vector<char>> candidate;
    int parent_candidate;
};

vector<vector<char>> test_p = {{'*','*','*','*','*','*','*','*','*','*'},
                               {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                               {'*',' ','.','b','w',' ',' ',' ',' ','*'},
                               {'*',' ',' ','*','*','*','*',' ',' ','*'},
                               {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                               {'*','*','*','*','*','*','*','*','*','*'}};

int size (vector<char>& v)
{
    return static_cast<int>(v.size());
}

void show_config (vector<vector<char>>& vec)
{
    //              
    assert(true);

    //               
    //                                

    //                
    for ( int i = 0; i < vec.size(); i++ )
    {
        for ( int j = 0; j < vec[i].size(); j++)
        {
            cout << vec [i][j];
        }
        cout << endl;
    }
}

//       

bool puzzle_ready (vector<vector<char>>& vec)
{
    //              
    assert(true);

    //               
    //                                                                                                      

    //                
    int counter = 0;
    for ( int i = 0; i < vec.size(); i++ )
    {
        for ( int j = 0; j < vec[i].size(); j++)
        {
            if (vec [i][j] == '.')
            {
                counter++;
            }
        }

    }
    return counter==0;

}

bool puzzle_present (vector<Candidate>& c, vector<vector<char>>& vec)
{
    //              
    assert(true);

    //               
    //                                                                                                  

    //                
    for (int i = 0; i < c.size(); i++)
    {
        return c[i].candidate == vec;
    }

}

Puzzle move_worker (Puzzle p, Pos next)
{
    //              
    assert(true);

    //               
    //                                                    

    //               
    cout << "In move function" << endl;
    //                       
    //                        

    int i = next.col;
    int j = next.row;

    p.puzzle[p.worker.row][p.worker.col] = ' ';
    p.puzzle[p.worker.row + j][p.worker.col+i] = 'w';
    return p;

}

bool can_go_north (Puzzle p)
{
    //              
    assert(true);

    //               
    //                                                             

    //                

    if (p.worker.row-1 <= 0)
    {
        return false;
    }
    else if(p.puzzle[p.worker.row-1][p.worker.col]=='*')
    {
        return false;
    }
    else if (p.puzzle[p.worker.row-1][p.worker.col]=='b')
    {
        if (p.puzzle[p.worker.row-2][p.worker.col]=='*')
        {
            return false;
        }
    }
    else
    {
        return true;
    }

}

Pos north (Puzzle p)
{
    //              
    assert(true);

    //               
    //                                 

    //                
    Pos n;
    n.col = p.worker.col;
    n.row = p.worker.row-1;
    cout << n.col << n.row;
    return n;

}

bool can_go_south (Puzzle p)
{
    //              
    assert(true);

    //               
    //                                                             

    //                

    if (p.worker.row+1 >= p.puzzle.size())
    {
        return false;
    }
    else if(p.puzzle[p.worker.row+1][p.worker.col]=='*')
    {
        return false;
    }
    else if (p.puzzle[p.worker.row+1][p.worker.col]=='b')
    {
        if (p.puzzle[p.worker.row+2][p.worker.col]=='*')
        {
            return false;
        }
    }
    else
    {
        return true;
    }

}

Pos south (Puzzle p)
{
    //              
    assert(true);

    //               
    //                                 

    //                
    Pos s;
    s.col = p.worker.col;
    s.row = p.worker.row+1;
    return s;

}

bool can_go_west (Puzzle p)
{
    //              
    assert(true);

    //               
    //                                                            

    //                

    if (p.worker.col-1 <= 0)
    {
        cout << "False 0" << endl;
        return false;
    }
    else if(p.puzzle[p.worker.row][p.worker.col-1]=='*')
    {
        cout << "False 1" << endl;
        return false;
    }
    else if (p.puzzle[p.worker.row][p.worker.col-1]=='b')
    {
        if (p.puzzle[p.worker.row][p.worker.col-2]=='*')
        {
            cout << "False 2" << endl;
            return false;
        }
    }
    else
    {
        cout << "True" << endl;
        return true;
    }

}

Pos west (Puzzle p)
{
    //              
    assert(true);

    //               
    //                                

    //                
    Pos w;
    w.col = p.worker.col-1;
    w.row = p.worker.row;
    return w;

}

bool can_go_east (Puzzle p)
{
    //              
    assert(true);

    //               
    //                                                            

    //                

    if (p.worker.col+1 <= 0)
    {
        return false;
    }
    else if(p.puzzle[p.worker.row][p.worker.col+1]=='*')
    {
        return false;
    }
    else if (p.puzzle[p.worker.row][p.worker.col+1]=='b')
    {
        if (p.puzzle[p.worker.row][p.worker.col+2]=='*')
        {
            return false;
        }
    }
    else
    {
        return true;
    }

}

Pos east (Puzzle p)
{
    //              
    assert(true);

    //               
    //                                

    //                
    Pos e;
    e.col = p.worker.col+1;
    e.row = p.worker.row;
    return e;

}

void tries (vector<Candidate>& vec, int i, Pos next, Pos initial )
{
    //              
    assert(i >= 0 && next.col >= 0 && next.row >= 0);

    //               
    //                                 

    //                
    cout << "In tries function" << endl;
    Puzzle p;
    p.puzzle = vec[i].candidate;
    p.worker = initial;
    Puzzle new_p = move_worker(p, next);
    Candidate new_vec = {new_p.puzzle, i};
    if (!puzzle_present(vec, new_p.puzzle))
    {
        cout << "puzzle not present met" << endl;
        vec.push_back(new_vec);
    }

}

void breadth_first_search (Puzzle start)
{
    //              
    assert(true);

    //               
    //                                                  

    //                

    vector<Candidate> vec = {{start.puzzle, -1}};
    int index = 0;
    while ( index < vec[index].candidate.size() && !puzzle_ready(vec[index].candidate))
    {
        cout << "Condition met" << endl;
        Puzzle p;
        p.puzzle = vec[index].candidate;
        p.worker = start.worker;
        if(can_go_north(p))
        {
            cout << "1st if" << endl;
            tries(vec, index, north (p), p.worker);
            cout << "Tried" << endl;
        }
        if(can_go_south(p))
        {
            tries(vec, index, south(p), p.worker) ;
        }
        if(can_go_west(p))
        {
            tries(vec, index, west (p), p.worker) ;
        }
        if(can_go_east(p))
        {
            tries(vec, index, east(p), p.worker) ;
        }
        index = index+1;

    }

}

int main()
{
    Puzzle start;
    start.puzzle = test_p;
    start.worker.col = 4;
    start.worker.row = 2;
    show_config(test_p);
    breadth_first_search(start);
    cout << "This is a test" << endl;
    show_config(test_p);

    return 0;
}

