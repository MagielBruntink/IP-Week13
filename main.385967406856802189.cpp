/*                                        
                                    
                                    
                                     
                                        */

/*                                        

                            

                  
                        
                                    
                                     
                                          
                                  
                                       

                                                                          
                                                                           

                                   
                                      
                                      
                                        
       

                                                                      

                                        */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

/*                                        

                           

                                        */

/*
                                                
                                                           
                                                                        
                                                        
*/

    const int max_depth = 10;

    struct Pos
    {
        int col, row;
    };

    struct Puzzle
    {
        vector<vector<char>> puzzle;
        Pos worker;
    };

    struct Candidate
    {
        Puzzle candidate;
        int parent_candidate;
    };

    vector<vector<char>> puzzle;
    vector<char> current_puzzle;
    vector<Candidate> c;
    vector<Puzzle> attempt;
    vector<Puzzle> shortest;

    vector<vector<char>> grid            = {{'*','*','*','*','*','*','*','*','*','*'},
                                        {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                                        {'*',' ','.','b','w',' ',' ',' ',' ','*'},
                                        {'*',' ','*','*','*','*','*','*','*','*'},
                                        {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                                        {'*','*','*','*','*','*','*','*','*','*'}};

//                                                                                  
//                                                                                  
//                                                                                  
//                                                                                  
//                                                                                  
//                                                                                   

Puzzle original_puzzle = {grid, {2,4}}; //                   

/*                                        

                          

                                        */

Pos find_worker (Puzzle input_puzzle)
{
    /*                          */
            assert(true);
    /*                      
                                                                                 
                                                              */

    for (unsigned int x = 0; x < input_puzzle.puzzle.size(); x++)
    {
        for (unsigned int y = 0; y < input_puzzle.puzzle[x].size(); y++)
        {
            if (input_puzzle.puzzle[x][y] == 'w' || input_puzzle.puzzle[x][y] == 'W')
            {
                input_puzzle.worker.row = x;
                input_puzzle.worker.col = y;
            }
        }
    }
    return input_puzzle.worker;
}

/*                                        

                    

                                        */

/*              */
void show_puzzle (vector<vector<char>>& input_puzzle)
{
/*                     */
        assert(true);
/*                      
                                                                                   */
    cout << endl;
    for (unsigned int x = 0; x < input_puzzle.size(); x++)
    {
        for (unsigned int y = 0; y < input_puzzle[x].size(); y++)
            cout << input_puzzle[x][y];
        cout << endl;
    }
}

/*                                        

                              

                                        */

int number_of_destinations (vector<vector<char>> current_puzzle)
{   /*              */ assert(true);
    /*               
                                                              */
    int destinations = 0;
    for (unsigned int x = 0; x < current_puzzle.size(); x++)
    {
        for (unsigned int i = 0; i < current_puzzle[x].size(); i++)
            if (current_puzzle[x][i] == '.')
                destinations++;
    }
//                                                               
    return destinations;
}

int number_of_Bs (vector<vector<char>> current_puzzle)
{   /*              */ assert(true);
    /*               
                                              */
    int number_of_B = 0;
    for (unsigned int x = 0; x < current_puzzle.size(); x++)
    {
        for (unsigned int i = 0; i < current_puzzle[x].size(); i++)
            if (current_puzzle[x][i] == 'B')
                number_of_B++;
    }
//                                                    
    return number_of_B;
}

bool solution_found (vector<vector<char>> original_puzzle, vector<vector<char>>& current_puzzle)
{
    /*              */ assert (true);
    /*               
                                                                       
                                                            */
    if (number_of_destinations(original_puzzle) == number_of_Bs(current_puzzle))
    {
        cout << "A solution has been found!" << endl;
        show_puzzle(current_puzzle);
        return true;
    }
    else
    {
        cout << "Solution has not been found yet. " << endl;
        return false;
    }
}

/*                                        

                                  

                                        */

bool can_go_north (Puzzle p)
{
    /*              */
    /*               
                                                  */
    if (p.puzzle[p.worker.row-1][p.worker.col] == '*')
    {
        cout << "Cannot go north " << endl;
        return false;
    }
    if (p.puzzle[p.worker.row-1][p.worker.col] == 'b' && p.puzzle[p.worker.row-2][p.worker.col] == '*')
    {
        cout << "Cannot go north " << endl;
        return false;
    }
    else
    {
        cout << "Can go north " << endl;
        return true;
    }
}

bool can_go_east (Puzzle p)
{
    /*              */
    /*               
                                                      */
    if (p.puzzle[p.worker.row][p.worker.col+1] == '*')
    {
        cout << "Cannot go east " << endl;
        return false;
    }
    if (p.puzzle[p.worker.row][p.worker.col+1] == 'b' && p.puzzle[p.worker.row][p.worker.col+2] == '*')
    {
        cout << "Cannot go east " << endl;
        return false;
    }
    else
    {
        cout << "Can go east " << endl;
        return true;
    }
}

bool can_go_south (Puzzle p)
{
    /*              */
    /*               
                                                      */
    if (p.puzzle[p.worker.row+1][p.worker.col] == '*')
    {
        cout << "Cannot go south " << endl;
        return false;
    }
    if (p.puzzle[p.worker.row+1][p.worker.col] == 'b' && p.puzzle[p.worker.row+2][p.worker.col] == '*')
    {
        cout << "Cannot go south " << endl;
        return false;
    }
    else if (p.puzzle[p.worker.row+1][p.worker.col] != '*')
    {
        cout << "Can go south, position: " << p.puzzle[p.worker.row+1][p.worker.col] << endl;
        return true;
    }
}

bool can_go_west (Puzzle p)
{
    /*              */
    /*               
    */
   //                                                                                                   
    if (p.puzzle[p.worker.row][p.worker.col-1] == '*')
    {
        cout << "Cannot go west " << endl;
        return false;
    }
    if (p.puzzle[p.worker.row][p.worker.col-1] == 'b' && p.puzzle[p.worker.row][p.worker.col-2] == '*')
    {
        cout << "Cannot go west " << endl;
        return false;
    }
    else
    {
        cout << "Can go west " << endl;
        return true;
    }
}

Puzzle move_worker (Puzzle& p, int row_d, int col_d)
{
    /*              */ //                                                                                                              
    /*                */

//                                             
//                          
    if (p.puzzle[p.worker.row][p.worker.col] = 'w' && p.puzzle[p.worker.row + row_d][p.worker.col + col_d] == ' ')
    {
//                                                                                                                                                                
//                                                                                                                                                                                             
        p.puzzle[p.worker.row][p.worker.col] = ' ';
        p.puzzle[p.worker.row + row_d][p.worker.col + col_d] = 'w';
    }
    else if (p.puzzle[p.worker.row][p.worker.col] = 'w' && p.puzzle[p.worker.row + row_d][p.worker.col + col_d] == 'b' && p.puzzle[p.worker.row + row_d + row_d][p.worker.col + col_d +col_d] == '.')
    {
//                                                                                                                                                                 
//                                                                                                                                                                                              
        p.puzzle[p.worker.row][p.worker.col] = ' ';
        p.puzzle[p.worker.row + row_d][p.worker.col + col_d] = 'w';
        p.puzzle[p.worker.row + row_d + row_d][p.worker.col + col_d +col_d] = 'B';
    }
    else if (p.puzzle[p.worker.row][p.worker.col] = 'w' && p.puzzle[p.worker.row + row_d][p.worker.col + col_d] == 'b' && p.puzzle[p.worker.row + row_d + row_d][p.worker.col + col_d +col_d] == ' ')
    {
//                                                                                                                                                                
//                                                                                                                                                                                             

        p.puzzle[p.worker.row][p.worker.col] = ' ';
        p.puzzle[p.worker.row + row_d][p.worker.col + col_d] = 'w';
        p.puzzle[p.worker.row + row_d + row_d][p.worker.col + col_d +col_d] = 'b';
    }
//                                                                                                                                                               
//                                                                                                                                                                                            
//                                            
//                          
    return p;
}

bool compare_puzzle(vector<vector<char>> puzzle1, vector<vector<char>> puzzle2)
{
    /*               */ assert (true);
    /*                                                                                                  */
    for (unsigned int x = 0; x < puzzle1.size(); x++)
    {
        for (unsigned int y = 0; y < puzzle1[x].size(); y++)
        {
            if (puzzle1[x][y] != puzzle2[x][y])
                return false;
        }
    }
    return true;
}

bool puzzle_present (vector<Candidate>& c, vector<vector<char>>& new_puzzle)
{
    /*               */ assert(true);
    /*                */
    cout << "\n We are now testing if we have tested this candidate before. " << endl;
    for (unsigned int x = 0; x < c.size(); x++)
    {
        if (compare_puzzle(c[x].candidate.puzzle, new_puzzle))
            return true;
    }
}

bool tries (vector<Candidate>& c, Puzzle& p, int i, int row_d, int col_d)
{   /*                      */
    /*                */
//                                                        
    //                          
    Puzzle new_puzzle = move_worker(p, row_d, col_d);
    Candidate new_candidate = {new_puzzle, i};
    if (!puzzle_present (c, new_puzzle.puzzle))
        c.push_back(new_candidate);
    return (solution_found(original_puzzle.puzzle, new_puzzle.puzzle));
}

void solve_breadth (Puzzle& original_puzzle)
{
    /*              */ assert(true);
    /*                */
    cout << "Solving with breadth-first" << endl;
    vector<Candidate> c = {{original_puzzle, -1}};
    int i = 0;
    while (i < c.size() && !solution_found(original_puzzle.puzzle, c[i].candidate.puzzle))
    {
        Puzzle p = c[i].candidate;
        p.worker = find_worker(p);
//                                                                            
        if (can_go_north (p))
            if (tries (c, p, i, -1, 0))
                return;
        if (can_go_east (p))
            if (tries (c, p, i, 0, 1))
                return;
        if (can_go_south (p))
            if (tries (c, p, i, 1, 0))
                return;
        if (can_go_west (p))
            if (tries (c, p, i, 0, -1))
                return;
        i++;
        cout << "i is equal to " << i << endl;
    }
    if (i < c.size())
        show_puzzle(c[i].candidate.puzzle);
}

/*            */
void show_path (vector<char>&/*       */, int i)
{
/*                     */
        assert(true);
/*                      
                                                    */

}

/*                                        

                                

                                        */

bool puzzle_ready(Puzzle p)
{

}

bool puzzle_present_depth (Puzzle new_puzzle, vector<Puzzle>& attempt)
{
    /*               */ assert(true);
    /*                */
    cout << "\nWe are now testing if we have tested this candidate before. " << endl;
    for (unsigned int x = 0; x < attempt.size(); x++)
    {
        if (compare_puzzle(attempt[x].puzzle, new_puzzle.puzzle))
            return true;
    }
}

void tries_depth (vector<Puzzle>& attempt, int row_d, int col_d, vector<Puzzle>& shortest, int max_depth)
{
    /*              */
    /*               
    */
//                                         
//                                                    
//                                                   
//     
//                                                 
//                                                  
//                                          
//     
}

void solve_depth (vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    /*               */ //                                              
    /*                                                                                                                              
    */
    cout << "\n Solving with depth-first" << endl;
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
        cout << "Can worker go north? " << endl;
        Puzzle p = attempt[attempt.size()-1];
        vector<Puzzle> pu = {p};
        Puzzle new_puzzle = move_worker(p, -1, 0);
        if (!puzzle_present_depth(new_puzzle, attempt))
        {
            attempt.push_back(new_puzzle); //        
            solve_depth(pu, shortest, max_depth);
            attempt.pop_back();      //       
        }
    }
    if (can_go_east(p))
    {
        cout << "Can worker go east? " << endl;
        Puzzle p = attempt[attempt.size()-1];
        vector<Puzzle> pu = {p};
        Puzzle new_puzzle = move_worker(p, 0, 1);
        if (!puzzle_present_depth(new_puzzle, attempt))
        {
            attempt.push_back(new_puzzle); //        
            solve_depth(pu, shortest, max_depth);
            attempt.pop_back();      //       
        }
    }
    if (can_go_south(p))
    {
        cout << "Can worker go south? " << endl;
        Puzzle p = attempt[attempt.size()-1];
        vector<Puzzle> pu = {p};
        Puzzle new_puzzle = move_worker(p, 1, 0);
        if (!puzzle_present_depth(new_puzzle, attempt))
        {
            attempt.push_back(new_puzzle); //        
            solve_depth(pu, shortest, max_depth);
            attempt.pop_back();      //       
        }
    }
    if (can_go_west(p))
    {
        cout << "Can worker go west? " << endl;
        Puzzle p = attempt[attempt.size()-1];
        vector<Puzzle> pu = {p};
        Puzzle new_puzzle = move_worker(p, 0, -1);
        if (!puzzle_present_depth(new_puzzle, attempt))
        {
            attempt.push_back(new_puzzle); //        
            solve_depth(pu, shortest, max_depth);
            attempt.pop_back();      //       
        }
    }

//                                                         
//                                                                        
//                                                                         
//                                                                         
}

/*                                        

            

                                        */

int main()
{
   solve_breadth(original_puzzle);
   solve_depth(attempt, shortest, max_depth);

    return 0;

}

/*                                     

                                  

                                       

  
                                                                             
                         
       
                                                                     
                            
       
             */
//                                                                
// 
//                              
//                     
//                        
//                                                                                               
//
//                           
//                                               
//                        
//         
//                                                                   
//                         
//         
//                                         
//                                                                
//                           
//                                                                
//                    
// 

//                     
//                                                                                             
// 
//                              
//                                
//                   
//                                                                                                                  
//                                                               
//  
//                   
//                              
//        
//                              
//                   
//         
//                                                                                     
//                                
//         
//     
//                   
//                             
// 

