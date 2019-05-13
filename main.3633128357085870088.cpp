//                               
//                                                                                  
//                                                                                 

/*                                                                                                                                       
                                                                                          
                                                                                                                        
                                                                                                                */

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;
const int MAX_SIZE = 10;
enum Direction =  {north,east,south,west};
typedef int coord;

string enter_filename(string& filename)
{
    assert(true);
    //                                                                                         
    cout<<"Please enter filename"<<endl;
    cin>>filename;
    return filename;
}

void print_puzzle (char puzzle[MAX_SIZE][MAX_SIZE], int rows, int columns){
    for (int i = 0; i <= rows; i++){
        for (int j = 0; j <  columns; j++){
            if (puzzle[i][j]){
                cout << puzzle[i][j];
            }
        }
        if (puzzle[i][0]){
        cout << endl;
        }
    }
}

bool read_file(string& filename, char puzzle[MAX_SIZE][MAX_SIZE], int& rows, int& columns){
    char symbol = ' ';
    ifstream myfile(filename);
    if(myfile.is_open ()){
       myfile.get(symbol);
       while (myfile){
            cout << symbol;
             if (symbol == '\n'){
                rows++;
                columns = 0;
            }
            else {
                puzzle[rows][columns] = symbol;
                columns++;
            }
            myfile.get(symbol);
    }
    cout << endl << endl;
    }
    myfile.close();
}

bool locate_box(char puzzle[MAX_SIZE][MAX_SIZE],coord& xb,coord& yb,int rows, int columns)
{
    for(int i=xb;i<columns;i++){
        for(int j=yb;j<rows;j++){
            if(puzzle[i][j]=='b'){
                xb=i;
                yb=j;
                return true;}
        }
    }
    return false
}

bool locate_worker(char puzzle[MAX_SIZE][MAX_SIZE],coord& xw,coord& yw,int rows, int columns)
{
    for(int i=xb;i<columns;i++){
        for(int j=yb;j<rows;j++){
            if(puzzle[i][j]=='w'||puzzle[i][j]=='W'){
                xw=i;
                yw=j;
                return true;}
        }
    }
    return false
}

bool locate_goal(char puzzle[MAX_SIZE][MAX_SIZE],coord& xg,coord& yg,int rows, int columns)
{
    for(int i=xb;i<columns;i++){
        for(int j=yb;j<rows;j++){
            if(puzzle[i][j]=='W'||puzzle[i][j]=='.'){
                xg=i;
                yg=j;
                return true;}
        }
    }
    return false
}

int calculate_route(char puzzle[MAX_SIZE][MAX_SIZE],coord& xg,coord& yg,coord& xw,coord& yw,coord& xb,coord& yb,int rows, int columns)
{
    coord xg=0;
    coord yg=0;
    coord xb=0;
    coord yb=0;
    coord xw=0;
    coord yw=0;
    if(!locate_box(puzzle,xb,yb,rows,columns))
        return 0;

}

/*                                               
 

 

                                                                                  
 
             
     
                                                                                   
                             
                                             
                                             
                            
                                 
                     
                                            
                                              
                                               
                                              
                             
                                               
                                              
                                 
                         
                                              
                                               
                                              
                             
                                               
                                              
                                 
                            
                 
                                                                                                                               
                             
                                             
                                             
                            
                                 
                     
                                            
                                              
                                               
                                              
                             
                                               
                                              
                                 
                         
                                              
                                               
                                              
                             
                                               
                                              
                                 
                            
                 
                                                                                                                               
                             
                                             
                                             
                            
                                 
                     
                                            
                                              
                                               
                                              
                             
                                               
                                              
                                 
                         
                                              
                                               
                                              
                             
                                               
                                              
                                 
                            
                 
                                                                                                                               
                             
                                             
                                             
                            
                                 
                     
                                            
                                              
                                               
                                              
                             
                                               
                                              
                                 
                         
                                              
                                               
                                              
                             
                                               
                                              
                                 
                            
                 
     
 
*/

int main(){
    string filename;
    bool wall = false;
    int rows =0;
    int columns =0;
    enter_filename(filename);
    char puzzle[MAX_SIZE][MAX_SIZE];
    read_file(filename, puzzle, rows, columns);
    print_puzzle(puzzle, rows, columns);
    return 0;
}

