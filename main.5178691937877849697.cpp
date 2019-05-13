#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cassert>

using namespace std;

//                                                            

enum Direction {North, South, West, East};

struct Puzzle{
    vector<char> arr;
    int width;
    int pos;
};

struct Candidate{
    Puzzle candidate;
    int parent;
};

void show_puzzle(Puzzle p){
    //            
    assert(true);
    //             
    //                                                     
    int j = 1;
    for(int i = 0; i < p.arr.size(); i++){
        cout << p.arr[i];
        if(j % p.width == 0){
            cout << endl;
        }
        j++;
    }
}

void read_file(ifstream& infile, Puzzle& puzzle, string filename){
    //            
    assert(true);
    //             
    //                                                                                                                        
    //                                                    
    char c;
    string line;
    int width;
    int i = 0;
    infile.open(filename + ".txt");

    getline(infile, line);
    puzzle.width = line.length();
    infile.clear();
    infile.close();

    infile.open(filename + ".txt");
    while(infile){

        infile.get(c);
        if(c == 'w'){
            puzzle.pos = i;
        }
        if(c != '\n'){
            puzzle.arr.push_back(c);
            i++;
        }
    }
    infile.clear();
    infile.close();
}

bool can_go_direction(Puzzle p, Direction d){
    //            
    assert(true);
    //             
    //                                                                                                            
    if(d == North){
        if(p.arr[p.pos - p.width] == 'b' || p.arr[p.pos - p.width] == 'B') return (p.arr[p.pos - 2*p.width] != '*' && (p.arr[p.pos - 2*p.width] != 'b' && p.arr[p.pos - 2*p.width] != 'B'));
        else return (p.arr[p.pos - p.width] != '*');
    }
    if(d == South){
        if(p.arr[p.pos + p.width] == 'b' || p.arr[p.pos + p.width] == 'B') return (p.arr[p.pos + 2*p.width] != '*' && (p.arr[p.pos + 2*p.width] != 'b' && p.arr[p.pos + 2*p.width] != 'B'));
        else return (p.arr[p.pos + p.width] != '*');
    }
    if(d == West){
       if(p.arr[p.pos - 1] == 'b' || p.arr[p.pos - 1] == 'B') return (p.arr[p.pos - 2] != '*' && (p.arr[p.pos - 2] != 'b' && p.arr[p.pos - 2] != 'B'));
        else return (p.arr[p.pos - 1] != '*');
    }
    if(d == East){
        if(p.arr[p.pos + 1] == 'b' || p.arr[p.pos + 1] == 'B') return (p.arr[p.pos + 2] != '*' && (p.arr[p.pos + 2] != 'b' && p.arr[p.pos + 2] != 'B'));
        else return (p.arr[p.pos + 1] != '*');
    }
}

int direct(Puzzle p, Direction d){
    //            
    assert(true);
    //             
    //                                                                                                        
    if(d == North)return p.pos - p.width;
    if(d == South)return p.pos + p.width;
    if(d == West)return p.pos - 1;
    if(d == East)return p.pos + 1;
}

Puzzle move_empty(Puzzle p, int next){
    //            
    assert(true);
    //             
    //                                                                                                                                                                    
    if(p.arr[p.pos] == 'W')p.arr[p.pos] = '.';
    else p.arr[p.pos] = ' ';
    if(p.arr[next] == '.')p.arr[next] = 'W';
    else if(p.arr[next] == ' ') p.arr[next] = 'w';
    else{
        if(p.arr[next] == 'b'){
            if(p.arr[next + next - p.pos] == '.') p.arr[next + (next - p.pos)] = 'B';
            else p.arr[next + (next - p.pos)] = 'b';
        }else if(p.arr[next] == 'B'){
            if(p.arr[next + next - p.pos] == '.'){
                p.arr[next + (next - p.pos)] = 'B';
                p.arr[next] = '.';
            }else{
                p.arr[next + (next - p.pos)] = 'b';
                p.arr[next] = '.';
            }
        }
        if(p.arr[next] == '.') p.arr[next] = 'W';
        else p.arr[next] = 'w';
    }
    p.pos = next;
    return p;
}

bool equal(Puzzle p1, Puzzle p2){
    //            
    assert(true);
    //             
    //                                                      
    bool equality = true;
    for(int i = 0; i < p1.arr.size(); i++){
        if(p1.arr[i] != p2.arr[i]){
            equality = false;
        }
    }
    return equality;
}

bool puzzle_ready(Puzzle p){
    //            
    assert(true);
    //             
    //                                                    
    //                                                                                                                                                 
    vector<char> dots;
    vector<char> boxes;
    vector<char> workers;
    for(int i = 0; i < p.arr.size(); i++){
        if(p.arr[i] == '.'){
            dots.push_back(p.arr[i]);
        }
    }
    for(int j = 0; j < p.arr.size(); j++){
        if(p.arr[j] == 'B'){
            boxes.push_back(p.arr[j]);
        }
    }
    for(int k = 0; k < p.arr.size(); k++){
        if(p.arr[k] == 'W'){
            workers.push_back(p.arr[k]);
        }
    }
    return dots.size() == 0 && workers.size() == 0 && boxes.size() > 0;
}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle p){
    //            
    assert(true);
    //             
    //                                                                                                 
    bool found = false;
    for(int i = 0; i < c.size(); i++){
        if(equal(p, c[i].candidate)){
            found = true;
        }
    }
    return found;
}

bool puzzle_present(Puzzle p, vector<Puzzle>& c){
    //            
    assert(true);
    //             
    //                                                                                              
    bool found = false;
    for(int i = 0; i < c.size(); i++){
        if(equal(p, c[i])){
            found = true;
        }
    }
    return found;
}

void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);
//                                  

void tries(vector<Candidate>& c, int i, int next){
    //            
    assert(true);
    //             
    //                                                                                                                 
    //                                            
    Puzzle p = c[i].candidate;
    Puzzle newp = move_empty(p, next);
    Candidate newc = {newp, i};
    if(!puzzle_present(c, i, newp)){
        c.push_back(newc);
    }
}

void tries(vector<Puzzle>& attempt, int next, vector<Puzzle>& shortest, int max_depth){
    //            
    assert(true);
    //             
    //                                                                                                                            
    //                                         
    Puzzle p    = attempt[attempt.size() - 1];
    Puzzle newp = move_empty(p, next);
    if(!puzzle_present(newp, attempt)){
        attempt.push_back(newp);
        depth_first(attempt, shortest, max_depth);
        attempt.pop_back();
    }
}

void show_path(vector<Candidate>c , int i){
    //            
    assert(true);
    //             
    //                                                                                            
    int j = i;
    while(j > -1){
        show_puzzle(c[j].candidate);
        cout << endl << endl;
        j = c[j].parent;
    }
}

void show_path(vector<Puzzle>& c){
    //            
    assert(true);
    //             
    //                                                                                            
    for(int i = 0; i < c.size(); i++){
        show_puzzle(c[i]);
        cout << endl << endl;
    }
}

void depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth){
    //            
    assert(attempt.size()>0 && max_depth >= 0);
    //             
    //                                                                                                                                       
    //                                                                                             
    const int CURRENT   = attempt.size();
    const int BEST      = shortest.size();
    Puzzle p            = attempt[CURRENT - 1];
    if(BEST > 0 && CURRENT >= BEST)return;
    else if(CURRENT > max_depth + 1)return;
    else if(puzzle_ready(p)){shortest = attempt; return;}
    if(can_go_direction(p, North)){ tries(attempt, direct(p, North), shortest, max_depth);}
    if(can_go_direction(p, South)){ tries(attempt, direct(p, South), shortest, max_depth);}
    if(can_go_direction (p, West)){ tries(attempt, direct(p,  West), shortest, max_depth);}
    if(can_go_direction (p, East)){ tries(attempt, direct(p,  East), shortest, max_depth);}
}

void breath_fisrt(Puzzle& start){
    //            
    assert(true);
    //             
    //                                                                                                 
    vector<Candidate> c = {{start, -1}};
    int i = 0;

    while(i < c.size() && !puzzle_ready(c[i].candidate)){
        Puzzle p = c[i].candidate;
        if(can_go_direction(p, North)){tries(c, i, direct(p, North));}
        if(can_go_direction(p, South)){tries(c, i, direct(p, South));}
        if(can_go_direction (p, West)){tries(c, i, direct(p,  West));}
        if(can_go_direction (p, East)){tries(c, i, direct(p,  East));}
        i += 1;
    }
    if(i < c.size()){
        show_path(c, i);
    }
}

int main()
{
    ifstream infile;
    string filename;
    Puzzle puzzle;
    int max_depth;
    vector<Puzzle> attempt;
    vector<Puzzle> shortest;
    cout << "what file to read?" << endl;
    cin >> filename;
    cout << "What is the max depth?" << endl; //                     
    cin >> max_depth; //                      
    read_file(infile, puzzle, filename);
    attempt.push_back(puzzle);
    cout << "width: " << puzzle.width << endl;
    //                     
    depth_first(attempt, shortest, max_depth);
    show_path(shortest); //                      
    return 0;
}

