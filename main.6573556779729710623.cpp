//                       

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

#define NDEBUG

using namespace std;

typedef vector<vector<char>> World;

struct Pos{
    int x;
    int y;
};

struct Candidate{
    World world;
    int depth;
    vector<char> path;
};

void operator<< (ostream& out, Pos pos){
    cout << "(" << pos.x << ", " << pos.y << ")" << endl;
}

void print(World world){
//      
    assert(true);
//                                        

    for(int y = 0; y < world.size(); y++){
        for(int x = 0; x < world[y].size(); x++){
            cout << world[y][x];
        }
        cout << endl;
    }
    cout << endl;
}

void print_path(vector<char>& path){
//      
    assert(true);
//                                       

    for(int i = 0; i < path.size(); i++){
        cout << path[i];
    }
    cout << endl;
}

void read_file(string filename, World& world){
    ifstream input(filename);

//                             
    assert(input.is_open());
//                                             

    char symbol;
    input.get(symbol);

    while(!input.eof()){
        vector<char> row;
        while(symbol != '\n'){
            row.push_back(symbol);
            input.get(symbol);
        }
        world.push_back(row);
        input.get(symbol); //               
    }

    input.close();
}

bool final_state(World world){
//      
    assert(true);
//                                                                                           

    for(int y = 0; y < world.size(); y++){
        for(int x = 0; x < world[y].size(); x++){
            if(world[y][x] == '.' || world[y][x] == 'W')
                return false;
        }
    }
    return true;
}

Pos find_worker(World world){
//                                           
    assert(true);
//                                                             

    for(int y = 0; y < world.size(); y++){
        for(int x = 0; x < world[y].size(); x++){
            if(world[y][x] == 'w' || world[y][x] == 'W'){
                Pos pos;
                pos.x = x;
                pos.y = y;
                return pos;
            }
        }
    }
}

Pos find_next(Pos start, Pos trans){
//      
    assert(true);
//                                                        

    Pos next;
    next.x = start.x + trans.x;
    next.y = start.y + trans.y;
    return next;
}

bool can_go_pos(World& world, Pos trans){
//      
    assert(true);
//                                                                                

    Pos worker = find_worker(world);
    Pos next = find_next(worker, trans);

    char n = world[next.y][next.x];

    if(n == '*')
        return false;
    if(n == 'b' || n == 'B'){
        Pos next2 = find_next(next, trans);
        char nn = world[next2.y][next2.x];

        if(nn == ' ' || nn == '.')
            return true;
        else
            return false;
    }

    return true;
}

bool can_go_north(World& world){
//      
    assert(true);
//                                            

    Pos trans = {0, -1};
    return can_go_pos(world, trans);
}

bool can_go_east(World& world){
//      
    assert(true);
//                                           

    Pos trans = {1, 0};
    return can_go_pos(world, trans);
}

bool can_go_south(World& world){
//      
    assert(true);
//                                            

    Pos trans = {0, 1};
    return can_go_pos(world, trans);
}

bool can_go_west(World& world){
//      
    assert(true);
//                                           

    Pos trans = {-1, 0};
    return can_go_pos(world, trans);
}

void go_pos(World& world, Pos trans){
//      
    assert(true);
/*       
                                         
             
             
              
              
              
              
                                      
                                              
*/
    Pos worker = find_worker(world);
    char w = world[worker.y][worker.x];
    Pos next = find_next(worker, trans);
    char n = world[next.y][next.x];

    if(w == 'w')
        world[worker.y][worker.x] = ' ';
    else //         
        world[worker.y][worker.x] = '.';

    if(n == ' ' || n == 'b')
        world[next.y][next.x] = 'w';
    else //                     
        world[next.y][next.x] = 'W';

    if(n == 'b' || n == 'B'){
        Pos next2 = find_next(next, trans);
        char nn = world[next2.y][next2.x];
        if(nn == ' ')
            world[next2.y][next2.x] = 'b';
        else //          
            world[next2.y][next2.x] = 'B';
    }
}

void go_north(World& world){
//                                 
    assert(can_go_north(world));
//                                                

    Pos trans = {0, -1};
    go_pos(world, trans);
}

void go_east(World& world){
//                                
    assert(can_go_east(world));
//                                               

    Pos trans = {1, 0};
    go_pos(world, trans);
}

void go_south(World& world){
//                                 
    assert(can_go_south(world));
//                                                

    Pos trans = {0, 1};
    go_pos(world, trans);
}

void go_west(World& world){
//                                
    assert(can_go_west(world));
//                                               

    Pos trans = {-1, 0};
    go_pos(world, trans);
}

bool candidate_present(vector<Candidate>& frontier, World& world){
//      
    assert(true);
//                                                                     

    for(int i = 0; i < frontier.size(); i++){
        if(frontier[i].world == world)
            return true;
    }
    return false;
}

bool tries(vector<Candidate>& frontier, Candidate& c){
//      
    assert(true);
//                                              

    if(!candidate_present(frontier, c.world)){
        frontier.push_back(c);
        if(final_state(c.world))
            return true;
    }

    return false;
}

Candidate breadth_first_search(World& world){
//      
    assert(true);
//                                                        

    vector<Candidate> frontier = {{world, 0}};

    while(true){
        Candidate c = frontier[0];
        c.depth++;
        frontier.erase(frontier.begin());

        if(can_go_north(c.world)){
            Candidate newc = c;
            go_north(newc.world);
            if(tries(frontier, newc))
                return newc;
        }
        if(can_go_east(c.world)){
            Candidate newc = c;
            go_east(newc.world);
            if(tries(frontier, newc))
                return newc;
        }
        if(can_go_south(c.world)){
            Candidate newc = c;
            go_south(newc.world);
            if(tries(frontier, newc))
                return newc;
        }
        if(can_go_west(c.world)){
            Candidate newc = c;
            go_west(newc.world);
            if(tries(frontier, newc))
                return newc;
        }
    }
}

bool candidate_present_and_worse(vector<Candidate>& tried, Candidate& attempt){
//      
    assert(true);
//                                                                                                        

    for(int i = 0; i < tried.size(); i++){
        if(tried[i].world == attempt.world && tried[i].depth < attempt.depth)
            return true;
    }
    return false;
}

void depth_first_search(vector<Candidate>& tried, Candidate& shortest, Candidate attempt, const int& BOUND){
//                 
    assert(BOUND > 0);
//                                                                     

    if(candidate_present_and_worse(tried, attempt))
        return;
    else
        tried.push_back(attempt);

    if(BOUND < attempt.depth || shortest.depth < attempt.depth)
        return;
    if(final_state(attempt.world) && attempt.depth < shortest.depth){
        shortest = attempt;
        return;
    }

    Candidate temp = attempt;
    //                      

    if(can_go_north(attempt.world)){
        attempt.depth++;
        attempt.path.push_back('N');
        go_north(attempt.world);
        depth_first_search(tried, shortest, attempt, BOUND);
        attempt = temp;
    }
    if(can_go_east(attempt.world)){
        attempt.depth++;
        attempt.path.push_back('E');
        go_east(attempt.world);
        depth_first_search(tried, shortest, attempt, BOUND);
        attempt = temp;
    }
    if(can_go_south(attempt.world)){
        attempt.depth++;
        attempt.path.push_back('S');
        go_south(attempt.world);
        depth_first_search(tried, shortest, attempt, BOUND);
        attempt = temp;
    }
    if(can_go_west(attempt.world)){
        attempt.depth++;
        attempt.path.push_back('W');
        go_west(attempt.world);
        depth_first_search(tried, shortest, attempt, BOUND);
        attempt = temp;
    }
}

int main()
{
    World world;

    read_file("challenge.6.txt", world);
    print(world);

    //                    
    Candidate solution = breadth_first_search(world);
    cout << "BREADTH FIRST SEARCH: " << solution.depth << endl;

    //                   
    const int BOUND = 5;
    Candidate shortest = {world, BOUND + 1};
    Candidate attempt = {world, 0};
    vector<Candidate> tried;

    depth_first_search(tried, shortest, attempt, BOUND);
    cout << "DEPTH FIRST SEARCH: ";
    if(shortest.depth == BOUND)
        cout << shortest.depth << endl;
    else
        cout << "There are no solutions found." << endl;

    return 0;
}

