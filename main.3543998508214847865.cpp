/*                                                                             
                                                                                                        */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

enum Cell {wall=0, emptycell, emptydest, w, W, b, B};

const int width=10;
const int height=6;

struct Pos
{
    int col, row;
};

struct Puzzle
{
    Cell board[height][width];
    Pos worker;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

bool operator== (const Pos& a, const Pos& b)
{//             
    assert(true);
/*                                                                                     
*/
    if(a.col==b.col && a.row==b.row)
        return 1;
    else
        return 0;
}

bool operator== (const Puzzle& a, const Puzzle& b)
{//             
    assert(true);
/*                                                                                   
*/
    if(a.board==b.board && a.worker==b.worker)
        return 1;
    else
        return 0;
}

bool operator== (const Candidate& a, const Candidate& b)
{//             
    assert(true);
/*                                                                                      
*/
    if(a.candidate==b.candidate && a.parent_candidate==b.parent_candidate)
        return 1;
    else
        return 0;
}

Puzzle challenge1            ={{{wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
                                {wall, emptycell, emptycell, emptycell, emptycell, emptycell, emptycell, emptycell, emptycell, wall},
                                {wall, emptycell, emptydest, b, w, emptycell, emptycell, emptycell, emptycell, wall},
                                {wall, emptycell, emptycell, wall, wall, wall, wall, emptycell, emptycell, wall},
                                {wall, emptycell, emptycell, emptycell, emptycell, emptycell, emptycell, emptycell, emptycell, wall},
                                {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall}}, {4, 2}};
/*
                                                                         
                                                                                     
                                                                                  
                                                                                             
                                                                                                  
                                                                                    
*/

void show_cell(Cell c[height][width])
{//              
    assert(true);
/*                                                          
*/
    for(int row=0; row<height; row++)
    {
        for(int col=0; col<width; col++)
        {
            if(c[row][col]==0)
                cout << '*';
            if(c[row][col]==1)
                cout << ' ';
            if(c[row][col]==2)
                cout << '.';
            if(c[row][col]==3)
                cout << 'w';
            if(c[row][col]==4)
                cout << 'W';
            if(c[row][col]==5)
                cout << 'b';
            if(c[row][col]==6)
                cout << 'B';
        }
        cout << endl;
    }
}

bool can_go_north(Puzzle p)
{//                                            
    assert(p.worker.col<width && p.worker.row<height);
/*                                                                                                                                                    
*/
    if(p.board[p.worker.row-1][p.worker.col]==1 || p.board[p.worker.row-1][p.worker.col]==2)
        return true;
    else if((p.board[p.worker.row-1][p.worker.col]==5 || p.board[p.worker.row-1][p.worker.col]==6) && (p.board[p.worker.row-2][p.worker.col]==1 || p.board[p.worker.row-2][p.worker.col]==2))
        return true;
    else
        return false;
}

bool can_go_east(Puzzle p)
{//                                            
    assert(p.worker.col<width && p.worker.row<height);
/*                                                                                                                                                  
*/
    if(p.board[p.worker.row][p.worker.col+1]==1 || p.board[p.worker.row][p.worker.col+1]==2)
        return true;
    else if((p.board[p.worker.row][p.worker.col+1]==5 || p.board[p.worker.row][p.worker.col+1]==6) && (p.board[p.worker.row][p.worker.col+2]==1 || p.board[p.worker.row][p.worker.col+2]==2))
        return true;
    else
        return false;
}

bool can_go_south(Puzzle p)
{//                                            
    assert(p.worker.col<width && p.worker.row<height);
/*                                                                                                                                                    
*/
    if(p.board[p.worker.row+1][p.worker.col]==1 || p.board[p.worker.row+1][p.worker.col]==2)
        return true;
    else if((p.board[p.worker.row+1][p.worker.col]==5 || p.board[p.worker.row+1][p.worker.col]==6) && (p.board[p.worker.row+2][p.worker.col]==1 || p.board[p.worker.row+2][p.worker.col]==2))
        return true;
    else
        return false;
}

bool can_go_west(Puzzle p)
{//                                            
    assert(p.worker.col<width && p.worker.row<height);
/*                                                                                                                                                  
*/
    if(p.board[p.worker.row][p.worker.col-1]==1 || p.board[p.worker.row][p.worker.col-1]==2)
        return true;
    else if((p.board[p.worker.row][p.worker.col-1]==5 || p.board[p.worker.row][p.worker.col-1]==6) && (p.board[p.worker.row][p.worker.col-2]==1 || p.board[p.worker.row][p.worker.col-2]==2))
        return true;
    else
        return false;
}

Pos north(Puzzle p)
{//                                            
    assert(p.worker.col<width && p.worker.row<height);
/*                                                                      
*/
    Pos a={p.worker.col, p.worker.row-1};
    return a;
}

Pos east(Puzzle p)
{//                                            
    assert(p.worker.col<width && p.worker.row<height);
/*                                                                     
*/
    Pos a={p.worker.col+1, p.worker.row};
    return a;
}

Pos south(Puzzle p)
{//                                            
    assert(p.worker.col<width && p.worker.row<height);
/*                                                                      
*/
    Pos a={p.worker.col, p.worker.row+1};
    return a;
}

Pos west(Puzzle p)
{//                                            
    assert(p.worker.col<width && p.worker.row<height);
/*                                                                     
*/
    Pos a={p.worker.col-1, p.worker.row};
    return a;
}

bool puzzle_ready(Puzzle p)
{//              
    assert(true);
/*                                                                                                      
*/
    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++)
            if(p.board[i][j]==2 || p.board[i][j]==5)
                return false;
    return true;
}

Puzzle move_worker(Puzzle p, Pos next)
{//                                                                                                                                                                                                
//                                                                                    
    assert(p.worker.col<width && p.worker.row<height);
/*                                                                                                            
*/
    //                                                     
    Puzzle r = p;
    r.worker = next;
    Cell value;
    int dir=0;

    if(next.row<p.worker.row && next.col==p.worker.col)     //            
        dir=0;
    else if(next.row==p.worker.row && next.col>p.worker.col)     //           
        dir=1;
    else if(next.row>p.worker.row && next.col==p.worker.col)     //            
        dir=2;
    else if(next.row==p.worker.row && next.col<p.worker.col)     //           
        dir=3;

    if(r.board[next.row][next.col]==5 || r.board[next.row][next.col]==6)        //                                   
        switch(dir)
        {   case 0:     if(r.board[next.row-1][next.col]==2)                //                 
                            r.board[next.row-1][next.col]=static_cast<Cell>(6);
                        else if(r.board[next.row-1][next.col]==1)
                            r.board[next.row-1][next.col]=static_cast<Cell>(5);
                        break;
            case 1:     if(r.board[next.row][next.col+1]==2)                //                
                            r.board[next.row][next.col+1]=static_cast<Cell>(6);
                        else if(r.board[next.row][next.col+1]==1)
                            r.board[next.row][next.col+1]=static_cast<Cell>(5);
                        break;
            case 2:     if(r.board[next.row+1][next.col]==2)                //                 
                            r.board[next.row+1][next.col]=static_cast<Cell>(6);
                        else if(r.board[next.row+1][next.col]==1)
                            r.board[next.row+1][next.col]=static_cast<Cell>(5);
                        break;
            case 3:     if(r.board[next.row][next.col-1]==2)                //                
                            r.board[next.row][next.col-1]=static_cast<Cell>(6);
                        else if(r.board[next.row][next.col-1]==1)
                            r.board[next.row][next.col-1]=static_cast<Cell>(5);
                        break;
        }

    if(r.board[next.row][next.col]==1 || r.board[next.row][next.col]==5)        //                                         
        r.board[next.row][next.col]=static_cast<Cell>(3);
    else
        r.board[next.row][next.col]=static_cast<Cell>(4);                                         //                                         

    if(p.board[p.worker.row][p.worker.col]==3)              //                                       
        r.board[p.worker.row][p.worker.col]=static_cast<Cell>(1);
    else
        r.board[p.worker.row][p.worker.col]=static_cast<Cell>(2);

    return r;
}

bool puzzle_present(vector<Candidate> c, Puzzle newp)
{//              
    assert(true);
/*                                                                                              
*/
    for(int counter=0; counter<c.size(); counter++)
        if(c[counter].candidate==newp)
            return true;
    return false;
}

void tries(vector<Candidate>& c, int i, Pos next)
{//              
    assert(true);
/*                                                                                                                                                                                         
*/
    Puzzle p=c[i].candidate;
    Puzzle newp = move_worker(p, next);
    Candidate newc = {newp, i};
    if(!puzzle_present(c, newp))
        c.push_back(newc);
}

void show_path(vector<Candidate> c, int i)
{//                                                                      
    assert(c.size()>0);
/*                                                               
*/
    int p=i;
    vector<Candidate> path;
    path.push_back(c[0]);
    while(p!=0)
    {
        path.push_back(c[p]);
        p=c[p].parent_candidate;
    }
    for(int counter=0; counter<path.size(); counter++)
    {
        show_cell(path[counter].candidate.board);
        cout << endl;
    }
}

void breadthsolve(Puzzle start)
{//                                                                              
    assert(true);
/*                                                                              
*/
    vector<Candidate> c;
    c.push_back({start, -1});
    int i=0;
    while(i<c.size() &&
          !puzzle_ready(c[i].candidate))
    {
        Puzzle p = c[i].candidate;
        if(can_go_north(p))
            tries(c, i, north(p));
        if(can_go_south(p))
            tries(c, i, south(p));
        if(can_go_west(p))
            tries(c, i, west(p));
        if(can_go_east(p))
            tries(c, i, east(p));
        i++;
    }
    cout << "Found solution at option " << i << endl;
    if (i<c.size())
        show_path(c, i);
}

void depth_show_path(vector<Puzzle> path)
{//              
    assert(true);
/*                                                     
*/
    for(int counter=0; counter<path.size(); counter++)
    {
        show_cell(path[counter].board);
        cout << endl;
    }
}

bool depth_puzzle_present(vector<Puzzle>& attempt, Puzzle p)
{//              
    assert(true);
/*                                                                                           
*/
    for(int counter=0; counter<attempt.size(); counter++)
        if(attempt[counter]==p)
            return true;
    return false;
}

void depthsolve( vector<Puzzle>& attempt
                ,vector<Puzzle>& shortest, int max_depth)
{//                                                                                                              
    assert(true);
/*                                                                                                                                                           
*/
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle p=attempt[CURRENT-1];
    if(puzzle_ready(p))
    {
        if(BEST > CURRENT || BEST==0){
            shortest=attempt;}
        return;
    }
    if(BEST>0 && CURRENT>=BEST)
        return;
    else if(CURRENT > max_depth+1)
        return;

    //                                                                                                                                                                
    Puzzle newp;
    if(can_go_north(p))
    {
        newp = move_worker(p, north(p));
        if(!depth_puzzle_present(attempt, newp))
        {
            attempt.push_back(newp);
            depthsolve(attempt, shortest, max_depth);
            attempt.pop_back();
        }
    }
    if(can_go_east(p))
    {
        newp = move_worker(p, east(p));
        if(!depth_puzzle_present(attempt, newp))
        {
            attempt.push_back(newp);
            depthsolve(attempt, shortest, max_depth);
            attempt.pop_back();
        }
    }
    if(can_go_south(p))
    {
        newp = move_worker(p, south(p));
        if(!depth_puzzle_present(attempt, newp))
        {
            attempt.push_back(newp);
            depthsolve(attempt, shortest, max_depth);
            attempt.pop_back();
        }
    }
    if(can_go_west(p))
    {
        newp = move_worker(p, west(p));
        if(!depth_puzzle_present(attempt, newp))
        {
            attempt.push_back(newp);
            depthsolve(attempt, shortest, max_depth);
            attempt.pop_back();
        }
    }
}

int main()
{
    vector<Puzzle> shortest;
    vector<Puzzle> chal1;
    chal1.push_back(challenge1);

    cout << "Breadth solve: " << endl;
    breadthsolve(challenge1);
    cout << "Depth solve:" << endl;
    depthsolve(chal1, shortest, 5);
    depth_show_path(shortest);
    return 0;
}

