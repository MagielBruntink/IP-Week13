//                        
//                     

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;
const int MAX_DEPTH = 40;

enum Sokoban {Wall,Box,Empty,Worker,BOX,Dest,WORKER};

enum Direction {Up=0, Right, Down, Left};

struct Pos
{
    int col, row;
};

struct Puzzle
{
    Sokoban board [WIDTH][HEIGHT];
    Pos worker;
    Pos dimention;
};

struct Candidate
{
    Puzzle puzzle;
    int parent_index;
    int steps;
};

bool operator==(Puzzle a, Puzzle b)
{
    //                                             
    assert(a.dimention.row == b.dimention.row && a.dimention.col == b.dimention.col);
    //                                                     

    for(int row = 0; row < a.dimention.row ; row++)
    {
        for (int col = 0; col < a.dimention.col; col++)
        {
            if(a.board[row][col]!=b.board[row][col]) return false;
        }
    }
    return true;
}

void readfile(Puzzle& initial)
{
    //             
    assert(true);
    //                                                            

    ifstream infile;
    cout << "Enter name of file you want to open including filetype: ";
    string filename;
    cin >> filename;
    infile.open(filename);

    if(infile.is_open())
    {
        char c;
        infile.get(c);
        int row = 0;
        int col = 0;
        //              
        while(infile)
        {
            switch(c){
                case '*' : initial.board[row][col] = Wall; col++; break;
                case 32 :  initial.board[row][col] = Empty; col++; break;
                case '.' :  initial.board[row][col] = Dest; col++; break;
                case 'w': initial.board[row][col] = Worker;
                                initial.worker.col=col; initial.worker.row=row; col++; break;
                case 'W': initial.board[row][col] = WORKER;
                                initial.worker.col=col; initial.worker.row=row; col++; break;
                case 'b': initial.board[row][col] = Box; col++; break;
                case 'B': initial.board[row][col] = BOX; col++; break;
                case 10: row++; initial.dimention.col=col; col=0; break;
                default: cout << "somethings wrong" << endl; break;
            }
           infile.get(c);
        }
        initial.dimention.row=row;
    }
    else cout << "opening failed" << endl;

}

void show_object(Sokoban ob)
{
    //             
    assert(true);
    //                                                            
        switch(ob)
        {
        case Wall : cout << '*' ; break;
        case Empty : cout << ' ' ; break;
        case Dest : cout << '.' ; break;
        case Worker: cout << 'w' ; break;
        case WORKER : cout << 'W' ; break;
        case Box : cout << 'b' ; break;
        case BOX : cout << 'B' ; break;
        default : cout << "ERROR"; break;
        }
}

void show_board (Puzzle p)
{
    //             
    assert(true);
    //                                     

    //                               
    cout << endl;
    for(int row=0; row < p.dimention.row; row++)
    {
        for(int col=0; col < p.dimention.col; col++)
        {
            show_object(p.board[row][col]);
        }
        cout << endl;
    }
    //                                                          
    //                                                    
}

bool valid_step (Puzzle p, Direction dir)
{
    //                                  
    assert(true);
    //                                                           

    switch (dir)
    {
        case Up: {
            if(p.board[p.worker.row-1][p.worker.col]==Wall) return false;
            else if (p.board[p.worker.row-1][p.worker.col]==Box||p.board[p.worker.row-1][p.worker.col]==BOX)
            {
                if (p.board[p.worker.row-2][p.worker.col]==Wall || p.board[p.worker.row-2][p.worker.col]==Box || p.board[p.worker.row-2][p.worker.col] ==BOX ) return false;
                else return true;
            }
            else return true;
        break;
        }
        case Right:{
            if(p.board[p.worker.row][p.worker.col+1]==Wall) return false;
            else if (p.board[p.worker.row][p.worker.col+1]==Box||p.board[p.worker.row][p.worker.col+1]==BOX)
            {
                if (p.board[p.worker.row][p.worker.col+2]==Wall || p.board[p.worker.row][p.worker.col+2]==Box || p.board[p.worker.row][p.worker.col+2] ==BOX ) return false;
                else return true;
            }
            else return true;
        break;
        }
        case Down:{
            if(p.board[p.worker.row+1][p.worker.col]==Wall) return false;
            else if (p.board[p.worker.row+1][p.worker.col]==Box||p.board[p.worker.row+1][p.worker.col]==BOX)
            {
                if (p.board[p.worker.row+2][p.worker.col]==Wall || p.board[p.worker.row+2][p.worker.col]==Box || p.board[p.worker.row+2][p.worker.col] ==BOX ) return false;
                else return true;
            }
            else return true;
        break;
        }
        case Left: {
            if(p.board[p.worker.row][p.worker.col-1]==Wall) return false;
            else if (p.board[p.worker.row][p.worker.col-1]==Box||p.board[p.worker.row][p.worker.col-1]==BOX)
            {
                if (p.board[p.worker.row][p.worker.col-2]==Wall || p.board[p.worker.row][p.worker.col-2]==Box || p.board[p.worker.row][p.worker.col-2] ==BOX ) return false;
                else return true;
            }
            else return true;
        break;
        }
    }
}

void update_puzzle (Puzzle& p, Direction dir)
{
    //             
    assert(valid_step(p, dir));
    //                                                                          

    if(p.board[p.worker.row][p.worker.col] ==Worker) p.board[p.worker.row][p.worker.col]=Empty;
    else p.board[p.worker.row][p.worker.col]=Dest;

    Pos next;
    Pos next_box;
    next_box.row = -1; next_box.col = -1;

    switch (dir)
    {
        case Up: {
            next.row = p.worker.row -1;
            next.col = p.worker.col;
            if(p.board[next.row][next.col]==BOX || p.board[next.row][next.col]==Box){
                next_box.row = next.row-1;
                next_box.col = next.col;
            }
        break;
        }
        case Right:{
            next.row=p.worker.row;
            next.col = p.worker.col+1;
            if(p.board[next.row][next.col]==BOX || p.board[next.row][next.col]==Box){
                next_box.row = next.row;
                next_box.col = next.col+1;
            }

        break;
        }
        case Down:{
            next.row = p.worker.row+1;
            next.col = p.worker.col;
            if(p.board[next.row][next.col]==BOX || p.board[next.row][next.col]==Box){
                next_box.row = next.row+1;
                next_box.col = next.col;
            }
        break;
        }
        case Left: {
            next.row = p.worker.row;
            next.col = p.worker.col-1;
            if(p.board[next.row][next.col]==BOX || p.board[next.row][next.col]==Box){
                next_box.row = next.row;
                next_box.col = next.col-1;
            }
        break;
        }
    }

    switch(p.board[next.row][next.col])
    {
            case Empty: p.board[next.row][next.col] = Worker; break;
            case Box:{
                p.board[next.row][next.col] = Worker;
                if(p.board[next_box.row][next_box.col] ==Empty) p.board[next_box.row][next_box.col] = Box;
                else p.board[next_box.row][next_box.col] = BOX;
                break;
            }
            case BOX:{
                p.board[next.row][next.col] = WORKER;
                if(p.board[next_box.row][next_box.col] ==Empty) p.board[next_box.row][next_box.col] = Box;
                else p.board[next_box.row][next_box.col] = BOX;
                break;
            }
            case Dest: p.board[next.row][next.col] = WORKER; break;
    }

    p.worker.row = next.row;
    p.worker.col = next.col;
}

bool puzzle_finished (Puzzle p)
{
    //             
    assert(true);
    //                                                                       

    for (int row = 0;  row < p.dimention.row; row++)
    {
        for (int col = 0; col < p.dimention.col; col++) if(p.board[row][col]==Box) return false;
    }
    return true;
}

bool candidate_in_Candidates(vector<Candidate> Candidates, Candidate candidate)
{
     //             
    assert(true);
    //                                                                                               
    for(int i=0; i < Candidates.size(); i++) if(Candidates[i].puzzle == candidate.puzzle) return true;

    return false;
}

void breadth_first(vector<Candidate>& Candidates, Candidate& best)
{
     //             
    assert(true);
    //                                                 
    best.steps = 1000;
    int index = 0;
    if(puzzle_finished(Candidates[index].puzzle))
    {
        best = Candidates[index];
        return;
    }

    while (index < Candidates.size())
    {
        vector<Candidate> next_Candidates;
        for(int i=0; i < 4; i++)
        {
            Candidate next;
            next = Candidates[index];
            if(valid_step(next.puzzle, static_cast<Direction> (i)))
            {
                update_puzzle(next.puzzle, static_cast<Direction>( i));
                next.parent_index = index;
                next.steps ++;
                if(puzzle_finished(next.puzzle)){
                    best = next;
                    return;
                }
                next_Candidates.push_back(next);
                //                        
                //                                                                         
            }
            for(int i=0; i < next_Candidates.size(); i++)  if(!candidate_in_Candidates(Candidates, next_Candidates[i])) Candidates.push_back(next_Candidates[i]);
        }
        index++;
    }

}

bool keep_checking_this_candidate(vector<Candidate>& candidates, Candidate candidate)
{
     //             
    assert(true);
    //                                                                                                      
    for(int i=0; i < candidates.size(); i++)
    {
        if(candidates[i].puzzle == candidate.puzzle)
        {
            if(candidates[i].steps > candidate.steps)
            {
                candidates[i].steps = candidate.steps;
                return true;
            }
            else return false;
        }
    }

    candidates.push_back(candidate);
    return true;
}

void depth_first(vector<Candidate>& Candidates, Candidate candidate, Candidate& best)
{
     //             
    assert(true);
    //                                                 
    if(puzzle_finished(candidate.puzzle))
    {
        if(candidate.steps < best.steps) best = candidate;
        return;
    }

    if (!keep_checking_this_candidate(Candidates, candidate)) return;
    else if (candidate.steps > MAX_DEPTH) return;
    else
    {
        for(int i=0; i < 4; i++)
        {
                Candidate next;
                next = candidate;
                //                                         
                if(valid_step(next.puzzle, static_cast<Direction> (i)))
                {
                    update_puzzle(next.puzzle, static_cast<Direction>( i));

                    next.steps ++;
                   //                         
                    //                                        

                    depth_first(Candidates, next, best);
                }
        }
    }
}

int main()
{
    Candidate initial;
    readfile(initial.puzzle);
    cout << "Initial: " << endl;
    show_board(initial.puzzle);
    initial.parent_index = -1;
    initial.steps = 0;

    vector<Candidate> Candidates;

    Candidate best;

    /*
                                  
                                    
                                                                                            
                            */

    depth_first(Candidates, initial, best);
    cout << "Fastest solution: " << best.steps << endl;
    show_board(best.puzzle);

}

