#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

/*          
                        
            */

enum  Cell{wall = 0, empty, destination, worker, worker_dest, box, box_dest , error};
enum  Direction{north, south, east, west};

const int MAX_ROWS = 20;
const int MAX_COLUMNS = 20;

int rows = 6;
int columns = 10;

struct Pos { int col, row;};

struct Puzzle {
    Cell board[MAX_ROWS][MAX_COLUMNS] =
            {{wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
             {wall, empty, empty, empty, empty, empty, empty, empty, empty, wall},
             {wall, empty, destination, box, worker, empty, empty, empty, empty, wall},
             {wall, empty, empty, wall, wall, wall, wall, empty, empty, wall},
             {wall, empty, empty, empty, empty, empty, empty, empty, empty, wall},
             {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall}
            };
    Pos worker_pos = {2,4};
    int open_dest = 1;
};
struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};
/*          
                        
            */

int size(vector<Candidate>& c)
{
    return c.size();
}

Cell char_to_cell(char c)
{
    assert(c == '*' || c == ' ' || c == '.' || c == 'W' || c == 'w' || c== 'b' || c =='B' || c == '?');
    //               
    //                                

    if(c == '*' )
        return wall;
    else if(c == ' ')
        return empty;
    else if(c == '.')
        return destination;
    else if(c == 'w')
        return worker;
    else if(c == 'W')
        return worker_dest;
    else if(c == 'b')
        return box;
    else if(c == 'B')
        return box_dest;
    else
        return error;
}

char cell_to_char(Cell cell)
{
    assert(true);
    //               
    //                               
    switch(cell)
    {
        case wall:
            return '*';
        case empty:
            return ' ';
        case destination:
            return '.';
        case worker:
            return 'w';
        case worker_dest:
            return 'W';
        case box:
            return 'b';
        case box_dest:
            return 'B';
        default:
            return '?';
    }
}

void show_puzzle(Puzzle puzzle, int& rows, int& columns)
{
    //              
    assert(true);
    char c;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            c = cell_to_char(puzzle.board[i][j]);
            cout << c;
        }
        cout << endl;
    }
}

/*
                                                 
 
                              
                     
                                                                

                         
     
                              
                            
                        
     
                 
 

                                                                                         
 
                              
                     
                                                
              
              
                 
                            
                      
                                   
     

                                            
         
                               
                  
                                                 
             
                              
                           
                             
                 
                                      

                 
                    
                 
                                           
                                                                
                       
                                                
                                                
                       
                                              
                                             
                                              
                                               
                        
                                
                 

             
                
         
                       
     
               
 

                     
 
                    
                                            
                           
                    
 
*/

/*                      
                        
                       */

bool can_go_north(Puzzle puzzle)
{
    Pos pos = {puzzle.worker_pos.row-1, puzzle.worker_pos.col};
    if(puzzle.board[pos.row][pos.col] == empty || puzzle.board[pos.row][pos.col] == destination)
        return true;
    else if(puzzle.board[pos.row][pos.col] == box)
    {
        if(puzzle.board[pos.row-1][pos.col] == empty|| puzzle.board[pos.row][pos.col] == destination)
            return true;
    }
    return false;

}

bool can_go_east(Puzzle puzzle)
{
    Pos pos = {puzzle.worker_pos.row, puzzle.worker_pos.col+1};
    if(puzzle.board[pos.row][pos.col] == empty || puzzle.board[pos.row][pos.col] == destination)
        return true;
    else if(puzzle.board[pos.row][pos.col] == box)
    {
        if(puzzle.board[pos.row][pos.col+1] == empty|| puzzle.board[pos.row][pos.col] == destination)
            return true;
    }
    return false;

}

bool can_go_south(Puzzle puzzle)
{
    Pos pos = {puzzle.worker_pos.row+1, puzzle.worker_pos.col};
    if(puzzle.board[pos.row][pos.col] == empty || puzzle.board[pos.row][pos.col] == destination)
        return true;
    else if(puzzle.board[pos.row][pos.col] == box)
    {
        if(puzzle.board[pos.row+1][pos.col] == empty|| puzzle.board[pos.row][pos.col] == destination)
            return true;
    }
    return false;

}

bool can_go_west(Puzzle puzzle)
{
    Pos pos = {puzzle.worker_pos.row, puzzle.worker_pos.col-1};
    if(puzzle.board[pos.row][pos.col] == empty || puzzle.board[pos.row][pos.col] == destination)
        return true;
    else if(puzzle.board[pos.row][pos.col] == box)
    {
        if(puzzle.board[pos.row][pos.col+1] == empty || puzzle.board[pos.row][pos.col] == destination)
            return true;
    }
    return false;

}

bool puzzle_ready(Puzzle puzzle)
{
    if(puzzle.open_dest == 0)
        return true;
    return false;
}

Pos pos_north(Puzzle puzzle)
{
    Pos pos;
    pos.row = puzzle.worker_pos.row-1;
    pos.col = puzzle.worker_pos.col;
    return pos;
}

Pos pos_east(Puzzle puzzle)
{
    Pos pos;
    pos.row = puzzle.worker_pos.row;
    pos.col = puzzle.worker_pos.col+1;
    return pos;
}

Pos pos_south(Puzzle puzzle)
{
    Pos pos;
    pos.row = puzzle.worker_pos.row+1;
    pos.col = puzzle.worker_pos.col;
    return pos;
}

Pos pos_west(Puzzle puzzle)
{
    Pos pos;
    pos.row = puzzle.worker_pos.row;
    pos.col = puzzle.worker_pos.col-1;
    return pos;
}

Puzzle move_worker(Puzzle puzzle, Pos next, Direction direction)
{
    Puzzle p;
    p.open_dest = puzzle.open_dest;
    p.worker_pos = next;
    if(puzzle.board[next.row][next.col] == box)
    {
        switch(direction)
        {
            case north:
                if(puzzle.board[next.row+1][next.col] == destination)
                {
                    p.board[next.row+1][next.col] = box_dest;
                    p.open_dest--;
                }
                else
                    p.board[next.row+1][next.col] = box;
                break;
            case east:
                if(puzzle.board[next.row][next.col+1] == destination)
                {
                    p.board[next.row][next.col+1] = box_dest;
                    p.open_dest--;
                }

                else
                    p.board[next.row][next.col+1] = box;
                break;
            case south:
                if(puzzle.board[next.row-1][next.col] == destination)
                {
                    p.board[next.row-1][next.col] = box_dest;
                    p.open_dest--;
                }

                else
                    p.board[next.row-1][next.col] = box;
                break;
            case west:
                if(puzzle.board[next.row][next.col-1] == destination)
                {
                    p.board[next.row][next.col-1] = box_dest;
                    p.open_dest++;
                }

                else
                    p.board[next.row][next.col-1] = box;
                break;
        }
    }
    return p;

}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle p, int& row, int& col)
{

    for (int j = 0; j < i; j++)
    {
        for (int k = 0; k < row; k++)
        {
            for (int l = 0; l < col; l++) {
                if(p.board[k][l] == c[j].candidate.board[k][l]){
                    return true;
                }

            }
        }
    }
    return false;
}

void show_path(vector<Candidate>& c, int i, int& row, int& col)
{

    for (int j = 0; j < i; j++)
    {
        for (int k = 0; k < row; k++)
        {
            for (int l = 0; l < col; l++) {
                cout << c[j].candidate.board[k][l];

            }
            cout <<endl;
        }
        cout <<endl;
    }
}

void tries(vector<Candidate>& c, int i, Pos next, Direction dir, int& row, int& col)
{
    Puzzle p = c[i].candidate;
    Puzzle newp = move_worker(p, next, dir);
    Candidate newc = {newp, i};
    if (!puzzle_present(c, i, newp, row, col))
        c.push_back(newc);
}

void solve(Puzzle start, int& row, int& col)
{
    vector<Candidate> c = {{start, -1}};
    int i =0;

    while( i < size(c) && !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if(can_go_north(p)) tries(c,i, pos_north(p), north, row, col);
        if(can_go_east(p)) tries(c,i,pos_east(p), east, row, col);
        if(can_go_south(p)) tries(c,i, pos_south(p), south, row, col);
        if(can_go_west(p)) tries(c,i,pos_west(p), west, row, col);
        i++;
    }
    if(i<size(c))
        show_path(c, i, row, col);
}

int main()
{

    Puzzle puzzle;

    cout << "amount of rows is " << rows<<endl;
    cout << "amount of columns is "<< columns<<endl;
    cout << "amount of destinations is " << puzzle.open_dest<<endl;
    show_puzzle(puzzle, rows, columns);

    solve(puzzle, rows, columns);
    return 0;
}
