#include <iostream>
#include <vector>
#include<fstream>
#include <stdexcept>
#include <assert.h>

using namespace std;

//                        

struct puzzle
{
    char puzzle[10][10]; //                                                                                  
    int location[2]; //                                    
    bool onFinal; //                                             
    int parent;
};

vector<puzzle> puzzleVec;
vector<puzzle> explored;
puzzle Solution;
int MAX_ITERATIONS = 25;
int best = MAX_ITERATIONS;

bool comparePuzzles(puzzle a, puzzle b)
{
    //             
    assert(true);
    //              
    //                                         
    for(int i =0; i<10; i++)
        for(int j=0; j<10; j++)
            if(a.puzzle[i][j] != b.puzzle[i][j])
                return false;
    return true;
}

bool cycle(puzzle a)
{
    //             
    assert(true);
    //              
    //                                       
    for(int i = 0; i < explored.size(); i++)
        if(comparePuzzles(a, explored.at(i)))
            return true;
    return false;
}

void findPlayer(puzzle& test)
{
    //             
    assert(true);
    //              
    //                                
    for(int i =0; i<10; i++)
        for(int j=0; j<10; j++)
            if(test.puzzle[i][j] == 'w' || test.puzzle[i][j] == 'W')
            {
                test.location[0] = i;
                test.location[1] = j;
            }
}

void fillPuzzle(puzzle& test)
{
    //             
    assert(true);
    //              
    //                 
    for(int i =0; i<10; i++)
        for(int j=0; j<10; j++)
            test.puzzle[i][j] = ' ';
    test.onFinal = false; //                                                                                     

}

bool solution(puzzle test)
{
    //             
    assert(true);
    //              
    //                                          
    for(int i =0; i<10; i++)
        for(int j=0; j<10; j++)
            if(test.puzzle[i][j] == 'b')
                return false;
    Solution = test;
    return true;
}

bool stepNorth(puzzle p)
{
    //             
    assert(true);
    //              
    //                                  
    return
        (p.puzzle[p.location[0] - 1][p.location[1]] == ' ') ||
        (p.puzzle[p.location[0] - 1][p.location[1]] == '.') ||
        (p.puzzle[p.location[0] - 1][p.location[1]] == 'b' && p.puzzle[p.location[0] - 2][p.location[1]] == ' ') ||
        (p.puzzle[p.location[0] - 1][p.location[1]] == 'b' && p.puzzle[p.location[0] - 2][p.location[1]] == '.') ||
        (p.puzzle[p.location[0] - 1][p.location[1]] == 'B' && p.puzzle[p.location[0] - 2][p.location[1]] == ' ') ||
        (p.puzzle[p.location[0] - 1][p.location[1]] == 'B' && p.puzzle[p.location[0] - 2][p.location[1]] == '.') ? true : false;
}
bool stepSouth(puzzle p)
{
    //             
    assert(true);
    //              
    //                                  
    return
        (p.puzzle[p.location[0] + 1][p.location[1]] == ' ') ||
        (p.puzzle[p.location[0] + 1][p.location[1]] == '.') ||
        (p.puzzle[p.location[0] + 1][p.location[1]] == 'b' && p.puzzle[p.location[0] + 2][p.location[1]] == ' ') ||
        (p.puzzle[p.location[0] + 1][p.location[1]] == 'b' && p.puzzle[p.location[0] + 2][p.location[1]] == '.') ||
        (p.puzzle[p.location[0] + 1][p.location[1]] == 'B' && p.puzzle[p.location[0] + 2][p.location[1]] == ' ') ||
        (p.puzzle[p.location[0] + 1][p.location[1]] == 'B' && p.puzzle[p.location[0] + 2][p.location[1]] == '.') ? true : false;
}
bool stepEast(puzzle p)
{
    //             
    assert(true);
    //              
    //                                 
    return
        (p.puzzle[p.location[0]][p.location[1] + 1] == ' ') ||
        (p.puzzle[p.location[0]][p.location[1] + 1] == '.') ||
        (p.puzzle[p.location[0]][p.location[1] + 1] == 'b' && p.puzzle[p.location[0]][p.location[1] + 2] == ' ') ||
        (p.puzzle[p.location[0]][p.location[1] + 1] == 'b' && p.puzzle[p.location[0]][p.location[1] + 2] == '.') ||
        (p.puzzle[p.location[0]][p.location[1] + 1] == 'B' && p.puzzle[p.location[0]][p.location[1] + 2] == ' ') ||
        (p.puzzle[p.location[0]][p.location[1] + 1] == 'B' && p.puzzle[p.location[0]][p.location[1] + 2] == '.') ? true : false;
}
bool stepWest(puzzle p)
{
    //             
    assert(true);
    //              
    //                                 
    return
        (p.puzzle[p.location[0]][p.location[1] - 1] == ' ') ||
        (p.puzzle[p.location[0]][p.location[1] - 1] == '.') ||
        (p.puzzle[p.location[0]][p.location[1] - 1] == 'b' && p.puzzle[p.location[0]][p.location[1] - 2] == ' ') ||
        (p.puzzle[p.location[0]][p.location[1] - 1] == 'b' && p.puzzle[p.location[0]][p.location[1] - 2] == '.') ||
        (p.puzzle[p.location[0]][p.location[1] - 1] == 'B' && p.puzzle[p.location[0]][p.location[1] - 2] == ' ') ||
        (p.puzzle[p.location[0]][p.location[1] - 1] == 'B' && p.puzzle[p.location[0]][p.location[1] - 2] == '.') ? true : false;
}

puzzle moveDir(char dir, puzzle init)
{
    //             
    assert(dir == 'n' || dir == 's' || dir == 'e' || dir == 'w');
    //              
    //                              
    puzzle test = init;
    int direction[2]; //      
    switch(dir)
    {
    case 'n':
        direction[0] = -1;
        direction[1] = 0;
        break;

    case 's':
        direction[0] = 1;
        direction[1] = 0;
        break;

    case 'e':
        direction[0] = 0;
        direction[1] = 1;
        break;

    default :
        direction[0] = 0;
        direction[1] = -1;
    }

    int cy = test.location[0]+direction[0];
    int cx = test.location[1]+direction[1];

    int cyp = test.location[0]+direction[0]*2; //                                                                           
    int cxp = test.location[1]+direction[1]*2;
    if(test.puzzle[cy][cx] == ' ')
    {
        if(test.onFinal)
        {
            test.puzzle[test.location[0]][test.location[1]] = '.';
            test.onFinal = false;
        }
        else
            test.puzzle[test.location[0]][test.location[1]] = ' ';

        test.location[0] = cy;
        test.location[1] = cx;
        test.puzzle[test.location[0]][test.location[1]] = 'w';
    }
    else if(test.puzzle[cy][cx] == '.')
    {
        if(test.onFinal)
        {
            test.puzzle[test.location[0]][test.location[1]] = '.';
            test.onFinal = false;
        }
        else
            test.puzzle[test.location[0]][test.location[1]] = ' ';

        test.location[0] = cy;
        test.location[1] = cx;
        test.puzzle[test.location[0]][test.location[1]] = 'W';
        test.onFinal = true;
    }
    else if(test.puzzle[cy][cx] == 'b' && test.puzzle[cyp][cxp] == ' ')
    {
        if(test.onFinal)
        {
            test.puzzle[test.location[0]][test.location[1]] = '.';
            test.onFinal = false;
        }
        else
            test.puzzle[test.location[0]][test.location[1]] = ' ';

        test.location[0] = cy;
        test.location[1] = cx;
        test.puzzle[test.location[0]][test.location[1]] = 'w';
        test.puzzle[cyp][cxp] = 'b';
    }
    else if(test.puzzle[cy][cx] == 'b' && test.puzzle[cyp][cxp] == '.')
    {
        if(test.onFinal)
        {
            test.puzzle[test.location[0]][test.location[1]] = '.';
            test.onFinal = false;
        }
        else
            test.puzzle[test.location[0]][test.location[1]] = ' ';

        test.location[0] = cy;
        test.location[1] = cx;
        test.puzzle[test.location[0]][test.location[1]] = 'w';
        test.puzzle[cyp][cxp] = 'B';
    }
    else if(test.puzzle[cy][cx] == 'B' && test.puzzle[cyp][cxp] == '.')
    {
        if(test.onFinal)
        {
            test.puzzle[test.location[0]][test.location[1]] = '.';
            test.onFinal = false;
        }
        else
            test.puzzle[test.location[0]][test.location[1]] = ' ';

        test.location[0] = cy;
        test.location[1] = cx;
        test.puzzle[test.location[0]][test.location[1]] = 'W';
        test.onFinal = true;
        test.puzzle[cyp][cxp] = 'B';
    }
    else if(test.puzzle[cy][cx] == 'B' && test.puzzle[cyp][cxp] == ' ')
    {
        if(test.onFinal)
        {
            test.puzzle[test.location[0]][test.location[1]] = '.';
            test.onFinal = false;
        }
        else
            test.puzzle[test.location[0]][test.location[1]] = ' ';

        test.location[0] = cy;
        test.location[1] = cx;
        test.puzzle[test.location[0]][test.location[1]] = 'W';
        test.onFinal = true;
        test.puzzle[cyp][cxp] = 'b';
    }
    return test;
}

int bfs()
{
    //             
    assert(true);
    //              
    //                                                      
    puzzle n;
    puzzle s;
    puzzle e;
    puzzle w;
    puzzleVec.at(0).parent = 0;
    for(int i = 0, b = 0; i < puzzleVec.size() && b < MAX_ITERATIONS; i++, b++)
    {
        if(solution(puzzleVec.at(i)))
            return puzzleVec.at(i).parent;
        explored.push_back(puzzleVec.at(i));

        n = moveDir('n', puzzleVec.at(i));
        n.parent += 1;
        e = moveDir('e', puzzleVec.at(i));
        e.parent += 1;
        s = moveDir('s', puzzleVec.at(i));
        s.parent += 1;
        w = moveDir('w', puzzleVec.at(i));
        w.parent += 1;

        if(!cycle(n))
            puzzleVec.push_back(n);
        if(!cycle(e))
            puzzleVec.push_back(e);
        if(!cycle(s))
            puzzleVec.push_back(s);
        if(!cycle(w))
            puzzleVec.push_back(w);
    }
    return MAX_ITERATIONS;
}

int dfs(puzzle input, int current)
{
    //             
    assert(true);
    //              
    //                                                    
    if(current > best)
        return best;
    if(solution(input))
    {
        best = current;
        return current;
    }
    if(stepNorth(input))
        dfs(moveDir('n', input), current+1);
    if(stepEast(input))
        dfs(moveDir('e', input), current+1);
    if(stepSouth(input))
        dfs(moveDir('s', input), current+1);
    if(stepWest(input))
        dfs(moveDir('w', input), current+1);
    return best;
}

puzzle loadFile(char* filename)
{
    //             
    assert(true);
    //              
    //              
    int x = 0;
    int y = 0;
    puzzle cache;
    char temp;
    fillPuzzle(cache);
    ifstream myfile;
    myfile.open(filename);
    if(!myfile)
        throw std::runtime_error("FAILED TO OPEN FILE");
    while(!myfile.eof())
    {
        temp = myfile.get();
        if (temp == '\n')
        {
            y++;
            x = 0;
        }
        else
        {
            cache.puzzle[y][x] = (char)temp;
            x++;
        }
    }
    findPlayer(cache);
    return cache;
}

int main()
{
    puzzle init = loadFile("challenge.1.a.txt");
    puzzleVec.push_back(init);
    cout << "It takes " << bfs() << " step(s)" << endl;
    cout << "It takes " << dfs(init, 0) << " step(s)" << endl;
    return 0;
}

