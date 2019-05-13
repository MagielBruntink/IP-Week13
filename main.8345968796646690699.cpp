#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

/*                                            
                                              
                                    
                                              
                                              
                                              
                                              
                                            */

const int MAX_FILENAME_LENGTH = 20;
const int NO_OF_ROWS = 10;
const int NO_OF_COLS = 10;
typedef int Cell;
const char WALL = '*';
const char EMPTY = ' ';
const char DEST = '.';
const char WORKER = 'w';
const char WORKER_D = 'W';
const char BOX = 'b';
const char BOX_D = 'B';
enum States {wall = 0, empty, dest, worker, worker_d, box, box_d};

struct Pos
{
    int row, col;
};

struct Puzzle
{
    States room [NO_OF_ROWS][NO_OF_COLS];
    Pos worker;
};

struct Candidate
{
    Puzzle candidate;
    int parent;
};

bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{
//                 
    assert(MAX_FILENAME_LENGTH >= 0);
//                  
/*                                                                                                                                                                                       
                                                                  */
//                
    cout << "Enter a filename of max length " << MAX_FILENAME_LENGTH << " with the enter character included" << endl;

    char x;
    int y = 0;
    for(y=0; y<MAX_FILENAME_LENGTH && x != '\n'; y++)
    {
        cin.get (x);
        filename[y] = x;
    }
    y --;
    if (filename[y] == '\n')
    {
        filename[y] = '\0';
        cout << "filename success\n";
        return true;
    }
    else
    {
        cout << "invalid filename\n";
        return false;
    }
}

bool read_puzzle_file (ifstream& infile, States room [NO_OF_ROWS] [NO_OF_COLS])
{//               
    assert (!infile.is_open());
/*                 
                                                                               
*/
    for (int i = 0; i < NO_OF_ROWS; i++)
    {
        for (int j = 0; j < NO_OF_COLS; j++)
        {
            room[i][j] = empty;
        }
    }
    char filename [MAX_FILENAME_LENGTH];
    int a = 0;
    int b = 0;
    char get;
    if (enter_filename(filename))
    {
        infile.open(filename);
        while (infile)
        {
            infile.get(get);
            if (get == WALL)
            {
                room[a][b] = wall;
                b++;
            }
            else if (get == EMPTY)
            {
                room[a][b] = empty;
                b++;
            }
            else if (get == DEST)
            {
                room[a][b] = dest;
                b++;
            }
            else if (get == WORKER)
            {
                room[a][b] = worker;
                b++;
            }
            else if (get == WORKER_D)
            {
                room[a][b] = worker_d;
                b++;
            }
            else if (get == BOX)
            {
                room[a][b] = box;
                b++;
            }
            else if (get == BOX_D)
            {
                room[a][b] = box_d;
                b++;
            }
            else if (get == '\n')
            {
                b = 0;
                a++;
            }
            else
            {
                cout << "Could not read the room state" << endl;
                return false;
            }
        }
        cout << "Reading succesful" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

void show_room (States room [NO_OF_ROWS][NO_OF_COLS])
{
//                 
    assert(true);
//                  
/*                  */
    for (int a = 0; a < NO_OF_ROWS; a++)
    {
        for (int b = 0; b < NO_OF_COLS; b++)
        {
            if (room[a][b] == wall)
            {
                cout << WALL;
            }
            else if (room[a][b] == box_d)
            {
                cout << BOX_D;
            }
            else if (room[a][b] == empty)
            {
                cout << EMPTY;
            }
            else if (room[a][b] == dest)
            {
                cout << DEST;
            }
            else if (room[a][b] == worker)
            {
                cout << WORKER;
            }
            else if (room[a][b] == worker_d)
            {
                cout << WORKER_D;
            }
            else if (room[a][b] == box)
            {
                cout << BOX;
            }
        }
        cout << '\n';
    }
}

ostream& operator<<(ostream& out, Pos& pos)
{
    out << "The worker is in column " << pos.col + 1 << '\n'
        << "The worker is in row " << pos.row + 1 << '\n' << endl;

    return out ;
}

ostream& operator<<(ostream& out, Puzzle a)
{
    show_room(a.room);
    return out;
}

ostream& operator<<(ostream& out, Candidate& candidate)
{
    out << candidate.candidate << '\n'
        << "Number of previous state " << candidate.parent;

    return out ;
}

Pos find_position(States a [NO_OF_ROWS][NO_OF_COLS])
{//              
    assert(true);
//               
//                                                     
    for (int i = 0; i < NO_OF_ROWS; i++)
    {
        for (int j = 0; j < NO_OF_COLS; j++)
        {
            if (a[i][j] == worker || a[i][j] == worker_d)
            {
                return {i, j};
            }
        }
    }
}

int number_of_boxes(Puzzle p)
{
//               
    assert ( true );
    /*                 
                                                                  
    */
    int counter = 0;
    for (int i = 0; i < NO_OF_ROWS; i++)
    {
        for(int j = 0; j < NO_OF_COLS; j++)
        {
            if(p.room[i][j] == box || p.room[i][j] == box_d)
                counter++;
        }
    }
    return counter;
}

int number_of_boxes_on_dest(Puzzle p)
{
//               
    assert ( true );
    /*                 
                                                                
    */
    int counter = 0;
    for (int i = 0; i < NO_OF_ROWS; i++)
    {
        for(int j = 0; j < NO_OF_COLS; j++)
        {
            if(p.room[i][j] == box_d){
                counter++;
            }
        }
    }
    return counter;
}

bool is_same_puzzle(Puzzle a, Puzzle b)
{
//               
    assert ( true );
    /*                 
                                                                                       
    */

    bool ok = true;

    for (int i = 0; i < NO_OF_ROWS; i++)
    {
        for(int j = 0; j < NO_OF_COLS; j++)
        {
            if(a.room[i][j] != b.room[i][j])
                ok = false;
        }
    }

    return ok;
}

bool room_done (Puzzle p)
{//              
    assert(true);
    //               
    //                                                                                                                         
    return number_of_boxes_on_dest(p) == number_of_boxes(p);
}

bool go_north(Puzzle a)
{
//               
    assert ( true );
    /*                 
                                                                                                                              
    */

    bool ok = false;

    if(a.room[a.worker.row-1][a.worker.col] == empty || a.room[a.worker.row-1][a.worker.col] == dest)
    {
        ok = true;
    }
    else if(a.room[a.worker.row-1][a.worker.col] == box || a.room[a.worker.row-1][a.worker.col] == box_d)
    {
        if(a.room[a.worker.row-2][a.worker.col] == empty || a.room[a.worker.row-2][a.worker.col] == dest)
        {
            ok = true;
        }
    }

    return ok;
}

bool go_south(Puzzle a)
{
//               
    assert ( true );
    /*                 
                                                                                                                              
    */

    bool ok = false;

    if(a.room[a.worker.row+1][a.worker.col] == empty || a.room[a.worker.row+1][a.worker.col] == dest)
    {
        ok = true;
    }
    else if(a.room[a.worker.row+1][a.worker.col] == box || a.room[a.worker.row+1][a.worker.col] == box_d)
    {
        if(a.room[a.worker.row+2][a.worker.col] == empty || a.room[a.worker.row+2][a.worker.col] == dest)
        {
            ok = true;
        }
    }

    return ok;
}

bool go_west(Puzzle a)
{
//               
    assert ( true );
    /*                 
                                                                                                                             
    */

    bool ok = false;

    if(a.room[a.worker.row][a.worker.col-1] == empty || a.room[a.worker.row][a.worker.col-1] == dest)
    {
        ok = true;
    }
    else if(a.room[a.worker.row][a.worker.col-1] == box || a.room[a.worker.row][a.worker.col-1] == box_d)
    {
        if(a.room[a.worker.row][a.worker.col-2] == empty || a.room[a.worker.row][a.worker.col-2] == dest)
        {
            ok = true;
        }
    }

    return ok;
}

bool go_east(Puzzle a)
{
//               
    assert ( true );
    /*                 
                                                                                                                             
    */

    bool ok = false;

    if(a.room[a.worker.row][a.worker.col+1] == empty || a.room[a.worker.row][a.worker.col+1] == dest)
    {
        ok = true;
    }
    else if(a.room[a.worker.row][a.worker.col+1] == box || a.room[a.worker.row][a.worker.col+1] == box_d)
    {
        if(a.room[a.worker.row][a.worker.col+2] == empty || a.room[a.worker.row][a.worker.col+2] == dest)
        {
            ok = true;
        }
    }

    return ok;
}

Pos north (Puzzle a)
{
    return {a.worker.row-1, a.worker.col};
}

Pos box_north(Puzzle a)
{
    return {a.worker.row-2, a.worker.col};
}

Pos south (Puzzle a)
{
    return {a.worker.row+1, a.worker.col};
}

Pos box_south (Puzzle a)
{
    return {a.worker.row+2, a.worker.col};
}

Pos east (Puzzle a)
{
    return {a.worker.row, a.worker.col+1};
}

Pos box_east (Puzzle a)
{
    return {a.worker.row, a.worker.col+2};
}

Pos west (Puzzle a)
{
    return {a.worker.row, a.worker.col-1};
}

Pos box_west (Puzzle a)
{
    return {a.worker.row, a.worker.col-2};
}

bool puzzle_present_bfs (vector<Candidate>& c, int i, Puzzle p)
{//              
    assert ( i >= 0 && i < c.size() );
    //               
    //                                                              

    bool ok = false;
    for (int j = 0; j < c.size(); j++)
    {
        if (is_same_puzzle(c[j].candidate, p))
        {
            ok = true;
        }
    }
    return ok;
}

bool puzzle_present_dfs (vector<Puzzle>& p, Puzzle a)
{
    //              
    assert(true);
    //               
    //                                                              
    bool ok = false;
    for (int i = 0; i < p.size(); i++)
    {
        if (is_same_puzzle(a, p[i]))
        {
            ok = true;
        }
    }
    return ok;
}

Puzzle move_worker_and_box(Puzzle a, Pos next, Pos box_next)
{
//               
    assert ( true );
    /*                 
                                                           
    */
    States Worker = a.room[a.worker.row][a.worker.col];
    States Worker_moving_to = a.room[next.row][next.col];
    States Box_moving_to = a.room[box_next.row][box_next.col];

    if(Worker == worker)                                                           //                                                
        a.room[a.worker.row][a.worker.col] = empty;                                //                     
    else if(Worker == worker_d)                                                   //                                              
        a.room[a.worker.row][a.worker.col] = dest;                               //               

    if(Worker_moving_to == empty || Worker_moving_to == dest)
    {
        if(Worker_moving_to == empty)                                                   //                                                
            a.room[next.row][next.col] = worker;                              //                                                 
        else if(Worker_moving_to == dest)                                             //          
            a.room[next.row][next.col] = worker_d;                           //                                                                     
        a.worker = next;
    }

    else if(Worker_moving_to == box || Worker_moving_to == box_d)
    {
        if(Box_moving_to == empty)                                                      //                                                  
            a.room[box_next.row][box_next.col] = box;                         //                                   
        else if(Box_moving_to == dest)                                                //                                              
            a.room[box_next.row][box_next.col] = box_d;                      //                            
        else if(Box_moving_to == box){
            a.room[box_next.row][box_next.col] = box;
        }

        if(Worker_moving_to == box)                                                //                                                
            a.room[next.row][next.col] = worker;                              //                                                
        else if(Worker_moving_to == box_d)                                        //          
            a.room[next.row][next.col] = worker_d;                           //                                                                        
        a.worker = next;
    }

    return a;
}

void tries_bfs (vector<Candidate>& c, int i, Pos next, Pos box_next)
{
    //              
    assert(true);
    //               
    //                                   
    Puzzle p = move_worker_and_box(c[i].candidate, next, box_next);
    Candidate nc = {p, i};
    if (!puzzle_present_bfs (c, i, p)) {
            c.push_back(nc);
    }
}

void show_path (vector<Candidate>& c, int i, int& counter)
{//              
    assert(true);
    //               
    //                                                  
    if (i < 0) return;
    else
    {
        counter++;
        show_path (c, c[i].parent, counter);
        cout << c[i].candidate;
    }
}

void solve_bfs (Puzzle start)
{//              
    assert(true);
    //               
    //                                     
    cout << "Calculating solution..." << endl;
    vector<Candidate> candidates;
    candidates.push_back({start,-1});
    int i = 0;
    while ((i < candidates.size()) && (!room_done(candidates[i].candidate)))  //                          
    {
        Puzzle p = candidates[i].candidate;
        if (go_north(p)) tries_bfs (candidates, i, north(p), box_north(p));
        if (go_south(p)) tries_bfs (candidates, i, south(p), box_south(p));
        if (go_west (p)) tries_bfs (candidates, i, west (p), box_west(p));
        if (go_east (p)) tries_bfs (candidates, i, east (p), box_east(p));
        i++;
    }
    if (room_done(candidates[i].candidate)){
        int counter=0;
        show_path(candidates, i,counter);
        cout << counter-1 << " steps needed to find the solution" << endl;
    }
}

void tries_dfs (vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth, Pos box_next);

void solve_dfs (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{//              
    assert(true);
    //               
    //                                    
    cout << "Calculating solution..." << endl;
    Puzzle p = attempt[attempt.size()-1];
    if(room_done(p)){
        if(shortest.size() == 0 || attempt.size() < shortest.size())
            shortest = attempt;
    }
    else if(shortest.size()!= 0 && shortest.size() < attempt.size()){
        return;
    }
    else if (attempt.size() > max_depth){
        return;
    }
    else{
    if (go_north (p)) tries_dfs (attempt, north (p), shortest, max_depth, box_north(p));
    if (go_south (p)) tries_dfs (attempt, south (p), shortest, max_depth, box_south(p));
    if (go_west  (p)) tries_dfs (attempt, west  (p), shortest, max_depth, box_west(p));
    if (go_east  (p)) tries_dfs (attempt, east  (p), shortest, max_depth, box_east(p));
    }
}

void tries_dfs (vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth, Pos box_next)
{//              
    assert(true);
    //               
    //                                   
    Puzzle p = move_worker_and_box(attempt[attempt.size()-1], next,box_next);
    if (!puzzle_present_dfs (attempt, p))
    {
        attempt.push_back (p) ;
        solve_dfs (attempt,shortest,max_depth) ;
        attempt.pop_back () ;
    }
}

int main()
{
    ifstream infile;
    States room [NO_OF_ROWS][NO_OF_COLS];
    vector<Puzzle> path;
    vector<Puzzle> best;
    Puzzle puzzle;
    read_puzzle_file(infile, puzzle.room);
    puzzle.worker = find_position(puzzle.room);

    //   
    solve_bfs(puzzle);

    /*   
                           
                              
                                         
     
                        
     
                                                               
    */

    infile.close();
    return 0;
}

