//                         
//                            

#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;
const int MAX_LINES = 20;
const int MAX_LINE_CHARS = 100;

enum Cell {Wall, Empty, Destination, Worker, Box, BoxFinal};

Cell char_to_cell(char c)
{
    if(c == '*')
        return Wall;
    else if(c == ' ')
        return Empty;
    else if(c == '.')
        return Destination;
    else if(c == 'w' || c == 'W')
        return Worker;
    else if(c == 'b')
        return Box;
    else if(c == 'B')
        return BoxFinal;
}

char cell_to_char(Cell c)
{
    if(c == Wall)
        return '*';
    else if(c == Empty)
        return ' ';
    else if(c == Destination)
        return '.';
    else if(c == Worker)
        return 'w';
    else if(c == Box)
        return 'b';
    else if(c == BoxFinal)
        return 'B';
}

struct Position
{
    int line;
    int column;
};

struct Puzzle
{
    vector<string> puzzle;
    Position warehouse_keeper;
};

struct Candidate
{
    Puzzle Candidate;
    int parent_candidate;
};

bool read_file(ifstream& infile, vector<string>& puzzle)
{
    //    
    assert(!infile.is_open());
    //     
    //                                              
    string filename;
    char filetext[MAX_LINES][MAX_LINE_CHARS];
    cout << "What is the name of the file? (please add .txt):\n";
    cin >> filename;
    infile.open(filename.c_str());
    if(infile)
    {
        int c = 0;
        while(infile)
        {
            infile.getline(filetext[c], MAX_LINE_CHARS, '\n');
            puzzle.push_back(filetext[c]);
            c++;
        }
        cout << "The file was read correctly.\n";
        return true;
    }
    cout << "Unfortunately, the file could not be accessed. Please try again later.\n";
    return false;
}

void display_game(vector<string>& puzzle)
{
    //    
    assert(true);
    //     
    //                                 
    for(int i = 0; i < MAX_LINES; i++)
    {
        cout << puzzle[i] << endl;
    }
}

char char_on_line(vector<string>& puzzle, int line, int column)
{
    //    
    assert(line >= 0 && line <= MAX_LINES && column >= 0 && columns <= MAX_LINE_CHARS);
    //     
    //                                                                   
    return puzzle[line].c_str()[column];
}

bool operator==(const Puzzle& a, const Puzzle& b)
{
    //    
    assert(true);
    //     
    //                                                                   
    for(int i = 0; i < MAX_LINES; i++)
    {
        for(int j = 0; i < MAX_LINE_CHARS; j++)
        {
            if(char_on_line(a, i, j) != char_on_line(b, i, j))
            {
                return false;
            }
        }
    }
    return true;
}

bool puzzle_done(Puzzle puzzle)
{
    //    
    assert(true);
    //     
    //                                                
    for(int i = 0; i < MAX_LINES; i++)
    {
        for(int j = 0; j < MAX_LINE_CHARS)
        {
            if(char_on_line(puzzle, i, j) == 'b')
            {
                return false;
            }
        }
    }
    return true;
}

bool puzzle_done(vector<Candidate> candidate, Puzzle puzzle, int total_count)
{
    //    
    assert(true);
    //     
    //                                                                        
    for(int i = 0; i < total_count; i++)
    {
        if(candidate[i].Candidate.puzzle == puzzle.puzzle)
        {
            return true;
        }
    }
    return false;
}

Position warehouse_keeper_start(vector<string>& puzzle)
{
    //    
    assert(true);
    //     
    //                                                          
    for(int i = 0; i<MAX_LINES; i++)
    {
        for(int j = 0; j<MAX_LINE_CHARS; j++)
        {
            if(puzzle[i][j] == 'w' || puzzle[i][j] == 'W')
            {
                return {i,j};
            }
        }
    }
}

Puzzle move_warehouse_worker(Puzzle puzzle, Position newpos)
{
    //    
    assert(newpos.column > 0 && newpos.line > 0 && newpos.column < MAX_LINE_CHARS && newpos.line < MAX_LINES);
    //     
    //                                                                           
    Puzzle newpuzzle = puzzle;
    newpuzzle.warehouse_keeper = newpos;
    bool box = false;
    bool Box = false;
    bool D = false;
    int movement_column = newpos.column - puzzle.warehouse_keeper.column;
    int movement_line = newpos.line - puzzle.warehouse_keeper.line;
    switch(char_to_cell(char_on_line(puzze, newpos.line, newpos.column)))
    {
        case Empty: break;
        case Destination: D = true;
        case Box: box = true;
        case BoxFinal: Box = true;
    }
    if(box)
    {
        newpuzzle.puzzle[newpos.line][newpos.column] = 'w';
        newpuzzle.puzzle[newpos.line + movement_line][newpos.column + movement_column] = 'b';
        if(puzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == 'w')
        {
            newpuzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == ' ';
        }
        else if(puzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == 'W')
        {
            newpuzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == '.';
        }
    }
    if(Box)
    {
        newpuzzle.puzzle[newpos.line][newpos.column] = 'W';
        newpuzzle.puzzle[newpos.line + movement_line][newpos.column + movement_column] = 'B';
        if(puzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == 'w')
        {
            newpuzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == ' ';
        }
        else if(puzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == 'W')
        {
            newpuzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == '.';
        }
    }
    if(D)
    {
        newpuzzle.puzzle[newpos.line][newpos.column] = 'W';
        if(puzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == 'w')
        {
            newpuzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == ' ';
        }
        else if(puzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == 'W')
        {
            newpuzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == '.';
        }
    }
    else{
        newpuzzle.puzzle[newpos.line][newpos.column] = 'w';
        if(puzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == 'w')
        {
            newpuzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == ' ';
        }
        else if(puzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == 'W')
        {
            newpuzzle.puzzle[puzzle.warehouse_keeper.line][puzzle.warehouse_keeper.column] == '.';
        }
    }
    return newpuzzle;
}

bool can_go_north(Puzzle puzzle)
{
    //    
    assert(true);
    //     
    //                                                                 
    switch(char_on_line(puzzle.puzzle, puzzle.warehouse_keeper.line + 1, puzzle.warehouse_keeper.column))
    {

        case 0: return false;
        case 1: return true;
        case 2: return true;
        case 4: if(char_on_line(puzzle.puzzle, puzzle.warehouse_keeper.line + 2, puzzle.warehouse_keeper.column) == (0 || 4)){return false;} //                                                              
                else{return true;}
        case 5: return true;
    }
}

bool can_go_south(Puzzle puzzle)
{
    //    
    assert(true);
    //     
    //                                                                 
    switch(char_on_line(puzzle.puzzle, puzzle.warehouse_keeper.line - 1, puzzle.warehouse_keeper.column))
    {
        case 0: return false;
        case 1: return true;
        case 2: return true;
        case 4: if(char_on_line(puzzle.puzzle, puzzle.warehouse_keeper.line - 2, puzzle.warehouse_keeper.column) == (0 || 4)){return false;}
                else{return true;}
        case 5: return false;
    }
}

bool can_go_east(Puzzle puzzle)
{
    //    
    assert(true);
    //     
    //                                                                
    switch(char_on_line(puzzle.puzzle, puzzle.warehouse_keeper.line , puzzle.warehouse_keeper.column + 1))
    {
        case 0: return false;
        case 1: return true;
        case 2: return true;
        case 4: if(char_on_line(puzzle.puzzle, puzzle.warehouse_keeper.line, puzzle.warehouse_keeper.column +2) == (0 || 4)){return false;}
                else{return true;}
        case 5: return false;
    }
}

bool can_go_west(Puzzle puzzle)
{
    //    
    assert(true);
    //     
    //                                                                
    switch(char_on_line(puzzle.puzzle, puzzle.warehouse_keeper.line, puzzle.warehouse_keeper.column - 1))
    {
        case 0: return false;
        case 1: return true;
        case 2: return true;
        case 4: if(char_on_line(puzzle.puzzle, puzzle.warehouse_keeper.line, puzzle.warehouse_keeper.column - 2) == (0 || 4)){return false;}
                else{return true;}
        case 5: return false;
    }
}

Position go_north(Puzzle puzzle)
{
    //    
    assert(true);
    //                                                      
    assert(can_go_north(puzzle));
    Position pos = pos = {puzzle.warehouse_keeper.line + 1, puzzle.warehouse_keeper.column};
    return pos;

}

Position go_south(Puzzle puzzle)
{
    //    
    assert(true);
    //                                                      
    assert(can_go_south(puzzle));
    Position pos = {puzzle.warehouse_keeper.line - 1, puzzle.warehouse_keeper.column};
    return puzzle.warehouse_keeper;
}

Position go_east(Puzzle puzzle)
{
    //    
    assert(true);
    //                                                     
    assert(can_go_east());
    Position pos = {puzzle.warehouse_keeper.line, puzzle.warehouse_keeper.column + 1};
    return pos;
}

Position go_west(Puzzle puzzle)
{
    //    
    assert(true);
    //                                                     
    assert(can_go_west());
    Position pos = {puzzle.warehouse_keeper.line, puzzle.warehouse_keeper.column - 1};
    return pos;
}

void Candidate_check(vector<Candidate>& candidate, int total_count, Position newpos)
{
    //    
    assert(total_count >= 0);
    //     
    //                                                                                          
    Puzzle puzzle = cand[total_count].candidate;
    Puzzle newpuzzle = move_warehouse_worker(puzzle, newpos);
    if(!puzzle_done(candidate, puzzle, total_count))
    {
        cand.push_back({newpos, i});
    }
}

int Breadth(Puzzle puzzle)
{
    //    
    assert(true);
    //     
    //                                                                    
    vector<Candidate> candidate = {{puzzle, -1}};
    int total_count = 0;
    while(counter<candidate.size() && !puzzle_done(candidate[total_count].Candidate))
    {
        Puzzle this_puzzle = candidate[total_count].Candidate;
        if(can_go_north(this_puzzle))
            Candidate_check(candidate, total_count, go_north(this_puzzle));
        if(can_go_south(this_puzzle))
            Candidate_check(candidate, total_count, go_south(this_puzzle));
        if(can_go_east(this_puzzle))
            Candidate_check(candidate, total_count, go_east(this_puzzle));
        if(can_go_west(this_puzzle))
            Candidate_check(candidate, total_count, go_west(this_puzzle));
        total_count++;
    }
    if(total_count < candidate.size())
    {
        show_puzzle(candidate[candidate.size()-1].Candidate);
        return candidate[candidate.size()-1].parent_candidate+1
    }

}

int main()
{
    ifstream infile;
    vector<string> puzzle;
    read_file(infile, puzzle);
    display_game(puzzle);
    cout << "The amount of moves required for a solution is: " << Breadth(puzzle) << endl;
    return 0;
}

//                                                                         
//                                                                   
//          

