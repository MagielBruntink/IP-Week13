#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

//              
//         

struct Candidate
{
    vector<vector<char>> candidate;
    int candidate_parent;
};

vector<vector<char>> puzzle = {{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
                                {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
                                {'*', ' ', '.', 'b', 'w', ' ', ' ', ' ', ' ', '*'},
                                {'*', ' ', ' ', '*', '*', '*', '*', ' ', ' ', '*'},
                                {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
                                {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}};

bool solution (vector<vector<char>> puzzles)
{
    bool solution = true;
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (puzzles[i][j] == 'b')
                solution = false;
        }
    }
    return solution;
}

bool can_go_up (vector<vector<char>> puzzles, int i, int j){
    if (puzzles[i-1][j] == '*')
        return false;
    else if (puzzles[i-1][j] == 'b' && puzzles[i-2][j] == '*')
        return false;
    else if (puzzles[i-1][j] == 'B')
        return false;
    else
        return true;
}

bool can_go_right (vector<vector<char>> puzzles, int i, int j)
{
    if (puzzles[i][j+1] == '*')
        return false;
    else if (puzzles[i][j+1] == 'b' && puzzles[i][j+2] == '*')
        return false;
    else if (puzzles[i][j+1] == 'B')
        return false;
    else
        return true;
}

bool can_go_down (vector<vector<char>> puzzles, int i, int j)
{
    if (puzzles[i+1][j] == '*')
        return false;
    else if (puzzles[i+1][j] == 'b' && puzzles[i+2][j] == '*')
        return false;
    else if (puzzles[i+1][j] == 'B')
        return false;
    else
        return true;
}

bool can_go_left (vector<vector<char>> puzzles, int i, int j)
{
    if (puzzles[i][j-1] == '*')
        return false;
    else if (puzzles[i][j-1] == 'b' && puzzles[i][j-2] == '*')
        return false;
    else if (puzzles[i][j-1] == 'B')
        return false;
    else
        return true;
}

void step_up (vector<vector<char>> puzzles, vector<vector<char>> new_puzzle)
{
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (puzzles[i][j] == 'w' && can_go_up(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i-1][j] = 'w';
            }
            else if (puzzles[i][j] == 'W' && can_go_up(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i-1][j] = 'w';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == 'b' && can_go_up(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i-1][j] = 'w';
                puzzles[i-2][j] = 'b';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == 'b' && can_go_up(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i-1][j] = 'w';
                puzzles[i-2][j] = 'b';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == 'b' && puzzles[i-2][j] == '.' && can_go_up(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i-1][j] = 'w';
                puzzles[i-2][j] = 'B';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == 'b' && puzzles[i-2][j] == '.' && can_go_up(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i-1][j] = 'w';
                puzzles[i-2][j] = 'B';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == '.' && can_go_up(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i-1][j] = 'W';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == '.' && can_go_up(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i-1][j] = 'W';
            }
        }
    }
    new_puzzle = puzzles;
}

void step_right (vector<vector<char>> puzzles, vector<vector<char>> new_puzzle)
{
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (puzzles[i][j] == 'w' && can_go_right(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i][j+1] = 'w';
            }
            else if (puzzles[i][j] == 'W' && can_go_right(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i][j+1] = 'w';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == 'b' && can_go_right(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i][j+1] = 'w';
                puzzles[i][j+2] = 'b';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == 'b' && can_go_right(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i][j+1] = 'w';
                puzzles[i][j+2] = 'b';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == 'b' && puzzles[i-2][j] == '.' && can_go_right(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i][j+1] = 'w';
                puzzles[i][j+2] = 'B';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == 'b' && puzzles[i-2][j] == '.' && can_go_right(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i][j+1] = 'w';
                puzzles[i][j+2] = 'B';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == '.' && can_go_right(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i][j+1] = 'W';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == '.' && can_go_right(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i][j+1] = 'W';
            }
        }
    }
    new_puzzle = puzzles;
}

void step_down (vector<vector<char>> puzzles, vector<vector<char>> new_puzzle)
{
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (puzzles[i][j] == 'w' && can_go_down(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i+1][j] = 'w';
            }
            else if (puzzles[i][j] == 'W' && can_go_down(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i+1][j] = 'w';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == 'b' && can_go_down(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i+1][j] = 'w';
                puzzles[i+2][j] = 'b';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == 'b' && can_go_down(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i+1][j] = 'w';
                puzzles[i+2][j] = 'b';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == 'b' && puzzles[i-2][j] == '.' && can_go_down(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i+1][j] = 'w';
                puzzles[i+2][j] = 'B';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == 'b' && puzzles[i-2][j] == '.' && can_go_down(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i+1][j] = 'w';
                puzzles[i+2][j] = 'B';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == '.' && can_go_down(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i+1][j] = 'W';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == '.' && can_go_down(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i+1][j] = 'W';
            }
        }
    }
    new_puzzle = puzzles;
}

void step_left (vector<vector<char>> puzzles, vector<vector<char>> new_puzzle)
{
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (puzzles[i][j] == 'w' && can_go_left(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i][j-1] = 'w';
            }
            else if (puzzles[i][j] == 'W' && can_go_left(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i][j-1] = 'w';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == 'b' && can_go_left(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i][j-1] = 'w';
                puzzles[i][j-2] = 'b';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == 'b' && can_go_left(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i][j-1] = 'w';
                puzzles[i][j-2] = 'b';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == 'b' && puzzles[i-2][j] == '.' && can_go_left(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i][j-1] = 'w';
                puzzles[i][j-2] = 'B';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == 'b' && puzzles[i-2][j] == '.' && can_go_left(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i][j-1] = 'w';
                puzzles[i][j-2] = 'B';
            }
            else if (puzzles[i][j] == 'w' && puzzles[i-1][j] == '.' && can_go_left(puzzles, i, j))
            {
                puzzles[i][j] = ' ';
                puzzles[i][j-1] = 'W';
            }
            else if (puzzles[i][j] == 'W' && puzzles[i-1][j] == '.' && can_go_left(puzzles, i, j))
            {
                puzzles[i][j] = '.';
                puzzles[i][j-1] = 'W';
            }
        }
    }
    new_puzzle = puzzles;
}

bool puzzle_present_breadth (vector<Candidate> c, int i, vector<vector<char>> new_puzzle)
{
    bool present = false;
    for (int j = i; j>=0; j--)
    {
        if (new_puzzle == c[j].candidate)
            present = true;
    }
    return present;
}

void tries_up (vector<Candidate>& c, int i)
{
    vector<vector<char>> puzzles = c[i].candidate;
    vector<vector<char>> new_puzzle;
    step_up(puzzles, new_puzzle);
    Candidate new_candidate = {new_puzzle, i};
    if (!puzzle_present_breadth(c, i, new_puzzle))
        c.push_back(new_candidate);
}

void tries_right (vector<Candidate>& c, int i)
{
    vector<vector<char>> puzzles = c[i].candidate;
    vector<vector<char>> new_puzzle;
    step_right(puzzles, new_puzzle);
    Candidate new_candidate = {new_puzzle, i};
    if (!puzzle_present_breadth(c, i, new_puzzle))
        c.push_back(new_candidate);
}

void tries_down (vector<Candidate>& c, int i)
{
    vector<vector<char>> puzzles = c[i].candidate;
    vector<vector<char>> new_puzzle;
    step_down(puzzles, new_puzzle);
    Candidate new_candidate = {new_puzzle, i};
    if (!puzzle_present_breadth(c, i, new_puzzle))
        c.push_back(new_candidate);
}

void tries_left (vector<Candidate>& c, int i)
{
    vector<vector<char>> puzzles = c[i].candidate;
    vector<vector<char>> new_puzzle;
    step_left(puzzles, new_puzzle);
    Candidate new_candidate = {new_puzzle, i};
    if (!puzzle_present_breadth(c, i, new_puzzle))
        c.push_back(new_candidate);
}

void Breadth_first_search ()
{ //              
    assert (true);
  //               
  //                                                      
    vector<Candidate> c = {{puzzle, -1}};
    int i = 0;
    while (i < c.size() && !solution(c[i].candidate))
    {
        vector<vector<char>> puzzles = c[i].candidate;
        tries_up(c, i);
        tries_right(c, i);
        tries_down(c, i);
        tries_left(c, i);
        i = i+1;
    }
}

bool puzzle_present_depth (vector<vector<char>> new_puzzle, vector<vector<vector<char>>> attempt)
{
    bool the_same = false;
    for (int i=0; i<attempt.size(); i++)
    {
        if (new_puzzle == attempt[i])
            the_same = true;
    }
    return the_same;
}

void try_up (vector<vector<vector<char>>>& attempt, vector<vector<vector<char>>>& shortest, int max_depth)
{
    vector<vector<char>> p = attempt[attempt.size()-1];
    vector<vector<char>> newp;
    step_up(p, newp);
    if (!puzzle_present_depth(newp, attempt))
    {
        attempt.push_back(newp);
        depth_first_search(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}
void try_right (vector<vector<vector<char>>>& attempt, vector<vector<vector<char>>>& shortest, int max_depth)
{
    vector<vector<char>> p = attempt[attempt.size()-1];
    vector<vector<char>> newp;
    step_right(p, newp);
    if (!puzzle_present_depth(newp, attempt))
    {
        attempt.push_back(newp);
        depth_first_search(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void try_down (vector<vector<vector<char>>>& attempt, vector<vector<vector<char>>>& shortest, int max_depth)
{
    vector<vector<char>> p = attempt[attempt.size()-1];
    vector<vector<char>> newp;
    step_down(p, newp);
    if (!puzzle_present_depth(newp, attempt))
    {
        attempt.push_back(newp);
        depth_first_search(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void try_left (vector<vector<vector<char>>>& attempt, vector<vector<vector<char>>>& shortest, int max_depth)
{
    vector<vector<char>> p = attempt[attempt.size()-1];
    vector<vector<char>> newp;
    step_left(p, newp);
    if (!puzzle_present_depth(newp, attempt))
    {
        attempt.push_back(newp);
        depth_first_search(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void depth_first_search (vector<vector<vector<char>>>& attempt, vector<vector<vector<char>>>& shortest, int max_depth)
{ //              
    assert (!attempt.empty() && max_depth >= 0);
  //               
  //                                                       
    const int current = attempt.size();
    const int best = shortest.size();
    vector<vector<char>> p = attempt[current-1];
    if (best > 0 && current>= best)
        return;
    else if (current > max_depth+1)
        return;
    else if (solution(p))
    {
        shortest = attempt;
        return;
    }
    try_up(attempt, shortest, max_depth);
    try_right(attempt, shortest, max_depth);
    try_down(attempt, shortest, max_depth);
    try_left(attempt, shortest, max_depth);
}

void show_puzzle ()
{
    for (int i = 0; i <6; i++)
    {
        for (int j = 0; j<10; j++)
        {
            cout << puzzle[i][j];
        }
        cout << endl;
    }
}

int main()
{
    int max_depth = 5;
    vector<vector<vector<char>>> initial_attempt = {{{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
                                                     {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
                                                     {'*', ' ', '.', 'b', 'w', ' ', ' ', ' ', ' ', '*'},
                                                     {'*', ' ', ' ', '*', '*', '*', '*', ' ', ' ', '*'},
                                                     {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
                                                     {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}}};
    vector<vector<vector<char>>> shortest_attempt;

    Breadth_first_search();
    depth_first_search(initial_attempt, shortest_attempt, max_depth);
    return 0;
}
