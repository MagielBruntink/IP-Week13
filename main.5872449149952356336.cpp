#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>

//                         
//                    
using namespace std;
/*
                     
                                         
                                   
                                     
                                                
                                
                                          
*/

const char WALL = '*';
const char EMPTY = ' ';
const char E_DEST = '.';
const char E_WORKER = 'w';
const char D_WORKER = 'W';
const char E_BOX = 'b';
const char D_BOX = 'B';

struct position {int row;
                 int column;
                };

vector<vector<char>> world;
typedef vector <vector<char>> Puzzle;
vector<Puzzle> attempt;
vector<Puzzle> shortest;
position pos;
const int MAX_DEPTH=1000;
int INDEX = 0;
int size(vector<char>& row)//                  
{
    assert(true);
    //                                                        
    return static_cast<int>(row.size());
}

int size(vector<vector<char>>& world)//                  
{
    assert(true);
    //                                                        
    return static_cast<int>(world.size());
}

int size(vector<Puzzle>& puzzle)//                  
{
    assert(true);
    //                                                        
    return static_cast<int>(puzzle.size());
}

void remove_elements(vector<char>& row)
{
    assert(true);
    //                                        
    for(int i = 0; i<size(row);i++)
    {
        row.pop_back();
    }
}

void remove_elements(vector<Puzzle>& attempts)
{
    assert(true);
    //                                        
    for(int i = 0; i<size(attempts);i++)
    {
        attempts.pop_back();
    }
}

bool read_file(string filename, vector<vector<char>>& world)
{
    assert(true);
    //                                                     
    ifstream infile;
    infile.open(filename);
    while(infile)
    {
        string line;
        vector<char> row;
        getline(infile, line);
        for(int i = 0; i < line.length() ;i++)
        {
            row.push_back(line[i]);

        }
        world.push_back(row);
    }
    infile.close();
    return true;
}

void show_world(vector<vector<char>>& world)
{
    assert(true);
    //                                                               
    for(int i = 0; i<size(world);i++)
    {
        for(int j = 0; j <size(world[i]);j++)
        {
            cout << world[i][j];
        }
        cout << endl;
    }
}

position find_pos(vector<vector<char>>& world)
{
    assert(true);
    //                                                 
    for(int i = 0; i < size(world); i++)
    {
        for(int j = 0; j <size(world[i]); j++)
        {
            if(world[i][j]==E_WORKER||world[i][j]==D_WORKER)
            {
                pos.row=i;
                pos.column=j;
                return pos;
            }
        }
    }
}

bool can_go_n(vector<vector<char>>& world)
{
    assert(true);
    //                                                                    
    pos=find_pos(world);
    if(world[pos.row-1][pos.column]==E_BOX||world[pos.row-1][pos.column]==D_BOX)
    {
        return (!(world[pos.row-2][pos.column]==WALL||world[pos.row-2][pos.column]==E_BOX||world[pos.row-2][pos.column]==D_BOX));
    }
    return (world[pos.row-1][pos.column]!=WALL);
}

bool can_go_s(vector<vector<char>>& world)
{
    assert(true);
    //                                                                    
    pos=find_pos(world);
    if(world[pos.row+1][pos.column]==E_BOX||world[pos.row+1][pos.column]==D_BOX)
    {
        return (!(world[pos.row+2][pos.column]==WALL||world[pos.row+2][pos.column]==E_BOX||world[pos.row+2][pos.column]==D_BOX));
    }
    return (world[pos.row+1][pos.column]!=WALL);
}

bool can_go_w(vector<vector<char>>& world)
{
    assert(true);
    //                                                                    
    pos=find_pos(world);
    if(world[pos.row][pos.column-1]==E_BOX||world[pos.row][pos.column-1]==D_BOX)
    {
        return (!(world[pos.row][pos.column-2]==WALL||world[pos.row][pos.column-2]==E_BOX||world[pos.row][pos.column-2]==D_BOX));
    }
    return (world[pos.row][pos.column-1]!=WALL);
}

bool can_go_e(vector<vector<char>>& world)
{
    assert(true);
    //                                                                    
    pos=find_pos(world);
    if(world[pos.row][pos.column+1]==E_BOX||world[pos.row][pos.column+1]==D_BOX)
    {
        return (!(world[pos.row][pos.column+2]==WALL||world[pos.row][pos.column+2]==E_BOX||world[pos.row][pos.column+2]==D_BOX));
    }
    return (world[pos.row][pos.column+1]!=WALL);
}

bool is_destination(vector<vector<char>>& world, int x, int y)
{
    assert(x<size(world)&&y<size(world[0]));
    //                                                               
    return world[x][y]==E_DEST;
}

char replace_chars(char now)
{
    assert(true);
    //                                                                                      
    switch(now)
    {
    case D_WORKER:
    case D_BOX: return E_DEST; break;
    case E_WORKER:
    case E_BOX: return EMPTY;
    }

}

void moving_n(vector<vector<char>>& world)
{
    assert(true);
    //                                                               
    find_pos(world);
    if(world[pos.row-1][pos.column]==D_BOX||world[pos.row-1][pos.column]==E_BOX)
    {
        if(is_destination(world, pos.row-2,pos.column))
            world[pos.row-2][pos.column]=D_BOX;
        else
            world[pos.row-2][pos.column]=E_BOX;
    }
    if(is_destination(world, pos.row-1,pos.column))
        world[pos.row-1][pos.column]=D_WORKER;
    else
        world[pos.row-1][pos.column]=E_WORKER;
    world[pos.row][pos.column]=replace_chars(world[pos.row][pos.column]);
}

void moving_s(vector<vector<char>>& world)
{
    assert(true);
    //                                                              
    find_pos(world);
    if(world[pos.row+1][pos.column]==D_BOX||world[pos.row+1][pos.column]==E_BOX)
    {
        if(is_destination(world, pos.row+2,pos.column))
            world[pos.row+2][pos.column]=D_BOX;
        else
            world[pos.row+2][pos.column]=E_BOX;
    }
    if(is_destination(world, pos.row+1,pos.column))
        world[pos.row+1][pos.column]=D_WORKER;
    else
        world[pos.row+1][pos.column]=E_WORKER;
    world[pos.row][pos.column]=replace_chars(world[pos.row][pos.column]);
}

void moving_e(vector<vector<char>>& world)
{
    assert(true);
    //                                                               
    find_pos(world);
    if(world[pos.row][pos.column+1]==D_BOX||world[pos.row][pos.column+1]==E_BOX)
    {
        if(is_destination(world, pos.row,pos.column+2))
            world[pos.row][pos.column+2]=D_BOX;
        else
            world[pos.row][pos.column+2]=E_BOX;
    }
    if(is_destination(world, pos.row,pos.column+1))
        world[pos.row][pos.column+1]=D_WORKER;
    else
        world[pos.row][pos.column+1]=E_WORKER;
    world[pos.row][pos.column]=replace_chars(world[pos.row][pos.column]);
}

void moving_w(vector<vector<char>>& world)
{
    assert(true);
    //                                                               
    find_pos(world);
    if(world[pos.row][pos.column-1]==D_BOX||world[pos.row][pos.column-1]==E_BOX)
    {
        if(is_destination(world, pos.row,pos.column-2))
            world[pos.row][pos.column-2]=D_BOX;
        else
            world[pos.row][pos.column-2]=E_BOX;
    }
    if(is_destination(world, pos.row,pos.column-1))
        world[pos.row][pos.column-1]=D_WORKER;
    else
        world[pos.row][pos.column-1]=E_WORKER;
    world[pos.row][pos.column]=replace_chars(world[pos.row][pos.column]);
}

bool solved(vector<vector<char>>& world)
{
    assert(true);
    //                                                  
    for(int i = 0; i<size(world);i++)
    {
        for(int j = 0; j <size(world[i]);j++)
        {
            if(world[i][j]==E_DEST||world[i][j]==D_WORKER)
                return false;
        }
    }
    return true;
}

void breadth_first(vector<vector<char>>& world,vector<Puzzle>& attempt)
{
    assert(true);
    //                                                          
    vector<Puzzle> candidates;
    int i = 0;
    attempt.push_back(world);
    while((!(solved(attempt[i])))&&i<=MAX_DEPTH)
    {
        //                       
        vector<vector<char>> newtry;
        if(can_go_n(attempt[i]))
        {
            newtry = attempt[i];
            moving_n(newtry);
            attempt.push_back(newtry);
        }
        if(can_go_s(attempt[i]))
        {
            newtry = attempt[i];
            moving_s(newtry);
            attempt.push_back(newtry);

        }
        if(can_go_e(attempt[i]))
        {
            newtry = attempt[i];
            moving_e(newtry);
            attempt.push_back(newtry);
        }
        if(can_go_w(attempt[i]))
        {
            newtry = attempt[i];
            moving_w(newtry);
            attempt.push_back(newtry);
        }
        i++;
        //               
    }
    cout << "Solved puzzle"<<endl<<endl;
    show_world(attempt[i]);
    cout <<endl<< "Length of path: " << i<<endl;
}

void depth_first(vector<vector<char>>& world, vector<Puzzle>&attempt, vector<Puzzle>&shortest);
//                                          

void tries(vector<vector<char>>& world, vector<Puzzle>&attempt, char direction)
{
    assert(true);
    //                                                                   
    if(direction == 'n')
    {
        moving_n(world);
        attempt.push_back(world);
        depth_first(world, attempt, shortest);
        attempt.pop_back();
    }
    if(direction=='s')
    {
        moving_s(world);
        attempt.push_back(world);
        depth_first(world, attempt, shortest);
        attempt.pop_back();
    }
    if(direction=='w')
    {
        moving_w(world);
        attempt.push_back(world);
        depth_first(world, attempt, shortest);
        attempt.pop_back();
    }
    if(direction=='e')
    {
        moving_e(world);
        attempt.push_back(world);
        depth_first(world, attempt, shortest);
        attempt.pop_back();
    }
}

void depth_first(vector<vector<char>>& world, vector<Puzzle>&attempt, vector<Puzzle>&shortest)
{
    assert(true);
    //                                 
    if(size(shortest)>0&&size(attempt)>=size(shortest))
    {
        return;
    }
    if(size(attempt)>MAX_DEPTH)
    {
        return;
    }
    if(solved(world))
    {
        shortest=attempt;
        return;
    }
    if(can_go_n(world))
    {
        tries(world, attempt, 'n');
    }
    if(can_go_s(world))
    {
        tries(world, attempt, 's');
    }
    if(can_go_e(world))
    {
        tries(world, attempt, 'e');
    }
    if(can_go_w(world))
    {
        tries(world, attempt, 'w');
    }
}

int main()
{
    read_file("challenge.1.b.txt", world);
    show_world(world);
    /*
                                  
                          
                                           
                    
                      
                    
                      
                    
                      
                    
                      
                    
                      
                        */
    //                                      
    //                                       
    breadth_first(world, attempt);
    return 0;
}

