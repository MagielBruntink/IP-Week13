//                                                     
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

struct State;
typedef vector<vector<bool>> vvb;
typedef vector<State> History;

const int MAX_WIDTH = 14;
const int MAX_HEIGHT = 14;
const int MAX_DEPTH = 31;
enum Dir{Left,Up,Right,Down};
vector<int> dx = {-1,0,1,0};
vector<int> dy = {0,-1,0,1};
vector<char> symbol = {'L','U','R','D'};

struct State{
	int width=0,height=0;
	vvb walls;
	vvb goals;
	vvb boxes;
	int workerx;
	int workery;
	bool finished(){
		//            
		assert(true);
		//             
		//                                           
		//                                                                  
		for (int y = 2;y<height+2;y++){
			for (int x = 2;x<width+2;x++){
				if (boxes[y][x] and not goals[y][x]){
					return false;
				}
			}
		}
		return true;
	}
	bool move(Dir dir){
		if (walls[workery+dy[dir]][workerx+dx[dir]]) //                       
			return false;
		if (boxes[workery+dy[dir]][workerx+dx[dir]] //                                 
		 and (walls[workery+2*dy[dir]][workerx+2*dx[dir]]
		  or boxes[workery+2*dy[dir]][workerx+2*dx[dir]]))
			return false;
		if (boxes[workery+dy[dir]][workerx+dx[dir]]){ //        
			boxes[workery+dy[dir]][workerx+dx[dir]] = false;
			boxes[workery+2*dy[dir]][workerx+2*dx[dir]] = true;
		}
		workerx += dx[dir];
		workery += dy[dir];
		return true;
	}
};

istream& operator>>(istream& input,State& state){
	//            
	assert(input);
	//                            
	//             
	//                                                       
	//                                                                            
	state.walls.assign(MAX_HEIGHT,vector<bool>(MAX_WIDTH,false));
	state.goals.assign(MAX_HEIGHT,vector<bool>(MAX_WIDTH,false));
	state.boxes.assign(MAX_HEIGHT,vector<bool>(MAX_WIDTH,false));
	int x=0,y=0;
	while (input){
		//                           
		char cell;
		input.get(cell);
		if (cell == '\n'){
			y++;
			x=0;
		}
		else{
			if (cell != ' '){
				state.width = max(state.width,x+1);
				state.height = max(state.height,y+1);
			}
			if (cell == '*')
				state.walls[y+2][x+2] = true;
			if (cell == '.' or cell == 'W' or cell == 'B')
				state.goals[y+2][x+2] = true;
			if (cell == 'b' or cell == 'B')
				state.boxes[y+2][x+2] = true;
			if (cell == 'w' or cell == 'W'){
				state.workerx = x+2;
				state.workery = y+2;
			}
			x++;
		}
	}
	return input;
}
ostream& operator<<(ostream& output,State& state){
	//            
	assert(output);
	//             
	//                                        
	for (int y = 2;y<state.height+2;y++){
		for (int x = 2;x<state.width+2;x++){
			if (state.walls[y][x]){ //        
				cout << '*';
			}
			else if (x == state.workerx and y == state.workery){ //          
				if (state.goals[y][x])
					cout << 'W';
				else
					cout << 'w';
			}
			else if (state.boxes[y][x]){ //       
				if (state.goals[y][x])
					cout << 'B';
				else
					cout << 'b';
			}
			else{ //     
				if (state.goals[y][x])
					cout << '.';
				else
					cout << ' ';
			}
		}
		cout << endl;
	}
	return output;
}

bool contains(History& history,State& state){
	//            
	assert(true);
	//             
	//                                      
	for (int i = 0;i<history.size();i++){
		if (history[i].boxes == state.boxes and
		 history[i].workerx == state.workerx and
		 history[i].workery == state.workery){
			return true;
		}
	}
	return false;
}

void solve_bfs(State puzzle,History& shortest){
	//            
	assert(true);
	//                                                    
	//             
	//                                                          
	vector<State> todo;
	vector<int> parent;
	todo.push_back(puzzle);
	parent.push_back(-1);
	int idx = 0;
	while (idx<todo.size() and not todo[idx].finished()){
		//                                                       
		cerr << idx << " " << todo.size() << endl;
		State current = todo[idx];
		for (int dir=0;dir<4;dir++){
			State next = current;
			if (next.move(static_cast<Dir>(dir)) and not contains(todo,next)){
				todo.push_back(next);
				parent.push_back(idx);
			}
		}
		idx++;
	}
	if (todo[idx].finished()){
		vector<State> temp; //                     
		while (idx >= 0){
			temp.push_back(todo[idx]);
			idx = parent[idx];
		}
		while (temp.size()>0){
			shortest.push_back(temp[temp.size()-1]);
			temp.pop_back();
		}

	}
	return;
}

void solve_dfs(History& attempt,string attemptStr,History& shortest,string& shortestStr){
	//            
	assert(attempt.size()>0 and MAX_DEPTH>=0);
	//             
	//                                                                   
	//                                                               
	//                 

	//                                          
	cerr << attemptStr << endl;
	if (shortest.size() > 0 and attempt.size()>=shortest.size())
		return;
	if (attempt.size()-1 > MAX_DEPTH) //                     
		return;
	State current = attempt[attempt.size()-1];
	if (current.finished()){
		shortest = attempt;
		shortestStr = attemptStr;
		return;
	}
	for (int dir=0;dir<4;dir++){
		State next = current;
		if (next.move(static_cast<Dir>(dir)) and not contains(attempt,next)){
			attempt.push_back(next);
			solve_dfs(attempt,attemptStr+symbol[dir],shortest,shortestStr);
			attempt.pop_back();
		}
	}
	return;
}

int main(){
	State puzzle;
	//                                                 
	cin >> puzzle;
	History start(1,puzzle);
	History shortest(0);
	string ans = "";
	solve_bfs(puzzle,shortest);
	//                                  
	for (State state:shortest)
		cout << state << endl;
	cout << ans << endl;
	return 0;
}
