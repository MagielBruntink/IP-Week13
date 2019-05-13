#include <iostream>
using namespace std;
#include <cmath>
#include <vector>
#include <cassert>
#include <fstream>
#include <cstring>
/*                                    
                         
                            
                                    */
/*                                    
                              
                                    */
const int GAME_WIDTH  =  8;
const int GAME_HEIGHT =  6;

enum cell {WALL, EMPTY, EMPTY_DEST, WORKER, WORKER_DEST, BOX, BOX_DEST};
const char cellRepresentation[7] = {'*', ' ', '.', 'w', 'W', 'b', 'B'};

/*  
                                      
                                                                       
                                       
*/
cell ascii2cell(char x, bool& success)
{ //           
  assert(true);
  //             
  //                                     
  for(int i = 0; i < 7; i++)
    if(x == cellRepresentation[i])
      return static_cast<cell>(i);

  cout << "An error occurred (2)" << endl;
  success = false;
  return WALL;  //                            
}

/*
                                               
                                                     
                                                                 
*/
bool getChallange(string identifier, cell game[GAME_HEIGHT][GAME_WIDTH])
{ //            
  assert(true);
  //             
  //                         
  string filename = "challenge." + identifier + ".txt";
  cout << "Opening " << filename << " ... " << endl;

  ifstream infile;
  infile.open(filename.c_str());

  if(!infile.is_open())
    return false;
  cout << "Opening " << filename << " was succesfull. " << endl;

  //                                            
  //                                 
  string  line = "";
  bool    success = true;
  int y = 0;
  while(getline(infile, line) && y < GAME_HEIGHT)
  {
    for(int x = 0; x < GAME_WIDTH; x++)
      game[y][x] = ascii2cell(line[x], success);
    y++;
  }
  if(!success)
    return false;
  return true;
}

/*
                                                     
*/
void displayGame(cell game[GAME_HEIGHT][GAME_WIDTH])
{ //           
  assert(true);
  //             
  //            
  cout << endl << endl;
  for(int y = 0; y < GAME_HEIGHT; y++)
  {
    for(int x = 0; x < GAME_WIDTH; x++)
      cout << cellRepresentation[static_cast<int>(game[y][x])];
    cout << endl;
  }
}

/*                                    
          
                                    */
struct Pos {
  int x;
  int y;
};

struct state {
  int stateNo;
  int parentState;
  Pos position;
  cell game[GAME_HEIGHT][GAME_WIDTH];
};

struct sit
{
  bool inFrontOfWall;
  bool inFrontOfBox;
  bool inFrontOfBoxes;
};

enum actions {LEFT, RIGHT, UP, DOWN};

Pos findTheGuy(cell game[GAME_HEIGHT][GAME_WIDTH])
{
  for(int y = 0; y < GAME_HEIGHT; y++)
    for(int x = 0; x < GAME_WIDTH; x++)
      if(game[y][x] == WORKER || game[y][x] == WORKER_DEST)
        return {x, y};
}

/*
                                                               
                                                               
*/
void copyGame(cell a[GAME_HEIGHT][GAME_WIDTH], cell b[GAME_HEIGHT][GAME_WIDTH])
{
  for(int y = 0; y < GAME_HEIGHT; y++)
    for(int x = 0; x < GAME_WIDTH; x++)
      b[y][x] = a[y][x];
}

/*
                                                     
                                                          
*/
bool isFinished(cell game[GAME_HEIGHT][GAME_WIDTH])
{//           
  assert(true);
  //             
  //                        
  for(int y = 0; y < GAME_HEIGHT; y++)
    for(int x = 0; x < GAME_WIDTH; x++)
      if(game[y][x] == BOX)
        return false;
  return true;
}

/*
                     
                                                   
*/

bool legalStep(state currentState, actions action)
{
  sit situation = {false, false, false};
  int x = currentState.position.x;
  int y = currentState.position.y;

  switch(action)
  {
    case static_cast<int>(LEFT): {

      int one = max((x - 1) % GAME_WIDTH, 0 );
      int two = max((x - 2) % GAME_WIDTH, 0 );

      if(currentState.game[y][one] == WALL) {
        situation.inFrontOfWall = true;

      }

      if(currentState.game[y][one] == BOX ||
         currentState.game[y][one] == BOX_DEST)
        situation.inFrontOfBox = true;

      if( currentState.game[y][two] == BOX ||
          currentState.game[y][two] == BOX_DEST ||
          currentState.game[y][two] == WALL
          && situation.inFrontOfBox)
        situation.inFrontOfBoxes = true;

    } break;

    case static_cast<int>(RIGHT): {

      int one = max((x + 1) % GAME_WIDTH, 0 );
      int two = max((x + 2) % GAME_WIDTH, 0 );

      if(currentState.game[y][one] == WALL) {
        situation.inFrontOfWall = true;

      }

      if(currentState.game[y][one] == BOX ||
         currentState.game[y][one] == BOX_DEST)
        situation.inFrontOfBox = true;

      if( currentState.game[y][two] == BOX ||
          currentState.game[y][two] == BOX_DEST ||
          currentState.game[y][two] == WALL
          && situation.inFrontOfBox)
        situation.inFrontOfBoxes = true;

    } break;

    case static_cast<int>(UP): {

      int one = max((y - 1) % GAME_HEIGHT, 0 );
      int two = max((y - 2) % GAME_HEIGHT, 0 );

      if(currentState.game[one][x] == WALL) {
        situation.inFrontOfWall = true;
      }

      if(currentState.game[one][x] == BOX ||
        currentState.game[one][x] == BOX_DEST ||
         currentState.game[one][x] == BOX_DEST)
        situation.inFrontOfBox = true;

      if( currentState.game[two][x] == BOX ||
          currentState.game[two][x] == WALL
          && situation.inFrontOfBox)
        situation.inFrontOfBoxes = true;

    } break;

    case static_cast<int>(DOWN): {

      int one = max((y + 1) % GAME_HEIGHT, 0 );
      int two = max((y + 2) % GAME_HEIGHT, 0 );

      if(currentState.game[one][x] == WALL) {
        situation.inFrontOfWall = true;
      }

      if(currentState.game[one][x] == BOX ||
          currentState.game[one][x] == BOX_DEST ||
         currentState.game[one][x] == BOX_DEST)
        situation.inFrontOfBox = true;

      if( currentState.game[two][x] == BOX ||
          currentState.game[two][x] == WALL
          && situation.inFrontOfBox)
        situation.inFrontOfBoxes = true;

    } break;

    default:  return false; break;
  }
  if(situation.inFrontOfWall || situation.inFrontOfBoxes)
    return false;
  return true;
}

/*
                                                           
                                          
                                                      
*/

void left(cell game[GAME_HEIGHT][GAME_WIDTH], Pos position)
{
  int x =     position.x;
  int y =     position.y;
  cell guy    = game[y][x];
  cell viewA  = game[y][x - 1]; //            
  cell viewB  = game[y][x - 2]; //            

  if( guy == WORKER_DEST )
    game[y][x] = EMPTY_DEST;
  else
    game[y][x] = EMPTY;

  if(viewA == BOX_DEST || viewA == EMPTY_DEST)
    game[y][x - 1] = WORKER_DEST;
  else
    game[y][x - 1] = WORKER;

  if(viewA == BOX || viewA == BOX_DEST)
  {
      if(viewB == EMPTY_DEST)
        game[y][x - 2] = BOX_DEST;
      else
        game[y][x - 2] = BOX;
  }
}

void right(cell game[GAME_HEIGHT][GAME_WIDTH], Pos position)
{
  int x =     position.x;
  int y =     position.y;
  cell guy    = game[y][x];
  cell viewA  = game[y][x + 1]; //            
  cell viewB  = game[y][x + 2]; //            

  if( guy == WORKER_DEST )
    game[y][x] = EMPTY_DEST;
  else
    game[y][x] = EMPTY;

  if(viewA == BOX_DEST || viewA == EMPTY_DEST)
    game[y][x + 1] = WORKER_DEST;
  else
    game[y][x + 1] = WORKER;

  if(viewA == BOX || viewA == BOX_DEST)
  {
      if(viewB == EMPTY_DEST)
        game[y][x + 2] = BOX_DEST;
      else
        game[y][x + 2] = BOX;
  }
}

void down(cell game[GAME_HEIGHT][GAME_WIDTH], Pos position)
{
  int x =     position.x;
  int y =     position.y;
  cell guy    = game[y][x];
  cell viewA  = game[y + 1][x]; //            
  cell viewB  = game[y + 2][x]; //            

  if( guy == WORKER_DEST )
    game[y][x] = EMPTY_DEST;
  else
    game[y][x] = EMPTY;

  if(viewA == BOX_DEST || viewA == EMPTY_DEST)
    game[y + 1][x] = WORKER_DEST;
  else
    game[y + 1][x] = WORKER;

  if(viewA == BOX || viewA == BOX_DEST)
  {
      if(viewB == EMPTY_DEST)
        game[y + 2][x] = BOX_DEST;
      else
        game[y + 2][x] = BOX;
  }
}

void up(cell game[GAME_HEIGHT][GAME_WIDTH], Pos position)
{
  int x =     position.x;
  int y =     position.y;
  cell guy    = game[y][x];
  cell viewA  = game[y - 1][x]; //            
  cell viewB  = game[y - 2][x]; //            

  if( guy == WORKER_DEST )
    game[y][x] = EMPTY_DEST;
  else
    game[y][x] = EMPTY;

  if(viewA == BOX_DEST || viewA == EMPTY_DEST)
    game[y - 1][x] = WORKER_DEST;
  else
    game[y - 1][x] = WORKER;

  if(viewA == BOX || viewA == BOX_DEST)
  {
      if(viewB == EMPTY_DEST)
        game[y - 2][x] = BOX_DEST;
      else
        game[y - 2][x] = BOX;
  }
}

/*
                                                                     
                                           
                                                            
                                     
           
*/
bool tries(vector<int>& frontier, vector<state>& states, actions action)
{//            
  assert(true);
  //             
  //                                                        
  state newState        = states[frontier.front()];
  newState.parentState  = frontier.front();
  newState.stateNo      = states.size();

  switch(action)
  {
    case LEFT:  left (newState.game, newState.position); break;
    case RIGHT: right(newState.game, newState.position); break;
    case UP:    up   (newState.game, newState.position); break;
    case DOWN:  down (newState.game, newState.position); break;
    default:    break;
  }

  newState.position = findTheGuy(newState.game);

  states.push_back(newState);
  //                           

  frontier.push_back( newState.stateNo );

  if(isFinished(newState.game))
    return true;
  return false;
}

void trace () {
  //            
  assert(true);
  //                                                          
  do
   {
     cout << '\n' << "Press a key to continue...";
   } while (cin.get() != '\n');
}

/*
                  
*/
void dumpFrontier (vector<int> frontier) {
  //            
  assert(true);
  //             
  //                         
  cout << '(';
  for(int i = 0; i < frontier.size(); i++)
    cout << frontier[i] << ',';
  cout << ')';
}

/*
               
                                                      
*/
void traceBack (vector<state>& states, int lastNO)
{ //           
  assert(lastNO > 0);
  //             
  //                                              

  vector<int> sequence;
  sequence.push_back(lastNO);

  while(lastNO != -1)
  {
    sequence.push_back(states[lastNO].parentState);
    lastNO = states[lastNO].parentState;
  }
  dumpFrontier(sequence);
  for(int i = sequence.size() - 2; i >= 0; i--) {
    //                                 
    displayGame(states[sequence[i]].game);
    trace();
  }
}

void bfsSolve(cell game[GAME_HEIGHT][GAME_WIDTH])
{ //           
  assert(true);
  //             
  //                          

  vector<state> states;
  vector<int>   frontier;
  frontier.push_back(0);
  Pos position = findTheGuy(game);
  states.push_back( {0, -1, position} );

  copyGame(game, states[0].game);

  bool foundSolution  = false;
  state finishState;
  while(  !foundSolution && frontier.size() != 0   )
  {
    //        
    if(frontier.front() % 100000 == 0)
        cout << "StateNO : " << frontier.front() << endl;
    //                       

    //        
    if( legalStep(states[frontier.front() ], LEFT) ) {
      foundSolution = tries(frontier, states, LEFT);
      if(foundSolution)
        finishState = states.back();
    }

    if( legalStep(states[frontier.front() ], RIGHT) ) {
      foundSolution = tries(frontier, states, RIGHT);
      if(foundSolution)
        finishState = states.back();
    }

    if( legalStep(states[ frontier.front() ], DOWN) ) {
      foundSolution = tries(frontier, states, DOWN);
      if(foundSolution)
        finishState = states.back();
    }

    if( legalStep(states[ frontier.front() ], UP) ) {
      foundSolution = tries(frontier, states, UP);
      if(foundSolution)
        finishState = states.back();
    }

    frontier.erase(frontier.begin());

  }

  cout << "Found a solution! Here is a traceback: " << endl;
  trace();
  traceBack(states, finishState.stateNo);
}

/*
               
                                                      
*/
int countSteps (vector<state>& states, int lastNO)
{ //           
  assert(lastNO > 0);
  //             
  //                                              

  vector<int> sequence;
  sequence.push_back(lastNO);

  while(lastNO != -1)
  {
    sequence.push_back(states[lastNO].parentState);
    lastNO = states[lastNO].parentState;
  }
  return sequence.size();
}

void dfsSolve(vector<state>& attempt, vector<state>& shortest, int depth);

void dump_attempt(vector<state>& attempt)
{
  cout << "Trace back:" << endl;
  for(int i = 0; i < attempt.size(); i++) {
      displayGame(attempt[i].game);
      if(isFinished(attempt[i].game))
      {
        cout << "It took less steps than expected! Finished. " << endl;
        return;
      }
      trace();
  }
}

void dfsTries(vector<state>& attempt, vector<state>& shortest, int depth, actions action)
{//            
  assert(true);
  //             
  //                                                        
  state newState        = attempt[attempt.size() - 1];
  newState.parentState  = 1;  //                                       
  newState.stateNo      = attempt.size();

  switch(action)
  {
    case LEFT:  left (newState.game, newState.position); break;
    case RIGHT: right(newState.game, newState.position); break;
    case UP:    up   (newState.game, newState.position); break;
    case DOWN:  down (newState.game, newState.position); break;
    default:    break;
  }
  //                           

  newState.position = findTheGuy(newState.game);
  attempt.push_back(newState);
  dfsSolve(attempt, shortest, depth);

  //                           

  if (isFinished(newState.game)) {
    shortest = attempt;
    cout << endl <<
            "Found a solution! It takes " << attempt.size() << " steps. " <<
            "Type --trace to trace $  ";
    string input = "";

    getline(cin, input);
    while(input == "--trace")
    {
      dump_attempt(shortest);
      cout << "Type --trace to trace $  ";

      getline(cin, input);
    }
  }
  attempt.pop_back();
}

void dfsSolve(vector<state>& attempt, vector<state>& shortest, int depth)
{ //           
  assert(depth > 0);

  const int CURRENT = attempt.size();
  const int BEST    = shortest.size();

  if      (BEST > 0 && CURRENT >= BEST) return;
  else if (CURRENT > depth + 1) return;

  state curr = attempt[attempt.size() - 1];

  if( legalStep(curr, LEFT) )
    dfsTries(attempt, shortest, depth, LEFT);

  curr = attempt[attempt.size() - 1];

  if( legalStep(curr, RIGHT) )
    dfsTries(attempt, shortest, depth, RIGHT);

  curr = attempt[attempt.size() - 1];

  if( legalStep(curr, UP) )
    dfsTries(attempt, shortest, depth, UP);

  curr = attempt[attempt.size() - 1];

  if( legalStep(curr, DOWN) )
    dfsTries(attempt, shortest, depth, DOWN);

}

void dfsSolveCATCH(vector<state>& attempt, vector<state>& shortest, int depth)
{
  dfsSolve(attempt, shortest, depth);
  cout << endl << endl;
  cout << "There are not more options to investigate. "
       << "Here is the last solution we found:" << endl;
  dump_attempt(shortest);
}
/*
              
              
                  
               
                                     
  */

void welcome_screen(cell game[GAME_HEIGHT][GAME_WIDTH],string puzzleNumber)
{
  //             
  assert(true);
  //              
  //                                                                                   
  cout << "Welcome to Sokuban solver" << endl << endl;
  if(!getChallange(puzzleNumber,game))
  {
    cout << "An error occurred (1)" << endl;
    return;
  }

  displayGame(game);
  cout << endl;
}

void options_screen(cell game[GAME_HEIGHT][GAME_WIDTH],string input)
{
  //             
  assert(true);
  //              
  //                                                                                                           
  cout<< "press any key to open options"<<endl;
  while(getline(cin, input))
  {
    if(input == "bfs")
      bfsSolve(game);
    if(input == "dfs")
    {
      cout << "Give an integervalue for the depth-bound $  ";
      int depth = 0;
      cin >> depth;

      state initial = {-1, -1, findTheGuy(game)};
      copyGame(game, initial.game);
      vector<state> states;
      states.push_back(initial);

      vector<state> shortest;

      dfsSolveCATCH(states, shortest, depth);
    }
    if(input == "--exit")
      return;
    cout << "Enter bfs, dfs or --exit to continue $ ";
  }
}

int main()
{
  string input="";
  cell game[GAME_HEIGHT][GAME_WIDTH];
  welcome_screen(game,"24");
  options_screen(game,input);
}

//          

