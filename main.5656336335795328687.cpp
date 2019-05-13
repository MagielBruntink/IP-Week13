#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
//                                        
using namespace std;
const int maxcolumn=10;
const int maxrow=10;

/*                                                                                                                      */
struct Position
{int column,row;
};

struct Puzzle
{char board[maxcolumn][maxrow]; //                                                                                                                                                           
Position workerplace;
int truecolumn;//                                          
int truerow;//               
};
struct Candidate
{Puzzle candidate;
int generation;
};

Puzzle get_puzzle(string filename) //               
{
    assert(true);
    Puzzle readout;
    readout.truecolumn=0; //                
    ifstream infile;
    infile.open(filename); //         
    char lastchar=infile.get(); //                                                    
    int rownumber=0;//                                        
    int columnnumber=0;//               
    while(infile)
    {
        while(lastchar!='\n')//              
        {
            readout.board[columnnumber][rownumber]=lastchar; //                      
            if(lastchar=='w' || lastchar=='W')
                readout.workerplace={columnnumber,rownumber};//                                                              
            columnnumber++; //                                              
            lastchar=infile.get();
        }
        lastchar=infile.get(); //                      
        if (readout.truecolumn==0)
            readout.truecolumn=columnnumber;//                                                                                                               
        columnnumber=0; //                                                      
        rownumber++;//                              
    }
    readout.truerow=rownumber;//                                                           
    infile.clear();
    infile.close();
    return readout;
}//                                                                           

void show_field(Puzzle situation) //                                                                                                                                                                                
{
    assert(situation.truerow>0&&situation.truecolumn>0);
    for (int row=0;row<situation.truerow;row++) //                               
    {
        for (int column=0; column<situation.truecolumn;column++) //                                    
            cout<<situation.board[column][row];
        cout<<"\n";//                                    
    }
}//                                                                              

bool puzzle_ready(Puzzle attempt)
{
    assert(attempt.truerow>0&&attempt.truecolumn>0);
    for (int row=0;row<attempt.truerow;row++) //                               
    {
        for (int column=0; column<attempt.truecolumn;column++) //                                    
            {
            if (attempt.board[column][row]=='.'|| attempt.board[column][row]=='W')
                return false;
            }
    }
    return true;
}//                                                                                                                     
bool can_go_north(Puzzle attempt)
{
    assert(true);
    if (attempt.board[attempt.workerplace.column][attempt.workerplace.row+1]==' ' || attempt.board[attempt.workerplace.column][attempt.workerplace.row+1]=='.' ) //                                                  
        return true;
    if (attempt.board[attempt.workerplace.column][attempt.workerplace.row+1]=='b' || attempt.board[attempt.workerplace.column][attempt.workerplace.row+1]=='B' ) //        
        if (attempt.board[attempt.workerplace.column][attempt.workerplace.row+2]==' ' || attempt.board[attempt.workerplace.column][attempt.workerplace.row+2]=='.') //                                                    
            return true;
    return false;//                                                                                                            
}//                                                                                                                                                                                                       
bool can_go_south(Puzzle attempt)
{
    assert(true);
    if (attempt.board[attempt.workerplace.column][attempt.workerplace.row-1]==' ' || attempt.board[attempt.workerplace.column][attempt.workerplace.row-1]=='.' ) //                                                   
        return true;
    if (attempt.board[attempt.workerplace.column][attempt.workerplace.row-1]=='b' || attempt.board[attempt.workerplace.column][attempt.workerplace.row-1]=='B' ) //        
        if (attempt.board[attempt.workerplace.column][attempt.workerplace.row-2]==' ' || attempt.board[attempt.workerplace.column][attempt.workerplace.row-2]=='.') //                                                    
            return true;
    return false;//                                                                                                            
}//                                                                                                                                                                                                       

bool can_go_east(Puzzle attempt)
{
    assert(true);
    if (attempt.board[attempt.workerplace.column+1][attempt.workerplace.row]==' ' || attempt.board[attempt.workerplace.column+1][attempt.workerplace.row]=='.' ) //                                                  
        return true;
    if (attempt.board[attempt.workerplace.column+1][attempt.workerplace.row]=='b' || attempt.board[attempt.workerplace.column+1][attempt.workerplace.row]=='B' ) //        
        if (attempt.board[attempt.workerplace.column+2][attempt.workerplace.row]==' ' || attempt.board[attempt.workerplace.column+2][attempt.workerplace.row]=='.') //                                                    
            return true;
    return false;//                                                                                                            
}//                                                                                                                                                                         

bool can_go_west(Puzzle attempt)
{
    assert(true);
    if (attempt.board[attempt.workerplace.column-1][attempt.workerplace.row]==' ' || attempt.board[attempt.workerplace.column-1][attempt.workerplace.row]=='.' ) //                                                  
        return true;
    if (attempt.board[attempt.workerplace.column-1][attempt.workerplace.row]=='b' || attempt.board[attempt.workerplace.column-1][attempt.workerplace.row]=='B' ) //        
        if (attempt.board[attempt.workerplace.column-2][attempt.workerplace.row]==' ' || attempt.board[attempt.workerplace.column-2][attempt.workerplace.row]=='.') //                                                    
            return true;
    return false;//                                                                                                            
}//                                                                                                                                                                       

bool puzzle_present_breadth(vector<Candidate> attempt, int i, Puzzle nexttry)
{
    assert(i<attempt.size());//                              
    for (int number=0; number<=i; number++) //                
        if(attempt[i].candidate.board==nexttry.board)//                               
            return true;//            
    return false;//                                      
}//                                                                                
void next_move(Puzzle& current, Position next)
{
    assert(next.row<current.truerow&& next.column<current.truecolumn && next.row>0&&next.column>0);//                                                                      
    if (current.board[current.workerplace.column][current.workerplace.row]=='w') //                      
        current.board[current.workerplace.column][current.workerplace.row]=' ';
    else
        current.board[current.workerplace.column][current.workerplace.row]='.';//                                                           
    if (current.board[next.column][next.row]==' ')                                //                                                                
        current.board[next.column][next.row]='w'; //                     
    else if (current.board[next.column][next.row]=='.')
        current.board[next.column][next.row]='W'; //                    
    else if (current.board[next.column][next.row]=='b')
    {
        current.board[next.column][next.row]='w'; //                  
        if (current.board[2*next.column-current.workerplace.column][2*next.row-current.workerplace.row]==' ')
            current.board[2*next.column-current.workerplace.column][2*next.row-current.workerplace.row]='b';//                                        
        else
            current.board[2*next.column-current.workerplace.column][2*next.row-current.workerplace.row]='B';//                                                                                                                 
    }
    else if (current.board[next.column][next.row]=='B')
    {
        current.board[next.column][next.row]='W';//                 
        if (current.board[2*next.column-current.workerplace.column][2*next.row-current.workerplace.row]==' ')
            current.board[2*next.column-current.workerplace.column][2*next.row-current.workerplace.row]='b';
        else
            current.board[2*next.column-current.workerplace.column][2*next.row-current.workerplace.row]='B';//                                                                                       
    }
    current.workerplace.row=next.row; //                         
    current.workerplace.column=next.column;
}//                                                                                                                                                            

void try_breadth(vector<Candidate>& attempt, int i, Position next)
{
    assert(i<attempt.size());
    Puzzle current = attempt[i].candidate;
    next_move(current,next);
    Candidate newattempt ={current, i};
    if (!puzzle_present_breadth(attempt,i,current))
        attempt.push_back(newattempt);
}//                                                                                                                                                   
Position north(Puzzle current)
{
    return {current.workerplace.column,current.workerplace.row+1};
}//                                                                                                                                                  
Position south(Puzzle current)
{
    return {current.workerplace.column,current.workerplace.row-1};
}//                                                                                                                                                  
Position east(Puzzle current)
{
    return {current.workerplace.column+1,current.workerplace.row};
}//                                                
Position west(Puzzle current)
{
    return {current.workerplace.column-1,current.workerplace.row};
}//                                                
void show_path_breadth(vector<Candidate> attempt, int& steps_needed)
{
    assert(true);
    steps_needed=0;
    int i=attempt[attempt.size()-1].generation;
    while (i>-1)
    {
        steps_needed++;
        show_field(attempt[i].candidate);
        i=attempt[i].generation;
    }
}//                                                                                                                  
void show_path_depth(vector<Puzzle> best)
{
    assert(true);
    for (int generation=0; generation<best.size(); generation++)
        show_field(best[generation]);
}//                                                         
void solve_breadth(Puzzle start_condition)//                                                                                                                                                                                                                      
{
    assert(true);
    vector<Candidate> attempt = {{start_condition,-1}};//
    int i = 0;
    while (i<attempt.size() && !puzzle_ready(attempt[i].candidate))
    {
        Puzzle active = attempt[i].candidate;
        if (can_go_north(active))
            try_breadth (attempt, i, north(active));
        if (can_go_south(active))
            try_breadth (attempt, i, south(active));
        if (can_go_east(active))
            try_breadth (attempt, i, east(active));
        if (can_go_west(active))
            try_breadth (attempt, i, west(active));
        i++;
    }
    if (i<attempt.size())
    {
        int steps_needed;
        show_path_breadth(attempt,steps_needed);
        cout<<"\n total steps needed:"<<steps_needed<<"\n";
    }
}//                                                                                                                                                                   
bool puzzle_present_depth(Puzzle nexttry, vector<Puzzle> attempt)
{
    assert(true);
    for (int number=0; number<attempt.size(); number++)//                
        if(attempt[number].board==nexttry.board)//                           
            return true;
    return false;
}//                                                                                                    

void solve_depth(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);//                                               
void try_depth(vector<Puzzle>& attempt,Position next, vector<Puzzle>& shortest, int max_depth)//                                                             
{
    assert(true);
    Puzzle active = attempt[attempt.size()-1];
    next_move(active,next);
    if(!puzzle_present_depth(active,attempt))
    {
        attempt.push_back(active);
        solve_depth(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}//                                                                                                                                                

void solve_depth(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth) //                                                                                                                                 
{ //                                                                                                            
    assert(true);
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    Puzzle active = attempt[CURRENT-1];
    if (BEST>0 && CURRENT>=BEST)
        return;
    else if (CURRENT> max_depth+1)
        return;
    else if (puzzle_ready(active))
    {
        shortest=attempt;
        return;
    }
    if (can_go_west(active))
        try_depth (attempt,west(active),shortest, max_depth);
    if (can_go_north(active))
        try_depth (attempt, north(active),shortest, max_depth);
    if (can_go_south(active))
        try_depth (attempt, south(active),shortest, max_depth);
    if (can_go_east(active))
        try_depth (attempt, east(active),shortest, max_depth);
}//                                                                                                                                                                         

int main()
{
    /*              */Puzzle hey= get_puzzle("challenge.23.txt");
    //                        
    solve_breadth(hey/*              */);
//                              
    return 0;
}

