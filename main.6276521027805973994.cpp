#include <iostream>
#include <vector>
#include <cassert>
#include <string>
using namespace std;
//                                 
enum Cell{wall,none,dest,worker,workerdest,box,boxdest};

const string SYMBOLS="* .wWbB";
const string FULLNAMES[]={"Wall","Empty","Dest","Worker","WorkerDest","Box","BoxDest"};
struct Pos{int row, col;};
const Pos UP={-1,0};
const Pos RIGHT={0,1};
const Pos DOWN={1,0};
const Pos LEFT={0,-1};
//                                             
//                                        
struct Puzzle{vector<vector<Cell> > field; vector<Pos> dests; Pos employee;};

struct Candidate{Puzzle candidate; int parent_candidate;};
//                 
//                                                                                                 
int size(const vector<Cell>& v){
    return(static_cast<int>(v.size()));
}

int size(const vector<vector<Cell> >& v){
    return(static_cast<int>(v.size()));
}

int size(const vector<Pos>& v){
    return(static_cast<int>(v.size()));
}

int size(const vector<Puzzle>& v){
    return(static_cast<int>(v.size()));
}

int size(const vector<Candidate>& v){
    return(static_cast<int>(v.size()));
}

int size(const vector<string>& v){
    return(static_cast<int>(v.size()));
}

int size(const string& v){
    return(static_cast<int>(v.size()));
}

ostream& operator<<(ostream& out, const vector<vector<Cell> >& p){
    //              
    assert(true);
    //                                                                            
    for(int row_i=0;row_i<size(p);row_i++){
        for(int col_i=0;col_i<size(p[row_i]);col_i++){
            out<<SYMBOLS[p[row_i][col_i]];
        }
    out<<endl;
    }
    return out;
}
bool operator==(const Pos& a,const Pos& b){
    //              
    assert(true);
    //                                                                                  
    return a.col==b.col&&a.row==b.row;
}

bool operator==(const Puzzle& a, const Puzzle& b){
    //              
    assert(true);
    //                                                                                  
    return a.field==b.field&&a.dests==b.dests&&a.employee==b.employee;
}

bool solved(const Puzzle& p){
    //              
    assert(true);
    //                                                                         
    for(int i=0;i<size(p.dests);i++){
        Cell c=p.field[p.dests[i].row][p.dests[i].col];
        if(c!=boxdest){
            return false;
        }
    }
    return true;
}

Cell remove_worker(Cell current){
    //              
    assert(current==worker || current==workerdest);
    //                                                              
    //                                    
    switch(current){
        case worker: return none;
        case workerdest: return dest;
        //                                          
        case wall: case box: case boxdest: case none: case dest: default: exit(3);
    };
}

Cell add_worker(Cell current){
    //              
    assert(current!=wall && current!=worker && current!= workerdest);
    //                                                          
    //                                                                   
    switch(current){
        case none: case box: return worker;
        case dest: case boxdest: return workerdest;
        //                                          
        case wall: case worker: case workerdest: default: exit(3);
    };
}

Cell add_box(Cell current){
    //              
    assert(current!=wall && current!=box && current!= boxdest && current!=worker && current!= workerdest);
    //                                                       
    //                                    
    switch(current){
        case none: return box;
        case dest: return boxdest;
        //                                          
        case wall: case box: case boxdest: case worker: case workerdest: default: exit(3);
    };
}

bool contains(const vector<Candidate>& c,const Puzzle& p){
    //              
    assert(true);
    //                                                                         
    int s=size(c);
    for(int i=0;i<s;i++){
        if(c[i].candidate==p){
            return true;
        }
    }
    return false;
}

void try_go(vector<Candidate>& c, Puzzle p, int i, const Pos& offset){
    //                                                                       
    //              
    assert(i<size(c)&&i>=0);
    //                                                                                                
    //                                   
    const Pos worker_pos=p.employee;
    Cell above=p.field[worker_pos.row+offset.row][worker_pos.col+offset.col];
    if(above==wall){
        return;
    }else if(above==box || above==boxdest){
        //                                                            
        //                                                  
        Cell above_box=p.field[worker_pos.row+2*offset.row][worker_pos.col+2*offset.col];
        if(above_box==wall || above_box==boxdest || above_box==box){
            //                                                                 
        }else{
            p.field[worker_pos.row][worker_pos.col]=remove_worker(p.field[worker_pos.row][worker_pos.col]);
            p.field[worker_pos.row+offset.row][worker_pos.col+offset.col]=add_worker(above);
            p.field[worker_pos.row+2*offset.row][worker_pos.col+2*offset.col]=add_box(above_box);
            p.employee={worker_pos.row+offset.row,worker_pos.col+offset.col};
            if(!contains(c,p)){
                c.push_back({p,i});
            }
        }
    }else{
        //                      
        p.field[worker_pos.row][worker_pos.col]=remove_worker(p.field[worker_pos.row][worker_pos.col]);
        p.field[worker_pos.row+offset.row][worker_pos.col+offset.col]=add_worker(above);
        p.employee={p.employee.row+offset.row,p.employee.col+offset.col};
        if(!contains(c,p)){
            c.push_back({p,i});
        }
    }
}

void show_path(vector<Candidate>& c, int i, int& path_depth){
    //              
    assert(size(c)>0&&i>=0&&path_depth>=0);
    //                                                             
    if(c[i].parent_candidate!=-1){
        path_depth++;
        show_path(c,c[i].parent_candidate, path_depth);
    }
    cout<<c[i].candidate.field;

}

void breadth_first(Puzzle& unsolved){
    //              
    assert(true);
    //                                                                    
    //                                                 
    vector<Candidate> c={{unsolved,-1}};
    int i=0;
    while(size(c)>i&&!solved(c[i].candidate)){
        Candidate curr=c[i];
        try_go(c,curr.candidate,i,UP);
        try_go(c,curr.candidate,i,DOWN);
        try_go(c,curr.candidate,i,RIGHT);
        try_go(c,curr.candidate,i,LEFT);
        i++;
    }
    if(size(c)<=i){
        //                                   
        cout<<"No solution found.";
    }else{
        int pd=0;
        cout<<"Solution found:"<<endl;
        show_path(c,i,pd);
        cout<<pd<<" step"<<(pd==1?"":"s")<<" required."<<endl;
    }

}

//                            
void solve(vector<Puzzle>& attempt, vector<Puzzle>& shortest, const int& MAX_DEPTH);

void tries(vector<Puzzle>& attempt,const Pos& offset, vector<Puzzle>& shortest, const int& MAX_DEPTH){
    //                                                                       
    //                                                              
    //              
    assert(MAX_DEPTH>0 && (size(shortest)==0 || size(shortest)>size(attempt)) && size(attempt)<=MAX_DEPTH);
    //                                                                                                              
    Puzzle p=attempt[size(attempt)-1];
    const Pos worker_pos=p.employee;
    Cell above=p.field[worker_pos.row+offset.row][worker_pos.col+offset.col];
    if(above==wall){
        return;
    }else if(above==box || above==boxdest){
        //                                                            
        //                                                  
        Cell above_box=p.field[worker_pos.row+2*offset.row][worker_pos.col+2*offset.col];
        if(above_box==wall || above_box==boxdest || above_box==box){
            //                                                                 
        }else{
            p.field[worker_pos.row][worker_pos.col]=remove_worker(p.field[worker_pos.row][worker_pos.col]);
            p.field[worker_pos.row+offset.row][worker_pos.col+offset.col]=add_worker(above);
            p.field[worker_pos.row+2*offset.row][worker_pos.col+2*offset.col]=add_box(above_box);
            p.employee={worker_pos.row+offset.row,worker_pos.col+offset.col};
            attempt.push_back(p);
            solve(attempt, shortest,MAX_DEPTH);
            attempt.pop_back();
        }
    }else{
        //                      
        p.field[worker_pos.row][worker_pos.col]=remove_worker(p.field[worker_pos.row][worker_pos.col]);
        p.field[worker_pos.row+offset.row][worker_pos.col+offset.col]=add_worker(above);
        p.employee={p.employee.row+offset.row,p.employee.col+offset.col};
        attempt.push_back(p);
        solve(attempt, shortest,MAX_DEPTH);
        attempt.pop_back();
    }
}

void solve(vector<Puzzle>& attempt, vector<Puzzle>& shortest, const int& MAX_DEPTH){
        //              
        assert(size(attempt)>0 && size(shortest)>=0 && MAX_DEPTH>=0);
        //                                                                    
        //                                              
        const int CURRENT= size(attempt);
        const int BEST= size(shortest);
        Puzzle cand = attempt[CURRENT-1];
        if(BEST>0 && CURRENT>=BEST){
            //                                                              
            return;
        }
        else if(CURRENT>MAX_DEPTH){
            //                                                      
            return;
        }else if(solved(cand)){
            //                                            
            shortest=attempt;
            return;
        }else{
            //                                           
            tries(attempt, UP, shortest, MAX_DEPTH);
            tries(attempt, RIGHT, shortest, MAX_DEPTH);
            tries(attempt, DOWN, shortest, MAX_DEPTH);
            tries(attempt, LEFT, shortest, MAX_DEPTH);
        }
}

void depth_first(Puzzle& unsolved,const int MAX_DEPTH){
    //              
    assert(MAX_DEPTH>=0);
    //                                                                                           
    //                                 
    vector<Puzzle> attempt={unsolved};
    vector<Puzzle> shortest={};
    solve(attempt,shortest,MAX_DEPTH);
    const int s=size(shortest);
    if(s==0){
        cout<<"No solution found.";
    }else{
        cout<<"Solution found:"<<endl;
        for(int i=0;i<s;i++){
            cout<<shortest[i].field;
        }
        //                                                            
        cout<<s-1<<" step"<<(s==2?"":"s")<<" required."<<endl;
    }
}

Puzzle from_strings(vector<string> represent,bool& valid){
    //              
    //                                                                                          
    assert(true);
    //                                                                      
    //                                                                    
    bool worker_found=false;
    Puzzle ret={{},{},{0,0}};
    for(int row_i=0;row_i<size(represent);row_i++){
        vector<Cell> this_row;
        for(int col_i=0;col_i<size(represent[row_i]);col_i++){
            unsigned index=SYMBOLS.find(represent[row_i][col_i]);
            if(index==string::npos){
                valid=false;
                return ret;
            }else{
                Cell curr_cell=static_cast<Cell>(index);
                if(curr_cell==worker||curr_cell==workerdest){
                    if(worker_found){
                        //                                                 
                        valid=false;
                        return ret;
                    }else{
                        worker_found=true;
                        ret.employee={row_i,col_i};
                    }
                }
                if(curr_cell==dest||curr_cell==boxdest||curr_cell==workerdest){
                    ret.dests.push_back({row_i,col_i});
                }
                this_row.push_back(curr_cell);
            }
        }
        ret.field.push_back(this_row);
    }
    return(ret);
}

int main(){
    bool valid=true;
    Puzzle challenge=from_strings({
    "**********",
    "*  w     *",
    "*  b   b *",
    "*  .     *",
    "*  ****. *",
    "*        *",
    "**********"
    },valid);
    if(valid){
        cout<<"Initial field:"<<endl;
        cout<<challenge.field<<endl;
        cout<<"Breadth first:"<<endl;
        breadth_first(challenge);
        cout<<"Depth first:"<<endl;
        depth_first(challenge,10);
        return 0;
    }else{
        cout<<"Invalid puzzle!"<<endl;
        return 1;
    }
}

