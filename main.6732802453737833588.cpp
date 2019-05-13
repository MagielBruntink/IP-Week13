//                          
//                    

#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 6;

int n;

struct Candidate
{
    vector<char> state;
    int parent_candidate;
};

vector<Candidate> candidates;

//                                                                     
void show_state(vector<char>& state, const int FIELD_WIDTH)
{
    //               
    assert(FIELD_WIDTH > 0);
    //                
    //                                     
    for (int i = 0; i < state.size(); i++)
    {
        cout << state[i];
        if ((i - (FIELD_WIDTH - 1)) % FIELD_WIDTH == 0 && i != 0) //                                
        {
            cout << '\n'; //            
        }
    }
}

bool puzzle_solved (vector<char>& state)
{
    //               
    assert(true);
    //                
    //                                                                                                                                   
    for (int i = 0; i < state.size(); i++)
    {
        if (state[i] == 'b')
            return false;
    }
    return true; //                                                                                       
}

int find_player(vector<char>& state)
{
    //               
    assert(true);
    //                
    //                                                                                                                                                       
    for (int i = 0; i < state.size(); i++)
    {
        if (state[i] == 'w' || state[i] == 'W')
            return i;
    }
    return -1; //                            
}

bool can_go_north(vector<char>& state, int pos_player)
{
    //               
    assert(pos_player >= 0 && pos_player < FIELD_WIDTH * FIELD_HEIGHT);
    //                
    //                                                                                                                  
    if (state[pos_player - FIELD_WIDTH] == ' ' || state[pos_player - FIELD_WIDTH] == '.') //                                       
        return true;
    else if ((state[pos_player - FIELD_WIDTH] == 'b' || state[pos_player - FIELD_WIDTH] == 'B') && (state[pos_player - 2 * FIELD_WIDTH] == '.' || state[pos_player - 2 * FIELD_WIDTH] == ' ')) //                                                                                       
        return true;
    else return false;

}

vector<Candidate> north(vector<Candidate>& candidates, int pos_player, int n) //                                                                 
{
    //               
    assert(can_go_north(candidates[n].state, find_player(candidates[n].state)));
    //                
    //                                                                                  
    switch(candidates[n].state[pos_player - FIELD_WIDTH])
    {
        //                                                            
        case ' ':
        candidates[n].state[pos_player - FIELD_WIDTH] = 'w';
        if (candidates[n].state[pos_player] == 'W')
            candidates[n].state[pos_player] = '.';
        else candidates[n].state[pos_player] = ' ';
        return candidates;
        break;

        case '.':
        candidates[n].state[pos_player - FIELD_WIDTH] = 'W';
        if (candidates[n].state[pos_player] == 'W')
            candidates[n].state[pos_player] = '.';
        else candidates[n].state[pos_player] = ' ';
        return candidates;
        break;
    }
    //                                                         
    switch(candidates[n].state[pos_player - 2 * FIELD_WIDTH])
    {
        case ' ':
        candidates[n].state[pos_player - 2 * FIELD_WIDTH] = 'b'; //                     
        if (candidates[n].state[pos_player - FIELD_WIDTH] == 'b') //                                                                                             
            candidates[n].state[pos_player - FIELD_WIDTH] = 'w';
        else candidates[n].state[pos_player - FIELD_WIDTH] = 'W';
        if (candidates[n].state[pos_player] == 'w') //                                                                                                    
            candidates[n].state[pos_player] = ' ';
        else candidates[n].state[pos_player] = '.';
        return candidates;
        break;

        case '.':
        candidates[n].state[pos_player - 2 * FIELD_WIDTH] = 'B'; //                     
        if (candidates[n].state[pos_player - FIELD_WIDTH] == 'b') //                                                                                             
            candidates[n].state[pos_player - FIELD_WIDTH] = 'w';
        else candidates[n].state[pos_player - FIELD_WIDTH] = 'W';
        if (candidates[n].state[pos_player] == 'w') //                                                                                                    
            candidates[n].state[pos_player] = ' ';
        else candidates[n].state[pos_player] = '.';
        return candidates;
        break;
    }

}

bool can_go_south(vector<char>& state, int pos_player)
{
    //               
    assert(pos_player >= 0 && pos_player < FIELD_WIDTH * FIELD_HEIGHT);
    //                
    //                                                                                                                  
    if (state[pos_player + FIELD_WIDTH] == ' ' || state[pos_player + FIELD_WIDTH] == '.') //                                       
        return true;
    else if ((state[pos_player + FIELD_WIDTH] == 'b' || state[pos_player + FIELD_WIDTH] == 'B') && (state[pos_player + 2 * FIELD_WIDTH] == '.' || state[pos_player + 2 * FIELD_WIDTH] == ' ')) //                                                                                       
        return true;
    else return false;

}

vector<Candidate> south(vector<Candidate>& candidates, int pos_player, int n) //                                                                 
{
    //               
    assert(can_go_south(candidates[n].state, find_player(candidates[n].state)));
    //                
    //                                                                                  
    switch(candidates[n].state[pos_player + FIELD_WIDTH])
    {
        //                                                            
        case ' ':
        candidates[n].state[pos_player + FIELD_WIDTH] = 'w';
        if (candidates[n].state[pos_player] == 'W')
            candidates[n].state[pos_player] = '.';
        else candidates[n].state[pos_player] = ' ';
        return candidates;
        break;

        case '.':
        candidates[n].state[pos_player + FIELD_WIDTH] = 'W';
        if (candidates[n].state[pos_player] == 'W')
            candidates[n].state[pos_player] = '.';
        else candidates[n].state[pos_player] = ' ';
        return candidates;
        break;
    }
    //                                                         
    switch(candidates[n].state[pos_player + 2 * FIELD_WIDTH])
    {
        case ' ':
        candidates[n].state[pos_player + 2 * FIELD_WIDTH] = 'b'; //                     
        if (candidates[n].state[pos_player + FIELD_WIDTH] == 'b') //                                                                                             
            candidates[n].state[pos_player + FIELD_WIDTH] = 'w';
        else candidates[n].state[pos_player + FIELD_WIDTH] = 'W';
        if (candidates[n].state[pos_player] == 'w') //                                                                                                    
            candidates[n].state[pos_player] = ' ';
        else candidates[n].state[pos_player] = '.';
        return candidates;
        break;

        case '.':
        candidates[n].state[pos_player + 2 * FIELD_WIDTH] = 'B'; //                     
        if (candidates[n].state[pos_player + FIELD_WIDTH] == 'b') //                                                                                             
            candidates[n].state[pos_player + FIELD_WIDTH] = 'w';
        else candidates[n].state[pos_player + FIELD_WIDTH] = 'W';
        if (candidates[n].state[pos_player] == 'w') //                                                                                                    
            candidates[n].state[pos_player] = ' ';
        else candidates[n].state[pos_player] = '.';
        return candidates;
        break;
    }

}

bool can_go_west(vector<char>& state, int pos_player)
{
    //               
    assert(pos_player >= 0 && pos_player < FIELD_WIDTH * FIELD_HEIGHT);
    //                
    //                                                                                                                                    
    if (state[pos_player - 1] == ' ' || state[pos_player - 1] == '.') //                                       
        return true;
    else if ((state[pos_player - 1] == 'b' || state[pos_player - 1] == 'B') && (state[pos_player - 2] == '.' || state[pos_player - 2] == ' ')) //                                                                                      
        return true;
    else return false;

}

vector<Candidate> west(vector<Candidate>& candidates, int pos_player, int n) //                                                                 
{
    //               
    assert(can_go_west(candidates[n].state, find_player(candidates[n].state)));
    //                
    //                                                                                 
    switch(candidates[n].state[pos_player - 1])
    {
        //                                                           
        case ' ':
        candidates[n].state[pos_player - 1] = 'w';
        if (candidates[n].state[pos_player] == 'W')
            candidates[n].state[pos_player] = '.';
        else candidates[n].state[pos_player] = ' ';
        return candidates;
        break;

        case '.':
        candidates[n].state[pos_player - 1] = 'W';
        if (candidates[n].state[pos_player] == 'W')
            candidates[n].state[pos_player] = '.';
        else candidates[n].state[pos_player] = ' ';
        return candidates;
        break;
    }
    //                                                         
    switch(candidates[n].state[pos_player - 2])
    {
        case ' ':
        candidates[n].state[pos_player - 2] = 'b'; //                     
        if (candidates[n].state[pos_player - 1] == 'b') //                                                                                             
            candidates[n].state[pos_player - 1] = 'w';
        else candidates[n].state[pos_player - 1] = 'W';
        if (candidates[n].state[pos_player] == 'w') //                                                                                                    
            candidates[n].state[pos_player] = ' ';
        else candidates[n].state[pos_player] = '.';
        return candidates;
        break;

        case '.':
        candidates[n].state[pos_player - 2] = 'B'; //                     
        if (candidates[n].state[pos_player - 1] == 'b') //                                                                                             
            candidates[n].state[pos_player - 1] = 'w';
        else candidates[n].state[pos_player - 1] = 'W';
        if (candidates[n].state[pos_player] == 'w') //                                                                                                    
            candidates[n].state[pos_player] = ' ';
        else candidates[n].state[pos_player] = '.';
        return candidates;
        break;
    }

}

bool can_go_east(vector<char>& state, int pos_player)
{
    //               
    assert(pos_player >= 0 && pos_player < FIELD_WIDTH * FIELD_HEIGHT);
    //                
    //                                                                                                                                       
    if (state[pos_player + 1] == ' ' || state[pos_player + 1] == '.') //                                       
        return true;
    else if ((state[pos_player + 1] == 'b' || state[pos_player + 1] == 'B') && (state[pos_player + 2] == '.' || state[pos_player + 2] == ' ')) //                                                                                      
        return true;
    else return false;

}

vector<Candidate> east(vector<Candidate>& candidates, int pos_player, int n) //                                                                 
{
    //               
    assert(can_go_east(candidates[n].state, find_player(candidates[n].state)));
    //                
    //                                                                                 
    switch(candidates[n].state[pos_player + 1])
    {
        //                                                           
        case ' ':
        candidates[n].state[pos_player + 1] = 'w';
        if (candidates[n].state[pos_player] == 'W')
            candidates[n].state[pos_player] = '.';
        else candidates[n].state[pos_player] = ' ';
        return candidates;
        break;

        case '.':
        candidates[n].state[pos_player + 1] = 'W';
        if (candidates[n].state[pos_player] == 'W')
            candidates[n].state[pos_player] = '.';
        else candidates[n].state[pos_player] = ' ';
        return candidates;
        break;
    }
    //                                                         
    switch(candidates[n].state[pos_player + 2])
    {
        case ' ':
        candidates[n].state[pos_player + 2] = 'b'; //                     
        if (candidates[n].state[pos_player + 1] == 'b') //                                                                                             
            candidates[n].state[pos_player + 1] = 'w';
        else candidates[n].state[pos_player + 1] = 'W';
        if (candidates[n].state[pos_player] == 'w') //                                                                                                    
            candidates[n].state[pos_player] = ' ';
        else candidates[n].state[pos_player] = '.';
        return candidates;
        break;

        case '.':
        candidates[n].state[pos_player + 2] = 'B'; //                     
        if (candidates[n].state[pos_player + 1] == 'b') //                                                                                             
            candidates[n].state[pos_player + 1] = 'w';
        else candidates[n].state[pos_player + 1] = 'W';
        if (candidates[n].state[pos_player] == 'w') //                                                                                                    
            candidates[n].state[pos_player] = ' ';
        else candidates[n].state[pos_player] = '.';
        return candidates;
        break;
    }

}

//                             
vector<Candidate> solve_breadth(vector<Candidate>& candidates, int pos_player, int n)
{
    //               

    //                
    //                                                                            
    int moves = 0;
    while (moves < candidates[n].state.size() && !puzzle_solved(candidates[n].state))
    {
        if (can_go_north(candidates[n].state, find_player(candidates[n].state)))
        {
            Candidate new_state;
            new_state.state = north(candidates, find_player(candidates[n].state), n);
            new_state.parent_candidate = n;
            candidates.push_back({new_state.state});
            moves += 1;
        }
    }
    if (puzzle_solved(candidates[n].state))
    {
        cout << "Puzzle solved succesfully in " << moves << " attempts." << endl;
        return candidates;
    }
    else
        cout << "Puzzle could not be solved in " << moves << "attempts." << endl;

}

int main()
{
    vector<char> challenge_0{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                             '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*',
                             '*', 'B', ' ', ' ', ' ', ' ', ' ', ' ', 'W', '*',
                             '*', ' ', ' ', '*', '*', '*', '*', ' ', ' ', '*',
                             '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*',
                             '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'};

    vector<char> challenge_1a{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                              '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*',
                              '*', ' ', '.', 'b', 'w', ' ', ' ', ' ', ' ', '*',
                              '*', ' ', ' ', '*', '*', '*', '*', ' ', ' ', '*',
                              '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*',
                              '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'};

    candidates.push_back({challenge_1a, -1}); //                                                                                                
    n = 0; //                    

    //            
    /*
                                                 
                                                       
                                                     
                                                                                       
                                                          
                                                 
                                                       
                                                          
                                                 
                                                                                       
                                                          
                                                 
                                                                                        
                                                           
                                                 
                                                                                        
                                                           
                                                 
    */

    solve_breadth(candidates, find_player(candidates[n].state), n);
    return -1;
}

