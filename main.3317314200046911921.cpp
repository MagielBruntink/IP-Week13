#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
                                                  

                                      

                                                  

                                          
                                          

                                                  
*/

/*
                                                  
                                      
                                                  
*/

enum Occupation {Space = ' ', Wall = '*', Box = 'b', Box_on_dest = 'B', Destination = '.', Worker = 'w', Worker_on_dest = 'W'};

struct Pos {
    int col;
    int row;
};

//                                          
const Pos D_NORTH = { 0, -1};
const Pos D_SOUTH = { 0,  1};
const Pos D_WEST  = {-1,  0};
const Pos D_EAST  = { 1,  0};

Pos operator+(const Pos& a, const Pos& b)
{//               
    assert(true);
 //                
 //                                       
    Pos result = a;
    result.col += b.col;
    result.row += b.row;
    return result;
}

struct Puzzle {
    vector< vector<Occupation> > cells;
    Pos worker_pos;
    int rows;
    int cols;
};

bool operator==(const Puzzle& a, const Puzzle& b)
{//               
    assert(true);
 //                
 //                                                                   
    return (a.cells == b.cells);
}

struct Candidate {
    Puzzle candidate;
    int parent_candidate;
    int moves;
};

bool is_valid_pos(Puzzle& p, Pos& pos)
{//               
    assert(true);
 //                
 //                                                                             
    return (pos.row >= 0 && pos.col >= 0 && pos.row < p.rows && pos.col < p.cols);
}

Occupation cell_at_pos(Puzzle& p, Pos& pos)
{//               
    assert(true);
 //                
 //                                                          
    return p.cells[pos.row][pos.col];
}

int size(vector<Candidate>& v)
{//               
    assert(true);
 //                
 //                                                            
	return static_cast<int>(v.size());
}

int size(vector<Occupation>& v)
{//               
    assert(true);
 //                
 //                                                            
	return static_cast<int>(v.size());
}

int size(vector<Puzzle>& v)
{//               
    assert(true);
 //                
 //                                                            
	return static_cast<int>(v.size());
}

ostream& operator<<(ostream& out, const Puzzle& p)
{//               
    assert(true);
 //                
 //                                                                          
    for (int row = 0; row < p.rows; row++)
    {
        for (int col = 0; col < p.cols; col++)
        {
            out << static_cast<char>(p.cells[row][col]);
        }
        out << endl;
    }
    return out;
}

bool load_challenge(string filename, Puzzle& p)
{//               
    assert(true);
 //                
 //                                                                                            
    ifstream infile(filename.c_str());
    if (infile)
    {
        int row = 0;
        char c;
        while (infile)
        {
            p.cells.push_back(vector<Occupation>());
            infile.get(c);
            while (c != '\n' && infile)
            {
                p.cells[row].push_back(static_cast<Occupation>(c));
                infile.get(c);
                if (c == 'w' || c == 'W')
                {
                    p.worker_pos.row = row;
                    p.worker_pos.col = size(p.cells[row]);
                }
            }
            row++;
        }
        p.cells.pop_back(); //                                
        p.rows = row - 1;
        p.cols = size(p.cells[0]);
        infile.close();
        return true;
    } else {
        cout << "File could not be opened." << endl;
        return false;
    }
}

/*
                                                  
                                  
                                                  
*/

bool puzzle_ready(Puzzle& p)
{//               
    assert(true);
 //                
 //                                                                                                    
    for (int row = 0; row < p.rows; row++)
    {
        for (int col = 0; col < p.cols; col++)
        {
            if (p.cells[row][col] == Box)
                return false;
        }
    }
    return true;
}

bool can_push_box(Puzzle& p, Pos& box_pos, Pos delta)
{//               
    assert(true);
 //                
 //                                                                             
    Pos cell_behind_box = box_pos + delta;
    if (is_valid_pos(p, cell_behind_box))
    {
        switch(cell_at_pos(p, cell_behind_box))
        {
            case Space:
            case Destination:
                return true;
                break;

            default:
                return false;
                break;
        }
    } else {
        return false;
    }
}

bool can_go_here(Puzzle& p, Pos delta)
{//               
    assert(true);
 //                
 //                                                                                                                                              
    Pos new_pos = p.worker_pos + delta;

    if (is_valid_pos(p, new_pos))
    {
        switch(cell_at_pos(p, new_pos))
        {
            case Wall:
                return false;
                break;

            case Box:
            case Box_on_dest:
                return can_push_box(p, new_pos, delta);
                break;

            default:
                return true;
                break;
        }

    } else {
        return false;
    }
}

void move_box(Puzzle& p, Pos box_pos)
{//               
    assert(true);
 //                
 //                                                                
    switch(cell_at_pos(p, box_pos))
    {
        case Space:
            p.cells[box_pos.row][box_pos.col] = Box;
            break;

        case Destination:
            p.cells[box_pos.row][box_pos.col] = Box_on_dest;
            break;
    }
}

void move_worker(Puzzle& p, Pos delta)
{//               
    assert(true);
 //                
 //                                                                   

    //                                    
    switch(cell_at_pos(p, p.worker_pos))
    {
        case Worker:
            p.cells[p.worker_pos.row][p.worker_pos.col] = Space;
            break;

        case Worker_on_dest:
            p.cells[p.worker_pos.row][p.worker_pos.col] = Destination;
            break;
    }

    p.worker_pos = p.worker_pos + delta;

    //                            
    switch(cell_at_pos(p, p.worker_pos))
    {
        case Space:
            p.cells[p.worker_pos.row][p.worker_pos.col] = Worker;
            break;

        case Destination:
            p.cells[p.worker_pos.row][p.worker_pos.col] = Worker_on_dest;
            break;

        case Box:
            move_box(p, p.worker_pos + delta);
            p.cells[p.worker_pos.row][p.worker_pos.col] = Worker;
            break;

        case Box_on_dest:
            move_box(p, p.worker_pos + delta);
            p.cells[p.worker_pos.row][p.worker_pos.col] = Worker_on_dest;
            break;
    }
}

bool puzzle_present_bf(vector<Candidate>& c, Puzzle& new_p)
{//               
    assert(true);
 //                
 //                                                                                         
    for (int i = 0; i<size(c); i++)
    {
        if (c[i].candidate == new_p)
            return true;
    }

    return false;
}

void tries_bf(vector<Candidate>& c, int i, Pos delta)
{//               
    assert(true);
 //                
 //                                                                                                                            
    Puzzle new_p = c[i].candidate;
    move_worker(new_p, delta);
    Candidate new_c = {new_p, i, c[i].moves+1};
    if (!puzzle_present_bf(c, new_p))
        c.push_back(new_c);
}

int solve_breath_first(Puzzle start)
{//               
    assert(true);
 //                
 //                                                                                                         
    vector<Candidate> c = {{start, -1, 0}};
    int i =0;
    while(i < size(c) && !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if (can_go_here(p, D_NORTH)) tries_bf(c, i, D_NORTH);
        if (can_go_here(p, D_SOUTH)) tries_bf(c, i, D_SOUTH);
        if (can_go_here(p, D_WEST))  tries_bf(c, i, D_WEST);
        if (can_go_here(p, D_EAST))  tries_bf(c, i, D_EAST);
        i++;
    }
    if (puzzle_ready(c[i].candidate))
        return c[i].moves;
    else
        return -1;
}

/*
                                                  
                                
                                                  
*/

bool puzzle_present_df(Puzzle& new_p, vector<Puzzle>& attempt)
{//               
    assert(true);
 //                
 //                                                                                
    for (int i = 0; i<size(attempt); i++)
    {
        if (attempt[i] == new_p)
            return true;
    }

    return false;
}

void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void tries_df(vector<Puzzle>& attempt, Pos delta, vector<Puzzle>& shortest, int max_depth)
{//               
    assert(true);
 //                
 //                                                                                                                                             
    Puzzle new_p = attempt[size(attempt)-1];
    move_worker(new_p, delta);
    if (!puzzle_present_df(new_p, attempt))
    {
        attempt.push_back(new_p); //        
        solve_depth_first(attempt, shortest, max_depth);
        attempt.pop_back(); //       
    }
}

void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{//               
    assert(true);
 //                
 //                                                                                       
    const int CURRENT = size(attempt);
    const int BEST = size(shortest);
    Puzzle p = attempt[CURRENT-1];

    if (BEST > 0 && CURRENT >= BEST) return;
    else if (CURRENT > max_depth+1) return;
    else if (puzzle_ready(p))
    {
        shortest = attempt;
        return;
    }
    if (can_go_here(p, D_NORTH)) tries_df(attempt, D_NORTH, shortest, max_depth);
    if (can_go_here(p, D_SOUTH)) tries_df(attempt, D_SOUTH, shortest, max_depth);
    if (can_go_here(p, D_WEST))  tries_df(attempt, D_WEST, shortest, max_depth);
    if (can_go_here(p, D_EAST))  tries_df(attempt, D_EAST, shortest, max_depth);
}

int main()
{
    Puzzle p;
    if (load_challenge("challenge.31.txt", p))
    {
        cout << "Input Puzzle:" << endl;
        cout << p;
        cout << "(size: " << p.rows << 'x' << p.cols << ')' << endl << endl;

        cout << "Minimum number of moves: " << solve_breath_first(p) << " (according to the breath first algorithm)" << endl;
        vector<Puzzle> attempt = {p};
        vector<Puzzle> shortest;
        solve_depth_first(attempt, shortest, 32);
        cout << "Minimum number of moves: " << (size(shortest)-1) << " (according to the depth first algorithm)" << endl;
    }
    return 0;
}

