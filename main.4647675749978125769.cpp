#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

//                                                                                

int ROWS = 0;       //                                                                                                       
int COLUMNS = 0;    //                                            
enum Object : char {wall = '*', empt = ' ', box = 'b', boxG = 'B', player ='w', playerG ='W', goal = '.', error = '!'}; //                                                                                                         
int MAX_ITER = 900; //                                                                                                
bool duplicateFlag = false; //                                                                  

struct Node
{
    vector<vector<Object>> field;
    int workerX;
    int workerY;
    int parentID;
};

//                                                                                                                                                
//                                           
bool InputFile(ifstream& input)
{
//               
    assert (input);
/*                
                                                                                                                                                      
                                          
*/
    string filename;
    cout << "Please enter the file name of the challenge you would like to solve (with .txt extension):\n";
    cin >> filename;
    input.open(filename);
    if (input.is_open())
        return true;
    else
        return false;
}

//                                                             
bool LegalMove(Node current, int x, int y)
{
//               
    assert (true);
/*                
                                                                                        
*/
    return(current.workerX + x >= 0 && current.workerX + x < COLUMNS && current.workerY + y >= 0 && current.workerY + y < ROWS && !(x != 0 && y != 0));
}

bool MoveObject(Node& current, int fromX, int fromY, int toX, int toY)
{
//               
    assert (true);
/*                
                                                                                                                                                   
                                                                                                      
*/
    Object local = current.field[fromY][fromX];
    Object next = current.field[fromY + toY][fromX + toX];

    if (local == player && next == wall)
        return false;
    else if(local == player && next == goal)
    {
        current.field[fromY][fromX] = empt;
        current.field[fromY + toY][fromX + toX] = playerG;
        current.workerX += toX;
        current.workerY += toY;
        return true;
    }
    else if(local == player && next == empt)
    {
        current.field[fromY][fromX] = empt;
        current.field[fromY + toY][fromX + toX] = player;
        current.workerX += toX;
        current.workerY += toY;
        return true;
    }
    else if(local == playerG && next == goal)
    {
        current.field[fromY][fromX] = goal;
        current.field[fromY + toY][fromX + toX] = playerG;
        current.workerX += toX;
        current.workerY += toY;
        return true;
    }
    else if(local == playerG && next == empt)
    {
        current.field[fromY][fromX] = goal;
        current.field[fromY + toY][fromX + toX] = player;
        current.workerX += toX;
        current.workerY += toY;
        return true;
    }
    else if((local == box || local == boxG) && (next == wall || next == box || next == boxG))
        return false;
    else if (local == box && next == empt)
    {
        current.field[fromY][fromX] = empt;
        current.field[fromY + toY][fromX + toX] = box;
        return true;
    }
    else if (local == box && next == goal)
    {
        current.field[fromY][fromX] = empt;
        current.field[fromY + toY][fromX + toX] = boxG;
        return true;
    }
    else if (local == boxG && next == empt)
    {
        current.field[fromY][fromX] = goal;
        current.field[fromY + toY][fromX + toX] = box;
        return true;
    }
    else if (local == boxG && next == goal)
    {
        current.field[fromY][fromX] = goal;
        current.field[fromY + toY][fromX + toX] = boxG;
        return true;
    }
    else if (local == player && next == box)
    {
        if(MoveObject(current, fromX + toX, fromY + toY, toX, toY));
        {
            current.field[fromY][fromX] = empt;
            current.field[fromY + toY][fromX + toX] = player;
            current.workerX += toX;
            current.workerY += toY;
            return true;
        }
        return false;
    }
    else if (local == playerG && next == box)
    {
        if(MoveObject(current, fromX + toX, fromY + toY, toX, toY));
        {
            current.field[fromY][fromX] = goal;
            current.field[fromY + toY][fromX + toX] = player;
            current.workerX += toX;
            current.workerY += toY;
            return true;
        }
        return false;
    }
    else if (local == player && next == boxG)
    {
        if(MoveObject(current, fromX + toX, fromY + toY, toX, toY));
        {
            current.field[fromY][fromX] = empt;
            current.field[fromY + toY][fromX + toX] = playerG;
            current.workerX += toX;
            current.workerY += toY;
            return true;
        }
        return false;
    }
    else if (local == playerG && next == boxG)
    {
        if(MoveObject(current, fromX + toX, fromY + toY, toX, toY));
        {
            current.field[fromY][fromX] = goal;
            current.field[fromY + toY][fromX + toX] = playerG;
            current.workerX += toX;
            current.workerY += toY;
            return true;
        }
        return false;
    }

    return false;
}

void AssignPlayer(Node& current)
{
//               
    assert (true);
/*                
                                                                                                                                   
*/
    for(int i = 0; i < COLUMNS; i++)
        for(int j = 0; j < ROWS; j++)
        {
            if(current.field[j][i] == player || current.field[j][i] == playerG)
            {
                current.workerX = i;
                current.workerY = j;
                return;
            }
        }
}

void PrintWorld(vector<vector<Object>>& world) //                                                           
{
//               
    assert (true);
/*                
                                    
*/
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
            cout << (char)world[i][j];
        cout << "\n";
    }
}

bool CheckSolution(Node target)
{
//               
    assert (true);
/*                
                                                                                                                                             
*/
    for(int a = 0; a < ROWS; a++)
        for(int b = 0; b < COLUMNS; b++)
            if (target.field[a][b] == goal || target.field[a][b] == playerG)
                    return false;
    return true;
}

bool CompareFields(Node f, Node g)
{
//               
    assert (true);
/*                
                                                                           
*/
    for(int a = 0; a < ROWS; a++)
        for(int b = 0; b < COLUMNS; b++)
            if(f.field[a][b] != g.field[a][b])
                    return false;
    return true;
}

//                                                             
bool CheckNotDuplicate(vector<Node>& tree, Node target)
{
//               
    assert (true);
/*                
                                                                           
*/
    int counter = 0;
    for(int i=0; i < tree.size(); i++)
    {
        if(!CompareFields(target, tree[i]))
            counter++;
    }
    return (counter == tree.size());
}

void AddIteration(vector<Node>& tree, Node old, int workerX, int workerY, int x, int y, int parentID)
{
//               
    assert (true);
/*                
                                                                                                                                                   
                           
*/
    duplicateFlag = false; //                       
    Node newNode;
    newNode.field = old.field;
    newNode.workerX = workerX;
    newNode.workerY = workerY;
    newNode.parentID = parentID;
    MoveObject(newNode, newNode.workerX, newNode.workerY, x, y);
    if(CheckNotDuplicate(tree, newNode))
        tree.push_back(newNode);
    else
        duplicateFlag = true; //                            
}

int BFS(vector<vector<Object>> init, vector<Node>& tree)
{
    Node current;
    int counter = -1;
    current.field = init;
    current.parentID = counter;
    AssignPlayer(current);
    tree.push_back(current);

    while((int)tree.size() > counter + 1)
    {
        counter++;
        current.workerX = tree[counter].workerX;
        current.workerY = tree[counter].workerY;
        current.parentID = counter;
        current.field = tree[current.parentID].field;

        if(CheckSolution(current))
            return counter;

        if(LegalMove(current, 1, 0))
            AddIteration(tree, current, current.workerX, current.workerY, 1, 0, counter);

        if(LegalMove(current, -1, 0))
            AddIteration(tree, current, current.workerX, current.workerY, -1, 0, counter);

        if(LegalMove(current, 0, 1))
            AddIteration(tree, current, current.workerX, current.workerY, 0, 1, counter);

        if(LegalMove(current, 0, -1))
            AddIteration(tree, current, current.workerX, current.workerY, 0, -1, counter);

    }
    return -1;
}

int SolutionLengthBFS(vector<Node> tree, Node solution)
{
    int counter = 0;
    Node temp = solution;
    while (temp.parentID != -1)
    {
        counter++;
        temp = tree[temp.parentID];
    }
    return counter;
}

//                                 
Object IsLegal(char target)
{
    switch(target)
    {
        case wall:
        case empt:
        case box:
        case boxG:
        case player:
        case playerG:
        case goal:  return (Object)target;
        default:    return error;
    }
}

//                                                                                                                                        
//                                                              
vector<vector<Object>> MakeWorld(ifstream& input)
{
//               
    assert (input.is_open());
/*                
                                         
                                                                                                               
*/
    vector<vector<Object>> field;
    vector<Object> line;
    string temp;
    while (getline(input, temp))
    {
        line.clear();
        for(int i = 0; i < temp.length(); i++)
            line.push_back(IsLegal(temp[i]));
        field.push_back(line);
        ROWS++;
        COLUMNS = temp.length(); //                                                         
    }
    input.close(); //                                                                                         
    return field;
}

//                                                                                                                                                  
void DFS(Node current, vector<Node>& tree, vector<Node>& best)
{
    if (tree.size() > MAX_ITER)
    {
        tree.pop_back();
        return;
    }
    if (tree.size() >= best.size())
    {
        tree.pop_back();
        return;
    }
    if (CheckSolution(current))
    {
        if (tree.empty())
            tree.push_back(current);
        best = tree;
        return;
    }
    else
    {
        if (LegalMove(current, 1, 0))
        {
            AddIteration(tree, current, current.workerX, current.workerY, 1, 0, 0);
            if (!duplicateFlag)
            {
                DFS(tree.back(), tree, best);
            }
        }
        if (LegalMove(current, -1, 0))
        {
            AddIteration(tree, current, current.workerX, current.workerY, 0, 1, 0);
            if (!duplicateFlag)
            {
                DFS(tree.back(), tree, best);
            }
        }
        if (LegalMove(current, 0, 1))
        {
            AddIteration(tree, current, current.workerX, current.workerY, -1, 0, 0);
            if (!duplicateFlag)
            {
                DFS(tree.back(), tree, best);
            }
        }
        if (LegalMove(current, 0, -1))
        {
            AddIteration(tree, current, current.workerX, current.workerY, 0, -1, 0);
            if (!duplicateFlag)
            {
                DFS(tree.back(), tree, best);
            }
        }
    }
}

int main()
{
    //                                             
    ifstream input;
    if (!InputFile(input))
    {
        cout << "ERROR ERROR"; //                                                              
        return -1;
    }
    vector<vector<Object>> world = MakeWorld(input);
    vector<Node> tree;
    //                           
    int solutionIndex;
    solutionIndex = BFS(world, tree);
    if (solutionIndex == -1)
    {
        cout << "There is no solution." << endl;
        return 0;
    }
    cout << "Solution:" << endl;
    PrintWorld(tree[solutionIndex].field);
    cout << endl;
    cout << "It took " << SolutionLengthBFS(tree, tree[solutionIndex]) << " step(s) to find a solution." << endl;
    //                         
    Node nothingHere;
    Node first = {world, 0, 0, 0};
    AssignPlayer(first);
    vector<Node> best(1000, nothingHere);
    DFS(first, tree, best);
    if (best.size() >= MAX_ITER)
        cout << "Could not find a solution." << endl;
    else
    {
        cout << "Solution:" << endl;
        PrintWorld(best.back().field);
        cout << "It took " << best.size() << " step(s) to find a solution." << endl;
    }
    return 0;
}

