#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

//                                       
//                                 

using namespace std;

enum Celll {Empty_space, Wall, Worker, Worker_on_d, Box, Box_on_d, Destination};

typedef vector<vector<Celll>> Universe;

struct Pos
{
    int row, col;
};

struct Puzzle
{
    Universe universe;
    Pos worker_at;
};

struct Candidate
{
    Puzzle universe;
    int parent_candidate;
};

void get_worker_pos(Universe universe, int& worker_row, int& worker_col)
{//              
    assert(true);
    /*               
                                                        
    */
    bool flag_stop = false;
    for (int i = 0; i < universe.size() && !flag_stop; i++)
    {
        for (int j = 0; j < universe[i].size() && !flag_stop; j++)
        {
            if(universe[i][j] == Worker || universe[i][j] == Worker_on_d)
            {
                worker_row = i;
                worker_col = j;
                flag_stop = true;
            }
        }
    }
}

void read_universe_file(ifstream& inputfile, string filename, Universe& universe)
{//              
    assert(true);
    /*               
                                             
    */
    inputfile.open(filename.c_str());
    string current_line;
    char current_cell;
    int i = 0;
    while(getline(inputfile, current_line))
    {
        universe.push_back(vector<Celll>());
        for (int j = 0; j < current_line.size(); j++)
        {
            current_cell = current_line.at(j);
            if (current_cell == '*')
                universe[i].push_back(Wall);
            else if (current_cell == ' ')
                universe[i].push_back(Empty_space);
            else if (current_cell == '.')
                universe[i].push_back(Destination);
            else if (current_cell == 'w')
                universe[i].push_back(Worker);
            else if (current_cell == 'W')
                universe[i].push_back(Worker_on_d);
            else if (current_cell == 'b')
                universe[i].push_back(Box);
            else if (current_cell == 'B')
                universe[i].push_back(Box_on_d);
        }
        i++;
    }
    inputfile.clear();
    inputfile.close();
}

void show_universe(Universe& universe)
{//              
    assert(true);
    /*               
                                       
    */
    Celll current_cell;
    cout << '\n';
    for (int i = 0; i < universe.size(); i++)
    {
        for (int j = 0; j < universe[i].size(); j++)
        {
            current_cell = universe[i][j];
            if (current_cell == Wall)
                cout << "*";
            else if (current_cell == Worker)
                cout << "w";
            else if (current_cell == Worker_on_d)
                cout << "W";
            else if (current_cell == Box)
                cout << "b";
            else if (current_cell == Box_on_d)
                cout << "B";
            else if (current_cell == Destination)
                cout << ".";
            else
                cout << " ";
        }
        cout << '\n';
    }
}

bool can_go_north (Puzzle p)
{//              
    assert(true);
    /*               
                                                          
    */
    if (p.universe[p.worker_at.row-1][p.worker_at.col] == Empty_space || p.universe[p.worker_at.row-1][p.worker_at.col] == Destination)
        return true;
    else if ((p.universe[p.worker_at.row-1][p.worker_at.col] == Box || p.universe[p.worker_at.row-1][p.worker_at.col] == Box_on_d) && (p.universe[p.worker_at.row-2][p.worker_at.col] == Empty_space || p.universe[p.worker_at.row-2][p.worker_at.col] == Destination))
        return true;
    else
        return false;
}

bool can_go_south (Puzzle p)
{//              
    assert(true);
    /*               
                                                          
    */
    if (p.universe[p.worker_at.row+1][p.worker_at.col] == Empty_space || p.universe[p.worker_at.row+1][p.worker_at.col] == Destination)
        return true;
    else if ((p.universe[p.worker_at.row+1][p.worker_at.col] == Box || p.universe[p.worker_at.row+1][p.worker_at.col] == Box_on_d) && (p.universe[p.worker_at.row+2][p.worker_at.col] == Empty_space || p.universe[p.worker_at.row+2][p.worker_at.col] == Destination))
        return true;
    else
        return false;
}

bool can_go_west (Puzzle p)
{//              
    assert(true);
    /*               
                                                         
    */
    if (p.universe[p.worker_at.row][p.worker_at.col-1] == Empty_space || p.universe[p.worker_at.row][p.worker_at.col-1] == Destination)
        return true;
    else if ((p.universe[p.worker_at.row][p.worker_at.col-1] == Box || p.universe[p.worker_at.row][p.worker_at.col-1] == Box_on_d) && (p.universe[p.worker_at.row][p.worker_at.col-2] == Empty_space || p.universe[p.worker_at.row][p.worker_at.col-2] == Destination))
        return true;
    else
        return false;
}

bool can_go_east (Puzzle p)
{//              
    assert(true);
    /*               
                                                         
    */
    if (p.universe[p.worker_at.row][p.worker_at.col+1] == Empty_space || p.universe[p.worker_at.row][p.worker_at.col+1] == Destination)
        return true;
    else if ((p.universe[p.worker_at.row][p.worker_at.col+1] == Box || p.universe[p.worker_at.row][p.worker_at.col+1] == Box_on_d) && (p.universe[p.worker_at.row][p.worker_at.col+2] == Empty_space || p.universe[p.worker_at.row][p.worker_at.col+2] == Destination))
        return true;
    else
        return false;
}

Pos north (Puzzle p)
{//              
    assert(true);
    /*               
                                                         
    */
    p.worker_at.row--;
    return p.worker_at;
}

Pos south (Puzzle p)
{//              
    assert(true);
    /*               
                                                         
    */
    p.worker_at.row++;
    return p.worker_at;
}

Pos east (Puzzle p)
{//              
    assert(true);
    /*               
                                                        
    */
    p.worker_at.col++;
    return p.worker_at;
}

Pos west (Puzzle p)
{//              
    assert(true);
    /*               
                                                        
    */
    p.worker_at.col--;
    return p.worker_at;
}

Puzzle move_worker (Puzzle p, Pos next)
{//              
    assert(true);
    /*               
                                                         
    */
    if (p.universe[next.row][next.col] == Empty_space)
        p.universe[next.row][next.col] = Worker;
    else if (p.universe[next.row][next.col] == Destination)
        p.universe[next.row][next.col] = Worker_on_d;
    else
    {
        if (p.worker_at.row + 1 == next.row)  // 
        {
            if (p.universe[next.row + 1][next.col] == Empty_space)
                p.universe[next.row + 1][next.col] = Box;
            else
                p.universe[next.row + 1][next.col] = Box_on_d;
        }
        else if (p.worker_at.row - 1 == next.row) // 
        {
            if (p.universe[next.row - 1][next.col] == Empty_space)
                p.universe[next.row - 1][next.col] = Box;
            else
                p.universe[next.row - 1][next.col] = Box_on_d;
        }
        else if (p.worker_at.col + 1 == next.col)  // 
        {
            if (p.universe[next.row][next.col + 1] == Empty_space)
                p.universe[next.row][next.col + 1] = Box;
            else
                p.universe[next.row][next.col + 1] = Box_on_d;
        }
        else if (p.worker_at.col - 1 == next.col)  // 
        {
            if (p.universe[next.row][next.col - 1] == Empty_space)
                p.universe[next.row][next.col - 1] = Box;
            else
                p.universe[next.row][next.col - 1] = Box_on_d;
        }

        if (p.universe[next.row][next.col] == Box)
            p.universe[next.row][next.col] = Worker;
        else
            p.universe[next.row][next.col] = Worker_on_d;
    }
    if (p.universe[p.worker_at.row][p.worker_at.col] == Worker)
        p.universe[p.worker_at.row][p.worker_at.col] = Empty_space;
    else if (p.universe[p.worker_at.row][p.worker_at.col] == Worker_on_d)
        p.universe[p.worker_at.row][p.worker_at.col] = Destination;

    p.worker_at = next;
    return p;
}

bool puzzle_present_breath (vector<Candidate>&  c, Puzzle p_to_check)
{//              
    assert(true);
    /*               
                                                         
    */
    for (int i = 0; i < c.size(); i++)
    {
        if (p_to_check.universe == c[i].universe.universe && p_to_check.worker_at.col == c[i].universe.worker_at.col && p_to_check.worker_at.row == c[i].universe.worker_at.row)
            return true;
    }
    return false;
}

bool puzzle_present_depth (vector<Puzzle>&  c, Puzzle p_to_check)
{//              
    assert(true);
    /*               
                                                
    */
    for (int i = 0; i < c.size(); i++)
    {
        if (p_to_check.universe == c[i].universe && p_to_check.worker_at.col == c[i].worker_at.col && p_to_check.worker_at.row == c[i].worker_at.row)
            return true;
    }
    return false;
}

bool puzzle_ready (Universe universe)
{//              
    assert(true);
    /*               
                                                 
    */
    for (int i = 0; i < universe.size(); i++)
    {
        for (int j = 0; j < universe[i].size(); j++)
        {
            if (universe[i][j] == Box)
            {
                return false;
            }
        }
    }
    return true;
}

void tries_breadth (vector<Candidate>&  c, int i, Pos next)
{//              
    assert(i >= 0);
    /*               
                                                                                  
    */
    Puzzle p = c[i].universe;
    Puzzle newp = move_worker(p, next);
    Candidate newc = {newp, i};
    if (!puzzle_present_breath(c, newp))
        c.push_back(newc);
}

void show_path (vector<Candidate>&  c, int i)
{//              
    assert(true);
    /*               
                                                                         
    */
    if (i < 0)
        return;
    else
    {
        show_path(c, c[i].parent_candidate);
        show_universe(c[i].universe.universe);
    }
}

void breadth_first_search (Puzzle start)
{//              
    assert(true);
    /*               
                                                     
    */
    vector<Candidate> c;
    c.push_back({start, -1});
    int i = 0;
    while(i < c.size() && !puzzle_ready(c[i].universe.universe))
    {
        Puzzle p = c[i].universe;
        if(can_go_north(p))
            tries_breadth(c, i, north(p));
        if(can_go_south(p))
            tries_breadth(c, i, south(p));
        if(can_go_west(p))
            tries_breadth(c, i, west(p));
        if(can_go_east(p))
            tries_breadth(c, i, east(p));
        i++;
    }
    if(i < c.size())
        show_path(c, i);
}

void solve_depth (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void tries_depth (vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth)
{//              
    assert(max_depth >= 0);
    /*               
                                                                     
    */
    Puzzle p = attempt[attempt.size() - 1];
    Puzzle newp = move_worker(p, next);
    if (!puzzle_present_depth(attempt, newp))
    {
        attempt.push_back(newp);
        solve_depth(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void solve_depth (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{//              
    assert(max_depth >= 0);
    /*               
                                                                                                                   
    */
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle p = attempt[CURRENT-1];
    if (BEST > 0 && CURRENT >= BEST)
        return;
    else if (CURRENT > max_depth+1)
        return;
    else if (puzzle_ready(p.universe))
    {
        shortest = attempt;
        return;
    }
    if(can_go_north(p))
        tries_depth(attempt, north(p), shortest, max_depth);
    if(can_go_south(p))
        tries_depth(attempt, south(p), shortest, max_depth);
    if(can_go_west(p))
        tries_depth(attempt, west(p), shortest, max_depth);
    if(can_go_east(p))
        tries_depth(attempt, east(p), shortest, max_depth);
}

void show_solution (vector<Puzzle>& v_to_show)
{//              
    assert(true);
    /*               
                                                     
    */
    for (int i = 0; i < v_to_show.size(); i++)
        show_universe(v_to_show[i].universe);
}

int main()
{
    ifstream infile;
    Universe universe;
    read_universe_file(infile, "challenge.1.a.txt", universe);
    int worker_row, worker_col;
    get_worker_pos(universe, worker_row, worker_col);
    Puzzle p = {universe, {worker_row, worker_col}};
    breadth_first_search(p);
    vector<Puzzle> attempt = {p};
    vector<Puzzle> best;
    solve_depth(attempt, best, 2);
    show_solution(best);
    return 0;
}

