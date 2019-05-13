#include <vector>
#include <iostream>
#include <cassert>

//                          
//                         

using namespace std;

enum Cell {Wall, Empty, EmptyDes, Worker, WorkerDes, Box, BoxDes};
enum Direction {North = 0, East = 1, South = 2, West = 3};
struct Pos {int row; int col;};
struct Puzzle {vector< vector<Cell> > puzzle; Pos pos;};
struct Candidate {Puzzle candidate; int parent_candidate;};

vector< vector<Cell> > start_puzzle =
                        {
							{ Wall, Wall, Wall, Wall, Wall, Wall, Wall },
							{ Wall, Worker, Empty, Empty, Empty, Wall, Wall },
							{ Wall, Empty, Box, Box, Empty, Empty, Wall },
							{ Wall, Empty, Wall, EmptyDes, Empty, EmptyDes, Wall },
							{ Wall, Empty, Empty, Empty, Empty, Empty, Wall },
							{ Wall, Wall, Wall, Wall, Wall, Wall, Wall }
						};

bool operator== (Puzzle& a, Puzzle& b)
{
    //    
    assert(true);
    //     
    //                                                             
    return a.puzzle == b.puzzle && a.pos.col == b.pos.col && a.pos.row == b.pos.row;
}

int cell_columns(vector<Cell>& a)
{
	//    
	assert(true);
	//     
	//                                                             
	return static_cast<int>(a.size());
}

int cell_rows(vector<vector<Cell>>& a)
{
    //    
	assert(true);
	//     
	//                                                                        
    return static_cast<int>(a.size());
}

int candidate_vector_size(vector<Candidate>& a)
{
    //    
	assert(true);
	//     
	//                                                                  
    return static_cast<int>(a.size());
}

int puzzle_size(vector<Puzzle>& a)
{
    //    
	assert(true);
	//     
	//                                                               
    return static_cast<int>(a.size());
}

const int COLUMNS = cell_columns(start_puzzle[0]);
const int ROWS = cell_rows(start_puzzle);

void show_puzzle(vector<vector<Cell>>& puzzle)
{
	//    
	assert(true);
	//     
	//               
	if(cell_rows(puzzle) <= 0){}
	else
    {
        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                switch(puzzle[i][j])
                {
                    case Wall: cout << '*'; break;
                    case Empty: cout << ' '; break;
                    case EmptyDes: cout << '.'; break;
                    case Worker: cout << 'w'; break;
                    case WorkerDes: cout << 'W'; break;
                    case Box: cout << 'b'; break;
                    case BoxDes: cout << 'B'; break;
                    default: cout << '?';
                }
            }
            cout << '\n';
        }
	}

}

bool in_front_of_wall(Puzzle puzzle, Direction dir)
{
    //    
    assert(true);
    //     
    //                                                                                 
    Pos position = puzzle.pos;
    switch(dir)
    {
    case North:
        if(puzzle.puzzle[position.row-1][position.col] == Wall)
            return true;
        else return false;
    case West:
        if(puzzle.puzzle[position.row][position.col-1] == Wall)
            return true;
        else return false;
    case East:
        if(puzzle.puzzle[position.row][position.col+1] == Wall)
            return true;
        else return false;
    case South:
        if(puzzle.puzzle[position.row+1][position.col] == Wall)
            return true;
        else return false;
    default: return false;
    }
}

bool box_on_des(Puzzle puzzle, Direction dir)
{
    //    
    assert(true);
    //     
    //                                                                                                      
    Pos position = puzzle.pos;
    switch(dir)
    {
    case North:
        if(puzzle.puzzle[position.row-1][position.col] == BoxDes)
            return true;
        else return false;
    case West:
        if(puzzle.puzzle[position.row][position.col-1] == BoxDes)
            return true;
        else return false;
    case East:
        if(puzzle.puzzle[position.row][position.col+1] == BoxDes)
            return true;
        else return false;
    case South:
        if(puzzle.puzzle[position.row+1][position.col] == BoxDes)
            return true;
        else return false;
    default: return false;
    }
}

bool in_front_of_box(Puzzle puzzle, Direction dir)
{
    //    
    assert(true);
    //    
    //                                                                             
    Pos position = puzzle.pos;
    switch(dir)
    {
    case North:
        if(puzzle.puzzle[position.row-1][position.col] == Box)
            return true;
        else return false;
    case West:
        if(puzzle.puzzle[position.row][position.col-1] == Box)
            return true;
        else return false;
    case East:
        if(puzzle.puzzle[position.row][position.col+1] == Box)
            return true;
        else return false;
    case South:
        if(puzzle.puzzle[position.row+1][position.col] == Box)
            return true;
        else return false;
    default: return false;
    }
}

bool multiple_obstacles(Puzzle puzzle, Direction dir)
{
    //    
    assert(true);
    //     
    //                                                                                                 
    //                                               
    if(in_front_of_box(puzzle, dir))
    {
        //                   
        Pos position = puzzle.pos;
        switch(dir)
        {
        case North:
            if  (
                   puzzle.puzzle[position.row-2][position.col] == Box ||
                   puzzle.puzzle[position.row-2][position.col] == BoxDes ||
                   puzzle.puzzle[position.row-2][position.col] == Wall
                )
                return true;
            else return false;
        case West:
            if  (
                   puzzle.puzzle[position.row][position.col-2] == Box ||
                   puzzle.puzzle[position.row][position.col-2] == BoxDes ||
                   puzzle.puzzle[position.row][position.col-2] == Wall
                )
                return true;
            else return false;
        case East:
            if  (
                   puzzle.puzzle[position.row][position.col+2] == Box ||
                   puzzle.puzzle[position.row][position.col+2] == BoxDes ||
                   puzzle.puzzle[position.row][position.col+2] == Wall
                )
                return true;
            else return false;
        case South:
            if  (
                   puzzle.puzzle[position.row+2][position.col] == Box ||
                   puzzle.puzzle[position.row+2][position.col] == BoxDes ||
                   puzzle.puzzle[position.row+2][position.col] == Wall
                )
                return true;
            else return false;
        default: return false;
        }
    }
    return false;
}

bool move_possible(Puzzle puzzle, Direction dir)
{
    //    
    assert(true);
    //     
    //                                                                        
    if(in_front_of_wall(puzzle, dir))
        return false;
    else if(box_on_des(puzzle, dir))
        return false;
    else if(multiple_obstacles(puzzle, dir))
        return false;
    else return true;
}

Pos direction(Direction dir)
{
    //    
    assert(static_cast<int>(dir) < 4);
    //     
    //                                                     
    switch(dir)
    {
    case North:
        return {-1,0};
    case East:
        return {0,1};
    case West:
        return {0,-1};
    case South:
        return {1,0};
    }
}

Puzzle swap(Puzzle current, Pos next)
{
    //    
    assert(cell_rows(current.puzzle) > 0);
    //     
    //                                                                                          
    //                                                                                     
    Pos pos = current.pos;
    Cell from = current.puzzle[pos.row][pos.col];
    Cell to = current.puzzle[pos.row+next.row][pos.col+next.col];
    if(from == WorkerDes)
        current.puzzle[pos.row][pos.col] = EmptyDes;
    else
        current.puzzle[pos.row][pos.col] = Empty;
    if(to == EmptyDes)
        current.puzzle[pos.row+next.row][pos.col+next.col] = WorkerDes;
    else
        current.puzzle[pos.row+next.row][pos.col+next.col] = Worker;
    current.pos = {current.pos.row+next.row, current.pos.col+next.col};
    return current;
}

Puzzle push(Puzzle current, Pos next)
{
    //    
    assert(cell_rows(current.puzzle) > 0);
    //     
    //                                                                                                 
    //                                                                                                       
    //              
    Pos worker = current.pos;
    Pos box = {worker.row+next.row, worker.col+next.col};
    Pos destination = {worker.row+(next.row*2),worker.col+(next.col*2)};
    Cell to = current.puzzle[destination.row][destination.col];
    if(to == EmptyDes)
            current.puzzle[destination.row][destination.col] = BoxDes;
    else
        current.puzzle[destination.row][destination.col] = Box;
    current.puzzle[box.row][box.col] = Empty;
    return swap(current, next);
}

bool puzzle_present(vector<Candidate>& c, Puzzle newp)
{
    //    
    assert(true);
    //     
    //                                                                                                
    //                                       
    int c_size = candidate_vector_size(c);
    for(int i = 0; i < c_size; i++)
        if(c[i].candidate.puzzle == newp.puzzle)
            return true;
    return false;
}

void tries(vector<Candidate>& c, int i, Direction dir)
{
    //    
    assert(i >= 0);
    //     
    //                                                                                               
    //                            
    Pos next = direction(dir);
    Puzzle p = c[i].candidate;
    Puzzle newp;
    if(!in_front_of_box(c[i].candidate, dir))
        newp = swap(c[i].candidate, next);
    else
        newp = push(c[i].candidate, next);
    if(!puzzle_present(c, newp))
    {
        Candidate newc = {newp, i};
        c.push_back(newc);
    }
}

bool puzzle_ready(Puzzle p)
{
    //    
    assert(true);
    //     
    //                                                                                              
    //                                                                                           
    //                                                                                           
    //                 
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
            if(p.puzzle[i][j] == EmptyDes || p.puzzle[i][j] == WorkerDes)
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
    if(i<0){}
    else
    {
        show_path(c, c[i].parent_candidate);
        show_puzzle(c[i].candidate.puzzle);
    }
}

void solve_breadth(Puzzle puzzle)
{
    //    
    assert(true);
    //     
    //                                                                                                 
    //                                                                                  
    vector<Candidate> c = {{puzzle, -1}};
    int i = 0;
    while(i < candidate_vector_size(c) && !puzzle_ready(c[i].candidate))
    //                                                                                                   
    //                                         
    {
        Puzzle p = c[i].candidate;
        for(int j = 0; j < 4; j++)
                if(move_possible(p, static_cast<Direction>(j)))
                    tries(c, i, static_cast<Direction>(j));
        i++;
    }
    if(puzzle_ready(c[i].candidate))
        cout << "puzzle ready\n";
    if(i < candidate_vector_size(c))
        show_path(c,i);
}

bool puzzle_present(Puzzle newp, vector<Puzzle>& attempt)
{
    //    
    assert(true);
    //     
    //                                                                                    
    int attempt_size = puzzle_size(attempt);
    for(int i = 0; i < attempt_size; i++)
        if(newp == attempt[i])
            return true;
    return false;
}

void show_solution(vector<Puzzle>& solution)
{
    //    
    assert(true);
    //     
    //                                               
    int solution_size = puzzle_size(solution);
    for(int i = 0; i < solution_size; i++)
        show_puzzle(solution[i].puzzle);
}

void solve_depth(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
    //    
    assert(max_depth >= 0);
    //     
    //                                                                                                
    //                                                                                                  
    //                                                                        
    const int CURRENT = puzzle_size(attempt);
    const int BEST = puzzle_size(shortest);
    Puzzle p = attempt[CURRENT-1];
    if(BEST > 0 && CURRENT >= BEST)
        return;
    else if(CURRENT > max_depth+1)
        return;
    else if(puzzle_ready(p))
    {
        shortest = attempt;
        return;
    }
    for(int i = 0; i < 4; i++)
        if(move_possible(p, static_cast<Direction>(i)))
        /*                                                                                       
                                                                                              
                                                                                                              
                                                                                                   
        */
        {
            Pos next = direction(static_cast<Direction>(i));
            Puzzle newp;
            if(!in_front_of_box(p, static_cast<Direction>(i)))
                newp = swap(p, next);
            else
                newp = push(p, next);
            if(!puzzle_present(newp, attempt))
            {
                attempt.push_back(newp);
                solve_depth(attempt, shortest, max_depth);
                attempt.pop_back();
            }
        }
}

int main()
{
	Puzzle puzzle ={start_puzzle, {1,1}}; //                         
	vector<Puzzle> test = {puzzle};
	vector<Puzzle> best = {};
	int max_depth = 10; //                          
	solve_breadth(puzzle);
	solve_depth(test, best, max_depth);
	show_solution(best);
	return 0;
}

