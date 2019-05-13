#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <vector>

//                                              
//                                               

using namespace std;

const int MAX_NR_ROWS = 10;
const int MAX_NR_COLUMNS = 10;

enum Cell {Wall=-1, Empty, Destination, Worker, WorkerDest, Box, BoxDest};
enum Direction {North, East, South, West};

struct Position
{
    int row;
    int column;
};

struct Board
{
    Cell board[MAX_NR_ROWS][MAX_NR_COLUMNS];
    Position worker_position;
    Position board_size;
};

struct Configuration
{
    Board puzzle;
    int parent;
};

void read_file(ifstream& infile)
{    //               
    assert (!infile.is_open());
    //                                                                     

    string filename;
    cout << "What's the name of the file?" << endl;
    cin >> filename;
    infile.open (filename.c_str());
    if (!infile.is_open())
        cout << "Opening file failed";
}

bool read_universe_file (ifstream& infile, Board& puzzle)
{
    //               
    assert (infile.is_open());
    //                                                  

    int row=0, column=0;
    char c;
    infile.get(c);
    while(infile)
    {
        while(c!='\r')
        {
            if (c=='*')
                puzzle.board[row][column]=Wall;
            else if (c==' ')
                puzzle.board[row][column]=Empty;
            else if (c=='.')
                puzzle.board[row][column]=Destination;
            else if (c=='w')
            {
                puzzle.board[row][column]=Worker;
                puzzle.worker_position.row=row;
                puzzle.worker_position.column=column;
            }

            else if (c=='W')
            {
                puzzle.board[row][column]=WorkerDest;
                puzzle.worker_position.row=row;
                puzzle.worker_position.column=column;
            }
            else if (c=='b')
                puzzle.board[row][column]=Box;
            else if (c=='B')
                puzzle.board[row][column]=BoxDest;
            else
            {
                cout << "There is an error in the input file" << endl;
                return false;
            }
            column++;
            infile.get(c);
        }
        infile.get(c);
        puzzle.board_size.column=column;
        row++;
        column=0;
        infile.get(c);
    }
    puzzle.board_size.row=row;

    return true;
}

void print_puzzle(Board puzzle)
{//             
    assert(true);
    //                                                
    for(int row=0; row<puzzle.board_size.row; row++)
    {
        for(int column=0; column<puzzle.board_size.column; column++)
        {
            switch(puzzle.board[row][column])
            {
                case Wall: cout << '*'; break;
                case Empty: cout << ' '; break;
                case Destination: cout << '.'; break;
                case Worker: cout << 'w'; break;
                case WorkerDest: cout << 'W'; break;
                case Box: cout << 'b'; break;
                case BoxDest: cout << 'B'; break;
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool puzzle_solved(Board puzzle)
{//             
    assert(true);
    //                                                                            
    //                                                                            
    //                       
    for (int row=0;row<puzzle.board_size.row;row++)
    {
        for (int column=0;column<puzzle.board_size.column;column++)
        {
            if (puzzle.board[row][column]==Box)
                return false;
        }
    }
    return true;
}

bool operator==(Board a, Board b)
{
    for(int i=0;i<max(a.board_size.row, b.board_size.row);i++)
    {
        for(int j=0;j<max(a.board_size.column, b.board_size.column);j++)
        {
            if(a.board[i][j]!=b.board[i][j])
                return false;
        }
    }
    return true;
}

bool repeated_board(int i, vector<Configuration>& configurations)
{
    //             
    assert((unsigned)i<configurations.size());
    //                                                                          
    //                       

    for(int j;j<i;j++)
    {
        if (configurations[i].puzzle==configurations[j].puzzle)
            return true;
    }
    return false;
}

bool box_in_corner(Board puzzle)
{
    //             
    assert(true);
    //                                                                              
    //                                                                                

    for(int row=0;row<puzzle.board_size.row;row++)
    {
        for(int column;column<puzzle.board_size.column;column++)
        {
            if(puzzle.board[row][column]==Box)
            {
                if( (puzzle.board[row-1][column]==Wall||puzzle.board[row+1][column]==Wall)
                    && (puzzle.board[row][column-1]==Wall||puzzle.board[row][column+1]==Wall) )
                        return true;
            }
        }
    }
    return false;
}

int number_of_steps(int i, vector<Configuration> configurations)
{
    //              
    assert(i>=0 && (unsigned)i<configurations.size());
    //                                                                            

    int steps_so_far=0;

    while(i>0)
    {
        i=configurations[i].parent;
        steps_so_far++;
    }
    return steps_so_far;
}

bool in_puzzle(Board puzzle, Position pos)
{
    //              
    assert(true);
    //                                                                             
    return(pos.column<puzzle.board_size.column&&pos.row<puzzle.board_size.row);
}

Position newposition(Position original, Direction dir)
{
    //              
    assert(true);
    //                                                                           

    Position nextpos = original;
    switch(dir)
    {
        case North: nextpos.row--; break;
        case South: nextpos.row++; break;
        case East: nextpos.column++; break;
        case West: nextpos.column--; break;
    }
    return nextpos;
}

bool can_step(Board board, Direction dir)
{
    //              
    assert(true);
    //                                                                                 
    //                  

    Position nextpos = newposition(board.worker_position, dir);

    if(!in_puzzle(board, nextpos))
        return false;
    else if(board.board[nextpos.row][nextpos.column]==Wall)
        return false;
    else if(board.board[nextpos.row][nextpos.column]==Box||
            board.board[nextpos.row][nextpos.column]==BoxDest)
            {
                Position nextnextpos = newposition(nextpos, dir);
                if(!in_puzzle(board, nextnextpos))
                    return false;
                else if(board.board[nextnextpos.row][nextnextpos.column]==Wall ||
                   board.board[nextnextpos.row][nextnextpos.column]==Box ||
                   board.board[nextnextpos.row][nextnextpos.column]==BoxDest)
                    return false;
            }
    return true;
}

bool in_front_of_box(Board board, Direction dir)
{
    //              
    assert(true);
    //                                                                                      
    //                    
    Position nextpos = newposition(board.worker_position, dir);
    return (board.board[nextpos.row][nextpos.column]==Box||
            board.board[nextpos.row][nextpos.column]==BoxDest);
}

void swap(Board& board, Position a, Position b)
{
    //              
    assert(board.board[a.row][a.column]!=Wall&&board.board[b.row][b.column]!=Wall);
    //                                                                             
    //                                                  

    const Cell HELP = board.board[a.row][a.column];

    if(board.board[a.row][a.column]==Destination||board.board[a.row][a.column]==WorkerDest
       || board.board[a.row][a.column]==BoxDest)
    {
        if(board.board[b.row][b.column]==Empty||board.board[b.row][b.column]==Destination)
            board.board[a.row][a.column]=Destination;
        else if(board.board[b.row][b.column]==Worker||board.board[b.row][b.column]==WorkerDest)
            board.board[a.row][a.column]=WorkerDest;
        else
            board.board[a.row][a.column]=BoxDest;
    }
    else
    {
        if(board.board[b.row][b.column]==Empty||board.board[b.row][b.column]==Destination)
            board.board[a.row][a.column]=Empty;
        else if(board.board[b.row][b.column]==Worker||board.board[b.row][b.column]==WorkerDest)
            board.board[a.row][a.column]=Worker;
        else
            board.board[a.row][a.column]=Box;
    }

    if(board.board[b.row][b.column]==Destination||board.board[b.row][b.column]==WorkerDest
       || board.board[b.row][b.column]==BoxDest)
    {
        if(HELP==Empty||HELP==Destination)
            board.board[b.row][b.column]=Destination;
        else if(HELP==Worker||HELP==WorkerDest)
            board.board[b.row][b.column]=WorkerDest;
        else
            board.board[b.row][b.column]=BoxDest;
    }
    else
    {
        if(HELP==Empty||HELP==Destination)
            board.board[b.row][b.column]=Empty;
        else if(HELP==Worker||HELP==WorkerDest)
            board.board[b.row][b.column]=Worker;
        else
            board.board[b.row][b.column]=Box;
    }

}

void step(Board& board, Direction dir, vector<Configuration>& configurations, int parent)
{
    //              
    assert(true);
    //                                                                                   
    //                                                                  
    if(can_step(board,dir))
    {
        Configuration new_config;
        new_config.puzzle = board;
        new_config.parent = parent;
        Position next_position = newposition(new_config.puzzle.worker_position,dir);
        if(in_front_of_box(new_config.puzzle,dir))
        {
            Position next_box = newposition(next_position,dir);
            swap(new_config.puzzle, next_position, next_box);
        }
        swap(new_config.puzzle, new_config.puzzle.worker_position, next_position);
        new_config.puzzle.worker_position =
            newposition(new_config.puzzle.worker_position, dir);

        configurations.push_back(new_config);
    }
}

int solve_breadth(int i, vector<Configuration>& configurations)
{//             
    assert(i>=0 && (unsigned)i<=configurations.size());
    /*
                                                                                
                                                                                       
                                                                                       
                                                                                   
                  
    */
    if ((unsigned)i==configurations.size())
    {
        cout << "No solution found" << endl;
        return 0;
    }
    else if(puzzle_solved(configurations[i].puzzle))
    {
        print_puzzle(configurations[i].puzzle);
        return number_of_steps(i, configurations);
    }
    else
    {
        if(!repeated_board(i, configurations)&&!box_in_corner(configurations[i].puzzle))
        {
            step(configurations[i].puzzle, North, configurations, i);
            step(configurations[i].puzzle, East, configurations, i);
            step(configurations[i].puzzle, South, configurations, i);
            step(configurations[i].puzzle, West, configurations, i);
        }
        return solve_breadth(i+1, configurations);
    }

    cout << "Reached end of solve function" << endl;
    return 0;
}
//                                                                             

bool repeated_board_depth(vector<Board>& configurations)
{
    //             
    assert(true);
    //                                                                          
    //                       

    for(int j;j<configurations.size()-1;j++)
    {
        if (configurations[configurations.size()-1]==configurations[j])
            return true;
    }
    return false;
}

bool step_depth(Board& board, Direction dir, vector<Board>& configurations)
{
    //              
    assert(true);
    //                                                                                   
    //                                                                  
    if(can_step(board,dir))
    {
        Board new_config = board;
        Position next_position = newposition(new_config.worker_position,dir);
        if(in_front_of_box(new_config,dir))
        {
            Position next_box = newposition(next_position,dir);
            swap(new_config, next_position, next_box);
        }
        swap(new_config, new_config.worker_position, next_position);
        new_config.worker_position =
            newposition(new_config.worker_position, dir);

        configurations.push_back(new_config);
    }
}

int solve_depth(int steps, vector<Board>& path, int& max_depth)
{
    //             
    assert(steps>=0 && steps<=max_depth);
    /*
                                                                              
                                                                                
                                                                            
                   
                                                                                     
                        
    */

    if(steps==max_depth)
        return -1;
    if(puzzle_solved(path[steps]))
    {
        print_puzzle(path[steps]);
        max_depth = steps;
        return steps;
    }
    else if(repeated_board_depth(path))
        return -2;
    else if(box_in_corner(path[steps]))
        return -3;

    else
    {
        for(int dir=0;dir<4;dir++)
        {
            if(step_depth(path[steps],(Direction) dir, path))
            {
                //                      
                int solution = solve_depth(steps+1, path, max_depth);
                if (solution>=0)
                    return solution;
                path.pop_back();
            }
        }
        return -4;
    }
}

int main()
{
    ifstream infile;
    read_file(infile);
    //                   
    Configuration original;
    vector<Configuration> configurations;
    original.parent = 0;
    if (read_universe_file(infile, original.puzzle))
    {
        configurations.push_back(original);
    }
    int solution = solve_breadth(0, configurations);
    cout << "Number of steps: " << solution << endl;
    /*
                       
                   
                          
                                 
                                             
     
                                           
     
                            
                                                                    
                                                    
    */
    return 0;
}

