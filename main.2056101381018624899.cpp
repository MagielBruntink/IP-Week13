#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*                                                                   
                 
                                 
                              
                                                                   */

enum Cell { WALL, EMPTY, DEST, WORKER, WORKER_ON_DEST, BOX, BOX_ON_DEST };

typedef vector<vector<Cell>> Board;
void depthFirst(vector<Board> &attempt, vector<Board> &best, int maxDepth);

struct pos {
  int x;
  int y;
};

struct Candidate {
  Board candidate;
  int parentCandidate;
};

int boardWidth(Board board) { return static_cast<int>(board.size()); }
int boardHeight(Board board) { return static_cast<int>(board[0].size()); }
int size(vector<Board> boards) { return static_cast<int>(boards.size()); }
int size(vector<Candidate> candidates) {
  return static_cast<int>(candidates.size());
}

char cellToChar(Cell cell) {
  assert(true);
  //                                              
  switch (cell) {
  case WALL:
    return '*';
  case EMPTY:
    return ' ';
  case DEST:
    return '.';
  case WORKER:
    return 'w';
  case WORKER_ON_DEST:
    return 'W';
  case BOX:
    return 'b';
  case BOX_ON_DEST:
    return 'B';
  }
  return '?';
}

ostream &operator<<(ostream &out, Board &board) {
  //                                
  assert(true);

  for (int y = 0; y < boardHeight(board); y++) {
    for (int x = 0; x < boardWidth(board); x++) {
      cout << cellToChar(board[x][y]) << " ";
    }
    out << endl;
  }

  return out;
}

Cell toCell(char c) {
  assert(true);
  switch (c) {
  case '*':
    return WALL;
  case ' ':
    return EMPTY;
  case '.':
    return DEST;
  case 'w':
    return WORKER;
  case 'W':
    return WORKER_ON_DEST;
  case 'b':
    return BOX;
  case 'B':
    return BOX_ON_DEST;
  default:
    cout << "error" << endl;
    return WALL;
  }
}

Board readBoardFromFile(string fileName) {
  assert(true);
  //                                                                        

  ifstream input_file;
  input_file.open(fileName);
  Board board;
  board.push_back({});
  int y = 0;
  int x = 0;
  while (input_file) {
    char c;
    input_file.get(c);
    if (c == '\n') {
      y++;
      x = 0;
    } else {
      if (x >= boardWidth(board)) {
        board.push_back({});
      }
      if (y >= static_cast<int>(board[x].size())) {
        board[x].push_back(EMPTY);
      }
      board[x][y] = toCell(c);
      x++;
    }
  }
  return board;
}

pos getWorkerPos(Board b) {
  assert(true);
  //                                                                           
  //        

  for (int x = 1; x < boardWidth(b) - 1; x++) {
    for (int y = 1; y < boardHeight(b) - 1; y++) {
      if (b[x][y] == WORKER || b[x][y] == WORKER_ON_DEST) {
        return {x, y};
      }
    }
  }
  return {-1, -1};
}

bool solved(Board b) {
  assert(boardWidth(b) > 0);
  //                                                             

  for (int x = 1; x < boardWidth(b) - 1; x++) {
    for (int y = 1; y < boardHeight(b) - 1; y++) {
      if (b[x][y] == BOX) {
        return false;
      }
    }
  }
  return true;
}

bool canMoveTo(Board b, int dir) { //                                      
  assert(dir <= 3 && dir >= 0);
  //                                                                            
  //                                                                            
  //      

  pos worker = getWorkerPos(b);
  int x = worker.x;
  int y = worker.y;
  switch (dir) {
  case 0:
    if (b[x][y - 1] == EMPTY || b[x][y - 1] == DEST ||
        (b[x][y - 1] == BOX && (b[x][y - 2] == EMPTY || b[x][y - 2] == DEST))) {
      return true;
    }
    break;
  case 1:
    if (b[x + 1][y] == EMPTY || b[x + 1][y] == DEST ||
        (b[x + 1][y] == BOX && (b[x + 2][y] == EMPTY || b[x + 2][y] == DEST))) {
      return true;
    }
    break;
  case 2:
    if (b[x][y + 1] == EMPTY || b[x][y + 1] == DEST ||
        (b[x][y + 1] == BOX && (b[x][y + 2] == EMPTY || b[x][y + 2] == DEST))) {
      return true;
    }
    break;
  case 3:
    if (b[x - 1][y] == EMPTY || b[x - 1][y] == DEST ||
        (b[x - 1][y] == BOX && (b[x - 2][y] == EMPTY || b[x - 2][y] == DEST))) {
      return true;
    }
    break;
  }
  return false;
}

int calcDir(pos oldp, pos newp) {
  assert(oldp.x >= 0 && oldp.y >= 0 && newp.x >= 0 && newp.y >= 0);
  //                                                                           
  //                                           

  if (newp.y - oldp.y < 0) {
    return 0;
  }
  if (newp.x - oldp.x > 0) {
    return 1;
  }
  if (newp.y - oldp.y > 0) {
    return 2;
  }
  if (newp.x - oldp.x < 0) {
    return 3;
  }
  return -1;
}

//                                                        
Board moveWorker(Board b, pos oldp, pos newp) {
  assert(true);
  //                                                                            
  //                                                                  
  //            

  int dir = calcDir(oldp, newp);
  //                                                                    

  if (b[oldp.x][oldp.y] == WORKER) {
    b[oldp.x][oldp.y] = EMPTY;
  } else if (b[oldp.x][oldp.y] == WORKER_ON_DEST) {
    b[oldp.x][oldp.y] = DEST;
  }

  if (b[newp.x][newp.y] == EMPTY) {
    b[newp.x][newp.y] = WORKER;
  } else if (b[newp.x][newp.y] == DEST) {
    b[newp.x][newp.y] = WORKER_ON_DEST;
  } else if (b[newp.x][newp.y] == BOX || b[newp.x][newp.y] == BOX_ON_DEST) {
    if (b[newp.x][newp.y] == BOX) {
      b[newp.x][newp.y] = WORKER;
    } else {
      b[newp.x][newp.y] = WORKER_ON_DEST;
    }

    switch (dir) {
    case 0:
      if (b[newp.x][newp.y - 1] == EMPTY) {
        b[newp.x][newp.y - 1] = BOX;
      } else {
        b[newp.x][newp.y - 1] = BOX_ON_DEST;
      }
      break;
    case 1:
      if (b[newp.x + 1][newp.y] == EMPTY) {
        b[newp.x + 1][newp.y] = BOX;
      } else {
        b[newp.x + 1][newp.y] = BOX_ON_DEST;
      }
      break;
    case 2:
      if (b[newp.x][newp.y + 1] == EMPTY) {
        b[newp.x][newp.y + 1] = BOX;
      } else {
        b[newp.x][newp.y + 1] = BOX_ON_DEST;
      }
      break;
    case 3:
      if (b[newp.x - 1][newp.y] == EMPTY) {
        b[newp.x - 1][newp.y] = BOX;
      } else {
        b[newp.x - 1][newp.y] = BOX_ON_DEST;
      }
      break;
    }
  }

  return b;
}

bool present(Board b, vector<Board> &checkedBoards) {
  assert(true);
  //                                                    

  for (int i = 0; i < size(checkedBoards); i++) {
    if (b == checkedBoards[i]) {
      return true;
    }
  }
  return false;
}

void tries(vector<Board> &attempt, pos current, pos next, vector<Board> &best,
           int maxDepth) {
  assert(maxDepth > 0);
  //                                                            

  Board b = attempt[size(attempt) - 1];
  Board newBoard = moveWorker(b, current, next);

  if (!present(newBoard, attempt)) {
    attempt.push_back(newBoard);
    depthFirst(attempt, best, maxDepth);
    attempt.pop_back();
  }
}

void depthFirst(vector<Board> &attempt, vector<Board> &best, int maxDepth) {
  assert(size(attempt) > 0 && maxDepth >= 0);
  //                                                                      
  //                                                                           

  const int CURRENT = size(attempt);
  const int BEST = size(best);
  Board b = attempt[CURRENT - 1];

  if (BEST > 0 && CURRENT >= BEST) {
    return;
  } else if (CURRENT > maxDepth + 1) {
    return;
  } else if (solved(b)) {
    best = attempt;
    return;
  }

  pos currentPos = getWorkerPos(b);

  if (canMoveTo(b, 0)) {
    //                             
    tries(attempt, currentPos, {currentPos.x, currentPos.y - 1}, best,
          maxDepth);
  }
  if (canMoveTo(b, 1)) {
    //                            
    tries(attempt, currentPos, {currentPos.x + 1, currentPos.y}, best,
          maxDepth);
  }
  if (canMoveTo(b, 2)) {
    //                             
    tries(attempt, currentPos, {currentPos.x, currentPos.y + 1}, best,
          maxDepth);
  }
  if (canMoveTo(b, 3)) {
    //                            
    tries(attempt, currentPos, {currentPos.x - 1, currentPos.y}, best,
          maxDepth);
  }
}

int printPath(vector<Candidate> stack, int index) {
  assert(size(stack) > index);
  //                                       

  if (index == -1) {
    return 1;
  }
  int i = printPath(stack, stack[index].parentCandidate);
  cout << stack[index].candidate << endl;
  return i + 1;
}

void breadthFirst(Board initialBoard) {
  assert(boardWidth(initialBoard) > 1);
  //                                                          
  //                                                          

  vector<Candidate> stack = {{initialBoard, -1}};
  int currentAttempt = 0;
  while (currentAttempt < size(stack) &&
         !solved(stack[currentAttempt].candidate)) {
    Board b = stack[currentAttempt].candidate;
    pos currentPos = getWorkerPos(b);

    if (canMoveTo(b, 0)) {
      stack.push_back(
          {moveWorker(b, currentPos, {currentPos.x, currentPos.y - 1}),
           currentAttempt});
    }
    if (canMoveTo(b, 1)) {
      stack.push_back(
          {moveWorker(b, currentPos, {currentPos.x + 1, currentPos.y}),
           currentAttempt});
    }
    if (canMoveTo(b, 2)) {
      stack.push_back(
          {moveWorker(b, currentPos, {currentPos.x, currentPos.y + 1}),
           currentAttempt});
    }
    if (canMoveTo(b, 3)) {
      stack.push_back(
          {moveWorker(b, currentPos, {currentPos.x - 1, currentPos.y}),
           currentAttempt});
    }
    currentAttempt++;
  }
  if (currentAttempt < size(stack)) {
    cout << "The best BFS solution path is:" << endl;
    cout << "BFS: The least amount of steps is: "
         << printPath(stack, currentAttempt) << endl;
  }
}

int main(int argc, char const *argv[]) {
  Board board = readBoardFromFile("challenge.1.a.txt");
  cout << "Initial position:" << endl;
  cout << board << endl;

  cout << "Executing Breadth-First Search..." << endl;
  breadthFirst(board);

  cout << "Executing Depth-First Search..." << endl;
  vector<Board> attempt;
  attempt.push_back(board);
  vector<Board> best;
  depthFirst(attempt, best, 5);
  cout << "DFS: The least amount of steps is: " << size(best) - 1 << endl;
  for (int i = 0; i < size(best); i++) {
    cout << best[i] << endl;
  }
  while (true) {
    cout << "Program exit" << endl;
    string test;
    cin >> test;
  }
  return 0;
}

