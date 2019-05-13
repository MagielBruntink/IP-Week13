#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <math.h>
#include <tuple>
#include <cctype>
#include <locale>
#include <algorithm>

using namespace std;

//                               
const char Wall = '*';
const char Air = ' ';
const char Destination = '.';
const char Worker_A = 'w';
const char Worker_D = 'W';
const char box_A = 'b';
const char box_D = 'B';

const int West=-2;
const int East=2;
const int South=-1;
const int North=1;
const int WIDTH= 10;                               //                                                                
const int HEIGHT= 6;                              //                                                                
//                                
//                                
//                               
//                               
//                               
//                               

int teller=0;

struct Pos{int col; int row;};
struct Puzzle{ char board [HEIGHT][WIDTH] ;Pos open ;  } ;
struct Candidate{ Puzzle candidate ;int parent_candidate;};

void solve2( vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);
void tries2( vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depth);

bool operator == (const Puzzle& p1, const Puzzle& p2)
{
    //                                                                                                                                
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            if (p1.board[i][j]!=p2.board[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

void ask_filename(string& filename)
{
    cout << "What filename do you want to enter?" << endl;
    cin >> filename;
}

void read_file(Puzzle& world)
{
    //               
    assert(true);
    /*                
                                                                                                                                                  
                            
    */
    ifstream infile;
    string filename;
    ask_filename(filename);
    infile.open(filename.c_str());
    char c;
    for (int i=0; i<HEIGHT; i++)
	{
		for (int j=0; j<WIDTH; j++)
		{
            infile.get(c);
            if (c==Worker_A|| c==Worker_D)
            {
                world.open.col=j;
                world.open.row=i;
            }
            if (c==10)
            {
                infile.get(c);
                world.board[i][j]=c;
            }
            else
            {
                world.board[i][j]=c;
            }
		}
	}
	infile.close();
}

void show_world (Puzzle world)
{
    //               
    assert(true);
    /*                
                                                          
    */
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            cout << world.board[i][j];
            if (j==WIDTH-1)
            {
                cout << endl;
            }
        }
    }
}
/*
                                 
 
                             
                           
                                     
     
                    
     
        
     
                     
     
 

                                 
 
                             
                           
                                     
     
                    
     
        
     
                     
     
 

                                
 
                           
                             
                                     
     
                    
     
        
     
                     
     
 

                                
 
                           
                             
                                     
     
                    
     
        
     
                     
     
 

                                 
 
                             
                           
                                     
     
                    
     
        
     
                     
     
 

                                 
 
                             
                           
                                     
     
                    
     
        
     
                     
     
 

                                
 
                           
                             
                                     
     
                    
     
        
     
                     
     
 

                                
 
                           
                             
                                     
     
                    
     
        
     
                     
     
 
*/
bool can_go_north(Puzzle world)
{
    //               
    assert(true);
    /*                
                                                                                                                                                                    
                                                      
    */
    int row=world.open.row-1;
    int col=world.open.col;
    if (world.board[row][col]==Wall)
    {
        return false;
    }
    if ((world.board[row][col]==box_A || world.board[row][col]==box_D) && (world.board[row-1][col]==Wall || world.board[row-1][col]==box_A ||world.board[row-1][col]==box_D))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool can_go_south(Puzzle world)
{
    //               
    assert(true);
    /*                
                                                                                                                                                                    
                                                      
    */
    int row=world.open.row+1;
    int col=world.open.col;
    if (world.board[row][col]==Wall)
    {
        return false;
    }
    if ((world.board[row][col]==box_A || world.board[row][col]==box_D) && (world.board[row+1][col]==Wall || world.board[row+1][col]==box_A ||world.board[row+1][col]==box_D))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool can_go_east(Puzzle world)
{
    //               
    assert(true);
    /*                
                                                                                                                                                                  
                                                     
    */
    int row=world.open.row;
    int col=world.open.col+1;
    if (world.board[row][col]==Wall)
    {
        return false;
    }
    if ((world.board[row][col]==box_A || world.board[row][col]==box_D) && (world.board[row][col+1]==Wall || world.board[row][col+1]==box_A ||world.board[row][col+1]==box_D))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool can_go_west(Puzzle world)
{
    //               
    assert(true);
    /*                
                                                                                                                                                                  
                                                     
    */
    int row=world.open.row;
    int col=world.open.col-1;
    if (world.board[row][col]==Wall)
    {
        return false;
    }
    else if ((world.board[row][col]==box_A || world.board[row][col]==box_D) && (world.board[row][col-1]==Wall || world.board[row][col-1]==box_A ||world.board[row][col-1]==box_D))
    {
        return false;
    }
    else
    {
        return true;
    }
}

Pos north(Puzzle world)
{
    //               
    assert(can_go_north(world));
    /*                
                                                                                    
    */
    //               
    assert(can_go_north(world));
    //                
    int row=world.open.row-1;
    int col=world.open.col;
    Pos next={col,row};
    return next;
}

Pos south(Puzzle world)
{
    //               
    assert(can_go_south(world));
    /*                
                                                                                    
    */
    int row=world.open.row+1;
    int col=world.open.col;
    Pos next={col,row};
    return next;
}

Pos east(Puzzle world)
{
    //               
    assert(can_go_east(world));
    /*                
                                                                                   
    */
    int row=world.open.row;
    int col=world.open.col+1;
    Pos next={col,row};
    return next;
}

Pos west(Puzzle world)
{
    //               
    assert(can_go_west(world));
    /*                
                                                                                   
    */
    int row=world.open.row;
    int col=world.open.col-1;
    Pos next={col,row};
    return next;
}

bool valid_pos(Pos check)
{
    //               
    assert(true);
    /*                
                                                                                                                                       
    */
    if (check.col<0 || check.row<0 || check.col>WIDTH || check.row>HEIGHT)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool check_destination (Puzzle world, Pos check)
{
    //               
    assert(true);
    /*                
                                                                                                   
    */
    int row=check.row;
    int col=check.col;
    if (world.board[row][col]==Destination)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Puzzle move_worker(Puzzle world, Pos next, int direction)
{
    //               
    assert(valid_pos(next)&& (direction==South || direction==North ||direction==East || direction==West));
    /*                
                                                                                                                                                             
                                                                                                      
    */
    int col=world.open.col;
    int row=world.open.row;
    if (world.board[row][col]==Worker_D)
    {
        world.board[row][col]=Destination;
    }
    else
    {
        world.board[row][col]=Air;
    }
    col=next.col;
    row=next.row;
    //                                                                           
    if (world.board[row][col]==box_D)
    {
        world.board[row][col]=Destination;
    }
    if (world.board[row][col]==box_A || world.board[row][col]==box_D)
    {
        if (direction==North)
        {
            Pos check={col,row-1};
            if (check_destination(world, check))
            {
                world.board[row-1][col]=box_D;
            }
            else
            {
                world.board[row-1][col]=box_A;
            }
        }
        else if (direction==East)
        {
            Pos check={col+1,row};
            if (check_destination(world, check))
            {
                world.board[row][col+1]=box_D;
            }
            else
            {
                world.board[row][col+1]=box_A;
            }
        }
        else if (direction==South)
        {
            Pos check={col,row+1};
            if (check_destination(world, check))
            {
                world.board[row+1][col]=box_D;
            }
            else
            {
                world.board[row+1][col]=box_A;
            }
        }
        else if (direction==West)
        {
            Pos check={col-1,row};
            if (check_destination(world, check))
            {
                world.board[row][col-1]=box_D;
            }
            else
            {
                world.board[row][col-1]=box_A;
            }
        }
    }
    //          
    //                                                                             
    if (!check_destination(world, next))
    {
        world.board[row][col]=Worker_A;
    }
    else
    {
        world.board[row][col]=Worker_D;
    }
    world.open=next;
    return world;
}

bool puzzle_ready (Puzzle world)
{
    //               
    assert(true);
    /*                
                                                                                                           
    */
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            if (world.board[i][j]==Worker_D || world.board[i][j]==box_A || world.board[i][j]== Destination)
            {
                return false;
            }
        }
    }
    return true;
}

void show_path(vector<Candidate>& all_worlds, int i)
{
    //               
    assert(i>=-1);
    /*                
                                                                                   
    */
    if (i<0)
    {
        cout << "Your puzzle has been solved, the solution is above" << endl;
    }
    else
    {
        show_world(all_worlds[i].candidate);
        cout << endl;
        teller++;
        show_path(all_worlds, all_worlds[i].parent_candidate);
    }
}

bool check_box_A_next_to_wall(Puzzle p, Pos check)
{
    //               
    assert(valid_pos(check));
    /*                
                                                                                                                          
    */
    int i=check.col;
    int j=check.row;
    if (p.board[i-1][j]==Wall || p.board[i+1][j]==Wall || p.board[i][j-1]==Wall || p.board[i][j+1]==Wall)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool one_worker(Puzzle p)
{
    //               
    assert(true);
    /*                
                                                                               
    */
    int counter=0;
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            if (p.board[i][j]==Worker_A ||p.board[i][j]==Worker_D)
            {
                counter++;
            }
        }
    }
    if (counter==1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void delete_other_workers(Puzzle p)
{
    //               
    assert(true);
    /*                
                                                                                                       
    */
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            if (p.board[i][j]==Worker_A ||p.board[i][j]==Worker_D)
            {
                if (p.open.col!=j || p.open.row!=i)
                {
                    p.board[i][j]==Air;
                }
            }
        }
    }
}

int count_boxes(Puzzle p)
{
    //               
    assert(true);
    /*                 
                                                                             
    */
    int counter=0;
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            if (p.board[i][j]==box_A || p.board[i][j]==box_D)
            {
                counter++;
            }
        }
    }
    return counter;
}

bool check_box_A_in_corner(Puzzle p)
{
    //               
    assert(true);
    /*                
                                                                                                                               
                                                                                                             
    */
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            int counter=0;
            if (p.board[i][j]==box_A)
            {
                Pos check={i,j};
                if (p.board[i-1][j]==Wall)
                {
                    counter++;
                }
                else if ((p.board[i-1][j]==box_A || p.board[i-1][j]==box_D) && (check_box_A_next_to_wall(p, check) && check_box_A_next_to_wall(p,{i-1,j})))
                {
                    counter ++;
                }
                if (p.board[i+1][j]==Wall)
                {
                    counter++;
                }
                else if ((p.board[i+1][j]==box_A || p.board[i+1][j]==box_D) && (check_box_A_next_to_wall(p, check) && check_box_A_next_to_wall(p,{i+1,j})))
                {
                    counter ++;
                }
                if (p.board[i][j-1]==Wall)
                {
                    counter++;
                }
                else if ((p.board[i][j-1]==box_A || p.board[i][j-1]==box_D) && (check_box_A_next_to_wall(p, check) && check_box_A_next_to_wall(p,{i,j-1})))
                {
                    counter ++;
                }
                if (p.board[i][j+1]==Wall)
                {
                    counter++;
                }
                else if ((p.board[i][j+1]==box_A || p.board[i][j+1]==box_D) && (check_box_A_next_to_wall(p, check) && check_box_A_next_to_wall(p,{i,j+1})))
                {
                    counter ++;
                }
                if (counter>=2)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle p)
{
    //               
    assert(i>=-1);
    /*                
                                                                                                                                                     
         
    */
    if (i<0)
    {
        return false;
    }
    else
    {
        if (p==c[i].candidate)
        {
            return true;
        }
        puzzle_present(c, i-1, p);
    }
}

void tries(vector<Candidate>&  c, int i, Pos next, int direction)
{
    //               
    assert(i>=0 && valid_pos(next) && (direction==West || direction==South || direction==North || direction==East));
    /*                
                                                                                                                                                            
                                                      
    */
    Puzzle p = c[i].candidate;
    Puzzle newp= move_worker(p, next, direction);
    Candidate newc=  {newp, i};
    show_world(newp);
    if (!puzzle_present(c, i, newp) && !check_box_A_in_corner(newp) )
    {
        c.push_back(newc) ;
    }
}

void solver(Puzzle start)
{
    //               
    assert(true);
    /*                
                                                                                                                                              
                                                                                                                                 
    */
    vector<Candidate> c= {{start,-1}} ;
    int i = 0 ;
    while (i  < c.size() && !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if(can_go_north(p))
        {
            (tries(c, i, north(p), North));
        }
        if(can_go_east(p))
        {
            (tries(c, i, east(p), East));
        }
        if(can_go_west(p ))
        {
            (tries(c, i, west(p), West));
        }
        if(can_go_south(p ))
        {
            (tries(c, i, south(p), South));
        }
        i=i+1;
    }
    if(i <c.size())
    {
        cout << "These are the steps to the solution" << endl;
        show_path(c, i);
        cout << "This solution consists of: " << teller << " steps." << endl;
    }
    else
    {
        cout << "No solution found!" << endl;
    }
}

/*                                                                                  
                                                          
 
                         
                                                                                              
                      
                                                                                                                                                             
                                                                                                      

                           
                           
                              
                 
                 
                                                                                 
                                                                     
     
                         
         
                                  
                                                
             
                                              
             
                
             
                                              
             
         
                              
         
                                  
                                                
             
                                              
             
                
             
                                              
             
         
                               
         
                                  
                                                
             
                                              
             
                
             
                                              
             
         
                               
         
                                  
                                                
             
                                              
             
                
             
                                              
             
         
     
                
                                   
                    
                 
 

                                                         
 
                     
                 
                      
                                                                                                                                                     
         

            
     
                     
     
        
     
                    
         
                        
         
                                   
     
 

                                                                                                        
 
                                         
                                                  
                                                        
     
                                             
                                              
                                             
     
 

                                                                              
 
                                       
                                     
                                  
                                  
     
               
     
                                  
     
               
     
                             
     
                          
               
     
                       
     
                                                           
     
                       
     
                                                            
     
                      
     
                                                              
     
                      
     
                                                           
     
 

*/

int main ()
{
    //                        
    Puzzle world;
    read_file(world);
    cout << "This is the starting world of this game:" << endl;
    show_world(world);
    cout << endl;
    if (check_box_A_in_corner(world))
    {
        cout << "This given world has no answer" << endl;
    }
    else
    {
        solver(world);
    }
    return 1;
}

