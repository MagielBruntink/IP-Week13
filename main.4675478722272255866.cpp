#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <fstream>

using namespace std;

//                                                      
//                                                  

const char MAX_ROWS = 10;
const char MAX_COLUMNS = 10;
const char WALL = '*';
const char EMPTY = ' ';
const char DESTINATION = '.';
const char WORKER = 'w';
const char DESTINATION_WORKER = 'W';
const char BOX = 'b';
const char DESTINATION_BOX = 'B';

struct Coordinate
{
    int row;
    int column;
};

struct Puzzle
{
    char puzzle[MAX_ROWS][MAX_COLUMNS];
    int rows;
    int columns;
    Coordinate worker;
};

struct Candidate
{
    Puzzle candidate;
    int parent;
};

int size(vector<Candidate> c)
{
    return static_cast<int>(c.size());
}

int size(vector<Puzzle> p)
{
    return static_cast<int>(p.size());
}

bool operator==(Puzzle& a, Puzzle& b)
{
    if (a.rows != b.rows || a.columns != b.columns || a.worker.row != b.worker.row || a.worker.column != b.worker.column)
        return false;

    for (int row = 0; row < a.rows; row++) {
        for (int column = 0; column < a.columns; column++) {
            if (a.puzzle[row][column] != b.puzzle[row][column])
                return false;
        }
    }

    return true;
}

void read_puzzle(Puzzle& puzzle, string file_name)
{
    //             
    assert(file_name != "");
    /*              
                                              
    */
    ifstream fin (file_name.c_str());
    int row = 0;
    int column = 0;
    fin.get(puzzle.puzzle[row][column]);
    while (fin) {
        if (puzzle.puzzle[row][column] == WORKER || puzzle.puzzle[row][column] == DESTINATION_WORKER) {
            puzzle.worker.row = row;
            puzzle.worker.column = column;
        }

        if (puzzle.puzzle[row][column] == '\n') {
            puzzle.columns = column;
            row++;
            column = 0;
        } else
            column++;
        fin.get(puzzle.puzzle[row][column]);
    }
    puzzle.rows = row;
}

void show(Puzzle& puzzle)
{
    //             
    assert(puzzle.rows > 0 && puzzle.columns > 0);
    /*              
                                  
    */
    for (int row = 0; row < puzzle.rows; row++) {
        for (int column = 0; column < puzzle.columns; column++) {
            cout << puzzle.puzzle[row][column];
        }
        cout << endl;
    }

    cout << puzzle.worker.row << ' ' << puzzle.worker.column << endl << endl;
}

bool can_go_direction(Puzzle& p, int d_row, int d_column)
{
    //             
    assert((d_row != 0 || d_column != 0) && (d_row == 0 || d_column == 0) && p.worker.column >= 0 && p.worker.row >= 0 && p.worker.row < p.rows && p.worker.column < p.columns);
    /*              
                                                                                             
    */
    char move_to = p.puzzle[p.worker.row + d_row][p.worker.column + d_column];
    char behind_move_to = p.puzzle[p.worker.row + 2 * d_row][p.worker.column + 2 * d_column];

    return (!((move_to == WALL) || ((move_to == BOX || move_to == DESTINATION_BOX) && (behind_move_to == BOX || behind_move_to == DESTINATION_BOX || behind_move_to == WALL))));
}

bool can_go_north(Puzzle& p)
{
    //             
    assert(true);
    /*              
                                                    
    */
    return can_go_direction(p, -1, 0);
}

bool can_go_east(Puzzle& p)
{
    //             
    assert(true);
    /*              
                                                   
    */
    return can_go_direction(p, 0, 1);
}

bool can_go_south(Puzzle& p)
{
    //             
    assert(true);
    /*              
                                                    
    */
    return can_go_direction(p, 1, 0);
}

bool can_go_west(Puzzle& p)
{
    //             
    assert(true);
    /*              
                                                   
    */
    return can_go_direction(p, 0, -1);
}

Puzzle go_direction(Puzzle p, int d_row, int d_column)
{
    //             
    assert(can_go_direction(p, d_row, d_column) &&  (d_row != 0 || d_column != 0) && (d_row == 0 || d_column == 0) && p.worker.column >= 0 && p.worker.row >= 0 && p.worker.row < p.rows && p.worker.column < p.columns && (p.puzzle[p.worker.row][p.worker.column] == WORKER || p.puzzle[p.worker.row][p.worker.column] == DESTINATION_WORKER));
    /*              
                                                                                       
                                                                                                                                                        
    */
    char& move_from = p.puzzle[p.worker.row][p.worker.column];
    char& move_to = p.puzzle[p.worker.row + d_row][p.worker.column + d_column];
    char& behind_move_to = p.puzzle[p.worker.row + 2 * d_row][p.worker.column + 2 * d_column];
    if (move_to == BOX || move_to == DESTINATION_BOX) {
        if (behind_move_to == DESTINATION)
            behind_move_to = DESTINATION_BOX;
        else
            behind_move_to = BOX;
    }

    if (move_to == DESTINATION || move_to == DESTINATION_BOX)
        move_to = DESTINATION_WORKER;
    else
        move_to = WORKER;

    if (move_from == DESTINATION_WORKER)
        move_from = DESTINATION;
    else
        move_from = EMPTY;

    p.worker.row += d_row;
    p.worker.column += d_column;

    return p;
}

Puzzle go_north(Puzzle& p)
{
    //             
    assert(true);
    /*              
                                              
                                                            
    */
    return go_direction(p, -1, 0);
}

Puzzle go_east(Puzzle& p)
{
    //             
    assert(true);
    /*              
                                             
                                                           
    */
    return go_direction(p, 0, 1);
}

Puzzle go_south(Puzzle& p)
{
    //             
    assert(true);
    /*              
                                              
                                                            
    */
    return go_direction(p, 1, 0);
}

Puzzle go_west(Puzzle& p)
{
    //             
    assert(true);
    /*              
                                             
                                                           
    */
    return go_direction(p, 0, -1);
}

bool puzzle_present(vector<Candidate>& c, Candidate n)
{
    //             
    assert(true);
    /*              
                               
    */
    for (int i = 0; i < size(c); i++)
        if(c[i].candidate == n.candidate)
            return true;

    return false;
}

void add(vector<Candidate>& c, Candidate newc)
{
    //             
    assert(true);
    /*              
                                                   
    */
    if (!puzzle_present(c, newc))
        c.push_back(newc);
}

int show_path(vector<Candidate>& c, int i)
{
    //             
    assert(i >= 0 && i < size(c));
    /*              
                                               
                                                   
    */
    if(c[i].parent == -1) {
        show(c[i].candidate);
        return 0;
    }

    int result = show_path(c, c[i].parent) + 1;
    show(c[i].candidate);

    return result;
}

bool solved(Puzzle& p)
{
    //             
    assert(true);
    /*              
                                                        
    */
    for (int row = 0; row < p.rows; row++) {
        for (int column = 0; column < p.columns; column++) {
            if (p.puzzle[row][column] == BOX)
                return false;
        }
    }

    return true;
}

void solve_breadth_first(Puzzle& start)
{
    //             
    assert(start.rows > 0 && start.columns > 0 && start.worker.row >= 0 && start.worker.row < start.rows && start.worker.column >= 0 && start.worker.column < start.columns);
    /*              
                                    
    */
    vector<Candidate> c = {{start, -1}};

    int i = 0;
    while (i < size(c) && !solved(c[i].candidate)) {
        Puzzle p = c[i].candidate;

        if (can_go_north(p))
            add(c, {go_north(p), i});
        if (can_go_east(p))
            add(c, {go_east(p), i});
        if (can_go_south(p))
            add(c, {go_south(p), i});
        if (can_go_west(p))
            add(c, {go_west(p), i});

        i++;
    }

    if (i < size(c))
        cout << "It took " << show_path(c, i) << " moves" << endl;
}

bool puzzle_present(vector<Puzzle>& attempt, Puzzle p)
{
    //             
    assert(true);
    /*              
                                     
    */
    for (int i = 0; i < size(attempt); i++) {
        if (attempt[i] == p)
            return true;
    }

    return false;
}

void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& best, int max_depth);

void add(vector<Puzzle>& attempt, Puzzle newp, vector<Puzzle>& best, int max_depth)
{
    //             
    assert(size(attempt) > 0 && max_depth >= 0);
    /*              
                                     
                                                                       
                                                                              
    */
    if (!puzzle_present(attempt, newp)) {
        attempt.push_back(newp);
        solve_depth_first(attempt, best, max_depth);
        attempt.pop_back();
    }
}

void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& best, int max_depth)
{
    //             
    assert(size(attempt) > 0 && max_depth >= 0);
    /*              
                                                                                                                                         
    */
    const int CURRENT = size(attempt);
    const int BEST = size(best);
    Puzzle p = attempt[CURRENT - 1];

    if (BEST > 0 && CURRENT >= BEST)
        return;
    else if (CURRENT > max_depth + 1)
        return;
    else if (solved(p)) {
        best = attempt;
        return;
    }

    if (can_go_north(p))
        add(attempt, go_north(p), best, max_depth);
    if (can_go_east(p))
        add(attempt, go_east(p), best, max_depth);
    if (can_go_south(p))
        add(attempt, go_south(p), best, max_depth);
    if (can_go_west(p))
        add(attempt, go_west(p), best, max_depth);

}

void show_solution(vector<Puzzle> c)
{
    //             
    assert(true);
    /*              
                                                                                               
                                                     
    */
    for (int i = 0; i < size(c); i++)
        show(c[i]);

    if (size(c) > 0)
        cout << "It took " << size(c) - 1 << " moves" << endl;
    else
        cout << "No solution could be found" << endl;
}

int main()
{
    Puzzle puzzle;
    vector<Puzzle> attempt;
    vector<Puzzle> best;
    read_puzzle(puzzle, "challenge.0.txt");
    solve_breadth_first(puzzle);

    attempt.push_back(puzzle);
    while (size(best) > 0)
        best.pop_back();
    solve_depth_first(attempt, best, 1);
    show_solution(best);
    attempt.pop_back();

    read_puzzle(puzzle, "challenge.1.a.txt");
    solve_breadth_first(puzzle);

    attempt.push_back(puzzle);
    while (size(best) > 0)
        best.pop_back();
    solve_depth_first(attempt, best, 16);
    show_solution(best);
    attempt.pop_back();

    read_puzzle(puzzle, "challenge.1.b.txt");
    solve_breadth_first(puzzle);

    attempt.push_back(puzzle);
    while (size(best) > 0)
        best.pop_back();
    solve_depth_first(attempt, best, 1);
    show_solution(best);
    attempt.pop_back();

    read_puzzle(puzzle, "challenge.23.txt");
    solve_breadth_first(puzzle);

    attempt.push_back(puzzle);
    while (size(best) > 0)
        best.pop_back();
    solve_depth_first(attempt, best, 24);
    show_solution(best);
    attempt.pop_back();
    return 0;
}

