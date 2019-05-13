#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cassert>

using namespace std;

//                            

enum class cell_type {
    wall, empty, worker, box
};

enum class direction {
    north, east, south, west
};

direction SEARCH_DIRECTIONS[] = { direction::north, direction::south, direction::west, direction::east };

struct position {
    size_t c;
    size_t r;
};

struct Cell {
    cell_type type;
    bool destination;
};

struct Puzzle {
    vector<Cell> cells;
    position worker;
    size_t width;
    size_t length;
};

struct Solution {
    bool solved;
    Puzzle puzzle;
    vector<Puzzle> path;
};

struct Candidate {
    Puzzle puzzle;
    int parent;
};

bool position_can_move(const position& position, direction dir, size_t width, size_t length) {
    assert(true);
    //                                                                                                         

    switch (dir) {
        case direction::north:  return position.r > 0;
        case direction::east:   return position.c + 1 < width;
        case direction::south:  return position.r + 1 < length;
        case direction::west:   return position.c > 0;
    }
}

position position_move(const position& position, direction dir) {
    assert(!(position.c == 0 && dir == direction::west));
    assert(!(position.r == 0 && dir == direction::north));
    //                                                  

    switch (dir) {
        case direction::north:  return { position.c, position.r - 1 };
        case direction::east:   return { position.c + 1, position.r };
        case direction::south:  return { position.c, position.r + 1 };
        case direction::west:   return { position.c - 1, position.r };
    }
}
bool operator==(const position& left, const position& right) {
    return left.c == right.c && left.r == right.r;
}

bool operator!=(const position& left, const position& right) {
    return !(left == right);
}

Cell cell_from_char(char c) {
    assert(c == '*' || c == ' ' || c == '.' || c == 'w' || c == 'W' || c == 'b' || c == 'B');
    //                                                                       

    Cell cell;

    switch (c) {
        case '*': cell.type = cell_type::wall;   cell.destination = false; break;
        case ' ': cell.type = cell_type::empty;  cell.destination = false; break;
        case '.': cell.type = cell_type::empty;  cell.destination = true;  break;
        case 'w': cell.type = cell_type::worker; cell.destination = false; break;
        case 'W': cell.type = cell_type::worker; cell.destination = true;  break;
        case 'b': cell.type = cell_type::box;    cell.destination = false; break;
        case 'B': cell.type = cell_type::box;    cell.destination = true;  break;
    }

    return cell;
}
bool operator==(const Cell& left, const Cell& right) {
    return left.type == right.type && left.destination == right.destination;
}

bool operator!=(const Cell& left, const Cell& right) {
    return !(left == right);
}

Puzzle make_puzzle(size_t length, vector<Cell> cells) {
    assert(length != 0);
    //                                                    

    Puzzle puzzle;
    puzzle.cells = cells;
    puzzle.length = length;
    puzzle.width = cells.size() / length;

    bool found = false;
    for (size_t i = 0; i < cells.size() && !found; ++i) {
        if (cells[i].type == cell_type::worker) {
            puzzle.worker.c = i % puzzle.width;
            puzzle.worker.r = i / puzzle.width;
            found = true;
        }
    }

    return puzzle;
}
bool operator==(const Puzzle& left, const Puzzle& right) {
    assert(true);
    //                                                                       

    if (left.worker != right.worker) return false;

    for (size_t i = 0; i < left.cells.size(); ++i) {
        if (left.cells[i] != right.cells[i]) return false;
    }

    return true;
}

bool operator!=(const Puzzle& left, const Puzzle& right) {
    return !(left == right);
}

bool puzzle_completed(const Puzzle& puzzle) {
    assert(true);
    //                                                                                                

    //                                                                                        
    for(Cell cell : puzzle.cells) {
        if(cell.type == cell_type::box && !cell.destination) return false;
    }

    return true;
}

Cell puzzle_at(const Puzzle& puzzle, position position) {
    //                                                       
    return puzzle.cells[position.c + position.r * puzzle.width];
}

void puzzle_set_type_at(Puzzle& puzzle, cell_type type, position position) {
    //                                                         
    puzzle.cells[position.c + position.r * puzzle.width].type = type;
}

bool puzzle_can_move(const Puzzle& puzzle, direction dir) {
    assert(true);
    //                                                                      

    //                                                         
    if (!position_can_move(puzzle.worker, dir, puzzle.width, puzzle.length)) return false;
    position new_position = position_move(puzzle.worker, dir);
    Cell cell = puzzle_at(puzzle, new_position);

    if (cell.type == cell_type::wall) return false;
    if (cell.type == cell_type::box) {
        if (!position_can_move(new_position, dir, puzzle.width, puzzle.length)) return false;

        position new_box_position = position_move(new_position, dir);
        Cell target_cell = puzzle_at(puzzle, new_box_position);

        if (target_cell.type != cell_type::empty) return false;
    }

    return true;
}

void puzzle_move(Puzzle& puzzle, direction dir) {
    assert(puzzle_can_move(puzzle, dir));
    //                                          

    //                                                                                               
    position new_position = position_move(puzzle.worker, dir);
    Cell new_cell = puzzle_at(puzzle, new_position);

    if (new_cell.type == cell_type::box) {
        position new_box_position = position_move(new_position, dir);

        puzzle_set_type_at(puzzle, cell_type::box, new_box_position);
    }
    puzzle_set_type_at(puzzle, cell_type::empty, puzzle.worker);
    puzzle_set_type_at(puzzle, cell_type::worker, new_position);
    puzzle.worker = new_position;
}
ostream& operator<<(ostream& os, const Cell& cell) {
    assert(true);
    //                                  

    switch (cell.type) {
        case cell_type::wall:   return os << '*';
        case cell_type::empty:  return os << (cell.destination ? '.' : ' ');
        case cell_type::worker: return os << (cell.destination ? 'W' : 'w');
        case cell_type::box:    return os << (cell.destination ? 'B' : 'b');
    }
}

ostream& operator<<(ostream& os, const Puzzle& puzzle) {
    assert(true);
    //                                    

    //                                
    for (size_t i = 0; i < puzzle.cells.size(); ++i) {
        os << puzzle.cells[i];
        if ((i + 1) % puzzle.width == 0) os << endl;
    }

    return os;
}

ostream& operator<<(ostream& os, const Solution& solution) {
    assert(true);
    //                                                            

    for (const Puzzle& node : solution.path) {
        os << node << endl;
    }

    return os;
}

istream& operator>>(istream& is, Puzzle& puzzle) {
    assert(true);
    //                                                      

    string line;
    size_t lines = 0;
    vector<Cell> cells;
    while (std::getline(is, line)) {
        if(line.empty() || line == "\r") continue;

        lines += 1;

        for(char c : line) {
            if(c == '\r') continue;

            Cell cell = cell_from_char(c);
            cells.push_back(cell);
        }
    }

    puzzle = make_puzzle(lines, cells);

    return is;
}

bool puzzle_present(const vector<Candidate>& c, const Puzzle& puzzle) {
    assert(true);
    //                                                    
    for(const Candidate& candidate : c) {
        if(candidate.puzzle == puzzle) return true;
    }

    return false;
}

void try_bfs(vector<Candidate>& c, int i, direction dir) {
    assert(i >= 0 && i < c.size());
    //                                                                                                                 

    //                                        
    Puzzle puzzle = c[i].puzzle;
    puzzle_move(puzzle, dir);

     if (!puzzle_present(c, puzzle)) {
        c.push_back({ puzzle, i });
    }
}

vector<Puzzle>& build_path(const vector<Candidate>& c, int i, vector<Puzzle>& path) {
    assert(true);
    //                                                                            

    if (i >= 0) {
        build_path(c, c[i].parent, path);

        path.push_back(c[i].puzzle);
    }

    return path;
}

Solution solve_bfs(Puzzle start) {
    assert(true);
    //                                                                                

    int i = 0;
    vector<Puzzle> path;
    vector<Candidate> c = { { start, -1 } }; //                                                               
    Solution solution;

    for (; i < c.size() && !puzzle_completed(c[i].puzzle); ++i) {
        Puzzle puzzle = c[i].puzzle;

        for (direction dir : SEARCH_DIRECTIONS) {
            if (puzzle_can_move(puzzle, dir)) try_bfs(c, i, dir);
        }
    }
    solution.solved = i < c.size();
    if(solution.solved) {
                solution.puzzle = c[i].puzzle;
        solution.path = build_path(c, i, path);
    }

    return solution;
}

void solve_dfs(vector<Puzzle>& p, vector<Puzzle>& b, size_t depth_limit);

bool has_puzzle(const vector<Puzzle>& p, const Puzzle& puzzle) {
    //                            
    for(const Puzzle& element : p) {
        if(element == puzzle) return true;
    }

    return false;
}

void try_dfs(vector<Puzzle>& p, vector<Puzzle>& b, direction dir, size_t depth_limit) {
    assert(!p.empty());
    //                                                                                                                   
    //                                              

    //                                                                                             
    Puzzle puzzle = p.back();

    puzzle_move(puzzle, dir);

    if (!has_puzzle(p, puzzle)) {
        p.push_back(puzzle);

        solve_dfs(p, b, depth_limit);

        p.pop_back();
    }
}

void solve_dfs(vector<Puzzle>& p, vector<Puzzle>& b, size_t depth_limit) {
    assert(!p.empty());
    //                                                                                                                          
    //                                              

    //                                                                                             
    Puzzle puzzle = p.back();
    bool better_potential_solution = b.empty() || p.size() < b.size();

    if (puzzle_completed(puzzle)) {
        if (better_potential_solution) {
            b = p;
        }
    } else if (p.size() < depth_limit && better_potential_solution) {

        for (direction dir : SEARCH_DIRECTIONS) {
            if (puzzle_can_move(puzzle, dir)) try_dfs(p, b, dir, depth_limit);
        }
    }
}

Solution solve_dfs(Puzzle puzzle, size_t depth_limit = 32) {
    assert(true);
    //                                                                                                   

    vector<Puzzle> best;
    vector<Puzzle> p = { puzzle };
    Solution solution;
    solve_dfs(p, best, depth_limit);

    solution.solved = !best.empty();
    if(solution.solved) {
        solution.puzzle = best.back();
        solution.path = best;
    }

    return solution;
}

int main() {
    ifstream is{"../challenge1.txt"};
    Puzzle puzzle;
    is >> puzzle;

    Solution solution = solve_bfs(puzzle);

    cout << "Found solution: " << (solution.solved ? "Yes" : "No") << endl;
    if (solution.solved) {
        cout << "Steps: " << solution.path.size() - 1 << endl;
        cout << "\nSolution" << endl;
        cout << solution.puzzle << endl;
        cout << "Path" << endl;
        cout << solution;
    }

    return 0;
}
