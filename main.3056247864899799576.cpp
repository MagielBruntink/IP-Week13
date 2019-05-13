#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

/*                              
              
                                
                                
                              */

/*
                                                                                                   
*/

using namespace std;

const int MAX_HEIGHT = 10;
const int MAX_WIDTH = 10;

struct Cell
{
    bool wall;
    bool worker;
    bool box;
    bool destination;
};

struct Pos
{
    int col;
    int row;
};

struct Puzzle
{
    Cell world [MAX_HEIGHT][MAX_WIDTH];
    Pos worker;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

int size (vector<Candidate>& data)
{
    return static_cast<int>(data.size());
}

int size (vector<Puzzle>& data)
{
    return static_cast<int>(data.size());
}

void create_empty_world (Cell world [MAX_HEIGHT][MAX_WIDTH])
{
    assert(true);
    /*         
                           
    */
    for(int i = 0; i < MAX_HEIGHT; i++)
    {
        for(int j = 0; j < MAX_WIDTH; j++)
        {
            world[i][j] = {false, false, false, false};
        }
    }
}

void show_world (Cell world [MAX_HEIGHT][MAX_WIDTH])
{
    assert(true);
    /*         
                      
    */
    for(int i = 0; i < MAX_HEIGHT; i++)
    {
        for(int j = 0; j < MAX_WIDTH; j++)
        {
            if(world[i][j].wall)
            {
                cout << '*';
            }
            else if(world[i][j].worker)
            {
                if(world[i][j].destination)
                {
                    cout << 'W';
                }
                else
                {
                    cout << 'w';
                }
            }
            else if(world[i][j].box)
            {
                if(world[i][j].destination)
                {
                    cout << 'B';
                }
                else
                {
                    cout << 'b';
                }
            }
            else if(world[i][j].destination)
            {
                cout << '.';
            }
            else
            {
                cout << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

void read_world (Puzzle& start)
{
    assert(true);
    /*         
                                               
    */

    ifstream input_file;
    input_file.open("challenge.23.txt");
    int i = 0;
    int j = 0;
    while(input_file)
    {
        char c;
        input_file.get(c);
        if(c == '*')
        {
            start.world[i][j].wall = true;
        }
        if(c == 'w' || c == 'W')
        {
            start.world[i][j].worker = true;
            start.worker.col = j;
            start.worker.row = i;
        }
        if(c == 'b' || c == 'B')
        {
            start.world[i][j].box = true;
        }
        if(c == 'W' || c == 'B' || c == '.')
        {
            start.world[i][j].destination = true;
        }
        if(c == '\n')
        {
            i++;
            j = 0;
        }
        else
        {
            j++;
        }
    }
}

bool solution(Cell world [MAX_HEIGHT][MAX_WIDTH])
{
    assert(true);
    /*         
                                                               
    */

    for(int i = 0; i < MAX_WIDTH; i++)
    {
        for(int j = 0; j < MAX_HEIGHT; j++)
        {
            if(world[i][j].destination)
            {
                if(!world[i][j].box)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

Pos north(Puzzle state)
{
    assert(true);
    /*         
                                             
    */
    return {state.worker.col, state.worker.row - 1};
}

Pos south(Puzzle state)
{
    assert(true);
    /*         
                                             
    */
    return {state.worker.col, state.worker.row + 1};
}

Pos west(Puzzle state)
{
    assert(true);
    /*         
                                            
    */
    return {state.worker.col - 1, state.worker.row};
}

Pos east(Puzzle state)
{
    assert(true);
    /*         
                                            
    */
    return {state.worker.col + 1, state.worker.row};
}

bool can_go_north(Puzzle state)
{
    assert(true);
    /*         
                                                                                       
    */
    if(state.world[state.worker.row - 1][state.worker.col].wall)
    {
        return false;
    }
    if(state.world[state.worker.row - 1][state.worker.col].box)
    {
        if(state.world[state.worker.row - 2][state.worker.col].wall || state.world[state.worker.row - 2][state.worker.col].box)
        {
            return false;
        }
    }
    return true;
}

bool can_go_south(Puzzle state)
{
    assert(true);
    /*         
                                                                                       
    */
    if(state.world[state.worker.row + 1][state.worker.col].wall)
    {
        return false;
    }
    if(state.world[state.worker.row + 1][state.worker.col].box)
    {
        if(state.world[state.worker.row + 2][state.worker.col].wall || state.world[state.worker.row + 2][state.worker.col].box)
        {
            return false;
        }
    }
    return true;
}

bool can_go_west(Puzzle state)
{
    assert(true);
    /*         
                                                                                      
    */
    if(state.world[state.worker.row][state.worker.col - 1].wall)
    {
        return false;
    }
    if(state.world[state.worker.row][state.worker.col - 1].box)
    {
        if(state.world[state.worker.row][state.worker.col - 2].wall || state.world[state.worker.row][state.worker.col - 2].box)
        {
            return false;
        }
    }
    return true;
}

bool can_go_east(Puzzle state)
{
    assert(true);
    /*         
                                                                                      
    */
    if(state.world[state.worker.row][state.worker.col + 1].wall)
    {
        return false;
    }
    if(state.world[state.worker.row][state.worker.col + 1].box)
    {
        if(state.world[state.worker.row][state.worker.col + 2].wall || state.world[state.worker.row][state.worker.col + 2].box)
        {
            return false;
        }
    }
    return true;
}

Puzzle move_empty (Puzzle state, Pos next)
{
    assert(next.col > 0 && next.row > 0);
    /*         
                                                          
    */
    if(state.world[next.row][next.col].box)
    {
        int dir_ver = next.row - state.worker.row;
        int dir_hor = next.col - state.worker.col;

        state.world[next.row + dir_ver][next.col + dir_hor].box = true;
        state.world[next.row][next.col].box = false;
    }

    state.world[next.row][next.col].worker = true;
    state.world[state.worker.row][state.worker.col].worker = false;
    state.worker = next;

    return state;
}

bool equals (Puzzle a, Puzzle b)
{
    assert(true);
    /*         
                                                        
    */
    for(int i = 0; i < MAX_HEIGHT; i++)
    {
        for(int j = 0; j < MAX_WIDTH; j++)
        {
            if(!(a.world[i][j].box == b.world[i][j].box && a.world[i][j].destination == b.world[i][j].destination && a.world[i][j].wall == b.world[i][j].wall && a.world[i][j].worker == b.world[i][j].worker))
            {
                return false;
            }
        }
    }

    return true;
}

bool puzzle_present (vector<Candidate>& c, int i, Puzzle state)
{
    assert(true);
    /*         
                                                             
    */
    while(i > 0)
    {
        if(equals(c[i].candidate, state))
        {
            return true;
        }
        i = c[i].parent_candidate;
    }
    return false;
}

bool depth_puzzle_present(Puzzle state, vector<Puzzle> attempt)
{
    assert(true);
    /*         
                                                           
    */
    int i = size(attempt) - 1;
    while(i > 0)
    {
        if(equals(attempt[i], state))
        {
            return true;
        }
        i--;
    }
    return false;
}

void tries (vector<Candidate>& c, int i, Pos next)
{
    assert(next.row > 0 && next.col > 0);
    /*         
                              
    */
    Puzzle p = c[i].candidate;
    Puzzle newp = move_empty (p, next);
    Candidate newc = {newp, i};
    if(!puzzle_present (c, i, newp))
    {
        c.push_back(newc);
    }
}

void show_path (vector<Candidate>& c, int i)
{
    assert(true);
    /*         
                               
    */
    while(i > 0)
    {
        show_world( c[i].candidate.world);
        i = c[i].parent_candidate;
    }
}

void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void depth_tries (vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth)
{
    assert(max_depth >= 0);
    /*         
                              
    */
    Puzzle p = attempt[size(attempt) - 1];
    Puzzle newp = move_empty(p, next);
    if(!depth_puzzle_present(newp, attempt))
    {
        attempt.push_back(newp);
        depth_first(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    assert(max_depth >= 0);
    /*         
                                             
    */
    const int CURRENT = size(attempt);
    const int BEST = size(shortest);
    Puzzle p = attempt[CURRENT - 1];

    if(BEST > 0 && CURRENT >= BEST)
    {
        return;
    }
    else if(CURRENT > max_depth + 1)
    {
        return;
    }
    else if(solution(p.world))
    {
        shortest = attempt;
        return;
    }
    if(can_go_north(p))
    {
        depth_tries(attempt, north(p), shortest, max_depth);
    }
    if(can_go_south(p))
    {
        depth_tries(attempt, south(p), shortest, max_depth);
    }
    if(can_go_west(p))
    {
        depth_tries(attempt, west(p), shortest, max_depth);
    }
    if(can_go_east(p))
    {
        depth_tries(attempt, east(p), shortest, max_depth);
    }
}

void breadth_first(Puzzle start)
{
    assert(true);
    /*         
                                               
    */
    vector<Candidate> c = {{start, -1}};
    int i = 0;

    while(i < size (c) && !solution( c[i].candidate.world))
    {
        Puzzle p = c[i].candidate;
        if(can_go_north(p))
        {
            tries(c, i, north (p));
        }
        if(can_go_south(p))
        {
            tries(c, i, south (p));
        }
        if(can_go_west(p))
        {
            tries(c, i, west (p));
        }
        if(can_go_east(p))
        {
            tries(c, i, west (p));
        }
        i++;
    }
    if(i < size(c))
    {
        show_path(c, i);
    }
}

void show_solution(vector<Puzzle> shortest)
{
    assert(true);
    /*         
                     
    */
    for(int i = 0; i < size(shortest); i++)
    {
        show_world(shortest[i].world);
    }
}

int main()
{
    Puzzle start;
    vector<Puzzle> attempt;
    vector<Puzzle> shortest;

    create_empty_world(start.world);
    read_world(start);
    attempt.push_back(start);
    show_world(start.world);
    depth_first(attempt, shortest, 24);
    show_solution(shortest);

}

