//                              
//                              
//                                                                                                                      
//                                 
/*
                   
                 
                 
                  
                    

                    

                       
                           

                   
 

                                                     
                                       
                   
              
              
                                      
                                       
                                  
                                     
                                         
                
                    
         
     
 

                                                       
                                          
                                           
                                 
         
     
 

                                                        
                                          
                                           
                               
         
     
 

            
                                       
                         
                        
                        
             
 
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
using namespace std;

typedef char cell;
const int Max_Rows = 7;
const int Max_Columns = 10;
struct pos {
    int x, y;
};

pos player;

struct Puzzle {
    pos guy;
    cell game[Max_Rows][Max_Columns];
};
struct Candidate {
    Puzzle candidate;
    int parent_candidate;
};

void cout_board (char game[Max_Rows][Max_Columns]) {
    assert(true);
    //                                                   
    for(int i = 0; i < Max_Rows; i++) {
        for(int q = 0; q < Max_Columns; q++) {
            cout << game[i][q];
        }
        cout<<endl;
    }
}

void copy_a_to_p(char copy[Max_Rows][Max_Columns], Puzzle& paste) {
    assert(true);
    //                                          
    for(int i = 0; i < Max_Rows; i++) {
        for(int q = 0; q < Max_Columns; q++) {
            paste.game[i][q] = copy[i][q];
        }
    }
};

void copy_p_to_a(Puzzle& paste, char copy[Max_Rows][Max_Columns]) {
    assert(true);
    //                                              
    for(int i = 0; i < Max_Rows; i++) {
        for(int q = 0; q < Max_Columns; q++) {
            copy[i][q] = paste.game[i][q] ;
        }
    }
};

bool can_go_dir (pos& player, int xdir, int ydir, char game[Max_Rows][Max_Columns]) {
    assert(true);
    //                                                        
    if (game[player.x +1*xdir][player.y+1*ydir] == '*')
        return false;
    if (game[player.x +1*xdir][player.y+1*ydir] == 'b')
        if (game[player.x+2*xdir][player.y+2*ydir] == '*' || game[player.x+2*xdir][player.y+2*ydir] == 'b')
            return false;
    else
        return true;
}

void step(pos& player, int xdir, int ydir, char game[Max_Rows][Max_Columns]) {
    assert(true);
    //                                                   
    if(can_go_dir(player, xdir, ydir, game))
    {
        if (game[player.x+1*xdir][player.y+1*ydir] == ' ') {
            game[player.x+1*xdir][player.y + 1*ydir] = 'w';
        }
        else if (game[player.x+1*xdir][player.y+1*ydir] == '.') {
            game[player.x+1*xdir][player.y + 1*ydir] = 'W';
        }
        else if (game[player.x+1*xdir][player.y+1*ydir] == 'b') {
            if (game[player.x+2*xdir][player.y + 2*ydir] == '.')
                game[player.x+2*xdir][player.y + 2*ydir] = 'B';
            else
                game[player.x+2*xdir][player.y + 2*ydir] = 'b';
            game[player.x+1*xdir][player.y + 1*ydir] = 'w';
        }
        if (game[player.x][player.y] == 'w')
            game[player.x][player.y] = ' ';
        else
            game[player.x][player.y] = '.';
        player.x = player.x +1*xdir;
        player.y = player.y +1*ydir;
    }
}

bool can_go_north (pos& player, char game[Max_Rows][Max_Columns]) {
    return (can_go_dir(player, -1, 0, game));
};
bool can_go_east (pos& player, char game[Max_Rows][Max_Columns]) {
    return (can_go_dir(player, 0, 1, game));
};
bool can_go_south (pos& player, char game[Max_Rows][Max_Columns]) {
    return (can_go_dir(player, 1, 0, game));
};
bool can_go_west (pos& player, char game[Max_Rows][Max_Columns]) {
    return (can_go_dir(player, 0, -1, game));
};

void step_north (pos& player, char game[Max_Rows][Max_Columns]) {
    if (can_go_north(player, game))
        step(player, -1, 0, game);
};
void step_east (pos& player, char game[Max_Rows][Max_Columns]) {
    if (can_go_east(player, game))
        step(player, 0, 1, game);
};
void step_south (pos& player, char game[Max_Rows][Max_Columns]) {
    if (can_go_south(player, game))
        step(player, 1, 0, game);
};
void step_west (pos& player, char game[Max_Rows][Max_Columns]) {
    if (can_go_west(player, game))
        step(player, 0, -1, game);
};

bool puzzle_ready (Puzzle p) {
    assert(true);
    //                               
    for(int i = 0; i < Max_Rows; i++) {
        for(int q = 0; q < Max_Columns; q++) {
            if (p.game[i][q] == 'b')
                return false;
        }
    }
    return true;
}

bool puzzle_present(vector<Candidate> c, int i, Candidate newc) {
    assert(i >= 0);
    //                                                               
    int q = 0;
    while (q < c.size()) {
        if (c[q] == newc.candidate)
            return false;
    }
    return true;

};

void tries (vector<Candidate> c, int i) {
    assert(i >= 0);
    //                                      
    Puzzle p = c[i].candidate;
    cell next[Max_Rows][Max_Columns];
    copy_p_to_a(p, next);
    step_north(player, next);
    copy_a_to_p(next,p);
    Candidate newc = {p,i};
    if (!puzzle_present(c, i, newc))
        c.push_back(newc);
};

void solve (Puzzle start) {
    assert(true);
    //                                                                                                               
    vector <Candidate> c = {{start, -1}};
    int i = 0;
    while (i < c.size() && !puzzle_ready(c[i].candidate)) {
        cell p[Max_Rows][Max_Columns];
        copy_p_to_a(c[i].candidate, p);
        if (can_go_north(player, p))
            tries(c, i);
        if (can_go_south(player, p))
            tries(c, i);
        if (can_go_west(player, p))
            tries(c, i);
        if (can_go_east(player, p))
            tries(c, i);
    }
};

int main() {
    cell game[Max_Rows][Max_Columns] =
    {
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*',' ',' ','w',' ',' ',' ',' ',' ','*'},
        {'*',' ',' ','b',' ',' ',' ',' ',' ','*'},
        {'*',' ',' ','.',' ',' ',' ',' ',' ','*'},
        {'*',' ',' ','*','*','*','*',' ',' ','*'},
        {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
        {'*','*','*','*','*','*','*','*','*','*'}
    };
    Puzzle start;
    start.guy.x = 1;
    start.guy.y = 3;
    copy_a_to_p(game, start);
    //             

    player.x = 1;
    player.y = 3;
    return 0;
}
