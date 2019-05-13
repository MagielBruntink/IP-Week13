#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

//                             

struct position
{
    int y;
    int x;
};

struct Attempt
{
    vector<vector<char>> field;
    position pos;
    int depth;
};

enum Moves {North, South, West, East};  //                                                         

vector<vector<char>> field;     //                                                                 

position start_position;        //                                                      

/*                         
                              
                              
                              
                               
                              
                              
                              
*/

void import_file (ifstream& infile)
{
//              
    assert(infile.is_open());
//                                                                                                                              

    for (int i = 0; !infile.eof(); i++)
    {
        char ch;
        vector<char> temp;
        for (int j = 0; infile.get(ch) && ch != 10; j++)
        {
            temp.push_back(ch);
            if (ch == 'w')
            {
                start_position.x = j;
                start_position.y = i;
            }
        }
        field.push_back(temp);
    }
}

void show_field (const vector<vector<char>>& field)
{
//              
    assert(field.size() > 0);
//                                                                                   
    cout << endl;
    for (int i = 0; i < field.size(); i++)
    {
        for (int j = 0; j < field[i].size(); j++)
            cout << field[i][j];
        cout << endl;
    }
}

bool solved (Attempt& attempt)
{
//               
    assert(attempt.field.size() > 0);
//                                                      

    for (int i = 0; i < attempt.field.size(); i++)
        for (int j = 0; j < attempt.field[i].size(); j++)
            if (attempt.field[i][j] == 'b')
                return false;
    return true;
}

bool can_go_direction (Attempt& attempt, position pos, Moves direction)
{
//               
    assert(attempt.field.size() > 0 && pos.x >= 0 && pos.x >= 0 && direction >= 0 && direction <= 3);
//                                                                                                                                       
    if (direction == North)
    {
        char nextpos = attempt.field[pos.y - 1][pos.x];
        if (nextpos == '*')
            return false;
        if (nextpos == 'b' && (attempt.field[pos.y - 2][pos.x] == '*' || attempt.field[pos.y - 2][pos.x] == 'b' || attempt.field[pos.y - 2][pos.x] == 'B'))
            return false;

        return true;
    }
    if (direction == South)
    {
        char nextpos = attempt.field[pos.y + 1][pos.x];
        if (nextpos == '*')
            return false;
        if (nextpos == 'b' && (attempt.field[pos.y + 2][pos.x] == '*' || attempt.field[pos.y + 2][pos.x] == 'b' || attempt.field[pos.y + 2][pos.x] == 'B'))
            return false;

        return true;
    }
    if(direction == East)
    {
        char nextpos = attempt.field[pos.y][pos.x + 1];
        if (nextpos == '*')
            return false;
        if (nextpos == 'b' && (attempt.field[pos.y][pos.x + 2] == '*' || attempt.field[pos.y][pos.x + 2] == 'b' || attempt.field[pos.y][pos.x + 2] == 'B'))
            return false;

        return true;
    }
    if(direction == West)
    {
        char nextpos = attempt.field[pos.y][pos.x - 1];
        if (nextpos == '*')
            return false;
        if (nextpos == 'b' && (attempt.field[pos.y][pos.x - 2] == '*' || attempt.field[pos.y][pos.x - 2] == 'b' || attempt.field[pos.y][pos.x - 2] == 'B'))
            return false;

        return true;
    }
}

Attempt move_position(Attempt& attempt, position& cpos, Moves direction)
{
//               
    assert(attempt.field.size() > 0 && cpos.x >= 0 && cpos.x >= 0 && direction >= 0 && direction <= 3);
//                                                                                               

    Attempt new_attempt = attempt;

    if (direction == North)
    {
        if (attempt.field[cpos.y][cpos.x] == 'W')
            new_attempt.field[cpos.y][cpos.x] = '.';
        else
            new_attempt.field[cpos.y][cpos.x] = ' ';

        if (attempt.field[cpos.y - 1][cpos.x] == 'b')
        {
            if (attempt.field[cpos.y - 2][cpos.x] == '.')
                new_attempt.field[cpos.y - 2][cpos.x] = 'B';
            else
                new_attempt.field[cpos.y - 2][cpos.x] = 'b';
        }
        if (attempt.field[cpos.y - 1][cpos.x] == '.')
            new_attempt.field[cpos.y - 1][cpos.x] = 'W';
        else
            new_attempt.field[cpos.y - 1][cpos.x] = 'w';

        new_attempt.pos = {cpos.y - 1, cpos.x};
        new_attempt.depth++;

        return new_attempt;
    }

    if (direction == South)
    {
        if (attempt.field[cpos.y][cpos.x] == 'W')
            new_attempt.field[cpos.y][cpos.x] = '.';
        else
            new_attempt.field[cpos.y][cpos.x] = ' ';

        if (attempt.field[cpos.y + 1][cpos.x] == 'b')
        {
            if (attempt.field[cpos.y + 2][cpos.x] == '.')
                new_attempt.field[cpos.y + 2][cpos.x] = 'B';
            else
                new_attempt.field[cpos.y + 2][cpos.x] = 'b';
        }
        if (attempt.field[cpos.y + 1][cpos.x] == '.')
            new_attempt.field[cpos.y + 1][cpos.x] = 'W';
        else
            new_attempt.field[cpos.y + 1][cpos.x] = 'w';

        new_attempt.pos = {cpos.y + 1, cpos.x};
        new_attempt.depth++;

        return new_attempt;
    }

    if (direction == East)
    {
        if (attempt.field[cpos.y][cpos.x] == 'W')
            new_attempt.field[cpos.y][cpos.x] = '.';
        else
            new_attempt.field[cpos.y][cpos.x] = ' ';

        if (attempt.field[cpos.y][cpos.x + 1] == 'b')
        {
            if (attempt.field[cpos.y][cpos.x + 2] == '.')
                new_attempt.field[cpos.y][cpos.x + 2] = 'B';
            else
                new_attempt.field[cpos.y][cpos.x + 2] = 'b';
        }
        if (attempt.field[cpos.y][cpos.x + 1] == '.')
            new_attempt.field[cpos.y][cpos.x + 1] = 'W';
        else
            new_attempt.field[cpos.y][cpos.x + 1] = 'w';

        new_attempt.pos = {cpos.y, cpos.x + 1};
        new_attempt.depth++;

        return new_attempt;
    }

    if (direction == West)
    {
        if (attempt.field[cpos.y][cpos.x] == 'W')
            new_attempt.field[cpos.y][cpos.x] = '.';
        else
            new_attempt.field[cpos.y][cpos.x] = ' ';

        if (attempt.field[cpos.y][cpos.x - 1] == 'b')
        {
            if (attempt.field[cpos.y][cpos.x - 2] == '.')
                new_attempt.field[cpos.y][cpos.x - 2] = 'B';
            else
                new_attempt.field[cpos.y][cpos.x - 2] = 'b';
        }
        if (attempt.field[cpos.y][cpos.x - 1] == '.')
            new_attempt.field[cpos.y][cpos.x - 1] = 'W';
        else
            new_attempt.field[cpos.y][cpos.x - 1] = 'w';

        new_attempt.pos = {cpos.y, cpos.x - 1};
        new_attempt.depth++;

        return new_attempt;
    }
}

bool already_done (Attempt attempt, vector<Attempt> frontier)
{
//               
    assert(attempt.field.size() > 0 && frontier.size() > 0);
//                                                                                     
    for (int i = 0; i < frontier.size(); i++)
    {
        for (int j = 0; j < attempt.field.size(); j++)
        {
            for (int k = 0; j < attempt.field[i].size(); k++)
            {
                if (attempt.field[j][k] != frontier[i].field[j][k])
                    return false;
            }
        }
    }
    return true;
}

int breath_first_search (const vector<vector<char>>& field)
{
//               
    assert(field.size() > 0);
//                                                                                              
    Attempt start = {field, start_position, 0};
    vector<Attempt> frontier = {start};
    int i = 0;

    for (i; !solved(frontier[i]); i++)
    {
        if (can_go_direction(frontier[i], frontier[i].pos, North))
        {
            Attempt new_attempt = move_position(frontier[i], frontier[i].pos, North);
            if (!already_done(new_attempt, frontier))
                frontier.push_back(new_attempt);
        }
        if (can_go_direction(frontier[i], frontier[i].pos, South))
        {
            Attempt new_attempt = move_position(frontier[i], frontier[i].pos, South);
            if (!already_done(new_attempt, frontier))
                frontier.push_back(new_attempt);
        }
        if (can_go_direction(frontier[i], frontier[i].pos, East))
        {
            Attempt new_attempt = move_position(frontier[i], frontier[i].pos, East);
            if (!already_done(new_attempt, frontier))
                frontier.push_back(new_attempt);
        }
        if (can_go_direction(frontier[i], frontier[i].pos, West))
        {
            Attempt new_attempt = move_position(frontier[i], frontier[i].pos, West);
            if (!already_done(new_attempt, frontier))
                frontier.push_back(new_attempt);
        }
    }
    return frontier[i].depth;
}

void depth_first_search (vector<Attempt>& frontier, vector<Attempt>& optimal, int max_depth)
{
//               
    assert(frontier.size() > 0 && max_depth >= 0);
//                                                                                            

    if (frontier[frontier.size() - 1].depth >= max_depth || (optimal.size() > 0 && frontier.size() > optimal.size()))   //                                                    
        return;

    if (solved(frontier[frontier.size() - 1]))                                                                          //                                         
    {
        optimal = frontier;
        return;
    }
    else
    {                                                                                                                   //                                         
        if (can_go_direction(frontier[frontier.size() - 1], frontier[frontier.size() - 1].pos, North))                      //                                     
        {
            Attempt new_attempt = move_position(frontier[frontier.size() - 1], frontier[frontier.size() - 1].pos, North);       //                                                                     
            if (!already_done(new_attempt, frontier))                                                                           //                                               
            {
                frontier.push_back(new_attempt);                                                                                    //                                            
                depth_first_search(frontier, optimal, max_depth);                                                                   //                                                                                          
                frontier.pop_back();                                                                                                //                                                                                               
            }
        }
        if (can_go_direction(frontier[frontier.size() - 1], frontier[frontier.size() - 1].pos, South))
        {
            Attempt new_attempt = move_position(frontier[frontier.size() - 1], frontier[frontier.size() - 1].pos, South);
            if (!already_done(new_attempt, frontier))
            {
                frontier.push_back(new_attempt);
                depth_first_search(frontier, optimal, max_depth);
                frontier.pop_back();
            }
        }
        if (can_go_direction(frontier[frontier.size() - 1], frontier[frontier.size() - 1].pos, East))
        {
            Attempt new_attempt = move_position(frontier[frontier.size() - 1], frontier[frontier.size() - 1].pos, East);
            if (!already_done(new_attempt, frontier))
            {
                frontier.push_back(new_attempt);
                depth_first_search(frontier, optimal, max_depth);
                frontier.pop_back();
            }
        }
        if (can_go_direction(frontier[frontier.size() - 1], frontier[frontier.size() - 1].pos, West))
        {
            Attempt new_attempt = move_position(frontier[frontier.size() - 1], frontier[frontier.size() - 1].pos, West);
            if (!already_done(new_attempt, frontier))
            {
                frontier.push_back(new_attempt);
                depth_first_search(frontier, optimal, max_depth);
                frontier.pop_back();
            }
        }
    }
}

int main()
{
    string filename;
    cout << "Type number of level you want solved." << endl;        //                                                       
    cin >> filename;
    cout << endl;
    ifstream infile ("challenge." + filename + ".txt");
    import_file(infile);

    cout << "Starting position: (" << start_position.x + 1 << ", " << start_position.y + 1 << "):" << endl;
    show_field(field);

    cout << "Moves used to complete level (BFS): " << breath_first_search(field) << endl;

    Attempt start = {field, start_position};
    vector<Attempt> frontier = {start};
    vector<Attempt> optimal;
    depth_first_search(frontier, optimal, 5);
    cout << "Moves used to complete level (DFS): " << optimal[optimal.size() - 1].depth << endl;
}

