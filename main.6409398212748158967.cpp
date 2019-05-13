//             
//                            

#include <iostream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

enum Cell {emptyC, emptyDest, box, boxOnDest, wall, workerOnEmptyC, workerOnDest};

enum Direction {north, east, south, west};

const vector<Direction> ALL_DIRECTIONS = {north, east, south, west};

struct Pos
{
    int x;
    int y;
};

struct World
{
    Pos worker;
    vector<vector<Cell>> env;
};

struct Candidate
{
    World candidate;
    int parent_candidate;
};

bool operator== (const World& w1, const World& w2)
{//               
    assert (true) ;
/*                 
                                       
*/
    if(w1.worker.x != w2.worker.x) return false;
    if(w1.worker.y != w2.worker.y) return false;
    if(w1.env.size() != w2.env.size()) return false;

    for(int i = 0; i < w1.env.size(); i++)
    {
        if(w1.env[i].size() != w2.env[i].size()) return false;
        for(int j = 0; j < w2.env[i].size(); j++)
            if(w1.env[i][j] != w2.env[i][j]) return false;
    }

    return true;
}

bool readChar(const char& ch, Cell& ce)
{//               
    assert (true) ;
/*                 
                                                                                                                   
*/
    switch(ch)
    {
        case '*':
            ce = wall;
            return true;
        case ' ':
            ce = emptyC;
            return true;
        case '.':
            ce = emptyDest;
            return true;
        case 'w':
            ce = workerOnEmptyC;
            return true;
        case 'W':
            ce = workerOnDest;
            return true;
        case 'b':
            ce = box;
            return true;
        case 'B':
            ce = boxOnDest;
            return true;
        default:
            return false;
    }
}

void readWorld(World& world, string filename)
{//               
    assert (true) ;
/*                 
                                                                        
*/
    ifstream inFile (filename.c_str());
    if(!inFile.is_open())
    {
       cout << "File could not be found!" << endl;
       return;
    }
    else
    {
        cout << "File opened!" << endl;
    }

    char ch = 'x';
    Cell ce;
    while(inFile)
    {
        vector<Cell> row;
        inFile.get(ch);
        while(readChar(ch, ce) && inFile)
        {
            row.push_back(ce);
            inFile.get(ch);
        }
        world.env.push_back(row);
    }
    for(int i = 0; i < world.env.size(); i++)
    {
        for(int j = 0; j < world.env[i].size(); j++)
        {
            if(world.env[i][j] == workerOnDest)
            {
                world.env[i][j] = emptyDest;
                world.worker.x = j;
                world.worker.y = i;
            }
            if(world.env[i][j] == workerOnEmptyC)
            {
                world.env[i][j] = emptyC;
                world.worker.x = j;
                world.worker.y = i;
            }
        }
    }

}

char showCell(const Cell& ce)
{//               
    assert (true) ;
/*                 
                                                           
*/
    switch(ce)
    {
        case wall:
            return '*';
        case emptyC:
            return ' ';
        case emptyDest:
            return '.';
        case box:
            return 'b';
        case boxOnDest:
            return 'B';
        default:
            return '?';
    }
}

void showWorld(const World& world)
{//               
    assert (true) ;
/*                 
                             
*/
    for(int i = 0; i < world.env.size(); i++)
    {
        for(int j = 0; j < world.env[i].size(); j++)
        {
            char ch = showCell(world.env[i][j]);
            if(ch == ' ' && world.worker.x == j && world.worker.y == i) ch = 'w';
            if(ch == '.' && world.worker.x == j && world.worker.y == i) ch = 'W';
            cout << ch;
        }
        cout << endl;
    }
}

bool isValidWorld(World& world)
{//               
    assert (true) ;
/*                 
                                                                                                             
*/
    int boxDestinationRelation = 0;
    for(int i = 0; i < world.env.size(); i++)
        for(int j = 0; j < world.env[i].size(); j++)
        {
            if(world.env[i][j] == emptyDest) boxDestinationRelation++;
            if(world.env[i][j] == box) boxDestinationRelation--;
        }
    return (0 == boxDestinationRelation);
}

bool isSolution(World& world)
{//               
    assert (true) ;
/*                 
                                                     
*/
    for(int i = 0; i < world.env.size(); i++)
    {
        for(int j = 0; j < world.env[i].size(); j++)
        {
            if(world.env[i][j] == emptyDest) return false;
        }
    }
    return true;
}

bool isPresent(vector<Candidate> c, World newW)
{//               
    assert (true) ;
/*                 
                                                                                        
*/
    for(int i = 0; i < c.size(); i++)
        if(newW == c[i].candidate) return true;
    return false;
}

bool isPresent(vector<World> v, World newW)
{//               
    assert (true) ;
/*                 
                                                                       
*/
    for(int i = 0; i < v.size(); i++)
        if(newW == v[i]) return true;
    return false;
}

void showSolution(vector<Candidate> c, int i, int counter)
{//               
    assert (true) ;
/*                 
                                                                                            
*/
    if(i >= 0)
    {
        showSolution(c, c[i].parent_candidate, counter+1);
        showWorld(c[i].candidate);
    }
    else cout << "The solution took " << counter-1 << " steps" << endl;
}

void showSolution(vector<World> solution)
{//               
    assert (true) ;
/*                 
                                                                                                
*/
    if(solution.size() == 0)
    {
        cout << "No Solution found in the given bound!" << endl;
        return;
    }
    cout << "The solution is " << solution.size()-1 << " steps long!" << endl;
    for(int i = 0; i < solution.size(); i++)
        showWorld(solution[i]);
}

void getNextPositions(Pos& p1, Pos& p2, Direction d)
{//               
    assert (true) ;
/*                 
                                                                                                                                      
*/
    switch(d)
    {
        case north:
            p1.y -= 1;
            p2.y -= 2;
            break;
        case south:
            p1.y += 1;
            p2.y += 2;
            break;
        case west:
            p1.x -= 1;
            p2.x -= 2;
            break;
        case east:
            p1.x += 1;
            p2.x += 2;
            break;
    }
}

void takeMove(World& w, Direction d)
{//               
    assert (true) ;
/*                 
                                                                       
*/
    Pos p1 = {w.worker.x, w.worker.y};
    Pos p2 = {w.worker.x, w.worker.y};
    getNextPositions(p1, p2, d);

    w.worker = p1;
    if(w.env[p1.y][p1.x] == box)
    {
        w.env[p1.y][p1.x] = emptyC;
        if(w.env[p2.y][p2.x] == emptyC) w.env[p2.y][p2.x] = box;
        else w.env[p2.y][p2.x] = boxOnDest;
    }
    if(w.env[p1.y][p1.x] == boxOnDest)
    {
        w.env[p1.y][p1.x] = emptyDest;
        if(w.env[p2.y][p2.x] == emptyC) w.env[p2.y][p2.x] = box;
        else w.env[p2.y][p2.x] = boxOnDest;
    }
}

bool canGo(const World& world, const Direction d)
{//               
    assert (true) ;
/*                 
                                                               
*/
    Pos p1 = {world.worker.x, world.worker.y};
    Pos p2 = {world.worker.x, world.worker.y};

    getNextPositions(p1, p2, d);

    if(p1.x >= 0 && p1.y >= 0 && p1.y < world.env.size())
        if(p1.x < world.env[p1.y].size())
            if(world.env[p1.y][p1.x] < 2) return true;
    if(p2.y < world.env.size() && p2.x >= 0 && p2.y >= 0)
        if(p2.x < world.env[p2.y].size())
            if(world.env[p2.y][p2.x] < 2 && world.env[p1.y][p1.x] < 4) return true;
    return false;
}

void triesBF(vector<Candidate>& c, int i, Direction d)
{//               
    assert (true) ;
/*                 
                                     
*/
    World newW = c[i].candidate;
    takeMove(newW, d);
    Candidate newC = {newW, i};
    if(!isPresent(c, newW))
    {
        c.push_back(newC);
    }
}

void solveBreadthFirst(World start)
{//               
    assert (true) ;
/*                 
                                                        
*/
    vector<Candidate> c = {{start, -1}};
    int i = 0;

    while(i < c.size() && !isSolution(c[i].candidate))
    {
        World world = c[i].candidate;
        for(int dir = 0; dir < 4; dir++)
            if(canGo(world, ALL_DIRECTIONS[dir])) triesBF(c, i, ALL_DIRECTIONS[dir]);
        i++;
    }
    if(i < c.size())
    {
        cout << "Solution found!" << endl << endl;
        showSolution (c, i, 0);

    }
    else cout << "No solution found!" << endl;
}

void solveDepthFirst(vector<World>& attempt, vector<World>& shortest, int maxDepth);

void triesDF(vector<World>& attempt, Direction d, vector<World>& shortest, int maxDepth)
{//               
    assert (true) ;
/*                 
                                                       
                                                                         
*/
    World w = attempt[attempt.size() - 1];
    World newW = w;
    takeMove(newW, d);
    if(!isPresent(attempt, newW))
    {
        attempt.push_back(newW); //        
        solveDepthFirst(attempt, shortest, maxDepth);
        attempt.pop_back();
    }
}

void solveDepthFirst(vector<World>& attempt, vector<World>& shortest, int maxDepth)
{//               
    assert (true) ;
/*                 
                                                       
                                                                         
*/
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    World world = attempt[CURRENT - 1];
    if(BEST > 0 && CURRENT >= BEST) {return;}
    else if(CURRENT > maxDepth + 1) {return;}
    else if(isSolution(world))
    {
        shortest = attempt;
        return;
    }
    for(int dir = 0; dir < 4; dir++)
            if(canGo(world, ALL_DIRECTIONS[dir])) triesDF(attempt, ALL_DIRECTIONS[dir], shortest, maxDepth);
}

int main()
{
    string challenge = "34";
    string inFilename = "challenge." + challenge + ".txt";
    World world;
    readWorld(world, inFilename);
    //                         
    vector<World> attempt = {world};
    vector<World> shortest;
    solveDepthFirst(attempt, shortest, 30);
    cout << "show sol";
    showSolution(shortest);
}

