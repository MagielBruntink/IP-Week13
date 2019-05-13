/*                                                                    
                        
                                                     
                                                     
                                                                     */

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

enum Cell      {Wall, Empty, Destination, Worker, Box, BoxDestination, Error};
enum Direction {Up, Down, Left, Right};

typedef vector<vector<Cell> > Puzzle;

struct Candidate
{
    Puzzle candidate;
    int    parent_candidate;
};

/*                                                                               
 
                                                                               */

Cell char_to_Cell (char c)
{
//                 
//   
//                  
/*                                                                   
*/
    Cell cell;
    if (c == '*')
        return cell = Wall;
    else if (c == ' ')
        return cell = Empty;
    else if (c == '.')
        return Destination;
    else if (c == 'w')
        return Worker;
    else if (c == 'b')
        return Box;
    else if (c == 'B')
        return BoxDestination;
    return cell = Error;
}

char Cell_to_char (Cell cell)
{
//                 

/*                
                                                                     
*/
    if (cell == Wall)
        return '*';
    else if (cell == Empty)
        return ' ';
    else if (cell == Destination)
        return '.';
    else if (cell == Worker)
        return 'w';
    else if (cell == Box)
        return 'b';
    else if (cell == BoxDestination)
        return 'B';
    return 'E';
}

/*                                                                               
 
                                                                               */

void read_file (Puzzle& puzzle, int row, ifstream& infile)
{
//                
    assert(infile.is_open());
//                 
//                                                                 
    char c;
    vector<Cell> new_line;
    puzzle.push_back(new_line);

    while (infile.get(c))
    {
        if (c == '\n')
            read_file(puzzle, ++row, infile);
        else
            puzzle[row].push_back(char_to_Cell(c));
    }
}

/*                                                                               
 
                                                                               */

void show (Puzzle& puzzle)
{
//                 

/*                
                                          
*/
    for (int i = 0; i < puzzle.size(); i++)
    {
        for (int j = 0; j < puzzle[i].size(); j++)
            cout << Cell_to_char(puzzle[i][j]);
        cout << endl;
    }
}

/*                                                                               
 
                                                                               */

bool search (Puzzle& puzzle, Cell cell, int& row, int& column)
{
//               

/*                
                                                             
                                                                            
*/
    row = -1;
    column = -1;
    for (int i = 0; i < puzzle.size(); i++)
        for (int j = 0; j < puzzle[i].size(); j++)
            if (puzzle[i][j] == cell)
            {
                row = i;
                column = j;
                return true;
            }
    return false;
}

bool is_complete (Puzzle& puzzle)
{
//                 

/*                
                                                                                
*/
    int row;
    int column;
    search (puzzle, Destination, row, column);
    return row == -1 && column == -1;
}

/*                                                                               
 
                                                                               */

void add (int& row, int& column, Direction dir)
{
//                 

/*                
                                                                                     
*/
    if (dir == Up)
        row--;
    else if (dir == Down)
        row++;
    else if (dir == Left)
        column--;
    else if (dir == Right)
        column++;
}

bool can_move (Puzzle& puzzle, Direction dir)
{
//                 

/*                
                                                                  
                                                        
*/
    int row;
    int column;
    if (search(puzzle, Worker, row, column) )
    {
        add (row, column, dir);
        return puzzle[row][column] == Empty;
    }
    return false;
}

bool can_move_box (Puzzle& puzzle, Direction dir)
{
//                 

/*                
                                                                
                                                     
                                                           
*/
    int row;
    int column;
    search (puzzle, Worker, row, column);
    add (row, column, dir);

    if (puzzle[row][column] != Box)
        return false;
    else
    {
        add(row, column, dir);
        return puzzle[row][column] == Empty || puzzle[row][column] == Destination;
    }
}

Puzzle move (Puzzle puzzle, Direction dir)
{
//                 

/*                
                                                    
*/
    int row;
    int column;
    search (puzzle, Worker, row, column);

    if (can_move (puzzle, dir))
    {
        puzzle[row][column] = Empty;
        add(row, column, dir);
        puzzle[row][column] = Worker;
    }
    return puzzle;
}

Puzzle move_box (Puzzle puzzle, Direction dir)
{
//                 

/*                
                                                              
                                                                
                                                             
                                    
*/
    int row;
    int column;
    search (puzzle, Worker, row, column);

    if (can_move_box (puzzle, dir))
    {
        puzzle[row][column] = Empty; //            
        add(row, column, dir);
        puzzle[row][column] = Worker;
        add(row,column, dir);
        if (puzzle[row][column] == Destination)
            puzzle[row][column] = BoxDestination;
        else if (puzzle[row][column] == Empty)
            puzzle[row][column] = Box;
    }
    return puzzle;
}

/*                                                                               
 
                                                                               */

bool puzzle_present (vector<Candidate>& track, int i, Puzzle p)
{
//                 

/*                
                                                                             
                                                                                    
                                                                           
                                                                        
*/
    for (int i = 0; i < track.size(); i++)
        if (track[i].candidate == p && track[i].parent_candidate == i)
            return true;
    return false;
}

void tries_box (vector<Candidate>& track, int i, Direction dir)
{
//                 

/*                
                                                                      
                                                      
*/
    Puzzle p = track[i].candidate;
    Puzzle newp = move_box(p, dir);
    Candidate newc = {newp, i};
    if (!puzzle_present (track, i, newp))
        track.push_back(newc);
}

void tries_move (vector<Candidate>& track, int i, Direction dir)
{
//                 

/*                
                                                                                                                                  
*/
    Puzzle p = track[i].candidate;
    Puzzle newp = move(p, dir);
    Candidate newc = {newp, i};
    if (!puzzle_present (track, i, newp))
        track.push_back(newc);
}

void show_path (vector<Candidate>& track)
{
//                 

/*                
                                                                  
*/
    for (int i = 0; i < track.size(); i++)
    {
        cout << "Candidate: " << track[i].parent_candidate << endl;
        show (track[i].candidate);
        cout << endl;
    }

}

void bfs_solve (Puzzle& start)
{
//                 

/*                
                                                                   
                                                   
*/
    vector<Candidate> track = {{start, -1}};

    int i = 0;
    while (i < track.size() && !is_complete(track[i].candidate))
    {
        Puzzle p = track[i].candidate;
        if (can_move_box(p, Up) )
            tries_box (track, i, Up);
        else if (can_move_box(p,Down) )
            tries_box (track, i, Down);
        else if (can_move_box(p, Left))
            tries_box (track, i, Left);
        else if (can_move_box(p, Right))
            tries_box (track, i, Right);

        else if (can_move(p, Up) )
            tries_move (track, i, Up);
        else if (can_move(p,Down) )
            tries_move (track, i, Down);
        else if (can_move(p, Left))
            tries_move (track, i, Left);
        else if (can_move(p, Right))
            tries_move (track, i, Right);
        i++;
    }
    show_path(track);
}

void tries (vector<Candidate>& attempt, Puzzle next_puzzle, vector<Candidate>& shortest, int& i, int max_depth); //                                                              

void dfs_solve (vector<Candidate>& attempt, vector<Candidate>& shortest, int& i, int max_depth)
{
//                 

/*                
                                                                 
                                                   
*/
    const int CURRENT = attempt.size();
    const int BEST    = shortest.size();
    Puzzle p          = attempt[CURRENT-1].candidate;

    if (BEST > 0 && CURRENT >= BEST )      { return; }
    else if (CURRENT > max_depth+1)        { return; }
    else if (is_complete(p))     { shortest = attempt; return; }

    if (can_move_box(p, Up))
        tries (attempt, move_box(p, Up) , shortest, i, max_depth);
    if (can_move_box(p, Down))
        tries (attempt, move_box(p, Down) , shortest, i, max_depth);
    if (can_move_box(p, Left))
        tries (attempt, move_box(p, Left) , shortest, i, max_depth);
    if (can_move_box(p, Right))
        tries (attempt, move_box(p, Right) , shortest, i, max_depth);

    if (can_move(p, Up))
        tries (attempt, move(p, Up), shortest, i, max_depth);
    if (can_move(p, Down))
        tries (attempt, move(p, Down), shortest, i, max_depth);
    if (can_move(p, Left))
        tries (attempt, move(p, Left), shortest, i, max_depth);
    if (can_move(p, Up))
        tries (attempt, move(p, Right), shortest, i, max_depth);
}

void tries (vector<Candidate>& attempt, Puzzle next_puzzle, vector<Candidate>& shortest, int& i, int max_depth)
{
//                 

/*                
                                                                                                                                  
*/
    if (!puzzle_present(attempt, i, next_puzzle))
    {
        Candidate newc = {next_puzzle, i};
        i++;
        attempt.push_back(newc);
        dfs_solve(attempt, shortest, i, max_depth);
        i--;
        attempt.pop_back();
    }
}

int main()
{
    Puzzle   puzzle;
    ifstream infile;
    string   filename;
    int max_depth = 10;
    int init      = 0;

    cout << "Please enter a filename of a challenge you want to solve" << endl;
    cin >> filename;
    infile.open(filename.c_str());
    read_file(puzzle, 0, infile);

    cout << "The solution using breadth-first search: " << endl;
    bfs_solve(puzzle);

    vector<Candidate> attempt = {{puzzle, -1}};
    vector<Candidate> shortest;
    dfs_solve(attempt, shortest, init, max_depth);
    cout << "The solution using depth-first search: " << endl;
    show_path(shortest);

    infile.close();
    return 0;
}

