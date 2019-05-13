//                                                                                         
//                                                                    
/*                                                                                                                                                                     
                 
                                                                                                                                                              
                                                                                                                                                       
                                                                        
                                                                                                                      
                                                                                
                                                                       
                                                                
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

enum Cell {Empty=0, Wall, Edest, Ework, Dwork, Ebox, Dbox};
//                                                                                                                                                   
//                                                                                

const char  EMPTY       = ' ' ;                 //                                       
const char  WALL        = '*' ;                 //                           
const char  EDEST       = '.' ;                 //                                                              
const char  EWORK       = 'w' ;                 //                                                      
const char  DWORK       = 'W' ;                 //                                                           
const char  EBOX        = 'b' ;                 //                                                   
const char  DBOX        = 'B' ;                 //                                                        

const int   MAXWIDTH    = 15 ;                  //                               
const int   MAXLENGTH   = 15 ;                  //                                
const int   MAXDEPTH    = 100 ;                 //                                          

struct Pos
{
    int col, row ; //                                  
};

struct Puzzle
{
    Cell universe [MAXLENGTH][MAXWIDTH] ;
    Pos worker ;
};

bool operator == (const Pos& p1, const Pos& p2)
{//               
    assert (true);
//                 
//                                                
    return p1.col == p2.col && p1.row == p2.row ;
}

bool operator == (const Puzzle& p1, const Puzzle& p2)
{//               
    assert (true);
//                 
//                                              
    return p1.universe == p2.universe && p1.worker == p2.worker ;
}

struct Candidate
{
    Puzzle candidate ;
    int parent_candidate ;
};

int size (vector<Puzzle>& check)
{//               
    assert (true);
//                 
//                               
    return static_cast<int> (check.size()) ;
}

int csize (vector<Candidate>& check)
{//               
    assert (true);
//                 
//                               
    return static_cast<int> (check.size()) ;
}

bool open_universe_file (ifstream& infile)
{//               
    assert (true);
//                 
//                                                                                   
    cout << "Enter the name of the file you wish to open." << endl;
    string filename ;
    getline (cin, filename) ;
    infile.open (filename.c_str()) ;
    if (infile)
        return true ;
    else
        return false ;
}

void fill_universe (Cell universe [MAXLENGTH][MAXWIDTH])
{//               
    assert (MAXLENGTH >= 0 && MAXWIDTH >= 0);
//                 
//                                                                                                                    
    for (int i = 0; i < MAXLENGTH; i++)
        for (int j = 0; j < MAXWIDTH; j++)
            universe [i][j] = Empty ;
}

Cell transform_to_cell (char a)
{//               
    assert (true);
//                 
//                                                                                         
    if (a == EMPTY)
        return Empty;
    else if (a == WALL)
        return Wall;
    else if (a == EDEST)
        return Edest;
    else if (a == EWORK)
        return Ework;
    else if (a == DWORK)
        return Dwork;
    else if (a == EBOX)
        return Ebox;
    else if (a == DBOX)
        return Dbox;
}

char transform_backto_char (Cell b)
{//               
    assert (true);
//                 
//                                                                                                                               
    if (b == 0)
        return EMPTY;
    else if (b == 1)
        return WALL ;
    else if (b == 2)
        return EDEST ;
    else if (b == 3)
        return EWORK ;
    else if (b == 4)
        return DWORK ;
    else if (b == 5)
        return EBOX ;
    else if (b == 6)
        return DBOX ;
}

bool read_universe_file (ifstream& infile, Cell universe [MAXLENGTH][MAXWIDTH], Pos& worker)
{//               
    assert (infile.is_open() && MAXLENGTH >= 0 && MAXWIDTH >= 0) ;
//                 
//                                                                                                                                                                                  
    char a ;
    int i = 0;
    int j = 0;
    int amount = 0; //                                                                                                     
    while (infile)
    {
        infile.get(a);
        if (j >= MAXWIDTH || i >= MAXLENGTH)
            return false ;
        else if (a == '\n')
        {
            i++ ;
            j = 0 ;
            cout << " " << endl;
        }
        else
        {
            Cell b = transform_to_cell(a);
            universe [i][j] = b ;
            if (b == Dwork || b == Ework)
            {
                worker.col = j ;
                worker.row = i ;
                amount++ ;
            }
            cout << universe [i][j] ;
            j++ ;
       }
    }
    if (amount != 1)
        return false;
    return true;
}

void show_universe (Cell universe[MAXLENGTH][MAXWIDTH])
{//               
    assert (true);
//                 
//                                      
    for (int i = 0; i < MAXLENGTH; i++)
    {
        for (int j = 0; j < MAXWIDTH; j++)
            {
                Cell b = universe[i][j] ;
                char a = transform_backto_char(b) ;
                cout << a ;
            }
        cout << " " << endl;
    }
}

bool legal_moves(char direction, Puzzle current)
{//               
    assert (current.worker.col > 0 && current.worker.row > 0 && current.worker.col < MAXWIDTH-1 && current.worker.row < MAXLENGTH-1);
    //                                                                     
//                 
//                                                                                   
//                                                                      
//                                                                                                                                                                                   

//                                                                                                                                     
    int c = 0;
    int r = 0;
    if (direction == 'l')
        c = -1 ;
    else if (direction == 'r')
        c = 1 ;
    else if (direction == 'd')
        r = 1 ;
    else if (direction == 'u')
        r = -1 ;
    if (current.universe [current.worker.row+r][current.worker.col+c] == Wall)
        return false ;
    else if (current.universe [current.worker.row+r][current.worker.col+c] != Ebox && current.universe [current.worker.row+r][current.worker.col+c] != Dbox)
        return true ;
    else if (current.universe [current.worker.row+2*r][current.worker.col+2*c] != Wall && current.universe [current.worker.row+2*r][current.worker.col+2*c] != Ebox && current.universe [current.worker.row+2*r][current.worker.col+2*c] != Dbox)
            return true ;
    return false ;
}

bool move_direction (char direction, Puzzle current)
{//               
    assert (current.worker.col > 0 && current.worker.row > 0 && current.worker.col < MAXWIDTH-1 && current.worker.row < MAXLENGTH-1);
//                 
//                                                                                                                                                  
//                                                                                    
    int c = 0;
    int r = 0;
    if (direction == 'l')
        c = -1 ;
    else if (direction == 'r')
        c = 1 ;
    else if (direction == 'd')
        r = 1 ;
    else if (direction == 'u')
        r = -1 ;
    if (current.universe[current.worker.row][current.worker.col] == Ework)
        current.universe [current.worker.row][current.worker.col] = Empty ;
    else if (current.universe[current.worker.row][current.worker.col] == Dwork)
        current.universe [current.worker.row][current.worker.col] = Edest ;
    else
        return false ;
    if (current.universe [current.worker.row+r][current.worker.col+c] == Dbox)
        {
            current.universe [current.worker.row+r][current.worker.col+c] = Dwork ;
            if (current.universe [current.worker.row+2*r][current.worker.col+2*c] == Empty)
                current.universe [current.worker.row+2*r][current.worker.col+2*c] = Ebox ;
            else if (current.universe [current.worker.row+2*r][current.worker.col+2*c] == Edest)
                current.universe [current.worker.row+2*r][current.worker.col+2*c] = Dbox ;
            else
                return false ;
                }
            if (current.universe [current.worker.row+r][current.worker.col+c] == Ebox)
            {
                current.universe [current.worker.row+r][current.worker.col+c] = Ework ;
                if (current.universe [current.worker.row+2*r][current.worker.col+2*c] == Empty)
                    current.universe [current.worker.row+2*r][current.worker.col+2*c] = Ebox ;
                else if (current.universe [current.worker.row+2*r][current.worker.col+2*c] == Edest)
                    current.universe [current.worker.row+2*r][current.worker.col+2*c] = Dbox ;
                else
                    return false ;
                }
        current.worker.col = current.worker.col +c ;
        current.worker.row = current.worker.row +r ;
        return true;
}

bool in_memory (Puzzle current, vector<Puzzle>& known)
{//               
    assert (true);
//                 
//                                                                                                                                                        
    int s = size(known) ;
    for (int i = 0; i < s; i++)
        if (known [i] == current)
            return true ;
    return false ;
}

bool in_BFSmemory (Candidate current, vector<Candidate>& known)
{//               
    assert (true);
//                 
//                                                                                                                                                        
    int s = csize(known) ;
    for (int i = 0; i < s; i++)
        if (known[i].candidate == current.candidate)
            return true ;
    return false ;
}

void update_best (vector<Puzzle>& best, vector<Puzzle>& attempt)
{//               
    assert (true);
//                 
//                                                                                      
    if (size(attempt) <= size(best))
        best = attempt ;
}

bool is_solved (vector<Puzzle>& attempt)
{//               
    assert (true);
//                 
//                                                              
    int s = size(attempt) - 1;
    Puzzle current = attempt [s] ;
    for (int i = 0; i < MAXLENGTH; i++)
        for (int j = 0; j < MAXWIDTH; j++)
            if (current.universe[i][j] == Edest)
                return false ;
    return true ;
}

bool no_legal_moves (vector<Puzzle>& attempt)
{//               
    assert (true);
//                 
//                                                   
    int s = size(attempt) - 1;
    Puzzle current = attempt [s] ;
    if (legal_moves('r', current))
        return false;
    if (legal_moves('d', current))
        return false;
    if (legal_moves('l', current))
        return false;
    if (legal_moves('u', current))
        return false;
    return true;
}

bool depth_first (vector<Puzzle>& best, vector<Puzzle>& attempt, int c)
{//               
    assert (c >= 0);
//                 
//                                                                                                                                              
//             
    if (size(attempt) > size(best)) //                                                                                                                 
        return false;
    else if (is_solved(attempt))
    {
        update_best(best, attempt) ;
        return true;
    }
    else if (no_legal_moves (attempt))
        return false;
//            
    //                                   
    //                                                                  
    //                                              
    else
    {
        attempt.push_back(attempt[c-1]) ;
        if (legal_moves('r', attempt [c-1]))
        {
            if (move_direction('r', attempt[c]))
            {
                if (!in_memory(attempt[c], attempt))
                    return depth_first(best, attempt, c+1);
                attempt.pop_back() ;
            }
            else
                return false ;
        }
        if (legal_moves('l', attempt [c-1]))
        {
            if (move_direction('l', attempt[c]))
            {
                if (!in_memory(attempt[c], attempt))
                    return depth_first(best, attempt, c+1);
                attempt.pop_back() ;
            }
            else
                return false ;
        }
        if (legal_moves('u', attempt [c-1]))
        {
            if (move_direction('u', attempt[c]))
            {
                if (!in_memory(attempt[c], attempt))
                    return depth_first(best, attempt, c+1);
                attempt.pop_back() ;
            }
            else
                return false ;
        }
        if (legal_moves('d', attempt [c-1]))
        {
            if (move_direction('d', attempt[c]))
            {
                if (!in_memory(attempt[c], attempt))
                    return depth_first(best, attempt, c+1);
                attempt.pop_back() ;
            }
            else
                return false ;
        }
    }
}

bool breadth_first (Puzzle start)
{//               
    assert (MAXLENGTH >= 0 && MAXWIDTH >= 0);
//                 
//                       
    vector<Candidate> c = {{start, -1}} ;
    int i = 0 ;
    while (i < csize(c) && !is_solved (c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if (legal_moves('r', p))
        {
            if (move_direction('r', p))
            {
                if (!in_BFSmemory(p, c))
                    {

                    }
            }
            else
                return false ;
    }

}

void clone_array (Cell goal [MAXLENGTH][MAXWIDTH], Cell source [MAXLENGTH][MAXWIDTH])
{//               
    assert (MAXLENGTH >= 0 && MAXWIDTH >= 0);
//                 
//                                               
    for (int i = 0; i < MAXLENGTH; i++)
        for (int j = 0; j < MAXWIDTH; j++)
            goal [i][j] = source [i][j] ;
}

void fill_best (vector<Puzzle>& best, Puzzle start)
{//               
    assert (MAXDEPTH >= 0);
//                 
//                                                                                                           
    for (int i = 0; i < MAXDEPTH; i++)
        best.push_back(start) ;
}

int main()
{
    ifstream infile ;
//                                  
    Cell startuniverse [MAXLENGTH][MAXWIDTH] ;
    vector<Puzzle> best ; //                                        
    vector<Puzzle> attempt ;
    Pos startworker ;
    fill_universe (startuniverse) ;
    while (!open_universe_file(infile))
        cout << "Could not open the file, try entering the name again." << endl;
    if (!read_universe_file(infile, startuniverse, startworker))
        cout << "Could not read the file, width or length exceeded their maximum or there was not a worker present." << endl;
    else
    {
        Puzzle start;
        clone_array (start.universe, startuniverse) ;
        start.worker = startworker ;
        fill_best (best, start) ;
        if (depth_first(best, attempt, 1))
        {
            cout << "The least amount of moves needed to solve the puzzle according to DFS is " << size (best) << endl;
            show_universe(startuniverse) ;
      //                           
        }
        else
            cout << "No solution with the current parameters and universe given for DFS." << endl;
  /*                                                        
         
                                                                                                                       
                                          
                                   
         
            
                                                                                    */
    }
    return 0;
}

