#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>;

using namespace std;

struct Node
{
    bool wall;
    bool box;
    bool dest;
};

enum Dir {N=0,E,S,W};

struct Solution
{
    vector<vector<Node>> skb;
    int x;
    int y;
    vector<Dir> path;
};

Node new_Node (bool w, bool b, bool d)
{
    assert (true);
    //                                                       
    Node n = {.wall=w, .box=b, .dest=d};
    return n;
}

Solution new_solution (vector<vector<Node>> newSKB, int newX, int newY, vector<Dir> newPath)
{
    assert (true);
    //                                                           
    Solution s = {.skb=newSKB, .x=newX, .y=newY, .path=newPath};
    return s;
}

void read_file (istream& infile, vector<vector<Node>>& out, int& x, int& y)
{
    assert (true);
    //                                                                                   
    vector<Node> help;
    string line = "";
    while (infile)
    {
        for (int i=0; i<line.length(); i++)
        {
            switch (line[i]) {
                case '*' :  help.push_back(new_Node(1,0,0));
                            break;
                case ' ' :  help.push_back(new_Node(0,0,0));
                            break;
                case '.' :  help.push_back(new_Node(0,0,1));
                            break;
                case 'b' :  help.push_back(new_Node(0,1,0));
                            break;
                case 'B' :  help.push_back(new_Node(0,1,1));
                            break;
                case 'w' :  help.push_back(new_Node(0,0,0));
                            x = i;
                            y = out.size();
                            break;
                case 'W' :  help.push_back(new_Node(0,0,1));
                            x = i;
                            y = out.size();
                            break;
                default :   break;
            }
        }
        out.push_back(help);
        help.erase(help.begin(), help.end());
        getline(infile, line);
    }
}

void print_sokuban(vector<vector<Node>> skb, int x, int y)
{
    assert(skb.size() >= y && skb[y].size() >= x);
    //                                                                                                         
    for (int i=0; i<skb.size(); i++)
    {
        for (int j=0; j<skb[i].size(); j++)
        {
            if (x==j && y==i)
                if (skb[i][j].dest)
                    cout << 'W';
                else
                    cout << 'w';
            else if (skb[i][j].wall)
                cout << '*';
            else if (skb[i][j].box)
                if (skb[i][j].dest)
                    cout << 'B';
                else
                    cout << 'b';
            else if (skb[i][j].dest)
                cout << '.';
            else
                cout << ' ';
        }
        cout << endl;
    }
}

bool is_solved (vector<vector<Node>> skb)
{
    assert (true);
    //                                                                                          
    for (int i=0; i<skb.size(); i++)
        for (int j=0; j<skb[i].size(); j++)
            if (!skb[i][j].dest && skb[i][j].box)
                return false;
    return true;
}

bool move_dir (vector<vector<Node>>& skb, int& x, int& y, Dir d)
{
    assert(skb.size() >= y && skb[y].size() >= x);
    //                                                                                  
    //                                                                                                                     
    int dX, dY;
    switch (d){
    case N : dX = 0;
             dY = -1;
             break;
    case E : dX = 1;
             dY = 0;
             break;
    case S : dX = 0;
             dY = 1;
             break;
    case W : dX = -1;
             dY = 0;
    }
    if (skb[y+dY][x+dX].wall)
        return false;
    else if (skb[y+dY][x+dX].box)
    {
        if (skb[y+dY+dY][x+dX+dX].wall || skb[y+dY+dY][x+dX+dX].box)
            return false;
        else
        {
            skb[y+dY+dY][x+dX+dX].box = 1;
            skb[y+dY][x+dX].box = 0;
            x += dX;
            y += dY;
        }
    }
    else
    {
        x += dX;
        y += dY;
    }
}

void bfs_skb (vector<vector<Node>> skb, int x, int y, vector<Dir>& path)
{
    if (is_solved(skb))
        return;
    Solution S;
    Solution Help;
    vector<Solution> Q;
    Q.push_back(new_solution(skb, x, y, {}));
    while (true)
    {
    S = Q[0];
    Help = S;
    Q.erase(Q.begin(),Q.begin()+1);
    for (int d=N; d<=W; d++)
        if (move_dir(S.skb, S.x, S.y, (Dir) d))
        {
            S.path.push_back((Dir) d);
            if (is_solved(S.skb))
            {
                path = S.path;
                return;
            }
            Q.push_back(S);

            S = Help;
        }

    }
}

int dfs_skb (vector<vector<Node>> skb, int x, int y, int& maxlength, vector<Dir>& path)
{
    vector<Dir> backup;
    if (is_solved(skb))
    {
        maxlength = path.size();
        return 0;
    }
    if (path.size() >= maxlength)
        return -1;
    int n=-1, m, oldx=x, oldy=y;
    vector<vector<Node>> help = skb;
    for (int d=N; d<=W; d++)
    {
        if (move_dir(skb, x, y, (Dir) d))
        {
            path.push_back((Dir) d);
            m = dfs_skb (skb, x, y, maxlength, path);
            if (m > n)
                n = m;
            if (n >= 0)
                backup = path;
            else
                path.pop_back();
            x = oldx;
            y = oldy;
        }
    }
    if (n == -1)
        return -1;
    else
        return (n + 1);
}

int main()
{
    ifstream in;
    in.open("challenge.25.txt");
    vector<vector<Node>> skb;
    vector<Dir> p,q;
    int xpos, ypos;
    read_file(in, skb, xpos, ypos);
    bfs_skb(skb, xpos, ypos, p);
    for (int i=0; i<p.size(); i++)
        cout << p[i];
    int n = p.size();
    cout << endl;
    dfs_skb(skb, xpos, ypos, n, q);
    for (int i=0; i<p.size(); i++)
        cout << p[i];
    print_sokuban(skb, xpos, ypos);
    return 0;
}

