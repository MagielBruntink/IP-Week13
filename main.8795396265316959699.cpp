//                        
//                       

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

enum Square {wall = 0, emptyc = 1, destination = 2, worker = 3, workerDes = 4, box = 5, boxDes = 6};
const char WALL = '*';
const char EMPTYC = ' ';
const char DESTINATION = '.';
const char WORKER = 'w';
const char WORKERDES = 'W';
const char BOX = 'b';
const char BOXDES = 'B';
const int ROWS = 6;
const int COLS = 11;

struct Candidate
{
    char candidate_world [ROWS][COLS];
    int pos_of_parent;
};

struct best_so_farchar
{
    char direction[ROWS*COLS];
    char best_so_far_world [ROWS][COLS];
};

vector<Candidate> puzzle;

void open_file (ifstream& infile)
{
assert (true);
    string filename;
    cout << "Hello user. Please enter the name of a file that contains a puzzle, so our programme can solve it: " << endl;
    cin >> filename;

    infile.open (filename.c_str());
    if (infile.is_open())
        cout << "File succesfully opened. " << endl;
    else
        cout << "Something went wrong opening the file. " << endl;
}

void display_world (char world [ROWS][COLS])
{
assert(world[0][0] == '*');
    for (int i = 0; i < ROWS; i ++)
    {
        for (int j = 0; j < COLS; j++)
            if ((world[i][j] != ' ') && (world[i][j] != '.') && (world[i][j] != '*') && (world[i][j] != 'w') && (world[i][j] != 'W') && (world[i][j] != 'b') && (world[i][j] != 'B'))
            {
                cout << endl;
                j = COLS;
            }

            else
                cout << world[i][j];
    }
}

void store_world (ifstream& infile, char world[ROWS][COLS])
{
assert (infile.is_open());

//              
//                                                                                                     
    char x;
    for (int i =0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            infile.get(x);
            if ((x != ' ') && (x != '.') && (x != '*') && (x != 'w') && (x != 'W') && (x != 'b') && (x != 'B'))
            {
                world[i][j] = x;
                j = COLS;
            }
            else
            {
                world[i][j] = x;
            }
        }
    }

    infile.close();
    cout << "The data has been stored in the array succesfully. " << endl;
}

void initial_worker_pos (char world [ROWS][COLS], int& i, int& j)
{
    for (i =0; i < ROWS; i++)
    {
        for (j =0; j < COLS; j++)
        {
            if (world[i][j] == 'w' || world[i][j] == 'W')
            return;
        }
    }

}

bool check_direction (char world [ROWS][COLS], int i, int j, int x, int y)
{
assert (0 <= i && i <= ROWS && 0 <= j && j <= COLS);
//              
//                                                                                            

    if ((world[i+x][j+y] == '*') ||
        (world[i+x][j+y] == 'b' && (world[i+x+x][j+y+y] == '*' || world[i+x+x][j+y+y] == 'b' || world[i+x][j+y] == 'B')) ||
        (world[i+x][j+y] == 'B' && (world[i+x+x][j+y+y] == '*' || world[i+x+x][j+y+y] == 'b' || world[i+x][j+y] == 'B'))
        )
        return false;
    return true;
}

bool can_go_north (char world[ROWS][COLS], int i, int j)
{
assert (0 <= i && i <= ROWS && 0 <= j && j <= COLS);
    int x = -1;
    int y = 0;
    if (check_direction (world, i, j, x, y))
        return true;
    return false;
}

bool can_go_east (char world[ROWS][COLS], int i, int j)
{
assert (0 <= i && i <= ROWS && 0 <= j && j <= COLS);
    int x = 0;
    int y = 1;
    if (check_direction (world, i, j, x, y))
        return true;
    return false;
}

bool can_go_south (char world[ROWS][COLS], int i, int j)
{
assert (0 <= i && i <= ROWS && 0 <= j && j <= COLS);
    int x = 1;
    int y = 0;
    if (check_direction (world, i, j, x, y))
        return true;
    return false;
}

bool can_go_west (char world[ROWS][COLS], int i, int j)
{
assert (0 <= i && i <= ROWS && 0 <= j && j <= COLS);
    int x = 0;
    int y = -1;
    if (check_direction (world, i, j, x, y))
        return true;
    return false;
}

void copy_array (char new_array [ROWS][COLS], char old_array [ROWS][COLS])
{
    for (int m =0; m < ROWS; m++)
        for (int g=0; g < COLS; g++)
            new_array[m][g] = old_array[m][g];
}

void go_north (char new_world [ROWS][COLS], char world [ROWS][COLS], int& i, int& j)
{

    assert (0 <= i && i <= ROWS && 0 <= j && j <= COLS);
//              
//                                                     

    copy_array (new_world, world);
    if (new_world[i][j] == 'w')
        new_world[i][j] = ' ';

    if (new_world[i][j] == 'W')
        new_world[i][j] = '.';

    if (new_world[i-1][j] == ' ')
    {
        new_world[i-1][j] = 'w';
        i = i-1;
        return;
    }
    if (new_world[i-1][j] == '.')
    {
        new_world[i-1][j] = 'W';
        i = i-1;
        return;
    }
    if (new_world[i-1][j] == 'b' && new_world[i-2][j] == '.')
    {
        new_world[i-1][j] = 'w';
        new_world[i-2][j] = 'B';
        i = i-1;
        return;
    }
    if (new_world[i-1][j] == 'b' && new_world[i-2][j] == ' ')
    {
        new_world[i-1][j] = 'w';
        new_world[i-2][j] = 'b';
        i = i-1;
        return;
    }
    if (new_world[i-1][j] == 'B' && new_world[i-2][j] == '.')
    {
        new_world[i-1][j] = 'W';
        new_world[i-2][j] = 'B';
        i = i-1;
        return;
    }
    if (new_world[i-1][j] == 'B' && new_world[i-2][j] == ' ')
    {
        new_world[i-1][j] = 'W';
        new_world[i-2][j] = 'b';
        i = i-1;
        return;
    }
}

void go_east (char new_world [ROWS][COLS], char world [ROWS][COLS], int& i, int& j)
{
    assert (0 <= i && i <= ROWS && 0 <= j && j <= COLS);
//              
//                                                     

    copy_array (new_world, world);

    if (new_world[i][j] == 'w')
        new_world[i][j] = ' ';

    if (new_world[i][j] == 'W')
        new_world[i][j] = '.';

    if (new_world[i][j+1] == ' ')
    {
        new_world[i][j+1] = 'w';
        j = j+1;
        return;
    }
    if (new_world[i][j+1] == '.')
    {
        new_world[i][j+1] = 'W';
        j = j+1;
        return;
    }
    if (new_world[i][j+1] == 'b' && new_world[i][j+2] == '.')
    {
        new_world[i][j+1] = 'w';
        new_world[i][j+2] = 'B';
        j = j+1;
        return;
    }
    if (new_world[i][j+1] == 'b' && new_world[i][j+2] == ' ')
    {
        new_world[i][j+1] = 'w';
        new_world[i][j+2] = 'b';
        j = j+1;
        return;
    }
    if (new_world[i][j+1] == 'B' && new_world[i][j+2] == '.')
    {
        new_world[i][j+1] = 'W';
        new_world[i][j+2] = 'B';
        j = j+1;
        return;
    }
    if (new_world[i][j+1] == 'B' && new_world[i][j+2] == ' ')
    {
        new_world[i][j+1] = 'W';
        new_world[i][j+2] = 'b';
        j = j+1;
        return;
    }
}

void go_south (char new_world [ROWS][COLS], char world [ROWS][COLS],int& i, int& j)
{
    assert (0 <= i && i <= ROWS && 0 <= j && j <= COLS);
//              
//                                                     

    copy_array (new_world, world);

    if (new_world[i][j] == 'w')
        new_world[i][j] = ' ';

    if (new_world[i][j] == 'W')
        new_world[i][j] = '.';

    if (new_world[i+1][j] == ' ')
    {
        new_world[i+1][j] = 'w';
        i = i+1;
        return;
    }
    if (new_world[i+1][j] == '.')
    {
        new_world[i+1][j] = 'W';
        i = i+1;
        return;
    }
    if (new_world[i+1][j] == 'b' && new_world[i+2][j] == '.')
    {
        new_world[i+1][j] = 'w';
        new_world[i+2][j] = 'B';
        i = i+1;
        return;
    }
    if (new_world[i+1][j] == 'b' && new_world[i+2][j] == ' ')
    {
        new_world[i+1][j] = 'w';
        new_world[i+2][j] = 'b';
        i = i+1;
        return;
    }
    if (new_world[i+1][j] == 'B' && new_world[i+2][j] == '.')
    {
        new_world[i+1][j] = 'W';
        new_world[i+2][j] = 'B';
        i = i+1;
        return;
    }
    if (new_world[i+1][j] == 'B' && new_world[i+2][j] == ' ')
    {
        new_world[i+1][j] = 'W';
        new_world[i+2][j] = 'b';
        i = i+1;
        return;
    }
}

void go_west (char new_world [ROWS][COLS], char world [ROWS][COLS], int& i, int& j)
{
    assert (0 <= i && i <= ROWS && 0 <= j && j <= COLS);
//              
//                                                     

    copy_array (new_world, world);

    if (new_world[i][j] == 'w')
        new_world[i][j] = ' ';

    if (new_world[i][j] == 'W')
        new_world[i][j] = '.';

    if (new_world[i][j-1] == ' ')
    {
        new_world[i][j-1] = 'w';
        j = j-1;
        return;
    }
    if (new_world[i][j-1] == '.')
    {
        new_world[i][j-1] = 'W';
        j = j-1;
        return;
    }
    if (new_world[i][j-1] == 'b' && new_world[i][j-2] == '.')
    {
        new_world[i][j-1] = 'w';
        new_world[i][j-2] = 'B';
        j = j-1;
        return;
    }
    if (new_world[i][j-1] == 'b' && new_world[i][j-2] == ' ')
    {
        new_world[i][j-1] = 'w';
        new_world[i][j-2] = 'b';
        j = j-1;
        return;
    }
    if (new_world[i][j-1] == 'B' && new_world[i][j-2] == '.')
    {
        new_world[i][j-1] = 'W';
        new_world[i][j-2] = 'B';
        j = j-1;
        return;
    }
    if (new_world[i][j-1] == 'B' && new_world[i][j-2] == ' ')
    {
        new_world[i][j-1] = 'W';
        new_world[i][j-2] = 'b';
        j = j-1;
        return;
    }
}

void initial_vector (char start[ROWS][COLS], vector<Candidate>& c)
{
assert (true);
//              
//                                                                                                                           
    Candidate first;

    copy_array (first.candidate_world, start);
    first.pos_of_parent = -1;

    c.push_back (first);

}

bool check_attempt (char attempt [ROWS][COLS])
{
    int increment = 0;
    for (int i =0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (attempt[i][j] == 'W' || attempt[i][j] == 'b' || attempt[i][j] == '.')
                increment++;
        }
    }
    return (increment == 0);
}

bool check_for_doubles (char kees[ROWS][COLS], char karel [ROWS][COLS])
{
    int incrementation =0;
    for (int m =0; m < ROWS; m++)
        for (int g=0; g < COLS; g++)
            if (kees[m][g] != karel[m][g])
                incrementation++;

    if (incrementation == 0)
        return false;
    return true;

}

void solve_breadth_first (vector<Candidate>& c, char world [ROWS][COLS], int i, int j)
{
assert (true);
//              
//                                                                                                             

    Candidate next_world;
    int parent_pos = 0;
    int pos_in_vector =0;

    char new_world [ROWS][COLS];
for (int k=0; k < pos_in_vector +1; k++)
                if (check_for_doubles(c[k].candidate_world, new_world))
                    c.push_back(next_world);
            pos_in_vector++;
    while (!check_attempt(c[pos_in_vector].candidate_world))
    {
        if (can_go_north(c[pos_in_vector].candidate_world, i, j))
        {
            go_north(new_world, c[pos_in_vector].candidate_world, i, j);
            copy_array (next_world.candidate_world, new_world);
            next_world.pos_of_parent = parent_pos;
            for (int k=0; k < pos_in_vector +1; k++)
                if (check_for_doubles(c[k].candidate_world, new_world))
                    c.push_back(next_world);
            pos_in_vector++;

        }
        if (can_go_east(c[pos_in_vector].candidate_world, i, j))
        {
            go_east(new_world, c[pos_in_vector].candidate_world, i, j);
            copy_array (next_world.candidate_world, new_world);
            next_world.pos_of_parent = parent_pos;
            for (int k=0; k < pos_in_vector +1; k++)
                if (check_for_doubles(c[k].candidate_world, new_world))
                    c.push_back(next_world);
            pos_in_vector++;

        }
        if (can_go_south(c[pos_in_vector].candidate_world, i, j))
        {
            go_south(new_world, c[pos_in_vector].candidate_world, i, j);
            copy_array (next_world.candidate_world, new_world);
            next_world.pos_of_parent = parent_pos;
            for (int k=0; k < pos_in_vector +1; k++)
                if (check_for_doubles(c[k].candidate_world, new_world))
                    c.push_back(next_world);
            pos_in_vector++;
        }
        if (can_go_west(c[pos_in_vector].candidate_world, i, j))
        {
            go_west(new_world, c[pos_in_vector].candidate_world, i, j);
            copy_array (next_world.candidate_world, new_world);
            next_world.pos_of_parent = parent_pos;
            for (int k=0; k < pos_in_vector +1; k++)
                if (check_for_doubles(c[k].candidate_world, new_world))
                    c.push_back(next_world);
            pos_in_vector++;
        }
    parent_pos++;
    }
    cout << "The puzzle has been solved! " << endl;

}

void solve_depth_first (char world[ROWS][COLS])
{
    if (check_attempt(world))
    {

    }
    else
    {

    }
}

int main()
{

    ifstream infile;
    char world [ROWS][COLS];
    //                           
    open_file (infile);
    store_world (infile, world);
    display_world(world);

    int i =0;
    int j = 0;
    initial_worker_pos(world, i, j);
    cout << "Position of worker is: " << i << " and " << j << endl;

    vector<Candidate> c;
    initial_vector(world, c);

    cout << "We will now solve the puzzle: " << endl;
    solve_breadth_first(c, world, i, j);

    return 0;
}

