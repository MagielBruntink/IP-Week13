#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

//                                                               
//                                                       

enum Type {wall, emptycell, destination, box_empty, box_destination};

struct Pos
{
    int x, y;
};

struct Puzzlestruct
{
    vector<vector<Type>> Board;
    Pos worker;
};

bool operator == (Pos a, Pos b)
{
   return((a.x == b.x) && (a.y==b.y));
}

bool operator !=(Pos a, Pos b)
{
    return (!(a == b));
}

bool operator ==(Puzzlestruct a, Puzzlestruct b)
{
    for (int x = 0; x < a.Board.size(); x++)
        {
        for (int y = 0; y < a.Board[x].size(); y++)
        {
            if ((a.Board[x][y] != b.Board[x][y]))
                {
                    return false;
                }

        }
    }
    return (a.worker == b.worker);
}

void open_file(ifstream& infile)
{
    //              
    assert(true);
    //                                   
    string filename;
    cout<< "Please give a filename; "<< endl;
    cin>> filename;
    infile.open(filename.c_str());
}

void read_puzzle(ifstream& infile, Puzzlestruct& puzzle)

{
    //              
    assert(infile.is_open());
    //                                                      
    string line;
    int x=0;
   while (infile)
   {
       getline(infile, line);
       puzzle.Board.push_back(vector<Type>());
       for(int y=0; y < line.length(); y++)
       {
           if(line[y] == '*') puzzle.Board[x].push_back(wall);
           else if(line[y] == ' ') puzzle.Board[x].push_back(emptycell);
           else if(line[y] == '.') puzzle.Board[x].push_back(destination);
           else if(line[y] == 'b') puzzle.Board[x].push_back(box_empty);
           else if(line[y] == 'B') puzzle.Board[x].push_back(box_destination);
           else if(line[y] == 'w')
           {
               puzzle.Board[x].push_back(emptycell);
               puzzle.worker = {x,y};
           }
          else if(line[y] == 'W')
           {
               puzzle.Board[x].push_back(destination);
               puzzle.worker = {x,y};
           }
        }
        x++;
   }
}

void show_puzzle(Puzzlestruct puzzle)
{
    //              
    assert(true);
    //                                    
    for(int x=0; x<puzzle.Board.size(); x++)
    {
        for(int y=0; y<puzzle.Board[x].size(); y++)
        {
            if(puzzle.Board[x][y] == wall) cout<< "*";
            if(puzzle.Board[x][y] == box_empty) cout << "b";
            if(puzzle.Board[x][y] == box_destination) cout<< "B";
            if((puzzle.Board[x][y] == emptycell) && ((puzzle.worker.x != x)|| (puzzle.worker.y != y))) cout << " ";
            if((puzzle.Board[x][y] == emptycell) && (puzzle.worker.x == x) && (puzzle.worker.y == y)) cout << "w";
            if((puzzle.Board[x][y] == destination) && (puzzle.worker.x == x) && (puzzle.worker.y == y)) cout << "W";
            if((puzzle.Board[x][y] == destination) && ((puzzle.worker.x != x) || (puzzle.worker.y != y))) cout << ".";
        }
    cout << endl;
    }
}

bool is_wall(int x, int y,Puzzlestruct puzzle)
{
    //              
    assert(true);
    //                                                        
    return(puzzle.Board[x][y] == wall);
}

bool is_box(int x, int y, Puzzlestruct puzzle)

{
    //              
    assert(true);
    //                                                              
    return(puzzle.Board[x][y] == box_empty || puzzle.Board[x][y] == box_destination);
}

bool check_valid_direction(Puzzlestruct puzzle, string direction)
{
    //              
    assert(true);
    //                                                                                                            

    int y = puzzle.worker.y;
    int x = puzzle.worker.x;
    Pos richting;
    Pos richting2;

    if (direction == "north")
        {;richting = {x-1,y};
        richting2 = {x-2,y};
        }
    if (direction == "east")
        {richting = {x,y+1};
        richting2 = {x,y+2};
        }
    if (direction == "south")
        {richting = {x+1,y};
        richting2 = {x+2,y};
        }
    if (direction == "west")
        {richting = {x,y-1};
        richting2 = {x,y-2};
        }

 if(is_wall(richting.x , richting.y , puzzle))
    {
    return false;
    }

 if(is_box(richting.x , richting.y,puzzle))
    {
        if (is_box(richting2.x , richting2.y,puzzle) || (is_wall(richting2.x , richting2.y,puzzle)))
            return false;
    }
return true;
}

void move_direction(Puzzlestruct& puzzle, string direction)
{
    //              
    assert(direction == "north" || direction == "east"|| direction == "south"|| direction == "west");
    //                                                                                                                      

    int y = puzzle.worker.y;
    int x = puzzle.worker.x;

    Pos richting;
    Pos richting2;

    if (direction == "north")
        {richting = {x-1,y};
        richting2 = {x-2,y};
        }
    if (direction == "east")
        {richting = {x,y+1};
        richting2 = {x,y+2};
        }
    if (direction == "south")
        {richting = {x+1,y};
        richting2 = {x+2,y};
        }
    if (direction == "west")
        {richting = {x,y-1};
        richting2 = {x,y-2};
        }

    if(!check_valid_direction(puzzle, direction))
        return;

    if (is_box(richting.x,richting.y,puzzle))
    {
        if (puzzle.Board[richting.x][richting.y] == box_empty)
        {
            if (puzzle.Board[richting2.x][richting2.y] == destination)
                puzzle.Board[richting2.x][richting2.y] = box_destination;
            else
                puzzle.Board[richting2.x][richting2.y] = box_empty;
            puzzle.Board[richting.x][richting.y] = emptycell;
        }

        if (puzzle.Board[richting.x][richting.y] == box_destination)
        {
            if (puzzle.Board[richting2.x][richting2.y] == destination)
                puzzle.Board[richting2.x][richting2.y] = box_destination;
            else
                puzzle.Board[richting2.x][richting2.y] = box_empty;
            puzzle.Board[richting.x][richting.y] = destination;
        }
    }
puzzle.worker = {richting.x, richting.y};
}

bool is_done(Puzzlestruct puzzle)
{
    //              
    assert(true);
    //                                                     

    for(int x = 0; x < puzzle.Board.size(); x++)
    {
        for(int y = 0; y < puzzle.Board[x].size(); y++)
            {
                if((puzzle.Board[x][y] == destination) || (puzzle.Board[x][y] == box_empty))
                    return false;
            }
    }
return true;
}

struct Candidatestruct
{
   Puzzlestruct candidate;
   int parent_candidate;
};

void show_path(vector<Candidatestruct>& wachtrij, int index)
{
    //              
    assert(index >= -1);
    //                                                                 
    if (index < 0)
        return;
    else
        {
        show_path(wachtrij,wachtrij[index].parent_candidate);
        show_puzzle(wachtrij[index].candidate);
        }

}

void extend_wachtrij(Puzzlestruct puzzle, vector<Candidatestruct>& wachtrij, int index)
{
    //              
    assert(index >= 0);
    //                                                                                                                                                       
    if (check_valid_direction(puzzle,"north"))
        {
            Puzzlestruct newpuzzle = puzzle;
            move_direction(newpuzzle, "north");
            bool a = true;
            for (int i = 0; i < index; i++)
                {
                    if (wachtrij[i].candidate == newpuzzle)
                    a = false;
                }
            if (a)
                wachtrij.push_back({newpuzzle, index});

        }
    if (check_valid_direction(puzzle,"east"))
        {
            Puzzlestruct newpuzzle = puzzle;
            move_direction(newpuzzle, "east");
            bool a = true;
            for (int i = 0; i< index; i++)
            {
                if (wachtrij[i].candidate == newpuzzle)
                    a = false;
            }
            if (a)
                wachtrij.push_back({newpuzzle, index});
        }
    if (check_valid_direction(puzzle,"south"))
        {
            Puzzlestruct newpuzzle = puzzle;
            move_direction(newpuzzle, "south");
            bool a = true;
            for (int i = 0; i< index; i++)
            {
                if (wachtrij[i].candidate == newpuzzle)
                    a = false;
            }
            if (a)
                wachtrij.push_back({newpuzzle, index});
        }
    if (check_valid_direction(puzzle,"west"))
        {
            Puzzlestruct newpuzzle = puzzle;
            move_direction(newpuzzle, "west");
            bool a = true;
            for (int i = 0; i< index; i++)
            {
                if (wachtrij[i].candidate == newpuzzle)
                    a = false;
            }
            if (a)
                wachtrij.push_back({newpuzzle, index});
        }
}

void breadt_first_search(Puzzlestruct startpuzzle)
{
    //              
    assert(true);
    //                                                                                     
    vector<Candidatestruct> wachtrij = {{startpuzzle, -1}};
    int index = 0;

    while(index < wachtrij.size() && !is_done(wachtrij[index].candidate))
    {
        if (index % 100 == 0)
            cout << "current puzzle is " << index << "(displayed per 100 puzzles)" << endl;
        extend_wachtrij(wachtrij[index].candidate, wachtrij, index);
        index++;

    }
        if (index < wachtrij.size())
            show_path(wachtrij,index);
        else cout << "no solutions found" << endl;
}

void depth_first_search(Puzzlestruct puzzle, int max_depth, int& shortest_length, int path_length, Puzzlestruct& shortest_solution)
{
    //              
    assert(max_depth > 0);
    //                                                                                   
    if (is_done(puzzle) && path_length < shortest_length)
        {shortest_length = path_length;
        shortest_solution = puzzle;
        return;
        }

    else if (is_done(puzzle))
    {
        return;
    }
    else if(path_length > shortest_length)
        return;

    else if (path_length > max_depth)
        {
        return;
        }

    if (check_valid_direction(puzzle,"north"))
    {
        Puzzlestruct newpuzzle = puzzle;
        move_direction(newpuzzle, "north");
        depth_first_search(newpuzzle, max_depth, shortest_length, path_length+1 ,shortest_solution);
    }

    if (check_valid_direction(puzzle,"east"))
    {
        Puzzlestruct newpuzzle = puzzle;
        move_direction(newpuzzle, "east");
        depth_first_search(newpuzzle,max_depth,shortest_length, path_length+1,shortest_solution);
    }

        if (check_valid_direction(puzzle,"south"))
    {
        Puzzlestruct newpuzzle = puzzle;
        move_direction(newpuzzle, "south");
        depth_first_search(newpuzzle,max_depth,shortest_length, path_length+1,shortest_solution);
    }

        if (check_valid_direction(puzzle,"west"))
    {
        Puzzlestruct newpuzzle = puzzle;
        move_direction(newpuzzle, "west");
        depth_first_search(newpuzzle,max_depth,shortest_length, path_length+1,shortest_solution);
    }
}

 int main()
{
    ifstream infile;
    Puzzlestruct puzzle = {};
    open_file(infile);
    read_puzzle(infile, puzzle);
    cout << "BREADTH FIRST SEARCH STARTED" << endl << endl << endl;
    breadt_first_search(puzzle);
    cout << "BREADTH FIRST SEARCH FINISHED" << endl << endl<< endl;
    int shortest_length = 30;
    int path_length = 0;
    int max_depth = 30;
    Puzzlestruct shortest_solution = puzzle;

    cout << "DEPTH FIRST SEARCH STARTED" << endl << endl << endl;
    depth_first_search(puzzle, max_depth, shortest_length, path_length, shortest_solution);
    show_puzzle(shortest_solution);
    cout << "DEPTH FIRST SEARCH FINISHED" << endl << endl<< endl;

    return 0;

}

