#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                                              
//                                          

const char wall='*';
const char empty_space=' ';
const char worker = 'w';
const char box_true= 'B';
const char box='b';
const int WIDTH=10;
const int HEIGHT=7;

struct Pos
{ int col, row ;
} ;

Pos position;

struct Puzzle
{ char board [WIDTH][HEIGHT] ;
  Pos open ;
} ;

struct Candidate
{ Puzzle candidate;
  int parent_candidate;
} ;

void put_together(Puzzle &start)
{
    assert(true);
    //                                                 
    char temp[HEIGHT][WIDTH] ={
                        {'*','*','*','*','*','*','*','*','*','*'},
                        {'*',' ',' ','w',' ',' ',' ',' ',' ','*'},
                        {'*',' ',' ','b',' ',' ',' ',' ',' ','*'},
                        {'*',' ',' ','.',' ',' ',' ',' ',' ','*'},
                        {'*',' ',' ','*','*','*','*',' ',' ','*'},
                        {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                        {'*','*','*','*','*','*','*','*','*','*'}
                            };

    for(int i = 0; i < HEIGHT; i++)
    {
        for(int y = 0; y < WIDTH; y++)
        {
            start.board[i][y] = temp[i][y];
        }
    }
}

Puzzle move_worker(Puzzle p, Pos next)
{
    assert(true);
    //                                                                   
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int y = 0; y < WIDTH; y++)
        {
            if(p.board[i][y] == 'w')
            {
                    if (p.board[next.row][next.col] == 'b')
                    {
                        if(p.board[(next.row - i)+next.row][(next.col - y)+next.col] == '.')
                        {
                            p.board[(next.row - i)+next.row][(next.col - y)+next.col] = 'B';
                        }
                        else p.board[(next.row - i)+next.row][(next.col - y)+next.col] == 'b';
                    }
                p.board[i][y] = ' ';

            }
        }
    }
    return p;
}

bool puzzle_ready(Puzzle p,int finish_num)
{
    assert(true);
    //                                                  
    int temp_count =0;
    for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                if(p.board[i][o]=='B')
                {
                    temp_count++;
                }

            }
    }
    if(finish_num==temp_count)
    {
        return true;
    }
    return false;

}

bool puzzle_present (vector<Candidate>& c,int i,Puzzle p)
{
    assert(true);
    //                                                                                            
    //                     
    int same = 0;
    for(int i = 0; i < c.size(); i++)
    {
        for(int q = 0; q < HEIGHT; q++)
        {
            for (int y = 0; y < WIDTH; y++)
            {
                if (c[i].candidate.board[q][y] == p.board[q][y])
                {
                    same++;
                }
            }
        }
        if (same == (HEIGHT*WIDTH))
        {
            return true;
        }
        same = 0;
    }
    return false;
}

bool puzzle_present_D (vector<Puzzle>& c,Puzzle p)
{
    assert(true);
    //                                                                                            
    //                     
    int same = 0;
    for(int i = 0; i < c.size(); i++)
    {
        for(int q = 0; q < HEIGHT; q++)
        {
            for (int y = 0; y < WIDTH; y++)
            {
                if (c[i].board[q][y] == p.board[q][y])
                {
                    same++;
                }
            }
        }
        if (same == (HEIGHT*WIDTH))
        {
            return true;
        }
        same = 0;
    }
    return false;
}

void tries(vector<Candidate>& c, int i, Pos next)
{
    assert(true);
    //                                                            
    Puzzle p = c[i].candidate ;
    Puzzle newp = move_worker(p, next);
    Candidate newc = {newp, i} ;
    if (!puzzle_present (c, i, newp))
        c.push_back (newc) ;

//                                   
//     
//                                      
//         
//                                               
//         
//                    
//     
}

Pos north(Puzzle p)
{
    assert(true);
    //                                                    
        for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                if(p.board[i][o]=='w')
                {
                    position.row = i-1;
                    position.col = o;
                    return position;
                }

            }
    }
}

Pos south(Puzzle p)
{
    assert(true);
    //                                                    
        for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                if(p.board[i][o]=='w')
                {
                    position.row = i+1;
                    position.col = o;
                    return position;
                }

            }
    }
}

Pos west(Puzzle p)
{
    assert(true);
    //                                                    
        for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                if(p.board[i][o]=='w')
                {
                    position.row = i;
                    position.col = o-1;
                    return position;
                }

            }
    }
}

Pos east(Puzzle p)
{
    assert(true);
    //                                                    
        for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                if(p.board[i][o]=='w')
                {
                    position.row = i;
                    position.col = o+1;
                    return position;
                }

            }
    }
}

bool can_go_north(Puzzle p)
{
    assert(true);
    //                                                                                   
    //                                                 
        for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                if(p.board[i][o]=='w')
                {
                    if(p.board[i-1][o]=='*')
                        return false;
                    if(p.board[i-1][o]=='b'&&p.board[i-2][o]=='b')
                        return false;
                    if(p.board[i-1][o]=='b'&&p.board[i-2][o]=='*')
                        return false;
                }

            }
    }

}

bool can_go_south(Puzzle p)
{
    assert(true);
    //                                                                                   
    //                                                 
        for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                if(p.board[i][o]=='w')
                {
                    if(p.board[i+1][o]=='*')
                        return false;
                    if(p.board[i+1][o]=='b'&&p.board[i+2][o]=='b')
                        return false;
                    if(p.board[i+1][o]=='b'&&p.board[i+2][o]=='*')
                        return false;
                }

            }
    }

}

bool can_go_west(Puzzle p)
{
    assert(true);
    //                                                                                  
    //                                                 
        for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                if(p.board[i][o]=='w')
                {
                    if(p.board[i][o-1]=='*')
                        return false;
                    if(p.board[i][o-1]=='b'&&p.board[i][o-2]=='b')
                        return false;
                    if(p.board[i][o-1]=='b'&&p.board[i][o-2]=='*')
                        return false;
                }

            }
    }

}
bool can_go_east(Puzzle p)
{
    assert(true);
    //                                                                                  
    //                                                 
        for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                if(p.board[i][o]=='w')
                {
                    if(p.board[i][o+1]=='*')
                        return false;
                    if(p.board[i][o+1]=='b'&&p.board[i][o+2]=='b')
                        return false;
                    if(p.board[i][o+1]=='b'&&p.board[i][o+2]=='*')
                        return false;
                }

            }
    }

}

void show_path (vector<Candidate>& c, int i)
{
    assert(true);
    //                                            
    int temp_num=0;
    while(i != 0)
    {
       i=c[i].parent_candidate;
       temp_num++;
    }
    cout << "The puzzle can be finished in " << temp_num << " step(s) using breadth first" <<endl;
}

void  breadth_first(Puzzle start,int finish_num)
{
    assert(true);
    //                                      
    vector<Candidate> c = {{start,-1}} ;
   int i = 0 ;
   while (i < c.size() && !puzzle_ready (c[i].candidate,finish_num))
   {
      Puzzle p = c[i].candidate ;
      if (can_go_north (p)) tries (c, i, north(p)) ;
      if (can_go_south (p))tries (c, i, south(p)) ;
      if (can_go_west  (p))tries (c, i, west(p)) ;
      if (can_go_east  (p)) tries (c, i, east(p)) ;
      i = i+1 ;
   }
   if (i < c.size())
	   show_path (c, i) ;
}

int finding_finish_states(Puzzle p)
{
    assert(true);
    //                                                                   
    int temp_count = 0;
    for(int i=0;i<HEIGHT;i++)
    {
            for(int o=0;o<WIDTH;o++)
            {
                //                             
                if(p.board[i][o]=='B'|| p.board[i][o]=='.')
                {
                    //                             
                    temp_count++;
                }

            }
    }
    return temp_count;
}

void tries_depth ( vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depth, int finish_num );

void depth_first ( vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth, int finish_num)
{
    assert(max_depth >= 0);
    //                                                                                                                   
   const int CURRENT = attempt.size();
   const int BEST    =  shortest.size() ;
   Puzzle p          = attempt[CURRENT-1] ;
   cout << BEST;
   if (BEST > 0 && CURRENT >= BEST)      { return ; }
   else if (CURRENT > max_depth+1)       { return ; }
   else if (puzzle_ready (p,finish_num)) { shortest = attempt ; return ; }
   if (can_go_north (p)) tries_depth (attempt, north (p), shortest, max_depth, finish_num) ;
   if (can_go_south (p)) tries_depth (attempt, south (p), shortest, max_depth, finish_num) ;
   if (can_go_west  (p)) tries_depth (attempt, west  (p), shortest, max_depth, finish_num) ;
   if (can_go_east  (p)) tries_depth (attempt, east  (p), shortest, max_depth, finish_num) ;

}

void tries_depth ( vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depth, int finish_num )
{
    assert(true);
    Puzzle p    = attempt[attempt.size()-1] ;
    Puzzle newp = move_worker(p,next) ;
    if (!puzzle_present_D (attempt, newp))
   {
       attempt.push_back (newp) ;   //        
       depth_first (attempt, shortest, max_depth,finish_num) ;
       attempt.pop_back () ;        //       
   }
}

int main()
{
   vector<Puzzle> attempt;
   vector<Puzzle> shortest;
   int max_depth = 80;
   Puzzle start;
   put_together(start);
   breadth_first(start,finding_finish_states(start));
   depth_first (attempt, shortest, max_depth, finding_finish_states(start));
}

