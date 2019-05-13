#include <iostream>
#include <vector>
#include <assert.h>
//                             
//                        

using namespace std;

const int WIDTH =10;
const int HEIGHT =6;
typedef int Cell;
const Cell EMPTY = WIDTH * HEIGHT;

typedef vector< vector<char> > field;

field f = {{'*','*','*','*','*','*','*','*','*','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*',' ','.','b','w',' ',' ',' ',' ','*'},
{'*',' ',' ','*','*','*','*',' ',' ','*'},
{'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
{'*','*','*','*','*','*','*','*','*','*'}};

struct worker_pos
{
    int col;
    int row;
};

struct Puzzle {
    field veld;
    worker_pos pos;
};

struct Candidate
{
    Puzzle candidate;
    int parent_candidate;
};

void show_matrix(field f)
{
    //             
    assert(true);
    //              
    //                              
    for (int i = 0; i < f.size(); i++) {
        for (int k = 0; k < f[i].size(); k++) {
            cout << f[i][k];
        }
        cout << endl;
    }
}
bool can_go_west(Puzzle p)
{
    //             
    assert(true);
    //              
    //                                               

    if(p.veld[p.pos.col][p.pos.row-1]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row-1]=='b'&&p.veld[p.pos.col][p.pos.row-2]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row-1]=='B'&&p.veld[p.pos.col][p.pos.row-2]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row-1]=='.')
    {
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row-1]=='b'&&p.veld[p.pos.col][p.pos.row-2]=='.'){
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row-1]=='B'&&p.veld[p.pos.col][p.pos.row-2]=='.')
    {
        return true;
    }
    else
    {
        cout << "false" << endl;
        return false;
    }
}
worker_pos west(Puzzle& p)
{
    //             
    assert(true);
    //              
    //                                                                             
    char y= p.veld[p.pos.col][p.pos.row-2];
    char z= p.veld[p.pos.col][p.pos.row-1];
    if(z== ' ')
    {
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row-1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "1" << endl;
    }
    else if(z == 'b' && y == '.')
    {
        p.veld[p.pos.col][p.pos.row-2] = 'B';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row-1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "2" << endl;
    }
    else if(z == 'B' && y == '.')
    {
        p.veld[p.pos.col][p.pos.row-2]='B';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row-1;
        p.veld[p.pos.col][p.pos.row] = 'W';
        cout << "3" << endl;
    }
    else if(z == 'b' && y == ' ')
    {
        p.veld[p.pos.col][p.pos.row-2]='b';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row-1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "4" << endl;
    }
    else if(z == 'B' && y == ' ')
    {
        p.veld[p.pos.col][p.pos.row-2]='b';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row-1;
        p.veld[p.pos.col][p.pos.row] = 'W';
        cout << "5" << endl;
    }
}

bool can_go_east(Puzzle p)
{
    //             
    assert(true);
    //              
    //                                               

    if(p.veld[p.pos.col][p.pos.row+1]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row+1]=='b'&&p.veld[p.pos.col][p.pos.row+2]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row+1]=='B'&&p.veld[p.pos.col][p.pos.row+2]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row+1]=='.')
    {
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row+1]=='b'&&p.veld[p.pos.col][p.pos.row+2]=='.'){
        return true;
    }
    else if(p.veld[p.pos.col][p.pos.row+1]=='B'&&p.veld[p.pos.col][p.pos.row+2]=='.')
    {
        return true;
    }
    else
    {
        cout << "false" << endl;
        return false;
    }
}

worker_pos east(Puzzle& p)
{
    //             
    assert(true);
    //              
    //                                                                             
    char y= p.veld[p.pos.col][p.pos.row+2];
    char z= p.veld[p.pos.col][p.pos.row+1];
    if(z== ' ')
    {
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row+1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "1" << endl;
    }
    else if(z == 'b' && y == '.')
    {
        p.veld[p.pos.col][p.pos.row+2] = 'B';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row+1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "2" << endl;
    }
    else if(z == 'B' && y == '.')
    {
        p.veld[p.pos.col][p.pos.row+2]='B';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row+1;
        p.veld[p.pos.col][p.pos.row] = 'W';
        cout << "3" << endl;
    }
    else if(z == 'b' && y == ' ')
    {
        p.veld[p.pos.col][p.pos.row+2]='b';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row+1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "4" << endl;
    }
    else if(z == 'B' && y == ' ')
    {
        p.veld[p.pos.col][p.pos.row+2]='b';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.row = p.pos.row+1;
        p.veld[p.pos.col][p.pos.row] = 'W';
        cout << "5" << endl;
    }
}

bool can_go_north(Puzzle p)
{
    //             
    assert(true);
    //              
    //                                                

    if(p.veld[p.pos.col-1][p.pos.row]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col-1][p.pos.row]=='b'&&p.veld[p.pos.col-2][p.pos.row]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col-1][p.pos.row]=='B'&&p.veld[p.pos.col-2][p.pos.row]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col-1][p.pos.row]=='.')
    {
        return true;
    }
    else if(p.veld[p.pos.col-1][p.pos.row]=='b'&&p.veld[p.pos.col-2][p.pos.row]=='.'){
        return true;
    }
    else if(p.veld[p.pos.col-1][p.pos.row]=='B'&&p.veld[p.pos.col-2][p.pos.row]=='.')
    {
        return true;
    }
    else
    {
        cout << "false" << endl;
        return false;
    }
}

worker_pos north(Puzzle& p)
{
    //             
    assert(true);
    //              
    //                                                                              
    char y= p.veld[p.pos.col-2][p.pos.row];
    char z= p.veld[p.pos.col-1][p.pos.row];
    if(z== ' ')
    {
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col-1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "1" << endl;
    }
    else if(z == 'b' && y == '.')
    {
        p.veld[p.pos.col-2][p.pos.row] = 'B';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col-1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "2" << endl;
    }
    else if(z == 'B' && y == '.')
    {
        p.veld[p.pos.col-2][p.pos.row]='B';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col-1;
        p.veld[p.pos.col][p.pos.row] = 'W';
        cout << "3" << endl;
    }
    else if(z == 'b' && y == ' ')
    {
        p.veld[p.pos.col-2][p.pos.row]='b';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col-1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "4" << endl;
    }
    else if(z == 'B' && y == ' ')
    {
        p.veld[p.pos.col-2][p.pos.row]='b';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col-1;
        p.veld[p.pos.col][p.pos.row] = 'W';
        cout << "5" << endl;
    }
}
bool can_go_south(Puzzle p)
{
    //             
    assert(true);
    //              
    //                                                

    if(p.veld[p.pos.col+1][p.pos.row]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col+1][p.pos.row]=='b'&&p.veld[p.pos.col+2][p.pos.row]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col+1][p.pos.row]=='B'&&p.veld[p.pos.col+2][p.pos.row]==' ')
    {
        return true;
    }
    else if(p.veld[p.pos.col+1][p.pos.row]=='.')
    {
        return true;
    }
    else if(p.veld[p.pos.col+1][p.pos.row]=='b'&&p.veld[p.pos.col+2][p.pos.row]=='.'){
        return true;
    }
    else if(p.veld[p.pos.col+1][p.pos.row]=='B'&&p.veld[p.pos.col+2][p.pos.row]=='.')
    {
        return true;
    }
    else
    {
        cout << "false" << endl;
        return false;
    }
}

worker_pos south(Puzzle& p)
{
    //             
    assert(true);
    //              
    //                                                                              
    char y= p.veld[p.pos.col+2][p.pos.row];
    char z= p.veld[p.pos.col+1][p.pos.row];
    if(z== ' ')
    {
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col+1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "1" << endl;
    }
    else if(z == 'b' && y == '.')
    {
        p.veld[p.pos.col+2][p.pos.row] = 'B';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col+1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "2" << endl;
    }
    else if(z == 'B' && y == '.')
    {
        p.veld[p.pos.col+2][p.pos.row]='B';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col+1;
        p.veld[p.pos.col][p.pos.row] = 'W';
        cout << "3" << endl;
    }
    else if(z == 'b' && y == ' ')
    {
        p.veld[p.pos.col+2][p.pos.row]='b';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col+1;
        p.veld[p.pos.col][p.pos.row] = 'w';
        cout << "4" << endl;
    }
    else if(z == 'B' && y == ' ')
    {
        p.veld[p.pos.col+2][p.pos.row]='b';
        if(p.veld[p.pos.col][p.pos.row]=='W')
        {
            p.veld[p.pos.col][p.pos.row]='.';
        }else
        {
            p.veld[p.pos.col][p.pos.row]=' ';
        }
        p.pos.col = p.pos.col+1;
        p.veld[p.pos.col][p.pos.row] = 'W';
        cout << "5" << endl;
    }
}

int main()
{
    worker_pos position = {2, 4};
    Puzzle p = {f, position};
    show_matrix(p.veld);
}

