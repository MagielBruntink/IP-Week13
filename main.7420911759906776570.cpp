#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

//                           
//                       

const int COLUMN = 7;
const int ROW = 6;

struct Pos {int row, col;};

struct Puzzle
{ char board [ROW][COLUMN];
  Pos worker ;
} ;

struct Candidate
{ Puzzle candidate ;
  int parent_candidate ;
} ;

//                                                                 
//                                                                 
//                                                                 
//                                                                 
//                                                                 
//                                                                  
//                                                      

//                                                                 
//                                                                 
//                                                                 
//                                                                 
//                                                                 
//                                                                 
//                                                                  
//                                                      

Puzzle challenge23 = {{{'*','*','*','*','*','*','*'},
                       {'*','w',' ',' ',' ','*','*'},
                       {'*',' ','b','b',' ',' ','*'},
                       {'*',' ','*','.',' ','.','*'},
                       {'*',' ',' ',' ',' ',' ','*'},
                       {'*','*','*','*','*','*','*'}},
                       {1, 1}}; //                   

//                                                     
//                                                     
//                                                     
//                                                     
//                                                     
//                                                     
//                                                      
//                                                     

void show (char puzzle [ROW][COLUMN])
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                      
*/
    for (int i = 0; i < ROW; i++)
    {
        for (int k = 0; k < COLUMN; k++)
        {
            cout << puzzle[i][k];
        }
        cout << endl;
    }

}

int size (vector<Candidate>& v)
{//               
    assert(true);
/*                 
                                             
*/
    return static_cast<int>(v.size());
}

int size (vector<Puzzle>& v)
{//               
    assert(true);
/*                 
                                             
*/
    return static_cast<int>(v.size());
}

bool puzzle_ready (Puzzle p)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                                           
                                                          
                                                                
*/
    for (int i = 0; i < ROW; i++)
    {
        for (int k = 0; k < COLUMN; k++)
        {
            if (p.board[i][k] == 'b')
                return false;
        }
    }
    return true;
}

bool operator== (const Puzzle& a, const Puzzle& b)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int k = 0; k < COLUMN; k++)
        {
            if (a.board[i][k] != b.board[i][k])
                return false;
        }
    }
    return true;
}

bool puzzle_present (vector<Candidate>& c, Puzzle p)
{//               
    assert(size(c) >= 0 && ROW >= 0 && COLUMN >= 0);
/*                 
                                                     
                               
*/
    for (int i = 0; i < size(c); i++)
    {
        if (p == c[i].candidate)
            return true;
    }
    return false;
}

Puzzle move_worker (Puzzle p, Pos next)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                            
                                                    
                          
*/
    int row_direction = next.row - p.worker.row;
    int col_direction = next.col - p.worker.col;

    if (p.board[p.worker.row][p.worker.col] == 'w') //                    
        p.board[p.worker.row][p.worker.col] = ' ';
    else if (p.board[p.worker.row][p.worker.col] == 'W')
        p.board[p.worker.row][p.worker.col] = '.';

    p.worker = next;

    if (p.board[p.worker.row][p.worker.col] == ' ') //                                       
        p.board[p.worker.row][p.worker.col] = 'w';
    else if (p.board[p.worker.row][p.worker.col] == '.')
        p.board[p.worker.row][p.worker.col] = 'W';
    else if (p.board[p.worker.row][p.worker.col] == 'b')
    {
        p.board[p.worker.row][p.worker.col] = 'w';
        if ( p.board[p.worker.row+row_direction][p.worker.col+col_direction] == ' ') //                                    
            p.board[p.worker.row+row_direction][p.worker.col+col_direction] = 'b';
        else
            p.board[p.worker.row+row_direction][p.worker.col+col_direction] = 'B';
    }
    else if (p.board[p.worker.row][p.worker.col] == 'B')
    {
        p.board[p.worker.row][p.worker.col] = 'W';
        if ( p.board[p.worker.row+row_direction][p.worker.col+col_direction] == ' ') //                                    
            p.board[p.worker.row+row_direction][p.worker.col+col_direction] = 'b';
        else
            p.board[p.worker.row+row_direction][p.worker.col+col_direction] = 'B';
    }
    return p;
}

void show_path (vector<Candidate>& c, int i)
{//               
    assert(size(c) >= 0 && i >= -1);
/*                 
                                                 
                  
*/
    if (c[i].parent_candidate == -1)
        cout << "Path: ";
    else
    {
        show_path(c, c[i].parent_candidate);
        cout << i << " ";
    }
}

bool can_go_north (Puzzle p)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                                
                                             

*/
    if (p.worker.row-1 < 0)
        return false;

    char new_pos = p.board[p.worker.row-1][p.worker.col];

    if (new_pos == '*')
        return false;
    else if (new_pos == 'b' || new_pos == 'B')
        return p.board[p.worker.row-2][p.worker.col] == ' ' ||
               p.board[p.worker.row-2][p.worker.col] == '.';
    else
        return true;
}

bool can_go_south (Puzzle p)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                                
                                             
*/
    if (p.worker.row+1 >= ROW)
        return false;

    char new_pos = p.board[p.worker.row+1][p.worker.col];

    if (new_pos == '*')
        return false;
    else if (new_pos == 'b' || new_pos == 'B')
        return p.board[p.worker.row+2][p.worker.col] == ' ' ||
               p.board[p.worker.row+2][p.worker.col] == '.';
    else
        return true;
}

bool can_go_west (Puzzle p)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                               
                                             
*/
    if (p.worker.col-1 < 0)
        return false;

    char new_pos = p.board[p.worker.row][p.worker.col-1];

    if (new_pos == '*')
        return false;
    else if (new_pos == 'b' || new_pos == 'B')
        return p.board[p.worker.row][p.worker.col-2] == ' ' ||
               p.board[p.worker.row][p.worker.col-2] == '.';
    else
        return true;
}

bool can_go_east (Puzzle p)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                               
                                             
*/
    if (p.worker.col+1 >= COLUMN)
        return false;

    char new_pos = p.board[p.worker.row][p.worker.col+1];

    if (new_pos == '*')
        return false;
    else if (new_pos == 'b' || new_pos == 'B')
        return p.board[p.worker.row][p.worker.col+2] == ' ' ||
               p.board[p.worker.row][p.worker.col+2] == '.';
    else
        return true;
}

Pos north (Puzzle p)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                                    
*/
    return {p.worker.row-1, p.worker.col};
}

Pos south (Puzzle p)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                                    
*/
    return {p.worker.row+1, p.worker.col};
}

Pos west (Puzzle p)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                                   
*/
    return {p.worker.row, p.worker.col-1};
}

Pos east (Puzzle p)
{//               
    assert(ROW >= 0 && COLUMN >= 0);
/*                 
                                                   
*/
    return {p.worker.row, p.worker.col+1};
}

void tries (vector<Candidate>& c, int i, Pos next)
{//               
    assert(size(c) >= 0 && i >= -1);
/*                 
                                                      
                                                                              
*/
    Puzzle p = c[i].candidate ;
    Puzzle newp = move_worker (p, next);
    Candidate newc = {newp, i} ;
    if (!puzzle_present (c, newp))
       c.push_back (newc) ;
}

void solve_breadth_first (Puzzle start)
{//               
    assert(true);
/*                 
                                                               
                                      
*/
    vector<Candidate> c = {{start,-1}} ;
    int i = 0 ;
    while (i < size (c) && !puzzle_ready (c[i].candidate))
    {
        Puzzle p = c[i].candidate ;
        if (can_go_north (p)) tries (c, i, north (p)) ;
        if (can_go_south (p)) tries (c, i, south (p)) ;
        if (can_go_west  (p)) tries (c, i, west  (p)) ;
        if (can_go_east  (p)) tries (c, i, east  (p)) ;
        i = i+1 ;
    }
    if (i < size (c))
        show_path (c, i) ;
}

bool   puzzle_present_depth (Puzzle p, vector<Puzzle>& c)
{//               
    assert(size(c) >= 0 && ROW >= 0 && COLUMN >= 0);
/*                 
                                                     
                               
*/
    for (int i = 0; i < size(c); i++)
    {
        if (p == c[i])
            return true;
    }
    return false;
}

void   show_solution  (vector<Puzzle>& a)
{//               
    assert(size(a) >= 0);
/*                 
                                    
*/
    for (int i; i < size(a); i++)
        show(a[i].board);

}

void solve_depth_first ( vector<Puzzle>& attempt
                       , vector<Puzzle>& shortest, int max_depth );

void tries_depth ( vector<Puzzle>& attempt,  Pos next
                 , vector<Puzzle>& shortest, int max_depth )
{//               
    assert(max_depth >= 0);
/*                 
                             
                            
                                                         
*/
    Puzzle p    = attempt[size (attempt)-1] ;
    Puzzle newp = move_worker (p, next) ;
    if (!puzzle_present_depth (newp, attempt))
    {   attempt.push_back (newp) ;   //        
       solve_depth_first (attempt, shortest, max_depth) ;
       attempt.pop_back () ;        //       
    }
}

void solve_depth_first ( vector<Puzzle>& attempt
                       , vector<Puzzle>& shortest, int max_depth )
{//               
    assert(max_depth >= 0);
/*                 
                                                                      
                                          
*/
    const int CURRENT = size (attempt) ;
    const int BEST    = size (shortest) ;
    Puzzle p          = attempt[CURRENT-1] ;
    if (BEST > 0 && CURRENT >= BEST)      { return ; }
    else if (CURRENT > max_depth+1)       { return ; }
    else if (puzzle_ready (p)) { shortest = attempt ; return ; }
    if (can_go_north (p)) tries_depth (attempt, north (p), shortest, max_depth) ;
    if (can_go_south (p)) tries_depth (attempt, south (p), shortest, max_depth) ;
    if (can_go_west  (p)) tries_depth (attempt, west  (p), shortest, max_depth) ;
    if (can_go_east  (p)) tries_depth (attempt, east  (p), shortest, max_depth) ;
}

int main()
{
    /*
                           
                                      
                                              
    */

    //              
    solve_breadth_first(challenge23);

    //            
    vector<Puzzle> attempt = {challenge23};
    vector<Puzzle> shortest;
    solve_depth_first (attempt, shortest, 23);
    show_solution(shortest);
    return 0;
}

