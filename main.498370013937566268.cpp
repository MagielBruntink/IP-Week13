#include <iostream>
#include <assert.h>
using namespace std;

//                           

typedef char Cell;

const int Height = 6;
const int Width = 10;

struct Pos
{
    int col, row;
};

struct Puzzle
{
    Cell board [Height][Width];
    Pos start;
};

Puzzle file_1a;

Pos box_1a;
Pos keeper_1a;
Pos destination_1a;

file_1a.board = [10][6];
box_1a.col = 3;
box_1a.row = 2;
keeper_1a.col = 4;
keeper_1a.row = 2;
destination_1a.col = 2;
destination_1a.row = 2;

/*                                                        
                                                                   
 
                                   
     
                                        
                                   
     
                                        
                                       
                                             
                                                       
                      
 
*/

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

bool can_move_north(Puzzle p, Pos start)
{
//              
assert(true);
/*                
                                                                 
*/
    if (p.board[start.col][start.row-1] != "*" && start.row-1 > -1)
        {
            if (p.board[start.col][start.row-1] == "b")
            {
                if (p.board[start.col][start.row-2] == "b" || p.board[start.col][start.row-2] == "*")
                    return false;
            }
            return true;
        }

    else
        return false;
}

bool can_move_south(Puzzle p, Pos start)
{
//              
assert(true);
/*                
                                                                 
*/
    if (p.board[start.col][start.row+1] != "*" && start.row+1 < Height)
        {
            if (p.board[start.col][start.row+1] == "b")
            {
                if (p.board[start.col][start.row+2] == "b" || p.board[start.col][start.row+2] == "*")
                    return false;
            }
            return true;
        }
    else
        return false;
}

bool can_move_east(Puzzle p, Pos start)
{
    //              
assert(true);
/*                
                                                                
*/
    if (p.board[start.col+1][start.row] != "*" && start.col+1 < Width)
        {
            if (p.board[start.col+1][start.row] == "b")
            {
                if (p.board[start.col+2][start.row] == "b" || p.board[start.col+2][start.row] == "*")
                    return false;
            }
            return true;
        }
    else
        return false;
}

bool can_move_west(Puzzle p, Pos start)
{
    //              
assert(true);
/*                
                                                                
*/
    if (p.board[start.col-1][start.row] != "*" && start.col-1 > -1)
        {
            if (p.board[start.col-1][start.row] == "b")
            {
                if (p.board[start.col-2][start.row] == "b" || p.board[start.col-2][start.row] == "*")
                    return false;
            }
            return true;
        }
    else
        return false;
}

bool move_keeper (Puzzle p, string Direction, Pos start)
{
//               
assert(true);
/*                
                                                                                      
*/
    switch(Direction)
    {
    case "north":
        if (p.board[start.col][start.row-1] == "b")
        {
            if(p.board[start.col][start.row-2] == ".")
                p.board[start.col][start.row-2] = "B";
            else
                p.board[start.col][start.row-2] = "b";
        }
        if (p.board[start.col][start.row-1] == ".")
            p.board[start.col][start.row-1] = "W";
        else
            p.board[start.col][start.row-1] = "w";
        p.board[start.col][start.row] = " "; break;
    case "south":
         if (p.board[start.col][start.row+1] == "b")
         {
             if(p.board[start.col][start.row+2] == ".")
                p.board[start.col][start.row+2] = "B";
             else
                p.board[start.col][start.row+2] = "b";
         }
         if (p.board[start.col][start.row+1] == ".")
            p.board[start.col][start.row+1] = "W";
         else
            p.board[start.col][start.row+1] = "w";
         p.board[start.col][start.row] = " "; break;
    case "east":
        if(p.board[start.col+1][start.row] == "b")
        {
            if(p.board[start.col+2][start.row] == ".")
                p.board[start.col+1][start.row] = "B";
            else
                p.board[start.col+2][start.row] = "b";
        }
        if(p.board[start.col+1][start.row] = ".")
            p.board[start.col+1][start.row] = "W";
        else
            p.board[start.col+1][start.row] = "w";
        p.board[start.col+1][start.row] = " "; break;
    case "west":
        if(p.board[start.col-1][start.row] == "b")
        {
            if(p.board[start.col-2][start.row] == ".")
                p.board[start.col-2][start.row] = "B";
            else
                p.board[start.col-2][start.row] = "b";
        }
        if(p.board[start.col-1][start.row] = ".")
            p.board[start.col-1][start.row] = "W";
        else
            p.board[start.col-1][start.row] = "w";
        p.board[start.col][start.row] = " "; break;
    default: cout << "Invalid direction" <<endl;
    }
    return true;
}

bool puzzle_ready(Puzzle p)
{
//               
assert(true);
/*                
                                                               
*/
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (p.board[i][j] == "b")
                return false;
        }
    }
    return true;
}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle p)
{
//               
assert(true && i < size(c));
/*                
                                                                           
*/
    for (int j = 0; j < size(c) ; j++)
    {
        for(int a = 0; a < Width; a++)
        {
            for(int b = 0; b < Height; b++)
            {
                if(c[i].candidate.board[a][b] != c[j].candidate.board[a][b])
                    return true;
            }
        }
    }
    return false;
}

void tries_breadth_first(vector<Candidate>& c, int i, string Direction)
{
//               
assert(true && i < size(c));
/*                
                                                                                     
*/
    Puzzle p = c[i].candidate;
    Puzzle newp = move_keeper (p, Direction);
    Candidate newc = {newp, i};
    if(!puzzle_present (c, i, newp))
        c.push_back(newc);
}

void show_path(Vector<Candidate>& c, i)
{
//               
assert (true && i < size(c));
/*                
                                      
*/
    for (int a = 0; a < Height; a++)
    {
        for (int b = 0; b < Width; b++)
        {
            cout << c[i].candidate.board[a][b];
        }
        cout << 'n' <<;
    }
}

void solve_breadth_first(Puzzle start)
{
//              
assert(true);
/*                
                                                 
*/
    vector<Candidate> c = {{start,-1}};
    int i = 0;
    while (i < size(c) && !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if(can_move_north(p)) tries_breadth_first(c,i,"north");
        if(can_move_south(p)) tries_breadth_first(c,i,"south");
        if(can_move_east(p)) tries_breadth_first(c,i,"east");
        if(can_move_west(p)) tries_breadth_first(c,i,"south");
        i += 1;
    }
    if (i < size(c))
        show_path (c,i);
}

const int max_depth = 20;

bool puzzle_present_depth_first (Puzzle p, vector<Puzzle>& c)
{
  //               
assert(true && i < size(c));
/*                
                                                                           
*/
    for (int j = 0; j < size(c); j++)
    {
        for(int a = 0; a < Width; a++)
        {
            for(int b = 0; b < Height; b++)
            {
                if(p.board[a][b] != c[j].board[a][b])
                    return true;
            }
        }
    }
    return false;
}

void tries_depth_first(vector<Puzzle>& attempt, string Direction, vector<Puzzle>& shortest, int max_depth)
{
//               
assert(true && i < size(c));
/*                
                                                                                     
*/
    Puzzle p = attempt[size(attempt-1)];
    Puzzle newp = move_keeper(p,direction);
    if (!puzzle_present_depth_first (newp, attempt))
    {
        attempt.push_back (newp) ;
        solve_depth_first(attempt, shortest, max_depth);
        attempt.pop_back ();
    }
}

void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
//              
assert(true);
/*                
                                                 
*/
    const int Current = size(attempt);
    const int Best = size(shortest);
    Puzzle p = attempt[Current-1];
    if (Best > 0 && Current >= Best) {return ;}
    else if (Current > max_depth+1) {return ;}
    else if (puzzle_ready(p)) {shortest = attempt; return ;}
    if (can_move_north(p)) tries_depth-first(attempt,"north",shortest,max_depth);
    if(can_move_south(p)) tries_depth-first(attempt,"south",shortest,max_depth);
    if(can_move_east(p)) tries_depth-first(attempt,"east",shortest,max_depth);
    if(can_move_west(p)) tries_depth-first(attempt,"west",shortest,max_depth);

    if (Best < max_depth)
    {
        show_solution(shortest);
        cout << Best << endl;
    }

}

void show_solution (vector<Puzzle>& c)
{
//               
assert (true && i < size(c));
/*                
                                      
*/
    for (int a = 0; a < Height; a++)
    {
        for (int b = 0; b < Width; b++)
        {
            cout << c.board[a][b];
        }
        cout << 'n' <<;
    }
}

int main()
{
    solve_breadth_first(file_1a);
    
    return 0;
}

