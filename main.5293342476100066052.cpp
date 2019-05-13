#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;
//                       
const int width = 7;
const int height = 6;
const string filename = "challenge.23.txt";

struct Pos
{
    int col;
    int row;
};

struct Puzzle
{
    char board[width][height];
    Pos worker;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

bool operator==(const Puzzle& a, const Puzzle& b)
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            if(a.board[i][j] != b.board[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

int size (vector<Candidate>& array)
{//              
    assert (true) ;
/*                
                                                       
*/
    return static_cast<int> (array.size()) ;
}

int size (vector<Puzzle>& array)
{//              
    assert (true) ;
/*                
                                                       
*/
    return static_cast<int> (array.size()) ;
}

void read_inputfile(ifstream& inputfile, Puzzle& puzzle)
{//              
    assert (inputfile) ;
/*                
                                                                 
*/
    inputfile.open(filename);
    int i = 0;
    int j = 0;
    char c;
    while(inputfile)
    {
        inputfile.get(c);
        if(c == '\n')
        {
            j++;
            i = 0;
        }
        else if (c == 'w')
        {
            puzzle.board[i][j] = c;
            puzzle.worker.col = i;
            puzzle.worker.row = j;
            i++;
        }
        else
        {
            puzzle.board[i][j] = c;
            i++;
        }
    }
}

void show_puzzle(Puzzle puzzle)
{//              
    assert (true) ;
/*                
                                                     
*/
    int i = 0;
    int j = 0;
    while(j < height)
    {
        while(i <width)
        {
            cout << puzzle.board[i][j];
            i++;
        }
        cout << '\n';
        j++;
        i=0;
    }
}

bool puzzle_ready (Puzzle puzzle)
{//              
    assert (true) ;
/*                
                                                                                  
*/
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            if(puzzle.board[i][j] == 'b')
            {
                return false;
            }
        }
    }
    return true;
}

bool puzzle_present_b(vector<Candidate>& candidate, int i, Puzzle puzzle)
{//              
    assert (true) ;
/*                
                                                                    
*/
    for(int k = 0; k < i; k++)
    {
        if(candidate[k].candidate == puzzle)
            return true;
    }
    return false;
}

Pos move_box(Pos prev, Pos next)
{
    return {2*next.col-prev.col, 2*next.row-prev.row};
}

Puzzle move_empty(Puzzle puzzle, Pos next)
{//              
    assert (true) ;
/*                
                                                                    
*/
    Pos prev = puzzle.worker;
    Puzzle newpuzzle = puzzle;
    bool push_box = false;
    Pos newbox = move_box(prev, next);
    newpuzzle.worker = next;

    switch(puzzle.board[next.col][next.row])
    {
        case ' ': newpuzzle.board[next.col][next.row]='w';break;
        case '.': newpuzzle.board[next.col][next.row]='W';break;
        case 'b': newpuzzle.board[next.col][next.row]='w'; push_box = true; break;
        case 'B': newpuzzle.board[next.col][next.row]='W'; push_box = true; break;
    }
    if (puzzle.board[prev.col][prev.row] == 'W')
        newpuzzle.board[prev.col][prev.row] = '.';
    else
        newpuzzle.board[prev.col][prev.row] = ' ';
    if(push_box)
    {
        switch(puzzle.board[newbox.col][newbox.row])
        {
            case '.': newpuzzle.board[newbox.col][newbox.row] = 'B'; break;
            case ' ': newpuzzle.board[newbox.col][newbox.row] = 'b'; break;
        }
    }
    return newpuzzle;
}

bool can_go_north (Puzzle puzzle)
{//              
    assert (true) ;
/*                
                                             
*/
    int column  = puzzle.worker.col;
    int row = puzzle.worker.row;
    switch(puzzle.board[column][row-1])
    {
        case ' ': return true; break;
        case '.': return true; break;
        case 'b': return ((puzzle.board[column][row-2] == ' ' || puzzle.board[column][row-2] == '.')); break;
        case 'B': return ((puzzle.board[column][row-2] == ' ' || puzzle.board[column][row-2] == '.')); break;
        case '*': return false; break;
        default: return false; break;
    }
}

bool can_go_west (Puzzle puzzle)
{//              
    assert (true) ;
/*                
                                            
*/
    int column  = puzzle.worker.col;
    int row = puzzle.worker.row;
    switch(puzzle.board[column-1][row])
    {
        case ' ': return true; break;
        case '.': return true; break;
        case 'b': return ((puzzle.board[column-2][row] == ' ' || puzzle.board[column-2][row] == '.')); break;
        case 'B': return ((puzzle.board[column-2][row] == ' ' || puzzle.board[column-2][row] == '.')); break;
        case '*': return false; break;
        default: return false; break;
    }
}

bool can_go_south (Puzzle puzzle)
{//              
    assert (true) ;
/*                
                                             
*/
    int column  = puzzle.worker.col;
    int row = puzzle.worker.row;
    switch(puzzle.board[column][row+1])
    {
        case ' ': return true; break;
        case '.': return true; break;
        case 'b': return ((puzzle.board[column][row+2] == ' ' || puzzle.board[column][row+2] == '.')); break;
        case 'B': return ((puzzle.board[column][row+2] == ' ' || puzzle.board[column][row+2] == '.')); break;
        case '*': return false; break;
        default: return false; break;
    }
}

bool can_go_east (Puzzle puzzle)
{//              
    assert (true) ;
/*                
                                            
*/
    int column  = puzzle.worker.col;
    int row = puzzle.worker.row;
    switch(puzzle.board[column+1][row])
    {
        case ' ': return true; break;
        case '.': return true; break;
        case 'b': return ((puzzle.board[column+2][row] == ' ' || puzzle.board[column+2][row] == '.')); break;
        case 'B': return ((puzzle.board[column+2][row] == ' ' || puzzle.board[column+2][row] == '.')); break;
        case '*': return false; break;
        default: return false; break;
    }
}

Pos north (Puzzle puzzle)
{//              
    assert (true) ;
/*                
                          
*/
    return {puzzle.worker.col, puzzle.worker.row-1};
}

Pos west (Puzzle puzzle)
{//              
    assert (true) ;
/*                
                         
*/
    return {puzzle.worker.col-1, puzzle.worker.row};
}

Pos south (Puzzle puzzle)
{//              
    assert (true) ;
/*                
                          
*/
    return {puzzle.worker.col, puzzle.worker.row+1};
}

Pos east (Puzzle puzzle)
{//              
    assert (true) ;
/*                
                         
*/
    return {puzzle.worker.col+1, puzzle.worker.row};
}

int parents(vector<Candidate>& c, int i)
{//              
    assert (true) ;
/*                
                                                         
*/
    int parents = 0;
    int index = i;
    while(c[index].parent_candidate != -1)
    {
        index=c[index].parent_candidate;
        parents++;
    }
    return parents;
}

//                       

void tries_b(vector<Candidate>& c, int i, Pos next)
{//              
    assert (true) ;
/*                
                                                                                            
*/
    Puzzle puzzle = c[i].candidate;
    Puzzle puzzle2 = move_empty(puzzle, next);
    Candidate c2 = {puzzle2,i};
    if (!puzzle_present_b(c, i, puzzle2))
        c.push_back(c2);
}

void solve_b(Puzzle puzzle)
{//              
    assert (true) ;
/*                
                                                                     
*/
    vector<Candidate> c = {{puzzle, -1}};
    int i =0;
    while (i < size(c) && !puzzle_ready(c[i].candidate))
    {
        Puzzle puzzle2 = c[i].candidate;
        if (can_go_north(puzzle2))
            tries_b(c, i, north(puzzle2));
        if (can_go_west(puzzle2))
            tries_b(c, i, west(puzzle2));
        if (can_go_south(puzzle2))
            tries_b(c, i, south(puzzle2));
        if (can_go_east(puzzle2))
            tries_b(c, i, east(puzzle2));
        i++;
    }
    if (i < size(c))
    {
        cout << "Solution with breadth-first search algorithm (in " << parents(c, i) << " moves):\n";
        show_puzzle(c[i].candidate);
    }
}

//                    

bool puzzle_present_d(Puzzle p, vector<Puzzle>& c)
{//              
    assert (true) ;
/*                
                                                      
*/
    int k = size(c);
    for(int i = 0; i < k; i++)
    {
        if(c[i] == p)
            return true;
    }
    return false;
}

void solve_d (vector<Puzzle>& attempt, vector<Puzzle>& best, int maximum);
void tries_d (vector<Puzzle>& attempt, vector<Puzzle>& best, int maximum, Pos next);

void tries_d (vector<Puzzle>& attempt, vector<Puzzle>& best, int maximum, Pos next)
{//              
    assert (true) ;
/*                
                                                                                                              
*/
    Puzzle puzzle = attempt[size(attempt)-1];
    Puzzle puzzle2 = move_empty(puzzle, next);
    if(!puzzle_present_d(puzzle2, attempt))
    {
        attempt.push_back(puzzle2);
        solve_d(attempt, best, maximum);
        attempt.pop_back();
    }

}

void solve_d (vector<Puzzle>& attempt, vector<Puzzle>& best, int maximum)
{//              
    assert (true) ;
/*                
                                                                                                                                   
*/
    const int current = size(attempt);
    const int bestd = size(best);
    Puzzle puzzle = attempt[current-1];
    if(bestd > 0 && current >= bestd)
    {
        return;
    }
    else if(current > maximum+1)
    {
        return;
    }
    else if (puzzle_ready(puzzle))
    {
        best = attempt;
        return;
    }
    if (can_go_north(puzzle))
            tries_d(attempt, best, maximum, north(puzzle));
    if (can_go_west(puzzle))
            tries_d(attempt, best, maximum, west(puzzle));
    if (can_go_south(puzzle))
            tries_d(attempt, best, maximum, south(puzzle));
    if (can_go_east(puzzle))
            tries_d(attempt, best, maximum, east(puzzle));
}

int main()
{
    Puzzle puzzle;
    ifstream inputfile;
    read_inputfile(inputfile, puzzle);
    cout << "Starting position:\n";
    show_puzzle(puzzle);
    solve_b(puzzle);
    vector<Puzzle> attempt = {puzzle};
    vector<Puzzle> best;
    solve_d(attempt, best, 30);
    cout << "Solution with depth-first search algorithm (in " << size(best)-1 << " moves):\n";
    show_puzzle(best[size(best)-1]);
    return 0;
}

