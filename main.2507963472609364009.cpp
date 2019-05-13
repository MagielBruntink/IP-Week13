#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

//                                                       

//                                                                                
//                                      

const int MAX_CHARS = 15;

struct Puzzle
{
    char matrix [MAX_CHARS][MAX_CHARS];
    int row;    //              
    int col;    //                 
    int parent;
    int steps;
};

void open_file (Puzzle& puzzle, ifstream& infile, int& width, int& height)
{
    //               
    assert (true);
    //                
    //                                                                  

    infile.open("challenge.23.txt");

    char temp;

    infile.get(temp);

    int row = 0;
    int col = 0;

    while (infile)
    {
        while (temp != '\n')
        {
            puzzle.matrix[row][col] = temp;
            if (temp == 'w' || temp == 'W')
            {
                puzzle.row = row;
                puzzle.col = col;
            }
            col++;
            infile.get(temp);
        }
        row++;
        width = col;
        col = 0;
        infile.get(temp);
    }

    height = row;

    puzzle.parent = -1;

    puzzle.steps = 0;

    infile.close();
}

bool is_solution (Puzzle puzzle)
{
    //               
    assert (true);
    //                
    //                                                                                                                              

    for (int row = 0; row < MAX_CHARS; row++)
        for (int col = 0; col < MAX_CHARS; col++)
            if (puzzle.matrix[row][col] == 'b')
                return false;

    return true;
}

bool operator== (const Puzzle& a, const Puzzle& b)
{
    //               
    assert (true);
    //                
    //                                                                                            

    for (int row = 0; row < MAX_CHARS; row++)
    {
        for (int col = 0; col < MAX_CHARS; col++)
        {
            if (a.matrix[row][col] != b.matrix[row][col])
                return false;
        }
    }

    return true;
}

bool in_vector (Puzzle puzzle, vector<Puzzle> attempts)
{
    //               
    assert (true);
    //                
    //                                                                                                                 

    for (int i = 0; i < attempts.size(); i++)
    {
        if (puzzle == attempts[i] && attempts[i].steps <= puzzle.steps)
            return true;
    }

    return false;
}

bool can_go_north (Puzzle puzzle, int width, int height)
{
    //               
    assert (height > 0 && width > 0);
    //                
    //                                                                                             

    if (puzzle.matrix[puzzle.row-1][puzzle.col] != '*')
    {
        if (puzzle.row - 2 >= 0 && puzzle.matrix[puzzle.row-2][puzzle.col] != '*' && puzzle.matrix[puzzle.row-2][puzzle.col] != 'b' && puzzle.matrix[puzzle.row-2][puzzle.col] != 'B')
            return true;
        else if (puzzle.matrix[puzzle.row-1][puzzle.col] == ' ' || puzzle.matrix[puzzle.row-1][puzzle.col] == '.')
            return true;
    }

    return false;
}

bool can_go_east (Puzzle puzzle, int width, int height)
{
    //               
    assert (height > 0 && width > 0);
    //                
    //                                                                                            

    if (puzzle.matrix[puzzle.row][puzzle.col+1] != '*')
    {
        if (puzzle.col + 2 < width && puzzle.matrix[puzzle.row][puzzle.col+2] != '*' && puzzle.matrix[puzzle.row][puzzle.col+2] != 'b' && puzzle.matrix[puzzle.row][puzzle.col+2] != 'B')
            return true;
        else if (puzzle.matrix[puzzle.row][puzzle.col+1] == ' ' || puzzle.matrix[puzzle.row][puzzle.col+1] == '.')
            return true;
    }

    return false;
}

bool can_go_south (Puzzle puzzle, int width, int height)
{
    //               
    assert (height > 0 && width > 0);
    //                
    //                                                                                             

    if (puzzle.matrix[puzzle.row+1][puzzle.col] != '*')
    {
        if (puzzle.row + 2 < height && puzzle.matrix[puzzle.row+2][puzzle.col] != '*' && puzzle.matrix[puzzle.row+2][puzzle.col] != 'b' && puzzle.matrix[puzzle.row+2][puzzle.col] != 'B')
            return true;
        else if (puzzle.matrix[puzzle.row+1][puzzle.col] == ' ' || puzzle.matrix[puzzle.row+1][puzzle.col] == '.')
            return true;
    }

    return false;
}

bool can_go_west (Puzzle puzzle, int width, int height)
{
    //               
    assert (height > 0 && width > 0);
    //                
    //                                                                                            

    if (puzzle.matrix[puzzle.row][puzzle.col-1] != '*')
    {
        if (puzzle.col - 2 >= 0 && puzzle.matrix[puzzle.row][puzzle.col-2] != '*' && puzzle.matrix[puzzle.row][puzzle.col-2] != 'b' && puzzle.matrix[puzzle.row][puzzle.col-2] != 'B')
            return true;
        else if (puzzle.matrix[puzzle.row][puzzle.col-1] == ' ' || puzzle.matrix[puzzle.row][puzzle.col-1] == '.')
            return true;
    }

    return false;
}

void go_north (Puzzle& puzzle)
{
    //               
    assert (true);
    //                
    //                                                                                  

    if (puzzle.matrix[puzzle.row][puzzle.col] == 'W')
    {
        if (puzzle.matrix[puzzle.row-1][puzzle.col] == ' ')
        {
            puzzle.matrix[puzzle.row-1][puzzle.col] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
        }
        else if (puzzle.matrix[puzzle.row-1][puzzle.col] == '.')
        {
            puzzle.matrix[puzzle.row-1][puzzle.col] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
        }
        else if (puzzle.matrix[puzzle.row-1][puzzle.col] == 'b')
        {
            puzzle.matrix[puzzle.row-1][puzzle.col] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
            if (puzzle.matrix[puzzle.row-2][puzzle.col] == ' ')
                puzzle.matrix[puzzle.row-2][puzzle.col] = 'b';
            else
                puzzle.matrix[puzzle.row-2][puzzle.col] = 'B';
        }
        else
        {
            puzzle.matrix[puzzle.row-1][puzzle.col] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
            if (puzzle.matrix[puzzle.row-2][puzzle.col] == ' ')
                puzzle.matrix[puzzle.row-2][puzzle.col] = 'b';
            else
                puzzle.matrix[puzzle.row-2][puzzle.col] = 'B';
        }
    }
    else
    {
        if (puzzle.matrix[puzzle.row-1][puzzle.col] == ' ')
        {
            puzzle.matrix[puzzle.row-1][puzzle.col] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
        }
        else if (puzzle.matrix[puzzle.row-1][puzzle.col] == '.')
        {
            puzzle.matrix[puzzle.row-1][puzzle.col] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
        }
        else if (puzzle.matrix[puzzle.row-1][puzzle.col] == 'b')
        {
            puzzle.matrix[puzzle.row-1][puzzle.col] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
            if (puzzle.matrix[puzzle.row-2][puzzle.col] == ' ')
                puzzle.matrix[puzzle.row-2][puzzle.col] = 'b';
            else
                puzzle.matrix[puzzle.row-2][puzzle.col] = 'B';
        }
        else
        {
            puzzle.matrix[puzzle.row-1][puzzle.col] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
            if (puzzle.matrix[puzzle.row-2][puzzle.col] == ' ')
                puzzle.matrix[puzzle.row-2][puzzle.col] = 'b';
            else
                puzzle.matrix[puzzle.row-2][puzzle.col] = 'B';
        }
    }

    puzzle.row = puzzle.row - 1;
}

void go_east (Puzzle& puzzle)
{
    //               
    assert (true);
    //                
    //                                                                                 

    if (puzzle.matrix[puzzle.row][puzzle.col] == 'W')
    {
        if (puzzle.matrix[puzzle.row][puzzle.col+1] == ' ')
        {
            puzzle.matrix[puzzle.row][puzzle.col+1] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
        }
        else if (puzzle.matrix[puzzle.row][puzzle.col+1] == '.')
        {
            puzzle.matrix[puzzle.row][puzzle.col+1] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
        }
        else if (puzzle.matrix[puzzle.row][puzzle.col+1] == 'b')
        {
            puzzle.matrix[puzzle.row][puzzle.col+1] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
            if (puzzle.matrix[puzzle.row][puzzle.col+2] == ' ')
                puzzle.matrix[puzzle.row][puzzle.col+2] = 'b';
            else
                puzzle.matrix[puzzle.row][puzzle.col+2] = 'B';
        }
        else
        {
            puzzle.matrix[puzzle.row][puzzle.col+1] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
            if (puzzle.matrix[puzzle.row][puzzle.col+2] == ' ')
                puzzle.matrix[puzzle.row][puzzle.col+2] = 'b';
            else
                puzzle.matrix[puzzle.row][puzzle.col+2] = 'B';
        }
    }
    else
    {
        if (puzzle.matrix[puzzle.row][puzzle.col+1] == ' ')
        {
            puzzle.matrix[puzzle.row][puzzle.col+1] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
        }
        else if (puzzle.matrix[puzzle.row][puzzle.col+1] == '.')
        {
            puzzle.matrix[puzzle.row][puzzle.col+1] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
        }
        else if (puzzle.matrix[puzzle.row][puzzle.col+1] == 'b')
        {
            puzzle.matrix[puzzle.row][puzzle.col+1] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
            if (puzzle.matrix[puzzle.row][puzzle.col+2] == ' ')
                puzzle.matrix[puzzle.row][puzzle.col+2] = 'b';
            else
                puzzle.matrix[puzzle.row][puzzle.col+2] = 'B';
        }
        else
        {
            puzzle.matrix[puzzle.row][puzzle.col+1] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
            if (puzzle.matrix[puzzle.row][puzzle.col+2] == ' ')
                puzzle.matrix[puzzle.row][puzzle.col+2] = 'b';
            else
                puzzle.matrix[puzzle.row][puzzle.col+2] = 'B';
        }
    }

    puzzle.col = puzzle.col + 1;
}

void go_south (Puzzle& puzzle)
{
    //               
    assert (true);
    //                
    //                                                                                  

    if (puzzle.matrix[puzzle.row][puzzle.col] == 'W')
    {
        if (puzzle.matrix[puzzle.row+1][puzzle.col] == ' ')
        {
            puzzle.matrix[puzzle.row+1][puzzle.col] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
        }
        else if (puzzle.matrix[puzzle.row+1][puzzle.col] == '.')
        {
            puzzle.matrix[puzzle.row+1][puzzle.col] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
        }
        else if (puzzle.matrix[puzzle.row+1][puzzle.col] == 'b')
        {
            puzzle.matrix[puzzle.row+1][puzzle.col] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
            if (puzzle.matrix[puzzle.row+2][puzzle.col] == ' ')
                puzzle.matrix[puzzle.row+2][puzzle.col] = 'b';
            else
                puzzle.matrix[puzzle.row+2][puzzle.col] = 'B';
        }
        else
        {
            puzzle.matrix[puzzle.row+1][puzzle.col] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
            if (puzzle.matrix[puzzle.row+2][puzzle.col] == ' ')
                puzzle.matrix[puzzle.row+2][puzzle.col] = 'b';
            else
                puzzle.matrix[puzzle.row+2][puzzle.col] = 'B';
        }
    }
    else
    {
        if (puzzle.matrix[puzzle.row+1][puzzle.col] == ' ')
        {
            puzzle.matrix[puzzle.row+1][puzzle.col] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
        }
        else if (puzzle.matrix[puzzle.row+1][puzzle.col] == '.')
        {
            puzzle.matrix[puzzle.row+1][puzzle.col] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
        }
        else if (puzzle.matrix[puzzle.row+1][puzzle.col] == 'b')
        {
            puzzle.matrix[puzzle.row+1][puzzle.col] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
            if (puzzle.matrix[puzzle.row+2][puzzle.col] == ' ')
                puzzle.matrix[puzzle.row+2][puzzle.col] = 'b';
            else
                puzzle.matrix[puzzle.row+2][puzzle.col] = 'B';
        }
        else
        {
            puzzle.matrix[puzzle.row+1][puzzle.col] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
            if (puzzle.matrix[puzzle.row+2][puzzle.col] == ' ')
                puzzle.matrix[puzzle.row+2][puzzle.col] = 'b';
            else
                puzzle.matrix[puzzle.row+2][puzzle.col] = 'B';
        }
    }

    puzzle.row = puzzle.row + 1;
}

void go_west (Puzzle& puzzle)
{
    //               
    assert (true);
    //                
    //                                                                                 

    if (puzzle.matrix[puzzle.row][puzzle.col] == 'W')
    {
        if (puzzle.matrix[puzzle.row][puzzle.col-1] == ' ')
        {
            puzzle.matrix[puzzle.row][puzzle.col-1] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
        }
        else if (puzzle.matrix[puzzle.row][puzzle.col-1] == '.')
        {
            puzzle.matrix[puzzle.row][puzzle.col-1] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
        }
        else if (puzzle.matrix[puzzle.row][puzzle.col-1] == 'b')
        {
            puzzle.matrix[puzzle.row][puzzle.col-1] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
            if (puzzle.matrix[puzzle.row][puzzle.col-2] == ' ')
                puzzle.matrix[puzzle.row][puzzle.col-2] = 'b';
            else
                puzzle.matrix[puzzle.row][puzzle.col-2] = 'B';
        }
        else
        {
            puzzle.matrix[puzzle.row][puzzle.col-1] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = '.';
            if (puzzle.matrix[puzzle.row][puzzle.col-2] == ' ')
                puzzle.matrix[puzzle.row][puzzle.col-2] = 'b';
            else
                puzzle.matrix[puzzle.row][puzzle.col-2] = 'B';
        }
    }
    else
    {
        if (puzzle.matrix[puzzle.row][puzzle.col-1] == ' ')
        {
            puzzle.matrix[puzzle.row][puzzle.col-1] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
        }
        else if (puzzle.matrix[puzzle.row][puzzle.col-1] == '.')
        {
            puzzle.matrix[puzzle.row][puzzle.col-1] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
        }
        else if (puzzle.matrix[puzzle.row][puzzle.col-1] == 'b')
        {
            puzzle.matrix[puzzle.row][puzzle.col-1] = 'w';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
            if (puzzle.matrix[puzzle.row][puzzle.col-2] == ' ')
                puzzle.matrix[puzzle.row][puzzle.col-2] = 'b';
            else
                puzzle.matrix[puzzle.row][puzzle.col-2] = 'B';
        }
        else
        {
            puzzle.matrix[puzzle.row][puzzle.col-1] = 'W';
            puzzle.matrix[puzzle.row][puzzle.col] = ' ';
            if (puzzle.matrix[puzzle.row][puzzle.col-2] == ' ')
                puzzle.matrix[puzzle.row][puzzle.col-2] = 'b';
            else
                puzzle.matrix[puzzle.row][puzzle.col-2] = 'B';
        }
    }

    puzzle.col = puzzle.col - 1;
}

int DFS (Puzzle candidate, vector<Puzzle>& attempts, int height, int width, int steps, int& shortest_so_far)
{
    //               
    assert (height > 0 && width > 0);
    //                
    //                                                                                                                        
    //                                                                                                                        
    //            

    if (is_solution(candidate) && steps < shortest_so_far)
    {
        shortest_so_far = steps;
        return steps;
    }
    if (is_solution(candidate))
        return 500;

    if (steps + 1 > shortest_so_far)
        return 500;

    int north = 500;
    int east = 500;
    int south = 500;
    int west = 500;
    Puzzle temp = candidate;

    if (can_go_north(candidate, width, height))
    {
        go_north(temp);
        temp.steps = steps + 1;
        if(!in_vector(temp, attempts))
        {
            attempts.push_back(temp);
            north = DFS(temp, attempts, height, width, steps+1, shortest_so_far);
        }

        temp = candidate;
    }
    if (can_go_east(candidate, width, height))
    {
        go_east(temp);
        temp.steps = steps + 1;
        if (!in_vector(temp, attempts))
        {
            attempts.push_back(temp);
            east = DFS(temp, attempts, height, width, steps+1, shortest_so_far);
        }

        temp = candidate;
    }
    if (can_go_south(candidate, width, height))
    {
        go_south(temp);
        temp.steps = steps + 1;
        if (!in_vector(temp, attempts))
        {
            attempts.push_back(temp);
            south = DFS(temp, attempts, height, width, steps+1, shortest_so_far);
        }

        temp = candidate;
    }
    if (can_go_west(candidate, width, height))
    {
        go_west(temp);
        temp.steps = steps + 1;
        if (!in_vector(temp, attempts))
        {
            attempts.push_back(temp);
            west = DFS(temp, attempts, height, width, steps+1, shortest_so_far);
        }

        temp = candidate;
    }

    return (min(min(north, east), min(south, west)));
}

void try_all_directions (Puzzle candidate, vector<Puzzle>& attempts, int height, int width, int& attempt)
{
    Puzzle north = candidate;
    Puzzle east = candidate;
    Puzzle south = candidate;
    Puzzle west = candidate;

    if (can_go_north(candidate, width, height))
    {
        go_north(north);
        if(!in_vector(north, attempts))
        {
            attempts.push_back(north);
            attempt++;
        }
    }
    if (can_go_east(candidate, width, height))
    {
        go_east(east);
        if (!in_vector(east, attempts))
        {
            attempts.push_back(east);
            attempt++;
        }
    }
    if (can_go_south(candidate, width, height))
    {
        go_south(south);
        if (!in_vector(south, attempts))
        {
            attempts.push_back(south);
            attempt++;
        }
    }
    if (can_go_west(candidate, width, height))
    {
        go_west(west);
        if (!in_vector(west, attempts))
        {
            attempts.push_back(west);
            attempt++;
        }
    }
}

int BFS (Puzzle candidate, vector<Puzzle>& attempts, int height, int width)
{
    //               
    assert (height > 0 && width > 0);
    //                
    //                                                                                

    if (is_solution(candidate))
        return 0;

    int attempt = 0;
    int base = attempt;
    int steps = 0;

    try_all_directions(candidate, attempts, height, width, attempt);

    while (true)    //                                                       
    {
        steps++;

        for (int i = base; i < attempts.size(); i++)
        {
            if (is_solution(attempts[i]))
                return steps;
        }

        base = attempt;

        for (int i = base; i < attempts.size(); i++)
        {
            try_all_directions(attempts[i], attempts, height, width, attempt);
        }
    }
}

int main()
{
    int width, height;
    Puzzle start = {};
    vector<Puzzle> attempts = {};
    int x = 50; //                    

    ifstream infile;

    open_file(start, infile, width, height);

    int result_DFS = DFS(start, attempts, height, width, 0, x);
    attempts.clear();
    int result_BFS = BFS(start, attempts, height, width);
    cout << "DFS: " << result_DFS << endl << "BFS: " << result_BFS;

    return 0;
}

