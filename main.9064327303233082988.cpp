#include <iostream>
#include <string>
#include <cassert>
#include <vector>
using namespace std;

//                                                                                                                                                       

struct Pos {int x; int y;};
struct Record {vector<char> state; Pos playerPos;};
struct Candidate {Record rec; int parent;};

int HEIGHT = 6;
int WIDTH = 10;

int posToIndex(int x, int y){
	return y*WIDTH+x;
}

Pos IndexToPos(int i){
	return {i%WIDTH,i/WIDTH};
}

int cSize(vector<Candidate>& v)
{
    return static_cast<int>(v.size());
}

int rSize(vector<Record>& v)
{
    return static_cast<int>(v.size());
}

void printState(vector<char>& state)
{
    for (int y = 0; y < HEIGHT; y++){
        for (int x = 0; x < WIDTH; x++){
            cout << state[posToIndex(x,y)];
        }
        cout << endl;
    }
}

bool isSolution(vector<char>& state){
    for (int x = 0; x < WIDTH; x++){
        for (int y = 0; y < HEIGHT; y++){
            char c = state[posToIndex(x,y)];
            if (c == '.' || c == 'W' || c == 'b'){
                return false;
            }
        }
    }
    return true;
}

bool sameStates(vector<char>& sA, vector<char>& sB)
{
    int maxEl = WIDTH*HEIGHT;
    for (int i = 0; i < maxEl; i++){
        if (sA != sB){
            return false;
        }
    }
    return true;
}

bool statePresent (vector<Candidate> can,int i,Record newRec)
{
    for (int counter = 0; counter <= i; counter++){
        if (sameStates(can[counter].rec.state,newRec.state))
        {
            return true;
        }
    }
    return false;
}

bool recordPresent (vector<Record> recs,Record newRec)
{
    int maxSize = rSize(recs);
    for (int counter = 0; counter <= maxSize; counter++){
        if (sameStates(recs[counter].state,newRec.state))
        {
            return true;
        }
    }
    return false;
}

bool going_possible(char target, char ObjectBehindTarget)
{
	return (target == ' ' || target == '.' || (target == 'b' && (ObjectBehindTarget == ' ' || ObjectBehindTarget == '.')) || (target == 'B' && (ObjectBehindTarget == ' ' || ObjectBehindTarget == '.')));
}

bool canLeft(Record rec)
{
    assert(rec.playerPos.y < HEIGHT || rec.playerPos.y >= 0 || rec.playerPos.x < WIDTH);

    if (rec.playerPos.x < 2){
        return false;
    } else {
        char target = rec.state[posToIndex(rec.playerPos.x-1,rec.playerPos.y)];
        char behindTarget = rec.state[posToIndex(rec.playerPos.x-2,rec.playerPos.y)];
        return going_possible(target, behindTarget);
    }
}

bool canRight(Record rec)
{
    assert(rec.playerPos.y < HEIGHT || rec.playerPos.y >= 0 || rec.playerPos.x >= 0);

    if (rec.playerPos.x >= WIDTH - 2){
        return false;
    } else {
        char target = rec.state[posToIndex(rec.playerPos.x+1,rec.playerPos.y)];
        char behindTarget = rec.state[posToIndex(rec.playerPos.x+2,rec.playerPos.y)];
        return going_possible(target, behindTarget);
    }
}

bool canUp(Record rec)
{
    assert(rec.playerPos.x < WIDTH || rec.playerPos.x >= 0 || rec.playerPos.y < HEIGHT);

    if (rec.playerPos.y < 2){
        return false;
    } else {
        char target = rec.state[posToIndex(rec.playerPos.x,rec.playerPos.y-1)];
        char behindTarget = rec.state[posToIndex(rec.playerPos.x,rec.playerPos.y-2)];
        return going_possible(target, behindTarget);
    }
}

bool canDown(Record rec)
{
    assert(rec.playerPos.x < WIDTH || rec.playerPos.x >= 0 || rec.playerPos.y >= 0);

    if (rec.playerPos.y >= HEIGHT - 2){
        return false;
    } else {
        char target = rec.state[posToIndex(rec.playerPos.x,rec.playerPos.y+1)];
        char behindTarget = rec.state[posToIndex(rec.playerPos.x,rec.playerPos.y+2)];
        return going_possible(target, behindTarget);
    }
}

void goUp (vector<Candidate>& can, int i)
{
    Record rec = can[i].rec;
    char target = rec.state[posToIndex(rec.playerPos.x,rec.playerPos.y-1)];
    char behindTarget = rec.state[posToIndex(rec.playerPos.x,rec.playerPos.y-2)];
    Record newRec = rec;
    newRec.playerPos.y = rec.playerPos.y-1;
    if (target == 'b' || target == 'B')
    {
        if (behindTarget == '.')
        {
            newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y-2)] ='B';
        }
        else
        {
            newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y-2)] ='b';
        }
    }
	if (target == '.' || target == 'B')
	{
    	newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y-1)] ='W';
	}
	else
	{
    	newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y-1)] ='w';
	}

    if (rec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] == 'W'){
        newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] = '.';
    } else {
        newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] = ' ';
    }

	Candidate newcan = {newRec, i};

	if (!statePresent (can, i, newRec))
	{
    	can.push_back(newcan);
	}
}

void goDown (vector<Candidate>& can, int i)
{
	Record rec = can[i].rec;
	char target = rec.state[posToIndex(rec.playerPos.x,rec.playerPos.y+1)];
	char behindTarget = rec.state[posToIndex(rec.playerPos.x,rec.playerPos.y+2)];
	Record newRec = rec;
	newRec.playerPos.y = newRec.playerPos.y+1;
   	if (target == 'b' || target == 'B')
   {
   	if (behindTarget == '.')
   	{
       	newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y+2)] ='B';
   	}
   	else
   	{
      	newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y+2)] ='b';
   	}
   }
	if (target == '.' || target == 'B')
	{
    	newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y+1)] ='W';
	}
	else
	{
    	newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y+1)] ='w';
	}

    if (rec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] == 'W'){
        newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] = '.';
    } else {
        newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] = ' ';
    }

	Candidate newcan = {newRec, i};
	if (!statePresent (can, i, newRec))
	{
    	can.push_back(newcan);
	}
}

void goLeft(vector<Candidate>& can, int i)
{
	Record rec = can[i].rec;
	char target = rec.state[posToIndex(rec.playerPos.x-1,rec.playerPos.y)];
	char behindTarget = rec.state[posToIndex(rec.playerPos.x-2,rec.playerPos.y)];
	Record newRec = rec;
	newRec.playerPos.x = newRec.playerPos.x-1;
   if (target == 'b' || target == 'B')
   {
   	if (behindTarget == '.')
   	{
       	newRec.state[posToIndex(rec.playerPos.x-2, rec.playerPos.y)] ='B';
   	}
   	else
   	{
      	newRec.state[posToIndex(rec.playerPos.x-2, rec.playerPos.y)] ='b';
   	}
   }
	if (target == '.' || target == 'B')
	{
    	newRec.state[posToIndex(rec.playerPos.x-1, rec.playerPos.y)] ='W';
	}
	else
	{
    	newRec.state[posToIndex(rec.playerPos.x-1, rec.playerPos.y)] ='w';
	}

    if (rec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] == 'W'){
        newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] = '.';
    } else {
        newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] = ' ';
    }

	Candidate newcan = {newRec, i};
	if (!statePresent (can, i, newRec))
	{
    	can.push_back(newcan);
	}
}
void goRight (vector<Candidate>& can, int i)
{
	Record rec = can[i].rec;
	char target = rec.state[posToIndex(rec.playerPos.x+1,rec.playerPos.y)];
	char behindTarget = rec.state[posToIndex(rec.playerPos.x+2,rec.playerPos.y)];
	Record newRec = rec;
	newRec.playerPos.x = newRec.playerPos.x+1;
   	if (target == 'b' || target == 'B')
   {
   	if (behindTarget == '.')
   	{
       	newRec.state[posToIndex(rec.playerPos.x+2, rec.playerPos.y)] ='B';
   	}
   	else
   	{
      	newRec.state[posToIndex(rec.playerPos.x+2, rec.playerPos.y)] ='b';
   	}
   }
	if (target == '.' || target == 'B')
	{
    	newRec.state[posToIndex(rec.playerPos.x+1, rec.playerPos.y)] ='W';
	}
	else
	{
    	newRec.state[posToIndex(rec.playerPos.x+1, rec.playerPos.y)] ='w';
	}

    if (rec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] == 'W'){
        newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] = '.';
    } else {
        newRec.state[posToIndex(rec.playerPos.x, rec.playerPos.y)] = ' ';
    }

	Candidate newcan = {newRec, i};
	if (!statePresent (can, i, newRec))
	{
    	can.push_back(newcan);
	}
}

Pos findPlayer(vector<char>& state)
{
    int mSize = WIDTH * HEIGHT;
    for (int i = 0; i < mSize; i++){
        if (state[i] == 'w' || state[i] == 'W'){
            return IndexToPos(i);
        }
    }
    return {-1,-1}; //         
}

void print_br_sol(vector<Candidate>& can, int i)
{
    vector<Record> recordList;
    while (i > -1){
        recordList.push_back(can[i].rec);
        i = can[i].parent;
    }

    for (int counter = rSize(recordList) -1; counter >= 0; counter--){
        cout << endl;
        printState(recordList[counter].state);
        cout << endl;
    }
}

void print_de_sol(vector<Record>& sol)
{
    int maxSize = rSize(sol);
    for (int i = 0; i < maxSize; i++){
        cout << endl;
        printState(sol[i].state);
        cout << endl;
    }
}

void brSolve(vector<char>& initialState)
{
    vector<Candidate> c = { {{initialState,findPlayer(initialState)} , -1} }; //                                                            
    int i = 0;
    while (i < cSize(c) && !isSolution(c[i].rec.state)){
        Record rec = c[i].rec;
        if (canUp(rec)){
            goUp(c, i);
        }
        if (canDown(rec)){
            goDown(c, i);
        }
        if (canLeft(rec)){
            goLeft(c, i);
        }
        if (canRight(rec)){
            goRight(c, i);
        }
        i++;
    }
    if (i < cSize(c)){
        print_br_sol(c, i);
    }
}

void deSolve(vector<Record>& attempt, vector<Record>& best, int max_depth); //                                  

void goDir(vector<Record>& attempt, vector<Record>& best, Pos dir, int max_depth)
{
    Record curr = attempt[rSize(attempt)-1];
    Record newRec = curr;

    int X = curr.playerPos.x;
    int Y = curr.playerPos.y;

    newRec.playerPos.x += dir.x;
    newRec.playerPos.y += dir.y;

    int targetIndex = posToIndex(X+dir.x,Y+dir.y);
    char target = curr.state[targetIndex];

    int behindTargetIndex = posToIndex(X+(dir.x*2),Y+(dir.y*2));
    char behindTarget = curr.state[behindTargetIndex];

    if (target == 'b' || target == 'B'){
        if (behindTarget == '.'){
            newRec.state[behindTargetIndex] = 'B';
        } else {
            newRec.state[behindTargetIndex] = 'b';
        }
    }

    if (target == '.' || target == 'B'){
        newRec.state[targetIndex] = 'W';
    } else {
        newRec.state[targetIndex] = 'w';
    }

    if (curr.state[posToIndex(X,Y)] == 'W'){
        newRec.state[posToIndex(X,Y)] = '.';
    } else {
        newRec.state[posToIndex(X,Y)] = ' ';
    }

    if (!recordPresent(attempt,newRec)){
        attempt.push_back(newRec); //    
        deSolve(attempt, best, max_depth); //                  
        attempt.pop_back(); //      
    }
}

void deSolve(vector<Record>& attempt, vector<Record>& best, int max_depth)
{
    //           
    //                          
    //                          
    //                       
    const int BEST = rSize(best);
    const int CURRENT = rSize(attempt);
    Record curr = attempt[CURRENT-1];

    if (BEST > 0 && CURRENT >= BEST){
        return;
    } else if (CURRENT > max_depth+1) {
        return;
    } else if (isSolution(curr.state)){
        best = attempt;
        return;
    }

    if (canUp(curr)){
        goDir(attempt, best, {0,-1}, max_depth);
    }
    if (canRight(curr)){
        goDir(attempt, best, {1,0}, max_depth);
    }
    if (canDown(curr)){
        goDir(attempt, best, {0,1}, max_depth);
    }
    if (canLeft(curr)){
        goDir(attempt, best, {-1,0}, max_depth);
    }
}

void setupAttempt(vector<char>& state, int width, int height, bool breadthFirst){
    WIDTH = width;
    HEIGHT = height;
    cout << "Global vars reset success" << endl;

    cout << "Starting state: " << endl;
    printState(state);

    cout << "This is ";
    if (isSolution(state)){
        cout << "already a ";
    } else {
        cout << "not yet a ";
    }
    cout << "solution." << endl;
    cout << "==============================" << endl;
    if (breadthFirst){
        cout << "Algorithm: Breadth-First:" << endl;
        brSolve(state);
    } else {
        cout << "Algorithm: Depth-First:" << endl;
        vector<Record> attempt = {{state, findPlayer(state)}}; //                                
        vector<Record> best;
        deSolve(attempt, best, 25);
        print_de_sol(best);
    }
}

int main()
{

    vector<char> state_1a = {'*','*','*','*','*','*','*','*','*','*',
                      	'*',' ',' ',' ',' ',' ',' ',' ',' ','*',
                      	'*',' ','.','b','w',' ',' ',' ',' ','*',
                      	'*',' ',' ','*','*','*','*',' ',' ','*',
                      	'*',' ',' ',' ',' ',' ',' ',' ',' ','*',
                      	'*','*','*','*','*','*','*','*','*','*'};
	vector<char> state_0 = {'*','*','*','*','*','*','*','*','*','*',
                        	'*',' ',' ',' ',' ',' ',' ',' ',' ','*',
                        	'*','B',' ',' ',' ',' ',' ',' ','w','*',
                        	'*',' ',' ','*','*','*','*',' ',' ','*',
                        	'*',' ',' ',' ',' ',' ',' ',' ',' ','*',
                        	'*','*','*','*','*','*','*','*','*','*'};
	vector<char> state_23 ={'*','*','*','*','*','*','*',
                        	'*','w',' ',' ',' ','*','*',
                        	'*',' ','b','b',' ',' ','*',
                        	'*',' ','*','.',' ','.','*',
                        	'*',' ',' ',' ',' ',' ','*',
                        	'*','*','*','*','*','*','*'};

    int width1 = 10;
    int height1 = 6;
    int width_23 = 7;
    int height_23 = 6;

    setupAttempt(state_0,width1,height1,true);
    cout << "--------------------" << endl << endl;
    setupAttempt(state_1a,width1,height1,true);
    cout << "--------------------" << endl << endl;
    setupAttempt(state_23,width_23,height_23,false);

    return 0;
}

