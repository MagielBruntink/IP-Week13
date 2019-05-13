#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>

using namespace std;

//                       

const int COLUMNS = 30;
const int ROWS = 30;

struct Puzzle
{
    char field [ROWS][COLUMNS];
};

int rows = 0;
int columns = 0;

enum Direction {Up, Down, Left, Right};

int row_worker = 0;
int column_worker = 0;

void read_file (string filename, Puzzle& field)
{//              
    assert (true);
/*                
                                                                                             
*/
    ifstream infile(filename);
    cout << "Reading file: " << endl << endl;
    int i = 0;
    int j = 0;
    char c;
    while (infile)
    {
        infile.get(c);
        if (c == '\n')
        {
            j++;
            i = 0;
            cout << endl;
        } else {
            field.field[j][i] = c;
            if (field.field[j][i] == 'w' || field.field [j][i] == 'W')
            {
                row_worker = j;
                column_worker = i;
            }
            columns = i;
            cout << c;
            i++;
            }
    }
    rows = j-1;
    infile.close();
    cout << endl;
}

void update_location (Puzzle& p)
{//              
    assert (true);
/*                
                                                                                            
*/
    int i = 0;
    int j = 0;
    while (p.field[i][j] != 'w' && p.field[i][j] != 'W')
    {
        if (j <columns)
        {
            j++;
        }
        else
        {
            i++;
            j = 0;
        }
    }
    row_worker = i;
    column_worker = j;
}

bool can_move_up (Puzzle& field, int row, int column)
{//              
    assert (row >= 0 && column >= 0 && row < ROWS && column < COLUMNS);
/*                
                                                                      
*/
    if (field.field[row][column] != 'W' && field.field[row][column] != 'w')
        return false;
    if (field.field[row-1][column] == '*')
        return false;
    if ((field.field[row-1][column] == 'b' || field.field[row-1][column] == 'B') &&
        (field.field[row-2][column] == 'b' || field.field[row-2][column] == 'B'))
        return false;
    if ((field.field[row-1][column] == 'b' || field.field[row-1][column] == 'B') && field.field[row-1][column] == '*')
        return false;
    return true;
}

bool can_move_down (Puzzle& field, int row, int column)
{//              
    assert (row >= 0 && column >= 0 && row < ROWS && column < COLUMNS);
/*                
                                                                        
*/
    if (field.field[row][column] != 'W' && field.field[row][column] != 'w')
        return false;
    if (field.field[row+1][column] == '*')
        return false;
    if ((field.field[row+1][column] == 'b' || field.field[row+1][column] == 'B')
        && (field.field[row+2][column] == 'b' || field.field[row+2][column] == 'B'))
        return false;
    if ((field.field[row+1][column] == 'b' || field.field[row+1][column] == 'B') && field.field[row+1][column] == '*')
        return false;
    return true;
}

bool can_move_left (Puzzle& field, int row, int column)
{//              
    assert (row >= 0 && column >= 0 && row < ROWS && column < COLUMNS);
/*                
                                                                        
*/
    if (field.field[row][column] != 'W' && field.field[row][column] != 'w')
        return false;
    if (field.field[row][column-1] == '*')
        return false;
    if ((field.field[row][column-1] == 'b' || field.field[row][column-1] == 'B')
        && (field.field[row][column-2] == 'b' || field.field[row][column-2] == 'B'))
        return false;
    if ((field.field[row][column-1] == 'b' || field.field[row][column-1] == 'B') && field.field[row][column-2] == '*')
        return false;
    return true;
}

bool can_move_right (Puzzle& field, int row, int column)
{//              
    assert (row >= 0 && column >= 0 && row < ROWS && column < COLUMNS);
/*                
                                                                         
*/
    if (field.field[row][column] != 'W' && field.field[row][column] != 'w')
        return false;
    if (field.field[row][column+1] == '*')
        return false;
    if ((field.field[row][column+1] == 'b' || field.field[row][column+1] == 'B')
        && (field.field[row][column+2] == 'b' || field.field[row][column+2] == 'B'))
        return false;
    if ((field.field[row][column+1] == 'b' || field.field[row][column+1] == 'B') && field.field[row][column+2] == '*')
        return false;
    return true;
}

void show_puzzle (Puzzle& field)
{//               
    assert (true);
/*                
                                
*/
    for (int j = 0; j < rows; j++)
    {
        cout << endl;
        for (int i = 0; i < columns+1; i++)
        {
            cout << field.field [j][i];
        }
    }
}

bool solved (Puzzle& field)
{//              
    assert (true);
/*                
                                                                  
*/
    for (int j=0; j < rows; j++)
    {
        for (int i=0; i < columns; i++)
        {
            if (field.field[i][j] == 'b')
                return false;
        }
    }
    return true;
}

bool puzzle_not_present (vector<Puzzle>& c, Puzzle& field)
{//              
    assert (true);
/*                
                   
*/
    int i = 0;
    int k = 0;
    int j = 0;
    while (i < c.size())
    {
        Puzzle now = c[i];
        while (now.field[k][j] == field.field[k][j])
        {
            if (j < columns)
            {
                j++;
            }
            else if (k < rows)
            {
                k++;
                j = 0;
            }
        }
        if (now.field[k][j] != field.field[k][j])
            return true;
    }
    return false;
}

void tries (vector<Puzzle>& c, int i,  int row, int column, Direction direction)
{//              
    assert (true);
/*                

*/
    Puzzle p = c[i];
    Puzzle new_p = p;
    update_location(new_p);
    int r1;
    int c1;
    int r2;
    int c2;
    switch (direction)
    {
        case Up     : r1 = row-1; c1 = column; r2 = row-2; c2 = column; break;
        case Down   : r1 = row+1; c1 = column; r2 = row+2; c2 = column; break;
        case Left   : r1 = row; c1 = column-1; r2 = row; c2 = column-2; break;
        case Right  : r1 = row; c1 = column+1; r2 = row; c2 = column+2; break;
    }
    if (p.field [r1][c1] == ' ')
    {
        new_p.field [r1][c1] = 'w';
    }
    if (p.field [r1][c1] == '.')
    {
        new_p.field [r1][c1] == 'W';
    }
    if (p.field [r1][c1] == 'b')
    {
        new_p.field [r1][c1] = 'w';
        if (p.field [r2][c2] == ' ')
        {
            new_p.field [r2][c2] = 'b';
        }
        if (p.field [r2][c2] == '.')
        {
            new_p.field [r2][c2] = 'B';
        }
    }
    if (p.field [r1][c1] == 'B')
    {
        new_p.field [r1][c1] == 'W';
        if (p.field [r2][c2] == ' ')
        {
            new_p.field [r2][c2] = 'b';
        }
        if (p.field [r2][c2] == '.')
        {
            new_p.field [r2][c2] = 'B';
        }
    }
    if (p.field [row][column] == 'w')
    {
        new_p.field [row][column] = ' ';
    }
    if (p.field [row][column] == 'W')
    {
        new_p.field [row][column] = '.';
    }
    row_worker = r1;
    column_worker = r2;
    if (puzzle_not_present(c, new_p))
    {
        c.push_back(new_p);
    }
}

int breadth_first_search (Puzzle& field)
{//              
    assert (true);
/*                
                                                                    
*/
    vector<Puzzle> c = {{field}};
    int i;
    while (!solved(field))
    {
        if (can_move_down(field, row_worker, column_worker))
            tries(c, i, row_worker, column_worker, Down);
        if (can_move_left(field, row_worker, column_worker))
            tries(c, i, row_worker, column_worker, Left);
        if (can_move_right(field, row_worker, column_worker))
            tries(c, i, row_worker, column_worker, Right);
        if (can_move_up(field, row_worker, column_worker))
            tries(c, i, row_worker, column_worker, Up);
        i++;
    }
    show_puzzle(c[i]);
    cout << endl << "Steps: " << i;
    return i;
}

void depth_first_search (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void tries2 (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth, Direction direction)
{//              
    assert (max_depth > 0 && attempt.size() > 0);
/*                
                                             
*/
    int a = attempt.size()-1;
    Puzzle p = attempt[a];
    Puzzle new_p = p;
    update_location(new_p);
    int r1;
    int c1;
    int r2;
    int c2;
    switch (direction)
    {
        case Up     : r1 = row_worker-1; c1 = column_worker; r2 = row_worker-2; c2 = column_worker; break;
        case Down   : r1 = row_worker+1; c1 = column_worker; r2 = row_worker+2; c2 = column_worker; break;
        case Left   : r1 = row_worker; c1 = column_worker-1; r2 = row_worker; c2 = column_worker-2; break;
        case Right  : r1 = row_worker; c1 = column_worker+1; r2 = row_worker; c2 = column_worker+2; break;
    }
    if (p.field [r1][c1] == ' ')
    {
        new_p.field [r1][c1] = 'w';
    }
    if (p.field [r1][c1] == '.')
    {
        new_p.field [r1][c1] == 'W';
    }
    if (p.field [r1][c1] == 'b')
    {
        new_p.field [r1][c1] = 'w';
        if (p.field [r2][c2] == ' ')
        {
            new_p.field [r2][c2] = 'b';
        }
        if (p.field [r2][c2] == '.')
        {
            new_p.field [r2][c2] = 'B';
        }
    }
    if (p.field [r1][c1] == 'B')
    {
        new_p.field [r1][c1] == 'W';
        if (p.field [r2][c2] == ' ')
        {
            new_p.field [r2][c2] = 'b';
        }
        if (p.field [r2][c2] == '.')
        {
            new_p.field [r2][c2] = 'B';
        }
    }
    if (p.field [row_worker][column_worker] == 'w')
    {
        new_p.field [row_worker][column_worker] = ' ';
    }
    if (p.field [row_worker][column_worker] == 'W')
    {
        new_p.field [row_worker][column_worker] = '.';
    }
    row_worker = r1;
    column_worker = r2;
    if (puzzle_not_present(attempt, new_p))
    {
        attempt.push_back(new_p);
        depth_first_search(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

int steps = 0;

void depth_first_search (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{//              
    assert (true);
/*                
                                                                    
*/
    int current = attempt.size();
    int best = shortest.size();
    Puzzle p = attempt[current-1];
    update_location(p);
    if (best >0 && current >= best)
        {return ;}
    if (current > max_depth+1)
        {return ;}
    if (solved(p))
        {shortest = attempt; return ;}
    steps++;
    if (can_move_down(p, row_worker, column_worker))
        {tries2(attempt, shortest, max_depth, Down);}
    if (can_move_left(p, row_worker, column_worker))
        {tries2(attempt, shortest, max_depth, Left);}
    if (can_move_right(p, row_worker, column_worker))
        {tries2(attempt, shortest, max_depth, Right);}
    if (can_move_up(p, row_worker, column_worker))
        {tries2(attempt, shortest, max_depth, Up);}
}

int main()
{
    Puzzle field = {};
    for (int j=0; j < COLUMNS; j++)
    {
        for (int i=0; i < ROWS; i++)
            field.field [j][i] = '0';
    }
    read_file("challenge.23.txt", field);
    vector<Puzzle> attempt = {field};
    vector<Puzzle> shortest = {};
    int max_depth = 5000;
    depth_first_search(attempt, shortest, max_depth);
    int depth = shortest.size();
    show_puzzle(shortest[depth-1]);
    cout << endl << "Steps: " << steps << endl;
    return 0;
}

