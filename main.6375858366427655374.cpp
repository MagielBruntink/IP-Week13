#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

//                              
//                              

enum type { worker = 0, wall, box, empty};
enum direction { north = 0, east, south, west};

struct Pos {
    int col;
    int row;
};

struct Cell {
    type type_cell;
    bool dest;
};

struct Sokoban {
    vector<Cell> cells;
    Pos worker;
    int width;
    int height;
};

struct Solution {
    Sokoban puzzle;
    vector<Sokoban> path;
};

struct Candidate {
    Sokoban candidate;
    int parent_candidate;
};

vector<direction> directions {north, east, south, west};

int size (vector<direction>& directions)
{
    return static_cast<int> (directions.size());
}

int size (vector<Cell>& cells)
{
    return static_cast<int> (cells.size());
}

int size (vector<Candidate> candidates)
{
    return static_cast<int> (candidates.size());
}

Sokoban construct_puzzle(int height, vector<Cell> cells)
{
//                
    assert( height > 0);
//                 
//                                                                  

    Sokoban puzzle;
    puzzle.width = cells.size() / height;
    puzzle.height = height;
    puzzle.cells = cells;

    bool worker_found = false;
    for (int n = 0; n < cells.size() && !worker_found; n++) {
        if (cells[n].type_cell == worker) {
            puzzle.worker.col = n % puzzle.width;
            puzzle.worker.row = n / puzzle.width;
            worker_found = true;
        }
    }

    return puzzle;
}

Cell set_cell(char c)
{
//                
    assert(c == '*' || c == ' ' || c == '.' || c == 'w' || c == 'W' || c == 'b' || c == 'B');
//                 
//                                                                                 

    Cell cell;

    if (c == '*')
    {
        cell.dest = false;
        cell.type_cell = wall;
    } else if (c == '.')
    {
        cell.dest = true;
        cell.type_cell = empty;
    } else if (c == ' ')
    {
        cell.dest = false;
        cell.type_cell = empty;
    } else if (c == 'B')
    {
        cell.dest = true;
        cell.type_cell = box;
    } else if (c == 'b')
    {
        cell.dest = false;
        cell.type_cell = box;
    } else if (c == 'W')
    {
        cell.dest = true;
        cell.type_cell = worker;
    } else if (c == 'w')
    {
        cell.dest = false;
        cell.type_cell = worker;
    }

    return cell;
}

ostream& operator<<(ostream& outfile, const Cell& cell)
{
//                
    assert( true);
//                 
//                                              

    if (cell.type_cell == wall)
        return outfile << '*';
    else if (cell.type_cell == empty && cell.dest)
        return outfile << '.';
    else if (cell.type_cell == empty && !cell.dest)
        return outfile << ' ';
    else if (cell.type_cell == box && cell.dest)
        return outfile << 'B';
    else if (cell.type_cell == box && !cell.dest)
        return outfile << 'b';
    else if (cell.type_cell == worker && cell.dest)
        return outfile << 'W';
    else if (cell.type_cell == worker && !cell.dest)
        return outfile << 'w';
}

bool operator== (const Cell& a, const Cell& b)
{
    if (a.dest == b.dest)
        if (a.type_cell == b.type_cell)
            return true;
    return false;
}

bool operator!= (const Cell& a, const Cell& b)
{
    return !(a == b);
}

bool operator== (const Sokoban& a, const Sokoban& b)
{
    for (int x = 0; x < a.cells.size(); x++)
        if (a.cells[x] != b.cells[x])
            return false;
    return true;
}

bool moveable (Pos pos, direction direc, int width, int height)
{
//                
    assert ( true);
//                 
//                                                                         

    if (direc == north)
        return pos.row > 0;
    else if (direc == east)
        return pos.col + 1 < width;
    else if (direc == south)
        return pos.row + 1 < height;
    else if (direc == west)
        return pos.col > 0;
}

Pos move_worker(const Pos& pos, direction direc)
{
//                
    assert(!(pos.col == 0 && direc == west) && !(pos.row == 0 && direc == north));
//                 
//                                                                 

    if (direc == north)
        return {pos.col, pos.row - 1};
    if (direc == east)
        return {pos.col + 1, pos.row};
    if (direc == south)
        return {pos.col, pos.row + 1};
    if (direc == west)
        return {pos.col - 1, pos.row};
}

void print_sokoban (Sokoban puzzle)
{
//                
    assert( true);
//                 
//                                                

    for (int x = 0; x < puzzle.cells.size(); x++)
    {
        cout << puzzle.cells[x];

        if ((x + 1) % puzzle.width == 0)
            cout << "\n";
    }

    return;
}

void print_path (Solution& solution)
{
//                
    assert( true);
//                 
//                                                              

    for (int x = 0; x < solution.path.size(); x++)
    {
        print_sokoban(solution.path[x]);
        cout << endl;
    }

    return;
}

void read_sokoban (ifstream& infile, Sokoban& puzzle)
{
//                
    assert( true);
//                 
//                                                         

    string line;
    char c;
    int height = 0;
    vector<Cell> cells;
    Cell cell;

    while (getline(infile, line))
    {
        height++;

        for(char c : line)
        {
            cell = set_cell(c);
            cells.push_back(cell);
        }
    }

    puzzle = construct_puzzle(height, cells);

    return;
}

bool puzzle_present (vector<Candidate>& candidates, Sokoban puzzle)
{
//                
    assert ( true);
//                 
//                                                                                                   

    for (int x = 0; x < candidates.size(); x++)
        if (candidates[x].candidate == puzzle)
            return true;
    return false;
}

bool puzzle_ready (Sokoban candidate)
{
//                
    assert ( true);
//                 
//                                                                

    for (int n = 0; n < candidate.cells.size(); n++)
        if (candidate.cells[n].type_cell == box && !candidate.cells[n].dest)
            return false;

    return true;
}

Cell puzzle_at(const Sokoban& puzzle, Pos pos)
{
//                
    assert ( true);
//                 
//                                                                   

    return puzzle.cells[pos.col + pos.row * puzzle.width];
}

void type_at(Sokoban& puzzle, type type, Pos pos)
{
//                
    assert ( true);
//                                                               

    puzzle.cells[pos.col + pos.row * puzzle.width].type_cell = type;
}

bool move_to_direc(const Sokoban& puzzle, direction direc)
{
//                
    assert( true);
//                 
//                                                                          

    if (!moveable(puzzle.worker, direc, puzzle.width, puzzle.height))
        return false;

    Pos newp = move_worker(puzzle.worker, direc);
    Cell cell = puzzle_at(puzzle, newp);

    if (cell.type_cell == wall)
        return false;
    if (cell.type_cell == box)
    {
        if (!moveable(newp, direc, puzzle.width, puzzle.height))
            return false;

        Pos newbp = move_worker(newp, direc);
        Cell wanted = puzzle_at(puzzle, newbp);

        if (wanted.type_cell != empty)
            return false;
    }

    return true;
}

void empty_move(Sokoban& puzzle, direction direc)
{
//                
    assert(move_to_direc(puzzle, direc));
//                 
//                                                       

    Pos newp = move_worker(puzzle.worker, direc);
    Cell newc = puzzle_at(puzzle, newp);

    if (newc.type_cell == box) {
        Pos newbp = move_worker(newp, direc);
        type_at(puzzle, box, newbp);
    }

    type_at(puzzle, empty, puzzle.worker);
    type_at(puzzle, worker, newp);
    puzzle.worker = newp;

    return;
}

void tries (vector<Candidate>& c, int i, direction direc)
{
//                
    assert ( i < c.size() && i >= 0);
//                 
//                                                   

    Sokoban p = c[i].candidate;

    empty_move(p, direc);

    if (!puzzle_present(c, p))
        c.push_back({p, i});
}

vector<Sokoban>& show_path(const vector<Candidate>& c, int i, vector<Sokoban>& path)
{
//                
    assert( true);
//                 
//                                              

    if (i >= 0) {
        show_path(c, c[i].parent_candidate, path);
        path.push_back(c[i].candidate);
    }

    return path;
}

Solution breadth_first (Sokoban first)
{
//                
    assert ( true);
//                 
//                                                                    

    Solution solution;
    int i = 0;
    vector<Candidate> c = {{first, -1}};
    vector<Sokoban> path;

    while (i < c.size() && !puzzle_ready(c[i].candidate))
    {
        Sokoban p = c[i].candidate;
        for (direction x : directions)
            if (move_to_direc(p, x))
                tries(c, i, x);
        i += 1;
    }

    if ( i < c.size())
    {
        solution.puzzle = c[i].candidate;
        solution.path = show_path(c, i, path);
    }

    return solution;
}

bool in_list (vector<Sokoban>& attempt, Sokoban& puzzle)
{
//                
    assert (true);
//                                                               

    for (int x = 0; x < attempt.size(); x++)
        if (attempt[x] == puzzle)
            return true;
    return false;
}

void solve (vector<Sokoban>& attempt, vector<Sokoban>& shortest, int limit);

void depth (vector<Sokoban>& attempt, vector<Sokoban>& shortest, direction direc, int limit)
{
//                
    assert ( true);
//                 
//                                                                                  

    Sokoban p = attempt[attempt.size()-1];

    empty_move(p, direc);

    if (!in_list(attempt, p))
    {
        attempt.push_back(p);
        solve(attempt, shortest, limit);
        attempt.pop_back();
    }
}

void solve (vector<Sokoban>& attempt, vector<Sokoban>& shortest, int limit)
{
//                
    assert ( true);
//                 
//                                                                             

    Sokoban p = attempt[attempt.size()-1];

    if ((shortest.empty() || attempt.size() < shortest.size()) && puzzle_ready(p))
        shortest = attempt;
    else if (attempt.size() < limit)
    {
        for (direction direc : directions)
            if (move_to_direc(p, direc))
                depth(attempt, shortest, direc, limit);
    }
}

Solution depth_first (Sokoban puzzle, int limit)
{
//                
    assert ( true);
//                 
//                                                           

    vector<Sokoban> shortest;
    vector<Sokoban> attempt = {puzzle};
    Solution solution;

    solve(attempt, shortest, limit);

    if (!shortest.empty())
    {
        solution.puzzle = shortest.back();
        solution.path = shortest;
    }

    return solution;
}

int main()
{
    ifstream infile;
    infile.open("challenge.34.txt");
    Sokoban puzzle;
    Solution solution;
    read_sokoban(infile, puzzle);

/*         
                               
     
                                         
                                                                                                     
                                     
                                       
                                  
                               
          
                                            
*/
//         
    solution = depth_first(puzzle, 35);
    if (!solution.path.empty())
    {
        cout << "It took " << solution.path.size() - 1 << " steps for depth-first search." << endl;
        cout << "\nSolution" << endl;
        print_sokoban(solution.puzzle);
        //                        
        //                     
    } else
        cout << "No solution found" << endl;

    infile.close();
    return 0;
}

