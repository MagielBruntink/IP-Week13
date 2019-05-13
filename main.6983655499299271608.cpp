#include <iostream>
#include<fstream>
#include<cassert>
#include<vector>
//                                
//                         

using namespace std;

const int WIDTH =10 ;
const int HEIGHT = 6;

struct Pos
{
    int row,col;
};

struct Puzzle
{
    char board[HEIGHT][WIDTH];
    Pos worker;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

void find_worker(Puzzle& p);

void print_puzzle(Puzzle p)
{
    //            
    assert(true);
    //                                                   
    for(int i = 0; i<HEIGHT;i++)
       {
           for(int j=0; j<WIDTH;j++)
            {
                cout<<p.board[i][j];
            }
            cout<<endl;
       }
}

bool puzzle_ready(Puzzle p)
{
    //            
    assert(true);
    //                                                                         
     for(int i=1; i<HEIGHT-1 ; i++ )
       {
           for(int j=1; j<WIDTH-1; j++)
            {
               p.worker.row=i;
               p.worker.col=j;
               if(p.board[i][j]=='.' || p.board[i][j]=='W')
                return false;
            }
       }
       return true;
}

Puzzle move_worker(Puzzle& p, Pos next)
{
    //            
    assert(true);
    //                                                                                
    find_worker(p);
    if(p.board[p.worker.row][p.worker.col]='W')
    {
            if(p.board[next.row][next.col]=='.')
        {
            p.board[p.worker.row][p.worker.col]='.';
            p.worker.row=next.row;
            p.worker.col=next.col;
            p.board[p.worker.row][p.worker.col]='W';
        }
        else
        {
            p.board[p.worker.row][p.worker.col]='.';
            p.worker.row=next.row;
            p.worker.col=next.col;
            p.board[p.worker.row][p.worker.col]='w';
        }
    }

    else
    {
           p.board[p.worker.row][p.worker.col]=' ';
           p.worker.row=next.row;
           p.worker.col=next.col;
           p.board[p.worker.row][p.worker.col]='w';
    }

    return p;
}

bool can_go_north(Puzzle p)
{
    //            
    assert(true);
    //                                                   
    return p.board[p.worker.row - 1][p.worker.col]!='*' && p.board[p.worker.row - 1][p.worker.col]!='B';

}

Pos north(Puzzle p)
{
    //            
    assert(true);
    //                                                        
    Pos position;
    position.row=p.worker.row-1;
    position.col=p.worker.col;
    return position;
}

bool can_go_south(Puzzle p)
{
    //            
    assert(true);
    //                                                  
    return p.board[p.worker.row+1][p.worker.col]!='*' && p.board[p.worker.row+1][p.worker.col]!='B' ;
}

Pos south(Puzzle p)
{
    //            
    assert(true);
    //                                                   
    Pos position;
    position.row=p.worker.row+1;
    position.col=p.worker.col;
    return position;
}

bool can_go_west(Puzzle p)
{
    //            
    assert(true);
    //                                                  
    return p.board[p.worker.row][p.worker.col -1]!='*' && p.board[p.worker.row][p.worker.col -1]!='B' ;
}

Pos west(Puzzle p)
{
    //            
    assert(true);
    //                                             
    Pos position;
    position.row=p.worker.row;
    position.col=p.worker.col-1;
    return position;
}

bool can_go_east(Puzzle p)
{
    //            
    assert(true);
    //                                                      
    return p.board[p.worker.row][p.worker.col+1]!='*' && p.board[p.worker.row][p.worker.col+1]!='B';
}

Pos east(Puzzle p)
{
    //            
    assert(true);
    //                                                  
    Pos position;
    position.row=p.worker.row;
    position.col=p.worker.col +1;
    return position;
}

void find_worker(Puzzle& p)
{
    //            
    assert(true);
    //                                                      
    for(int i=0;i<HEIGHT;i++)
       {
           for(int j=0;j<WIDTH;j++)
           {
               if (p.board[i][j]=='w'|| p.board[i][j]=='W')
               {
                   p.worker.row=i;
                   p.worker.col=j;
               }
           }
       }
}

bool operator==(Pos p , Pos e)
{
   return p.row==e.row && p.col==e.col;
}

bool operator ==(Puzzle p, Puzzle e)
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int k = 0; k<WIDTH;k++)
        {
            if(p.board[i][k]!=e.board[i][k])
               return false;
        }
    }
    return true;
}

Puzzle push_box(Puzzle& p, Pos box) //                                       
{
    //            
    assert(true);
    //                                                                                                             
    if(box == north(p) && p.board[box.row -1][box.col]!='*' && p.board[box.row-1][box.col]!='B')
    {

        if(p.board[box.row -1][box.col]=='.')
            p.board[box.row -1][box.col]='B';
        else
        p.board[box.row-1][box.col]='b';
        if(p.board[box.row+1][box.col]=='w')
        {
            p.board[box.row+1][box.col]=' ';
            p.board[box.row][box.col]='w';
        }
        else if(p.board[box.row+1][box.col]=='W')
        {
            p.board[box.row+1][box.col]='.';
            p.board[box.row][box.col]='w';
        }
        else;
    }
    else if (box == south(p) && p.board[box.row+1][box.col]!='*' && p.board[box.row+1][box.col]!='B')
    {

        if(p.board[box.row+1][box.col]=='.')
            p.board[box.row+1][box.col]='B';
        else
            p.board[box.row+1][box.col]='b';

            if(p.board[box.row-1][box.col]=='w')
        {
            p.board[box.row-1][box.col]=' ';
            p.board[box.row][box.col]='w';
        }
        else if(p.board[box.row-1][box.col]=='W')
        {
            p.board[box.row-1][box.col]='.';
            p.board[box.row][box.col]='w';
        }
        else;
    }
    else if (box == east(p) && p.board[box.row][box.col+1]!='*' && p.board[box.row][box.col+1]!='B')
    {

        if(p.board[box.row][box.col+1]=='.')
            p.board[box.row][box.col+1]='B';
        else
            p.board[box.row][box.col+1]='b';

            if(p.board[box.row][box.col-1]=='w')
        {
            p.board[box.row][box.col-1]=' ';
            p.board[box.row][box.col]='w';
        }
        else if(p.board[box.row][box.col-1]=='W')
        {
            p.board[box.row][box.col-1]='.';
            p.board[box.row][box.col]='w';
        }
        else;
    }
    else if ( box == west(p) && p.board[box.row][box.col-1]!='*'&& p.board[box.row][box.col-1]!='B')
    {

        if(p.board[box.row][box.col-1]=='.')
            p.board[box.row][box.col-1]='B';
        else
            p.board[box.row][box.col-1]='b';

            if(p.board[box.row][box.col+1]=='w')
        {
            p.board[box.row][box.col+1]=' ';
            p.board[box.row][box.col]='w';
        }
        else if(p.board[box.row][box.col+1]=='W')
        {
            p.board[box.row][box.col+1]='.';
            p.board[box.row][box.col]='w';
        }
        else;
    }
    else
        return p;
    return p;
}

void show_path(vector<Candidate> c, int i)
{
    //            
    assert(i>=-1);
    //                                              
    if (i == -1)
        return;
    else
        {
            show_path(c, c[i].parent_candidate);
            print_puzzle(c[i].candidate);
            cout<<endl;
        }
}

bool puzzle_present(vector<Candidate>&c ,Puzzle p)
{
    //            
    assert(true);
    //                                                                         
    for(int l=0;l<c.size();l++)
    {
        if(c[l].candidate==p)
            return true;
    }
    return false;
}

void tries(vector<Candidate>& c , int i,Pos nxt)
{
    //            
    assert(i>=0);
    //                                                    
    Puzzle p = c[i].candidate;
    Puzzle newp;
    if (p.board[nxt.row][nxt.col]==' ' || p.board[nxt.row][nxt.col]=='.' )
       {
        newp=move_worker(p,nxt);
        Candidate newc ={newp,i};
        if(!puzzle_present(c,newp))
        c.push_back(newc);
       }
    else if (p.board[nxt.row][nxt.col]=='b' || p.board[nxt.row][nxt.col]=='.')
        {
            newp=push_box(p,nxt); //                                                            
            Candidate newc={newp,i};
            if(!puzzle_present(c,newp))
            c.push_back(newc);
        }
    else
        return;

}

bool puzzle_present(Puzzle p, vector<Puzzle>& c)
{
    //            
    assert(true);
    //                                                                         
    for(int l=0;l<c.size();l++)
    {
        if(c[l]==p)
            return true;
    }
    return false;
}

void show_solution(vector<Puzzle> c)
{
    //            
    assert(true);
    //                                                   
    for(int k=0;k<c.size();k++)
    {
        for(int i = 0; i<HEIGHT;i++)
       {
           for(int j=0; j<WIDTH;j++)
            {
                cout<<c[k].board[i][j];
            }
            cout<<endl;
       }
    }
}

void dfs(vector<Puzzle>& attempt , vector<Puzzle>& shortest , int max_depth);

void tries_dfs(vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth)
{
    //            
    assert(max_depth>=0);
    //                                                       

    Puzzle p= attempt[attempt.size()-1];

    if (p.board[next.row][next.col]==' ')
    {
        Puzzle newp= move_worker(p,next);
        if(!puzzle_present(newp, attempt))
            {
               attempt.push_back(newp);
               dfs(attempt,shortest,max_depth);
               attempt.pop_back();
            }
    }
    else if(p.board[next.row][next.col]=='b')
    {
        Puzzle newp= push_box(p,next);
        if(!puzzle_present(newp, attempt))
            {
                attempt.push_back(newp);
                dfs(attempt,shortest,max_depth);
                attempt.pop_back();
            }
    }
    else
        return;
}

void dfs(vector<Puzzle>& attempt , vector<Puzzle>& shortest , int max_depth)
{
    //            
    assert(max_depth>=0);
    //                                                
    find_worker(attempt[0]); //    
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle p = attempt[CURRENT-1];
    if(BEST>0 && CURRENT >= BEST)
        return;
    else if(CURRENT> max_depth +1)
        return;
    else if(puzzle_ready(p))
    {
        shortest=attempt;
        return;
    }

    if(can_go_north(p)){

        tries_dfs(attempt, north(p),shortest, max_depth);
    }

    if(can_go_south(p))
        tries_dfs(attempt , south(p), shortest,max_depth);
    if(can_go_west(p))
        tries_dfs(attempt , west(p), shortest,max_depth);
    if(can_go_east(p))
        tries_dfs(attempt,west(p),shortest,max_depth);

}

void bfs_search(Puzzle start)
{
    //            
    assert(true);
    //                                                                          
    find_worker(start);
    vector<Candidate> c={{start,-1}};
    int i=0;
    while(i<c.size() && !puzzle_ready(c[i].candidate))
    {
        Puzzle p=c[i].candidate;
        if(can_go_north(p))
            tries(c,i,north(p));
        if(can_go_south(p))
            tries(c,i,south(p));
        if(can_go_east(p))
            tries(c,i,east(p));
        if(can_go_west(p))
            tries(c,i,west(p));
        i=i+1;
    }
    if(i<c.size())
        show_path(c,i);
}

int main()
{
    //                          
    /*                       
                          
                
                                 
           
                               
     
                  
                                  
         
                      
                      
         
     
               
                              
                                
        
                                    
             
                              
             
                       
        
                
                                
        
                                   
                                 
        
                      
                      
                              
                            
                                         
                                 
                                
                                     
                               */
    return 0;
}

