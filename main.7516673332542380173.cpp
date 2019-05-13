#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

/*
                         
                    
*/

const int MAX_HEIGHT = 10;
const int MAX_WIDTH = 12;
char game [MAX_HEIGHT][MAX_WIDTH];
int number = 0;
int maxDepth = 35;
struct loc{
int height;
int width;
};
struct Candidate{
loc location;
int vectornr;
int parent;
int onDestination;
char gameMap [MAX_HEIGHT][MAX_WIDTH];
};
struct deptCandidate {
loc location;
int onDestination;
char gameMap [MAX_HEIGHT][MAX_WIDTH];
};

bool mapEqual(char game [MAX_HEIGHT][MAX_WIDTH], char nextgame [MAX_HEIGHT][MAX_WIDTH]);

int size(vector<Candidate>& c)
{
    return static_cast<int> (c.size());
}

int size(vector<deptCandidate>& c)
{
    return static_cast<int> (c.size());
}

bool read (ifstream& infile, string nr)
{
//              
assert(!infile.is_open());
/*
               
                                                  
*/
    string challenge = "challenge.";
    string txt = ".txt";
    string all = challenge + nr + txt;
    infile.open(all);
    if (!infile.is_open())
    {
        return 0;
    }
    cout << "challenge " << nr << " is opened." << endl;
    char c;
    int i = 0;
    int j = 0;
    while (infile)
    {
       c = infile.get();
        if (c == '\n')
        {
            j=0;
            i++;
            c = infile.get();
        }
        game [i][j] = c;
        j++;
    }
     infile.close();
     return 1;
}

bool breathin (Candidate candidate, vector<Candidate>& c)
{
    //              
    assert(true);
    /*
                   
                                   
    */
    for(int i = 1; i < size(c); i++)
    {
        if(mapEqual(candidate.gameMap, c[i].gameMap))
        {
            return true;
        }
    }
    return false;
}

void show(Candidate c)
{
    //               
    assert(true);
    /*
                   
                                                                       
    */
    for(int j=0; j<MAX_HEIGHT; j++)
    {
        for(int i=0; i<MAX_WIDTH; i++)
        {
            cout << c.gameMap [j][i];
        }
        cout << endl;
    }

}

void showdept(deptCandidate c)
{
    //               
    assert(true);
    /*
                   
                                                                       
    */
    for(int j=0; j<MAX_HEIGHT; j++)
    {
        for(int i=0; i<MAX_WIDTH; i++)
        {
            cout << c.gameMap [j][i];
        }
        cout << endl;
    }

}

bool puzzle_ready(Candidate c, int destination)
{
    //               
    assert(destination > 0);
    /*
                   
                                                                              
    */
    if(c.onDestination == destination)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool can_go_north (Candidate c)
{
    //              
    assert(true);
    /*
                   
                                                                                          
    */
    if(c.gameMap[c.location.height-1][c.location.width] == '*')
    {
        return false;
    }
    else if(c.gameMap[c.location.height-1][c.location.width] == 'b' || c.gameMap[c.location.height-1][c.location.width] == 'B')
    {
        if(c.gameMap[c.location.height-2][c.location.width] == '*' || c.gameMap[c.location.height-2][c.location.width] == 'b' || c.gameMap[c.location.height-2][c.location.width] == 'B')
        {
            return false;
        }
    }
    return true;
}

bool can_go_south (Candidate c)
{
    //              
    assert(true);
    /*
                   
                                                                                          
    */
    if(c.gameMap[c.location.height+1][c.location.width] == '*')
    {
        return false;
    }
    else if(c.gameMap[c.location.height+1][c.location.width] == 'b' || c.gameMap[c.location.height+1][c.location.width] == 'B')
    {
        if(c.gameMap[c.location.height+2][c.location.width] == '*' || c.gameMap[c.location.height+2][c.location.width] == 'b' || c.gameMap[c.location.height+2][c.location.width] == 'B')
        {
            return false;
        }
    }
    return true;
}

bool can_go_west (Candidate c)
{
    //              
    assert(true);
    /*
                   
                                                                                         
    */
    if(c.gameMap[c.location.height][c.location.width-1] == '*')
    {
        return false;
    }
    else if(c.gameMap[c.location.height][c.location.width-1] == 'b' || c.gameMap[c.location.height][c.location.width-1] == 'B')
    {
        if(c.gameMap[c.location.height][c.location.width-2] == '*' || c.gameMap[c.location.height][c.location.width-2] == 'b' || c.gameMap[c.location.height][c.location.width-2] == 'B')
        {
            return false;
        }
    }
    return true;
}

bool can_go_east (Candidate c)
{
    //              
    assert(true);
    /*
                   
                                                                                         
    */
    if(c.gameMap[c.location.height][c.location.width+1] == '*')
    {
        return false;
    }
    else if(c.gameMap[c.location.height][c.location.width+1] == 'b' || c.gameMap[c.location.height][c.location.width+1] == 'B')
    {
        if(c.gameMap[c.location.height][c.location.width+2] == '*' || c.gameMap[c.location.height][c.location.width+2] == 'b' || c.gameMap[c.location.height][c.location.width+2] == 'B')
        {
            return false;
        }
    }
    return true;
}

void triesBreathFirst (vector<Candidate>& c, int i, int h, int w)
{
    //              
    assert(true);
    /*
                   
                                                                                           
    */
    int temph = c[i].location.height;
    int tempw = c[i].location.width;
    Candidate child = c[i];
    child.vectornr = size(c);
    child.parent = c[i].vectornr;
    child.location.height += h;
    child.location.width += w;
    if (c[i].gameMap[temph+h][tempw+w] == 'b') //     
    {
        if(c[i].gameMap[temph+h+h][tempw+w+w] == '.')
        {
            child.gameMap[temph+h+h][tempw+w+w] = 'B';
            child.gameMap[temph+h][tempw+w] = ' ';

            child.onDestination++;
        }
        if(c[i].gameMap[temph+h+h][tempw+w+w] == ' ')
        {
            child.gameMap[temph+h+h][tempw+w+w] = 'b';
            child.gameMap[temph+h][tempw+w] = ' ';
        }
    }
    else if (c[i].gameMap[temph+h][tempw+w] == 'B') //         
    {
        if(c[i].gameMap[temph+h+h][tempw+w+w] == '.')
        {
            child.gameMap[temph+h+h][tempw+w+w] = 'B';
            child.gameMap[temph+h][tempw+w] = '.';
        }
        else if (c[i].gameMap[temph+h+h][tempw+w+w] == ' ')
        {
            child.gameMap[temph+h+h][tempw+w+w] = 'b';
            child.gameMap[temph+h][tempw+w] = '.';
            child.onDestination--;
        }
    }
    if (child.gameMap[temph][tempw] == 'w') //    
    {
        if (child.gameMap[temph+h][tempw+w] == '.')
        {
           child.gameMap[temph+h][tempw+w] = 'W';
           child.gameMap[temph][tempw] = ' ';
        }
        else if (child.gameMap[temph+h][tempw+w] == ' ')
        {
            child.gameMap[temph+h][tempw+w] = 'w';
            child.gameMap[temph][tempw] = ' ';
        }
    }
    else if (child.gameMap[temph][tempw] == 'W')
    {
        if (child.gameMap[temph+h][tempw+w] == '.')
        {
           child.gameMap[temph+h][tempw+w] = 'W';
           child.gameMap[temph][tempw] = '.';
        }
        else if (child.gameMap[temph+h][tempw+w] == ' ')
        {
            child.gameMap[temph+h][tempw+w] = 'w';
            child.gameMap[temph][tempw] = '.';
        }
    }
    if(!breathin(child, c))
    {
        c.push_back(child);
    }
}

void show_path (vector<Candidate>& c, int i)
{
    //              
    assert(true);
    /*
                   
                                                    
    */
    if(c[i].parent == -1)
    {
        show(c[i]);
    }
    else
    {
        number++;
        show_path(c, c[i].parent);
        show(c[i]);
    }
}

void solveBreathFirst ()
{
    //              
    assert(true);
    /*
                   
                                 
    */
    vector <Candidate> c;
    int destination = 0;
    loc location;
    Candidate candidate;
    int blockOnDes = 0;
    for(int i=0; i<MAX_HEIGHT; i++)
    {
        for(int j=0; j<MAX_WIDTH; j++)
        {
            if(game [i][j] == 'B' || game [i][j] == 'W' || game [i][j] == '.')
            {
                destination++;
            }
            if(game [i][j] == 'B')
            {
                blockOnDes++;
            }
            if(game [i][j] == 'w' || game [i][j] == 'W')
            {
                location = {i,j};
                candidate.location = location;
                candidate.vectornr = 0;
                candidate.parent = -1;
                candidate.onDestination = 0;

                for(int k=0; k<MAX_HEIGHT; k++)
                {
                    for(int l=0; l<MAX_WIDTH; l++)
                    {
                        candidate.gameMap[k][l] = game[k][l];
                    }
                }
            }
        }
    }
    candidate.onDestination = blockOnDes;
    c.push_back(candidate);

    int i = 0;
    while (i < size(c) && !puzzle_ready (c[i], destination))
    {
        if (can_go_north (c[i])) {triesBreathFirst (c, i, -1, 0);}
        if (can_go_south (c[i])) {triesBreathFirst (c, i, 1, 0);}
        if (can_go_west (c[i])) {triesBreathFirst (c, i, 0, -1);}
        if (can_go_east (c[i])) {triesBreathFirst (c, i, 0, 1);}
        i++;
    }
    if (i < size (c))
    {
        show_path(c,i);
    }
    cout << number;
}

bool mapEqual(char game [MAX_HEIGHT][MAX_WIDTH], char nextgame [MAX_HEIGHT][MAX_WIDTH])
{
    //              
    assert(true);
    /*
                   
                                 
    */
    for(int i = 0; i < MAX_HEIGHT; i++)
    {
        for(int j = 0; j < MAX_WIDTH; j++)
        {
            if(!(game[i][j] == nextgame[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}

bool in (deptCandidate candidate, vector<deptCandidate>& c)
{
    //              
    assert(true);
    /*
                   
                                   
    */
    for(int i = 1; i < size(c); i++)
    {
        if(mapEqual(candidate.gameMap, c[i].gameMap))
        {
            return true;
        }
    }
    return false;
}

void solveDepthFirst (vector<deptCandidate>& c, vector<deptCandidate>& shortest, int& destination);

void triesDeptFirst (vector<deptCandidate>& c, int i, int h, int w, vector<deptCandidate>& shortest, int destination)
{
    //              
    assert(true);
    /*
                   
                                             
    */
    int temph = c[i].location.height;
    int tempw = c[i].location.width;
    deptCandidate child = c[i];
    child.location.height += h;
    child.location.width += w;
    if (c[i].gameMap[temph+h][tempw+w] == 'b') //     
    {
        if(c[i].gameMap[temph+h+h][tempw+w+w] == '.')
        {
            child.gameMap[temph+h+h][tempw+w+w] = 'B';
            child.gameMap[temph+h][tempw+w] = ' ';

            child.onDestination++;
        }
        if(c[i].gameMap[temph+h+h][tempw+w+w] == ' ')
        {
            child.gameMap[temph+h+h][tempw+w+w] = 'b';
            child.gameMap[temph+h][tempw+w] = ' ';
        }
    }
    else if (c[i].gameMap[temph+h][tempw+w] == 'B') //         
    {
        if(c[i].gameMap[temph+h+h][tempw+w+w] == '.')
        {
            child.gameMap[temph+h+h][tempw+w+w] = 'B';
            child.gameMap[temph+h][tempw+w] = '.';
        }
        else if (c[i].gameMap[temph+h+h][tempw+w+w] == ' ')
        {
            child.gameMap[temph+h+h][tempw+w+w] = 'b';
            child.gameMap[temph+h][tempw+w] = '.';
            child.onDestination--;
        }
    }
    if (child.gameMap[temph][tempw] == 'w') //    
    {
        if (child.gameMap[temph+h][tempw+w] == '.')
        {
           child.gameMap[temph+h][tempw+w] = 'W';
           child.gameMap[temph][tempw] = ' ';
        }
        else if (child.gameMap[temph+h][tempw+w] == ' ')
        {
            child.gameMap[temph+h][tempw+w] = 'w';
            child.gameMap[temph][tempw] = ' ';
        }
    }
    else if (child.gameMap[temph][tempw] == 'W')
    {
        if (child.gameMap[temph+h][tempw+w] == '.')
        {
           child.gameMap[temph+h][tempw+w] = 'W';
           child.gameMap[temph][tempw] = '.';
        }
        else if (child.gameMap[temph+h][tempw+w] == ' ')
        {
            child.gameMap[temph+h][tempw+w] = 'w';
            child.gameMap[temph][tempw] = '.';
        }
    }
    if(!in(child, c))
    {
    c.push_back(child);
    solveDepthFirst(c, shortest, destination);
    c.pop_back();
    }
}

void show_pathdept (vector<deptCandidate>& c)
{
    //              
    assert(true);
    /*
                   
                                                    
    */
    int temp = -1;
    for(int i = 0; i < size(c); i++)
    {
        showdept(c[i]);
        temp++;
    }
    cout << temp;
}

bool puzzle_readydept(deptCandidate c, int destination)
{
    //               
    assert(destination > 0);
    /*
                   
                                                                              
    */
    if(c.onDestination == destination)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool can_go_northdept (deptCandidate c)
{
    //              
    assert(true);
    /*
                   
                                                                                          
    */
    if(c.gameMap[c.location.height-1][c.location.width] == '*')
    {
        return false;
    }
    else if(c.gameMap[c.location.height-1][c.location.width] == 'b' || c.gameMap[c.location.height-1][c.location.width] == 'B')
    {
        if(c.gameMap[c.location.height-2][c.location.width] == '*' || c.gameMap[c.location.height-2][c.location.width] == 'b' || c.gameMap[c.location.height-2][c.location.width] == 'B')
        {
            return false;
        }
    }
    return true;
}

bool can_go_southdept (deptCandidate c)
{
    //              
    assert(true);
    /*
                   
                                                                                          
    */
    if(c.gameMap[c.location.height+1][c.location.width] == '*')
    {
        return false;
    }
    else if(c.gameMap[c.location.height+1][c.location.width] == 'b' || c.gameMap[c.location.height+1][c.location.width] == 'B')
    {
        if(c.gameMap[c.location.height+2][c.location.width] == '*' || c.gameMap[c.location.height+2][c.location.width] == 'b' || c.gameMap[c.location.height+2][c.location.width] == 'B')
        {
            return false;
        }
    }
    return true;
}

bool can_go_westdept (deptCandidate c)
{
    //              
    assert(true);
    /*
                   
                                                                                         
    */
    if(c.gameMap[c.location.height][c.location.width-1] == '*')
    {
        return false;
    }
    else if(c.gameMap[c.location.height][c.location.width-1] == 'b' || c.gameMap[c.location.height][c.location.width-1] == 'B')
    {
        if(c.gameMap[c.location.height][c.location.width-2] == '*' || c.gameMap[c.location.height][c.location.width-2] == 'b' || c.gameMap[c.location.height][c.location.width-2] == 'B')
        {
            return false;
        }
    }
    return true;
}

bool can_go_eastdept (deptCandidate c)
{
    //              
    assert(true);
    /*
                   
                                                                                         
    */
    if(c.gameMap[c.location.height][c.location.width+1] == '*')
    {
        return false;
    }
    else if(c.gameMap[c.location.height][c.location.width+1] == 'b' || c.gameMap[c.location.height][c.location.width+1] == 'B')
    {
        if(c.gameMap[c.location.height][c.location.width+2] == '*' || c.gameMap[c.location.height][c.location.width+2] == 'b' || c.gameMap[c.location.height][c.location.width+2] == 'B')
        {
            return false;
        }
    }
    return true;
}

void solveDepthFirst (vector<deptCandidate>& c, vector<deptCandidate>& shortest, int& destination)
{
    //              
    assert(true);
    /*
                   
                                
    */
    const int CURRENT = size(c);
    const int BEST = size(shortest);
    if(BEST > 0 && CURRENT >= BEST) { return ; }
    else if(CURRENT > maxDepth+1) { return; }
    else if(puzzle_readydept(c[CURRENT-1], destination)) { shortest = c; return; }
    if (can_go_northdept (c[CURRENT-1])) {triesDeptFirst (c, CURRENT-1, -1, 0, shortest, destination);}
    if (can_go_southdept (c[CURRENT-1])) {triesDeptFirst (c, CURRENT-1, 1, 0, shortest, destination);}
    if (can_go_westdept (c[CURRENT-1])) {triesDeptFirst (c, CURRENT-1, 0, -1, shortest, destination);}
    if (can_go_eastdept (c[CURRENT-1])) {triesDeptFirst (c, CURRENT-1, 0, 1, shortest, destination);}
}

void DepthFirst ()
{
    //              
    assert(true);
    /*
                   
                                           
    */
    vector<deptCandidate> attempt;
    vector<deptCandidate> shortest;
    vector <deptCandidate> c;
    int destination = 0;
    loc location;
    deptCandidate candidate;
    int blockOnDes = 0;
    for(int i=0; i<MAX_HEIGHT; i++)
    {
        for(int j=0; j<MAX_WIDTH; j++)
        {
            if(game [i][j] == 'B' || game [i][j] == 'W' || game [i][j] == '.')
            {
                destination++;
            }
            if(game [i][j] == 'B')
            {
                blockOnDes++;
            }
            if(game [i][j] == 'w' || game [i][j] == 'W')
            {
                location = {i,j};
                candidate.location = location;
                candidate.onDestination = 0;

                for(int k=0; k<MAX_HEIGHT; k++)
                {
                    for(int l=0; l<MAX_WIDTH; l++)
                    {
                        candidate.gameMap[k][l] = game[k][l];
                    }
                }
            }
        }
    }
    candidate.onDestination = blockOnDes;
    c.push_back(candidate);
    solveDepthFirst(c, shortest, destination);
    show_pathdept(shortest);
}

int main()
{
    //                 
    string nr = "31";
    ifstream infile;
    if (read(infile, nr));
    //            
    solveBreathFirst();
    DepthFirst();
}

