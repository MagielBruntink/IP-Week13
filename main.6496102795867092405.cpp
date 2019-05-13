#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cassert>

/*                                           

                                                
                                               

                                            */

using namespace std;
const int WIDTH = 15;
const int HEIGHT = 15;

typedef char Cell;

struct Position
{
    int col, row;
};

Position MAX_POS = {0,0};

struct World
{
    Cell world[WIDTH][HEIGHT];
    Position worker;
};

ostream& operator<< (ostream& out, Position pos)
{
    //             
    assert(true);
    //                                             
    out << "row:" << pos.row << " column:" << pos.col << endl;
    return out;
}

bool operator== (Position& a, Position& b)
{
    //             
    assert(true);
    //                                                                       
    if (a.col == b.col &&  a.row == b.row)
        return true;
    else
        return false;
}

bool operator== (World& a, World& b)
{
    //             
    assert(true);
    //                                                                       
    if (a.worker == b.worker && a.world == b.world)
        return true;
    else
        return false;
}

bool print_vector_position(vector<Position> vec)
{
    //              
    assert(true);
    //                                                                       
    for(int i = 0;  i < vec.size(); i++)
    {
        cout << vec[i];
    }
}

/*                    */
bool is_valid_token(char c)
{
    //              
    assert(true);
    //                                                                                                    
    if(c == '*' || c == ' '|| c == '.' || c == 'w' || c == 'W' || c == 'B' || c == 'b')
        return true;
    else
        return false;
}

void read_a_row(ifstream& infile, World& start, Position& pos, vector<Position>& destinations, char& c)
{
    //              
    assert(infile.is_open());
    /*               
                                                                                                                                                          
                                                                                                                       */
    pos.col = 0;
    while(c != '\n' && infile)
    {
        if(c == '.' || c == 'B' || c == 'W')
            destinations.push_back(pos);
        if(c == 'W' || c == 'w')
            start.worker = pos;
        start.world[pos.col][pos.row] = c;
        pos.col++;
        infile.get(c);
    }
}

bool put_file_in_array(ifstream& infile, World& start, vector<Position>& destinations)
{
    //             
    assert(infile.is_open());
    /*               
                                                                                                                                                                    
                                                                                    */
    Position filling = {0,0};
    char c = '\0';
    infile.get(c);
    while(filling.row < HEIGHT && c != '\n' && infile)
    {
        read_a_row(infile, start, filling, destinations, c);
        filling.row++;
        infile.get(c);
    }
    MAX_POS = filling;
    if (filling.row > 0 && is_valid_token(start.world[0][0]))
        return true;
    else
    {cout << "not filled" << endl;
        return false;}

}

string ask_for_filename()
{
    //              
    assert(true);
    //                                                                  
    string user_input;
    cout << "Which file do you want to try? Include .txt" << endl;
    cin >> user_input;
    return user_input;
}

bool read_file(ifstream& infile, World& start, vector<Position>& destinations)
{
    //              
    assert(!infile.is_open());
    //                                                                                                              
    //                                                                                                 
    //                                                                                           
    string filename = ask_for_filename();
    infile.open(filename.c_str());
    if (!infile.is_open())
    {
        cout << "File not found" << endl;
        return false;
    }
    if (put_file_in_array(infile, start, destinations))
    {
        return true;
    }
    else
    {
        return false;
    };
}

void show_world(Cell world[WIDTH][HEIGHT])
{
    //              
    assert(true);
    //                                                                                                               
    //                                                                                                 
    for(int row = 0; row < HEIGHT; row++)
    {
        for(int column = 0; column < WIDTH; column++)
        {
            if(is_valid_token(world[column][row]))
                cout << world[column][row];
        }
        if (is_valid_token(world[1][row]))
            cout << endl;
    }
}

/*                  */
/*                                  */
enum Direction {north, east, south, west};

bool out_of_bounds(Position position)
{
    //              
    assert(MAX_POS.col >= 0 && MAX_POS.row >= 0);
    //                                                                                       
    if(position.col < 0 || position.row < 0 || position.col >= MAX_POS.col || position.row >= MAX_POS.row)
        return true;
    else
        return false;
}

bool front_of_wall(Position new_pos, Cell world[WIDTH][HEIGHT])
{
    //              
    assert(!out_of_bounds(new_pos));
    //                                                                                                    
    if (world[new_pos.col][new_pos.row] == '*')
    {
        return true;
    }
    else
        return false;
}

bool front_of_box(Position new_pos, Cell world[WIDTH][HEIGHT])
{
    //              
    assert(!out_of_bounds(new_pos));
    //                                                                                                  
    if (world[new_pos.col][new_pos.row] == 'B'|| world[new_pos.col][new_pos.row] == 'b')
    {
        return true;
    }
    else
        return false;
}

bool is_part_of(Position position, vector<Position> positions)
{
    //              
    assert(true);
    //                                                                                                         

    for (int i =0; i < positions.size(); i++)
    {
        if(positions[i] == position)
            return true;
    }
    return false;
}

Cell upgrade_destination(Position old_pos, vector<Position> destinations, Cell old)
{
    //              
    assert(is_valid_token(old));
    //                                                                                                                                        
    //                                                         
    if (is_part_of(old_pos, destinations))
    {
        if (old == ' ')
            return '.';
        else if (old == 'w')
            return 'W';
        else if (old == 'b')
            return 'B';
        else
            return old;
    }
    else
    {
        if (old == '.')
            return ' ';
        else if (old == 'W')
            return 'w';
        else if (old == 'B')
            return 'b';
        else
            return old;
    }
}

World swap_tokens(World& w, Position old_pos, Position new_pos, vector<Position> destination)
{
     //              
    assert(true);
    //                                                                                                                                                    
    Cell temp_new = upgrade_destination(old_pos, destination, w.world[new_pos.col][new_pos.row]);
    Cell temp_old = upgrade_destination(new_pos, destination, w.world[old_pos.col][old_pos.row]);
    w.world[old_pos.col][old_pos.row] = temp_new;
    w.world[new_pos.col][new_pos.row] = temp_old;
    return w;
}

World swap_worker(World& w, Position new_pos, vector<Position> destination)
{
    //              
    assert(true);
    //                                                                                                                                   
    w = swap_tokens(w, w.worker, new_pos, destination);
    w.worker = new_pos;
    return w;
}

World push_box(World& world, Position position_box, vector<Position> destination, Direction wind)
{
    //              
    assert(true);
    //                                                                                                                                                   
    Position new_position;
    Position old_box = position_box;
      switch(wind)
    {
    case north:
        new_position = {position_box.col, position_box.row-1};
        break;
    case south:
        new_position = {position_box.col, position_box.row+1};
        break;
    case west:
        new_position = {position_box.col-1, position_box.row};
        break;
    case east:
        new_position = {position_box.col+1, position_box.row};
        break;
    }

    world = swap_tokens(world, old_box, new_position, destination);
    return world;

}

bool go_direction(World w, Direction wind, bool push, Position& new_position)
{
    //              
    assert(true);
    //                                                                                                                                        
    //                                                                                                  
    switch(wind)
    {
    case north:
        new_position = {w.worker.col, w.worker.row-1};
        break;
    case south:
        new_position = {w.worker.col, w.worker.row+1};
        break;
    case west:
        new_position = {w.worker.col-1, w.worker.row};
        break;
    case east:
        new_position = {w.worker.col+1, w.worker.row};
        break;
    }

    if(out_of_bounds(new_position))
        return false;
    else if(front_of_wall(new_position, w.world))
        return false;
    else if (front_of_box(new_position, w.world) && !push)
        return false;
    else if (front_of_box(new_position, w.world))
    {
        w.worker =  new_position;
        Position box_position = new_position;
        return (go_direction(w, wind, false, box_position));
    }
    else
    {
        return true;
    };

}

/*                               */

struct Candidate
{
    World candidate;
    int parent_candidate;
};

bool puzzle_done(World& w, vector<Position> destinations)
{
    //             
    assert(destinations.size() > 0);
    //                                                                                                                                         
    for(int i = 0; i < destinations.size(); i++)
    {
        if(w.world[destinations[i].col][destinations[i].row] != 'B')
            return false;
    }
    return true;
}

bool world_present(vector<Candidate>& c, World w)
{
    //              
    assert(c.size() > 0);
    //                                                           
    for(int j = 0; j < c.size(); j++)
    {
        if (c[j].candidate == w)
        {
            return true;
        }
    }
    return false;
}

void tries(vector<Candidate>& c, int i, Position next, vector<Position> destinations, Direction wind)
{
    //              
    assert(true);
    //                                                                                                                                       
    //                                     
    World w = c[i].candidate;
    if (front_of_box(next, w.world))
    {
            w = push_box(w, next, destinations, wind);
    }
    w = swap_worker(w, next, destinations);
    World neww = w;
    Candidate newc = {neww, i};
    if(!world_present(c, neww))
        c.push_back(newc);
}

vector<World> path(vector<Candidate>& c, int i)
{
    //              
    assert(i >= -1);
    //                                                                                                                                      
    vector<World> path_so_far;
    if(i >= 0)
    {
        path_so_far = path(c, c[i].parent_candidate);
        path_so_far.push_back(c[i].candidate);
    }

    return path_so_far;
}

void show_path(vector<Candidate>& c, int i)
{
    //              
    assert(i >= -1);
    //                                                                                                                    
    vector<World> path_from_furthest = path(c, i);
    for(int j = 0; j < path_from_furthest.size(); j++)
    {
        show_world(path_from_furthest[j].world);
    }
}

void solve_puzzle(World start, vector<Position> destinations)
{
    //              
    assert(true);
    //                                                                                                                                                
    //                                                                                                                                                  
    //                                                                         

    vector<Candidate> c = {{start, -1}};
    int i = 0;
    int size_of = c.size();
    while(i < c.size() && !puzzle_done(c[i].candidate, destinations))
    {
        World w  = c[i].candidate;
        Position new_position;
        if(go_direction(w,north,true,new_position))
            tries(c, i, new_position, destinations, north);
        if(go_direction(w,south,true,new_position))
            tries(c, i, new_position, destinations, south);
        if(go_direction(w,east,true,new_position))
            tries(c, i, new_position, destinations, east);
        if(go_direction(w,west,true,new_position))
            tries(c, i, new_position, destinations, west);
        i = i+1;
    }
    if (i <c.size())
    {
        cout << "SOLVED!!" << endl;
        show_path(c, i);
    }
}

/*                                 */
bool world_present_dfs(vector<World> v, World w)
{
    //              
    assert(v.size() > 0);
    //                                                           
    for(int i = 0; i < v.size(); i++)
{
        if (v[i] == w)
        {
            return true;
        }
    }
    return false;
}

void solve_puzzle_dfs(vector<World>& attempt, vector<World>& shortest, int max_depth, vector<Position> destinations);

void triesdfs (vector<World>& attempt, Position next, vector<World>& shortest, vector<Position> destinations, Direction wind, int max_depth)
{
    //              
    assert(true);
    //                                                                                                                                          
    World w = attempt[attempt.size()-1];
    if (front_of_box(next, w.world))
    {
            w = push_box(w, next, destinations, wind);
    }
    w = swap_worker(w, next, destinations);
    World neww = w;
    if(!world_present_dfs(attempt, neww))
    {
        attempt.push_back(neww);
        solve_puzzle_dfs(attempt, shortest, max_depth, destinations);
        attempt.pop_back();
    }
}

void solve_puzzle_dfs(vector<World>& attempt, vector<World>& shortest, int max_depth, vector<Position> destinations)
{
    //              
    assert(attempt.size()>0 && max_depth >= 0);
    //                                                                                                          
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    World w = attempt[CURRENT-1];
    if(BEST > 0 && CURRENT >= BEST)
        return;
    else if(CURRENT > max_depth+1)
        return;
    else if(puzzle_done(w, destinations))
    {
        shortest = attempt;
        return;
    }
    Position new_position;
    if(go_direction(w,north,true,new_position))
            triesdfs(attempt, new_position, shortest, destinations, north, max_depth);
    if(go_direction(w,south,true,new_position))
            triesdfs(attempt, new_position, shortest, destinations, south, max_depth);
    if(go_direction(w,east,true,new_position))
            triesdfs(attempt, new_position, shortest, destinations, east, max_depth);
    if(go_direction(w,west,true,new_position))
            triesdfs(attempt, new_position, shortest, destinations, west, max_depth);
}

void show_vector_shortest(vector<World> shortest)
{
    //              
    assert(shortest.size());
    //                                                               
    for(int i = 0; i < shortest.size(); i++)
    {
        show_world(shortest[i].world);
    }
}

int main()
{
    World start{{},{0,0}};
    vector <Position> destinations;
    vector <World> attempt, shortest;
    ifstream infile;
    if(!read_file(infile, start, destinations))
    {
        cout << "Something went wrong";
        return -1;
    }
    show_world(start.world);
    attempt.push_back(start);
    solve_puzzle_dfs(attempt, shortest, 4, destinations);
    show_vector_shortest(shortest);
    return 0;
}

