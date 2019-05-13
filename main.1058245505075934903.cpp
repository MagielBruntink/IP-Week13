/*
                               
                              
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

const int MAX_WIDTH = 30;
const int MAX_HEIGHT = 30;

enum Cell{wall, empty_cell, empty_destination, worker, worker_on_dest, box, box_on_dest};

struct Puzzle
{
    int width;
    int height;
    Cell board [MAX_WIDTH][MAX_HEIGHT];
    int worker_column;
    int worker_row;
};

struct Candidate
{
    Puzzle puzzle;
    int parent_candidate;
};

bool operator==(const Puzzle& a, const Puzzle& b)
{
    //         
    assert(true);
    //          
    //                                         
    if(a.width!=b.width||a.height!=b.height)
        return false;
    for(int j=0; j<a.height; j++)
        for(int i=0; i<a.width; i++)
            if(a.board[j][i]!=b.board[j][i])
                return false;
    return true;
}

void read_board(Puzzle& puzzle, string filename)
{
    //        
    assert(true);
    //         
    //                                    
    //                                 
    //                                                                          
    //                                                                             
    ifstream inputfile;
    inputfile.open(filename);
    if(!inputfile.is_open())
    {
        cout << "File couldn't be opened.\n";
        return;
    }
    char c;
    int i=0;
    int j=0;
    inputfile.get(c);
    while(inputfile)
    {
        if(c=='\n')
        {
            puzzle.width = i;
            i=-1;//                                           
            j++;
        }
        else if(c=='*')
            puzzle.board[j][i] = wall;
        else if(c==' ')
            puzzle.board[j][i] = empty_cell;
        else if(c=='.')
            puzzle.board[j][i] = empty_destination;
        else if(c=='w')
        {
            puzzle.board[j][i] = worker;
            puzzle.worker_column = i;
            puzzle.worker_row = j;
        }
        else if(c=='W')
        {
            puzzle.board[j][i] = worker_on_dest;
            puzzle.worker_column = i;
            puzzle.worker_row = j;
        }
        else if(c=='b')
            puzzle.board[j][i] = box;
        else if(c=='B')
            puzzle.board[j][i] = box_on_dest;
        else
        {
            cout << "The file doesn't have the proper form.\n";
            return;
        }
        i++;
        inputfile.get(c);
    }
    puzzle.height = j;//                                        
}

void display_board(Puzzle& puzzle)
{
    //         
    assert(puzzle.width>=0 && puzzle.height>=0&&puzzle.width <=MAX_WIDTH&& puzzle.height<=MAX_HEIGHT);
    //          
    //                                              
    cout << "Displaying board:\n";
    for(int j=0; j <puzzle.height; j++)
    {
        for(int i=0;i<puzzle.width; i++)
        {
            switch(puzzle.board[j][i])
            {
                case wall:              cout << '*';break;
                case empty_cell:        cout << ' '; break;
                case empty_destination: cout << '.'; break;
                case worker:            cout << 'w'; break;
                case worker_on_dest:    cout << 'W'; break;
                case box:               cout << 'b'; break;
                case box_on_dest:       cout << 'B'; break;
            }
        }
        cout << endl;
    }
}

bool puzzle_ready(Puzzle puzzle)
{
    //         
    assert(puzzle.width>=0 && puzzle.height>=0&&puzzle.width <=MAX_WIDTH&& puzzle.height<=MAX_HEIGHT);
    //          
    //                                                                    
    for(int j=0; j<puzzle.height; j++)
        for(int i=0; i<puzzle.width; i++)
        {
            if(puzzle.board[j][i]==box)
                return false;
        }
    return true;
}

bool puzzle_present(vector<Candidate>& candidates,  Puzzle puzzle)
{
    //         
    assert(true);
    //          
    //                                                            
    //                                                 
    for(int i=0;i<candidates.size(); i++)
    {
        if(candidates[i].puzzle == puzzle)
            return true;
    }
    return false;
}

bool is_wall(Puzzle puzzle, int row, int column)
{
    //         
    assert( column>=0&&column<puzzle.width&&row>=0&&row<puzzle.height );
    //          
    //                                                         

    return( puzzle.board[row][column]==wall );
}

bool is_box(Puzzle& puzzle, int row, int column)
{
    //         
    assert(column>=0&&column<puzzle.height&&row>=0&&row<puzzle.width);
    //          
    //                                                        

    return( puzzle.board[row][column]==box||puzzle.board[row][column] == box_on_dest );
}

bool can_go_north(Puzzle& puzzle)
{
    //         
    assert(true);
    //          
    //                                                            
    int worker_row = puzzle.worker_row; //               
    int worker_column = puzzle. worker_column;

    if(worker_row<=0||is_wall(puzzle, worker_row-1, worker_column) )
        return false;
    if(is_box(puzzle, worker_row-1, worker_column))
        if( worker_row-1<=0 || is_wall(puzzle,worker_row-2, worker_column) || is_box(puzzle, worker_row-2,worker_column))
            return false;
    return true;
}

bool can_go_south(Puzzle& puzzle)
{
    //         
    assert(true);
    //          
    //                                                            
    int worker_row = puzzle.worker_row; //               
    int worker_column = puzzle. worker_column;

    if(worker_row>=puzzle.height-1||is_wall(puzzle, worker_row+1, worker_column) )
        return false;
    if(is_box(puzzle, worker_row+1, worker_column))
        if( worker_row+1==puzzle.height || is_wall(puzzle,worker_row+2, worker_column)|| is_box(puzzle, worker_row+2,worker_column))
            return false;
    return true;
}

bool can_go_east(Puzzle& puzzle)
{
    //         
    assert(true);
    //          
    //                                                           
    int worker_row = puzzle.worker_row; //               
    int worker_column = puzzle. worker_column;

    if(worker_column>=puzzle.width-1||is_wall(puzzle, worker_row, worker_column+1) )
        return false;
    if(is_box(puzzle, worker_row, worker_column+1))
        if( worker_column+1==puzzle.width || is_wall(puzzle,worker_row, worker_column+2)|| is_box(puzzle, worker_row,worker_column+2))
            return false;
    return true;
}

bool can_go_west(Puzzle& puzzle)
{
    //         
    assert(true);
    //          
    //                                                           
    int worker_row = puzzle.worker_row; //               
    int worker_column = puzzle. worker_column;

    if(worker_column<=0||is_wall(puzzle, worker_row, worker_column-1) )
        return false;
    if( is_box(puzzle, worker_row, worker_column-1) )
        if( worker_column-1<=0 || is_wall(puzzle,worker_row, worker_column-2)|| is_box(puzzle, worker_row,worker_column-2))
            return false;
    return true;
}

void remove_worker(Puzzle& puzzle)
{
    //         
    assert( puzzle.board[puzzle.worker_row][puzzle.worker_column]== worker||puzzle.board[puzzle.worker_row][puzzle.worker_column]== worker_on_dest );
    //          
    //                                                                      
    //                                                                       
    if(puzzle.board[puzzle.worker_row][puzzle.worker_column]== worker)
        puzzle.board[puzzle.worker_row][puzzle.worker_column] = empty_cell;
    else
        puzzle.board[puzzle.worker_row][puzzle.worker_column] = empty_destination;
}

void place_worker(Puzzle& puzzle,int row, int column)
{
    //         
    assert( !is_wall(puzzle, row, column) );
    //                                                           
    //                                                                       
    Cell c = puzzle.board[row][column];
    if(c==empty_cell||c==box)
        puzzle.board[row][column] = worker;
    else
        puzzle.board[row][column] = worker_on_dest;
}

void place_box(Puzzle& puzzle, int row, int column)
{
    //         
    assert(!is_wall(puzzle, row, column)&& !is_box(puzzle, row, column) );
    //                                                      
    Cell c = puzzle.board[row][column];
    if(c==empty_destination)
        puzzle.board[row][column] = box_on_dest;
    else
        puzzle.board[row][column] = box;
}

Puzzle move_north(Puzzle puzzle)
{
    //         
    assert(can_go_north(puzzle));
    //          
    //                                          
    int w_row = puzzle.worker_row;
    int w_col = puzzle.worker_column;
    remove_worker(puzzle);
    if(is_box(puzzle, w_row-1, w_col))
        place_box(puzzle, w_row-2, w_col);
    place_worker(puzzle, w_row-1, w_col);
    puzzle.worker_row -= 1;
    return puzzle;
}

Puzzle move_south(Puzzle puzzle)
{
    //         
    assert(can_go_south(puzzle));
    //          
    //                                          
    int w_row = puzzle.worker_row;
    int w_col = puzzle.worker_column;
    remove_worker(puzzle);
    if(is_box(puzzle, w_row+1, w_col))
        place_box(puzzle, w_row+2, w_col);
    place_worker(puzzle, w_row+1, w_col);
    puzzle.worker_row += 1;
    return puzzle;
}

Puzzle move_east(Puzzle puzzle)
{
    //         
    assert( can_go_east(puzzle) );
    //          
    //                                         
    int w_row = puzzle.worker_row;
    int w_col = puzzle.worker_column;
    remove_worker(puzzle);
    if(is_box(puzzle, w_row, w_col+1))
        place_box(puzzle, w_row, w_col+2);
    place_worker(puzzle, w_row, w_col+1);
    puzzle.worker_column += 1;
    return puzzle;
}

Puzzle move_west(Puzzle puzzle)
{
    //         
    assert( can_go_west(puzzle) );
    //          
    //                                         
    int w_row = puzzle.worker_row;
    int w_col = puzzle.worker_column;
    remove_worker(puzzle);
    if(is_box(puzzle, w_row, w_col-1))
        place_box(puzzle, w_row, w_col-2);
    place_worker(puzzle, w_row, w_col-1);
    puzzle.worker_column -= 1;
    return puzzle;
}

void tries (vector<Candidate>& candidates, int i, Puzzle new_puzzle)
{
    //         
    assert(true);
    //          
    //                                                        
    //                                                                        
    Candidate newc = {new_puzzle, i} ;
    if (!puzzle_present (candidates, new_puzzle))
        candidates.push_back (newc) ;
}

void show_path(vector<Candidate>& candidates, int i)
{
    //         
    assert(i<candidates.size()&&i>=0);
    //          
    //                                                                              
    //                                 

    vector<int> solution_backwards = {i};
    while(candidates[i].parent_candidate>=0)
    {
        i=candidates[i].parent_candidate;
        solution_backwards.push_back(i);
    }
    cout << "The step-by-step solution using BFS:\nStart:\n";
    for(int i = solution_backwards.size() - 1; i>=0;i--)
        display_board( candidates[solution_backwards[i]].puzzle );
    cout << "The number of moves using BFS was: " << solution_backwards.size()-1 << endl;
}

void find_solution_BFS(Puzzle start)
{
    //         
    assert(start.width>=0 && start.height>=0&&start.width <=MAX_WIDTH&& start.height<=MAX_HEIGHT);
    //          
    //                                                
    //                                                    
    //                                 

    vector<Candidate> candidates = {{start,-1}};

    Puzzle p;
    int i = 0;
    while (i < candidates.size() &&
                !puzzle_ready (candidates[i].puzzle))
    {
        p = candidates[i].puzzle ;
        if (can_go_north (p))   tries(candidates, i, move_north (p)) ;
        if (can_go_south (p))   tries(candidates, i, move_south (p)) ;
        if (can_go_west (p))    tries(candidates, i, move_west (p)) ;
        if (can_go_east (p))    tries(candidates, i, move_east (p)) ;
        i = i+1 ;
    }
    if(i<candidates.size() )
        show_path(candidates, i);
    else
        cout << "No solution found with BFS\n";
}

bool puzzle_present2(Puzzle puzzle, vector<Puzzle>& attempt)
{
    //         
    assert(true);
    //          
    //                                                         
    //                                                 
    for(int i=0;i<attempt.size(); i++)
    {
        if(attempt[i] == puzzle)
            return true;
    }
    return false;
}

void solve( vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void tries2( vector<Puzzle>& attempt, Puzzle new_p, vector<Puzzle>& shortest, int max_depth)
{
    //         
    assert(true);
    //          
    //                                                    
    //                                                                                      

    if (!puzzle_present2(new_p, attempt))
    {
        attempt.push_back(new_p) ; //        
        solve(attempt, shortest, max_depth) ;
        attempt.pop_back() ; //       
    }
}

void solve( vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    //         
    assert(true);
    //          
    //                                                                
    //                                                                                          
    //                                                                              
    const int CURRENT= attempt.size() ;
    const int BEST = shortest.size() ;
    Puzzle p = attempt[CURRENT-1] ;
    if(BEST > 0 && CURRENT>= BEST) { return; }
    else if(CURRENT> max_depth+1) { return; }
    else if( puzzle_ready(p) ) { shortest= attempt; return; }
    if(can_go_north(p)) tries2(attempt, move_north(p), shortest, max_depth) ;
    if(can_go_south(p)) tries2(attempt, move_south(p), shortest, max_depth) ;
    if(can_go_west(p))  tries2(attempt, move_west(p), shortest, max_depth) ;
    if(can_go_east(p))  tries2(attempt, move_east(p), shortest, max_depth) ;
}

void show_solution_DFS(vector<Puzzle>& shortest)
{
    //         
    assert(true);
    //          
    //                                                           

    cout << "The step-by-step solution using DFS:\nStart:\n";
    for(int i = 0; i<shortest.size();i++)
        display_board( shortest[i] );
    cout << "The number of moves using DFS was: " << shortest.size()-1 << endl;
}

void find_solution_DFS(Puzzle start, int max_depth)
{
    //         
    assert(true);
    //          
    //                                                                          
    //                                                                       
    //                                 

    vector<Puzzle> attempt;
    vector<Puzzle> shortest;
    attempt.push_back(start);

    solve( attempt, shortest, max_depth);

    if(shortest.size()>0)
        show_solution_DFS(shortest);
    else
        cout << "No solution found with DFS and max_depth=" << max_depth << endl;
}

int main()
{
    Puzzle puzzle;
    read_board(puzzle, "challenge.23.txt");
    cout << "Done reading.\n";
    cout << "puzzle width:" << puzzle.width<< " puzzle height:" << puzzle.height << endl;
//                          

    find_solution_BFS(puzzle);
    find_solution_DFS(puzzle, 25);

    return 0;
}

