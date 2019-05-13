
//                                                                

#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <array>

using namespace std;
typedef int Cell;

const int ROWS = 6;
const int COLUMNS = 10;

char Legenda[7] = {'*',' ', '.', 'b', 'B', 'w', 'W'};
char Richting[4] = {'N', 'S', 'W', 'E'};
struct Pos
{//                            
    int row, column;
};

struct ArrayList
{//                                            
  Cell Matrix [ROWS][COLUMNS];
  vector<int> Path;
};

void direction_coordinates(Pos& location, const char direction)
{
//               
    assert(true);
//                
//                                                                        
    if (direction == 'N'){
      location.row = location.row - 1;
      //                           
    }
    if (direction == 'S'){
      location.row = location.row + 1;
      //                           
    }
    if (direction == 'E'){
    //                                  
      location.column = location.column + 1;
      //                                 
    }
    if (direction == 'W'){
      location.column = location.column - 1;
     //                           
    }

}
bool can_push(Pos location, const char& direction, Cell Matrix[ROWS][COLUMNS])
{
//               
    assert(true);
//                
//                                                           
//                                               
    direction_coordinates(location, direction);

    if(Matrix[location.row][location.column] == 1 || Matrix[location.row][location.column] == 2 ){
  //                       
      return true;
    }
  //                      
    return false;
}

bool can_move(Pos location, const char direction, Cell Matrix[ROWS][COLUMNS])
{
//              
    assert(true);
//                
//                                                        
//                                                              
//           
    direction_coordinates(location, direction);

    if(Matrix[location.row][location.column] == 1){
      //                            
      return true;
    }
    if(Matrix[location.row][location.column] == 3 || Matrix[location.row][location.column] == 4)
      return can_push(location, direction, Matrix);
    //                                                                      
    return false;
}

bool is_solution( Cell Matrix[ROWS][COLUMNS])
{
//               
    assert(true);
//                
//                                          
    for(int i = 0; i <= ROWS -1; i++){
        for(int j = 0; j <= COLUMNS -1; j++)
        {
          if(Matrix[i][j] == 3)
            return false;
        }
    }
    return true;
}

void move_box(Pos location, const char direction, Cell Matrix[ROWS][COLUMNS])
{
//               
assert(true);
//                
//                                               
    direction_coordinates(location, direction);
    Matrix[location.row][location.column] = Matrix[location.row][location.column] + 2;
}

void move_worker(Pos& location, char direction, Cell Matrix[ROWS][COLUMNS])
{

//               
    assert(can_move(location, direction, Matrix));
//                
//                                                    
    Matrix[location.row][location.column] = Matrix[location.row][location.column] -4;
    //                                                                      
    direction_coordinates(location, direction);
    //                                                                     
    if(Matrix[location.row][location.column] == 3)
    {
        move_box(location, direction, Matrix);
        Matrix[location.row][location.column] = 5;
    }
    if(Matrix[location.row][location.column] == 4)
    {
        move_box(location, direction, Matrix);
        Matrix[location.row][location.column] = 6;
    }
    if(Matrix[location.row][location.column] == 1){
      Matrix[location.row][location.column] = 5;
    }
    if(Matrix[location.row][location.column] == 2)
      Matrix[location.row][location.column] = 6;
}

bool discovered(Cell Matrix [ROWS][COLUMNS], vector<ArrayList>& History)
{
//               
    assert(true);
//                
//                                                    
  for (int k = 0; k <= History.size() - 1; k++)
  {
      for (int i = 0; i <= ROWS - 1; i++)
      {
          for (int j = 0; j <= COLUMNS - 1; j++)
          {
              if (History[k].Matrix[i][j] == Matrix[i][j])
                  return false;
          }
      }
  }
  return true;
}

void CopyArray(ArrayList& CurrentMatrix,  Cell Matrix[ROWS][COLUMNS])
{
//               
    assert(true);
//                
//                                         
    for(int i = 0; i <= ROWS -1; i++)
    {
        for(int j = 0; j <= COLUMNS -1; j++)
        {
            CurrentMatrix.Matrix[i][j] = Matrix[i][j];
        }
    }
}

void add_to_vectors(vector<ArrayList>& History_tmp, vector<ArrayList>& History, vector<ArrayList>& Frontier, Cell Matrix[ROWS][COLUMNS], int i)
{
//               
    assert(true);//                
//                              
    ArrayList CurrentMatrix;
    CopyArray(CurrentMatrix, Matrix);
    CurrentMatrix.Path = History[History.size()-1].Path;
    CurrentMatrix.Path.push_back(i);
    History_tmp.push_back(CurrentMatrix);
    Frontier.push_back(CurrentMatrix);
    //                                               

}

void pop_front(vector<ArrayList>& a)
{
//               
    assert(true);
//                
//                                            
    for(int i = 0; i <= a.size()-2; i++)
        a[i] = a[i+1];
    a.pop_back();
}

void show_world(Cell Matrix[ROWS][COLUMNS])
{
//               
    assert(true);//                
//                               
    for (int i = 0; i <= ROWS-1; i++)
    {
        for (int j = 0; j <= COLUMNS-1; j++)
            cout << Legenda[Matrix[i][j]];
        cout << endl;
    }
    cout << endl;
}
void one_step(Pos& location, char direction, Cell Matrix[ROWS][COLUMNS])
{
//               
    assert(true);
//               
//                                                    
  if(can_move(location, direction, Matrix)){
      //                    
      move_worker(location, direction, Matrix);
}
}

void merge_history(vector<ArrayList>& History, vector<ArrayList>& History_tmp)
{
//               
    assert(true);
//                
//                                                            
    for (int i = 0; i <= History_tmp.size() - 1; i ++)
        History.push_back(History_tmp[i]);
    //                                                     
}

bool SearchLocation(Pos& location, Cell Matrix[ROWS][COLUMNS])
{
//               
    assert(true);
//                
//                                                               
    for(int i = 0; i <= ROWS -2; i++){
        for(int j = 0; j <= COLUMNS -2; j++)
        {
            if(Matrix[i][j] == 5 || Matrix[i][j] == 6 )
            {
                location.row = i;
                location.column = j;
                return true;
            }
        }
    }
    return false;
}

bool bfs(Pos location, Cell Matrix[ROWS][COLUMNS], vector<ArrayList>& History)
{
//               
    assert(true);
//                
//                                                                                    
    vector<ArrayList> Frontier;
    ArrayList CurrentMatrix;
    if(is_solution(Matrix))
      return true;
    bool found = false;
    CopyArray(CurrentMatrix,Matrix);

    CurrentMatrix.Path;
    Frontier.push_back(CurrentMatrix);
    History.push_back(CurrentMatrix);
    while(!found)
    {

       vector<ArrayList> History_tmp;
       for(int i = 0; i <= 3; i++)
       {
           Matrix = Frontier[0].Matrix;
           SearchLocation(location, Matrix);
          //                                                 
          //                    
          //                                
          one_step(location, Richting[i], Matrix);
          //                    
          if (discovered)
          {
            //                                                                
            add_to_vectors(History_tmp, History, Frontier, Matrix, i);
            //                         
          }
          if (is_solution(Matrix))
          {
              found = true;
              merge_history(History, History_tmp);
              //                                    
              return true;
          }
       }
       pop_front(Frontier);
       merge_history(History, History_tmp);
    }
    return false;
}

bool dfs(Pos location, Cell Matrix[ROWS][COLUMNS], vector<ArrayList>& History , int current_depth, int& max_depth, int& leastmoves, int direction){
//              
  assert (true);
//
    one_step(location, Richting[direction], Matrix);
    SearchLocation(location, Matrix);
    if(discovered)
    {
        ArrayList CurrentMatrix;
        CopyArray(CurrentMatrix, Matrix);
        History.push_back(CurrentMatrix);

    }
    else
        return false;

    if(is_solution(Matrix)){
        if (current_depth < leastmoves)
        {
          //                
          leastmoves = current_depth;
          max_depth = leastmoves;
          show_world(Matrix);
        }
        return true;
    }
    else if (current_depth >= max_depth){
        current_depth--;
        return false;
    }
    else{
        for(int i = 0; i <= 3; i++){
            current_depth++;
            return dfs(location, Matrix, History, current_depth, max_depth, leastmoves, i);
        }

    }
}

void print_result(vector<ArrayList>& History)
{//              
  assert (true);
//                
//                                                                      
//                                                   
ArrayList Result;
  Result.Path = History[History.size()-1].Path;
  cout << "Found a result in " << Result.Path.size() <<" steps using breath first search."<< endl;
  CopyArray(Result, History[History.size()-1].Matrix);
  //                                                
  //                          
 //                                               

  show_world(Result.Matrix);
}

int main()
{

    ifstream startposition;
    //      
    //        
    //      
    //      
    //      
    //      
    //     

    Cell Matrix[ROWS][COLUMNS]={{0,0,0,0,0,0,0,0,0,0},
                               {0,1,1,1,1,1,1,1,1,0},
                               {0,2,3,1,1,1,5,1,1,0},
                               {0,1,1,0,0,0,0,1,1,0},
                               {0,1,1,1,1,1,1,1,1,0},
                               {0,0,0,0,0,0,0,0,0,0}};
    //                 
    //                           
    Pos location;

    SearchLocation(location, Matrix);
        //                   
    //                                      
    //                   
    /*                       
                                            
        
                                                */
   //                                                
   vector<ArrayList> History;
   bfs(location, Matrix, History);
   print_result(History);
   int current_depth = 0;
   int max_depth = 50;
   int leastmoves = max_depth + 1;
   int i = 0;
   cout << endl << "Using depth first search, the result is found in: ";
   dfs(location, Matrix, History, current_depth, max_depth, leastmoves, i);
}

