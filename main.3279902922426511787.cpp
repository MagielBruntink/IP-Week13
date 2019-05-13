//                                      
#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <string>

using namespace std;

const char  WALL                 = '*',
            EMPTY                = ' ',
            EMPTY_WORKER         = 'w',
            EMPTY_BOX            = 'b',
            DESTINATION          = '.',
            DESTINATION_WORKER   = 'W',
            DESTINATION_BOX      = 'B';

const int   MAX_WIDTH = 20,
            MAX_HEIGHT = 20;

typedef int Width;
typedef int Height;

enum Cell {Wall, Empty, EmptyWorker, EmptyBox, Destination, DestinationWorker, DestinationBox};

struct Position
{
    int col, row;
};

struct Puzzle
{
    Cell board [MAX_WIDTH][MAX_HEIGHT];
    Position worker;
    Width width;
    Height height;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

bool operator== (const Position& a, const Position& b)
{
    /*   */
    assert(true);
    /*    
                                                    
    */

    return a.col == b.col && a.row == b.row;
}

bool operator!= (const Position& a, const Position& b)
{
    /*   */
    assert(true);
    /*    
                                   
    */

    return !(a == b);
}

Position operator+ (const Position& a, const Position& b)
{
    /*   */
    assert(true);
    /*    
                                                                   
    */

    Position c;
    c.col = a.col + b.col;
    c.row = a.row + b.row;
    return c;
}

Position operator- (const Position& a, const Position& b)
{
    /*   */
    assert(true);
    /*    
                                                                           
    */

    Position c;
    c.col = a.col - b.col;
    c.row = a.row - b.row;
    return c;
}

Position operator* (const Position& a, const int b)
{
    /*   */
    assert(true);
    /*    
                                                           
    */

    Position c;
    c.col = a.col * b;
    c.row = a.row * b;
    return c;
}

bool operator== (const Puzzle& a, const Puzzle& b)
{
    /*   */
    assert(true);
    /*    
                                              
    */

    if (a.worker != b.worker) return false;
    if (a.width != b.width || a.height != b.height) return false;

    for (int i = 0; i < a.width; i++)
    {
        for (int ii = 0; ii < a.height; ii++)
        {
            if (a.board[i][ii] != b.board[i][ii]);
                return false;
        }
    }
    return true;
}

Position Pos (int x, int y)
{
    /*   */
    assert(true);
    /*    
                                 
    */

    return {x, y};
}

bool ReadPuzzle (Puzzle& puzzle, string filename)
{
    /*   */
    assert(!filename.empty());
    /*    
                                               
    */

    ifstream puzzle_file;
    puzzle_file.open(filename.c_str());

    if(!puzzle_file)
    {
        cout << "File was not read correctly.\n";
        return false;
    }
    puzzle.width = 0;
    puzzle.height = 0;

    int col = 0, row = 0;
    while(!puzzle_file.eof())
    {
        char cell = puzzle_file.get();
        switch (cell)
        {
        case WALL:
            puzzle.board[col++][row] = Wall;
            break;
        case EMPTY:
            puzzle.board[col++][row] = Empty;
            break;
        case EMPTY_WORKER:
            puzzle.worker = Pos (col, row);
            puzzle.board[col++][row] = EmptyWorker;
            break;
        case EMPTY_BOX:
            puzzle.board[col++][row] = EmptyBox;
            break;
        case DESTINATION:
            puzzle.board[col++][row] = Destination;
            break;
        case DESTINATION_WORKER:
            puzzle.board[col++][row] = DestinationWorker;
            break;
        case DESTINATION_BOX:
            puzzle.board[col++][row] = DestinationBox;
            break;
        case '\n':
            row++;
            col = 0;
            break;
        default:

            return false;
        }

        if (col > puzzle.width)
            puzzle.width = col;
        if (row > puzzle.height)
            puzzle.height = row;
    }
    puzzle_file.close();
}

void show (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                
    */

    for (int i = 0; i < puzzle.height; i++)
    {
        for (int ii = 0; ii < puzzle.width; ii++)
        {
            switch (puzzle.board[ii][i])
            {
            case Wall:
                cout << WALL;
                break;
            case Empty:
                cout << EMPTY;
                break;
            case EmptyWorker:
                cout << EMPTY_WORKER;
                break;
            case EmptyBox:
                cout << EMPTY_BOX;
                break;
            case Destination:
                cout << DESTINATION;
                break;
            case DestinationWorker:
                cout << DESTINATION_WORKER;
                break;
            case DestinationBox:
                cout << DESTINATION_BOX;
                break;
            }
        }
        cout << endl;
    }
}

bool can_go (Cell next_cell)
{
    /*   */
    assert(true);
    /*    
                                                      
    */

    assert (next_cell != EmptyWorker && next_cell != DestinationWorker);

    switch (next_cell)
    {
    case Empty:
    case Destination:
        return true;
    case Wall:
    case EmptyBox:
    case DestinationBox:
        return false;
    default:
        return false;
    }
}

Position north (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                            
    */

    Position worker = puzzle.worker;
    assert (worker.row - 1 >= 0);

    worker.row--;
    return worker;
}

Position south (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                            
    */

    Position worker = puzzle.worker;
    assert (worker.row + 1 < puzzle.height);

    worker.row++;
    return worker;
}

Position east (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                           
    */

    Position worker = puzzle.worker;
    assert (worker.col + 1 < puzzle.width);

    worker.col++;
    return worker;
}

Position west (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                           
    */

    Position worker = puzzle.worker;
    assert (worker.col - 1 >= 0);

    worker.col--;
    return worker;
}

bool can_go_north (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                                      
    */

    Position worker = puzzle.worker;
    return worker.row - 1 >= 0 && can_go (puzzle.board[worker.col][worker.row - 1]);
}

bool can_go_south (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                                      
    */

    Position worker = puzzle.worker;
    return worker.row + 1 < puzzle.height && can_go (puzzle.board[worker.col][worker.row + 1]);
}

bool can_go_east (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                                     
    */

    Position worker = puzzle.worker;
    return worker.col + 1 < puzzle.width && can_go (puzzle.board[worker.col + 1][worker.row]);
}

bool can_go_west (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                                     
    */

    Position worker = puzzle.worker;
    return worker.col - 1 >= 0 && can_go (puzzle.board[worker.col - 1][worker.row]);
}

bool isBox (Cell cell)
{
    /*   */
    assert(true);
    /*    
                                  
    */

    switch (cell)
    {
    case EmptyBox:
    case DestinationBox:
        return true;
    default:
        return false;
    }
}

bool next_to_box (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                           
    */

    Position worker = puzzle.worker;
    return ((worker.col - 1 >= 0            && isBox(puzzle.board[worker.col - 1][worker.row])) ||
            (worker.col + 1 < puzzle.height && isBox(puzzle.board[worker.col + 1][worker.row])) ||
            (worker.row - 1 >= 0            && isBox(puzzle.board[worker.col][worker.row - 1])) ||
            (worker.row + 1 < puzzle.width  && isBox(puzzle.board[worker.col][worker.row + 1])));
}

bool isEmpty (Cell cell)
{
    /*   */
    assert(true);
    /*    
                                                        
    */

    switch (cell)
    {
    case Empty:
    case Destination:
        return true;
    default:
        return false;
    }
}

bool can_push_north (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                
    */

    if (!next_to_box(puzzle))
        return false;
    Position worker = puzzle.worker;
    if (worker.row - 1 < 0 || !isBox (puzzle.board[worker.col][worker.row - 1]))
        return false;
    if (worker.row - 2 < 0 || !isEmpty (puzzle.board[worker.col][worker.row - 2]))
        return false;
    return true;
}

bool can_push_south (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                                
    */

    if (!next_to_box(puzzle))
        return false;
    Position worker = puzzle.worker;
    if (worker.row + 1 >= puzzle.height || !isBox (puzzle.board[worker.col][worker.row + 1]))
        return false;
    if (worker.row + 2 >= puzzle.height || !isEmpty (puzzle.board[worker.col][worker.row + 2]))
        return false;
    return true;
}

bool can_push_east (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                               
    */

    if (!next_to_box(puzzle))
        return false;
    Position worker = puzzle.worker;
    if (worker.col + 1 >= puzzle.width || !isBox (puzzle.board[worker.col + 1][worker.row]))
        return false;
    if (worker.col + 2 >= puzzle.width || !isEmpty (puzzle.board[worker.col + 2][worker.row]))
        return false;
    return true;
}

bool can_push_west (Puzzle puzzle)
{
    /*   */
    assert(true);
    /*    
                                               
    */

    if (!next_to_box(puzzle))
        return false;
    Position worker = puzzle.worker;
    if (worker.col - 1 < 0 || !isBox (puzzle.board[worker.col - 1][worker.row]))
        return false;
    if (worker.col - 2 < 0 || !isEmpty (puzzle.board[worker.col - 2][worker.row]))
        return false;
    return true;
}

void step_off (Puzzle& puzzle)
{
    /*   */
    assert(true);
    /*    
                                               
    */

    Position worker = puzzle.worker;
    switch (puzzle.board[worker.col][worker.row])
    {
    case EmptyWorker:
        puzzle.board[worker.col][worker.row] = Empty;
        break;
    case DestinationWorker:
        puzzle.board[worker.col][worker.row] = Destination;
        break;
    }
}

void step_on (Puzzle& puzzle)
{
    /*   */
    assert(true);
    /*    
                                            
    */

    Position worker = puzzle.worker;
    switch (puzzle.board[worker.col][worker.row])
    {
    case Empty:
        puzzle.board[worker.col][worker.row] = EmptyWorker;
        break;
    case Destination:
        puzzle.board[worker.col][worker.row] = DestinationWorker;
        break;
    }
}

void move_off (Puzzle& puzzle, Position box)
{
    /*   */
    assert(true);
    /*    
                                            
    */
    switch (puzzle.board[box.col][box.row])
    {
    case EmptyBox:
        puzzle.board[box.col][box.row] = Empty;
        break;
    case DestinationBox:
        puzzle.board[box.col][box.row] = Destination;
        break;
    }
}

void move_on (Puzzle& puzzle, Position box)
{
    /*   */
    assert(true);
    /*    
                                     
    */
    switch (puzzle.board[box.col][box.row])
    {
    case Empty:
        puzzle.board[box.col][box.row] = EmptyBox;
        break;
    case Destination:
        puzzle.board[box.col][box.row] = DestinationBox;
        break;
    }
}

Puzzle go_pos (Puzzle puzzle, Position pos)
{
    /*   */
    assert (isEmpty(puzzle.board[pos.col][pos.row]));
    /*    
                                                                         
    */

    step_off (puzzle);
    puzzle.worker = pos;
    step_on (puzzle);
    return puzzle;
}

Puzzle push_pos (Puzzle puzzle, Position pos)
{
    /*   */
    Position offset = (pos - puzzle.worker);
    Position boxPos = pos + offset;
    assert (isBox(puzzle.board[pos.col][pos.row]) && isEmpty(puzzle.board[boxPos.col][boxPos.row]));
    /*    
                                                                                                            
    */

    move_off(puzzle, pos);
    move_on(puzzle, boxPos);

    return go_pos(puzzle, pos);
}

bool puzzle_ready (Puzzle p)
{
    /*   */
    assert(true);
    /*    
                                                                                                 
    */

    int box = 0, destination = 0;
    for (int i = 0; i < p.width; i++)
    {
        for (int ii = 0; ii < p.height; ii++)
        {
            switch (p.board[i][ii])
            {
            case EmptyBox:
                box++;
                break;
            case Destination:
            case DestinationWorker:
                destination++;
                break;
            }
        }
    }
    if (box > 0 && destination > 0)
        return false;
    return true;
}

bool breadth_first_puzzle_present (vector<Candidate>& c, int i, Puzzle p)
{
    /*   */
    assert(true);
    /*    
                                                                                         
    */

    for (int j = 0; j < c.size(); j++)
    {
        if (p == c[j].candidate)
            return true;
    }
    return false;
}

void breadth_first_tries_move (vector<Candidate>& c, int i, Position next)
{
    /*   */
    assert(true);
    /*    
                                     
    */

    Puzzle p = c[i].candidate;
    Puzzle newp = go_pos (p, next);
    Candidate newc = {newp, i};
    if (!breadth_first_puzzle_present (c, i, newp))
        c.push_back(newc);
}

void breadth_first_tries_push (vector<Candidate>& c, int i, Position next)
{
    /*   */
    assert(true);
    /*    
                                    
    */
    Puzzle p = c[i].candidate;
    Puzzle newp = push_pos (p, next);
    Candidate newc = {newp, i};
    if (!breadth_first_puzzle_present (c, i, newp))
        c.push_back(newc);
}

void show_path(vector<Candidate> c, int i)
{
    /*   */
    assert(true);
    /*    
                                                        
    */

    if (i < 0) return;

    show_path (c, c[i].parent_candidate);
    cout << "Step " << i << endl;
    show (c[i].candidate);
}

void breadth_first_solve (Puzzle start)
{
    /*   */
    assert(true);
    /*    
                                         
    */

    vector<Candidate> c = {{start, -1}};
    int i = 0;
    while (i < c.size() && !puzzle_ready (c[i].candidate))
    {
        cout << i << endl;
        Puzzle p = c[i].candidate;
        if (can_go_north (p)) breadth_first_tries_move (c, i, north (p));
        if (can_go_south (p)) breadth_first_tries_move (c, i, south (p));
        if (can_go_east (p)) breadth_first_tries_move (c, i, east (p));
        if (can_go_west (p)) breadth_first_tries_move (c, i, west (p));
        if (can_push_north (p)) breadth_first_tries_push (c, i, north (p));
        if (can_push_south (p)) breadth_first_tries_push (c, i, south (p));
        if (can_push_east (p)) breadth_first_tries_push (c, i, east (p));
        if (can_push_west (p)) breadth_first_tries_push (c, i, west (p));
        i++;
    }
    if (i < c.size())
        show_path(c, i);
}

bool depth_first_puzzle_present (Puzzle p, vector<Puzzle> attempt)
{
    /*   */
    assert(true);
    /*    
                                                 
    */

    for (int i = 0; i < attempt.size(); i++)
    {
        if(attempt[i] == p)
            return true;
    }
    return false;
}

void depth_first_solve (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);
void depth_first_tries_move (vector<Puzzle>& attempt, Position next, vector<Puzzle>& shortest, int max_depth)
{
    /*   */
    assert(true);
    /*    
                                     
    */

    Puzzle p = attempt[attempt.size() - 1];
    Puzzle newp = go_pos(p, next);
    if (!depth_first_puzzle_present (newp, attempt))
    {
        attempt.push_back (newp);
        depth_first_solve(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void depth_first_tries_push (vector<Puzzle>& attempt, Position next, vector<Puzzle>& shortest, int max_depth)
{
    /*   */
    assert(true);
    /*    
                                    
    */

    Puzzle p = attempt[attempt.size() - 1];
    Puzzle newp = push_pos(p, next);
    if (!depth_first_puzzle_present (newp, attempt))
    {
        attempt.push_back (newp);
        depth_first_solve(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void depth_first_solve (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    /*   */
    assert(attempt.size() > 0 && max_depth >= 0);
    /*    
                                        
    */

    const int CURRENT   = attempt.size();
    const int BEST      = shortest.size();
    Puzzle p            = attempt[CURRENT - 1];
    if (BEST > 0 && CURRENT >= BEST) return;
    if (CURRENT > max_depth + 1) return;
    if (puzzle_ready (p))
    {
        shortest = attempt;
        return;
    }
    if (can_go_north (p)) depth_first_tries_move (attempt, north (p), shortest, max_depth);
    if (can_go_south (p)) depth_first_tries_move (attempt, south (p), shortest, max_depth);
    if (can_go_east (p)) depth_first_tries_move (attempt, east (p), shortest, max_depth);
    if (can_go_west (p)) depth_first_tries_move (attempt, west (p), shortest, max_depth);
    if (can_push_north (p)) depth_first_tries_push (attempt, north (p), shortest, max_depth);
    if (can_push_south (p)) depth_first_tries_push (attempt, south (p), shortest, max_depth);
    if (can_push_east (p)) depth_first_tries_push (attempt, east (p), shortest, max_depth);
    if (can_push_west (p)) depth_first_tries_push (attempt, west (p), shortest, max_depth);
}

void show_steps (vector<Puzzle> attempt)
{
    /*   */
    assert(true);
    /*    
                                          
    */

    for (int i = 0; i < attempt.size(); i++)
    {
        cout << "Step " << i << endl;
        show(attempt[i]);
    }
}

int main()
{
    string filename = "challenge.23.txt";
    Puzzle puzzle;
    ReadPuzzle (puzzle, filename);
//                                 

    vector<Puzzle> attempt = {puzzle}, shortest;
    depth_first_solve(attempt, shortest, 25);
    show_steps(shortest);
    return 0;
}

