#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <vector>

using namespace std;

//       
//                           

enum Cell { Wall, Empty, Destination, Worker, WorkerDestination, Box, BoxDestination };
vector<char> Representations = {'*', ' ', '.', 'w', 'W', 'b', 'B' };
enum Direction { East, North, West, South };
typedef vector<vector<Cell>> Puzzle;

struct Pos{
    int row, col;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

void move_two(Cell& w, Cell& e)
{//            
    assert(true);
    //               
    //                                                      
    //                                               
    //                                    
    if(w == Worker) w = Empty;
    else            w = Destination;

    if(e == Empty)  e = Worker;
    else            e = WorkerDestination;
}

void move_three(Cell& w, Cell& b, Cell& e)
{//             
    assert(true);
    //                               
    //                               
    //                           
    //                                  
    if(w == Worker) w = Empty;
    else            w = Destination;

    if(b == Box)    b = Worker;
    else            b = WorkerDestination;

    if(e == Empty)  e = Box;
    else            e = BoxDestination;
}

int size(vector<Cell>& v)
{
    return static_cast<int>(v.size());
}

int size(Puzzle& v)
{
    return static_cast<int>(v.size());
}

int size(vector<Candidate>& v)
{
    return static_cast<int>(v.size());
}

int size(vector<Puzzle>& v)
{
    return static_cast<int>(v.size());
}

bool operator==(Puzzle& a, Puzzle& b)
{//            
    assert(true);
    //              
    //                                                                      
    int rows = size(a);

    if(rows != size(b))
        return false;
    else if(rows < 1) //                                                                              
        return true;

    int cols = size(a[0]);
    if(rows != size(b) || cols != size(b[0]))
        return false;

    for(int row = 0; row < rows; row++)
        for(int col = 0; col < cols; col++)
            if(a[row][col] != b[row][col])
                return false;

    return true;
}

int symbol_index(char c)
{//            
    assert(true);
    //                                                                                 
    //                                               
    int s = static_cast<int>(Representations.size());

    for(int i = 0; i < s; i++)
        if(c == Representations[i])
            return i;

    return s;
}

bool read_world(ifstream& inputfile, Puzzle& world)
{//             
    assert(inputfile && inputfile.is_open());
/*               
                                                                                                         
                                                                
*/

    vector<Cell> line;
    while(inputfile)
    {
        char c;
        inputfile.get(c);
        if(inputfile)
        {
            if(c == '\n')
            {
                world.push_back(line);
                line.clear();
            }
            else if(symbol_index(c) == -1)
            {
                cout << "Unknown symbol encountered " << c << endl;
                world.clear();
                return false;
            }
            else
            {
                line.push_back(static_cast<Cell>(symbol_index(c)));
            }
        }
    }
    return true;
}

ostream& operator<< (ostream& out, Puzzle& p)
{//               
    assert (true) ;
/*                 
                                                                          
*/
    int h_max = size(p);
    int w_max = size(p[0]);

    for(int h = 0; h < h_max; h++)
    {
        for(int w = 0; w < w_max; w++)
        {
            out << Representations[p[h][w]];
        }
        out << endl;
    }
    return out;
}

Pos worker_pos(Puzzle p)
{//            
    assert(true);
    //               
    //                                                       

    Pos pos = {-1, -1};

    for(int row = 0; row < size(p); row++)
        for(int col = 0; col < size(p[0]); col++)
            if (p[row][col] == Worker ||
                p[row][col] == WorkerDestination)
                {
                    pos.col = col;
                    pos.row = row;
                    return pos;
                }

    cout << "Couldn't find the worker!" << endl;
    return pos;
}

bool puzzle_ready(Puzzle p)
{//             
    assert(true);
    //               
    //                                                                                           

    for(int row = 0; row < size(p); row++)
        for(int col = 0; col < size(p[0]); col++)
            if (p[row][col] == Destination || p[row][col] == WorkerDestination)
                return false;

    return true;
}

bool puzzle_present(vector<Candidate>& c, Puzzle p)
{//             
    assert(true);
    //               
    //                                                                                         

    int cands = size(c);
    for(int j = 0; j < cands; j++)
    {
        if(p == c[j].candidate)
            return true;
    }
    return false;
}

bool puzzle_present(Puzzle p, vector<Puzzle>& puzzles)
{//             
    assert(true);
    //               
    //                                                                                

    int x = size(puzzles);
    for(int i = 0; i < x; i++)
    {
        if(p == puzzles[i])
            return true;
    }
    return false;
}

Pos north(Puzzle p)
{//            
    assert(true);
    //               
    //                                                                    
    Pos w = worker_pos(p);
    w.row = w.row-1;
    return w;
}

Pos south(Puzzle p)
{//            
    assert(true);
    //               
    //                                                                    
    Pos w = worker_pos(p);
    w.row = w.row+1;
    return w;
}

Pos west(Puzzle p)
{//            
    assert(true);
    //               
    //                                                                   
    Pos w = worker_pos(p);
    w.col = w.col-1;
    return w;
}

Pos east(Puzzle p)
{//            
    assert(true);
    //               
    //                                                                   
    Pos w = worker_pos(p);
    w.col = w.col+1;
    return w;
}

Puzzle move_worker(Puzzle p, Direction next)
{//             
    assert(true);
    //               
    //                                                                                                  
    Pos worker = worker_pos(p);
    Pos neighbor;

    switch(next)
    {
        case East: neighbor = east(p); break;
        case West: neighbor = west(p); break;
        case North: neighbor = north(p); break;
        case South: neighbor = south(p); break;
    }

    if(p[neighbor.row][neighbor.col] == Empty ||
       p[neighbor.row][neighbor.col] == Destination)
        move_two(p[worker.row][worker.col],
                 p[neighbor.row][neighbor.col]);
    else
    {
        Pos neighbor2 = {neighbor.row, neighbor.col};
        switch(next)
        {
            case East: neighbor2.col++; break;
            case West: neighbor2.col--; break;
            case North: neighbor2.row--; break;
            case South: neighbor2.row++; break;
        }
        move_three(p[worker.row][worker.col],
                   p[neighbor.row][neighbor.col],
                   p[neighbor2.row][neighbor2.col]);
    }

    return p;
}

void show_path(vector<Candidate>& c, int i, int steps)
{//             
    assert(true);
    //               
    //                                                  

    //          
    if(i<0)
    {
        cout << "Steps " << steps << endl;
        return;
    }

    cout << c[i].candidate;
    cout << endl;
    steps++;
    show_path(c, c[i].parent_candidate, steps);
}

bool can_go(Cell a, Cell b, Cell c)
{//            
    assert(true);
    //              
    //                                                                                 
    //                                           

    return (((a == Worker || a == WorkerDestination) && (b == Empty || b == Destination)) ||
            ((a == Worker || a == WorkerDestination) && (b == Box || b == BoxDestination) && (c == Empty || c == Destination)));
}

bool can_go_north(Puzzle p)
{//            
    assert(true);
    //               
    //                                           
    Pos w = worker_pos(p);
    Pos neighbor = north(p);

    if(w.row-2 >= 0)
        return can_go(p[w.row][w.col],
              p[neighbor.row][neighbor.col],
              p[neighbor.row-1][neighbor.col]);
    else
        return can_go(p[w.row][w.col],
              p[neighbor.row][neighbor.col],
              Wall);
}

bool can_go_south(Puzzle p)
{//            
    assert(true);
    //               
    //                                           
    Pos w = worker_pos(p);
    Pos neighbor = south(p);

    if(w.row+2 < size(p))
        return can_go(p[w.row][w.col],
              p[neighbor.row][neighbor.col],
              p[neighbor.row+1][neighbor.col]);
    else
        return can_go(p[w.row][w.col],
              p[neighbor.row][neighbor.col],
              Wall);
}

bool can_go_west(Puzzle p)
{//            
    assert(true);
    //               
    //                                          

    Pos w = worker_pos(p);
    Pos neighbor = west(p);

    if(w.col-2 >= 0)
        return can_go(p[w.row][w.col],
              p[neighbor.row][neighbor.col],
              p[neighbor.row][neighbor.col-1]);
    else
        return can_go(p[w.row][w.col],
              p[neighbor.row][neighbor.col],
              Wall);
}

bool can_go_east(Puzzle p)
{//            
    assert(true);
    //               
    //                                          

    Pos w = worker_pos(p);
    Pos neighbor = east(p);

    if(w.col+2 < size(p[0]))
        return can_go(p[w.row][w.col],
              p[neighbor.row][neighbor.col],
              p[neighbor.row][neighbor.col+1]);
    else
        return can_go(p[w.row][w.col],
              p[neighbor.row][neighbor.col],
              Wall);
}

void tries(vector<Candidate>& c, int i, Direction next)
{//             
    assert(i >= 0);
    //               
    //                                         
    //                                                                                  

    Puzzle p = c[i].candidate ;
    Puzzle newp = move_worker(p, next);
    Candidate newc = {newp, i} ;
    if (!puzzle_present(c, newp))
        c.push_back(newc) ;
}

void solve_breadth_first(Puzzle start, bool show_solution)
{//             
    assert(true);
    //               
    //                                                                  
    //                                                       

    vector<Candidate> c = {{start, -1}};
    int i = 0;
    while(i < size(c) &&
          !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if(can_go_north(p)) tries (c, i, North);
        if(can_go_south(p)) tries (c, i, South);
        if(can_go_west(p)) tries (c, i, West);
        if(can_go_east(p)) tries (c, i, East);
        i = i+1;
    }

    if(i < size(c) && show_solution)
        show_path(c, i, -1);
}

void tries(vector<Puzzle>& attempt, Direction next, vector<Puzzle>& shortest, int max_depth);

void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{//             
    assert(true);
    //               
    //                                                                

    const int CURRENT = size(attempt) ;
    const int BEST = size(shortest) ;
    Puzzle p = attempt[CURRENT-1] ;
    if(BEST > 0 && CURRENT>= BEST) { return; }
    else if(CURRENT> max_depth+1) { return; }
    else if(puzzle_ready(p)) { shortest= attempt; return; }
    if(can_go_north(p)) tries (attempt, North, shortest, max_depth);
    if(can_go_south(p)) tries (attempt, South, shortest, max_depth);
    if(can_go_west(p)) tries (attempt, West, shortest, max_depth);
    if(can_go_east(p)) tries (attempt, East, shortest, max_depth);
}

void tries(vector<Puzzle>& attempt, Direction next, vector<Puzzle>& shortest, int max_depth)
{//            
    assert(max_depth > 0);
    //                
    //                                         
    //                                                                               
    Puzzle p = attempt[size(attempt)-1];
    Puzzle newp = move_worker(p, next);
    if(!puzzle_present(newp, attempt))
    {
        attempt.push_back(newp);
        solve_depth_first(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void show_solution(vector<Puzzle>& v)
{//             
    assert(true);
    //              
    //                                                        

    int x = size(v);
    for(int i = 0; i < x; i++)
    {
        cout << v[i] << endl;
    }
}

//       
//      
//      
//      
//      

vector<vector<Cell>> Puzzle1 = {
    {Wall, Wall, Wall, Wall, Wall},
    {Wall, Empty, Empty, Empty, Wall},
    {Wall, Worker, Box, Destination, Wall},
    {Wall, Wall, Wall, Wall, Wall}};

//       
//      
//      
//      
//      

vector<vector<Cell>> Puzzle2 = {
    {Wall, Wall, Wall, Wall, Wall},
    {Wall, Worker, Empty, Empty, Wall},
    {Wall, Empty, Box, Destination, Wall},
    {Wall, Wall, Wall, Wall, Wall}};

string get_file_name()
{//            
    assert(true);
    //               
    //                                     
    cout << "Enter Sokoban configuration file name: " << endl;
    string filename;
    getline(cin, filename);
    return filename;
}

//                                                    
//                                                    

int main()
{
    //       
    //       
    cout << "Puzzle 1" << endl;
    solve_breadth_first(Puzzle1, true);
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
    /*
             
                                                
                                                          
     
                                                    
                  
     
                                   
                            
                                 
                                            
                          
                                    
        
                                                            
    */
    return 0;
}

