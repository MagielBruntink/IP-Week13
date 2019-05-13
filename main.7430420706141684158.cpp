#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;
/*
             

                            
                       
*/

enum Cell {Wall, Empty, Dest, Worker, Worker_dest, Box, Box_dest};

const char WALL = '*';
const char EMPTY = ' ';
const char DEST = '.';
const char WORKER = 'w';
const char WORKER_DEST = 'W';
const char BOX = 'b';
const char BOX_DEST = 'B';

struct Pos
{
    int row;
    int col;
};

struct Puzzle
{
    vector<vector<Cell>> sokoban;
    Pos worker;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

void show_cell (Puzzle puzzle, int i, int j)
{
    //              
    assert(i >= 0 && j >=0);
    //                                                                                                                      
    if(puzzle.sokoban[i][j] == Wall)
        cout << WALL;
    if(puzzle.sokoban[i][j] == Empty)
        cout << EMPTY;
    if(puzzle.sokoban[i][j] == Dest)
        cout << DEST;
    if(puzzle.sokoban[i][j] == Worker)
        cout << WORKER;
    if(puzzle.sokoban[i][j] == Worker_dest)
        cout << WORKER_DEST;
    if(puzzle.sokoban[i][j] == Box)
        cout << BOX;
    if(puzzle.sokoban[i][j] == Box_dest)
        cout << BOX_DEST;
}

void show_puzzle (Puzzle puzzle)
{
    //              
    assert(true);
    //                                                     
    int rows = puzzle.sokoban.size();
    int cols = puzzle.sokoban[0].size();
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            show_cell(puzzle, i, j);
        cout << "\n";
    }
}

bool puzzle_ready (Puzzle puzzle)
{
    //              
    assert(true);
    //                                                                  
    int rows = puzzle.sokoban.size();
    int cols = puzzle.sokoban[0].size();
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(puzzle.sokoban[i][j] == Box)
                return false;
        }
    }
    return true;
}

bool same_puzzle(Puzzle a, Puzzle b)
{
    //              
    assert(true);
    //                                                                              
    int row_a = a.sokoban.size();
    int col_a = a.sokoban[0].size();
    int row_b = b.sokoban.size();
    int col_b = b.sokoban[0].size();
    if(row_a != row_b || col_a != col_b)
        return false;
    for(int i = 0; i < row_a; i++)
    {
        for(int j = 0; j < col_a; j++)
        {
            if(a.sokoban[i][j] != b.sokoban[i][j])
                return false;
        }
    }
    return true;
}

bool puzzle_present(vector<Candidate>& c, Puzzle p)
{
    //              
    assert(true);
    //                                                                                                                     
    int length = c.size();
    for(int i = 0; i < length; i++)
    {
        if(same_puzzle(c[i].candidate, p))
            return true;
    }
    return false;
}

void show_path(vector<Candidate>& c, int i, int& nr_moves)
{
    //              
    assert(i >= 0);
    //                                                                                                                            
    //                                                                                
    if(c[i].parent_candidate == -1)
        show_puzzle(c[i].candidate);
    else
    {
        show_path(c, c[i].parent_candidate, nr_moves);
        nr_moves = nr_moves+1;
        show_puzzle(c[i].candidate);
    }
}

Pos north (Puzzle p)
{
    //              
    assert(true);
    //                                                                                    
    Pos north = {p.worker.row - 1, p.worker.col};
    return north;
}

Pos south (Puzzle p)
{
    //              
    assert(true);
    //                                                                                      
    Pos south = {p.worker.row + 1, p.worker.col};
    return south;
}

Pos east (Puzzle p)
{
    //              
    assert(true);
    //                                                                                           
    Pos east = {p.worker.row, p.worker.col + 1};
    return east;
}

Pos west (Puzzle p)
{
    //              
    assert(true);
    //                                                                                          
    Pos west = {p.worker.row, p.worker.col - 1};
    return west;
}

bool can_go_north(Puzzle p)
{
    //              
    assert(true);
    //                                                                                                                  
    //                                                                      
    int row = north(p).row;
    int col = north(p).col;
    if(p.sokoban[row][col] == Wall)
        return false;
    if(p.sokoban[row][col] == Box && (p.sokoban[row-1][col] == Wall || p.sokoban[row-1][col] == Box))
        return false;
    else
        return true;
}

bool can_go_south(Puzzle p)
{
    //              
    assert(true);
    //                                                                                                                    
    //                                                                          
    int row = south(p).row;
    int col = south(p).col;
    if(p.sokoban[row][col] == Wall)
        return false;
    if(p.sokoban[row][col] == Box && (p.sokoban[row+1][col] == Wall || p.sokoban[row+1][col] == Box))
        return false;
    else
        return true;
}

bool can_go_east(Puzzle p)
{
    //              
    assert(true);
    //                                                                                                                            
    //                                                                                          
    int row = east(p).row;
    int col = east(p).col;
    if(p.sokoban[row][col] == Wall)
        return false;
    if(p.sokoban[row][col] == Box && (p.sokoban[row][col+1] == Wall || p.sokoban[row][col+1] == Box))
        return false;
    else
        return true;
}

bool can_go_west(Puzzle p)
{
    //              
    assert(true);
    //                                                                                                                           
    //                                                                                        
    int row = west(p).row;
    int col = west(p).col;
    if(p.sokoban[row][col] == Wall)
        return false;
    if(p.sokoban[row][col] == Box && (p.sokoban[row][col-1] == Wall || p.sokoban[row][col-1] == Box))
        return false;
    else
        return true;
}

Puzzle move_worker (Puzzle p, Pos next)
{
    //              
    assert(true);
    //                                                                                                                      
    //                                                                                                                           
    //                
    int row = next.row;
    int col = next.col;
    int row_w = p.worker.row;
    int col_w = p.worker.col;
    int row_os = row - row_w;
    int col_os = col - col_w;
    Puzzle new_p = p;

    if(p.sokoban[row][col] == Empty)
        new_p.sokoban[row][col] = Worker;
    else if(p.sokoban[row][col] == Dest)
        new_p.sokoban[row][col] = Worker_dest;
    else if(p.sokoban[row][col] == Box)
    {
        if(p.sokoban[row + row_os][col + col_os] == Empty)
            new_p.sokoban[row + row_os][col + col_os] = Box;
        else if(p.sokoban[row + row_os][col + col_os] == Dest)
            new_p.sokoban[row + row_os][col + col_os] = Box_dest;
        new_p.sokoban[row][col] = Worker;
    }
    if(p.sokoban[row_w][col_w] == Worker)
        new_p.sokoban[row_w][col_w] = Empty;
    else if(p.sokoban[row_w][col_w] == Worker_dest)
        new_p.sokoban[row_w][col_w] = Dest;

    return new_p;
}

void tries_bf(vector<Candidate>& c, int i, Pos next)
{
    //              
    assert(i >= 0);
    //                                                                                                                  
    //                                  
    Puzzle p = c[i].candidate;
    Puzzle new_p = move_worker(p, next);
    Candidate new_c = {new_p, i};
    if(!puzzle_present(c, new_p))
        c.push_back(new_c);
}

void solve_bf(Puzzle start)
{
    //              
    assert(true);
    //                                                                                                                       
    //                                                                                                             
    vector<Candidate> c = {{start, -1}};
    int i = 0;
    while (i < c.size() && !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if(can_go_north(p))
            tries_bf(c, i, north(p));
        if(can_go_south(p))
            tries_bf(c, i, south(p));
        if(can_go_east(p))
            tries_bf(c, i, east(p));
        if(can_go_west(p))
            tries_bf(c, i, west(p));
        i = i+1;
    }
    if(i < c.size())
    {
        int nr_moves = 0;
        show_path(c, i, nr_moves);
        cout << "The least amount of moves needed to solve the puzzle is: " << nr_moves << "\n";
    }
    else
        cout << "After " << i << " tries, no solution was found...";
}

bool puzzle_present_df(Puzzle p, vector<Puzzle>& c)
{
    //              
    assert(true);
    //                                                                                                                  
    int length = c.size();
    for(int i = 0; i < length; i++)
    {
        if(same_puzzle(c[i], p))
            return true;
    }
    return false;
}

void show_solution(vector<Puzzle>& c)
{
    //              
    assert(true);
    //                                                                            
    int length = c.size();
    for(int i = 0; i < length; i++)
        show_puzzle(c[i]);
}

void tries_df(vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth);

void solve_df(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    //              
    assert(max_depth > 0);
    //                                                                                                                     
    //                       
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle p = attempt[CURRENT-1];
    if (BEST > 0 && CURRENT >= BEST)
        return;
    else if(CURRENT > max_depth+1)
        return;
    else if(puzzle_ready(p))
    {
        shortest = attempt;
        return;
    }
    else
    {
        if(can_go_north(p))
            tries_df(attempt, north(p), shortest, max_depth);
        if(can_go_south(p))
            tries_df(attempt, south(p), shortest, max_depth);
        if(can_go_east(p))
            tries_df(attempt, east(p), shortest, max_depth);
        if(can_go_west(p))
            tries_df(attempt, west(p), shortest, max_depth);
    }
}

void tries_df(vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth)
{
    //              
    assert(max_depth > 0);
    //                                                                                                                        
    //                                                                                                                       
    //                                                      
    Puzzle p = attempt[attempt.size()-1];
    Puzzle new_p = move_worker(p, next);
    if(!puzzle_present_df(new_p, attempt))
    {
        attempt.push_back(new_p);  //       
        solve_df(attempt, shortest, max_depth);
        attempt.pop_back();        //      
    }
}

int main()
{
    cout << "Hello world!" << endl;
    Puzzle start_0 = {{{Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall},
                       {Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall},
                       {Wall,Box_dest,Empty,Empty,Empty,Empty,Empty,Empty,Worker,Wall},
                       {Wall,Empty,Empty,Wall,Wall,Wall,Wall,Empty,Empty,Wall},
                       {Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall},
                       {Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall}}, {2,8}};
    Puzzle start_1a = {{{Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall},
                        {Wall, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Wall},
                        {Wall, Empty, Dest, Box, Worker, Empty, Empty, Empty, Empty, Wall},
                        {Wall, Empty, Empty, Wall, Wall, Wall, Wall, Empty, Empty, Wall},
                        {Wall, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Wall},
                        {Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall}}, {2,4}};
    Puzzle start_1b = {{{Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall},
                        {Wall, Empty, Empty, Worker, Empty, Empty, Empty, Empty, Empty, Wall},
                        {Wall, Empty, Empty, Box, Empty, Empty, Empty, Empty, Empty, Wall},
                        {Wall, Empty, Empty, Dest, Empty, Empty, Empty, Empty, Empty, Wall},
                        {Wall, Empty, Empty, Wall, Wall, Wall, Wall, Empty, Empty, Wall},
                        {Wall, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Wall},
                        {Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall}}, {1,3}};
    Puzzle start_23 = {{{Wall, Wall, Wall, Wall, Wall, Wall, Wall},
                        {Wall, Worker, Empty, Empty, Empty, Wall, Wall},
                        {Wall, Empty, Box, Box, Empty, Empty, Wall},
                        {Wall, Empty, Wall, Dest, Empty, Dest, Wall},
                        {Wall, Empty, Empty, Empty, Empty, Empty, Wall},
                        {Wall, Wall, Wall, Wall, Wall, Wall, Wall}}, {1,1}};
    Puzzle start_25 = {{{Wall, Wall, Wall, Wall, Wall, Wall, Wall},
                        {Wall, Wall, Worker, Empty, Empty, Wall, Wall},
                        {Wall, Empty, Empty, Wall, Empty, Empty, Wall},
                        {Wall, Empty, Box, Box_dest, Box, Empty, Wall},
                        {Wall, Empty, Empty, Dest, Empty, Empty, Wall},
                        {Wall, Wall, Empty, Dest, Empty, Wall, Wall},
                        {Wall, Wall, Wall, Wall, Wall, Wall, Wall}}, {1,2}};
    Puzzle start_31 = {{{Wall, Wall, Wall, Wall, Wall, Wall, Wall},
                        {Wall, Wall, Wall, Empty, Empty, Wall, Wall},
                        {Wall, Worker, Empty, Dest, Box, Wall, Wall},
                        {Wall, Empty, Empty, Empty, Box, Empty, Wall},
                        {Wall, Empty, Wall, Dest, Empty, Empty, Wall},
                        {Wall, Empty, Empty, Empty, Empty, Empty, Wall},
                        {Wall, Wall, Wall, Wall, Wall, Wall, Wall}}, {2,1}};
    Puzzle start_34 = {{{Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall},
                        {Wall, Wall, Wall, Empty, Empty, Empty, Wall, Wall},
                        {Wall, Dest, Worker, Box, Empty, Empty, Wall, Wall},
                        {Wall, Wall, Wall, Empty, Box, Dest, Wall, Wall},
                        {Wall, Dest, Wall, Wall, Box, Empty, Wall, Wall},
                        {Wall, Empty, Wall, Empty, Dest, Empty, Wall, Wall},
                        {Wall, Box, Empty, Box_dest, Box, Box, Dest, Wall},
                        {Wall, Empty, Empty, Empty, Dest, Empty, Empty, Wall},
                        {Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall}}, {2,2}};
    //              
    solve_bf(start_1b);

    //            
    vector<Puzzle> attempt = {start_1b};
    vector<Puzzle> shortest;
    int max_depth = 1;
    solve_df(attempt, shortest, max_depth);
    show_solution(shortest);
    cout << "The least number of moves needed to solve the puzzle is: " << shortest.size()-1;
    return 0;
}

/*
                                                                
                  
                  
                  
                                                                               
                                                      
*/

/*
                                                                           
                                                                                   
                                                                                       
                                                                               
                                                                                   
                                                                                    
                                                                                     
                                                                                             
                                                                                           
                                                                                         
                                                                                             
                                                                                              
                                                                                     
                                                                                              
                                                                                           
                                                                                            
                                                                                         
                                                                                             
                                                                                              
                                                                   
                                                                        
                                                                    
                                                                     
                                                                        
                                                                            
                                                                   
                                                                       
                                                                       
                                                                       
                                                                       
                                                                     
                                                                            
                                                                   
                                                                     
                                                                     
                                                                      
                                                                      
                                                                        
                                                                            
                                                                         
                                                                            
                                                                            
                                                                         
                                                                         
                                                                            
                                                                           
                                                                              
                                                                                  
*/

