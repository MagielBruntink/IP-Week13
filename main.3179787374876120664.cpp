#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                                                       
//                                                 

/*                                                                                                                                
                                                                                                       
                                                                                                  */

int rows, columns;

struct Puzzles
{
    char p [20][20];
};

struct Pos
{
    int row, col;
};

void puzzle_in (ifstream& in, Puzzles& puzzle)
{
    //             
    assert(in.is_open());
    //                                           
    char a;
    int row=0;
    int column=0;
    in.get(a);
    int n=0;
    while (in)
    {

       while (a!='\n')
    {

        puzzle.p[row][column]=a;
        column++;
        if (n<column)
            n=column;
        in.get(a);
    }
    column=0;
    in.get(a);
    row ++;
    }
    columns=n;
    rows=row;
}

void show (Puzzles& puzzle)
{
    //             
    assert(true);
    //                                             
    for (int i=0;i<rows;i++)
    {
        for (int j=0;j<columns;j++)
        {
            cout<<puzzle.p[i][j];
        }
        cout<<endl;
    }

}

void findw (Puzzles& puzzle, Pos& w)
{
    assert(true)
    //                                        
    for (int i=0; i<rows;i++)
        for (int j=0;j<columns;j++)
        {
           if(puzzle.p[i][j]=='w'||puzzle.p[i][j]=='W')
            {
                w.col=j;
                w.row=i;
                return;
            }
        }
}

bool puzzle_ready (Puzzles& puzzle)
{
    //             
    assert(true);
    //                                                                      
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++)
            if(puzzle.p[i][j]=='b')
                return false;
    return true;
}

bool box_check (Puzzles& puzzle, int r, int c, char d)
{
    //              
    assert(true);
    //                                                                  
    //                             
    if (puzzle.p[r][c]=='b'|| puzzle.p[r][c]=='B')
    {
        switch (d)
        {
        case 'n':{ if (puzzle.p[r-1][c]=='b'|| puzzle.p[r-1][c]=='B'||puzzle.p[r-1][c]=='*')
                        return false;}
        case 's':{ if (puzzle.p[r+1][c]=='b'|| puzzle.p[r+1][c]=='B'||puzzle.p[r+1][c]=='*')
                        return false;}
        case 'w':{ if (puzzle.p[r][c-1]=='b'|| puzzle.p[r][c-1]=='B'||puzzle.p[r][c-1]=='*')
                        return false;}
        case 'e':{ if (puzzle.p[r][c+1]=='b'|| puzzle.p[r][c+1]=='B'||puzzle.p[r][c+1]=='*')
                        return false;}
        }

    }
    return true;
}

bool can_go_north (Puzzles& puzzle)
{
    //             
    assert(true);
    //                                                      
    Pos w;
    findw(puzzle,w);
    if(puzzle.p[w.row-1][w.col]=='*' || !box_check(puzzle,w.row-1,w.col,'n'))
    {
        return false;
    }
    return true;

}

bool can_go_south (Puzzles& puzzle)
{
    //             
    assert(true);
    //                                                      
    Pos w;
    findw(puzzle,w);
    if(puzzle.p[w.row+1][w.col]=='*' || !box_check(puzzle,w.row+1,w.col,'s'))
        return false;
    return true;

}

bool can_go_west (Puzzles& puzzle)
{
    //             
    assert(true);
    //                                                     
    Pos w;
    findw(puzzle,w);
    if(puzzle.p[w.row][w.col-1]=='*' || !box_check(puzzle,w.row,w.col-1,'w'))
        return false;
    return true;

}

bool can_go_east (Puzzles& puzzle)
{
    //             
    assert(true);
    //                                                     
    Pos w;
    findw(puzzle,w);
    if(puzzle.p[w.row][w.col+1]=='*' || !box_check(puzzle,w.row,w.col+1,'e'))
        return false;
    return true;

}

Pos north (Puzzles& puzzle)
{
    Pos w;
    findw(puzzle,w);
    w.row-=1;
    return w;

}

Pos south (Puzzles& puzzle)
{
    Pos w;
    findw(puzzle,w);
    w.row+=1;
    return w;

}

Pos west (Puzzles& puzzle)
{
    Pos w;
    findw(puzzle,w);
    w.col-=1;
    return w;

}

Pos east (Puzzles& puzzle)
{
    Pos w;
    findw(puzzle,w);
    w.col+=1;
    return w;

}

bool puzzle_present(Puzzles puzzle, vector<Puzzles>& c)
{
    for(int i=0;i<c.size();i++)
    {
        bool is_present=true;
        for(int j=0;j<rows;j++)
            for(int k=0;k<columns;k++)
                if(puzzle.p[j][k]!=c[i].p[j][k])
                    is_present=false;
        if(is_present) return is_present;
    }
    return false;
}

Puzzles move_worker (Puzzles& puzzle, Pos next)
{
    Pos old_w;
    findw(puzzle,old_w);
    if (puzzle.p[next.row][next.col]!='b' && puzzle.p[next.row][next.col]!='B')
    {
        if (puzzle.p[old_w.row][old_w.col]=='w')
        puzzle.p[old_w.row][old_w.col]=' ';
        if (puzzle.p[old_w.row][old_w.col]=='W')
        puzzle.p[old_w.row][old_w.col]='.';
        if (puzzle.p[next.row][next.col]==' ')
        puzzle.p[next.row][next.col]='w';
        if (puzzle.p[next.row][next.col]=='.')
        puzzle.p[next.row][next.col]='W';
    }
    else
    {
        int d_row=next.row-old_w.row;
        int d_col=next.col-old_w.col;

        if (puzzle.p[next.row+d_row][next.col+d_col]==' ') {puzzle.p[next.row+d_row][next.col+d_col]='b';}
        if (puzzle.p[next.row+d_row][next.col+d_col]=='.') {puzzle.p[next.row+d_row][next.col+d_col]='B';}

        if (puzzle.p[next.row][next.col]=='b')             {puzzle.p[next.row][next.col]='w';}
        if (puzzle.p[next.row][next.col]=='B')             {puzzle.p[next.row][next.col]='W';}

        if (puzzle.p[old_w.row][old_w.col]=='w') {puzzle.p[old_w.row][old_w.col]=' ';}
        if (puzzle.p[old_w.row][old_w.col]=='W') {puzzle.p[old_w.row][old_w.col]='.';}
    }
    return puzzle;
}

void solve(vector<Puzzles>& attempt,vector<Puzzles>& shortest, int max_depth);

void tries( vector<Puzzles>& attempt,Pos next,vector<Puzzles>& shortest,int max_depth)
{
    Puzzles p = attempt[attempt.size()-1] ;
    Puzzles newp= move_worker(p, next) ;
    if (!puzzle_present(newp, attempt))
    {
        attempt.push_back(newp) ; //        
        solve(attempt, shortest, max_depth) ;
        attempt.pop_back() ; //       
    }
}

void solve(vector<Puzzles>& attempt,vector<Puzzles>& shortest, int max_depth)
{
    //              
    assert(attempt.size()>0 && max_depth>=0);
    //                                                                                                                   
    const int CURRENT= attempt.size();
    const int BEST = shortest.size();
    Puzzles p = attempt[CURRENT-1];
    if(BEST > 0 && CURRENT>= BEST) return;
    else if(CURRENT> max_depth+1) return;
    else if(puzzle_ready(p))
        {
            shortest=attempt;
            return;
        }
    if(can_go_north(p)) tries(attempt, north(p), shortest, max_depth) ;
    if(can_go_south(p)) tries(attempt, south(p), shortest, max_depth) ;
    if(can_go_west(p))  tries(attempt, west (p), shortest, max_depth) ;
    if(can_go_east(p))  tries(attempt, east(p), shortest, max_depth) ;
}

int main()
{

    string name;
    cout<<"Enter the name of the file (without .txt)"<<endl;
    cin>> name;
    name=name+".txt";
    ifstream infile (name.c_str());
    Puzzles puzzle;
    vector<Puzzles> attempt,shortest;
    puzzle_in(infile, puzzle);
    attempt.push_back(puzzle);
    solve(attempt,shortest,30);
    for(int i=0;i<shortest.size();i++)
        show(shortest[i]);
    return 0;
}

/*             */

/*

                  

              
 
                    
  

          
 
                 
  

                
 
                      
                         
  

                                              
 
                   
                         
                                                 
           
              
                 
              
            
              
     

                       
         

                                    
                     
                         
                         
                      
         
                 
                  
               
     
              
             
 

                           
 
                   
                 
                                                   
                              
     
                                     
         
                                 
         
                   
     

 

                                    
 
                              
                                     
         
                                                        
             
                        
                        
                       
             
         

 

                                   
 
                   
                 
                                                                            
                             
                                    
                                   
                             
                
 

                                                      
 
                                                  
     
                  
         
                 
         
                                                                                      
                             
         
                 
         
                                                                                      
                             
         
                 
         
                                                                                      
                             
         
                 
         
                                                                                      
                             
         
         

     
                
 

                                   
 
                   
                 
                                                            
          
                    
                                    
                                                                             
                     
                

 

                                   
 
                   
                 
                                                            
          
                    
                                                                             
                     
                

 

                                  
 
                   
                 
                                                           
          
                    
                                                                             
                     
                

 

                                  
 
                   
                 
                                                           
          
                    
                                                                             
                     
                

 

                           
 
          
                    
             
             
 

                           
 
          
                    
             
             
 

                          
 
          
                    
             
             
 

                          
 
          
                    
             
             
 

                                              
 
              
                        
                                                                               
     
                                                
                                               
                                                
                                               
                                              
                                             
                                              
                                             
     
        
     
                                     
                                     
                                      
                                                          
                                                         
                                                          
                                                         
                                              
                                             
                                              
                                             

                                                
                                               
                                                
                                               
                                              
                                             
                                              
                                             

     
                  
 

                                                                
 
                          
     
                             
                                 
                                        
                                                          
                                     
                      
                              
     
                 
 

                                            
 
                    
            
               
        
     
                                           
                             
     
 

                                                  

                         
 
                                       
               
                        
                                          
     
                                   
                           
                                   
                           
                                   
                          
                                   
                          
                                  
                 
     
                   
                         
 

                                                 
 
                                
                                       
                               
                                    
                           
                           
 

          
 

                
                                                            
               
                     
                                   
                   
          
                    
                              
                 
              */

