#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>

/* 
                        
                             
*/

using namespace std;

struct Puzzle {
    string cells;
    int width = 0;
    int height = 0;
    int w_row = 0;
    int w_col = 0;
    int moves = 0;

    char& operator () (int row, int col){
        //               
        //              
        assert(col >= 0 && col < width && row >= 0);
        assert(row >= 0 && row < height);
        //              
        //                            
        return cells[row * width + col];
    }
    bool operator == (const Puzzle& rhs) const{
        //              
        assert(true);
        //              
        //                                        
        return width == rhs.width &&
            height == rhs.height &&
            w_row == rhs.w_row &&
            w_col == rhs.w_col &&
            cells == rhs.cells;
    }
};

enum Move {
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8,
};

void print(Puzzle& p){
    //             
    assert(true);
    //              
    //                                                   
    for(int i = 0; i < p.height; i++){
        for(int j = 0; j < p.width; j++){
            cout << p(i, j);
        }
        cout << endl;
    }
    cout << endl;
}

bool move_if_legal(Puzzle& p, Move m){
    //              
    assert(true);
    //              
    //                                                                      
    int target_row = 0;
    int target_col = 0;;
    switch(m){
        case UP:    target_row = -1; break;
        case DOWN:  target_row =  1; break;
        case LEFT:  target_col = -1; break;
        case RIGHT: target_col =  1; break;
    }

    //             
    if(p.w_row + target_row < 0 || p.w_row + target_row >= p.height ||
       p.w_col + target_col < 0 || p.w_col + target_col >= p.width)
        return false;

    char& current = p(p.w_row, p.w_col);
    char& target = p(p.w_row + target_row, p.w_col + target_col);

    //                                  
    if(target == 'b' || target == 'B'){
        char& b_target = p(p.w_row + 2 * target_row, p.w_col + 2 * target_col);
        if(b_target == ' ')
            b_target = 'b';
        else if(b_target == '.')
            b_target = 'B';
        else return false;
    }

    //                     
    if(target == ' ' || target == 'b')
        target = 'w';
    else if(target == '.' || target == 'B')
        target = 'W';
    else return false;

    //                         
    if(current == 'W')
        current = '.';
    else
        current = ' ';

    p.w_row += target_row;
    p.w_col += target_col;
    p.moves++;
    return true;
}

int boxes_to_move( Puzzle& p){
    //            
    assert(true);
    //              
    //                                                   
    int completion = 0;
    for(int i = 0; i < p.height; i++){
        for(int j = 0; j < p.width; j++){
            if(p(i, j) == 'b')
                completion++;
        }
    }
    return completion;
}

Puzzle bf_solve( Puzzle& p){
    //             
    assert(true);
    //              
    //                                                                                     
    vector<Puzzle> nodes;

    Puzzle tmp = p;
    nodes.push_back(tmp);

    for(;;){
        Puzzle next = nodes.front();
        nodes.erase(nodes.begin(), nodes.begin() + 1);

        print(next);

        if(boxes_to_move(next) == 0){
            return next;
        }

        tmp = next;
        if(move_if_legal(tmp, UP) && find(nodes.begin(), nodes.end(), tmp) == nodes.end())
            nodes.push_back(tmp);
        tmp = next;
        if(move_if_legal(tmp, DOWN) && find(nodes.begin(), nodes.end(), tmp) == nodes.end())
            nodes.push_back(tmp);
        tmp = next;
        if(move_if_legal(tmp, LEFT) && find(nodes.begin(), nodes.end(), tmp) == nodes.end())
            nodes.push_back(tmp);
        tmp = next;
        if(move_if_legal(tmp, RIGHT) && find(nodes.begin(), nodes.end(), tmp) == nodes.end())
            nodes.push_back(tmp);
    }
}

void df_solve_rec( Puzzle& p, vector<Move>& moves, vector<Move>& best, int depth, int max_depth){
    if(depth >= max_depth){
        return;
    }
    if(depth >= (int)best.size() && (int)best.size())
        return;
    if(boxes_to_move(p) == 0){
        best = moves;
        return;
    }

    Puzzle tmp = p;
    if(move_if_legal(tmp, UP)){
        moves.push_back(UP);
        df_solve_rec(tmp, moves, best, depth + 1, max_depth);
        moves.pop_back();
    }
    tmp = p;
    if(move_if_legal(tmp, DOWN)){
        moves.push_back(DOWN);
        df_solve_rec(tmp, moves, best, depth + 1, max_depth);
        moves.pop_back();
    }
    tmp = p;
    if(move_if_legal(tmp, LEFT)){
        moves.push_back(LEFT);
        df_solve_rec(tmp, moves, best, depth + 1, max_depth);
        moves.pop_back();
    }
    tmp = p;
    if(move_if_legal(tmp, RIGHT)){
        moves.push_back(RIGHT);
        df_solve_rec(tmp, moves, best, depth + 1, max_depth);
        moves.pop_back();
    }
}

vector<Move> df_solve( Puzzle& p, int max_depth){
    //              
    assert(true);
    //               
    //                                                                                   
    vector<Move> result;
    vector<Move> moves;
    df_solve_rec(p, moves, result, 0, max_depth);
    return result;
}

int main()
{
    char tmp[] = {"**********\n*       w*\n*  b     *\n*  .     *\n*  ****  *\n*        *\n**********\n"};
    Puzzle p;
    for(int i = 0; tmp[i]; i++){
        if(tmp[i] == '\n'){
            p.height++;
            if(p.width == 0){
                p.width = i;
            }
        }
        else
            p.cells.push_back(tmp[i]);
        if(tmp[i] == 'w' || tmp[i] == 'W'){
            p.w_row = p.height;
            p.w_col = p.width ? i % (p.width + 1) : i;
        }
    }

    Puzzle result = bf_solve(p);
    cout << "Number of moves: " << result.moves << endl;

    vector<Move> other_result = df_solve(p, 25);
    cout << "Number of moves: " << other_result.size();

    return 0;
}

