#include <iostream>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<cassert>
#include <iostream>
//                                              

using namespace std;

const char wall_cell = '*';
const char empty_cell = ' ';
const char empty_destination_cell  = '.';
const char worker_empty = 'w';
const char worker_dest = 'W';
const char box_empty = 'b';
const char box_destination = 'B';

typedef vector<vector<char> > field;

struct Puzzle {
    field f;
    int x, y;
};

field f =
{{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}
,{'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'}
,{'*', 'B', ' ', ' ', ' ', ' ', ' ', ' ', 'w', '*'}
,{'*', ' ', ' ', '*', '*', '*', '*', ' ', ' ', '*'}
,{'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'}
,{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}};

ostream& operator<< (ostream& out, const field Field)
{
    for (int i = 0; i<Field.size(); i++)
    {
        for (int j = 0; j<Field[i].size(); j++)
        {
            out << Field[i][j];
        }
        out << endl;
    }
    return out;
}

vector<field> queue;
vector<field> visited;

bool puzzle_ready(field Field) //      
{
      assert (true);
    //                                       
    for (int i = 0; i<Field.size(); i++)
    {
        for (int j = 0; j<Field[i].size(); j++)
        {
            if (Field [i][j] == 'b')
                return false;
        }
    }
    return true;
}

bool   can_go_north(field Field)
{
      assert (true);
    //                                  
    for (int i = 0; i<Field.size(); i++)
    {
        for (int j = 0; j<Field[i].size(); j++)
        {
            if (Field[i][j] == 'w')
            {
                if (Field[i-1][j] != '*')
                {
                    return true;
                }
            }
        }
    }
}

bool can_go_south (field Field)
{
      assert (true);
    //                                  
    for (int i = 0; i<Field.size(); i++)
    {
        for (int j = 0; j<Field[i].size(); j++)
        {
            if (Field[i][j] == 'w')
            {
                if (Field[i+1][j] != '*')
                {
                    return true;
                }
            }
        }
    }
}

bool can_go_west (field Field)
{
      assert (true);
    //                                 
    for (int i = 0; i<Field.size(); i++)
    {
        for (int j = 0; j<Field[i].size(); j++)
        {
            if (Field[i][j] == 'w')
            {
                if (Field[i][j-1] != '*')
                {
                    return true;
                }
            }
        }
    }
}

bool can_go_east (field Field)
{
    assert (true);
    //                                 
    for (int i = 0; i<Field.size(); i++)
    {
        for (int j = 0; j<Field[i].size(); j++)
        {
            if (Field[i][j] == 'w')
            {
                if (Field[i][j+1] != '*')
                {
                    return true;
                }
            }
        }
    }
}

void go_north (Puzzle Field)
{
    assert (true);
    //                    
    if (Field.f[Field.x-1][Field.y] == 'b' || Field.f[Field.x-1][Field.y] == 'B' && Field.f[Field.x-2][Field.y] != '*')
    {
        if (Field.f[Field.x-2][Field.y] == '.')
        {
            Field.f[Field.x-2][Field.y] = 'B';
        }
        else
        {
        Field.f[Field.x][Field.y] = Field.f[Field.x-2][Field.y];
        Field.f[Field.x-1][Field.y]= 'w';
        Field.f[Field.x-2][Field.y]= Field.f[Field.x-1][Field.y];
        }

    }
    else
    {
        if (Field.f[Field.x-1][Field.y] == '.')
        {
        Field.f[Field.x][Field.y] = ' ';
        Field.f[Field.x-1][Field.y]= 'W';
        }
        Field.f[Field.x][Field.y] = Field.f[Field.x-1][Field.y];
        Field.f[Field.x-1][Field.y]= 'w';
    }

}

void go_east (Puzzle Field)
{
    assert (true);
    //                   
    if (Field.f[Field.x][Field.y+1] == 'b' || Field.f[Field.x][Field.y+1] == 'B' && Field.f[Field.x][Field.y+2] != '*')
    {
         if (Field.f[Field.x][Field.y+2] == '.')
        {
            Field.f[Field.x][Field.y+2] = 'B';
        }
        else
        {
        Field.f[Field.x][Field.y] = Field.f[Field.x][Field.y+2];
        Field.f[Field.x][Field.y+1]= 'w';
        Field.f[Field.x][Field.y+2]= Field.f[Field.x][Field.y+1];
        }
    }
    else
    {
        if (Field.f[Field.x][Field.y+1] == '.')
        {
        Field.f[Field.x][Field.y] = ' ';
        Field.f[Field.x][Field.y+1]= 'W';
        }
        Field.f[Field.x][Field.y] = Field.f[Field.x][Field.y+1];
        Field.f[Field.x][Field.y+1]= 'w';
    }
}

void go_south (Puzzle Field)
{
    assert (true);
    //                    
    if (Field.f[Field.x+1][Field.y] == 'b' || Field.f[Field.x+1][Field.y] == 'B' && Field.f[Field.x+2][Field.y] != '*')
    {
         if (Field.f[Field.x+2][Field.y] == '.')
        {
            Field.f[Field.x+2][Field.y] = 'B';
        }
        else
        {
        Field.f[Field.x][Field.y] = Field.f[Field.x+2][Field.y];
        Field.f[Field.x+1][Field.y]= 'w';
        Field.f[Field.x+2][Field.y]= Field.f[Field.x+1][Field.y];
        }
    }
    else
    {
        if (Field.f[Field.x+1][Field.y] == '.')
        {
        Field.f[Field.x][Field.y] = ' ';
        Field.f[Field.x+1][Field.y]= 'W';
        }
        Field.f[Field.x][Field.y] = Field.f[Field.x+1][Field.y];
        Field.f[Field.x+1][Field.y]= 'w';
    }
}

void go_west (Puzzle Field)
{
    assert (true);
    //                   
    if (Field.f[Field.x][Field.y-1] == 'b' || Field.f[Field.x][Field.y-1] == 'B' && Field.f[Field.x][Field.y-2] != '*')
    {
         if (Field.f[Field.x][Field.y-2] == '.')
        {
            Field.f[Field.x][Field.y-2] = 'B';
        }
        else
        {
        Field.f[Field.x][Field.y] = Field.f[Field.x][Field.y-2];
        Field.f[Field.x][Field.y-1]= 'w';
        Field.f[Field.x][Field.y-2]= Field.f[Field.x][Field.y-1];
        }
    }
    else
    {
        if (Field.f[Field.x][Field.y-1] == '.')
        {
        Field.f[Field.x][Field.y] = ' ';
        Field.f[Field.x][Field.y-1]= 'W';
        }
        Field.f[Field.x][Field.y] = Field.f[Field.x][Field.y-1];
        Field.f[Field.x][Field.y-1]= 'w';
    }
}

void breadth_first(Puzzle Field, field f)
{
    assert(true);

    //                                         
    while (!puzzle_ready(f))
    {
        for (int i = 0; i<f.size(); i++)
        {
            for (int j = 0; j<f[i].size(); j++)
            {
                if (can_go_north(f))
                {
                    go_north(Field);
                }
                else if (can_go_east(f))
                {
                    go_east(Field);
                }
                else if (can_go_south(f))
                {
                   go_south(Field);
                }
                else if (can_go_west(f))
                {
                    go_west(Field);
                }
            }
        }
    }
    cout << f;
}

int main()
{
    Puzzle p = {f, 9, 3};
    breadth_first(p, f);
    return 0;
}

