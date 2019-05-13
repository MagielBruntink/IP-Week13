#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

enum GameObject{Wall='*', Empty=' ', EmptyDest='.', Worker='w', WorkerDest='W', Box='b', BoxDest='B'};

typedef vector<vector<GameObject>> GameWorld;

struct Candidate{GameWorld candidate; int parent_candidate;};

void print_world(GameWorld world)
{
    //             
    assert(true);
    /*               
                                                 
    */
    for(unsigned int i=0; i<world.size(); i++){
        for(unsigned int j=0; j<world[i].size(); j++){
            cout << (char)world[i][j];
        }
        cout << endl;
    }
    cout << endl;
    return;
}

void process_file(ifstream& input, GameWorld& world)
{
    //             
    assert(input.is_open());
    /*               
                                                               
    */
    char input_char = ' ';
    int counter = 0;
    while(input){
        input.get(input_char);
        //                                                                                     
        if(input_char != '\n'){
            world.push_back(vector<GameObject>());
        }
        while(input && input_char != '\n'){
            world[counter].push_back((GameObject)input_char);
            input.get(input_char);
        }
        counter++;
    }
    return;
}

bool open_file(ifstream& input_file, string filename)
{
    //             
    assert(true);
    /*               
                                                                      
                              
    */
    input_file.open(filename.c_str());
    if(input_file.is_open()){
        return true;
    } else{
        return false;
    }
}

bool close_file(ifstream& input_file)
{
    //             
    assert(true);
    /*               
                                                                        
                              
    */
    //           
    input_file.clear();
    input_file.close();
    if(input_file){
        return true;
    } else{
        //                                      
        return false;
    }
}

void find_worker(GameWorld world, int& i, int& j)
{
    //             
    assert(true);
    /*               
                                                                   
                                                          
    */
    for(unsigned int k=0; k<world.size(); k++){
        for(unsigned int l=0; l<world[k].size(); l++){
            if(world[k][l] == Worker){
                i = k;
                j = l;
                return;
            }
        }
    }
    i = -1;
    j = -1;
    return;
}

bool worlds_match(GameWorld a, GameWorld b){
    //             
    assert(true);
    /*               
                                                                                             
    */
    if(a.size() != b.size()){
        return false;
    }
    for(unsigned int i=0; i<a.size(); i++){
        if(a[i].size() != b[i].size()){
            return false;
        }
        for(unsigned int j=0; j<a[i].size(); j++){
            if(a[i][j] != b[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool world_present(vector<Candidate> candidates, GameWorld world)
{
    //             
    assert(true);
    /*               
                                                                                                                        
    */
    for(unsigned int i=0; i<candidates.size(); i++){
        if(worlds_match(candidates[i].candidate, world)){
            return true;
        }
    }
    return false;
}

void add_candidates(vector<Candidate>& candidates, int index, GameWorld world)
{
    //             
    assert(true);
    /*               
                                                                                                              
    */
    int i, j;
    find_worker(world, i, j);
    GameWorld copy_world = world;
    //                        
    if(world[i-1][j] != Wall && !((world[i-1][j]== Box || world[i-1][j] == BoxDest) && !(world[i-2][j] == Empty || world[i-2][j] == EmptyDest)) ){
        copy_world[i][j] = Empty;
        if(world[i-1][j] == Box || world[i-1][j] == BoxDest){
            if(world[i-2][j] == EmptyDest){
                copy_world[i-2][j] = BoxDest;
            } else{
                copy_world[i-2][j] = Box;
            }
        }
        copy_world[i-1][j] = Worker;
        if(!world_present(candidates, copy_world)){
            candidates.push_back({copy_world, index});
        }
        copy_world = world;
    }
    //                       
    if(world[i][j+1] != Wall && !((world[i][j+1]== Box || world[i][j+1] == BoxDest) && !(world[i][j+2] == Empty || world[i][j+2] == EmptyDest)) ){
        copy_world[i][j] = Empty;
        if(world[i][j+1] == Box || world[i][j+1] == BoxDest){
            if(world[i][j+2] == EmptyDest){
                copy_world[i][j+2] = BoxDest;
            } else{
                copy_world[i][j+2] = Box;
            }
        }
        copy_world[i][j+1] = Worker;
        if(!world_present(candidates, copy_world)){
            candidates.push_back({copy_world, index});
        }
        copy_world = world;
    }
    //                        
    if(world[i+1][j] != Wall && !((world[i+1][j]== Box || world[i+1][j] == BoxDest) && !(world[i+2][j] == Empty || world[i+2][j] == EmptyDest)) ){
        copy_world[i][j] = Empty;
        if(world[i+1][j] == Box || world[i+1][j] == BoxDest){
            if(world[i+2][j] == EmptyDest){
                copy_world[i+2][j] = BoxDest;
            } else{
                copy_world[i+2][j] = Box;
            }
        }
        copy_world[i+1][j] = Worker;
        if(!world_present(candidates, copy_world)){
            candidates.push_back({copy_world, index});
        }
        copy_world = world;
    }
    //                       
    if(world[i][j-1] != Wall && !((world[i][j-1]== Box || world[i][j-1] == BoxDest) && !(world[i][j-2] == Empty || world[i][j-2] == EmptyDest)) ){
        copy_world[i][j] = Empty;
        if(world[i][j-1] == Box || world[i][j-1] == BoxDest){
            if(world[i][j-2] == EmptyDest){
                copy_world[i][j-2] = BoxDest;
            } else{
                copy_world[i][j-2] = Box;
            }
        }
        copy_world[i][j-1] = Worker;
        if(!world_present(candidates, copy_world)){
            candidates.push_back({copy_world, index});
        }
    }
}

bool world_ready(GameWorld world){
    //             
    assert(true);
    /*               
                                                                 
    */
    for(unsigned int i=0; i<world.size(); i++){
        for(unsigned int j=0; j<world[i].size(); j++){
            if(world[i][j] == Box){
                return false;
            }
        }
    }
    return true;
}

void show_path(vector<Candidate> candidates, int i){
    //             
    assert(true);
    /*               
                                                                                                      
                                     
    */
    vector<int> path;
    while(i != -1){
        path.push_back(i);
        i = candidates[i].parent_candidate;
    }
    for(int j=path.size()-1; j>=0; j--){
        print_world(candidates[path[j]].candidate);
    }
}

void solve(GameWorld start)
{
    //             
    assert(true);
    /*               
                                                                                                          
                                  
    */
    vector<Candidate> candidates = {{start, -1}};
    int i = 0;
    while(i < candidates.size() && !world_ready(candidates[i].candidate)){
        GameWorld p = candidates[i].candidate;
        add_candidates(candidates, i, p);
        i++;

    }
    if(i < candidates.size()){
        cout << "Solution: " << endl;
        show_path(candidates, i);
    }
}

//                                                                

/*
                                                                                                                                 
                         
              
              
              
              
              
              

                           
              
              
              
              
              
              

              
              
              
              
              
              

                           
              
              
              
              
              
              
              

              
              
              
              
              
              
              
*/

int main()
{
    ifstream input;
    GameWorld world;
    vector<string> world_names = {"challenge.0.txt", "challenge.1.a.txt", "challenge.1.b.txt", "challenge.23.txt", "challenge.25.txt", "challenge.31.txt", "challenge.34.txt"};
    for(unsigned int i=0; i<world_names.size(); i++){
        if(!open_file(input, world_names[i])){
            cout << "Unable to open file, exiting" << endl;
            return -1;
        }
        process_file(input, world);
        if(!close_file(input)){
            cout << "Unable to close file properly, exiting" << endl;
            return -1;
        }
        solve(world);
        GameWorld empty_world;
        world = empty_world;
    }
}

