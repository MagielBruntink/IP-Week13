#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//                                        
//                                           

const char Wall = '*';
const char EmptyCell = ' ';
const char EmptyDestCell = '.';
const char WorkeronEmptyCell = 'w';
const char WorkeronDestCell = 'W';
const char BoxonEmptyCell = 'b';
const char BoxonDestcell = 'B';

typedef vector<vector<char> > field;

field f = {{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}, {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
           {'*', 'B', ' ', ' ', ' ', ' ', ' ', ' ', 'w', '*'}, {'*', ' ', ' ', '*', '*', '*', '*', ' ', ' ', '*'},
           {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'}, {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}};

vector<field> que;
vector<field> candidate;

struct pos
{
    int col, row;
};

struct puzzle
{
    field f;
    int y = 2;
    int x = 8;
};

struct Candidate
{
    puzzle candidate;
    int parent_candidate;
};

puzzle p;

vector<Candidate> c = {{p, - 1}};

void print_map(field f)
{
    for(int i = 0; i < f.size(); i++)
    {
        for(int j = 0; j < f[i].size(); j++)
        {
            cout << f[i][j] << ' ';
        }
    cout << endl;
    }
}

bool puzzle_ready(puzzle p)
{

    for(int i = 0; i < f.size(); i++)
    {
        for(int j = 0; j < f[i].size(); j++)
        {
            if(f[i][j] == BoxonEmptyCell)
                return false;
        }
    }
   return true;
}

bool puzzle_present (vector<Cadnidate>& c, int i, puzzle p)
{
    if (c.candidate == p)
        return true;
    return false;

}

bool can_go_north(puzzle p)
{

    if (f[p.y][p.x] == WorkeronEmptyCell && f[p.y - 1][p.x] != Wall)
        return true;
    else if (f[p.y -1][p.x] == BoxonEmptyCell || f[p.y -1][p.x] == BoxonDestcell)
        {
            if (f[p.y-2][p.x] != Wall && f[p.y-2][p.x] != BoxonDestcell && f[p.y-2][p.x] != BoxonEmptyCell)
            {
                return true;
            }
        }
    return false;
}

bool can_go_south (puzzle p)
{
   if (f[p.y][p.x] == WorkeronEmptyCell && f[p.y+1][p.x] != Wall)
        return true;
    else if (f[p.y+1][p.x] == BoxonEmptyCell || f[p.y+1][p.x] == BoxonDestcell)
        {
            if (f[p.y+2][p.x] != Wall && f[p.y+2][p.x] != BoxonDestcell && f[p.y+2][p.x] != BoxonEmptyCell)
            {
                return true;
            }
        }
    return false;
}

bool can_go_east(puzzle p)
{
  if (f[p.y][p.x] == WorkeronEmptyCell && f[p.y+1][p.x] != Wall)
        return true;
    else if (f[p.y][p.x+1] == BoxonEmptyCell || f[p.y][p.x+1] == BoxonDestcell)
        {
            if (f[p.y][p.x+2] != Wall && f[p.y][p.x+2] != BoxonDestcell && f[p.y][p.x+2] != BoxonEmptyCell)
            {
                return true;
            }
        }
    return false;
}

bool can_go_west(puzzle p)
{
   if (f[p.y][p.x] == WorkeronEmptyCell && f[p.y-1][p.x] != Wall)
        return true;
    else if (f[p.y][p.x-1] == BoxonEmptyCell || f[p.y][p.x-1] == BoxonDestcell)
        {
            if (f[p.y][p.x-2] != Wall && f[p.y][p.x-2] != BoxonDestcell && f[p.y][p.x-2] != BoxonEmptyCell)
            {
                return true;
            }
        }
    return false;
}

void north (puzzle p)
{
    assert(can_go_north(p));

    if(f[p.y][p.x] == WorkeronEmptyCell)
        f[p.y][p.x] = EmptyCell;
    else if(f[p.y][p.x] == WorkeronDestCell)
            f[p.y][p.x] == EmptyDestCell;
    if( (f[p.y-1][p.x] == BoxonEmptyCell || f[p.y-1][p.x] == EmptyCell))
        f[p.y-1][p.x] = WorkeronEmptyCell;
    else if(f[p.y-1][p.x] == BoxonDestcell || f[p.y-1][p.x] == EmptyDestCell)
            f[p.y-1][p.x] == WorkeronDestCell;
    if(f[p.y-2][p.x] == EmptyCell && f[p.y-1][p.x] == BoxonEmptyCell)
        f[p.y-2][p.x] = BoxonEmptyCell;
    if(f[p.y-2][p.x] == EmptyDestCell && (f[p.y-1][p.x] == BoxonEmptyCell ||f[p.y-1][p.x] == BoxonDestcell ))
        f[p.y-2][p.x] == BoxonDestcell;
}

void south (puzzle p)
{
    assert(can_go_south(p));

    if(f[p.y][p.x] == WorkeronEmptyCell)
        f[p.y][p.x] = EmptyCell;
    else if(f[p.y][p.x] == WorkeronDestCell)
            f[p.y][p.x] == EmptyDestCell;
    if( (f[p.y+1][p.x] == BoxonEmptyCell || f[p.y+1][p.x] == EmptyCell))
        f[p.y+1][p.x] = WorkeronEmptyCell;
    else if(f[p.y+1][p.x] == BoxonDestcell || f[p.y+1][p.x] == EmptyDestCell)
            f[p.y+1][p.x] == WorkeronDestCell;
    if(f[p.y+2][p.x] == EmptyCell && f[p.y+1][p.x] == BoxonEmptyCell)
        f[p.y+2][p.x] = BoxonEmptyCell;
    if(f[p.y+2][p.x] == EmptyDestCell && (f[p.y+1][p.x] == BoxonEmptyCell ||f[p.y+1][p.x] == BoxonDestcell ))
        f[p.y+2][p.x] == BoxonDestcell;
}

void east (puzzle p)
{
    assert(can_go_east(p));

    if(f[p.y][p.x] == WorkeronEmptyCell)
        f[p.y][p.x] = EmptyCell;
    else if(f[p.y][p.x] == WorkeronDestCell)
            f[p.y][p.x] == EmptyDestCell;
    if( (f[p.y][p.x+1] == BoxonEmptyCell || f[p.y][p.x+1] == EmptyCell))
        f[p.y][p.x+1] = WorkeronEmptyCell;
    else if(f[p.y][p.x+1] == BoxonDestcell || f[p.y][p.x+1] == EmptyDestCell)
            f[p.y][p.x+1] == WorkeronDestCell;
    if(f[p.y][p.x+2] == EmptyCell && f[p.y][p.x+1] == BoxonEmptyCell)
        f[p.y][p.x+2] = BoxonEmptyCell;
    if(f[p.y][p.x+2] == EmptyDestCell && (f[p.y][p.x+1] == BoxonEmptyCell ||f[p.y][p.x+1] == BoxonDestcell ))
        f[p.y][p.x+2] == BoxonDestcell;
}
void west (puzzle p)
{
    assert(can_go_west(p));

    if(f[p.y][p.x] == WorkeronEmptyCell)
        f[p.y][p.x] = EmptyCell;
    else if(f[p.y][p.x] == WorkeronDestCell)
            f[p.y][p.x] == EmptyDestCell;
    if( (f[p.y][p.x-1] == BoxonEmptyCell || f[p.y][p.x-1] == EmptyCell))
        f[p.y][p.x-1] = WorkeronEmptyCell;
    else if(f[p.y][p.x-1] == BoxonDestcell || f[p.y][p.x-1] == EmptyDestCell)
            f[p.y][p.x-1] == WorkeronDestCell;
    if(f[p.y][p.x-2] == EmptyCell && f[p.y][p.x-1] == BoxonEmptyCell)
        f[p.y][p.x-2] = BoxonEmptyCell;
    if(f[p.y][p.x-2] == EmptyDestCell && (f[p.y][p.x-1] == BoxonEmptyCell ||f[p.y][p.x-1] == BoxonDestcell ))
        f[p.y][p.x-2] == BoxonDestcell;
}

void move_worker(puzzle p, pos next)
{
    assert(next.col >= 0 && next.row >= 0);

    if (next.col > p.x && next.row == p.y)
       east(p);
    else if (next.col < p.x && next.row == p.y)
            west(p);
    else if (next.col == p.x && next.row > p.y)
            south(p);
    else if (next.col == p.x && next.row < p.y)
            north(p);
}

void tries (vector<Candidate>& c, int i, pos next)
{
    puzzle p = c[i].candidate;
    puzzle newp = move_worker(p, next);
    Candidate newc = {newp, i};
    if (!puzzle_present(c,i, newp))
        c.push_back(newc);
}
void solve (puzzle start)
{

}

//                                                          

/*                                                   
 

                                    
                         
     
                                                                
                    
     

        
                     
 

                     
 
                      
                                                                          
                      

                                 
     
                                                                 
                                   
                    
     

                                    
                        

 
*/
/*                                                           
 
                   
                                                                                                              
                                                        
           

                                              
                                                      
                              
                                        
                          
                              

                            
                              
                                        
                              
                                   
                                        
                              
                                       
                                        
                              
                                           
                                        
                              
                                          
                                        
                              
                                       
                                        
                              
                                        
                                        
                              

                 

             
                                                                 
         
*/

int main()
{
    cout << "Hello! We will now test the functions." << endl;

    return 0;
}

