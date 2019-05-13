//                                      
//                                       

//                                                                                             
//                                                                                                
//                                                            

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <string>

using namespace std;

/*                                                                    
                                                     
                                                                     */

const int MAX_ROWS = 20 ;
const int MAX_COLUMNS = 20 ;

struct position
{
    int row ;
    int column ;
} ;

struct config
{
    int Puzzle[MAX_ROWS][MAX_COLUMNS] ;
    vector<position> boxes ;
    position worker ;
} ;

struct Candidate
{
    config candidate ;
    int parent_candidate ;
} ;

/*                                                                    
                                               
                                                                     */
bool check_array(int a[MAX_ROWS][MAX_COLUMNS], int b[MAX_ROWS][MAX_COLUMNS], int rows, int columns)
{
    //            
    assert(rows >=0 && columns >= 0) ;
    /*
                  
                                                      
    */
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            if(a[i][j] != b[i][j])
                return false;
    return true ;
}

/*                                                                    
                                                  
                                                                     */

void read_puzzle(config& start, int& rows, int& columns)
{
    //            
    assert(rows >=0 && columns >= 0) ;
    /*
                  
                                                                                    
    */

    string filename;
    cout << "Please enter a filename: " ; getline(cin, filename) ;

    ifstream fin(filename.c_str()) ;

    if(!fin.is_open())
        cout << "Could not open the file." ;

    char c ;
    int column = 0 ;
    int index_box = 3 ;

    fin.get(c);

    while(fin)
    {

        if(c == 'B')
            {
                start.Puzzle[rows][column++] = -1*index_box ;
                position box ;
                box.row = rows ;
                box.column = column - 1;
                start.boxes.push_back(box) ;
                index_box++ ;
            }
        else if (c == 'W')
            {
                start.Puzzle[rows][column++] = -2 ;
                start.worker.row = rows ;
                start.worker.column = column - 1;
            }
        else if (c == '.')
            start.Puzzle[rows][column++] = -1 ;
        else if (c == ' ')
            start.Puzzle[rows][column++] = 0 ;
        else if (c == '*')
            start.Puzzle[rows][column++] = 1 ;
        else if (c == 'w')
            {
                start.Puzzle[rows][column++] = 2 ;
                start.worker.row = rows ;
                start.worker.column = column - 1;
            }
        else if (c == 'b')
            {
                start.Puzzle[rows][column++] = index_box ;
                position box ;
                box.row = rows ;
                box.column = column - 1 ;
                start.boxes.push_back(box) ;
                index_box++ ;
            }
        else
        {
            rows++ ;
            columns = column ;
            column = 0 ;
        }

        fin.get(c);
    }
}

/*                                                                    
                                                
                                                                     */

void output_puzzle(config puzzle, int rows, int columns)
{
    //            
    assert(rows >=0 && columns >= 0) ;
    /*
                  
                                              
    */
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(puzzle.Puzzle[i][j] <= -3)
                cout<<"B" ;
            else if(puzzle.Puzzle[i][j] == -2)
                cout<<"W" ;
            else if(puzzle.Puzzle[i][j] == -1)
                cout<<"." ;
            else if(puzzle.Puzzle[i][j] == 0)
                cout<<" " ;
            else if(puzzle.Puzzle[i][j] == 1)
                cout<<"*" ;
            else if(puzzle.Puzzle[i][j] == 2)
                cout<<"w" ;
            else if(puzzle.Puzzle[i][j] >= 3)
                cout<<"b" ;
        }
        cout<<endl;
    }

}

/*                                                                    
                                    
                                                                     */

int size (vector<position>& boxes)
{
    //            
    assert(true) ;
    /*
                  
                                                                 
    */
    return static_cast<int> (boxes.size ()) ;
}

int size_candidate (vector<Candidate>& c)
{
    //            
    assert(true) ;
    /*
                  
                                                                 
    */
    return static_cast<int> (c.size ()) ;
}

int size_config (vector<config>& c)
{
    //            
    assert(true) ;
    /*
                  
                                                                 
    */
    return static_cast<int> (c.size ()) ;
}

/*                                                                    
                                     
                                                                     */

/*                                                                    
                                 
                                                                     */
bool can_go_north_box (config puzzle, int i, int j)
{
    //            
    assert(i >=0 && j >= 0) ;
    /*
                  
                                                         
    */
    if(puzzle.Puzzle[i-1][j] == 0 || puzzle.Puzzle[i-1][j] == -1)
        return true ;
    return false ;
}

bool can_go_north (config puzzle)
{
    //            
    assert(true) ;
    /*
                  
                                                                                            
    */
    if(puzzle.Puzzle[puzzle.worker.row - 1][puzzle.worker.column] != 1)
    {
        if(puzzle.Puzzle[puzzle.worker.row - 1][puzzle.worker.column] >= 3 || puzzle.Puzzle[puzzle.worker.row - 1][puzzle.worker.column] <= -3)
            return (can_go_north_box(puzzle, puzzle.worker.row - 1, puzzle.worker.column)) ;
        else return true ;
    }
    return false ;
}

/*                                                                    
                                 
                                                                     */

bool can_go_south_box (config puzzle, int i, int j)
{
    //            
    assert(i >=0 && j >= 0) ;
    /*
                  
                                                         
    */
    if(puzzle.Puzzle[i+1][j] == 0 || puzzle.Puzzle[i+1][j] == -1)
        return true ;
    return false ;
}

bool can_go_south (config puzzle)
{
    //            
    assert(true) ;
    /*
                  
                                                                                            
    */
    if(puzzle.Puzzle[puzzle.worker.row + 1][puzzle.worker.column] != 1)
    {
        if(puzzle.Puzzle[puzzle.worker.row + 1][puzzle.worker.column] >= 3 || puzzle.Puzzle[puzzle.worker.row + 1][puzzle.worker.column] <= -3)
            return (can_go_south_box(puzzle, puzzle.worker.row + 1, puzzle.worker.column)) ;
        else return true ;
    }
    return false ;
}

/*                                                                    
                                
                                                                     */

bool can_go_east_box (config puzzle, int i, int j)
{
    //            
    assert(i >=0 && j >= 0) ;
    /*
                  
                                                        
    */
    if(puzzle.Puzzle[i][j+1] == 0 || puzzle.Puzzle[i][j+1] == -1)
        return true ;
    return false ;
}

bool can_go_east (config puzzle)
{
    //            
    assert(true) ;
    /*
                  
                                                                                           
    */
    if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column + 1] != 1)
    {
        if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column + 1] >= 3 || puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column + 1] <= -3)
            return (can_go_east_box(puzzle, puzzle.worker.row, puzzle.worker.column + 1)) ;
        else return true ;
    }
    return false ;
}

/*                                                                    
                                
                                                                     */

bool can_go_west_box (config puzzle, int i, int j)
{
    //            
    assert(i >=0 && j >= 0) ;
    /*
                  
                                                        
    */
    if(puzzle.Puzzle[i][j-1] == 0 || puzzle.Puzzle[i][j-1] == -1)
        return true ;
    return false ;
}

bool can_go_west (config puzzle)
{
    //            
    assert(true) ;
    /*
                  
                                                                                           
    */
    if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column - 1] != 1)
    {
        if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column - 1] >= 3 || puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column - 1] <= -3)
            return (can_go_west_box(puzzle, puzzle.worker.row, puzzle.worker.column - 1)) ;
        else return true ;
    }
    return false ;
}

/*                                                                    
                                     
                                                                     */

/*                                                                    
                                 
                                                                     */

position north (config puzzle)
{
    //            
    assert(true) ;
    /*
                  
                                                              
    */

    position next ;

    next.row = puzzle.worker.row - 1 ;
    next.column = puzzle.worker.column ;

    return next ;
}

/*                                                                    
                                 
                                                                     */

position south (config puzzle)
{
    //            
    assert(true) ;
    /*
                  
                                                              
    */

    position next ;

    next.row = puzzle.worker.row + 1 ;
    next.column = puzzle.worker.column ;

    return next ;
}

/*                                                                    
                                
                                                                     */

position east (config puzzle)
{
    //            
    assert(true) ;
    /*
                  
                                                             
    */

    position next ;

    next.row = puzzle.worker.row ;
    next.column = puzzle.worker.column + 1 ;

    return next ;
}

/*                                                                    
                                
                                                                     */

position west (config puzzle)
{
    //            
    assert(true) ;
    /*
                  
                                                             
    */
    position next ;

    next.row = puzzle.worker.row ;
    next.column = puzzle.worker.column - 1 ;

    return next ;
}

/*                                                                    
                                        
                                                                     */

config change(config puzzle, position next)
{
        //            
        assert(true) ;
        /*
                      
                                                                  
        */

        if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] == -2)
            puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = -1 ;
        else
            puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = 0 ;

        int row_box = next.row - puzzle.worker.row ;
        int column_box = next.column - puzzle.worker.column ;

        puzzle.worker.row = next.row ;
        puzzle.worker.column = next.column ;

        if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] == -1)
            puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = -2 ;
        else if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] == 0)
            puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = 2 ;
        else if(puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] >= 3 || puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] <= -3)
        {
            int index = puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] ;
            int neg = 0 ;

            if(index < 0)
                {
                    index = -1 * index ;
                    neg = 1 ;
                }

            index -= 3 ;

            puzzle.boxes[index].row += row_box ;
            puzzle.boxes[index].column += column_box ;

            if(puzzle.Puzzle[puzzle.boxes[index].row][puzzle.boxes[index].column] == -1)
                puzzle.Puzzle[puzzle.boxes[index].row][puzzle.boxes[index].column] = -1 * (index + 3) ;
            else
                puzzle.Puzzle[puzzle.boxes[index].row][puzzle.boxes[index].column] = index + 3 ;

            if(neg == 1)
                puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = -2 ;
            else
                puzzle.Puzzle[puzzle.worker.row][puzzle.worker.column] = 2 ;
        }

    return puzzle;
}

/*                                                                    
                                            
                                                                     */

bool puzzle_ready (config puzzle, int rows, int columns)
{
    //            
    assert(rows >= 0 && columns >= 0) ;
    /*
                  
                                                         
    */
    for (int i = 0; i < rows; i++)
       for (int j = 0; j < columns; j++)
         if(puzzle.Puzzle[i][j] >= 3)
            return false ;
    return true;
}

/*                                                                    
                                                          
                                                                     */

bool puzzle_present(vector<Candidate> c, int i, Candidate new_puzzle, int rows, int columns)
{
    //            
    assert(rows >= 0 && columns >= 0 && i >= 0) ;
    /*
                  
                                                              
    */
    for (int index = 0; index < i; index++)
        if(check_array(c[index].candidate.Puzzle, new_puzzle.candidate.Puzzle, rows, columns))
            return true ;

    return false ;
}

/*                                                                    
                                                    
                                                                     */

void tries(vector<Candidate>& c, int i, position next, int rows, int columns)
{
    //            
    assert(rows >= 0 && columns >= 0 && i >= 0) ;
    /*
                  
                                                                                                       
    */

    config p = c[i].candidate ;
    config newp = change(p, next) ;
    Candidate newc = {newp, i} ;

    if(!puzzle_present(c, i, newc, rows, columns))
        c.push_back(newc) ;
}

/*                                                                    
                                             
                                                                     */
void show_steps (vector<Candidate> c, int i)
{
    //            
    assert(i >= 0) ;
    /*
                  
                                                                                       
    */

    int counter = 0 ;

    while (i != -1)
    {
        i = c[i].parent_candidate ;
        counter ++ ;
    }

    cout<<counter - 1;
}

/*                                                                    
                                   
                                                                     */
void solve (config start, int rows, int columns)
{
    //            
    assert(rows >= 0 && columns >= 0) ;
    /*
                  
                                                
    */
   vector<Candidate> c = {{start, -1}} ;
   int i = 0 ;
   while (i < size_candidate(c) && !puzzle_ready (c[i].candidate, rows, columns))
   {
       config p = c[i].candidate ;
      if (can_go_north(p))
        tries(c, i, north(p), rows, columns) ;
      if (can_go_south(p))
        tries(c, i, south(p), rows, columns) ;
      if (can_go_west(p))
        tries(c, i, west(p), rows, columns) ;
      if (can_go_east(p))
        tries(c, i, east(p), rows, columns) ;
      i = i+1 ;

   }
   if (i < size_candidate (c))
	   show_steps (c, i) ;
}

/*                                                                    
                                                         
                                                                     */

bool puzzle_present_dfs(config new_puzzle, vector<config> attempt, int rows, int columns)
{
    //            
    assert(rows >= 0 && columns >= 0) ;
    /*
                  
                                                              
    */

    for (int index = 0; index < size_config(attempt); index++)
        if(check_array(attempt[index].Puzzle, new_puzzle.Puzzle, rows, columns))
            return true ;

    return false ;
}

/*                                                                    
                                                
                                                                     */
void solve_dfs (vector<config>& attempt, vector<config>& shortest, int max_depth, int rows, int columns) ;

void tries_dfs (vector<config>& attempt, position next, vector<config>& shortest, int max_depth, int rows, int columns)
{
    //            
    assert(rows >= 0 && columns >= 0 && max_depth >= 0) ;
    /*
                  
                                                                                                    
    */

   config p    = attempt[size_config(attempt) - 1] ;
   config newp = change(p, next) ;

   if (!puzzle_present_dfs (newp, attempt, rows, columns))
   {
       attempt.push_back (newp) ;
       solve_dfs (attempt, shortest, max_depth, rows, columns) ;
       attempt.pop_back () ;
   }
}

/*                                                                    
                                   
                                                                     */

void solve_dfs (vector<config>& attempt, vector<config>& shortest, int max_depth, int rows, int columns)
{
    //            
    assert(rows >= 0 && columns >= 0 && max_depth >= 0 && size_config(attempt) > 0) ;
    /*
                  
                                              
    */
    const int CURRENT = size_config (attempt) ;
    const int BEST    = size_config (shortest) ;
    config p          = attempt[CURRENT-1] ;

    if (BEST > 0 && CURRENT >= BEST)      { return ; }
    else if (CURRENT > max_depth+1)       { return ; }
    else if (puzzle_ready (p, rows, columns)) { shortest = attempt ; return ; }
    if (can_go_north(p))
        tries_dfs (attempt, north(p), shortest, max_depth, rows, columns) ;
    if (can_go_south(p))
        tries_dfs (attempt, south(p), shortest, max_depth, rows, columns) ;
    if (can_go_west(p))
        tries_dfs (attempt, west(p), shortest, max_depth, rows, columns) ;
    if (can_go_east(p))
        tries_dfs (attempt, east(p), shortest, max_depth, rows, columns) ;
}

/*                                                                    
                                          
                                                                     */

void steps_dfs (vector<config> shortest)
{
    //            
    assert(true) ;
    /*
                  
                                                                        
    */
    cout<<size_config(shortest) - 1 ;
}

int main()
{
    int rows = 0, columns = 0 ;
    config start ;
    read_puzzle(start, rows, columns) ;
    output_puzzle(start, rows, columns) ;

    solve(start, rows, columns) ;

    //                                                                                     

    /*                        
                             

                              

                                                     
                         */

    return 0;
}

