//                                                           
#include <iostream>
#include<vector>
#include<cassert>
using namespace std;
const int MAX_ROWS = 20;
const int MAX_COLUMNS= 20;

enum Cell{empty_cell=0, empty_destination, box_on_empty, box_on_destination, worker_on_empty, worker_on_destination, wall};
int map[MAX_ROWS][MAX_COLUMNS]=
{
{6,6,6,6,6,6,6,6,6,6},
{6,0,0,0,0,0,0,0,0,6},
{6,3,0,0,0,0,0,0,4,6},
{6,0,0,6,6,6,6,0,0,6},
{6,0,0,0,0,0,0,0,0,6},
{6,6,6,6,6,6,6,6,6,6},
};

struct Pos{
int col, row;
};

struct Puzzle
{
int map[MAX_ROWS][MAX_COLUMNS];
Pos position;
};

struct Candidate{
Puzzle candidate;
int parent_candidate;
};

bool puzzle_ready(Puzzle p){}//                       
bool puzzle_present(vector<Candidate>& c, int i, Puzzle p){}//                        
void show_path(vector<Candidate>&c,int i){}//                        
bool   puzzle_present (Puzzle p, vector<Puzzle>& c){} //                       
void   show_solution  (vector<Puzzle>&c){}//                       

bool can_go_north(Puzzle p){
if(map[p.position.row-1][p.position.col] == empty_cell || map[p.position.row-1][p.position.col] == empty_destination)
    return true;
}

bool can_go_east(Puzzle p){
if(map[p.position.row][p.position.col+1] == empty_cell || map[p.position.row][p.position.col+1] == empty_destination)
    return true;
}

bool can_go_south(Puzzle p){
if(map[p.position.row+1][p.position.col] == empty_cell || map[p.position.row+1][p.position.col] == empty_destination)
    return true;
}

bool can_go_west(Puzzle p){
if(map[p.position.row][p.position.col-1] == empty_cell || map[p.position.row][p.position.col-1] == empty_destination)
    return true;
}

Pos north(Puzzle p){
    for(int r=0; r<MAX_ROWS; r++){
        for (int c=0; c<MAX_COLUMNS; c++){
            if(can_go_north(p)){
                    map[r][c]=map[r-1][c];
        }
    }
 }
 return p.position;
}

Pos east(Puzzle p){
    for(int r=0; r<MAX_ROWS; r++){
        for (int c=0; c<MAX_COLUMNS; c++){
            if(can_go_east(p)){
                    map[r][c]=map[r][c+1];
      }
     }
   }
 return p.position;
}

Pos south(Puzzle p){
    for(int r=0; r<MAX_ROWS; r++){
        for (int c=0; c<MAX_COLUMNS; c++){
            if(can_go_south(p)){
                    map[r][c]=map[r+1][c];
       }
     }
   }
 return p.position;
}

Pos west(Puzzle p){
if(can_go_west(p)){
        for(int r=0; r<MAX_ROWS; r++){
        for (int c=0; c<MAX_COLUMNS; c++){
            if(can_go_west(p)){
                    map[r][c]=map[r][c-1];
        }
      }
    }
   }
 return p.position;
}

/*                                    
                                               

  
 */

bool show_map(){
	//             
	assert(true);
	//                                     
for(int row=0; row<MAX_ROWS; row++){
    for(int col=0; col<MAX_COLUMNS; col++){
        switch(map[row][col]){
        case empty_cell:
            cout<<" ";
            break;
        case empty_destination:
            cout<<'.';
            break;
        case box_on_empty:
            cout<<'b';
            break;
        case box_on_destination:
            cout<<'B';
            break;
        case worker_on_empty:
            cout<<'w';
            break;
        case worker_on_destination:
            cout<<'W';
        default:
            cout<<'*';
            break;
        return true;
        }
    }cout<<endl;
}
}

void tries_breadth(vector<Candidate>&c, int i, Pos next)
{
	//            
	assert(true);
	Puzzle p=c[i].candidate;
	Puzzle newp= move_box(p,next);
	Candidate newc= {newp,i};
	if(!puzzle_present(c,i,newp))
    c.push_back(newc);
}

void solve_breadth_first(Puzzle start){
	//             
	assert(true);
	//                                                                                                              
    vector<Candidate> c={{start,-1}};
    int i=0;
    while(i<c.size()&& !puzzle_ready (c[i].candidate))
    {
        Puzzle p= c[i].candidate;
        if (can_go_north (p)) tries_breadth(c, i, north(p));
        if (can_go_south (p)) tries_breadth(c, i, south(p));
        if (can_go_west  (p)) tries_breadth(c, i,  west(p));
        if (can_go_east  (p)) tries_breadth(c, i,  east(p));
        i++;
    }
    if (i<c.size())
        show_path(c,i);
}

void tries_depth( vector<Puzzle>& attempt,  Pos next, vector<Puzzle>& shortest, int max_depth )
{
	//             
	assert(true);
     Puzzle p    = attempt[p.size(attempt)-1] ;
     Puzzle newp = move_empty (p, next) ;
     if (!puzzle_present (newp, attempt))
     {
         attempt.push_back (newp) ;
         solve_depth_first() (attempt, shortest, max_depth) ;
         attempt.pop_back () ;
     }
}

void solve_depth_first( vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth )
	//             
	assert(true);
	//                                                                                                              
{   const int CURRENT = size (attempt) ;
    const int BEST    = size (shortest) ;
    Puzzle p          = attempt[CURRENT-1] ;
    if (BEST > 0 && CURRENT >= BEST)      { return ; }
    else if (CURRENT > max_depth+1)       { return ; }
    else if (puzzle_ready (p)) { shortest= attempt ; return ; }
    if (can_go_north (p))
    {
        tries_depth(attempt, north (p), shortest, max_depth) ;
    }
    if (can_go_east(p))
    {
        tries_depth(attempt, east(p), shortest, max_depth);
    }
    if (can_go_south(p)){
        tries_depth(attempt,south(p),shortest,max_depth);
    }
    if (can_go_west(p))
    {
        tries_depth(attempt,south(p),shortest,max_depth);
    }
}

int main()
{
    show_map();
    solve_breadth_first();
    solve_depth_first();

    return 0;
}

