#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

//                                                               

using namespace std;

int Direction[4][2] {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct Steps{
    vector<vector<char>> Combination;
    int StepCount;
};

struct Point{
    int Row;
    int Column;
};

void PrintPuzzle (vector<vector<char>>& Puzzle){
    //                       
    assert(true);
    //                       
    for (vector<char> PuzzleLine: Puzzle) {
        for (char Character: PuzzleLine)
            cout << Character;
        cout << endl;
    }
}

void operator>>(ifstream& file, vector<vector<char>>& Puzzle){
    //                       
    assert(true);
    //                                                     
    string Line;
    while(getline(file, Line)){
        vector<char> PuzzleLine;
        for (char Character: Line) {
            PuzzleLine.push_back(Character);
        }
        Puzzle.push_back(PuzzleLine);
    }
}

bool CheckIfCompleted (vector<vector<char>> Puzzle){
    //                       
    assert(true);
    //                                                   
    for (vector<char> PuzzleLine: Puzzle)
        for (char Character: PuzzleLine)
            if (Character == 'b')
                return false;
    return true;
}

bool Check(vector<vector<char>> Puzzle, int X, int Y, Point Worker){
    //                                    
    assert(Worker.Row < Puzzle.size() && Worker.Column < Puzzle[0].size());
    //                                                          
    if (Puzzle[Worker.Row + X][Worker.Column + Y] == ' ' || Puzzle[Worker.Row + X][Worker.Column + Y] == '.')
        return true;
    if (Puzzle[Worker.Row + X][Worker.Column + Y] == 'b' || Puzzle[Worker.Row + X][Worker.Column + Y] == 'B')
        return Puzzle[Worker.Row + 2*X][Worker.Column + 2*Y] == ' ' || Puzzle[Worker.Row + 2*X][Worker.Column + 2*Y] == '.';
    return false;
}

char Uncapped (char Character){
    //                                                    
    assert(Character > 64 && Character < 91 || Character > 96 && Character < 123);
    //                                                                                               
    if (Character < 91)
        return Character + 32;
    return Character;
}

char Capped (char Character) {
    //                                                    
    assert(Character > 64 && Character < 91 || Character > 96 && Character < 123);
    //                                                                                               
    if (Character > 96)
        return Character - 32;
    return Character;
}

Steps Try(Steps New, int X, int Y, Point WorB){
    //                                                                     
    assert(WorB.Row < New.Combination.size() && WorB.Column < New.Combination[0].size());
    //                                                                                
    char BoxWorker = New.Combination[WorB.Row][WorB.Column];
    Point B;
    char Character = New.Combination[WorB.Row + X][WorB.Column + Y];
    switch(Character) {
        case ' ': New.Combination[WorB.Row + X][WorB.Column + Y] = Uncapped(BoxWorker); New.StepCount += 1; break;
        case '.': New.Combination[WorB.Row + X][WorB.Column + Y] = Capped(BoxWorker);   New.StepCount += 1;break;
        case 'B': B.Row = WorB.Row + X; B.Column = WorB.Column + Y;
                  New = Try(New, X, Y, B); New.Combination[WorB.Row + X][WorB.Column + Y] = Capped(BoxWorker);break;
        case 'b': B.Row = WorB.Row + X; B.Column = WorB.Column + Y;
                  New = Try(New, X, Y, B); New.Combination[WorB.Row + X][WorB.Column + Y] = Uncapped(BoxWorker); break;
    }
    if (BoxWorker > 96)
        New.Combination[WorB.Row][WorB.Column] = ' ';
    else
        New.Combination[WorB.Row][WorB.Column] = '.';
    return New;
}

bool IsIn (vector<vector<char>> Puzzle, vector<Steps> Queue) {
    //                           
    assert(true);
    //                                                              
    for (Steps Step: Queue)
        if (Puzzle == Step.Combination )
            return false;
    return true;
}

void Create(vector<vector<char>> Puzzle, Point& W){
    //                       
    assert(true);
    //                                                  
    for (int Row = 0; Row < Puzzle.size(); Row++)
        for (int Column = 0; Column < Puzzle[Row].size(); Column++)
            if (Puzzle[Row][Column] == 'w' || Puzzle[Row][Column] == 'W'){
                W.Row = Row;
                W.Column = Column;
                return;
            }
}

int BreadthFirst (vector<vector<char>> Puzzle) {
    //                      
    assert(true);
    //                                                      
    vector<Steps> Queue;
    Steps Step; Step.Combination = Puzzle; Step.StepCount = 0;
    int Counter = 0;
    Queue.push_back(Step);
    Point W;
    while (true) {
        Create(Queue[Counter].Combination, W);
        for (int Direct = 0; Direct < 4; Direct++){
            if (Check(Queue[Counter].Combination, Direction[Direct][0], Direction[Direct][1], W)){
                Steps New = Try(Queue[Counter], Direction[Direct][0], Direction[Direct][1], W);
                if (CheckIfCompleted(New.Combination)) return New.StepCount;
                if (IsIn(New.Combination, Queue)) Queue.push_back(New);
            }
        }
        Counter++;
    }
}

int DepthFirst (vector<vector<char>> Puzzle, vector<Steps> Queue, int& Depth, int& Shortest, int& Bound) {
    //                                                                 
    assert(Depth <= Bound+1 && Shortest <= Bound);
    //                                                           
    if (Depth > Shortest || Depth > Bound)
        return Bound;
    Point W;
    Create(Puzzle, W);
    if (!CheckIfCompleted(Puzzle))
        for (int Direct = 0; Direct < 4; Direct++) {
            if (Check(Puzzle, Direction[Direct][0], Direction[Direct][1], W)) {
                Steps New;
                New.Combination = Puzzle;
                New.StepCount = Depth;
                New = Try(New, Direction[Direct][0], Direction[Direct][1], W);
                if (IsIn(New.Combination, Queue)) {
                    Queue.push_back(New);
                    DepthFirst(New.Combination, Queue, New.StepCount, Shortest, Bound);
                }
                Create(Puzzle, W);
            }
        }
    else if (Depth < Shortest)
        Shortest = Depth;
    return Shortest;
}

    int main() {
        vector<vector<char>> puzzle;
        ifstream file;
        file.open("challenge.23.txt");
        file >> puzzle;
        int Bound = 24;
        vector<Steps> Queue;
        int Depth = 0;
        cout << BreadthFirst(puzzle) << endl;
        cout << DepthFirst(puzzle, Queue, Depth, Bound, Bound) << endl;
    return 0;
}
