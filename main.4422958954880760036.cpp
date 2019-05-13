//                       
//                        

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

const char WALL     = '*';      //                                                                
const char EMPTY    = ' ';      //                                                                       
const char DEST     = '.';      //                                                                                   
const char WORKER   = 'w';      //                                                                                     
const char WORKDEST = 'W';      //                                                                                          
const char BOX      = 'b';      //                                                                                
const char BOXDEST  = 'B';      //                                                                                     

struct Candidate
{
    vector<char> candidate;
    int parent_candidate;
};

bool open_text_file (ifstream& infile)
{
//                
    assert (!infile.is_open());
/*                 
                                                                                   */

    cout << "Please enter the name of the file with the challenge you want to open: " << endl;
    string filename;
    cin >> filename;
    infile.open(filename.c_str());
    return infile.is_open();
}

int no_of_columns (ifstream& infile)
{
//                
    assert (infile.is_open());
/*                 
                                                                                                                                      */

    string temp;
    getline(infile,temp);

    infile.clear();
    infile.seekg(0,ios::beg);

    return temp.length();
}

void read_configuration (ifstream& infile, vector<char>& Map)
{
//                
    assert (infile.is_open());
/*                 
                                                                                                                   */

    char c;
    while (infile)
    {
        infile.get(c);
        Map.push_back(c);
    }
}

void print_configuration (vector<char>& Puzzle)
{
//                
    assert (Puzzle.size() != 0);
/*                 
                                                                                                                   */

    for (int i = 0; i < Puzzle.size()-1; i++)
    {
        cout << Puzzle[i];
    }
}

bool puzzle_ready (vector<char>& Puzzle)
{
//                
    assert (Puzzle.size() > 0);
/*                 
                                                                    */

    for (int i = 0; i < Puzzle.size() - 1; i++)
    {
        if (Puzzle[i] == DEST || Puzzle[i] == WORKDEST || Puzzle[i] == BOX)
            return false;
    }
    return true;
}

int worker (vector<char>& Puzzle)
{
//                
    assert (Puzzle.size() > 0);
/*                 
                                                                                          */

    int i = 0;
    while (Puzzle[i] != WORKER && Puzzle[i] != WORKDEST)
    {
        i++;
    }
    return i;
}

bool check_position (vector<char>& Puzzle, int new_pos, int row_up)
{
//                
    assert (Puzzle.size() > 0);
/*                 
                                                                                                        
                                       
                                           
                                                    */

    if (new_pos < 0)
        return false;
    else if (Puzzle[new_pos] == WALL)
        return false;
    else if ((Puzzle[new_pos] == BOX || Puzzle[new_pos] == BOXDEST) && (Puzzle[row_up] == BOX || Puzzle[row_up] == BOXDEST || Puzzle[row_up] == WALL))
        return false;
    else
        return true;
}

bool can_go_north (vector<char>& Puzzle, int& pos, int& width)
{
//                
    assert (Puzzle.size() > 0 && pos >= 0 && pos < Puzzle.size());
/*                 
                                                            */

    int new_pos = pos - width;
    int row_up = pos - 2 * width;

    check_position(Puzzle, new_pos, row_up);
}

bool can_go_south (vector<char>& Puzzle, int& pos, int& width)
{
//                
    assert (Puzzle.size() > 0 && pos >= 0);
    /*               
                                                            */

    int new_pos = pos + width;
    int row_up = pos + 2 * width;

    check_position(Puzzle, new_pos, row_up);
}

bool can_go_east (vector<char>& Puzzle, int& pos)
{
//                
    assert (Puzzle.size() > 0 && pos >= 0);
/*                 
                                                           */

    int new_pos = pos + 1;
    int row_up = new_pos + 1;

    check_position(Puzzle, new_pos, row_up);
}

bool can_go_west (vector<char>& Puzzle, int& pos)
{
//                
    assert (Puzzle.size() > 0 && pos >= 0);
/*                 
                                                           */

    int new_pos = pos - 1;
    int row_up = new_pos - 1;

    check_position(Puzzle, new_pos, row_up);
}

void move(vector<char>& Puzzle, int& pos, int new_pos, int up)
{
//                
    assert (Puzzle.size() > 0 && pos >= 0 && new_pos >= 0);
/*                 
                                                                                                           */

    if(Puzzle[pos] == WORKER && Puzzle[new_pos] == BOX && Puzzle[up] == DEST)
    {
        Puzzle[pos] = EMPTY;
        Puzzle[new_pos] = WORKER;
        Puzzle[up] = BOXDEST;
    }
    if(Puzzle[pos] == WORKDEST && Puzzle[new_pos] == BOX && Puzzle[up] == DEST)
    {
        Puzzle[pos] = DEST;
        Puzzle[new_pos] = WORKER;
        Puzzle[up] = BOXDEST;
    }
    if(Puzzle[pos] == WORKER && Puzzle[new_pos] == BOX && Puzzle[up] == EMPTY)
    {
        Puzzle[pos] = EMPTY;
        Puzzle[new_pos] = WORKER;
        Puzzle[up] = BOX;
    }
    if(Puzzle[pos] == WORKDEST && Puzzle[new_pos] == BOX && Puzzle[up] == EMPTY)
    {
        Puzzle[pos] = DEST;
        Puzzle[new_pos] = WORKER;
        Puzzle[up] = BOX;
    }
    if(Puzzle[pos] == WORKER && Puzzle[new_pos] == BOXDEST && Puzzle[up] == DEST)
    {
        Puzzle[pos] = EMPTY;
        Puzzle[new_pos] = WORKDEST;
        Puzzle[up] = BOXDEST;
    }
    if(Puzzle[pos] == WORKDEST && Puzzle[new_pos] == BOXDEST && Puzzle[up] == DEST)
    {
        Puzzle[pos] = DEST;
        Puzzle[new_pos] = WORKDEST;
        Puzzle[up] = BOXDEST;
    }
    if(Puzzle[pos] == WORKER && Puzzle[new_pos] == BOXDEST && Puzzle[up] == EMPTY)
    {
        Puzzle[pos] = EMPTY;
        Puzzle[new_pos] = WORKDEST;
        Puzzle[up] = BOX;
    }
    if(Puzzle[pos] == WORKDEST && Puzzle[new_pos] == BOXDEST && Puzzle[up] == EMPTY)
    {
        Puzzle[pos] = DEST;
        Puzzle[new_pos] = WORKDEST;
        Puzzle[up] = BOX;
    }
    if(Puzzle[pos] == WORKER && Puzzle[new_pos] == DEST)
    {
        Puzzle[pos] = EMPTY;
        Puzzle[new_pos] = WORKDEST;
    }
    if(Puzzle[pos] == WORKER && Puzzle[new_pos] == EMPTY)
    {
        Puzzle[pos] = EMPTY;
        Puzzle[new_pos] = WORKER;
    }
    if(Puzzle[pos] == WORKDEST && Puzzle[new_pos] == DEST)
    {
        Puzzle[pos] = DEST;
        Puzzle[new_pos] = WORKDEST;
    }
    if(Puzzle[pos] == WORKDEST && Puzzle[new_pos] == EMPTY)
    {
        Puzzle[pos] = DEST;
        Puzzle[new_pos] = WORKER;
    }
}

void go_north(vector<char>& Puzzle, int& pos, int& width)
{
//                
    assert (Puzzle.size() > 0 && pos >= 0);
/*                 
                                                                                       */

    int new_pos = pos - width;
    int up = pos - 2 * width;

    move(Puzzle, pos, new_pos, up);
    pos = new_pos;
}

void go_south(vector<char>& Puzzle, int& pos, int& width)
{
//                
    assert (Puzzle.size() > 0 && pos >= 0);
/*                 
                                                                                       */

    int new_pos = pos + width;
    int up = pos + 2 * width;

    move(Puzzle, pos, new_pos, up);
    pos = new_pos;
}

void go_west(vector<char>& Puzzle, int& pos)
{
//                
    assert (Puzzle.size() > 0 && pos >= 0);
/*                 
                                                                                      */

    int new_pos = pos - 1;
    int up = pos - 2;

    move(Puzzle, pos, new_pos, up);
    pos = new_pos;
}

void go_east(vector<char>& Puzzle, int& pos)
{
//                
    assert (Puzzle.size() > 0 && pos >= 0);
/*                 
                                                                                      */

    int new_pos = pos + 1;
    int up = pos + 2;

    move(Puzzle, pos, new_pos, up);
    pos = new_pos;
}

/*                                                                       
 
                                            
     
                            
                        
     
                 
 

                                              

                     
 

 

                    
 

 

                     
 

 

                    
 

 

                                              
 
                  
                    
*//                  
    The puzzle is being solved, using depth-first search. *// 

    vector<Candidate> c = {{Puzzle, -1}};

    if (can_go_north(p, pos, width))
        tries_north_b ();
    if (can_go_east(p, pos))
        tries_east_b ();
    if (can_go_south(p, pos, width))
        tries_south_b ();
    if (can_go_west(p, pos))
        tries_west_b ();
}*/

bool puzzle_present_d (vector<char>& p, vector<vector<char> >& Attempt)
{
//                
    assert ( true );
/*                 
                                                                 */

    for (int i = 0; i < Attempt.size(); i++)
    {
        if (Attempt[i] == p)
            return true;
    }
    return false;
}

void solve_depth_first (vector<vector<char> >& Attempt, vector<vector<char> >& Shortest, int max_depth, int& pos, int& width);

void tries_north_d (vector<vector<char> >& Attempt, vector<vector<char> >& Shortest, int max_depth, int& pos, int& width)
{
//                
    assert (true);
/*                 
                                                                              */

    vector<char> p = Attempt[Attempt.size()-1];
    go_north(p, pos, width);
    if (!puzzle_present_d(p, Attempt))
    {
        Attempt.push_back (p);
        solve_depth_first(Attempt, Shortest, max_depth, pos, width);
        Attempt.pop_back();
    }
}

void tries_east_d (vector<vector<char> >& Attempt, vector<vector<char> >& Shortest, int max_depth, int& pos, int& width)
{
//                
    assert (true);
/*                 
                                                                             */

    vector<char> p = Attempt[Attempt.size()-1];
    go_east(p, pos);
    if (!puzzle_present_d(p, Attempt))
    {
        Attempt.push_back (p);
        solve_depth_first(Attempt, Shortest, max_depth, pos, width);
        Attempt.pop_back();
    }
}

void tries_south_d (vector<vector<char> >& Attempt, vector<vector<char> >& Shortest, int max_depth, int& pos, int& width)
{
//                
    assert (true);
/*                 
                                                                              */

    vector<char> p = Attempt[Attempt.size()-1];
    go_south(p, pos, width);
    if (!puzzle_present_d(p, Attempt))
    {
        Attempt.push_back (p);
        solve_depth_first(Attempt, Shortest, max_depth, pos, width);
        Attempt.pop_back();
    }
}

void tries_west_d (vector<vector<char> >& Attempt, vector<vector<char> >& Shortest, int max_depth, int& pos, int& width)
{
//                
    assert (true);
/*                 
                                                                             */

    vector<char> p = Attempt[Attempt.size()-1];
    go_west(p, pos);
    if (!puzzle_present_d(p, Attempt))
    {
        Attempt.push_back (p);
        solve_depth_first(Attempt, Shortest, max_depth, pos, width);
        Attempt.pop_back();
    }
}

void solve_depth_first (vector<vector<char> >& Attempt, vector<vector<char> >& Shortest, int max_depth, int& pos, int& width)
{
//                
    assert (max_depth > 0);
/*                 
                                                          */

    const int CURRENT = Attempt.size();
    const int BEST = Shortest.size();
    vector<char> p = Attempt[CURRENT-1];

    if (BEST > 0 && CURRENT >= BEST)
        return;
    else if (CURRENT > max_depth + 1)
        return;
    else if (puzzle_ready(p))
    {
        Shortest = Attempt;
        return;
    }

    if (can_go_north(p, pos, width))
        tries_north_d (Attempt, Shortest, max_depth, pos, width);
    if (can_go_east(p, pos))
        tries_east_d (Attempt, Shortest, max_depth, pos, width);
    if (can_go_south(p, pos, width))
        tries_south_d (Attempt, Shortest, max_depth, pos, width);
    if (can_go_west(p, pos))
        tries_west_d (Attempt, Shortest, max_depth, pos, width);
}

void show_solution (vector<vector<char> >& Shortest)
{
//                
    assert (true);
/*                 
                                           */

    cout << "\nThe shortest solution, consists of: " << Shortest.size() << " steps." << endl;
    for (int i = 0; i < Shortest.size(); i++)
        print_configuration(Shortest[i]);
}

int main()
{
    ifstream infile;
    if (open_text_file(infile))
    {
        cout << "File opened successfully." << endl;
    }
    else
        cout << "Program aborted: opening file didn't succeed." << endl;

    vector<char> Puzzle;

    int width = no_of_columns(infile) + 1;
    read_configuration(infile,Puzzle);

    cout << "\nThe starting configuration that was read from the file is as follows: " << endl;
    print_configuration(Puzzle);

    int pos = worker(Puzzle);

    vector<vector<char> > Attempt = {Puzzle};
    vector<vector<char> > Shortest;

    solve_depth_first (Attempt, Shortest, 30, pos, width);
    show_solution(Shortest);

    infile.clear();
    infile.close();
    return 0;
}
