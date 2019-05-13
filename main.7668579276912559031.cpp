#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;

char board[100][100];

struct Pos {int col, row;};
struct Puzzle {char board[100][100] ; Pos worker;};
struct Candidate {Puzzle puzzle; int previous;};

vector<Candidate> c;

void array_copy(char a[100][100], char b[100][100])
{
    //                                         
    //                        
    for (int i = 0; i< sizeof(a); i++)
        for (int j = 0; j< sizeof(a[0]); j++)
        {
            a[i][j] = b[i][j];
        }
}

Puzzle get_puzzle (ifstream& infile)
{
    //                 
    int i = 0;  //             
    int j = 0;  //             
    char a;
    Pos start;
    //                                   
    while (infile)
    {
        cin.get(a);
        if (a == '\n')
        {
            j++;
            i = 0;
        }
        else
        {
            board[i][j] = a;
            i++;
        }
    }
    for (int y = 1 ; y < sizeof(board)-1 ; y++)
        for (int x = 1 ; x < sizeof(board[0]-1) ; x++) //                                                             
            if (board[y][x] == 'w' || board[y][x] == 'W')
            {
                //              
                Puzzle puzzle;
                array_copy(puzzle.board, board);
                puzzle.worker = {y,x};
                return puzzle;
            }
}

bool can_go_north (Puzzle puzzle)
{
    //                               
    //                                                                
    if (puzzle.board[puzzle.worker.col-1][puzzle.worker.row] == '*' ||
        (puzzle.board[puzzle.worker.col-1][puzzle.worker.row] == 'b' && (puzzle.board[puzzle.worker.col-2][puzzle.worker.row] != ' ' || puzzle.board[puzzle.worker.col-2][puzzle.worker.row] != '.')) ||
        (puzzle.board[puzzle.worker.col-1][puzzle.worker.row] == 'B' && (puzzle.board[puzzle.worker.col-2][puzzle.worker.row] != ' ' || puzzle.board[puzzle.worker.col-2][puzzle.worker.row] != '.')))
         return false;
    return true;
}

bool can_go_east (Puzzle puzzle)
{
    //                               
    //                                                               
    if (puzzle.board[puzzle.worker.col][puzzle.worker.row+1] == '*' ||
        (puzzle.board[puzzle.worker.col][puzzle.worker.row+1] == 'b' && (puzzle.board[puzzle.worker.col][puzzle.worker.row+2] != ' ' || puzzle.board[puzzle.worker.col][puzzle.worker.row+2] != '.')) ||
        (puzzle.board[puzzle.worker.col][puzzle.worker.row+1] == 'B' && (puzzle.board[puzzle.worker.col][puzzle.worker.row+2] != ' ' || puzzle.board[puzzle.worker.col][puzzle.worker.row+2] != '.')))
         return false;
    return true;
}

bool can_go_south (Puzzle puzzle)
{
    //                               
    //                                                                
    if (puzzle.board[puzzle.worker.col+1][puzzle.worker.row] == '*' ||
        (puzzle.board[puzzle.worker.col+1][puzzle.worker.row] == 'b' && (puzzle.board[puzzle.worker.col+2][puzzle.worker.row] != ' ' || puzzle.board[puzzle.worker.col+2][puzzle.worker.row] != '.')) ||
        (puzzle.board[puzzle.worker.col+1][puzzle.worker.row] == 'B' && (puzzle.board[puzzle.worker.col+2][puzzle.worker.row] != ' ' || puzzle.board[puzzle.worker.col+2][puzzle.worker.row] != '.')))
         return false;
    return true;
}

bool can_go_west (Puzzle puzzle)
{
    //                               
    //                                                               
    if (puzzle.board[puzzle.worker.col][puzzle.worker.row-1] == '*' ||
        (puzzle.board[puzzle.worker.col][puzzle.worker.row-1] == 'b' && (puzzle.board[puzzle.worker.col][puzzle.worker.row-2] != ' ' || puzzle.board[puzzle.worker.col][puzzle.worker.row-2] != '.')) ||
        (puzzle.board[puzzle.worker.col][puzzle.worker.row-1] == 'B' && (puzzle.board[puzzle.worker.col][puzzle.worker.row-2] != ' ' || puzzle.board[puzzle.worker.col][puzzle.worker.row-2] != '.')))
         return false;
    return true;
}

Puzzle north (Puzzle puzzle)
{
    //                  
    //                                           
    if (puzzle.board[puzzle.worker.col][puzzle.worker.row] == 'w')
    {
        if (puzzle.board[puzzle.worker.col-1][puzzle.worker.row] == ' ')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.col--;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
        }
        else if (puzzle.board[puzzle.worker.col-1][puzzle.worker.row] == '.')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.col--;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
        }
        else if (puzzle.board[puzzle.worker.col-1][puzzle.worker.row] == 'b')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.col--;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
            if (board[puzzle.worker.col-1][puzzle.worker.row] = ' ')
                board[puzzle.worker.col-1][puzzle.worker.row] = 'b';
            else
                board[puzzle.worker.col-1][puzzle.worker.row] = 'B';
        }
        else
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.col--;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
            if (board[puzzle.worker.col-1][puzzle.worker.row] = ' ')
                board[puzzle.worker.col-1][puzzle.worker.row] = 'b';
            else
                board[puzzle.worker.col-1][puzzle.worker.row] = 'B';
        }
    }
    else
    {
        if (puzzle.board[puzzle.worker.col-1][puzzle.worker.row] == ' ')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.col--;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
        }
        else if (puzzle.board[puzzle.worker.col-1][puzzle.worker.row] == '.')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.col--;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
        }
        else if (puzzle.board[puzzle.worker.col-1][puzzle.worker.row] == 'b')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.col--;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
            if (board[puzzle.worker.col-1][puzzle.worker.row] = ' ')
                board[puzzle.worker.col-1][puzzle.worker.row] = 'b';
            else
                board[puzzle.worker.col-1][puzzle.worker.row] = 'B';
        }
        else
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.col--;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
            if (board[puzzle.worker.col-1][puzzle.worker.row] = ' ')
                board[puzzle.worker.col-1][puzzle.worker.row] = 'b';
            else
                board[puzzle.worker.col-1][puzzle.worker.row] = 'B';
        }
    }
    return puzzle;
}

Puzzle east (Puzzle puzzle)
{
    //                 
    //                                          
    if (puzzle.board[puzzle.worker.col][puzzle.worker.row] == 'w')
    {
        if (puzzle.board[puzzle.worker.col][puzzle.worker.row+1] == ' ')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.row++;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
        }
        else if (puzzle.board[puzzle.worker.col][puzzle.worker.row+1] == '.')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.row++;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
        }
        else if (puzzle.board[puzzle.worker.col][puzzle.worker.row+1] == 'b')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.row++;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
            if (board[puzzle.worker.col][puzzle.worker.row+1] = ' ')
                board[puzzle.worker.col][puzzle.worker.row+1] = 'b';
            else
                board[puzzle.worker.col][puzzle.worker.row+1] = 'B';
        }
        else
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.row++;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
            if (board[puzzle.worker.col][puzzle.worker.row+1] = ' ')
                board[puzzle.worker.col][puzzle.worker.row+1] = 'b';
            else
                board[puzzle.worker.col][puzzle.worker.row+1] = 'B';
        }
    }
    else
    {
        if (puzzle.board[puzzle.worker.col][puzzle.worker.row+1] == ' ')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.row++;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
        }
        else if (puzzle.board[puzzle.worker.col][puzzle.worker.row+1] == '.')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.row++;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
        }
        else if (puzzle.board[puzzle.worker.col][puzzle.worker.row+1] == 'b')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.row++;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
            if (board[puzzle.worker.col][puzzle.worker.row+1] = ' ')
                board[puzzle.worker.col][puzzle.worker.row+1] = 'b';
            else
                board[puzzle.worker.col][puzzle.worker.row+1] = 'B';
        }
        else
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.row++;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
            if (board[puzzle.worker.col][puzzle.worker.row+1] = ' ')
                board[puzzle.worker.col][puzzle.worker.row+1] = 'b';
            else
                board[puzzle.worker.col][puzzle.worker.row+1] = 'B';
        }
    }
    return puzzle;
}

Puzzle south (Puzzle puzzle)
{
    //                  
    //                                           
    if (puzzle.board[puzzle.worker.col][puzzle.worker.row] == 'w')
    {
        if (puzzle.board[puzzle.worker.col+1][puzzle.worker.row] == ' ')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.col++;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
        }
        else if (puzzle.board[puzzle.worker.col+1][puzzle.worker.row] == '.')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.col++;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
        }
        else if (puzzle.board[puzzle.worker.col+1][puzzle.worker.row] == 'b')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.col++;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
            if (board[puzzle.worker.col+1][puzzle.worker.row] = ' ')
                board[puzzle.worker.col+1][puzzle.worker.row] = 'b';
            else
                board[puzzle.worker.col+1][puzzle.worker.row] = 'B';
        }
        else
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.col++;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
            if (board[puzzle.worker.col+1][puzzle.worker.row] = ' ')
                board[puzzle.worker.col+1][puzzle.worker.row] = 'b';
            else
                board[puzzle.worker.col+1][puzzle.worker.row] = 'B';
        }
    }
    else
    {
        if (puzzle.board[puzzle.worker.col+1][puzzle.worker.row] == ' ')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.col++;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
        }
        else if (puzzle.board[puzzle.worker.col+1][puzzle.worker.row] == '.')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.col++;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
        }
        else if (puzzle.board[puzzle.worker.col+1][puzzle.worker.row] == 'b')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.col++;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
            if (board[puzzle.worker.col+1][puzzle.worker.row] = ' ')
                board[puzzle.worker.col+1][puzzle.worker.row] = 'b';
            else
                board[puzzle.worker.col+1][puzzle.worker.row] = 'B';
        }
        else
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.col++;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
            if (board[puzzle.worker.col+1][puzzle.worker.row] = ' ')
                board[puzzle.worker.col+1][puzzle.worker.row] = 'b';
            else
                board[puzzle.worker.col+1][puzzle.worker.row] = 'B';
        }
    }
    return puzzle;
}

Puzzle west (Puzzle puzzle)
{
    //                 
    //                                          
    if (puzzle.board[puzzle.worker.col][puzzle.worker.row] == 'w')
    {
        if (puzzle.board[puzzle.worker.col][puzzle.worker.row-1] == ' ')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.row--;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
        }
        else if (puzzle.board[puzzle.worker.col][puzzle.worker.row-1] == '.')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.row--;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
        }
        else if (puzzle.board[puzzle.worker.col][puzzle.worker.row-1] == 'b')
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.row--;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
            if (board[puzzle.worker.col][puzzle.worker.row-1] = ' ')
                board[puzzle.worker.col][puzzle.worker.row-1] = 'b';
            else
                board[puzzle.worker.col][puzzle.worker.row-1] = 'B';
        }
        else
        {
            board[puzzle.worker.col][puzzle.worker.row] = ' ';
            puzzle.worker.row--;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
            if (board[puzzle.worker.col][puzzle.worker.row-1] = ' ')
                board[puzzle.worker.col][puzzle.worker.row-1] = 'b';
            else
                board[puzzle.worker.col][puzzle.worker.row-1] = 'B';
        }
    }
    else
    {
        if (puzzle.board[puzzle.worker.col][puzzle.worker.row-1] == ' ')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.row--;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
        }
        else if (puzzle.board[puzzle.worker.col][puzzle.worker.row-1] == '.')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.row--;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
        }
        else if (puzzle.board[puzzle.worker.col][puzzle.worker.row-1] == 'b')
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.row--;
            board[puzzle.worker.col][puzzle.worker.row] = 'w';
            if (board[puzzle.worker.col][puzzle.worker.row-1] = ' ')
                board[puzzle.worker.col][puzzle.worker.row-1] = 'b';
            else
                board[puzzle.worker.col][puzzle.worker.row-1] = 'B';
        }
        else
        {
            board[puzzle.worker.col][puzzle.worker.row] = '.';
            puzzle.worker.row--;
            board[puzzle.worker.col][puzzle.worker.row] = 'W';
            if (board[puzzle.worker.col][puzzle.worker.row-1] = ' ')
                board[puzzle.worker.col][puzzle.worker.row-1] = 'b';
            else
                board[puzzle.worker.col][puzzle.worker.row-1] = 'B';
        }
    }
    return puzzle;
}

bool puzzle_ready (Puzzle puzzle)
{
    //                               
    //                                                    
    for (int y = 1 ; y < sizeof(board)-1 ; y++)
        for (int x = 1 ; x < sizeof(board[0])-1 ; x++) //                                                                                        
            if (board[y][x] == 'b')
                return false;
    return true;
}

bool twin_check (vector<Candidate>& c, int i, Puzzle p)
{
    //                                                                           
    //                                                                                               
    bool a=true;
    for (int k = 0; k < i; k++)
    {
        for (int l = 1 ; l < sizeof(board)-1 ; l++)
            for (int m = 1 ; m < sizeof(board[0])-1 ; m++)
                if (p.board[l][m] != c[k].puzzle.board[l][m])
                {
                    a=false;
                    l+=1037;
                }
        if (p.worker.row == c[k].puzzle.worker.row && p.worker.col == c[k].puzzle.worker.col || a)
            return true;
        a=true;
    }

}

void tries (vector<Candidate>& c, int j, Puzzle p) //                              
{
    //                                                                     
    //                                                                         
    Candidate newc = {p,j};
    if (!twin_check(c, c.size(), p))
        c.push_back(newc);
}

void print_configuration(Puzzle puzz)
{
    //                               
    //                                              
    for (int l = 0 ; l < sizeof(board) ; l++)
    {
        for (int m = 0 ; m < sizeof(board[0]) ; m++)
            cout << puzz.board[l][m];
        cout << endl;
    }
}

void show_path(vector<Candidate>& c, int i)
{
    //                                      
    //                                                          
    while (i >= 0)
    {
        print_configuration(c[i].puzzle);
        i = c[i].previous;
    }
}

void breadth_solve (vector<Candidate>& c, Puzzle start)
{
    //                                                       
    //                                                             
    c.push_back({start,-1});
    int i=0;
    while (i< c.size() && !puzzle_ready(c[i].puzzle))
    {
        Puzzle p = c[i].puzzle;
        if (can_go_north(p))
            tries(c, i, north(p));
        if (can_go_east(p))
            tries(c, i, east(p));
        if (can_go_south(p))
            tries(c, i, south(p));
        if (can_go_west(p))
            tries(c, i, west(p));
        i++;
    }
    show_path(c,i);
}

/*                                                                                                         */

void depth_solve (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{

}

void start_depth_solve (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth, ifstream& infile)
{
    //                                                                                
    //                                   
    attempt.push_back(get_puzzle(infile));
    depth_solve(attempt, shortest, max_depth);
}

/* 
                                                                                                                                    
                                                                                                         
*/

int main()
{
    //                                                                                                                                 
    return 0;
}

