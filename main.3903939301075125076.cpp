#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>

using namespace std;

enum Objects {ground, wall, destination, worker, worker_on_destination, box, box_on_destination};
const vector<char> CELL_SYMBOL {' ', '*', '.', 'w', 'W', 'b', 'B'};

struct Position {
int row;
int column;
};

Position operator+ (const Position& a, const Position& b)
{ //              
    assert(true);
  /*               
                                      */
    return Position({a.row+b.row, a.column+b.column});
}

struct Cell {
Objects symbol;
bool can_move_onto;
bool is_destination;
bool keeper;
bool box;
};

enum dir_index {north, east, south, west};
const vector<Position> DIRECTION {Position({-1, 0}), Position({0, 1}), Position({1, 0}), Position({0, -1}) };

typedef vector<vector<Cell>> Puzzle;

//     
bool operator== (const Cell& a, const Cell& b)
{//              
    assert(true);
  /*               
                                                      */
    return (a.can_move_onto == b.can_move_onto) &&
           (a.is_destination == b.is_destination) &&
           (a.keeper == b.keeper) &&
           (a.box == b.box);
}

//                                              
bool operator== (const Puzzle& a, const Puzzle& b)
{//              
    assert(true);
  /*               
                                                        */
    if (a.size() == b.size())
    {
        for (int row=0; row < a.size(); row++)
        {
            if (a[row].size() == b[row].size())
            {
                for (int column=0; column < a[row].size(); column++)
                {
                    if ( !( a[row][column] == b[row][column] ))
                        return false;
                }
            }
            else
                return false;
        }
        return true;
    }
    else
        return false;
}

//     
Objects cast_Objects_from_char(char c)
{//              
    assert(true);
  /*               
                                                 */
    switch (c)
    {
        case ' ':
            return ground;
        case '*':
            return wall;
        case '.':
            return destination;
        case 'w':
            return worker;
        case 'W':
            return worker_on_destination;
        case 'b':
            return box;
        case 'B':
            return box_on_destination;
    }
}

//     
Cell char_to_cell (char c)
{//              
    assert(true);
  /*               
                                                */
    Cell cell;
    cell.symbol = cast_Objects_from_char(c);

    cell.can_move_onto = !(cell.symbol == wall);
    cell.is_destination = (cell.symbol == destination || cell.symbol == worker_on_destination || cell.symbol == box_on_destination);
    cell.keeper = (cell.symbol == worker || cell.symbol == worker_on_destination);
    cell.box = (cell.symbol == box || cell.symbol == box_on_destination);

    return cell;
}

//     
void update_cell (Cell& cell)
{//              
    assert(true);
  /*               
                                                              */
    if (cell.is_destination)
    {
        if (cell.keeper)
            cell.symbol = worker_on_destination;
        else if (cell.box)
            cell.symbol = box_on_destination;
        else
            cell.symbol = destination;
    }

    else if (cell.keeper)
        cell.symbol = worker;
    else if (cell.box)
        cell.symbol = box;
    else if (cell.can_move_onto)
        cell.symbol = ground;
    else
        cell.symbol = wall;
}

//                                               
void Update_puzzle (Puzzle& puzzle)
{//              
    assert(true);
  /*               
                                             */
    for (int row=0; row < puzzle.size(); row++)
    {
        for (int column=0; column < puzzle[row].size(); column++)
        {
            update_cell(puzzle[row][column]);
        }
    }
}

//                                                                    
void open_file (ifstream& stream)
{//              
    assert(true);
  /*               
                                                              */
    string name = " ";

    do{
    cout << "which file should be opened? ";
    cin >> name;

    stream.open(name.c_str());
    if (! stream)
        cout << "can not open that file!" << endl;

    } while (! stream);
}

//                                                
void read_puzzle (Puzzle& puzzle)
{//              
    assert(true);
  /*               
                                                      */
    puzzle.clear();
    ifstream reader;
    string line;

    open_file(reader);

    while( getline(reader, line))
    {
        puzzle.push_back(vector<Cell>());
        int row = puzzle.size()-1;

        for (int i=0; i<line.size(); i++)
        {
            puzzle[row].push_back(char_to_cell(line[i]));
        }
    }

    reader.close();
}

//                                               
ostream& operator<< (ostream& out, const Puzzle puzzle)
{//               
    assert(puzzle.size() > 0);
/*                 
                          */
    cout << " - - Puzzle: - - " << endl;
    for (int row=0; row < puzzle.size(); row++)
    {
        cout << "|";
        for (int column=0; column < puzzle[row].size(); column++)
        {
            cout << CELL_SYMBOL[puzzle[row][column].symbol];
        }
        cout << "|" << endl;
    }
    cout << " - - - - - - - - " << endl;

    return out;
}

//                                                                 
bool puzzle_done (Puzzle puzzle)
{//              
    assert(puzzle.size() > 0);
  /*               
                                                */
    for (int row=0; row < puzzle.size(); row++)
    {
        for (int column=0; column < puzzle[row].size(); column++)
        {
            if ( puzzle[row][column].is_destination && !puzzle[row][column].box )
                return false;
        }
    }
    return true;
}

//                                                                 
Position keeper_position(Puzzle puzzle)
{//              
    assert(puzzle.size() > 0);
  /*               
                                                             */
    for (int row=0; row < puzzle.size(); row++)
    {
        for (int column=0; column < puzzle[row].size(); column++)
        {
            if ( puzzle[row][column].keeper )
                return Position( {row, column } );
        }
    }
}

//                                                                                  
ostream& operator<< (ostream& out, const vector<Puzzle> puzzle)
{//               
    assert(puzzle.size() > 0);
/*                 
                                            */
    for (int i=0; i < puzzle.size(); i++)
    {
        Position k = keeper_position(puzzle[i]);
        cout << i << " Keeper at: " << k.column << "," << k.row << endl;
    }

    return out;
}

//     
bool can_move_towards (Puzzle puzzle, Position& keeper, Position delta)
{//               
    assert(puzzle.size() > 0);
    assert( 0 <= keeper.row && keeper.row < puzzle.size() && 0 < keeper.column && keeper.column < puzzle[keeper.row].size());
    assert( -1 <= delta.row && delta.row <= 1 && -1 <= delta.column && delta.column <= 1 );
/*                 
                                                                                  
     */
    bool yes_we_can = true;
    int new_row = keeper.row+delta.row;
    int new_col = keeper.column+delta.column;

    //                     
    if ( 0 <= new_row && new_row < puzzle.size() &&
         0 <= new_col && new_col < puzzle[new_row].size())
    {
        //                                     
        if (! puzzle[new_row][new_col].can_move_onto)
            yes_we_can=false;

        //                                 
        if ( puzzle[new_row][new_col].box)
        {
            //                                           
            if ( puzzle[new_row+delta.row][new_col+delta.column].box ||
                !puzzle[new_row+delta.row][new_col+delta.column].can_move_onto)
            {
                yes_we_can = false;
            }
        }
    }
    else
        yes_we_can = false;

    return yes_we_can;
}

//     
Puzzle move_towards (Puzzle puzzle, Position keeper, Position Delta)
{//               
    assert(can_move_towards(puzzle, keeper, Delta));
/*                 
                                                                                      
    */
    int new_row = keeper.row+Delta.row;
    int new_col = keeper.column+Delta.column;

    puzzle[keeper.row][keeper.column].keeper = false;
    puzzle[new_row][new_col].keeper = true;

    if (puzzle[new_row][new_col].box)
    {
        puzzle[new_row][new_col].box = false;
        puzzle[new_row+Delta.row][new_col+Delta.column].box = true;
    }

    keeper = keeper + Delta;

    return puzzle;
}

//                               
struct Attempt{
Puzzle attempt;
int parent;
};

//                                                                                          
bool contain (vector<Attempt> attempts, Puzzle p)
{//               
    assert(attempts.size() >= 0);
/*                 
                                                       
    */
    for (int i=0; i<attempts.size(); i++)
    {
        if (attempts[i].attempt == p)
            return true;
    }
    return false;
}

//     
void tries_breadth (vector<Attempt>& a, int i, Position keeper, Position delta )
{//               
    assert( -1 <= delta.row && delta.row <= 1 && -1 <= delta.column && delta.column <= 1 );
/*                 
                                                                                       
    */
    Puzzle p = Puzzle(a[i].attempt);

    Puzzle newp = move_towards(p, keeper, delta);

    if (! contain(a, newp))
        a.push_back({newp, i});
}

//                                                                      
int breadth_first (Puzzle puzzle)
{//               
    assert(puzzle.size() > 0);
/*                 
                                                                                                        */
    Puzzle p;
    Position keeper;
    vector<Attempt> a = {{puzzle, -1}};
    int i = 0;
    int moves = 0;

    while (i < a.size() && !puzzle_done( a[i].attempt))
    {
        p = a[i].attempt;
        keeper = keeper_position(p);
        //                                                                          

        if(can_move_towards(p, keeper, DIRECTION[north])) { tries_breadth(a, i, keeper, DIRECTION[north]); }
        if(can_move_towards(p, keeper, DIRECTION[east])) { tries_breadth(a, i, keeper, DIRECTION[east]); }
        if(can_move_towards(p, keeper, DIRECTION[south])) { tries_breadth(a, i, keeper, DIRECTION[south]); }
        if(can_move_towards(p, keeper, DIRECTION[west])) { tries_breadth(a, i, keeper, DIRECTION[west]); }
        i++;
    }

    if (i < a.size())
    {
        Update_puzzle(a[i].attempt);
        cout << a[i].attempt;

        while (a[i].parent >= 0)
        {
            i = a[i].parent;
            moves++;
        }
    }

    return moves;
}

//            
//                                                                                          
bool contain (vector<Puzzle> attempts, Puzzle p) //                                   
{//               
    assert(attempts.size() >= 0);
/*                 
                                                       
    */
    for (int i=0; i<attempts.size(); i++)
    {
        if (attempts[i] == p)
            return true;
    }
    return false;
}

void solve(vector<Puzzle>&, vector<Puzzle>&, int);

//      
void tries_depth (vector<Puzzle>& attempt, Position keeper, Position delta, vector<Puzzle>& shortest, int max_depth )
{//               
    assert( -1 <= delta.row && delta.row <= 1 && -1 <= delta.column && delta.column <= 1 );
/*                 
                                                                                              
    */
    Puzzle p = attempt[attempt.size() - 1];

    Puzzle newp = move_towards(p, keeper, delta);

    if (! contain(attempt, newp))
    {
        attempt.push_back(newp);
        solve(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

//                                                                               
void solve (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{//               
    assert(max_depth > 0);
/*                 
                                                                                            */
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle p = attempt[CURRENT-1];
    Position keeper = keeper_position(p);

    if (BEST > 0 && CURRENT > BEST) { return; }
    else if (CURRENT > max_depth+1) { return; }
    else if (puzzle_done(p)) {shortest = attempt; return; }

    if(can_move_towards(p, keeper, DIRECTION[north])) { tries_depth(attempt, keeper, DIRECTION[north], shortest, max_depth); }
    if(can_move_towards(p, keeper, DIRECTION[east])) { tries_depth(attempt, keeper, DIRECTION[east], shortest, max_depth); }
    if(can_move_towards(p, keeper, DIRECTION[south])) { tries_depth(attempt, keeper, DIRECTION[south], shortest, max_depth); }
    if(can_move_towards(p, keeper, DIRECTION[west])) { tries_depth(attempt, keeper, DIRECTION[west], shortest, max_depth); }
}

int main()
{//               
    assert(true);
/*                 
                                                                                                            */
    Puzzle puzzle;
    read_puzzle(puzzle);
    cout << puzzle;

    int attempts_breadth = breadth_first(puzzle);
    cout << attempts_breadth << " moves needed" << endl;

    cout << " - - Recursion - - " << endl;
    cout << puzzle;
    vector<Puzzle> attempt = {puzzle};
    vector<Puzzle> best;
    solve(attempt, best, 25);
    cout << best;
    cout << best.size() - 1 << " moves needed" << endl;
}

