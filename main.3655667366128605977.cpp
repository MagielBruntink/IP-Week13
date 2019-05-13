#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define puzzleField vector<vector<char> >

//                                              

int g_rows;
int g_columns;

struct puzzleInfo
{
    puzzleField currentPuzzle;
    int parent;
    int worker_x;
    int worker_y;
};

bool openFile(string filepath, fstream& file)
{
    file.open(filepath.c_str());
    return file;
}

void readPuzzle(puzzleField& puzzle, fstream& infile, int& worker_x, int& worker_y){
    string line;
    while(getline(infile, line)){
        vector<char> temp;
        for (int i = 0; i < line.length(); i++){
            if (line[i] == 'W' || line[i] == 'w'){
                worker_x = g_rows;
                worker_y = i;
            }
            temp.push_back(line[i]);
        }
        puzzle.push_back(temp);
        g_rows++;
    }
}

bool checkDuplicates(puzzleField puzzle, vector<puzzleField>& stateList)
{
    for (int k = 0; k < stateList.size(); k++){
        bool temp = true;
        for (int i = 0; i < g_rows; i++)
            for (int j = 0; j < g_columns; j++)
                if (puzzle[i][j] != stateList[k][i][j])
                    temp = false;
        if (temp)
            return true;
    }
    return false;
}

void showPuzzle(puzzleField puzzle)
{
    for (int i = 0; i < puzzle.size(); i++){
        for (int j = 0; j < puzzle[i].size(); j++)
            cout << puzzle[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

bool correctPuzzle(puzzleField puzzle)
{
    for (int i = 0; i < puzzle.size(); i++)
        for (int j = 0; j < puzzle[i].size(); j++)
            if (puzzle[i][j] == 'b')
                return false;
    return true;
}

bool onCell(puzzleInfo puzzle)
{
    puzzleField temp = puzzle.currentPuzzle;
    int x = puzzle.worker_x;
    int y = puzzle.worker_y;
    if (temp[x][y] == 'w')
        return false;
    return true;
}

bool emptyCellInFront(puzzleInfo puzzle, int dx, int dy)
{
    puzzleField temp = puzzle.currentPuzzle;
    int x = puzzle.worker_x;
    int y = puzzle.worker_y;
    if (temp[x+dx][y+dy] == '.')
        return true;
    return false;
}

bool boxInFront(puzzleInfo puzzle, int dx, int dy)
{
    puzzleField temp = puzzle.currentPuzzle;
    int x = puzzle.worker_x;
    int y = puzzle.worker_y;
    if (temp[x+dx][y+dy] == 'b')
        return true;
    return false;
}

bool boxInFrontOnCell(puzzleInfo puzzle, int dx, int dy)
{
    puzzleField temp = puzzle.currentPuzzle;
    int x = puzzle.worker_x;
    int y = puzzle.worker_y;
    if (temp[x+dx][y+dy] == 'B')
        return true;
    return false;
}

bool cantMove(puzzleInfo puzzle, int dx, int dy)
{
    puzzleField temp = puzzle.currentPuzzle;
    int x = puzzle.worker_x;
    int y = puzzle.worker_y;
    if (temp[x+dx][y+dy] == 'B' && temp[x+2*dx][y+2*dy] == 'B')
        return true;
    else if (temp[x+dx][y+dy] == 'B' && temp[x+2*dx][y+2*dy] == 'b')
        return true;
    else if (temp[x+dx][y+dy] == 'b' && temp[x+2*dx][y+2*dy] == 'B')
        return true;
    else if (temp[x+dx][y+dy] == 'b' && temp[x+2*dx][y+2*dy] == 'b')
        return true;
    else if (temp[x+dx][y+dy] == 'B' && temp[x+2*dx][y+2*dy] == '*')
        return true;
    else if (temp[x+dx][y+dy] == 'b' && temp[x+2*dx][y+2*dy] == '*')
        return true;
    else if (temp[x+dx][y+dy] == '*')
        return true;
    return false;
}

puzzleField moveWorker(puzzleInfo& puzzle, int dx, int dy)
{
    puzzleField comp = puzzle.currentPuzzle;
    puzzleField temp = puzzle.currentPuzzle;
    int x = puzzle.worker_x;
    int y = puzzle.worker_y;
    if (cantMove(puzzle, dx, dy))
        return comp;
    if (onCell(puzzle))
        temp[x][y] = '.';
    else
        temp[x][y] = ' ';
    if (boxInFront(puzzle, dx, dy)){
        temp[x+dx][y+dy] = 'w';
        if (comp[x+2*dx][y+2*dy] == '.')
            temp[x+2*dx][y+2*dy] = 'B';
        else
            temp[x+2*dx][y+2*dy] = 'b';
    }
    else if (boxInFrontOnCell(puzzle, dx, dy)){
        temp[x+dx][y+dy] = 'W';
        if (comp[x+2*dx][y+2*dy] == '.')
            temp[x+2*dx][y+2*dy] = 'B';
        else
            temp[x+2*dx][y+2*dy] = 'b';
    }
    else if (emptyCellInFront(puzzle, dx, dy))
        temp[x+dx][y+dy] = 'W';
    else
        temp[x+dx][y+dy] = 'w';
    return temp;
}

void addNorth(vector<puzzleInfo>& tree, int i, vector<puzzleField>& stateList, bool& added)
{
    added = false;
    puzzleInfo temp = tree[i];
    puzzleField tempNorth = moveWorker(temp, -1, 0);
    if (!checkDuplicates(tempNorth, stateList)){
        added = true;
        temp.currentPuzzle = tempNorth;
        temp.parent = i;
        temp.worker_x = temp.worker_x - 1;
        tree.push_back(temp);
        stateList.push_back(temp.currentPuzzle);
    }
}

void addEast(vector<puzzleInfo>& tree, int i, vector<puzzleField>& stateList, bool& added)
{
    added = false;
    puzzleInfo temp = tree[i];
    puzzleField tempEast = moveWorker(temp, 0, 1);
    if (!checkDuplicates(tempEast, stateList)){
        added = true;
        temp.currentPuzzle = tempEast;
        temp.parent = i;
        temp.worker_y = temp.worker_y + 1;
        tree.push_back(temp);
        stateList.push_back(temp.currentPuzzle);
    }
}

void addSouth(vector<puzzleInfo>& tree, int i, vector<puzzleField>& stateList, bool& added)
{
    added = false;
    puzzleInfo temp = tree[i];
    puzzleField tempSouth = moveWorker(temp, 1, 0);
    if (!checkDuplicates(tempSouth, stateList)){
        added = true;
        temp.currentPuzzle = tempSouth;
        temp.parent = i;
        temp.worker_x = temp.worker_x + 1;
        tree.push_back(temp);
        stateList.push_back(temp.currentPuzzle);
    }
}

void addWest(vector<puzzleInfo>& tree, int i, vector<puzzleField>& stateList, bool& added)
{
    added = false;
    puzzleInfo temp = tree[i];
    puzzleField tempWest = moveWorker(temp, 0, -1);
    if (!checkDuplicates(tempWest, stateList)){
        added = true;
        temp.currentPuzzle = tempWest;
        temp.parent = i;
        temp.worker_y = temp.worker_y - 1;
        tree.push_back(temp);
        stateList.push_back(temp.currentPuzzle);
    }
}

void addChildren(vector<puzzleInfo>& tree, int i, vector<puzzleField>& stateList)
{
    puzzleInfo temp = tree[i];
    puzzleField tempNorth = moveWorker(temp, -1, 0);
    puzzleField tempEast = moveWorker(temp, 0, 1);
    puzzleField tempSouth = moveWorker(temp, 1, 0);
    puzzleField tempWest = moveWorker(temp, 0, -1);
    if (!checkDuplicates(tempNorth, stateList)){
        temp.currentPuzzle = tempNorth;
        temp.parent = i;
        temp.worker_x = temp.worker_x - 1;
        tree.push_back(temp);
        stateList.push_back(temp.currentPuzzle);
    }
    temp = tree[i];
    if (!checkDuplicates(tempEast, stateList)){
        temp.currentPuzzle = tempEast;
        temp.parent = i;
        temp.worker_y = temp.worker_y + 1;
        tree.push_back(temp);
        stateList.push_back(temp.currentPuzzle);
    }
    temp = tree[i];
    if (!checkDuplicates(tempSouth, stateList)){
        temp.currentPuzzle = tempSouth;
        temp.parent = i;
        temp.worker_x = temp.worker_x + 1;
        tree.push_back(temp);
        stateList.push_back(temp.currentPuzzle);
    }
    temp = tree[i];
    if (!checkDuplicates(tempWest, stateList)){
        temp.currentPuzzle = tempWest;
        temp.parent = i;
        temp.worker_y = temp.worker_y - 1;
        tree.push_back(temp);
        stateList.push_back(temp.currentPuzzle);
    }
}

void showSolution(vector<puzzleInfo> tree, int i, int& stepCounter)
{
    if (i < 0){
        return;
    }
    else{
        stepCounter++;
        showPuzzle(tree[i].currentPuzzle);
        showSolution(tree, tree[i].parent, stepCounter);
    }
}

/*
                       
*/
void solveBFS(vector <puzzleInfo>& tree, puzzleField initialPuzzle, int worker_x, int worker_y, vector<puzzleField>& stateList)
{
    int index = 0;
    while (index < tree.size() && !correctPuzzle(tree[index].currentPuzzle)){
        addChildren(tree, index, stateList);
        index++;
    }
    if (correctPuzzle(tree[index].currentPuzzle)){
        int stepCounter = 0;
        cout << "The shortest solution of the puzzle is:" << endl;
        showSolution(tree, index, stepCounter);
        cout << "It can be done in " << stepCounter << " steps." << endl;
    }
}

/*
                       
*/void solveDFS(vector <puzzleInfo>& tree, vector<puzzleField> stateList, int currentDepth, int& maxDepth, int index, int& bestSolutionSoFar)
{
    if (correctPuzzle(tree[index].currentPuzzle)){
        cout << "We found a solution!" << endl;
        if (bestSolutionSoFar == -1)
            bestSolutionSoFar = index;
        else if (tree[index].parent < tree[bestSolutionSoFar].parent)
            bestSolutionSoFar = index;
        maxDepth = currentDepth;
    }
    else if (currentDepth < maxDepth){
        puzzleField p = tree[index].currentPuzzle;
        bool added = false;
        addNorth(tree, index, stateList, added);
        if (added)
            solveDFS(tree, stateList, currentDepth+1, maxDepth, tree.size()-1, bestSolutionSoFar);
        addEast(tree, index, stateList, added);
        if (added)
            solveDFS(tree, stateList, currentDepth+1, maxDepth, tree.size()-1, bestSolutionSoFar);
        addSouth(tree, index, stateList, added);
        if (added)
            solveDFS(tree, stateList, currentDepth+1, maxDepth, tree.size()-1, bestSolutionSoFar);
        addWest(tree, index, stateList, added);
        if (added)
            solveDFS(tree, stateList, currentDepth+1, maxDepth, tree.size()-1, bestSolutionSoFar);
    }

}

int main()
{
    string filename = "challenge.23.txt";
    fstream infile;
    vector <puzzleField> stateList;
    int worker_x, worker_y;
    if (openFile(filename, infile)){
        cout << "File was opened." << endl;
        puzzleField puzzle;
        readPuzzle(puzzle, infile, worker_x, worker_y);
        stateList.push_back(puzzle);
        g_columns = puzzle[0].size();
        cout << g_rows << ' ' << g_columns << endl;
        showPuzzle(puzzle);
        puzzleInfo node;
        vector<puzzleInfo> tree;
        node.currentPuzzle = puzzle;
        node.parent = -1;
        node.worker_x = worker_x;
        node.worker_y = worker_y;
        tree.push_back(node);
        int bestSolutionSoFar = -1;
        int maxDepth = 35;
        int stepCounter = 0;
        cout << "Starting to solve" << endl;
        solveBFS(tree, puzzle, worker_x, worker_y, stateList);
        //                                                             
        cout << "We've found a solution with a depth of " << maxDepth << ":" << endl;
        //                                                   
    }
    else
        cout << "File couldn't be opened." << endl;
    return 0;
}

