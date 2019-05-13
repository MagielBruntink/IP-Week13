#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

struct Pos
{
    int col;
    int row;
};

struct Puzzle
{
    vector< vector<char> > puzzle;
    Pos warehouse_keeper;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};
bool operator==(const Puzzle& a, const Puzzle& b)
{
    for(int r = 0; r < a.puzzle.size(); r++)
    {
        for(int k =0; k < a.puzzle[r].size(); k++)
        {
            if(a.puzzle[r][k] != b.puzzle[r][k])
                return false;
        }
    }
    return true;
}
bool operator!=(const Pos& a, const Pos& b)
{
    if(a.row == b.row && a.col == b.col)
    {
        return false;
    }
    else {return true;}
}
Puzzle read_challenge(vector< vector<char> >& puzzle, ifstream& infile)
{
    assert(true);
    //                
    //                                                                                                                                                                         
    cout << "Which challenge do you want to play? (No need to enter the .txt extenstion)" << endl;
    string challenge;
    getline(cin,challenge);
    string filename = challenge + ".txt";
    infile.open(filename.c_str());
    string help;
    getline(infile,help);
    char help2[help.length()];
    strcpy(help2,help.c_str());
    vector<char> puzzle_row;
    for(int i = 0; i < help.length(); i++)
    {
        puzzle_row.push_back(help2[i]);
    }
    puzzle.push_back(puzzle_row);
    while(infile)
    {
        puzzle_row.clear();
        getline(infile,help);
        strcpy(help2,help.c_str());
        for(int i = 0; i < help.length(); i++)
        {
            puzzle_row.push_back(help2[i]);
        }
        puzzle.push_back(puzzle_row);
    }
    infile.close();
    puzzle.pop_back();
    Puzzle p;
    p.puzzle = puzzle;
    for(int r = 0; r < puzzle.size(); r++)
    {
        for(int k = 0; k < puzzle[r].size(); k++)
        {
            if(puzzle[r][k] == 'w' || puzzle[r][k] == 'W')
            {
                p.warehouse_keeper.col = k;
                p.warehouse_keeper.row = r;
            }
        }
    }
    return p;
}

void show_challenge(Puzzle p)
{
    assert(p.puzzle.size() >= 0);
    //                
    //                                               
    for(int r = 0; r < p.puzzle.size(); r++)
    {
        for(int k = 0; k< p.puzzle[r].size(); k++)
        {
            cout << p.puzzle[r][k];
        }
        cout << endl;
    }
}
void show_path(vector<Candidate> C, int i, int& steps)
{
    assert(true);
    //                
    //                                                                                                                                                             
    if(i < 0)
    {
        return;
    }
    else
    {
        steps++;
        show_path(C,C[i].parent_candidate,steps);
        show_challenge(C[i].candidate);
    }
}
bool puzzle_ready(Puzzle p)
{
    for (int r = 0; r < p.puzzle.size(); r++)
    {
        for (int k = 0; k < p.puzzle[r].size(); k++)
        {
            if(p.puzzle[r][k] == 'b')
                return false;
        }
    }
    return true;
}
bool can_go_north(Puzzle p)
{
    assert(true);
    //                
    //                                                                           
    if(p.puzzle[p.warehouse_keeper.row + 1][p.warehouse_keeper.col] != '*')
    {
        if(p.puzzle[p.warehouse_keeper.row + 1][p.warehouse_keeper.col] == 'b' || p.puzzle[p.warehouse_keeper.row + 1][p.warehouse_keeper.col] == 'B')
        {
            if(p.puzzle[p.warehouse_keeper.row + 2][p.warehouse_keeper.col] == '*' || p.puzzle[p.warehouse_keeper.row + 2][p.warehouse_keeper.col] == 'b' || p.puzzle[p.warehouse_keeper.row + 2][p.warehouse_keeper.col] == 'B')
                return false;
        }
        return true;
    }
    else
        return false;
}
bool can_go_south(Puzzle p)
{
    assert(true);
    //                
    //                                                                           
    if(p.puzzle[p.warehouse_keeper.row - 1][p.warehouse_keeper.col] != '*')
    {
        if(p.puzzle[p.warehouse_keeper.row - 1][p.warehouse_keeper.col] == 'b' || p.puzzle[p.warehouse_keeper.row - 1][p.warehouse_keeper.col] == 'B')
        {
            if(p.puzzle[p.warehouse_keeper.row - 2][p.warehouse_keeper.col] == '*' || p.puzzle[p.warehouse_keeper.row - 2][p.warehouse_keeper.col] == 'b' || p.puzzle[p.warehouse_keeper.row - 2][p.warehouse_keeper.col] == 'B')
                return false;
        }
        return true;
    }
    else
        return false;
}
bool can_go_east(Puzzle p)
{
    assert(true);
    //                
    //                                                                          
    if(p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col - 1] != '*')
    {
        if(p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col - 1] == 'b' || p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col - 1] == 'B')
        {
            if(p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col - 2] == '*' || p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col - 2] == 'b' || p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col - 2] == 'B')
                return false;
        }
        return true;
    }
    else
        return false;
}
bool can_go_west(Puzzle p)
{
    assert(true);
    //                
    //                                                                          
    if(p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col + 1] != '*')
    {
        if(p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col + 1] == 'b' || p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col + 1] == 'B')
        {
            if(p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col + 2] == '*' || p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col + 2] == 'b' || p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col + 2] == 'B')
                return false;
        }
        return true;
    }
    else
        return false;
}
Pos north(Puzzle p, int j)
{
    assert(j >= 1);
    //                
    //                                                       
    Pos newpos;
    newpos.row = p.warehouse_keeper.row + j;
    newpos.col = p.warehouse_keeper.col;
    return newpos;
}
Pos south(Puzzle p, int j)
{
    assert(j >= 1);
    //                
    //                                                       
    Pos newpos;
    newpos.row = p.warehouse_keeper.row - j;
    newpos.col = p.warehouse_keeper.col;
    return newpos;
}
Pos east(Puzzle p, int j)
{
    assert(j >= 1);
    //                
    //                                                      
    Pos newpos;
    newpos.col = p.warehouse_keeper.col - j;
    newpos.row = p.warehouse_keeper.row;
    return newpos;
}
Pos west(Puzzle p, int j)
{
    assert(j >= 1);
    //                
    //                                                      
    Pos newpos;
    newpos.col = p.warehouse_keeper.col + j;
    newpos.row = p.warehouse_keeper.row;
    return newpos;
}
Puzzle move_warehouse(Puzzle p , Pos next, Pos further)
{
    assert(next != further && next.row >= 0 && further.row >= 0 && next.row <= p.puzzle.size() && further.row <= p.puzzle.size());
    //                
    //                                                                                        
    //                       
    Puzzle newp;
    newp.puzzle = p.puzzle;
    if(p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] == 'w')
    {
        if(newp.puzzle[next.row][next.col] == ' ')
        {
            newp.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] = ' ';
            newp.puzzle[next.row][next.col] = 'w';
        }
        else if(newp.puzzle[next.row][next.col] == '.')
        {
            newp.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] = ' ';
            newp.puzzle[next.row][next.col] = 'W';
        }
        else if(newp.puzzle[next.row][next.col] == 'b')
        {
            newp.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] = ' ';
            newp.puzzle[next.row][next.col] = 'w';
            if(p.puzzle[further.row][further.col] == '.')
                newp.puzzle[further.row][further.col] = 'B';
            else
                newp.puzzle[further.row][further.col] = 'b';
        }
        else if(newp.puzzle[next.row][next.col] == 'B')
        {
            newp.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] = ' ';
            newp.puzzle[next.row][next.col] = 'W';
            if(p.puzzle[further.row][further.col] == '.')
                newp.puzzle[further.row][further.col] = 'B';
            else
                newp.puzzle[further.row][further.col] = 'b';
        }
    }
    else if(p.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] == 'W')
    {
        if(newp.puzzle[next.row][next.col] == ' ')
        {
            newp.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] = '.';
            newp.puzzle[next.row][next.col] = 'w';
        }
        else if(newp.puzzle[next.row][next.col] == '.')
        {
            newp.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] = '.';
            newp.puzzle[next.row][next.col] = 'W';
        }
        else if(newp.puzzle[next.row][next.col] == 'b')
        {
            newp.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] = '.';
            newp.puzzle[next.row][next.col] = 'w';
            if(p.puzzle[further.row][further.col] == '.')
                newp.puzzle[further.row][further.col] = 'B';
            else
                newp.puzzle[further.row][further.col] = 'b';
        }
        else if(newp.puzzle[next.row][next.col] == 'B')
        {
            newp.puzzle[p.warehouse_keeper.row][p.warehouse_keeper.col] = '.';
            newp.puzzle[next.row][next.col] = 'W';
            if(p.puzzle[further.row][further.col] == '.')
                newp.puzzle[further.row][further.col] = 'B';
            else
                newp.puzzle[further.row][further.col] = 'b';
        }
    }
    newp.warehouse_keeper = next;
    return newp;
}
bool puzzle_original(vector<Candidate>& c, int i, Puzzle p)
{
    assert(true);
    //                
    //                                                  
    //                        
    for (int j = 0; j <= i; j++)
    {
        if(c[j].candidate == p)
        {
            return false;
        }
    }
    return true;
}
void tries(vector<Candidate>& c, int i, Pos next, Pos further )
{
    assert(next != further);
    //                
    //                                                                                                            
    Puzzle p = c[i].candidate;
    Puzzle newp = move_warehouse(p,next,further);
    Candidate newc = {newp, i};
    if(puzzle_original(c,i,newp))
        c.push_back(newc);
}
void solve_breadth_first(Puzzle& puzzle, int& steps)
{
    assert(true);
    //                
    //                                                                                                                               
    vector<Candidate> c = {{puzzle,-1}};
    int i = 0;
    while(i < c.size() && !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if(can_go_north(p))
            tries(c,i,north(p,1),north(p,2));
        if(can_go_south(p))
            tries(c,i,south(p,1),south(p,2));
        if(can_go_east(p))
            tries(c,i,east(p,1),east(p,2));
        if(can_go_west(p))
            tries(c,i,west(p,1),west(p,2));
        i = i + 1;
    }
    if(i < c.size())
    {
        show_path(c, i,steps);
    }

}
bool puzzle_original2(Puzzle p, vector<Puzzle>& c)
{
    assert(true);
    //                
    //                                          
    //                        
    for(int i = 0; i < c.size(); i++)
    {
        if(p == c[i])
        {
            return false;
        }
    }
    return true;
}
bool tries2(vector<Puzzle>& attempt, Pos next, Pos further, vector<Puzzle>& shortest, int max_depth)
{
    assert(next != further);
    //                
    //                                                                                                                                     
    //                                            
    Puzzle p = attempt[attempt.size() - 1];
    Puzzle newp = move_warehouse(p,next,further);
    if(puzzle_original2(newp,attempt))
    {
        attempt.push_back(newp);
        return true;
    }
    return false;

}
void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    assert(true);
    //                
    //                                                                                
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle p = attempt[CURRENT - 1];
    if(BEST > 0 && CURRENT >= BEST)
        return;
    else if(CURRENT > max_depth + 1)
        return;
    else if(puzzle_ready(p))
    {
        shortest = attempt;
        return;
    }
    if(can_go_north(p))
    {
        if(tries2(attempt,north(p,1), north(p,2),shortest,max_depth))
        {
            solve_depth_first(attempt,shortest,max_depth);
            attempt.pop_back();
        }
    }
    if(can_go_south(p))
    {
        if(tries2(attempt,south(p,1), south(p,2),shortest,max_depth))
        {
            solve_depth_first(attempt,shortest,max_depth);
            attempt.pop_back();
        }
    }
    if(can_go_west(p))
    {
        if(tries2(attempt,west(p,1), west(p,2),shortest,max_depth))
        {
            solve_depth_first(attempt,shortest,max_depth);
            attempt.pop_back();
        }
    }
    if(can_go_east(p))
    {
        if(tries2(attempt,east(p,1), east(p,2),shortest,max_depth))
        {
            solve_depth_first(attempt,shortest,max_depth);
            attempt.pop_back();
        }
    }
}

int main()
{
    vector< vector<char> > puzzle;
    ifstream infile;
    int steps, max_depth, input;
    steps = 0;
    Puzzle p = read_challenge(puzzle,infile);
    vector<Puzzle> p_attempt, p_solutions;
    p_attempt.push_back(p);
    show_challenge(p);
    cout << "Which method do you want to use: " << endl;
    cout << "1.) Breadth first method" << endl;
    cout << "2.) Depth first method" << endl;
    cin >> input;
    if(input == 1)
    {
        cout << "The solution is: " << endl;
        solve_breadth_first(p,steps);
        cout << "The amount of steps needed was : " << steps - 1 << endl;
    }
    else if(input == 2)
    {
        cout << "What do you want to be the maximal depth of a attempt to a solution? (please, keep in mind the challenge used)" << endl;
        cin >> max_depth;
        cout << "The solution is: " << endl;
        solve_depth_first(p_attempt,p_solutions,max_depth);
        for(int i = 0 ; i < p_solutions.size(); i++)
        {
            show_challenge(p_solutions[i]);
        }
        cout << "The amount of needed steps are: " << p_solutions.size() - 1 << endl;
    }

    return 0;
}

