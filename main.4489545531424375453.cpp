#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

struct sokoban_cell
{
    char cell;
    bool destenation_cell;
};

struct current_attempt
{
    vector<vector<sokoban_cell> > puzzle;
    int index;
    int parent;
    string action;
};
vector<vector<sokoban_cell> > puzzle;

operator>> (istream& in, sokoban_cell& sokoban)
{
    char c;
    in >> c;
    if(c == 'W')
    {
        sokoban.destenation_cell = true;
        sokoban.cell = 'w';
    }
    else if(c == 'B')
    {
        sokoban.destenation_cell = true;
        sokoban.cell = 'b';
    }
    else if(c == '.')
    {
        sokoban.destenation_cell = true;
        sokoban.cell = '.';
    }
    else
    {
        sokoban.destenation_cell = false;
        sokoban.cell = c;
    }
}

operator<< (ostream& out, const sokoban_cell& sokoban)
{
    if(sokoban.destenation_cell)
    {
        if(sokoban.cell == 'b')
            cout << 'B';
        if(sokoban.cell == 'w')
            cout << 'W';
        else
            cout << '.';
    }
    else
        cout << sokoban.cell;
}

operator== (const sokoban_cell& sokoban, const char& c)
{
    if(sokoban.destenation_cell)
    {
        if(sokoban.cell == c && sokoban.destenation_cell == false)
            {
                return true;
            }

        if(sokoban.cell == 'w' && sokoban.destenation_cell == true && c == 'W')
            return true;
        if(sokoban.cell == 'b' && sokoban.destenation_cell == true && c == 'B')
            return true;
        if(sokoban.cell == '.' && sokoban.destenation_cell == true && c == '.')
            return true;
        else
            return false;
    }
    else
    {
       if(sokoban.cell == c)
       {
           return true;
       }
       else
            return false;

    }

}

void show_puzzle(vector<current_attempt>& all_attempts, current_attempt& attempt)
{//              
assert(all_attempts.size() > 0);
//                                                                                  
    if(attempt.parent == -1)
        return;
    else
    {
        show_puzzle(all_attempts,all_attempts[attempt.parent]);
        cout << attempt.action << "\n";
    }

}

bool complete(vector<current_attempt> all_attempts, int& x)
{//              
assert(all_attempts.size() > 0);
//                                                                                                     
    int z;
    if(all_attempts.size() > 3)
        z = 3;
    else
        z = all_attempts.size();

    for(int h = z ;h <= 0;h--)
    {
        for(int i = 0 ;i <= all_attempts[x-h].puzzle.size() ;i++)
        {
            for(int j = 0;j <= all_attempts[x-h].puzzle[i].size() ;j++)
            {
                if(puzzle[i][j] == 'b')
                {
                    x -= h;
                    cout << "h";
                    return true;
                }

            }
        }
    }
    return false;
}

void find_w(vector<vector<sokoban_cell> >& puzzle, int& n, int& m)
{//              
assert(puzzle.size() > 0);
//                                                                                           
    for(int i = 0;i < puzzle.size() ;i++)
    {

        for(int j = 0;j < puzzle[i].size() ;j++)
        {
            if(puzzle[i][j] == 'w' || puzzle[i][j] == 'W')
            {
                n = i;
                m = j;
                return;
            }
        }
    }
}

bool two_boxes(vector<vector<sokoban_cell> >& puzzle, int new_n , int new_m, int n, int m)
{//              
assert(puzzle.size() > 0);
//                                                                                   
    if(puzzle[n][m] == 'b' || puzzle[n][m] == 'B')
    {
        if(puzzle[n+new_n][m+new_m] == 'b' || puzzle[n+new_n][m+new_m] == 'B' || puzzle[n+new_n][m+new_m] == '*')
            return false;
    }
    return true;
}

bool can_move_west(vector<vector<sokoban_cell> >& puzzle)
{//              
assert(puzzle.size() > 0);
//                                                                                                   
    int n;
    int m;
    find_w(puzzle,n,m);
    m--;
    if(puzzle[n][m] == '*' || two_boxes(puzzle,0,-1,n,m))
        return false;
    return true;
}

bool can_move_north(vector<vector<sokoban_cell> >& puzzle)
{//              
assert(puzzle.size() > 0);
//                                                                                                    

    int n;
    int m;
    find_w(puzzle,n,m);

    n--;
    if(puzzle[n][m] == '*' || two_boxes(puzzle,-1,0,n,m))
        {
            return false;
        }

    return true;
}

bool can_move_east(vector<vector<sokoban_cell> >& puzzle)
{//              
assert(puzzle.size() > 0);
//                                                                                                    
    int n;
    int m;
    find_w(puzzle,n,m);
    m++;
    if(puzzle[n][m] == '*' || two_boxes(puzzle,0,1,n,m))
        return false;
    return true;
}

bool can_move_south(vector<vector<sokoban_cell> >& puzzle)
{//              
assert(puzzle.size() > 0);
//                                                                                                    
    int n;
    int m;
    find_w(puzzle,n,m);
    n++;
    if(puzzle[n][m] == '*' || two_boxes(puzzle,1,0,n,m))
        return false;
    return true;
}

void try_moving_west(vector<current_attempt> all_attempts,current_attempt attempt)
{//              
assert(all_attempts.size() > 0 && can_move_west(attempt.puzzle));
//                                                                                                                
    cout<< "36.625";
    int n;
    int m;
    vector<vector<sokoban_cell> > puzzle = attempt.puzzle;
    find_w(puzzle,n,m);
    cout<< "36.75";
    if(puzzle[n][m] == 'w')
        puzzle[n][m]= {' ', false};
    else
        puzzle[n][m]= {'.',true};
    m--;
    if(puzzle[n][m] == ' ')
        puzzle[n][m]= {'.',true};
    else if(puzzle[n][m] == '.')
        puzzle[n][m] = {'W',true};
    else if(puzzle[n][m] == 'b')
    {
        puzzle[n][m] = {'w', false};
        if(puzzle[n][m--] == ' ')
            puzzle[n][m--] = {'b', false};
        else
            puzzle[n][m--] = {'B', true};
    }
    else if(puzzle[n][m] == 'B')
    {
        puzzle[n][m] = {'W',true};
        if(puzzle[n][m--] == ' ')
            puzzle[n][m--] = {'b', false};
        else
            puzzle[n][m--] = {'B', true};
    attempt.parent = attempt.index;
    attempt.index = all_attempts.size();
    attempt.action = "north";
    all_attempts.push_back(attempt);

    }
}

void try_moving_north(vector<current_attempt> all_attempts,current_attempt attempt)
{//              
assert(all_attempts.size() > 0 && can_move_north(attempt.puzzle));
//                                                                                                                  
    int n;
    int m;
    vector<vector<sokoban_cell> > puzzle = attempt.puzzle;
    find_w(puzzle,n,m);
    if(puzzle[n][m] == 'w')
        puzzle[n][m]= {' ', false};
    else
        puzzle[n][m]= {'.',true};
    n--;
    if(puzzle[n][m] == ' ')
        puzzle[n][m]= {'.',true};
    else if(puzzle[n][m] == '.')
        puzzle[n][m] = {'W',true};
    else if(puzzle[n][m] == 'b')
    {
        puzzle[n][m] = {'w', false};
        if(puzzle[n--][m] == ' ')
            puzzle[n--][m] = {'b', false};
        else
            puzzle[n--][m] = {'B', true};
    }
    else if(puzzle[n][m] == 'B')
    {
        puzzle[n][m] = {'W',true};
        if(puzzle[n--][m] == ' ')
            puzzle[n--][m] = {'b', false};
        else
            puzzle[n--][m] = {'B', true};
    attempt.parent = attempt.index;
    attempt.index = all_attempts.size();
    attempt.action = "west";
    all_attempts.push_back(attempt);
    }
}

void try_moving_east(vector<current_attempt> all_attempts,current_attempt attempt)
{//              
assert(all_attempts.size() > 0 && can_move_east(attempt.puzzle));
//                                                                                                                  

    int n;
    int m;
    vector<vector<sokoban_cell> > puzzle = attempt.puzzle;
    find_w(puzzle,n,m);
    if(puzzle[n][m] == 'w')
        puzzle[n][m]= {' ', false};
    else
        puzzle[n][m]= {'.',true};
    m++;
    if(puzzle[n][m] == ' ')
        puzzle[n][m]= {'.',true};
    else if(puzzle[n][m] == '.')
        puzzle[n][m] = {'W',true};
    else if(puzzle[n][m] == 'b')
    {
        puzzle[n][m] = {'w', false};
        if(puzzle[n][m++] == ' ')
            puzzle[n][m++] = {'b', false};
        else
            puzzle[n][m++] = {'B', true};
    }
    else if(puzzle[n][m] == 'B')
    {
        puzzle[n][m] = {'W',true};
        if(puzzle[n][m++] == ' ')
            puzzle[n][m++] = {'b', false};
        else
            puzzle[n][m++] = {'B', true};
    attempt.parent = attempt.index;
    attempt.index = all_attempts.size();
    attempt.action = "south";
    all_attempts.push_back(attempt);
    }
}

void try_moving_south(vector<current_attempt> all_attempts,current_attempt attempt)
{//              
assert(all_attempts.size() > 0 && can_move_south(attempt.puzzle));
//                                                                                                                  
    int n;
    int m;
    vector<vector<sokoban_cell> > puzzle = attempt.puzzle;
    find_w(puzzle,n,m);
    if(puzzle[n][m] == 'w')
        puzzle[n][m]= {' ', false};
    else
        puzzle[n][m]= {'.',true};
    n++;
    if(puzzle[n][m] == ' ')
        puzzle[n][m]= {'.',true};
    else if(puzzle[n][m] == '.')
        puzzle[n][m] = {'W',true};
    else if(puzzle[n][m] == 'b')
    {
        puzzle[n][m] = {'w', false};
        if(puzzle[n++][m] == ' ')
            puzzle[n++][m] = {'b', false};
        else
            puzzle[n++][m] = {'B', true};
    }
    else if(puzzle[n][m] == 'B')
    {
        puzzle[n][m] = {'W',true};
        if(puzzle[n++][m] == ' ')
            puzzle[n++][m] = {'b', false};
        else
            puzzle[n++][m] = {'B', true};
    attempt.parent = attempt.index;
    attempt.index = all_attempts.size();
    attempt.action = "east";
    all_attempts.push_back(attempt);
    }
}

void breadth_search(vector<vector<sokoban_cell> >& puzzle)
{//              
assert(puzzle.size() > 0);
/*                                                                                                                                    
*/
    int x = 0;
    int i = 0;
    vector<current_attempt> all_attempts = {{puzzle,0,-1," "}};
    current_attempt attempt = all_attempts[i] ;
    while (!complete(all_attempts,x) && i < all_attempts.size())
    {
        if(can_move_north(attempt.puzzle))
        {
            try_moving_north(all_attempts, attempt);
            x++;
        }
        if(can_move_west(attempt.puzzle))
        {
            try_moving_north(all_attempts, attempt);
            x++;
        }
        if(can_move_south(attempt.puzzle))
        {
            try_moving_north(all_attempts, attempt);
            x++;
        }
        if(can_move_east(attempt.puzzle))
        {
            try_moving_north(all_attempts, attempt);
            x++;
        }
        i++;
    }
    if(complete(all_attempts,x))
        show_puzzle(all_attempts,attempt);
    else
        cout << "no possibilities";
}

void show_path(vector<string> attempt, int n)
{//              
assert(puzzle.size() > 0);
//                                                                                                    
    if(n < 0)
        return;
    else
    {
        show_path(attempt, n-1);
        cout << attempt[n] << "\n";
    }
}

bool in_a_loop(vector<current_attempt> all_attempts, vector<vector<sokoban_cell> > puzzle)
{//              
assert(puzzle.size() > 0);
//                                                                                                           
    for(int i = 0 ; i < all_attempts.size();i++)
    {
        if(puzzle == all_attempts[i].puzzle)
            return true;
    }
    return false;
}
void depth_search(vector<current_attempt> all_attempts, vector<vector<sokoban_cell> > puzzle, vector<string> attempt,int& steps)
{//              
assert(puzzle.size() > 0);
/*                                                                                                                       
*/
    if(in_a_loop(all_attempts,puzzle));
        return;
    all_attempts.push_back({puzzle,0,0,attempt[steps-1]});
    if(complete(all_attempts,steps))
    {
        show_path(attempt,attempt.size());
        return;
    }
    else
    {
        if(can_move_north(puzzle))
        {
            attempt.push_back("north");
            steps++;
            all_attempts.push_back({puzzle,0,0,attempt[steps-1]});
            try_moving_north(all_attempts, all_attempts[steps+1]);
            all_attempts.pop_back();
            depth_search(all_attempts, all_attempts[steps+1].puzzle, attempt, steps);
            all_attempts.pop_back();
            steps--;
            attempt.pop_back();
        }
        if(can_move_west(puzzle))
        {
            attempt.push_back("west");
            steps++;
            all_attempts.push_back({puzzle,0,0,attempt[steps-1]});
            try_moving_west(all_attempts, all_attempts[steps+1]);
            all_attempts.pop_back();
            depth_search(all_attempts, all_attempts[steps+1].puzzle, attempt, steps);
            all_attempts.pop_back();
            steps--;
            attempt.pop_back();
        }
        if(can_move_south(puzzle))
        {
            attempt.push_back("south");
            steps++;
            all_attempts.push_back({puzzle,0,0,attempt[steps-1]});
            try_moving_south(all_attempts, all_attempts[steps+1]);
            all_attempts.pop_back();
            depth_search(all_attempts, all_attempts[steps+1].puzzle, attempt, steps);
            all_attempts.pop_back();
            steps--;
            attempt.pop_back();
        }
        if(can_move_east(puzzle))
        {
            attempt.push_back("east");
            steps++;
            all_attempts.push_back({puzzle,0,0,attempt[steps-1]});
            try_moving_east(all_attempts, all_attempts[steps+1]);
            all_attempts.pop_back();
            depth_search(all_attempts, all_attempts[steps+1].puzzle, attempt, steps);
            all_attempts.pop_back();
            steps--;
            attempt.pop_back();
        }
    }

}

int main()
{
    vector<string> attempt;
    vector<current_attempt> all_attempts;
    int steps = 0;
    breadth_search(puzzle);
    depth_search(all_attempts,puzzle,attempt,steps);
    return 0;
}

