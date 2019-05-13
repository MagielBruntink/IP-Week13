#include <iostream>
#include <vector>
#include <cassert>
//                                                              

using namespace std;

const char WALL = '*';
const char WORKER = 'w';
const char WDEST = 'W';
const char BOX = 'b';
const char BDEST = 'B';
const char EMPTY = ' ';
const char DEST = '.';
typedef char Cell;
typedef vector<vector<Cell>> Puzzle;

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

struct Pos
{
    int col, row;
};

struct Step
{
    Pos from,to;
} ;

int size( vector<Cell>& data )
{
    return static_cast<int>(data.size());
}

int size( Puzzle& data )
{
    return static_cast<int>(data.size());
}

int size( vector<Puzzle>& data )
{
    return static_cast<int>(data.size());
}

int size(vector<Candidate>& data)
{
    return static_cast<int>(data.size());
}

bool is_south_of_box(Puzzle& puzzle, Pos worker_pos)
{
    //    
    assert(worker_pos.col > 0 && worker_pos.row > 0);
    //     
    //                                                                    
    int r = worker_pos.row;
    int c = worker_pos.col;
    if(puzzle[c-1][r] == BOX || puzzle[c-1][r] == BDEST )
    {
        return true;
    }
    return false;
}

bool is_north_of_box(Puzzle& puzzle, Pos worker_pos)
{
    //    
    assert(worker_pos.col > 0 && worker_pos.row > 0);
    //     
    //                                                                    
    int r = worker_pos.row;
    int c = worker_pos.col;
    if(puzzle[c+1][r] == BOX || puzzle[c+1][r] == BDEST )
    {
        return true;
    }
    return false;
}

bool is_east_of_box(Puzzle& puzzle, Pos worker_pos)
{
    //    
    assert(worker_pos.col > 0 && worker_pos.row > 0);
    //     
    //                                                                   
    int r = worker_pos.row;
    int c = worker_pos.col;
    if(puzzle[c][r-1] == BOX || puzzle[c][r-1] == BDEST )
    {
        return true;
    }
    return false;
}

bool is_west_of_box(Puzzle& puzzle, Pos worker_pos)
{
    //    
    assert(worker_pos.col > 0 && worker_pos.row > 0);
    //     
    //                                                                   
    int r = worker_pos.row;
    int c = worker_pos.col;
    if(puzzle[c][r+1] == BOX || puzzle[c][r+1] == BDEST )
    {
        return true;
    }
    return false;
}

Pos find_worker(Puzzle& room)
{
    //    
    assert(true);
    //     
    //                                                  
    for(int r = 0; r < size(room); r++)
        for(int c = 0; c < size(room[0]); c++)
            if(room[r][c] == 'w' || room[r][c] == 'W')
                return {r,c};
}

void move_box_west(Puzzle& puzzle)
{
    //    
    assert(true);
    //     
    //                                                                  
    //                                                                    
    //                                      
    Pos wpos = find_worker(puzzle);

    if(puzzle[wpos.col][wpos.row - 2] == EMPTY)
        puzzle[wpos.col][wpos.row - 2] = BOX;
    else
        puzzle[wpos.col][wpos.row - 2] = BDEST;

    if(puzzle[wpos.col][wpos.row - 1] == BOX)
        puzzle[wpos.col][wpos.row - 1] = EMPTY;
    else
        puzzle[wpos.col][wpos.row - 1] = DEST;
}

void move_box_east(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                  
    //                                                                    
    //                                      
    Pos wpos = find_worker(puzzle);

    if(puzzle[wpos.col][wpos.row + 2] == EMPTY)
        puzzle[wpos.col][wpos.row + 2] = BOX;
    else
        puzzle[wpos.col][wpos.row + 2] = BDEST;

    if(puzzle[wpos.col][wpos.row + 1] == BOX)
        puzzle[wpos.col][wpos.row + 1] = EMPTY;
    else
        puzzle[wpos.col][wpos.row + 1] = DEST;
}

void move_box_south(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                  
    //                                                                     
    //                                      
    Pos wpos = find_worker(puzzle);

    if(puzzle[wpos.col + 2][wpos.row] == EMPTY)
        puzzle[wpos.col + 2][wpos.row] = BOX;
    else
        puzzle[wpos.col + 2][wpos.row] = BDEST;

    if(puzzle[wpos.col + 1][wpos.row] == BOX)
        puzzle[wpos.col + 1][wpos.row] = EMPTY;
    else
        puzzle[wpos.col + 1][wpos.row] = DEST;
}

void move_box_north(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                  
    //                                                                     
    //                                      
    Pos wpos = find_worker(puzzle);

    if(puzzle[wpos.col - 2][wpos.row] == EMPTY)
        puzzle[wpos.col - 2][wpos.row] = BOX;
    else
        puzzle[wpos.col - 2][wpos.row] = BDEST;

    if(puzzle[wpos.col - 1][wpos.row] == BOX)
        puzzle[wpos.col - 1][wpos.row] = EMPTY;
    else
        puzzle[wpos.col - 1][wpos.row] = DEST;
}

void move_worker_west(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                
    //                                                       
    //                                      
    Pos wpos = find_worker(puzzle);

    if(puzzle[wpos.col][wpos.row - 1] == EMPTY)
        puzzle[wpos.col][wpos.row - 1] = WORKER;
    else
        puzzle[wpos.col][wpos.row - 1] = WDEST;

    if(puzzle[wpos.col][wpos.row] == WORKER)
        puzzle[wpos.col][wpos.row] = EMPTY;
    else
        puzzle[wpos.col][wpos.row] = DEST;
}

void move_worker_east(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                
    //                                                       
    //                                      
    Pos wpos = find_worker(puzzle);

    if(puzzle[wpos.col][wpos.row + 1] == EMPTY)
        puzzle[wpos.col][wpos.row + 1] = WORKER;
    else
        puzzle[wpos.col][wpos.row + 1] = WDEST;

    if(puzzle[wpos.col][wpos.row] == WORKER)
        puzzle[wpos.col][wpos.row] = EMPTY;
    else
        puzzle[wpos.col][wpos.row] = DEST;
}

void move_worker_north(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                
    //                                                        
    //                                      
    Pos wpos = find_worker(puzzle);

    if(puzzle[wpos.col - 1][wpos.row] == EMPTY)
        puzzle[wpos.col - 1][wpos.row] = WORKER;
    else
        puzzle[wpos.col - 1][wpos.row] = WDEST;

    if(puzzle[wpos.col][wpos.row] == WORKER)
        puzzle[wpos.col][wpos.row] = EMPTY;
    else
        puzzle[wpos.col][wpos.row] = DEST;
}

void move_worker_south(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                
    //                                                        
    //                                      
    Pos wpos = find_worker(puzzle);

    if(puzzle[wpos.col + 1][wpos.row] == EMPTY)
        puzzle[wpos.col + 1][wpos.row] = WORKER;
    else
        puzzle[wpos.col + 1][wpos.row] = WDEST;

    if(puzzle[wpos.col][wpos.row] == WORKER)
        puzzle[wpos.col][wpos.row] = EMPTY;
    else
        puzzle[wpos.col][wpos.row] = DEST;
}

void go_north(Puzzle& puzzle)
{
    //    
    assert(true);
    //     
    //                                                                
    //                                                                
    //                                                                    
    //                      

    //               
    Pos worker_pos = find_worker(puzzle);

    //                                     
    if (is_south_of_box(puzzle, worker_pos))
        move_box_north(puzzle);

    move_worker_north(puzzle);
}

void go_south(Puzzle& puzzle)
{
    //    
    assert(true);
    //     
    //                                                                
    //                                                                
    //                                                                    
    //                      
    //               
    Pos worker_pos = find_worker(puzzle);

    //                                     
    if (is_north_of_box(puzzle, worker_pos))
        move_box_south(puzzle);

    move_worker_south(puzzle);
}

void go_east(Puzzle& puzzle)
{
    //    
    assert(true);
    //     
    //                                                                
    //                                                                
    //                                                                    
    //                      
    //               
    Pos worker_pos = find_worker(puzzle);

    //                                     
    if (is_west_of_box(puzzle, worker_pos))

        move_box_east(puzzle);

    move_worker_east(puzzle);
}

void go_west(Puzzle& puzzle)
{
    //    
    assert(true);
    //     
    //                                                                
    //                                                                
    //                                                                    
    //                      
    //               
    Pos worker_pos = find_worker(puzzle);

    //                                     
    if (is_east_of_box(puzzle, worker_pos))
        move_box_west(puzzle);

    move_worker_west(puzzle);
}

bool can_go_north(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                    
    //                                                
    Pos p = find_worker(puzzle);
    char tocell = puzzle[p.col-1][p.row];

    if(tocell == WALL)
        return false;

    if(tocell == EMPTY || tocell == DEST)
        return true;

    if((tocell == BOX  || tocell == BDEST) && (puzzle[p.col - 2][p.row] == EMPTY || puzzle[p.col - 2][p.row] == DEST))
        return true;

}

bool can_go_south(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                    
    //                                                
    Pos p = find_worker(puzzle);
    char tocell = puzzle[p.col + 1][p.row];
    if(tocell == WALL)
        return false;
    if(tocell == EMPTY || tocell == DEST)
        return true;
    if((tocell == BOX || tocell == BDEST) && (puzzle[p.col + 2][p.row] == EMPTY|| puzzle[p.col + 2][p.row] == DEST))
        return true;
}

bool can_go_west(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                    
    //                                                
    Pos p = find_worker(puzzle);
    char tocell = puzzle[p.col][p.row - 1];

    if(tocell == WALL)
        return false;
    if(tocell == EMPTY || tocell == DEST)
        return true;
    if((tocell == BOX || tocell == BDEST) && (puzzle[p.col][p.row - 2] == EMPTY || puzzle[p.col][p.row - 2] == DEST))
        return true;

}

bool can_go_east(Puzzle& puzzle)
{
     //    
    assert(true);
    //     
    //                                                                    
    //                                                
    Pos p = find_worker(puzzle);
    char tocell = puzzle[p.col][p.row +1];
    if(tocell == WALL)
        return false;
    if(tocell == EMPTY || tocell == DEST)
        return true;
    if((tocell == BOX || tocell == BDEST) && (puzzle[p.col][p.row + 2] == EMPTY || puzzle[p.col][p.row + 2] == DEST))
        return true;
}

void print_puzzle(Puzzle& room)
{
    //    
    assert(true);
    //     
    //                                    
    for(int r = 0; r < size(room); r++)
    {
        for(int c = 0; c < size(room[0]); c++)
        {
            cout << room[r][c];
        }
        cout << endl;
    }
    cout << endl;
}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle newp)
{
    //    
    assert(i > 0);
    //     
    //                                                                   
    //               
    while(i >= 0)
    {
        if(c[i].candidate == newp)
            return true;
        i = c[i].parent_candidate;
    }
    return false;
}

bool puzzle_present(Puzzle& newp, vector<Puzzle>& attempt)
{
    for(int i = 0; i < size(attempt); i++)
    {
        if(newp == attempt[i])
            return true;
    }
    return false;
}

bool puzzle_ready(Puzzle p)
{
     //    
    assert(true);
    //     
    //                                                                      
    //                              
    for(int r = 0; r < size(p); r++)
        for(int c = 0; c < size(p[0]); c++)
            if(p[r][c] == '.' || p[r][c] == 'W')
                return false;
    return true;
}

void show_path(vector<Candidate>& c, int i)
{
    //    
    assert(true);
    //     
    //                                                                 
    //          
    if(i < 0)
        print_puzzle(c[i].candidate);
    else
    {
        print_puzzle(c[i].candidate);
        show_path(c, c[i].parent_candidate);
    }
}

void solve_breadth_first(Puzzle& start)
{
    //    
    assert(true);
    //     
    //                                                               
    //                                                                      
    //                   
    vector<Candidate> c = {{start, -1}};
    int i = 0;
    while(i < size(c) && !puzzle_ready(c[i].candidate))
    {
        cout << size(c) << endl;
        Puzzle p = c[i].candidate;
        if(can_go_north(p))
        {
            //                                
            Puzzle newp = p;
            go_north(newp);
            //                                     
            if(!puzzle_present(c, i, newp))
            {
                Candidate newc = {newp, i};
                //                         
                c.push_back(newc);
            }
        }

        if(can_go_south(p))
        {
            Puzzle newp = p;
            go_south(newp);
            if(!puzzle_present(c, i, newp))
            {
                Candidate newc = {newp, i};
                c.push_back(newc);
            }

        }

        if(can_go_west(p))
        {
            Puzzle newp = p;
            go_west(newp);
            if(!puzzle_present(c, i, newp))
            {
                Candidate newc = {newp, i};
                c.push_back(newc);
            }

        }

        if(can_go_east(p))
        {
            Puzzle newp = p;
            go_south(newp);
            if(!puzzle_present(c, i, newp))
            {
                Candidate newc = {newp, i};
                c.push_back(newc);
            }

        }

        i++;
    }
    if(i<size(c)) show_path(c, i);
}

void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    //    
    assert(max_depth > 0);
    //     
    //                                                             
    //                                                                      
    //                                                                      
    //                          

    const int CURRENT = size(attempt);
    const int BEST = size(shortest);
    Puzzle p = attempt[CURRENT-1];
    if(BEST > 0 && CURRENT >= BEST) return;
    else if(CURRENT > max_depth+1) return;
    else if(puzzle_ready(p))
    {
        shortest = attempt;
        return;
    }
    if(can_go_north(p))
    {
        //                                
        Puzzle newp = p;
        go_north(newp);
        //                                 
        if(!puzzle_present(newp, attempt))
        {
            attempt.push_back(newp);//       
            solve_depth_first(attempt, shortest, max_depth);
            attempt.pop_back();//      
        }

    }

    if(can_go_south(p))
    {
        Puzzle newp = p;
        go_south(newp);
        if(!puzzle_present(newp, attempt))
        {
            attempt.push_back(newp);//       
            solve_depth_first(attempt, shortest, max_depth);
            attempt.pop_back();//      
        }
    }

    if(can_go_west(p))
    {
        Puzzle newp = p;
        go_west(newp);
        if(!puzzle_present(newp, attempt))
        {
            attempt.push_back(newp);//       
            solve_depth_first(attempt, shortest, max_depth);
            attempt.pop_back();//      
        }
    }

    if(can_go_east(p))
    {
        Puzzle newp = p;
        go_east(newp);
        if(!puzzle_present(newp, attempt))
        {
            attempt.push_back(newp);//       
            solve_depth_first(attempt, shortest, max_depth);
            attempt.pop_back();//      
        }
    }

}

int main()
{
    Puzzle room =               {   {'*','*','*','*','*','*','*','*','*','*'} ,
                                    {'*',' ',' ',' ',' ',' ','.',' ',' ','*'} ,
                                    {'*',' ',' ',' ',' ','.','b','b',' ','*'} ,
                                    {'*',' ',' ','*','*','*','*',' ','w','*'} ,
                                    {'*',' ',' ',' ',' ',' ',' ',' ','b','*'} ,
                                    {'*','*','*','*','*','*','*','*','.','*'} };
    vector<Puzzle> shortest;
    vector<Puzzle> attempt;
    attempt.push_back(room);
    solve_depth_first(attempt, shortest, 8);
    for(int i = 0; i< size(shortest); i++)
    {
        print_puzzle(shortest[i]);
    }

    return 0;

}

