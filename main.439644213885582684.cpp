#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

//                             
//                        

/*                                                                  
 
                   
                          
                            
              
                 
     
                 
                          
                          
                                            
                                         
            
     
             
 */

const int width = 10;
const int length = 6;

vector<vector<char>> challenge {    {'*','*','*','*','*','*','*','*','*','*'},
    {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ','.',' ','w',' ',' ','b',' ','*'},
    {'*',' ','b','*','*','*','*',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ','.',' ',' ','*'},
    {'*','*','*','*','*','*','*','*','*','*'}};

struct pos
{
    int col;
    int row;
};

struct challenge_struct
{
    vector<vector<char>> challenge;
    pos poppetje;
};

struct candidate
{
    challenge_struct fectur;
    int parent_candidate;
};

void show_challenge (vector<vector<char>>& chal)
{
//               
    assert(true);
//                
//                                
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
            cout << chal [i][j];
        cout << endl;
    }
    return;
}

bool challenge_ready(challenge_struct p)
{
//               
    assert(true);
//                
//                                                              
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
            if (p.challenge [i][j] == '.' || p.challenge [i][j] == 'W')
                return false;
    }
    return true;
}

bool operator== (const challenge_struct& p1, const challenge_struct& p2)
{
//               
    assert(true);
//                
//                              
    return p1.challenge == p2.challenge;
}

bool challenge_present(vector<candidate>& c, challenge_struct p)
{
//               
    assert(true);
//                
//                                                                                      
    for (int i = 0; i < c.size(); i++)
    {
        if (p.challenge == c[i].fectur.challenge)
            return true;
    }
    return false;
}

bool challenge_present_2(vector<challenge_struct>& c, challenge_struct p)
{
//               
    assert(true);
//                
//                                                                                      
    for (int i = 0; i < c.size(); i++)
    {
        if (p.challenge == c[i].challenge)
            return true;
    }
    return false;
}

bool can_go_north (challenge_struct p)
{
//               
    assert(true);
//                
//                                                                    
    //                                                                                                                       

    if((p.challenge.at(p.poppetje.row-1).at(p.poppetje.col) == 'b' || p.challenge.at(p.poppetje.row-1).at(p.poppetje.col) == 'B'))
    {
        if(p.challenge.at(p.poppetje.row-2).at(p.poppetje.col) != '*')
        {
            return true;
        }
    }
    //                        
    if(p.challenge.at(p.poppetje.row-1).at(p.poppetje.col) != '*' && p.challenge.at(p.poppetje.row-1).at(p.poppetje.col) != 'b' && p.challenge.at(p.poppetje.row-1).at(p.poppetje.col) != 'B')
        return true;
    return false;
}

bool can_go_south(challenge_struct p)
{
//               
    assert(true);
//                
//                                                                    
    if((p.challenge.at(p.poppetje.row+1).at(p.poppetje.col) == 'b' || p.challenge.at(p.poppetje.row+1).at(p.poppetje.col) == 'B'))
    {
        if(p.challenge.at(p.poppetje.row+2).at(p.poppetje.col) != '*')
        {
            return true;
        }
    }
    //                        
    if(p.challenge.at(p.poppetje.row+1).at(p.poppetje.col) != '*' && p.challenge.at(p.poppetje.row+1).at(p.poppetje.col) != 'b' && p.challenge.at(p.poppetje.row+1).at(p.poppetje.col) != 'B')
        return true;
    return false;
}

bool can_go_west (challenge_struct p)
{
//               
    assert(true);
//                
//                                                                   
    if((p.challenge.at(p.poppetje.row).at(p.poppetje.col-1) == 'b' || p.challenge.at(p.poppetje.row).at(p.poppetje.col-1) == 'B'))
    {
        if(p.challenge.at(p.poppetje.row).at(p.poppetje.col-2) != '*')
        {
            return true;
        }
    }
    //                        
    if(p.challenge.at(p.poppetje.row).at(p.poppetje.col-1) != '*' && p.challenge.at(p.poppetje.row).at(p.poppetje.col-1) != 'b' && p.challenge.at(p.poppetje.row).at(p.poppetje.col-1) != 'B')
        return true;
    return false;
}

bool can_go_east (challenge_struct p)
{
//               
    assert(true);
//                
//                                                                   
    if((p.challenge.at(p.poppetje.row).at(p.poppetje.col+1) == 'b' || p.challenge.at(p.poppetje.row).at(p.poppetje.col+1) == 'B'))
    {
        if(p.challenge.at(p.poppetje.row).at(p.poppetje.col+2) != '*')
        {
            return true;
        }
    }
    //                        
    if(p.challenge.at(p.poppetje.row).at(p.poppetje.col+1) != '*' && p.challenge.at(p.poppetje.row).at(p.poppetje.col+1) != 'b' && p.challenge.at(p.poppetje.row).at(p.poppetje.col+1) != 'B')
        return true;
    return false;
}

pos north (challenge_struct p)
{
//               
    assert(true);
//                
//                                                             
    p.poppetje.row = p.poppetje.row - 1;
}

pos south (challenge_struct p)
{
//               
    assert(true);
//                
//                                                             
    p.poppetje.row = p.poppetje.row + 1;
}

pos west (challenge_struct p)
{
//               
    assert(true);
//                
//                                                            
    p.poppetje.col = p.poppetje.col - 1;
}

pos east (challenge_struct p)
{
//               
    assert(true);
//                
//                                                            
    p.poppetje.col = p.poppetje.col + 1;
}

challenge_struct move_empty(challenge_struct p, pos direction)
{
//               
    assert(true);
//                
//                                                                                                   
    //                                   
    //                                                      
    //                            

    pos new_worker_pos = {p.poppetje.col + direction.col, p.poppetje.row + direction.row};
    pos new_box_pos = {p.poppetje.col + 2 * direction.col, p.poppetje.row + 2 * direction.row};
    //                                                                
    //                                                          

    if((p.challenge[new_worker_pos.row][new_worker_pos.col]) == 'b')
    {
        p.challenge[new_worker_pos.row][new_worker_pos.col] = 'w';
        if (p.challenge[new_box_pos.row][new_box_pos.col] == '.')
            p.challenge[new_box_pos.row][new_box_pos.col] = 'B';
        else
            p.challenge[new_box_pos.row][new_box_pos.col] = 'b';
    }
    if((p.challenge[new_worker_pos.row][new_worker_pos.col]) == 'B')
    {
        p.challenge[new_worker_pos.row][new_worker_pos.col] = 'W';
        if (p.challenge[new_box_pos.row][new_box_pos.col] == '.')
            p.challenge[new_box_pos.row][new_box_pos.col] = 'B';
        else
            p.challenge[new_box_pos.row][new_box_pos.col] = 'b';
    }
    if((p.challenge[new_worker_pos.row][new_worker_pos.col]) == ' ')
    {
        p.challenge[new_worker_pos.row][new_worker_pos.col] = 'w';
    }
    if((p.challenge[new_worker_pos.row][new_worker_pos.col]) == '.')
    {
        p.challenge[new_worker_pos.row][new_worker_pos.col] = 'W';
    }
    if (p.challenge[p.poppetje.row][p.poppetje.col] == 'w')
    {
        p.challenge[p.poppetje.row][p.poppetje.col] = ' ';
    }
    if (p.challenge[p.poppetje.row][p.poppetje.col] == 'W')
    {
        p.challenge[p.poppetje.row][p.poppetje.col] = '.';
    }

    //                            

    p.poppetje = new_worker_pos;
    //                            
    //                                 
    return p;
}

void tries (vector<candidate>& c, int i, pos next)
{
//               
    assert(true);
//                
//                                                                                      
    challenge_struct p = c[i].fectur;
    challenge_struct newp = move_empty (p, next);
    candidate newc = {newp, i};
    if (!challenge_present(c, newp))
    {
        //                        
        c.push_back(newc);
    }
}

int show_path (vector<candidate>& c, int i, int counter)
{
//               
    assert(counter >= 0);
//                
//                                                                        
    if (i < 0)
    {
        counter--;
        return counter;
    }
    else
    {
        counter++;
        counter = show_path(c, c[i].parent_candidate, counter);
        show_challenge(c[i].fectur.challenge);
        return counter;
    }
}

void solve_BFS (challenge_struct start)
{
//               
    assert(true);
//                
//                                 
    //                            
    vector<candidate> c = {{start, -1}};
    int i = 0;
    while (i < c.size() && !challenge_ready(c[i].fectur))
    {
        //                          
        challenge_struct p = c[i].fectur;
        //                            
        //                       
        if (can_go_north(p))
        {
            //                               
            tries(c, i, {0, -1});
            //                              
        }
        if (can_go_south(p))
        {
            //                               
            tries(c, i, {0, 1});
            //                              
        }
        if (can_go_west(p))
        {
            //                              
            tries(c, i, {-1, 0});
            //                             
        }
        if (can_go_east(p))
        {
            //                              
            tries(c, i, {1, 0});
            //                             
        }
        //                        
        i++;
    }
    //                            
    if (i < c.size())
    {
        cout << "Solution:" << endl;
        cout << "Optimal solution is: " << show_path (c, i, 0) << " step(s) long." << endl;
    }
}
void solve_DFS(vector<challenge_struct>& attempt, vector<challenge_struct>& shortest, int max_depth);

void tries_DFS (vector<challenge_struct>& attempt, pos next, vector <challenge_struct>& shortest, int max_depth)
{
//               
    assert(max_depth >= 0);
//                
//                                                                                      
    challenge_struct p = attempt[attempt.size()-1];
    challenge_struct newp = move_empty(p, next);
    if (!challenge_present_2(attempt, newp))
    {
        attempt.push_back(newp);
        solve_DFS(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void solve_DFS(vector<challenge_struct>& attempt, vector<challenge_struct>& shortest, int max_depth)
{
//               
    assert(true);
//                
//                                 
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    challenge_struct p = attempt[CURRENT - 1];
    if (BEST > 0 && CURRENT >= BEST)
    {
        return;
    }
    else if (CURRENT > max_depth+1)
    {
        return;
    }
    else if (challenge_ready(p))
    {
        shortest = attempt;
        return;
    }
    if (can_go_north(p))
        tries_DFS(attempt, {0, -1}, shortest, max_depth);
    if(can_go_south(p))
        tries_DFS(attempt, {0, 1}, shortest, max_depth);
    if (can_go_west(p))
        tries_DFS(attempt, {-1, 0}, shortest, max_depth);
    if (can_go_east(p))
        tries_DFS(attempt, {1, 0}, shortest, max_depth);

}

int main()
{
    challenge_struct puzzle = challenge_struct();
    puzzle.challenge = challenge;
    puzzle.poppetje = {4,2};
    solve_BFS(puzzle);

    vector<challenge_struct> attempt = {puzzle};
    vector<challenge_struct> shortest;
    int max_depth = 50;
    solve_DFS(attempt, shortest, max_depth);
    for(int i = 0; i < shortest.size(); i++)
    {
        show_challenge(shortest.at(i).challenge);
    }
    cout << "Optimal path is: " << shortest.size() - 1 << " step(s) long." << endl;
    return 0;
}

