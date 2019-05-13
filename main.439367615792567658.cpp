//                                                                                                                     
//                                                          
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
using namespace std;

enum Object {Wall=0, Empty_floor=1, Destination=2, Box=3, Worker=4, Box_at_dest=5, Worker_at_dest=6};
const int ROWS              = 7 ;
const int COLUMNS           = 7 ;
struct Pos
{
    int row, col;
};
struct Puzzle
{
    Object board[ROWS][COLUMNS];
    Pos open;
};
struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};
Puzzle puzzle;
void tries_depth (vector<Puzzle>& attempt, Pos direction, vector<Puzzle>& shortest, int max_depth);
bool enter_filename (ifstream& inputfile, string filename)
{
    //              
    assert (true);
    /*               
                                                
    */
    cout << "Please enter file name: " << endl;
    getline(cin, filename);
    inputfile.open(filename.c_str());
    if (inputfile)
    {
        cout << "the file has been opened succesfully" << endl;
    }
    else
    {
        cout << "the file couldn't be opened/doesn't exist" << endl;
    }
    return inputfile.is_open();
}

bool read_board (ifstream& inputfile)
{
    //              
    assert (inputfile.is_open());
    /*               
                                                                
    */
    char temp;
    for (int i=0; i< ROWS;i ++)
    {
        for (int j=0; j< COLUMNS; j++)
        {
            if (inputfile)
            {
                inputfile.get(temp);
                if (temp == '*')
                    puzzle.board[i][j]=Wall;
                else if (temp == ' ')
                    puzzle.board[i][j]=Empty_floor;
                else if (temp == '.')
                    puzzle.board[i][j]=Destination;
                else if (temp == 'b')
                    puzzle.board[i][j]=Box;
                else if (temp == 'w')
                    puzzle.board[i][j]=Worker;
                else if (temp == 'B')
                    puzzle.board[i][j]=Box_at_dest;
                else if (temp == 'W')
                    puzzle.board[i][j]=Worker_at_dest;

            }
        }
        inputfile.ignore();
    }
}

void show_board (ifstream& inputfile)
{
    //             
    assert (inputfile.is_open());
    /*               
                                 
    */
    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<COLUMNS; j++)
        {
            cout << puzzle.board[i][j];
        }
        cout << endl;
    }
}

bool puzzle_ready (Puzzle p)
{
//               
    assert (ROWS > 0 && COLUMNS > 0);
//                
//                                                                          
    for (int i = 0; i < ROWS ; i++)
    {
        for (int j = 0; j < COLUMNS ; j++ )
            if (p.board [i][j] == Box || p.board [i][j] == Worker)
                return false;
    }
    return true;
}

Pos find_worker (Puzzle p)
{
//               
    assert (ROWS > 0 && COLUMNS > 0);
//                
//                                                  
    for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
                if (p.board[i][j] == Worker || p.board[i][j] == Worker_at_dest)
                {
                    Pos worker;
                    worker.row = i;
                    worker.col = j;
                    return worker;
                }
        }
    return {-1,-1};
}

Pos north ()
{
//               
    assert (true);
//                
//                                           
    Pos north = {-1, 0};
}

Pos south ()
{
//               
    assert (true);
//                
//                                           
    Pos north = {1, 0};
}

Pos west ()
{
//               
    assert (true);
//                
//                                          
    Pos west = {0, -1};
}

Pos east ()
{
//               
    assert (true);
//                
//                                          
    Pos east = {0, 1};
}

bool can_go_direction (Puzzle p, Pos direction)
{
//               
    assert (true);
//                
//                                                                               
    Pos worker = find_worker(p);
    int new_row = worker.row + direction.row;
    int new_col = worker.col + direction.col;
    if (p.board[new_row][new_col] == Empty_floor || p.board[new_row][new_col] == Destination )
        return true;
    else if (p.board[new_row][new_col] == Wall )
        return false;
    else if (p.board[new_row][new_col] == Box)
        {
            if (p.board[new_row + direction.row][new_col + direction.col] == Empty_floor || p.board[new_row + direction.row][new_col + direction.col] == Destination)
                return true;
            else
                return false;
        }

}

bool can_go_north (Puzzle p)
{
//               
    assert (true);
//               
//                                               
    Pos a_direction = north();
    can_go_direction(p, a_direction);
}

bool can_go_south (Puzzle p)
{
//               
    assert (true);
//               
//                                               
    Pos a_direction = south();
    can_go_direction(p, a_direction);
}

bool can_go_west (Puzzle p)
{
//               
    assert (true);
//               
//                                              
    Pos a_direction = west();
    can_go_direction(p, a_direction);
}

bool can_go_east (Puzzle p)
{
//               
    assert (true);
//               
//                                              
    Pos a_direction = east();
    can_go_direction(p, a_direction);
}

void show_path (vector<Candidate>& c, int i)
{
//               
    assert (i >= -1);
//                
//                                                         
    vector<Puzzle> solution;
    if (i = -1)
        return;

    else
    {
        show_path (c, c[i].parent_candidate);
        for (int m = 0; m < ROWS; m++)
        {
            for (int n = 0; n < COLUMNS; n++)
                cout << c[i].candidate.board[m][n];
        }
        cout << endl;
    }
}

void change_old_place_worker (Puzzle& p)
{
//               
    assert (true);
//                
//                                                               
    Pos worker = find_worker(p);
    if (p.board[worker.row][worker.col] == Worker)
        p.board[worker.row][worker.col] = Empty_floor;
    if (p.board[worker.row][worker.col] == Worker_at_dest)
        p.board[worker.row][worker.col] = Destination;
}

void copy_array (Puzzle p, Puzzle newp)
{
//               
    assert (true);
//                
//                                            
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j <COLUMNS; j++)
            newp.board[i][j]= p.board [i][j];
    newp.open = p.open;
}

void move_worker (Puzzle& p, Pos direction)
{
//                
    assert(true);
//                 
//                                                                                                                 
    Pos worker = find_worker(p);
    int new_row = worker.row + direction.row;
    int new_col = worker.col + direction.col;
    if (p.board[new_row][new_col] == Destination)
    {
        p.board[new_row][new_col] = Worker_at_dest;
        change_old_place_worker(p);
    }
    if (p.board[new_row][new_col] == Empty_floor)
    {
        p.board[new_row][new_col] = Worker;
        change_old_place_worker(p);
    }
    if (p.board[new_row][new_col] == Box)
    {
        if (p.board[new_row + direction.row][new_col + direction.col] == Destination)
        {
            p.board[new_row][new_col] = Worker;
            p.board[new_row + direction.row][new_col + direction.col] = Box_at_dest;
            change_old_place_worker(p);
        }

        if (p.board[new_row + direction.row][new_col + direction.col] == Empty_floor)
        {
            p.board[new_row][new_col] = Worker;
            p.board[new_row + direction.row][new_col + direction.col] = Box;
            change_old_place_worker(p);
        }
    }
    if (p.board[new_row][new_col] == Box_at_dest)
    {
            if (p.board[new_row + direction.row][new_col + direction.col] == Destination)
        {
            p.board[new_row][new_col] = Worker_at_dest;
            p.board[new_row + direction.row][new_col + direction.col] = Box_at_dest;
            change_old_place_worker(p);
        }

        if (p.board[new_row + direction.row][new_col + direction.col] == Empty_floor)
        {
            p.board[new_row][new_col] = Worker_at_dest;
            p.board[new_row + direction.row][new_col + direction.col] = Box;
            change_old_place_worker(p);
        }
    }

}

bool puzzle_present_1 (vector<Candidate>& c, Puzzle newp)
{
//               
    assert (true);
//                
//                                                                   
    for (int k = 0; k < c.size() ; k++)
    {
        int counter = 0;
        for (int i = 0; i < ROWS; i++)
        {
             for (int j = 0; j < COLUMNS; j++)
                    if (newp.board[i][j] == c[k].candidate.board[i][j])
                        counter++;

        }
        if (counter == ROWS * COLUMNS)
        return true;
    }
    return false;
}

bool puzzle_present_2(Puzzle newp, vector<Puzzle>& attempt)
{
//               
    assert (true);
//                
//                                                                   
    for (int k = 0; k < attempt.size() ; k ++)
        {
            int counter = 0;
            for(int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLUMNS; j++)
                    if (newp.board[i][j] == attempt[k].board[i][j])
                        counter++;
            }
            if (counter = ROWS * COLUMNS)
            return true;
        }
    return false;
}

//                      
void tries_breadth (vector<Candidate>& c, int i, Pos direction)
{
//               
    assert (i >= 0);
//                
//                                                            
    Puzzle p = c[i].candidate;
    Puzzle newp;
    copy_array(p, newp);
    move_worker (newp, direction);
    Candidate newc = {newp, i};
    if (!puzzle_present_1 (c, newp))
        c.push_back(newc);
}

void solve_breadth (Puzzle start)
{
//               
    assert (true);
//                
//                                                                      
    vector<Candidate> c = {{start, -1}};
    int i = 0;
    while (i < c.size() && !puzzle_ready (c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if (can_go_north(p)) tries_breadth (c, i, north ());
        if (can_go_south(p)) tries_breadth (c, i, south ());
        if (can_go_west (p)) tries_breadth (c, i, west  ());
        if (can_go_east (p)) tries_breadth (c, i, east  ());
        i = i + 1;
    }
    if (i < c.size())
        show_path(c, i);
}

//                     
void solve_depth (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
//               
    assert (max_depth >= 0);
//                
//                                 
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle p = attempt[CURRENT-1];
    if (BEST > 0 && CURRENT >= BEST){return ;}
    else if (CURRENT > max_depth+1) {return ;}
    else if (puzzle_ready(p)) {shortest = attempt; return ;}
    if (can_go_north(p)) tries_depth (attempt, north (), shortest, max_depth);
    if (can_go_south(p)) tries_depth (attempt, south (), shortest, max_depth);
    if (can_go_west (p)) tries_depth (attempt, west  (), shortest, max_depth);
    if (can_go_east (p)) tries_depth (attempt, east  (), shortest, max_depth);
}

void tries_depth (vector<Puzzle>& attempt, Pos direction, vector<Puzzle>& shortest, int max_depth)
{
//               
    assert (max_depth >= 0);
//                
//                                                        
    Puzzle p = attempt[attempt.size()-1];
    Puzzle newp;
    copy_array(p, newp);
    move_worker (newp, direction);
    if (!puzzle_present_2 (newp, attempt))
    {
        attempt.push_back(newp);
        solve_depth (attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

int main ()
{
    string filename;
    ifstream inputfile;
    enter_filename(inputfile, filename);
    read_board(inputfile);
    show_board(inputfile);
    cout << "what solve programm do you want to use? Breadth first = 1, Depth first = 2" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        Puzzle start;
        solve_breadth(start);
    }
    if (choice == 2)
    {
        vector<Puzzle> attempt;
        vector<Puzzle> shortest;
        int max_depth;
        cout << "what is the max depth you want to use?" << endl;
        cin >> max_depth;
        solve_depth(attempt, shortest, max_depth);
    }
    return 0;
}

