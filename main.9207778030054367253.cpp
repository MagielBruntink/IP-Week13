#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

/*
                                                    
*/

using namespace std;

string challenge;

struct puzzle{
    vector<vector<char> > field;
    int xW;
    int yW;
};

struct candidate {
    puzzle candidate;
    int parent_candidate;
};

void print_puzzle(puzzle p)
{
    //              
    assert(p.field.size() > 0 && p.field[0].size() > 0);
    //                                                          
    vector<vector<char > > field = p.field;
    for (int i = 0; i < field.size(); i++){
        for ( int j = 0; j < field[i].size(); j ++ ){
            cout<<field[i][j];
        }
        cout << endl;
    }
    //                                                                           
}

void read_field(string filename, puzzle& p)
{
    //              
    assert(filename != "");
    //                                              
    ifstream infile(filename.c_str());
    cout << "Reading file..." << endl;
    do {
        string line;
        getline(infile,line,'\n');
        vector<char> lineVector;
        for (int i = 0; i < line.size(); i ++ ){
            if (line[i] == 'w') {
                p.xW = i;
                p.yW = p.field.size();
            }
            lineVector.push_back(line[i]);
        }
        p.field.push_back(lineVector);
    } while (infile);
    cout << "Done reading file" << endl;
}

struct direction{
    int x;
    int y;
};

bool can_move_w(puzzle p, direction d)
{
    //              
    assert(d.x <= 1 && d.x >= -1 && d.y <= 1 && d.y >= -1);
    //                                                                           
    //                                                           
    int newX = p.xW + d.x;
    int newY = p.yW + d.y;
    if (p.field[newY][newX] == ' ' || p.field[newY][newX] == '.'){
        return true;
    }
    if (p.field[newY][newX] == 'b' || p.field[newY][newX] == 'B' ){
        newX += d.x;
        newY += d.y;
        if (p.field[newY][newX] == ' ' || p.field[newY][newX] == '.'){
            return true;
        }
    }
    return false;
}

void move_w(puzzle& p, direction d){
    //              
    assert(can_move_w(p,d));
    //                                                                                                   
    if (p.field[p.yW][p.xW] == 'w'){ //                            
        p.field[p.yW][p.xW] = ' '; //                                    
    } else {
        p.field[p.yW][p.xW] = '.'; //                               
    }
    p.xW = p.xW + d.x; //                     
    p.yW = p.yW + d.y;
    if (p.field[p.yW][p.xW] == 'b' || p.field[p.yW][p.xW] == 'B'){ //                              
        if (p.field[p.yW + d.y][p.xW+d.x] == ' '){
            p.field[p.yW + d.y][p.xW + d.x] = 'b'; //           
        } else {
            p.field[p.yW + d.y][p.xW + d.x] = 'B'; //                         
        }
    }
    if (p.field[p.yW][p.xW] == '.' || p.field[p.yW][p.xW] == 'B'){ //                         
        p.field[p.yW][p.xW] = 'W'; //                         
    } else {
        p.field[p.yW][p.xW] = 'w'; //         
    }
}

bool puzzles_equal(puzzle p1, puzzle p2){
    //              
    assert(p1.field.size() == p2.field.size() && p1.field[0].size() == p2.field[0].size());
    //                                                         
    for (int i = 0; i< p1.field.size() ; i++){
        for (int j = 0; j< p1.field[i].size(); j++){
            if (p1.field[i][j] != p2.field[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool puzzle_present(vector<candidate> candidates, candidate c){
    //              
    assert(true);
    //                                                                                                                            
    for (int i = 0; i < candidates.size(); i++){
        if (puzzles_equal(candidates[i].candidate, c.candidate)) {
            return true;
        }
    }
    return false;
}

void write_path(vector<candidate> candidates, int i, string filename) {
    //              
    assert(i > -1 && filename != "");
    //                                                     
    ofstream outfile(filename.c_str());
    vector<vector<char > > field;
    while( i >= 0) {
        field = candidates[i].candidate.field;
        for (int j = 0; j < field.size(); j++){
            for ( int k = 0; k < field[j].size(); k ++ ){
                outfile << field[j][k];
            }
            outfile << endl;
        }
        i = candidates[i].parent_candidate;
    }
    outfile.close();
}

void show_path(vector<candidate> candidates, int i ){
    //              
    assert(i >= 0);
    //                                                                                                    
    while (i >= 0) {
        print_puzzle(candidates[i].candidate);
        i = candidates[i].parent_candidate;
    }
}

bool solution(puzzle p )
{
    //              
    assert(p.field.size() >0);
    //                                                              
    vector<vector< char > > field = p.field;
    for ( int i = 0; i < field.size(); i++){
        for ( int j = 0; j < field[i].size(); j++){
            if (field[i][j] == 'b'){
                return false;
            }
        }
    }
    //                                             
    return true;
}

void tries (vector<candidate>& c, int i , direction d) {
    //              
    assert(true);
    //                                                                                                  
    puzzle p = c[i].candidate;
    puzzle newP = p;
    move_w(newP,d);
    candidate newC = {newP, i};
    if (!puzzle_present(c,newC)){
        c.push_back(newC);
    }
}

void solve(puzzle start) {
    //              
    assert(true);
    //                                               
    cout << "Trying to find a solution breadth-first"<< endl;
    vector<candidate> c = {{start, -1}};
    int i = 0;
    while ( i < c.size() && !solution(c[i].candidate)) {
        puzzle p = c[i].candidate;
        if (can_move_w(p, {0,-1})) tries(c, i, {0,-1}); //       
        if (can_move_w(p, {0,1})) tries(c, i, {0,1});//          
        if (can_move_w(p, {1,0})) tries(c, i, {1,0}); //           
        if (can_move_w(p, {-1,0})) tries(c, i, {-1,0}); //          
        i++;
    }
    if ( i < c.size() ) {
        cout << "There is a solution and it is: "<< endl;
        show_path(c, i);
        write_path(c,i,challenge + " breadth-first solution.txt");
    } else {
        cout << "There is no solution?" << endl;
    }
}

void write_best(vector<puzzle> best, string filename) {
    //              
    assert(filename != "");
    //                                                                           
    ofstream outfile(filename.c_str());
    vector<vector<char > > field;
    for (int i = 0; i < best.size(); i++) {
        field = best[i].field;
        for (int j = 0; j < field.size(); j++){
            for ( int k = 0; k < field[j].size(); k ++ ){
                outfile << field[j][k];
            }
            outfile << endl;
        }
    }
    outfile.close();
}

bool puzzle_present_depth(puzzle p, vector<puzzle> c) {
    //              
    assert(c.size() > 0);
    //                                                                             
    for ( int i = 0; i < c.size(); i++){
        if ( puzzles_equal(p,c[i])) {
            return true;
        }
    }
    return false;
}

void solve_depth (vector<puzzle>& attempt, vector<puzzle>& shortest, int max_depth );

void tries_depth (vector<puzzle>& attempt, direction d, vector<puzzle>& shortest, int max_depth){
    puzzle p = attempt[attempt.size() - 1];
    puzzle newp = p;
    move_w(newp, d);
    if(!puzzle_present_depth(newp,attempt)){
        attempt.push_back(newp);
        solve_depth(attempt,shortest, max_depth);
        attempt.pop_back();
    }
}

void solve_depth (vector<puzzle>& attempt, vector<puzzle>& shortest, int max_depth ){
    //              
    assert(true);
    //                                                                               
    const int CURRENT = attempt.size();
    const int BEST = shortest.size();
    puzzle p = attempt[CURRENT -1];
    if( BEST > 0 && CURRENT >= BEST) {
        return;
    }
    else if (CURRENT > max_depth + 1) {
        return;
    }
    else if (solution(p)) {
        shortest = attempt;
        return;
    }
    if (can_move_w(p, {0,-1})) tries_depth(attempt, {0,-1}, shortest, max_depth); //       
    if (can_move_w(p, {0,1})) tries_depth(attempt, {0,1}, shortest, max_depth);//          
    if (can_move_w(p, {1,0})) tries_depth(attempt, {1,0}, shortest, max_depth); //           
    if (can_move_w(p, {-1,0})) tries_depth(attempt, {-1,0}, shortest, max_depth); //          
}

void solve_puzzle_depth(puzzle p) {
    //              
    assert(true);
    //                                                                     
    cout << "Solving the puzzle depth-first..." << endl;
    vector<puzzle> attempt = {p};
    vector<puzzle> shortest;
    int max_depth = 10;
    solve_depth(attempt,shortest,25);
    if (shortest.size() > 0){
        cout << "There is a solution and it is: " << endl;
        for (int i = 0; i < shortest.size(); i++){
            print_puzzle(shortest[i]);
        }
        write_best(shortest, challenge + " depth-first solution.txt");
    } else {
        cout << "There is no solution?" << endl;
    }
}

int main()
{
    challenge = "challenge.23";
    puzzle p;
    read_field(challenge + ".txt", p);
    print_puzzle(p);
    solve(p); //              
    //                                    

    return 0;
}

