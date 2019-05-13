#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <math.h>

using namespace std;

/*                                              
                                                
                                                
                                              */

const int LENGTH = 6;
const int WIDTH = 7;

struct Position
{
    int row, col;
} ;

struct Puzzle
{
    vector<vector<char>> puzzle;
    Position object ;
} ;

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

bool puzzle_ready(Puzzle p)
{
    /*                */
    assert (true);
    /*                                                                                                   */
    for (int i = 0; i < p.puzzle.size(); i++)
    {
        for (int j = 0; j < p.puzzle[i].size(); j++)
        {
            if (p.puzzle[i][j] == '.' || p.puzzle[i][j] == 'W')
            {
                return false;
            }
        }
    }
    return true;
}

bool puzzle_present_BreadthFirst (vector<Candidate>& c, Puzzle p)
{
    /*                */
    assert (true);
    /*                                                                             */
    for (int i = 0; i < c.size(); i++)
    {
        if (c[i].candidate.puzzle == p.puzzle)
        {
            return true;
        }
    }
    return false;
}

bool puzzle_present_DepthFirst (vector<Puzzle>& c, Puzzle p)
{
    /*                */
    assert (true);
    /*                                                                           */
    for (int i = 0; i < c.size(); i++)
    {
        if (c[i].puzzle == p.puzzle)
        {
            return true;
        }
    }
    return false;
}

bool can_go_north(Puzzle p)
{
    /*                */
    assert (true);
    /*                                                              */
    if ((p.puzzle[p.object.row-1][p.object.col] == '*') || ((p.puzzle[p.object.row-1][p.object.col] == 'b') && (p.puzzle[p.object.row-2][p.object.col] == '*'))
            || ((p.puzzle[p.object.row-1][p.object.col] == 'B') && (p.puzzle[p.object.row-2][p.object.col] == '*')))
    {
        return false;
    }
    return true;
}

Position north (Puzzle p)
{
    p.object.row = p.object.row-1;
}

bool can_go_south(Puzzle p)
{
    /*                                                            */
    assert (true);
    /*                  */
    if ((p.puzzle[p.object.row+1][p.object.col] == '*') || ((p.puzzle[p.object.row+1][p.object.col] == 'b') && (p.puzzle[p.object.row+2][p.object.col] == '*'))
            || ((p.puzzle[p.object.row+1][p.object.col] == 'B') && (p.puzzle[p.object.row+2][p.object.col] == '*')))
    {
        return false;
    }
    return true;
}

Position south(Puzzle p)
{
    p.object.row = p.object.row+1;
}

bool can_go_west(Puzzle p)
{
    /*                */
    assert (true);
    /*                                                        */
    if ((p.puzzle[p.object.row][p.object.col-1] == '*') || ((p.puzzle[p.object.row][p.object.col-1] == 'b') && (p.puzzle[p.object.row][p.object.col-2] == '*'))
            || ((p.puzzle[p.object.row][p.object.col-1] == 'B') && (p.puzzle[p.object.row][p.object.col-2] == '*')))
    {
        return false;
    }
    return true;
}

Position west (Puzzle p)
{
    p.object.col = p.object.col-1;
}

bool can_go_east(Puzzle p)
{
    /*                */
    assert (true);
    /*                                                             */
    if ((p.puzzle[p.object.row][p.object.col+1] == '*') || ((p.puzzle[p.object.row][p.object.col+1] == 'b') && (p.puzzle[p.object.row][p.object.col+2] == '*'))
            || ((p.puzzle[p.object.row][p.object.col+1] == 'B') && (p.puzzle[p.object.row][p.object.col+2] == '*')))
    {
        return false;
    }
    return true;
}

Position east (Puzzle p)
{
    p.object.col = p.object.col+1;
}

void show_puzzle(vector<vector<char>>& puzz)
{
    /*                */
    assert (true);
    /*                                                                */
    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            cout << puzz[i][j];
        }
        cout << endl;
    }
}
Puzzle move_empty(Puzzle p, Position direction)
{
    /*                */
    assert (true);
    /*                                                                                                */
    Position worker = {p.object.row + direction.row, p.object.col + direction.col};
    Position box = {p.object.row + 2 * direction.row, p.object.col + 2 * direction.col};

    if ((p.puzzle[worker.row][worker.col]) == 'b')
    {
        p.puzzle[worker.row][worker.col] = 'w';
        if ((p.puzzle[box.row][box.col]) == '.')
        {
            p.puzzle[box.row][box.col] = 'B';
        }
        else
        {
            p.puzzle[box.row][box.col] = 'b';
        }
    }
    else
    {
        if ((p.puzzle[worker.row][worker.col]) == 'B')
        {
            p.puzzle[worker.row][worker.col] = 'W';
            if ((p.puzzle[box.row][box.col]) == '.')
            {
                p.puzzle[box.row][box.col] = 'B';
            }
            else
            {
                p.puzzle[box.row][box.col] = 'b';
            }
        }
    }

    if (p.puzzle[worker.row][worker.col] == ' ')
    {
        p.puzzle[worker.row][worker.col] = 'w';
    }
    if (p.puzzle[worker.row][worker.col] == '.')
    {
        p.puzzle[worker.row][worker.col] = 'W';
    }

    if (p.puzzle[p.object.row][p.object.col] == 'w')
    {
        p.puzzle[p.object.row][p.object.col] = ' ';
    }
    else
    {
        p.puzzle[p.object.row][p.object.col] = '.';
    }

    p.object = worker;
    return p;
}

void tries_BreadthFirst (vector<Candidate>& c, int i, Position next)
{
    /*                */
    assert (true);
    /*                                                                                                            */
    Puzzle p = c[i].candidate;
    Puzzle newp = move_empty(p, next);
    Candidate newc = {newp, i};
    if (!puzzle_present_BreadthFirst(c, newp))
    {
        c.push_back(newc);
    }
}

void solve_DepthFirst (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void tries_DepthFirst (vector<Puzzle>& attempt, Position next, vector<Puzzle>& shortest, int max_depth)
{
    /*                 */
    assert (true);
    /*                                                                                                           */
    Puzzle p = attempt[attempt.size()-1];
    Puzzle newp = move_empty(p, next);
    if (!puzzle_present_DepthFirst(attempt, newp))
    {
        attempt.push_back(newp);
        solve_DepthFirst(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

int show_path (vector<Candidate>& c, int i, int counter)
{
    /*                */
    assert (counter >= 0);
    /*                                                                         */
    if (i < 0)
    {
        counter--;
        return counter;
    }
    else
    {
        counter++;
        counter = show_path(c, c[i].parent_candidate, counter);
        show_puzzle(c[i].candidate.puzzle);
    }
}

void solve_BreadthFirst (Puzzle start)
{
    /*                */
    assert (true);
    /*                                                             */
    vector<Candidate> c = {{start,-1}};
    int i = 0;
    while (i < c.size() && !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if (can_go_north(p))
        {
            tries_BreadthFirst(c, i, {-1,0});
        }
        if (can_go_south(p))
        {
           tries_BreadthFirst(c, i, {1,0});
        }
        if (can_go_west(p))
        {
            tries_BreadthFirst(c, i, {0,-1});
        }
        if (can_go_east(p))
        {
            tries_BreadthFirst(c, i, {0,1});
        }
        i++;
    }
    if (i < c.size())
    {
        cout << "=~~~~~~~~~~~~~~~~~~~~~~=" << endl << "The optimal path is:" << endl << "=~~~~~~~~~~~~~~~~~~~~~~=" << endl << endl;
        show_path(c, i, 0);
    }
    cout << endl << "=~~~~~~~~~~~~~~~~~~~~~~=" << endl << "End of solution" << endl << "=~~~~~~~~~~~~~~~~~~~~~~=" << endl;
}

void solve_DepthFirst (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    /*                */
    assert (true);
    /*                                                             */
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle p = attempt[CURRENT-1];
    if (BEST > 0 && CURRENT >= BEST)
        return;
    else if (CURRENT > max_depth+1)
        return;
    else if (puzzle_ready(p))
    {
        shortest = attempt;
        return;
    }
    if (can_go_north(p))
    {
        tries_DepthFirst(attempt, {-1,0}, shortest, max_depth);
    }
    if (can_go_south(p))
    {
           tries_DepthFirst(attempt, {1,0}, shortest, max_depth);
    }
    if (can_go_west(p))
    {
        tries_DepthFirst(attempt, {0,-1}, shortest, max_depth);
    }
    if (can_go_east(p))
    {
        tries_DepthFirst(attempt, {0,1}, shortest, max_depth);
    }
}

int main()
{
    vector<vector<char> > puzzle = {{'*','*','*','*','*','*','*'},
                                    {'*','w',' ',' ',' ','*','*'},
                                    {'*',' ','b','b',' ',' ','*'},
                                    {'*',' ','*','.',' ','.','*'},
                                    {'*',' ',' ',' ',' ',' ','*'},
                                    {'*','*','*','*','*','*','*'}};

    Puzzle p = Puzzle();
    p.puzzle = puzzle;
    p.object = {1, 1};
    solve_BreadthFirst(p);

    vector<Puzzle> attempt = {p};
    vector<Puzzle> shortest;
    int max_depth = 20;
    solve_DepthFirst(attempt, shortest, max_depth);

    cout << endl << "=~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~=" << endl << "For depth-first search the optimal path is: " <<
            shortest.size() - 1 << " step(s) long." << endl << "=~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~=" << endl;
    return 0;
}

