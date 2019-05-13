//                      
//                  

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
using namespace std;

const int WIDTH= 8 ;  //           
const int HEIGHT= 6 ;  //            
typedef int Cell;        //                            
const Cell EMPTY= WIDTH* HEIGHT;

struct Pos{ int col, row;          //                      
} ;                               //                    

struct Worker{
    const char Empty                = 'w' ;
    const char Destination          = 'W' ; ;
} ;

struct Box{
    const char Empty             = 'b' ;
    const char Destination            = 'B' ;
} ;

struct Puzzle
{
    Cell board [WIDTH][HEIGHT];
    Pos open;
    Worker worker;
    Box box;
    const char WALL              = '*' ;
    const char EMPTY_CELL        = ' ' ;
    const char EMPTY_DEST        = '.' ;
};

struct Candidate
{ Puzzle candidate;
  int parent_candidate;
}  ;

char Puzzle0 [7][11] = {"**********","*        *", "*B      w*", "*  ****  *", "*        *", "**********"};
char Puzzle_1A [7][11] = {"**********", "*        *", "* .bw    *", "*  ****  *", "*        *", "**********"};
char Puzzle_1B [8][11] = {"**********", "*  w     *","*  b     *","*  .     *","*  ****  *","*        *","**********"};
char Puzzle_23 [8][8] = {"*******","*w   **","* bb  *","* *. .*","*     *","*******"};
char Puzzle_25 [8][8] = {"*******","**w  **","*  *  *","* bBb *","*  .  *","** . **","*******"};
char Puzzle_31 [8][8] = {"*******","***  **","*w .b**","*   b *","* *.  *","*     *","*******"};
char Puzzle_34 [9][10] = {"********","***   **","*.wb  **","*** b.**","*.**b **","* * . **","*b Bbb.*","*   .  *","********"};

//                                                                                         

void printPuzzle()
{
    cout << "There are 7 puzzles, choose one by entering a number between 1 and 7: " << endl;
    cout << "That puzzle will be printed." << endl;
    int num;
    cin >> num;
    //              
    assert (num >= 1 && num <= 7);
    //                
    //                                                                                                       
    switch(num)
    {
    case 1:
        for (int i = 0; i < sizeof (Puzzle0)/ sizeof(Puzzle0[0]); i++)
            cout << Puzzle0[i] << endl;
        break;
    case 2:
        for (int i = 0; i <sizeof (Puzzle_1A)/ sizeof(Puzzle_1A[0]); i++)
            cout << Puzzle_1A[i] << endl;
        break;
    case 3:
        for (int i = 0; i < sizeof (Puzzle_1B)/ sizeof(Puzzle_1B[0]); i++)
            cout << Puzzle_1B[i] << endl;
        break;
    case 4:
        for (int i = 0; i < sizeof (Puzzle_23)/ sizeof(Puzzle_23[0]); i++)
            cout << Puzzle_23[i] << endl;
        break;
    case 5:
        for (int i = 0; i < sizeof (Puzzle_25)/ sizeof(Puzzle_25[0]); i++)
            cout << Puzzle_25[i] << endl;
        break;
    case 6:
        for (int i = 0; i < sizeof (Puzzle_31)/ sizeof(Puzzle_31[0]); i++)
            cout << Puzzle_31[i] << endl;
        break;
    case 7:
        for (int i = 0; i < sizeof (Puzzle_34)/ sizeof(Puzzle_34[0]); i++)
            cout << Puzzle_34[i] << endl;
        break;
    }
}

bool puzzle_ready(Puzzle p)
{
    //              
    assert(true);
    //               
    for ( int i = 0 ; i < WIDTH ; i++)
        for( int j = 0 ; j <HEIGHT ; j++)
            if (p.board[i][j]=p.EMPTY_DEST) return false;

}

Puzzle move_empty(Puzzle p, Pos next)
{
    //             
    assert(true);
    //                 
    //                                                                               
    for ( int i = 0 ; i < WIDTH ; i++)
        for( int j = 0 ; j <HEIGHT ; j++)
            if (p.board[i][j]=p.worker.Empty)
            {
                p.board[i][j]=p.EMPTY_CELL;
                if (p.board[next.row][next.col]==p.EMPTY_CELL)
                    p.board[next.row][next.col]=p.worker.Empty;
                if (p.board[next.row][next.col]==p.EMPTY_DEST)
                    p.board[next.row][next.col]=p.worker.Destination;
            }

            else if (p.board[i][j]==p.worker.Destination)
            {
                p.board[i][j]=p.EMPTY_DEST;
                if (p.board[next.row][next.col]==p.EMPTY_CELL)
                    p.board[next.row][next.col]=p.worker.Empty;
                if (p.board[next.row][next.col]==p.EMPTY_DEST)
                    p.board[next.row][next.col]=p.worker.Destination;
            }
}
bool same( Puzzle a, Puzzle b )
{
    //             
    assert(true);
    //              
    //                   
    for(int i =0; i<WIDTH;i++)
        for(int j = 0 ; j <HEIGHT ; j++)
            if (a.board[i][j]!=b.board[i][j])
                return false;
    return true;
}
bool   puzzle_present( vector<Puzzle>& c,int i,Puzzle p)
{

    //            
    assert(i>=0);
    /*               
                                             
    */
    for( int j = 0; j < c.size(); j++ )
        if( same(c[i],p )) return true;
    return false;
}

ostream& operator<< (ostream& out, Puzzle c)
{//               
    assert (true) ;
    out << c.board   << endl ;
    return out ;
}

void   show_solution(Puzzle c)
{
    for(int i =0;i<WIDTH;i++)
    {
        for(int j = 0; j<HEIGHT;j++)
            cout<<c.board[i][j];
        cout<<"\n";
    }

}
bool   can_go_north(Puzzle p)
{
    //             
    assert(true);
    /*              
                                            
                                                          
                                                                                                 
    */
        for ( int i = 0 ; i < WIDTH ; i++)
            for( int j = 0 ; j <HEIGHT ; j++)
                if (p.board[i][j]==p.worker.Empty||p.board[i][j]==p.worker.Destination) //           
                {
                    if (p.board[i-1][j]==p.WALL)
                        return false;
                    if (p.board[i-1][j]==p.box.Destination||p.board[i-1][j]==p.box.Empty)
                       for (;i >0;i--)
                       {
                           if (p.board[i-1][j]==p.WALL)
                            return false;
                           if (p.board[i-1][j]==p.EMPTY_CELL||p.board[i-1][j]==p.EMPTY_DEST)
                            return true;
                       }
                }
    return true;
}

Pos north(Puzzle p)
{
        for ( int i = 0 ; i < WIDTH ; i++)
            for( int j = 0 ; j <HEIGHT ; j++)
                if (p.board[i][j]==p.worker.Empty||p.board[i][j]==p.worker.Destination)
                {
                    return i+1;
                    northrow=j;
                }
}
bool   can_go_south(Puzzle p)
{
    //             
    assert(true);
    /*              
                           
    */
        for ( int i = 0 ; i < WIDTH ; i++)
            for( int j = 0 ; j <HEIGHT ; j++)
                if (p.board[i][j]==p.worker.Empty||p.board[i][j]==p.worker.Destination) //           
                {
                    if (p.board[i+1][j]==p.WALL)
                        return false;
                    if (p.board[i+1][j]==p.box.Destination||p.board[i+1][j]==p.box.Empty)
                       for (;i <WIDTH;i++)
                       {
                           if (p.board.[i+1][j]==p.WALL)
                            return false;
                           if (p.board.[i+1][j]==p.EMPTY_CELL||p.board.[i+1][j]==p.EMPTY_DEST)
                            return true;
                       }
                }
    return true;
}
Pos south(Puzzle p)
{
        for ( int i = 0 ; i < WIDTH ; i++)
            for( int j = 0 ; j <HEIGHT ; j++)
                if (p.board[i][j]==p.worker.Empty||p.board[i][j]==p.worker.Destination)
                {
                    south.col=i+1;
                    south.row=j;
                }
}
bool   can_go_west(Puzzle p)
{
    //             
    assert(true);
    /*              
                           
    */
        for ( int i = 0 ; i < WIDTH ; i++)
            for( int j = 0 ; j <HEIGHT ; j++)
                if (p.board[i][j]==p.worker.Empty||p.board[i][j]==p.worker.Destination) //           
                {
                    if (p.board[i][j-1]==p.WALL)
                        return false;
                    if (p.board[i][j-1]==p.box.Destination||p.board[i][j-1]==p.box.Empty)
                       for (;j >0;j--)
                       {
                           if (p.board.[i][j-1]==p.WALL)
                            return false;
                           if (p.board.[i][j-1]==p.EMPTY_CELL||p.board.[i][j-1]==p.EMPTY_DEST)
                            return true;
                       }
                }
    return true;
}
Pos west (Puzzle p)
{
        for ( int i = 0 ; i < WIDTH ; i++)
            for( int j = 0 ; j <HEIGHT ; j++)
                if (p.board[i][j]==p.worker.Empty||p.board[i][j]==p.worker.Destination)
                {
                    west.col=i;
                    west.row=j-1;
                }
}
bool   can_go_east(Puzzle p)
{
    //             
    assert(true);
    /*              
                           
    */
        for ( int i = 0 ; i < WIDTH ; i++)
            for( int j = 0 ; j <HEIGHT ; j++)
                if (p.board[i][j]==p.worker.Empty||p.board[i][j]==p.worker.Destination) //           
                {
                    if (p.board[i][j+1]==p.WALL)
                        return false;
                    if (p.board[i][j+1]==p.box.Destination||p.board[i][j+1]==p.box.Empty)
                       for (;j <HEIGHT;j++)
                       {
                           if (p.board.[i][j+1]==p.WALL)
                            return false;
                           if (p.board.[i][j+1]==p.EMPTY_CELL||p.board.[i][j+1]==p.EMPTY_DEST)
                            return true;
                       }
                }
    return true;
}
Pos east (Puzzle p)
{
        for ( int i = 0 ; i < WIDTH ; i++)
            for( int j = 0 ; j <HEIGHT ; j++)
                if (p.board[i][j]==p.worker.Empty||p.board[i][j]==p.worker.Destination)
                {
                    east.col=i;
                    east.row=j+1;
                }
}

void show_path (vector<Candidate> C,int i)
{
    if (i< 0){ return 0;}
    else
        [show_path (C, C[i].parent_candidate) ; show (C[i].candidate)

}
void bf_solve(Puzzlestart)
{  vector<Candidate> c= {{start,-1}} ;
    int i = 0 ;
    while(i <size(c) && !puzzle_ready(c[i].candidate))
        {  Puzzle p = c[i].candidate;
            if(can_go_north(p )) tries(c, i, north(p)) ;
            if(can_go_south(p )) tries(c, i, south(p)) ;
            if(can_go_west(p ))  tries(c, i, west (p)) ;
            if(can_go_east(p))   tries(c, i, east (p)) ;
            i = i+1 ;
        }
        if(i <size(c))
        show_path(c, i) ;
}

void bf_tries(vector<Candidate>&  c, inti, Posnext)
{   Puzzle p = c[i].candidate ;
    Puzzle newp= move_empty(p, next);
    Candidate newc=  {newp   ,  i}  ;
    if (!puzzle_present(c,  i,  newp   ))
        c.push_back(newc) ;
}

void df_solve( vector<Puzzle>& attempt
              , vector<Puzzle>& shortest, intmax_depth)
{  const int CURRENT= size(attempt) ;
    const int BEST    = size(shortest) ;
    Puzzle p = attempt[CURRENT-1]  ;
    if(BEST > 0 && CURRENT>= BEST)      { return; }
    else if(CURRENT> max_depth+1)       { return; }
    else if(puzzle_ready(p)) { shortest= attempt; return; }
    if(can_go_north(p)) tries(attempt, north(p), shortest,  max_depth)  ;
    if(can_go_south(p)) tries(attempt, south(p), shortest,  max_depth) ;
    if(can_go_west(p))  tries(attempt, west  (p), shortest,  max_depth) ;
    if(can_go_east(p)) tries(attempt, east(p), shortest,  max_depth) ;
}

void df_tries( vector<Puzzle>& attempt,  Pos next
           , vector<Puzzle>& shortest, intmax_depth)
{  Puzzle p = attempt[size (attempt)-1]  ;
   Puzzle newp= move_empty(p, next) ;
   if (!puzzle_present(newp   , attempt))
   {   attempt.push_back(newp   ) ;   //        
       solve(attempt, shortest,  max_depth) ;
       attempt.pop_back() ;        //       
   }
}

int main()
{
    int num;
    cout << "Puzzle 1 = Puzzle0\n"
         << "Puzzle 2 = Puzzle_1A\n"
         << "Puzzle 3 = Puzzle_1B\n"
         << "Puzzle 4 = Puzzle_23\n"
         << "Puzzle 5 = Puzzle_25\n"
         << "Puzzle 6 = Puzzle_31\n"
         << "Puzzle 7 = Puzzle_34\n" << endl;

    while (num != 0)
         printPuzzle();

        return 0;
}

