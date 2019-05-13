#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
using namespace std;

//                     

vector<vector<char>> map = {{'*','*','*','*','*','*','*','*','*','*'}
                ,{'*',' ',' ',' ',' ',' ',' ',' ',' ','*'}
                ,{'*',' ','.','b','w',' ',' ',' ',' ','*'}
                ,{'*',' ',' ','*','*','*','*',' ',' ','*'}
                ,{'*',' ',' ',' ',' ',' ',' ',' ',' ','*'}
                ,{'*','*','*','*','*','*','*','*','*','*'}};

struct Candidate
{
    vector<vector<char>> candidate;
    int parent_candidate;
};

vector<Candidate> candidatevector = {{map,-1}};

bool steppossible(int i, int j, int oi, int oj)
{
    //   
    assert(true);
    //                                                                                             
    if(map[i][j] == '*')
    {
        return false;
    }
    if(map[i][j] == 'b')
    {
        if(i>oi)
            if(map[i+1][j] == '*' || map[i+1][j] == 'B')
                return false;
        if(i<oi)
            if(map[i-1][j] == '*' || map[i-1][j] == 'B')
                return false;
        if(j>oj)
            if(map[i][j+1] == '*' || map[i][j+1] == 'B')
                return false;
        if(j<oj)
            if(map[i][j-1] == '*'|| map[i][j-1] == 'B')
                return false;
    }
    else
    {
        return true;
    }
}

bool issolution(vector<vector<char>> c)
{
    //   
    assert(true);
    //                                                                      
    for (int i = 0 ; i < 6 ;i++)
    {
        for (int j = 0 ; j < 10 ; j++)
            if(c[i][j] == 'b')
                return false;

    }
    return true;
}
vector<vector<char>> maptemp;
void goleft(int i, int j, vector<vector<char>> map2)
{//   
    assert(true);
    //                                                                                  
    if (map2[i][j-1] == 'b')
    {
        if (map2[i][j-2]=='.')
            map2[i][j-2] = 'B';
        else
            map2[i][j-2] = 'b';
        if (map2[i][j] == 'W')
        {
            map2[i][j - 1] = 'w';
            map2[i][j] = '.';
        }
        else if (map2[i][j] == 'w')
        {
            map2[i][j - 1] = 'w';
            map2[i][j] = ' ';
        }
    }
    else if (map2[i][j-1] == '.')
    {
        map2[i][j-1] = 'W';
        if (map2[i][j] == 'W')
        {
            map2[i][j] = '.';
        }
        else
            map2[i][j] = ' ';
    }
    else if (map2[i][j-1] == ' ')
    {
        map2[i][j-1] = 'w';
        if (map2[i][j] == 'W')
        {
            map2[i][j] = '.';
        }
        else
            map2[i][j] = ' ';
    }
    maptemp = map2;
}

void goright(int i, int j, vector<vector<char>> map2)
{
    //   
    assert(true);
    //                                                                                   
    if (map2[i][j+1] == 'b')
    {
        if (map2[i][j+2]=='.')
            map2[i][j+2] = 'B';
        else
            map2[i][j+2] = 'b';
        if (map2[i][j] == 'W')
        {
            map2[i][j + 1] = 'w';
            map2[i][j] = '.';
        }
        else if (map2[i][j] == 'w')
        {
            map2[i][j + 1] = 'w';
            map2[i][j] = ' ';
        }
    }
    else if (map2[i][j+1] == '.')
    {
        map2[i][j+1] = 'W';
        if (map2[i][j] == 'W')
        {
            map2[i][j] = '.';
        }
        else
            map2[i][j] = ' ';
    }
    else if (map2[i][j+1] == ' ')
    {
        map2[i][j+1] = 'w';
        if (map2[i][j] == 'W')
        {
            map2[i][j] = '.';
        }
        else
            map2[i][j] = ' ';
    }
    maptemp = map2;
}

void goup(int i, int j, vector<vector<char>> map)
{
    //   
    assert(true);
    //                                                                                
    if (map[i-1][j] == 'b')
    {
        if (map[i-2][j]=='.')
            map[i-2][j] = 'B';
        else
            map[i-2][j] = 'b';
        if (map[i][j] == 'W')
        {
            map[i-1][j] = 'w';
            map[i][j] = '.';
        }
        else if (map[i][j] == 'w')
        {
            map[i-1][j] = 'w';
            map[i][j] = ' ';
        }
    }
    else if (map[i-1][j] == '.')
    {
        map[i-1][j] = 'W';
        if (map[i][j] == 'W')
        {
            map[i][j] = '.';
        }
        else
            map[i][j] = ' ';
    }
    else if (map[i-1][j] == ' ')
    {
        map[i-1][j] = 'w';
        if (map[i][j] == 'W')
        {
            map[i][j] = '.';
        }
        else
            map[i][j] = ' ';
    }
    maptemp = map;
}

void godown(int i, int j, vector<vector<char>> map)
{
    //   
    assert(true);
    //                                                                                  
    if (map[i+1][j] == 'b')
    {
        if (map[i+2][j]=='.')
            map[i+2][j] = 'B';
        else
            map[i+2][j] = 'b';
        if (map[i][j] == 'W')
        {
            map[i+1][j] = 'w';
            map[i][j] = '.';
        }
        else if (map[i][j] == 'w')
        {
            map[i+1][j] = 'w';
            map[i][j] = ' ';
        }
    }
    else if (map[i+1][j] == '.')
    {
        map[i+1][j] = 'W';
        if (map[i][j] == 'W')
        {
            map[i][j] = '.';
        }
        else
            map[i][j] = ' ';
    }
    else if (map[i-1][j] == ' ')
    {
        map[i+1][j] = 'w';
        if (map[i][j] == 'W')
        {
            map[i][j] = '.';
        }
        else
            map[i][j] = ' ';
    }
    maptemp = map;
}
int posi;
int posj;
void searchworker(vector<vector<char>> map)
{
    //   
    assert(true);
    //                                                                                                                      
    for (int i = 0 ; i < 6 ;i++)
    {
        for (int j = 0 ; j < 10 ; j++)
            if(map[i][j] == 'w' || map[i][j] == 'W')
            {
                posi = i;
                posj = j;
            }

    }

}

bool puzzlepresent(vector<Candidate>& c, int i, vector<vector<char>> m)
{
    //   
    assert(true);
    //                                                                
    for (int i = 0; i < m.size() ; i++)
    {
        for (int j = 0 ; j < c.size() ; j++)
        {
            if (m == c[j].candidate)
                return true;
        }
    }
    return false;
}

void tries(vector<Candidate>& c, int i,int nposi, int nposj, char move)
{
    //   
    assert(true);
    //                                                                                                        
    vector<vector<char>> p = c[i].candidate;
    if (move == 'l')
        goleft(nposi,nposj,p);
    if (move == 'r')
        goright(nposi,nposj,p);
    if (move == 'u')
        goup(nposi,nposj,p);
    if (move == 'd')
        godown(nposi,nposj,p);
    Candidate newc = {maptemp,i};
    if (puzzlepresent(c,i,p));
    c.push_back(newc);

}
void breadthfirstsearch(vector<vector<char>> map)
{
    //   
    assert(true);
    //                                                                                                                   
    vector<Candidate> c = {{map,-1}};
    int i = 0;
    while (i < c.size() && !issolution(c[i].candidate))
    {
        vector<vector<char>> p = c[i].candidate;
        searchworker(p);
        if (steppossible(posi+1,posj,posi,posj))tries(c,i,posi,posj,'u');
        if (steppossible(posi-1,posj,posi,posj))tries(c,i,posi,posj,'d');
        if (steppossible(posi,posj+1,posi,posj))tries(c,i,posi,posj,'r');
        if (steppossible(posi,posj-1,posi,posj))tries(c,i,posi,posj,'l');
        i++;
    }
}

void tries2 (vector<vector<char>>& attempt, int nposi, int nposj,vector<vector<char>> shortest, int max_depth)
{
    //   
    assert(true);
    //     
    vector<vector<char>> p;
    p[0] = attempt[attempt.size()-1];
    //       
}
void depthfirstsearch(vector<vector<char>>& attempt, vector<vector<char>> shortest, int max_depth)
{
    //   
    assert(true);
    //                                   
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    vector<vector<char>> p;
    p[0] = attempt[CURRENT-1];
    if (BEST > 0 && CURRENT >= BEST) {return;}
    else if (CURRENT > max_depth+1) {return;}
    else if (issolution(p)) {shortest = attempt ; return;}
    searchworker(p);
    if (steppossible(posi+1,posj,posi,posj))tries2;
    if (steppossible(posi-1,posj,posi,posj))tries2;
    if (steppossible(posi,posj+1,posi,posj))tries2;
    if (steppossible(posi,posj-1,posi,posj))tries2;
}
int main()
{breadthfirstsearch(map);
    for(int i = 0 ; i < 6 ; i++)
    {
        for (int j = 0 ; j < 10 ; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}
