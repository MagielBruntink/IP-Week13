//                                              

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

struct Game{ //                                                                        
	vector<string> board;
	int player_x;
	int player_y;
};

struct Candidate{ //        
    Game self;
    int parent;
};

enum Direction {North, East, South, West};

const int MAX_DEPTH = 34;

istream& operator>> (istream& in, Game& game) {
    //              
    assert (true);
/*                
                                         */
    Game input;
    string line = "";
    char temp;
    in.get(temp);
    while (in){
        if (temp == '\n') {
            input.board.push_back(line);
            line = "";
        } else {
            line = line + temp;
        }
        if (temp == 'w' || temp == 'W'){ //                          
            input.player_x = static_cast<int>(line.length())-1;
            input.player_y = static_cast<int>(input.board.size());
        }
        in.get(temp);
    }
    game = input;
    in.clear();
    return in;
}

void print_game(Game game){
    //                
    assert(true);
    //                                  
    if (!game.board.empty()){
        for (int i = 0; i < static_cast<int>(game.board.size()); i++){
            cout << game.board[i];
            cout << endl;
        }
    }
    cout << endl;
}

bool open_input_file (ifstream& infile, string infile_name) {
    //               
    assert(!infile.is_open());
    //                                                                              
    infile.open(infile_name.c_str());
    if (!infile.is_open()) return false;
    cout << "The file " << infile_name << " has been opened successfully." << endl << endl;
    return true;
}

bool read_input (Game& game, string filename){
    //               
    assert(game.board.empty());
    //                                                                                 
    ifstream input;
    if (!open_input_file(input, filename)){
        cout << "Error: File " << filename << " could not be opened." << endl;
        return false;
    }
    input >> game;
    if (game.board.empty()){
        cout << "Error: Game board could not be read." << endl;
        return false;
    }
    input.close();
    if (!input) {
        cout << "Error: Input file could not be closed." << endl;
        return false;
    }
    return true;
}

bool can_go_dir(Game game, Direction dir){
    //                
    assert(game.player_y >= 0 && game.player_y < static_cast<int>(game.board.size()));
    assert(game.player_x >= 0 && game.player_x < static_cast<int>(game.board[game.player_y].length()));
    assert(dir == North || dir == East || dir == South || dir == West);
    //                                                                    
    char block1; //                               
    char block2; //                                
    switch (dir){
        case North: if (game.player_y-1 >= 0){
                        block1 = game.board[game.player_y-1][game.player_x];
                    } else block1 = '*';
                    if (game.player_y-2 >= 0){
                        block2 = game.board[game.player_y-2][game.player_x];
                    } else block2 = '*';
                    break;
        case East:  if (game.player_x+1 < static_cast<int>(game.board[game.player_y].length())){
                        block1 = game.board[game.player_y][game.player_x+1];
                    } else block1 = '*';
                    if (game.player_x+2 < static_cast<int>(game.board[game.player_y].length())){
                        block2 = game.board[game.player_y][game.player_x+2];
                    } else block2 = '*';
                    break;
        case South: if (game.player_y+1 < static_cast<int>(game.board.size())){
                        block1 = game.board[game.player_y+1][game.player_x];
                    } else block1 = '*';
                    if (game.player_y+2 < static_cast<int>(game.board.size())){
                        block2 = game.board[game.player_y+2][game.player_x];
                    } else block2 = '*';
                    break;
        case West:  if (game.player_x-1 >= 0){
                        block1 = game.board[game.player_y][game.player_x-1];
                    } else block1 = '*';
                    if (game.player_x-2 >= 0){
                        block2 = game.board[game.player_y][game.player_x-2];
                    } else block2 = '*';
                    break;
        default:    return false;
    }
    switch (block1){ //                                                                                                         
        case ' ':
        case '.':   return true; break;
        case 'b':
        case 'B':   switch (block2){
                        case ' ':
                        case '.':   return true; break;
                        default:    return false; break;
                    } break;
        default:   return false; break;
    }
}

Game next_step(Game game, Direction dir){
    //                
    assert(game.player_y >= 0 && game.player_y < static_cast<int>(game.board.size()));
    assert(game.player_x >= 0 && game.player_x < static_cast<int>(game.board[game.player_y].length()));
    assert(dir == North || dir == East || dir == South || dir == West);
    //                                                                                     
    Game output = game;
    int offset_x = 0;
    int offset_y = 0;
    if (game.board[game.player_y][game.player_x] == 'W'){
        output.board[game.player_y][game.player_x] = '.';
    } else output.board[game.player_y][game.player_x] = ' ';
    switch (dir){
        case North: offset_y = -1; break;
        case East:  offset_x = 1; break;
        case South: offset_y = 1; break;
        case West:  offset_x = -1; break;
        default:    break;
    }
    output.player_x = game.player_x + offset_x; //                                                                                                              
    output.player_y = game.player_y + offset_y; //                                                                                                              
    switch (game.board[output.player_y][output.player_x]){
        case ' ':
        case 'b':   output.board[output.player_y][output.player_x] = 'w'; break;
        case '.':
        case 'B':   output.board[output.player_y][output.player_x] = 'W'; break;
        default:    break;
    }
    if (game.board[output.player_y][output.player_x] == 'b' || game.board[output.player_y][output.player_x] == 'B'){
        switch (game.board[output.player_y + offset_y][output.player_x + offset_x]){
            case ' ':   output.board[output.player_y + offset_y][output.player_x + offset_x] = 'b'; break;
            case '.':   output.board[output.player_y + offset_y][output.player_x + offset_x] = 'B'; break;
            default:    break;
        }
    }
    return output;
}

bool complete(Game game){
    //                
    assert(!game.board.empty());
    //                                                                                               
    for (int y = 0; y < static_cast<int>(game.board.size()); y++){
        for (int x = 0; x < static_cast<int>(game.board[y].length()); x++){
            if (game.board[y][x] == 'b') return false; //                               
        }
    }
    return true;
}

//                                                           

void show_solution_BFS(vector<Candidate>& c, int i){
    //                
    assert(i < static_cast<int>(c.size()));
    //                                                       
    vector<Game> path;
    Candidate step = c[i];
    while (step.parent != -1){
        path.insert(path.begin(),step.self);
        step = c[step.parent];
    }
    path.insert(path.begin(),c[0].self);
    for (int j = 0; j < static_cast<int>(path.size()); j++){
        cout << "Step " << j << ":" << endl;
        print_game(path[j]);
    }
}

bool game_present_BFS(vector<Candidate>& c, int i, Game g){
    //                
    assert(static_cast<int>(c.size()) > 0);
    for (int k = 0; k < static_cast<int>(c.size()); k++){
        assert(c[k].self.board.size() == g.board.size());
    }
    //                                                      
    bool same;
    for (int j = 0; j < static_cast<int>(c.size()); j++){
        same = true;
        for (int y = 0; y < static_cast<int>(c[j].self.board.size()); y++){
            if (c[j].self.board[y] != g.board[y]) same = false;
        }
        if (same == true) return true;
    }
    return false;
}

void tries_BFS(vector<Candidate>& c, int i, Direction dir){
    //                
    assert(i >= 0 && i < static_cast<int>(c.size()));
    assert(dir == North || dir == East || dir == South || dir == West);
    //                                                    
    //                                                          
    Game g = c[i].self;
    Game g_next = next_step(g, dir);
    Candidate c_next = {g_next, i};
    if (!game_present_BFS(c, i, g_next)) c.push_back (c_next);
}

void solve_BFS (Game start){
    //                
    assert(!start.board.empty());
    assert(start.player_y >= 0 && start.player_y < static_cast<int>(start.board.size()));
    assert(start.player_x >= 0 && start.player_x < static_cast<int>(start.board[start.player_y].length()));
    //                 
    vector<Candidate> c = {{start, -1}};
    int i = 0;
    Game g;
    while (i < static_cast<int>(c.size()) && !complete(c[i].self)){
        g = c[i].self;
        if (can_go_dir(g, North)) tries_BFS(c, i, North);
        if (can_go_dir(g, East)) tries_BFS(c, i, East);
        if (can_go_dir(g, South)) tries_BFS(c, i, South);
        if (can_go_dir(g, West)) tries_BFS(c, i, West);
        i++;
    }
    if (i < static_cast<int>(c.size())) show_solution_BFS(c, i);
}

//                                                              

void show_solution_DFS(vector<Game>& optimal){
    //                
    assert(static_cast<int>(optimal.size()) > 0);
    //                                                       
    for (int i = 0; i < static_cast<int>(optimal.size()); i++){
        cout << "Step " << i << ":" << endl;
        print_game(optimal[i]);
    }
}

bool game_present_DFS(vector<Game>& attempt, Game g){
    //                
    assert(static_cast<int>(attempt.size()) > 0);
    for (int k = 0; k < static_cast<int>(attempt.size()); k++){
        assert(attempt[k].board.size() == g.board.size());
    }
    //                                                            
    bool same;
    for (int j = 0; j < static_cast<int>(attempt.size()); j++){
        same = true;
        for (int y = 0; y < static_cast<int>(attempt[j].board.size()); y++){
            if (attempt[j].board[y] != g.board[y]) same = false;
        }
        if (same == true) return true;
    }
    return false;
}

void solve_DFS(vector<Game>& attempt, vector<Game>& optimal, int max_depth); //                    

void tries_DFS(vector<Game>& attempt, vector<Game>& optimal, Direction dir, int max_depth){
    //                
    assert(static_cast<int>(attempt.size()) > 0);
    assert(dir == North || dir == East || dir == South || dir == West);
    //                 
    Game g = attempt[static_cast<int>(attempt.size())-1];
    Game g_next = next_step(g, dir);
    if (!game_present_DFS(attempt, g_next)){
        attempt.push_back(g_next);
        solve_DFS(attempt, optimal, max_depth);
        attempt.pop_back();
    }
}

void solve_DFS (vector<Game>& attempt, vector<Game>& optimal, int max_depth){
    //                
    assert(static_cast<int>(attempt.size()) > 0);
    //                                                                         
    const int CURRENT = static_cast<int>(attempt.size());
    const int BEST = static_cast<int>(optimal.size());
    Game g = attempt[CURRENT-1];
    if (BEST > 0 && CURRENT >= BEST) {return;}
    else if (CURRENT > max_depth+1)  {return;}
    else if (complete(g)) {optimal = attempt; return;}
    if (can_go_dir(g, North)) tries_DFS(attempt, optimal, North, max_depth);
    if (can_go_dir(g, East)) tries_DFS(attempt, optimal, East, max_depth);
    if (can_go_dir(g, South)) tries_DFS(attempt, optimal, South, max_depth);
    if (can_go_dir(g, West)) tries_DFS(attempt, optimal, West, max_depth);
}

//                                                         

int main(){
    string filename;
    cout << "Please enter a puzzle filename:" << endl;
    getline(cin, filename);
    Game game;
    if (!(read_input(game, filename))){
        return -1;
    }

    cout << "BFS:" << endl;
    solve_BFS(game);

    cout << "DFS:" << endl;
    vector<Game> start = {game};
    vector<Game> solution = {};
    solve_DFS(start, solution, MAX_DEPTH);
    show_solution_DFS(solution);

    return 0;
}

/*                           

       
       
       
       
       
       
       

       
       
       
       
       
       
       

       
       
       
       
       
       
       

       
       
       
       
       
       
       

       
       
       
       
       
       
       

       
       
       
       
       
       
       

       
       
       
       
       
       
       

       
       
       
       
       
       
       

       
       
       
       
       
       
       

       
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

        
       
       
       
       
       
       

                          

       
       
       
       
       
       
       
       

       
       
       
       
       
       
       
       

       
       
       
       
       
       
       
       

       
       
       
       
       
       
       
       

       
       
       
       
       
       
       
       

       
       
       
       
       
       
       
       

       
       
       
       
       
       
       
       

       
       
       
       
       
       
       
       

       
       
       
       
       
       
       
       

       
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

        
       
       
       
       
       
       
       

*/

