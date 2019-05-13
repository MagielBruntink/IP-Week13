//                          
//                            

/*
                                                                             
                                                                                                          
*/
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
using namespace std;

enum Cell {Wall=0, Empty, Destination, Worker, Dest_worker, Box, Dest_box};                         //                                                                           

const char WALL                 = '*' ;               //                                                          
const char EMPTY                = ' ' ;               //                                                          
const char DESTINATION          = '.' ;
const char WORKER               = 'w' ;
const char DEST_WORKER          = 'W' ;
const char BOX                  = 'b' ;
const char DEST_BOX             = 'B' ;
const int NO_OF_ROWS        = 5 ;                //                                                                      
const int NO_OF_COLUMNS     = 8 ;                //                                                                        
const int ROWS              = NO_OF_ROWS    + 2 ; //                                                                            
const int COLUMNS           = NO_OF_COLUMNS + 2 ; //                                                                               
const int MAX_FILENAME_LENGTH   = 80 ;              //                                                                                   

vector<int> destinations;
//                       
//                        

struct Puzzle
{
    Cell universe[ROWS][COLUMNS];
    int position;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

//                                
bool enter_filename (char filename [MAX_FILENAME_LENGTH])
{   //              
    assert(true);
    //                                                                                       
    int i=0;
    while(i<=MAX_FILENAME_LENGTH)
    {
        cin.get(filename[i]);
        if(filename[i]=='\n')
        {
            filename[i] = '\0';
            return true;
        }
        i++;
    }

     return false;
}

//                           

char convert_cell_to_char(Cell a)
{
    //             
    assert(true);
    //                                   
    int b =(int)a;
    switch(b){
        case 0: return '*';
        case 1: return ' ';
        case 2: return '.';
        case 3: return 'w';
        case 4: return 'W';
        case 5: return 'b';
        case 6: return 'B';
    }
}

Cell convert_char_to_cell(char a)
{
    //             
    assert(true);
    //                                    
    switch(a){
        case '*': return Wall;
        case ' ': return Empty;
        case '.': return Destination;
        case 'w': return Worker;
        case 'W': return Dest_worker;
        case 'b': return Box;
        case 'B': return Dest_box;
    }
}

int workeri (int W)
{
    //    
    assert(W>=0);
    /*     
                                   
    */
    return W/COLUMNS;
}

int workerj (int W)
{
    //    
    assert(W>=0);
    /*     
                                   
    */
    return W%COLUMNS;
}

int convert_index_to_int(int i, int j)
{
    //    
    assert(i>=0 && j>=0);
    /*     
                                         
    */
    return COLUMNS*i+j;
}

bool read_universe_file (ifstream& inputfile, Puzzle& start,vector<int>& destinations)
{
//                
    assert(inputfile.is_open());
    //                                                                                                  

    char d;
    string c;
    cout<< "Below is the exact strings from the file" <<endl;
    for(int i =0;i<ROWS;i++)
    {
        getline(inputfile, c);
        cout <<c;
        for(int j=0;j<COLUMNS;j++)
        {

            d = c[j];
            start.universe[i][j] = convert_char_to_cell(d);
            if(start.universe[i][j] == Destination)
            {
                destinations.push_back(convert_index_to_int(i,j));
            }
            if(start.universe[i][j] == Worker)
            {
                start.position = convert_index_to_int(i,j);
            }
        }
        cout<< endl;
    }
     if(d=='\0') return true;
     else return false;

}

void show_universe (Puzzle p)
{
    //             
    assert(true);
    //                                                  
    cout << "Below is the data structure visualised."<<endl;
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {
            cout<<convert_cell_to_char(p.universe[i][j]);
        }
        cout<<endl;
    }
}

Puzzle up(Puzzle& p)
{
    //    
    assert(true);
    /*     
                                                            
    */
    int W = p.position;
    int iw = workeri(W);
    int jw = workerj(W);
    p.universe[iw][jw]   = Empty;
    if (p.universe[iw-1][jw]==Box)
    {
        p.universe[iw-2][jw] = Box;
    }
    p.universe[iw-1][jw] = Worker;
    p.position = W-COLUMNS;
    return p;
}

Puzzle down(Puzzle& p)
{
    //    
    assert(true);
    /*     
                                                                                        
    */
    int W = p.position;
    int iw = workeri(W);
    int jw = workerj(W);
    p.universe[iw][jw]   = Empty;
    if (p.universe[iw+1][jw]==Box)
    {
        p.universe[iw+2][jw] = Box;
    }
    p.universe[iw+1][jw] = Worker;
    p.position = W+COLUMNS;
    return p;
}

Puzzle left(Puzzle& p)
{
    //    
    assert(true);
    /*     
                                                                                        
    */
    int W = p.position;
    int iw = workeri(W);
    int jw = workerj(W);
    p.universe[iw][jw]   = Empty;
    if (p.universe[iw][jw-1]==Box)
    {
        p.universe[iw][jw-2] = Box;
    }
    p.universe[iw][jw-1] = Worker;
    p.position = W-1;
    return p;
}

Puzzle right(Puzzle& p)
{
    //    
    assert(true);
    /*     
                                                                                        
    */
    int W = p.position;
    int iw = workeri(W);
    int jw = workerj(W);
    p.universe[iw][jw]   = Empty;
    if (p.universe[iw][jw+1]==Box)
    {
        p.universe[iw][jw+2] = Box;
    }
    p.universe[iw][jw+1] = Worker;
    p.position = W + 1;
    return p;
}

int finished(vector<Candidate>& c,vector<int>& destinations, int l)
{
    //    
    assert(true);
    /*     
                                                                             
    */
    for(int k = l; k<c.size();k++)
    {
    Puzzle p = c[k].candidate;

    vector<int> boxes;
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {
            if(p.universe[i][j]==Box)
            {
                boxes.push_back(convert_index_to_int(i,j));
            }
        }
    }
    if(boxes.size() == destinations.size() && boxes == destinations)
    {
        show_universe(p);
        return k;
    }
    }
    return 0;
}

/*
                    
 
          
                 
           
                                          

                                      
     
                          
                           
     
                                  
         
                                     
             
                                                           
             
         
     
                                                                    
     
                 
     
     
             
 */

bool can_up(Puzzle& p)
{
    //    
    assert(true);
    /*     
                                                                                                    
    */
    int iw = workeri(p.position);
    int jw = workerj(p.position);
    if ((p.universe[iw-1][jw]==Box && p.universe[iw-2][jw]!=Wall && p.universe[iw-2][jw]!=Box) || (p.universe[iw-1][jw]!=Wall && p.universe[iw-1][jw] != Box && p.universe[iw-1][jw] != Dest_box))
    {
        return true;
    }
    else
        return false;
}
bool can_down(Puzzle& p)
{
    //    
    assert(true);
    /*     
                                                                                                    
    */
    int iw = workeri(p.position);
    int jw = workerj(p.position);
    if ((p.universe[iw+1][jw]==Box && p.universe[iw+2][jw]!=Wall && p.universe[iw+2][jw]!=Box) || (p.universe[iw+1][jw]!=Wall && p.universe[iw+1][jw] != Box && p.universe[iw+1][jw] != Dest_box))
    {
        return true;
    }
    else
        return false;
}
bool can_left(Puzzle& p)
{
    //    
    assert(true);
    /*     
                                                                                                    
    */
    int iw = workeri(p.position);
    int jw = workerj(p.position);
    if ((p.universe[iw][jw-1]==Box && p.universe[iw][jw-2]!=Wall && p.universe[iw][jw-2]!=Box) || (p.universe[iw][jw-1]!=Wall && p.universe[iw][jw-1] != Box && p.universe[iw][jw-1] != Dest_box))
    {
        return true;
    }
    else
        return false;
}
bool can_right(Puzzle& p)
{
    //    
    assert(true);
    /*     
                                                                                                    
    */
    int iw = workeri(p.position);
    int jw = workerj(p.position);
    if ((p.universe[iw][jw+1]==Box && p.universe[iw][jw+2]!=Wall && p.universe[iw][jw+2]!=Box) || (p.universe[iw][jw+1]!=Wall && p.universe[iw][jw+1] != Box && p.universe[iw][jw+1] != Dest_box))
    {
        return true;
    }
    else
        return false;
}

Puzzle move_worker(Puzzle& p, int direction)
{
    //    
    assert(direction == 0 || direction == 1 || direction == 2 || direction ==3);
    /*     
                                                  
    */
    switch(direction)
    {
        case 0: return up(p);
        case 1: return down(p);
        case 2: return left(p);
        case 3: return right(p);
    }
}

bool puzzle_present (vector<Candidate>& c, int i, Puzzle& newp)
{
    //    
    assert(i>=0);
    /*     
                                                                   
    */
    for(int j=1;j<COLUMNS-1;j ++)
    {
        for(int k=1; k<ROWS-1; k++)
        {
            if(c[i].candidate.universe[j][k] != newp.universe[j][k])
            {
                return false;
            }
        }
    }
    return true;
}/*
                                                           
 
          
                 
           
                                                                   

                                 
     
                                   
         
                                                             
             
                             
             
         
     
                
 
*/
void tries(vector<Candidate>& c, int i, int direction)
{
    //    
    assert(i>=0 && direction >= 0 && direction <= 3);
    /*     
                      
    */
    Puzzle p = c[i].candidate;
    Puzzle newp = move_worker(p, direction);
    Candidate newc = {newp, i};
    if (!puzzle_present(c,i,newp))
    {
        c.push_back(newc);
    }
}
/*
                                                                                           
 
          
                                                                    
           
                      

                                        
                                            
                                       
     
                                
                                          
                           
     
 
*/

void BFS(Puzzle start)
{
    //   
    assert(true);
    /*    
                                  
    */
    vector<Candidate> c = {{start,-1}};
    int i = 0;
    int l = 0;
    while(i<c.size() && !finished(c, destinations,l))
    {
        l = l + c.size();
        Puzzle p = c[i].candidate;
        if(can_up(p))
        {
            tries(c,i,0);
        }
        if(can_down(p))
        {
            tries(c,i,1);
        }
        if(can_left(p))
        {
            tries(c,i,2);
        }
        if(can_right(p))
        {
            tries(c,i,3);
        }
        i++;

    }
}
/*
                                                                          
 
         
                        
          
                                 

                                       
                                     
                                  
                                  
     
                
     
                                  
     
                
     
                         
     
                           
                
     
                 
     
                                             
     
                   
     
                                             
     
                   
     
                                             
     
                    
     
                                             
     
                                      
     
                                   
     
 
*/

int main()
{
    char filename[MAX_FILENAME_LENGTH];
    Puzzle start;

    int max_depth;

    //                                      
    //                             
    ifstream inputfile;

    if (enter_filename(filename))
        inputfile.open(filename);
    else cout<<"Error: File couldn't be opened.";

    cout<<read_universe_file(inputfile,start,destinations)<<endl;
//                                           
//                    
    for(int i = 0; i<destinations.size(); i++)
    {
        cout << destinations[i] << ", ";
    }
    show_universe(start);
    BFS(start);
    //                                  

    return 0;
}

