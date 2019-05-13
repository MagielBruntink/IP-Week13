#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                                                                     
//                                                                             
//                                                         

using namespace std;

const char WALL                              = '*' ;
const char EMPTY_CELL                        = ' ' ;
const char EMPTY_DESTINATION_CELL            = '.' ;
const char WORKER                            = 'w' ;
const char WORKER_DESTINATION                = 'W' ;
const char BOX                               = 'b' ;
const char BOX_DESTINATION                   = 'B';
int ROWS_COUNT;
int COLS_COUNT;
const int NO_OF_ROWS = 6;
const int NO_OF_COLS = 10;

int DESTINATION_COUNTER = 0;
/*
           
 
            
            
               
  
*/
struct Position
{
    int col, row;
};

struct Cell
{
    char board [NO_OF_ROWS][NO_OF_COLS];
    Position w;
};

/*
                     
 
                                           
                                        
  
*/

struct Candidate
{
    Cell candidate;
    int parent_candidate;
};

vector<Cell> destinations;

char pos (int row, int col, Cell p)
{
    //            
    assert(true);
    //                                                  

    return p.board[row][col];
}

void find_destinations (vector<Position>& destinations, Cell start)
{
    //            
    assert(true);
    //                                                                                                                
    //                                                                          

    for(int row = 1; row <= NO_OF_ROWS; row++)
    {
        for (int col = 1; col <= NO_OF_COLS; col++ )
        {
            if(start.board[row][col] ==  'B' || start.board[row][col] == 'W' || start.board[row][col] == '.')
            {
                Position position;
                position.col = col;
                position.row = row;
                destinations.push_back(position);
                DESTINATION_COUNTER++;
            }
        }

    }
}

bool puzzle_ready (Cell p, vector<Position>& destinations)
{
    //            
    assert(true);
    //                                                                                              
    for (int i = 0; i <= DESTINATION_COUNTER; i++)
    {
        if ((p.board[destinations[i].row][destinations[i].col] != 'W') ||
                (p.board[destinations[i].row][destinations[i].col] != 'B'))
            return false;
    }
    return true;
}
/*                                                      
                                     
 
                  
                 
                                                                  
                   
                    
     
                                   
                     
     
                 

                                           

 
*/
Cell north(Cell& p)
{
    //            
    assert(true);
    //                                         
    p.w.row -= 1;
}

Cell south(Cell& p)
{
    //            
    assert(true);
    //                                         
    p.w.row += 1;
}

Cell east(Cell& p)
{
    //            
    assert(true);
    //                                        
    p.w.col += 1;
}

Cell west(Cell& p)
{
    //            
    assert(true);
    //                                        
    p.w.col -= 1;
}

bool can_go_north(Cell p)
{
    //            
    assert(true);
    //                                                                                                                                                                             
    if ((pos(p.w.row - 1, p.w.col, p) != '*') ||
            (pos(p.w.row - 1, p.w.col, p) != 'b'))
    {
        return true;
    }
    if ((pos(p.w.row - 1, p.w.col, p) == 'b') &&
            (pos(p.w.row - 2, p.w.col, p) != '*') &&
            (pos(p.w.row - 2, p.w.col, p) != 'b') &&
            (pos(p.w.row - 2, p.w.col, p) != 'B'))
    {
        return true;
    }
    return false;
}

bool can_go_south(Cell p)
{
    //            
    assert(true);
    //                                                                                                                                                                             
    if ((pos(p.w.row + 1, p.w.col, p) != '*') ||
            (pos(p.w.row + 1, p.w.col, p) != 'b'))
    {
        return true;
    }
    if ((pos(p.w.row + 1, p.w.col, p) == 'b') &&
            (pos(p.w.row + 2, p.w.col, p) != '*') &&
            (pos(p.w.row + 2, p.w.col, p) != 'b') &&
            (pos(p.w.row + 2, p.w.col, p) != 'B'))
    {
        return true;
    }
    return false;
}

bool can_go_west(Cell p)
{
    //            
    assert(true);
    //                                                                                                                                                                            
    if ((pos(p.w.row, p.w.col - 1, p) != '*') ||
            (pos(p.w.row, p.w.col - 1, p) != 'b'))
    {
        return true;
    }
    if ((pos(p.w.row, p.w.col - 1, p) == 'b') &&
            (pos(p.w.row, p.w.col - 2, p) != '*') &&
            (pos(p.w.row, p.w.col - 2, p) != 'b') &&
            (pos(p.w.row, p.w.col - 2, p) != 'B'))
    {
        return true;
    }
    return false;
}

bool can_go_east(Cell p)
{
    //            
    assert(true);
    //                                                                                                                                                                            
    if ((pos(p.w.row, p.w.col + 1, p) != '*') ||
            (pos(p.w.row, p.w.col + 1, p) != 'b'))
    {
        return true;
    }
    if ((pos(p.w.row, p.w.col + 1, p) == 'b') &&
            (pos(p.w.row, p.w.col + 2, p) != '*') &&
            (pos(p.w.row, p.w.col + 2, p) != 'b') &&
            (pos(p.w.row, p.w.col + 2, p) != 'B'))
    {
        return true;
    }
    return false;
}

Cell move_empty(Cell& p, Cell next, int direction)
{
    //            
    assert(true);
    //                                                                    
    if(p.board[next.w.row][next.w.col] == 'b' && direction == 1)
    {
        (p.board[next.w.row - 1][next.w.col]) = 'b';
    }
    if(p.board[next.w.row][next.w.col] == 'b' && direction == 2)
    {
        (p.board[next.w.row + 1][next.w.col]) = 'b';
    }
    if(p.board[next.w.row][next.w.col - 1] == 'b' && direction == 3)
    {
        (p.board[next.w.row - 1][next.w.col]) = 'b';
    }
    if(p.board[next.w.row][next.w.col + 1] == 'b' && direction == 4)
    {
        (p.board[next.w.row - 1][next.w.col]) = 'b';
    }

    p.w.row = next.w.row;
    p.w.col = next.w.col;
}

bool operator== (Cell one, Cell two)
{
    return (one.board == one.board);
}

bool puzzle_present (vector<Candidate> c, int i, Cell new_p)
{
    //            
    assert(true);
    //                                                                                                          
    for (int j = 0; j < i; j++)
    {
        if(c[j].candidate == new_p)
            return true;
    }
}

void tries (vector<Candidate>& c, int i, Cell next, int direction)
{
    //            
    assert(true);
    //                                                                                                                                           
    Cell p = c[i].candidate;
    Cell new_p = move_empty (p, next, direction);
    Candidate new_c = {new_p,i};
    if(!puzzle_present(c,i,new_p))
    {
        c.push_back(new_c);
    }
}

void solve(Cell start)
{
    //            
    assert(true);
    //                                             
    Candidate starting;
    starting.candidate = start;
    starting.parent_candidate = -1;
    vector<Candidate> c;
    c.push_back(starting);

    int i = 0;
    while((i < c.size()) && (!puzzle_ready(c[i].candidate, destinations&)))
    {
        Cell p = c[i].candidate;
        if(can_go_north(p))
        {
            tries(c, i, north(p), 1);
        }
        if(can_go_south(p))
        {
            tries(c, i, south(p), 2);
        }
        if(can_go_west(p))
        {
            tries(c, i, west(p), 3);
        }
        if(can_go_east(p))
        {
            tries(c, i, east(p), 4);
        }
        i++;
    }
    if (i < c.size())
    {
        show_path(c, i);
    }
}

/*                              
                                     
 
                     
           

                     
                    
     
                         
                   
     

               
                                       
                                           

 
*/

bool read_puzzle_file (ifstream& inputfile, Cell& start)
{
    //            
    assert(inputfile.is_open());
    //                                                                                                  
    char c;
    int i = 0;

    while (inputfile)
    {
        for (int row = 1; row <= NO_OF_ROWS ; row++)
        {
            for (int col = 1; col <= NO_OF_COLS ; col++ )
            {
                inputfile.get(c);
                if (c == 'w')
                {
                    start.w.row = row;
                    start.w.col = col;
                }
                start.board[row][col] = c;
                i++;
            }

            inputfile.get(c);

        }
    }
    return true;
}
/*                              
                                        
 
                  
                 
                                                         
              

                                                       
     
                               
                                    
            
         
                         
                                    
                
         
     
 
*/
int main ()
{
    vector<Cell> puzzle;

    string infile = "challenge.1.b.txt" ;
    //                                        
    //                       
    ifstream inputfile (infile.c_str());

    if(inputfile.is_open())
    {
        count_rows(inputfile);
        inputfile.clear();
        inputfile.close();
        ifstream inputfile (infile.c_str());

        count_cols(inputfile);
        inputfile.clear();
        inputfile.close();
        ifstream inputfile2 (infile.c_str());

        read_puzzle_file(inputfile2, puzzle);
        print_puzzle(puzzle);
        pos(3,4,puzzle);
    }
    else
    {
        cout << "Something went wrong with opening the file :(" << endl;
    }

    return 0;
}

