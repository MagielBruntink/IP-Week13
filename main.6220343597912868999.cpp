#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

//                                              
//                                                   

ifstream infile;

const int WIDTH  = 20;
const int HEIGHT = 20;
char world[WIDTH][HEIGHT];
int bestSolution;

struct Pos
{ int x, y ;
} ;
struct Puzzle
{ char world [WIDTH][HEIGHT] ;
  Pos open ;
} ;

struct Candidate{
    Puzzle candidate;
    int parent;
};

Puzzle start;

void fill_world(ifstream& infile, Puzzle& first, int worldheight, int worldwidth, string filename){
//               
    assert ( true );
/*                
                                                                                   
*/
    char c;
    infile.close();
    infile.open(filename);
    for(int i = 0; i < worldheight; i++){
        for(int j = 0; j < worldwidth; j++){
            infile.get(c);
            first.world[i][j] = c;
        }
    }
}

void show_world(Puzzle last, int worldheight, int worldwidth){
//               
    assert ( true );
/*                
                                           
*/
    for(int i = 0; i < worldheight; i++){
        for(int j = 0; j < worldwidth; j++){
            if(last.world[i][j] == '\n'){
            } else {
            cout << last.world[i][j];
            }
        }
        cout << endl;
    }
}

bool solved(Puzzle current){
//               
    assert ( true );
/*                
                                                                                                                                                               
                              
*/
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            if(current.world[i][j] == 'b'){

                return false;
            }
        }
    }
    return true;
}

Puzzle move_next(Puzzle p, string pos){
//               
    assert (pos == "east" || pos == "north" || pos == "south" || pos == "west");
/*                
                                                                                             
*/
    int x;
    int y;
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(p.world[i][j] == 'W' || p.world[i][j] == 'w'){
                x = i;
                y = j;
            }
        }
    }

    if(pos == "east"){
        if(p.world[x][y+1] == ' '){
            p.world[x][y+1] = 'w';
        }
        if(p.world[x][y+1] == '.'){
            p.world[x][y+1] = 'W';
        }
        if(p.world[x][y+1] == 'b' || p.world[x][y+1] == 'B'){
            if(p.world[x][y+2] == '.'){
                p.world[x][y+2] = 'B';
            } else {
                p.world[x][y+2] = 'b';
            }
            if(p.world[x][y+1] == 'B'){
                p.world[x][y+1] = 'W';
            } else {
                p.world[x][y+1] = 'w';
            }
        }
        if(p.world[x][y] == 'W'){
            p.world[x][y] = '.';
        } else {
            p.world[x][y] = ' ';
        }
    } else if(pos == "west"){
        if(p.world[x][y-1] == ' '){
            p.world[x][y-1] = 'w';
        }
        if(p.world[x][y-1] == '.'){
            p.world[x][y-1] = 'W';
        }
        if(p.world[x][y-1] == 'b' || p.world[x][y-1] == 'B'){
            if(p.world[x][y-2] == '.'){
                p.world[x][y-2] = 'B';
            } else {
                p.world[x][y-2] = 'b';
            }
            if(p.world[x][y-1] == 'B'){
                p.world[x][y-1] = 'W';
            } else {
                p.world[x][y-1] = 'w';
            }
        }
        if(p.world[x][y] == 'W'){
            p.world[x][y] = '.';
        } else {
            p.world[x][y] = ' ';
        }
    } else if(pos == "north"){
        if(p.world[x-1][y] == ' '){
            p.world[x-1][y] = 'w';
        }
        if(p.world[x-1][y] == '.'){
            p.world[x-1][y] = 'W';
        }

        if(p.world[x-1][y] == 'b' || p.world[x-1][y] == 'B'){
            if(p.world[x-2][y] == '.'){
                p.world[x-2][y] = 'B';
            } else {
                p.world[x-2][y] = 'b';
            }
            if(p.world[x-1][y] == 'B'){
                p.world[x-1][y] = 'W';
            } else {
                p.world[x-1][y] = 'w';
            }
        }
        if(p.world[x][y] == 'W'){
            p.world[x][y] = '.';
        } else {
            p.world[x][y] = ' ';
        }
    } else if(pos == "south"){
        if(p.world[x+1][y] == ' '){
            p.world[x+1][y] = 'w';
        }
        if(p.world[x+1][y] == '.'){
            p.world[x+1][y] = 'W';
        }
        if(p.world[x+1][y] == 'b' || p.world[x+1][y] == 'B'){
            if(p.world[x+2][y] == '.'){
                p.world[x+2][y] = 'B';
            } else {
                p.world[x+2][y] = 'b';
            }
            if(p.world[x+1][y] == 'B'){
                p.world[x+1][y] = 'W';
            } else {
                p.world[x+1][y] = 'w';
            }
        }
        if(p.world[x][y] == 'W'){
            p.world[x][y] = '.';
        } else {
            p.world[x][y] = ' ';
        }
    }
    return p;
}

void triesb (vector<Candidate>& c, int i, string pos){
//               
    assert ( true );
/*                
                                           
*/
    Puzzle p  = c[i].candidate;
    Puzzle newWorld = move_next(p, pos);
    Candidate newCandidate = {newWorld, i};
    c.push_back(newCandidate);
}

bool can_go_west(Puzzle p, int worldheight, int worldwidth){
//               
    assert ( true );
/*                
                                                            
*/
    int x;
    int y;
    for(int i = 0; i < worldheight; i++){
        for(int j = 0; j < worldwidth; j++){
            if(p.world[i][j] == 'W' || p.world[i][j] == 'w'){
                x = i;
                y = j;
            }
        }
    }
if(p.world[x][y-1] == '*')  { return false; }
    if(p.world[x][y-1] == ' ' || p.world[x][y-1] == '.')    { return true;  }
    if(p.world[x][y-1] == '*')                              { return false; }

    if(p.world[x][y-1] == 'b' || p.world[x][y-1] == 'B'){
        if(p.world[x][y-2] == 'b' || p.world[x][y-2] == 'B' )   { return false; }
        if(p.world[x][y-2] == '*')                              { return false; }
        if(p.world[x][y-1] == ' ' || p.world[x][y-1] == '.')    { return true;  }
    }
}

bool can_go_east(Puzzle p, int worldheight, int worldwidth){
//               
    assert ( true );
/*                
                                                            
*/
    int x;
    int y;
    for(int i = 0; i < worldheight; i++){
        for(int j = 0; j < worldwidth; j++){
            if(p.world[i][j] == 'W' || p.world[i][j] == 'w'){
                x = i;
                y = j;
            }
        }
    }

    if(p.world[x][y+1] == '*')  { return false; }
    if(p.world[x][y+1] == ' ' || p.world[x][y+1] == '.')    {  return true;  }
    if(p.world[x][y+1] == '*')                              {  return false; }

    if(p.world[x][y+1] == 'b' || p.world[x][y+1] == 'B'){
        if(p.world[x][y+2] == 'b' || p.world[x][y+2] == 'B' )   { return false; }
        if(p.world[x][y+2] == '*')                              { return false; }
        if(p.world[x][y+2] == ' ' || p.world[x][y+1] == '.')    { return true;  }
    }
}

bool can_go_north (Puzzle p, int worldheight, int worldwidth){
//               
    assert ( true );
/*                
                                                            
*/
    int x;
    int y;
    for(int i = 0; i < worldheight; i++){
        for(int j = 0; j < worldwidth; j++){
            if(p.world[i][j] == 'W' || p.world[i][j] == 'w'){
                x = i;
                y = j;
            }
        }
    }

    if(p.world[x-1][y] == '*')  { return false; }
    if(p.world[x-1][y] == ' ' || p.world[x-1][y] == '.')    { return true;  }
    if(p.world[x-1][y] == '*')                              { return false; }

    if(p.world[x-1][y] == 'b' || p.world[x-1][y] == 'B'){
        if(p.world[x-2][y] == 'b' || p.world[x-2][y] == 'B' )   { return false; }
        if(p.world[x-2][y] == '*')                              { return false; }
        if(p.world[x-2][y] == ' ' || p.world[x-2][y] == '.')    { return true;  }
    }
}

bool can_go_south (Puzzle p, int worldheight, int worldwidth){
//               
    assert ( true );
/*                
                                                             
*/
    int x;
    int y;
    for(int i = 0; i < worldheight; i++){
        for(int j = 0; j < worldwidth; j++){
            if(p.world[i][j] == 'W'|| p.world[i][j] == 'w'){
                x = i;
                y = j;
            }
        }
    } if(p.world[x+1][y] == '*')  { return false; }
    if(p.world[x+1][y] == ' ' || p.world[x+1][y] == '.')    { return true;  }
    if(p.world[x+1][y] == '*')                              { return false; }

    else if(p.world[x+1][y] == 'b' || p.world[x+1][y] == 'B'){
        if(p.world[x+2][y] == 'b' || p.world[x+2][y] == 'B' )   { return false; }
        if(p.world[x+2][y] == '*')                              { return false; }
        if(p.world[x+2][y] == ' ' || p.world[x+2][y] == '.')    { return true;  }
    }
}

int calculate_width (ifstream& infile){
//               
    assert ( true );
/*                
                                                             
*/
    char c;
    for(int i = 1; i < 50; i++){
        infile.get(c);
        if(c == '\n'){
            return i;
        }
    }
    cout << "file is too big!" << endl;
    return 0;
}

int calculate_height (ifstream& infile, string filename){
//               
    assert ( true );
/*                
                                                             
*/
    infile.close();
    infile.open(filename);
    string str;
    int height = 1;
    while(getline(infile,str)){
        height++;
    }
    int const HEIGHT = height;
    return height;
}

int  breadth_first(Puzzle start, int worldheight, int worldwidth){
//               
    assert ( worldheight >= 0 && worldwidth >= 0 );
/*                
                                                                                       
*/
    int i = 0;
    vector<Candidate> c = {{start, -1}};

    while(!solved(c[i].candidate)){
        Puzzle p = c[i].candidate;
        show_world(p, worldheight, worldwidth);
        if( can_go_north(p, worldheight, worldwidth))  { triesb(c, i, "north");  }
        if( can_go_south(p, worldheight, worldwidth))  { triesb(c, i, "south");  }
        if( can_go_west (p, worldheight, worldwidth))  { triesb(c, i, "west" );  }
        if( can_go_east (p ,worldheight, worldwidth))  { triesb(c, i, "east" );  }

        i++;

    }
    show_world(c[i].candidate, worldheight, worldwidth);
    return c[i].parent + 1;

}

bool puzzle_present(Puzzle p, vector<Puzzle>& c){
//               
    assert ( true );
/*                

*/
    for(int i = 0; i < c.size(); i++){
        if(c[i].world == p.world){
            return true;
        }
    }
    return false;
}

vector<Puzzle> attempt;
vector<Puzzle> shortest;
int max_depth = 200;
void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth, int worldheight, int worldwidth);

void triesd(vector<Puzzle>& attempt, string pos, vector<Puzzle>& shortest, int max_depth, int worldheight, int worldwidth){
//               
    assert (max_depth >= 0 && worldheight >= 0 && worldwidth >= 0);
/*                
                                           
*/
    Puzzle p = attempt[attempt.size()-1];
    Puzzle newp = move_next(p, pos);
    if (!puzzle_present(newp, attempt)){
        attempt.push_back(newp);
        depth_first(attempt, shortest, max_depth, worldheight, worldwidth);
        attempt.pop_back();
    }
}

void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth, int worldheight, int worldwidth){
//               
    assert (max_depth >= 0 && worldheight >= 0 && worldwidth >= 0);
/*                
                                                                                       
*/
    const int CURRENT   = attempt.size();
    const int BEST      = shortest.size();
    Puzzle p            = attempt[CURRENT-1];
    if(BEST > 0 && CURRENT >= BEST)     {  return; }
    else if (CURRENT > max_depth+1)     {  return; }
    else if (solved(p))          { shortest = attempt ; return ; }
    if (can_go_north(p, worldheight, worldwidth))   {triesd (attempt, "north", shortest, max_depth, worldheight, worldwidth); }
    if (can_go_south(p, worldheight, worldwidth))   {triesd (attempt, "south", shortest, max_depth, worldheight, worldwidth); }
    if (can_go_west(p, worldheight, worldwidth))    {triesd (attempt, "west" , shortest, max_depth, worldheight, worldwidth); }
    if (can_go_east(p, worldheight, worldwidth))    {triesd (attempt, "east" , shortest, max_depth, worldheight, worldwidth); }
}

int main(){
//               
    assert (max_depth >= 0 && worldheight >= 0 && worldwidth >= 0);
/*                
                                                                                                                  
*/
    string filename;
    cout << "what file would you like to open? " << endl;
    cin >> filename;
    infile.open(filename);
    int worldwidth = calculate_width(infile);
    int worldheight =  calculate_height(infile, filename);

    fill_world(infile, start, worldheight, worldwidth, filename);
    show_world(start, worldheight, worldwidth);
//                                                            
//                                    
    attempt.push_back(start);
    depth_first(attempt, shortest, max_depth,  worldheight, worldwidth);

    show_world(shortest[shortest.size()-1], worldheight, worldwidth);

    return 0;
}

