//                                                 
//                                            

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
using namespace std;

const char WALL = '*';
const char EMPTYCELL = ' ';
const char EMPTYDESTINATION = '.';
const char WORKER = 'w';
const char WORKERDESTINATION = 'W';
const char BOX = 'b';
const char BOXDESTINATION = 'B';
const int MAX_FILENAME_LENGTH = 20;

bool enter_file(char filename[MAX_FILENAME_LENGTH])
{
    //            
    assert(true);
    //             
    //                                                                                                          
    //                                                                         

    cout << "Please enter the name of a file: ";

    bool break_out = false;

    int c = 0;
    char C;
    while (c < MAX_FILENAME_LENGTH && !break_out)
    {
        cin.get (C);
        if (C == '\n')
        {
            break_out = true;
            filename[c] = '\0';
            cout << "Filename successfully entered" << endl;
        }
        else
           filename[c] = C;
        c++;
    }

    return break_out;
}

bool read_file(ifstream& infile, vector<char>& puzzle)
{
    //            
    assert(infile.is_open());
    //             
    //                                                            

    char c;
    while (!infile.eof())
    {
        infile.get(c);
        switch(c)
        {
            case '\n': puzzle.push_back(c); break;
            case WALL: puzzle.push_back(c); break;
            case EMPTYCELL: puzzle.push_back(c); break;
            case EMPTYDESTINATION: puzzle.push_back(c); break;
            case WORKER: puzzle.push_back(c); break;
            case WORKERDESTINATION: puzzle.push_back(c); break;
            case BOX: puzzle.push_back(c); break;
            case BOXDESTINATION: puzzle.push_back(c); break;
            default: cout << "Unknown Character" << endl;
        }
    }
}

void show_puzzle(vector<char>& puzzle)
{
    //            
    assert(true);
    //             
    //                                          

    for (int i = 0; i < puzzle.size(); i++)
        cout << puzzle[i];
}

int width(vector<char>& puzzle, int& counter)
{
    //            
    assert(true);
    //             
    //                                                   

    counter = 0;

    for(int i = 0; puzzle[i] != '\n'; i++)
        counter++;

    counter++;
    return counter;
}

//                    
bool can_go_north(vector<char>& puzzle, int& counter)
{
    //            
    assert(counter > 0);
    //             
    //                                                                                               
    //                                                                                            

    for(int i = 0; i < puzzle.size(); i++)
    {
        if(puzzle[i] == WORKER || puzzle[i] == WORKERDESTINATION)
        {
            if(puzzle[i-counter] == WALL)
                return false;
            else if((puzzle[i-counter] == BOX || puzzle[i-counter] == BOXDESTINATION) && (puzzle[i-(2*counter)] == WALL || puzzle[i-(2*counter)] == BOX || puzzle[i-(2*counter)] == BOXDESTINATION))
                return false;
        }
    }
    return true;
}

bool can_go_east(vector<char>& puzzle)
{
    //            
    assert(true);
    //             
    //                                                                                              
    //                                                                                           

    for(int i = 0; i < puzzle.size(); i++)
    {
        if(puzzle[i] == WORKER || puzzle[i] == WORKERDESTINATION)
        {
            if(puzzle[i+1] == WALL)
                return false;
            else if((puzzle[i+1] == BOX || puzzle[i+1] == BOXDESTINATION) && (puzzle[i+2] == WALL || puzzle[i+2] == BOX || puzzle[i+2] == BOXDESTINATION))
                return false;
        }
    }
    return true;
}

bool can_go_south(vector<char>& puzzle, int& counter)
{
    //            
    assert(counter > 0);
    //             
    //                                                                                               
    //                                                                                            

    for(int i = 0; i < puzzle.size(); i++)
    {
        if(puzzle[i] == WORKER || puzzle[i] == WORKERDESTINATION)
        {
            if(puzzle[i+counter] == WALL)
                return false;
            else if((puzzle[i+counter] == BOX || puzzle[i+counter] == BOXDESTINATION) && (puzzle[i+(2*counter)] == WALL || puzzle[i+(2*counter)] == BOX || puzzle[i+(2*counter)] == BOXDESTINATION))
                return false;
        }
    }
    return true;
}

bool can_go_west(vector<char>& puzzle)
{
    //            
    assert(true);
    //             
    //                                                                                              
    //                                                                                           

    for(int i = 0; i < puzzle.size(); i++)
    {
        if(puzzle[i] == WORKER || puzzle[i] == WORKERDESTINATION)
        {
            if(puzzle[i-1] == WALL)
                return false;
            else if((puzzle[i-1] == BOX || puzzle[i-1] == BOXDESTINATION) && (puzzle[i-2] == WALL || puzzle[i-2] == BOX || puzzle[i-2] == BOXDESTINATION))
                return false;
        }
    }
    return true;
}

void north(vector<char>& puzzle, int& counter)
{
    //            
    assert(counter > 0 && can_go_north(puzzle, counter));
    //             
    //                                      

    for(int i = 0; i < puzzle.size(); i++)
    {
        if(puzzle[i] == WORKER && puzzle[i-counter] == BOX && puzzle[i-(2*counter)] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-counter] = WORKER;
            puzzle[i-(2*counter)] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-counter] == BOX && puzzle[i-(2*counter)] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-counter] = WORKER;
            puzzle[i-(2*counter)] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-counter] == BOX && puzzle[i-(2*counter)] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-counter] = WORKER;
            puzzle[i-(2*counter)] = BOX;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-counter] == BOX && puzzle[i-(2*counter)] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-counter] = WORKER;
            puzzle[i-(2*counter)] = BOX;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-counter] == BOXDESTINATION && puzzle[i-(2*counter)] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-counter] = WORKERDESTINATION;
            puzzle[i-(2*counter)] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-counter] == BOXDESTINATION && puzzle[i-(2*counter)] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-counter] = WORKERDESTINATION;
            puzzle[i-(2*counter)] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-counter] == BOXDESTINATION && puzzle[i-(2*counter)] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-counter] = WORKERDESTINATION;
            puzzle[i-(2*counter)] = BOX;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-counter] == BOXDESTINATION && puzzle[i-(2*counter)] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-counter] = WORKERDESTINATION;
            puzzle[i-(2*counter)] = BOX;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-counter] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-counter] = WORKERDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-counter] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-counter] = WORKER;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-counter] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-counter] = WORKERDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-counter] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-counter] = WORKER;
            return;
        }
    }
}

void east(vector<char>& puzzle)
{
    //            
    assert(can_go_east(puzzle));
    //             
    //                                     

    for(int i = 0; i < puzzle.size(); i++)
    {
        if(puzzle[i] == WORKER && puzzle[i+1] == BOX && puzzle[i+2] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+1] = WORKER;
            puzzle[i+2] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+1] == BOX && puzzle[i+2] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+1] = WORKER;
            puzzle[i+2] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+1] == BOX && puzzle[i+2] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+1] = WORKER;
            puzzle[i+2] = BOX;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+1] == BOX && puzzle[i+2] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+1] = WORKER;
            puzzle[i+2] = BOX;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+1] == BOXDESTINATION && puzzle[i+2] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+1] = WORKERDESTINATION;
            puzzle[i+2] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+1] == BOXDESTINATION && puzzle[i+2] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+1] = WORKERDESTINATION;
            puzzle[i+2] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+1] == BOXDESTINATION && puzzle[i+2] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+1] = WORKERDESTINATION;
            puzzle[i+2] = BOX;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+1] == BOXDESTINATION && puzzle[i+2] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+1] = WORKERDESTINATION;
            puzzle[i+2] = BOX;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+1] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+1] = WORKERDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+1] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+1] = WORKER;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+1] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+1] = WORKERDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+1] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+1] = WORKER;
            return;
        }
    }
}

void south(vector<char>& puzzle, int& counter)
{
    //            
    assert(counter > 0 && can_go_south(puzzle, counter));
    //             
    //                                      

    for(int i = 0; i < puzzle.size(); i++)
    {
        if(puzzle[i] == WORKER && puzzle[i+counter] == BOX && puzzle[i+(2*counter)] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+counter] = WORKER;
            puzzle[i+(2*counter)] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+counter] == BOX && puzzle[i+(2*counter)] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+counter] = WORKER;
            puzzle[i+(2*counter)] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+counter] == BOX && puzzle[i+(2*counter)] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+counter] = WORKER;
            puzzle[i+(2*counter)] = BOX;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+counter] == BOX && puzzle[i+(2*counter)] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+counter] = WORKER;
            puzzle[i+(2*counter)] = BOX;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+counter] == BOXDESTINATION && puzzle[i+(2*counter)] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+counter] = WORKERDESTINATION;
            puzzle[i+(2*counter)] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+counter] == BOXDESTINATION && puzzle[i+(2*counter)] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+counter] = WORKERDESTINATION;
            puzzle[i+(2*counter)] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+counter] == BOXDESTINATION && puzzle[i+(2*counter)] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+counter] = WORKERDESTINATION;
            puzzle[i+(2*counter)] = BOX;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+counter] == BOXDESTINATION && puzzle[i+(2*counter)] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+counter] = WORKERDESTINATION;
            puzzle[i+(2*counter)] = BOX;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+counter] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+counter] = WORKERDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i+counter] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i+counter] = WORKER;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+counter] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+counter] = WORKERDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i+counter] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i+counter] = WORKER;
            return;
        }
    }
}

void west(vector<char>& puzzle)
{
    //            
    assert(can_go_west(puzzle));
    //             
    //                                     

    for(int i = 0; i < puzzle.size(); i++)
    {
        if(puzzle[i] == WORKER && puzzle[i-1] == BOX && puzzle[i-2] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-1] = WORKER;
            puzzle[i-2] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-1] == BOX && puzzle[i-2] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-1] = WORKER;
            puzzle[i-2] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-1] == BOX && puzzle[i-2] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-1] = WORKER;
            puzzle[i-2] = BOX;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-1] == BOX && puzzle[i-2] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-1] = WORKER;
            puzzle[i-2] = BOX;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-1] == BOXDESTINATION && puzzle[i-2] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-1] = WORKERDESTINATION;
            puzzle[i-2] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-1] == BOXDESTINATION && puzzle[i-2] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-1] = WORKERDESTINATION;
            puzzle[i-2] = BOXDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-1] == BOXDESTINATION && puzzle[i-2] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-1] = WORKERDESTINATION;
            puzzle[i-2] = BOX;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-1] == BOXDESTINATION && puzzle[i-2] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-1] = WORKERDESTINATION;
            puzzle[i-2] = BOX;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-1] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-1] = WORKERDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKER && puzzle[i-1] == EMPTYCELL)
        {
            puzzle[i] = EMPTYCELL;
            puzzle[i-1] = WORKER;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-1] == EMPTYDESTINATION)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-1] = WORKERDESTINATION;
            return;
        }
        else if(puzzle[i] == WORKERDESTINATION && puzzle[i-1] == EMPTYCELL)
        {
            puzzle[i] = EMPTYDESTINATION;
            puzzle[i-1] = WORKER;
            return;
        }
    }
}

bool puzzle_ready(vector<char>& puzzle)
{
    //            
    assert(true);
    //             
    //                               

    for(int i = 0; i < puzzle.size(); i++)
    {
        if(puzzle[i] == BOX)
            return false;
    }
    return true;
}

struct Candidate
{
    vector<char> candidate;
    int parent_candidate;
};

bool puzzle_present1(vector<Candidate>& c, vector<char>& p)
{
    //            
    assert(true);
    //             
    //                                                          
    //                           

    for(int i = 0; i < c.size(); i++)
        if(c[i].candidate == p)
            return true;
    return false;
}

void show_path(vector<Candidate>& c, int i)
{
    //            
    assert(true);
    //             
    //                           
    //                                            

    if(i < 0)
        return;
    else
    {
        show_path(c, c[i].parent_candidate);
        show_puzzle(c[i].candidate);
    }
}

void tries_north1(vector<Candidate>& c, int i, int& counter)
{
    //            
    assert(counter > 0);
    //             
    //                                                                                                                    

    vector<char> p = c[i].candidate;
    north(p, counter);
    Candidate newc = {p, i};
    if(!puzzle_present1(c, p))
        c.push_back(newc);
}

void tries_east1(vector<Candidate>& c, int i)
{
    //            
    assert(true);
    //             
    //                                                                                                                   

    vector<char> p = c[i].candidate;
    east(p);
    Candidate newc = {p, i};
    if(!puzzle_present1(c, p))
        c.push_back(newc);
}

void tries_south1(vector<Candidate>& c, int i, int& counter)
{
    //            
    assert(counter > 0);
    //             
    //                                                                                                                    

    vector<char> p = c[i].candidate;
    south(p, counter);
    Candidate newc = {p, i};
    if(!puzzle_present1(c, p))
        c.push_back(newc);
}

void tries_west1(vector<Candidate>& c, int i)
{
    //            
    assert(true);
    //             
    //                                                                                                                   

    vector<char> p = c[i].candidate;
    west(p);
    Candidate newc = {p, i};
    if(!puzzle_present1(c, p))
        c.push_back(newc);
}

void solve1(vector<char>& puzzle, int& counter)
{
    //            
    assert(counter > 0);
    //             
    //                                                         

    vector<Candidate> c = {{puzzle, -1}};
    int i = 0;
    while (i < c.size() && !puzzle_ready(c[i].candidate))
    {
        vector<char> p = c[i].candidate;
        if(can_go_north(p, counter))
            tries_north1(c, i, counter);
        if(can_go_east(p))
            tries_east1(c, i);
        if(can_go_south(p, counter))
            tries_south1(c, i, counter);
        if(can_go_west(p))
            tries_west1(c, i);
        i++;
    }
    if(i < c.size())
        show_path(c, i);
    else
        cout << "No solution" << endl;
}

//                  
bool puzzle_present2(vector<char>& p, vector<vector<char>>& attempt)
{
    //            
    assert(true);
    //             
    //                                                                          
    //                           

    for(int i = 0; i < attempt.size(); i++)
        if(attempt[i] == p)
            return true;
    return false;
}

void solve2(vector<vector<char>>& attempt, vector<vector<char>>& shortest, int max_depth, int& counter);
//                             

void tries_north2(vector<vector<char>>& attempt, vector<vector<char>>& shortest, int max_depth, int& counter)
{
    //            
    assert(max_depth > 0 && counter > 0);
    //             
    //                                                                                                                                
    //                                                                                              

    vector<char> p = attempt[attempt.size()-1];
    north(p, counter);
    if(!puzzle_present2(p, attempt))
    {
        attempt.push_back(p);
        solve2(attempt, shortest, max_depth, counter);
        attempt.pop_back();
    }
}

void tries_east2(vector<vector<char>>& attempt, vector<vector<char>>& shortest, int max_depth, int& counter)
{
    //            
    assert(max_depth > 0 && counter > 0);
    //             
    //                                                                                                                               
    //                                                                                              

    vector<char> p = attempt[attempt.size()-1];
    east(p);
    if(!puzzle_present2(p, attempt))
    {
        attempt.push_back(p);
        solve2(attempt, shortest, max_depth, counter);
        attempt.pop_back();
    }
}

void tries_south2(vector<vector<char>>& attempt, vector<vector<char>>& shortest, int max_depth, int& counter)
{
    //            
    assert(max_depth > 0 && counter > 0);
    //             
    //                                                                                                                                
    //                                                                                              

    vector<char> p = attempt[attempt.size()-1];
    south(p, counter);
    if(!puzzle_present2(p, attempt))
    {
        attempt.push_back(p);
        solve2(attempt, shortest, max_depth, counter);
        attempt.pop_back();
    }
}

void tries_west2(vector<vector<char>>& attempt, vector<vector<char>>& shortest, int max_depth, int& counter)
{
    //            
    assert(max_depth > 0 && counter > 0);
    //             
    //                                                                                                                               
    //                                                                                              

    vector<char> p = attempt[attempt.size()-1];
    west(p);
    if(!puzzle_present2(p, attempt))
    {
        attempt.push_back(p);
        solve2(attempt, shortest, max_depth, counter);
        attempt.pop_back();
    }
}

void solve2(vector<vector<char>>& attempt, vector<vector<char>>& shortest, int max_depth, int& counter)
{
    //            
    assert(max_depth > 0 && counter > 0);
    //             
    //                                                       

    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    vector<char> p = attempt[CURRENT-1];

    if(BEST > 0 && CURRENT >= BEST)
        return;
    else if(CURRENT > max_depth+1)
        return;
    else if(puzzle_ready(p))
    {
        shortest = attempt;
        return;
    }

    if(can_go_north(p, counter))
        tries_north2(attempt, shortest, max_depth, counter);
    if(can_go_east(p))
        tries_east2(attempt, shortest, max_depth, counter);
    if(can_go_south(p, counter))
        tries_south2(attempt, shortest, max_depth, counter);
    if(can_go_west(p))
        tries_west2(attempt, shortest, max_depth, counter);
}

void show_solution(vector<vector<char>>& shortest)
{
    //            
    assert(true);
    //             
    //                                                                       

    for(int i = 0; i < shortest.size(); i++)
        show_puzzle(shortest[i]);
}

int main()
{
    //                                                                                       
    //                                                              

    char filename[MAX_FILENAME_LENGTH];
    enter_file(filename);
    ifstream file(filename);

    vector<char> puzzle;

    read_file(file, puzzle);
    show_puzzle(puzzle);

    int counter;
    width(puzzle, counter);

    vector<vector<char>> attempt ={puzzle};
    vector<vector<char>> shortest;

//                                           
//                            

    cout << "Depth-first search" << endl;
    solve2(attempt, shortest, 30, counter);
    show_solution(shortest);

    return 0;
}

