/*                                                                    
                                                                      
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std ;

enum Cell {wall=0, empty, empty_dest, worker, worker_dest, box, box_dest};

struct Puzzle {
  vector<Cell> board ;
  int pos ;
} ;

struct Candidate {
  Puzzle candidate ;
  int parent_candidate ;
} ;

vector<Cell> puzzle = {wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,
                         wall,empty,empty,empty,empty,empty,empty,empty,empty,wall,
                         wall,empty,empty_dest,box,worker,empty,empty,empty,empty,wall,
                         wall,empty,empty,wall,wall,wall,wall,empty,empty,wall,
                         wall,empty,empty,empty,empty,empty,empty,empty,empty,wall,
                         wall,wall,wall,wall,wall,wall,wall,wall,wall,wall};

void show_puzzle (Puzzle p) {
//               
//                
/*                
                           
*/
for (int i = 0; i < puzzle.size(); i++) {
  if (i % 10 == 0 && i > 0)
    cout << '\n';

  if (p.board[i] == wall)
    cout << "*";
  else if (p.board[i] == empty)
    cout << " ";
  else if (p.board[i] == empty_dest)
    cout << ".";
  else if (p.board[i] == worker)
    cout << "w";
  else if (p.board[i] == worker_dest)
    cout << "W";
  else if (p.board[i] == box)
    cout << "b";
  else if (p.board[i] == box_dest)
    cout << "B";
 }
 cout << '\n';
}

bool puzzle_ready (Puzzle p) {
  for(int i = 0; i < p.board.size(); i++){
    if(p.board[i] == box)
      return false;
  }
  return true;
}

bool puzzle_present (vector<Candidate>& c, int i, Puzzle p){
  for(int i = 0; i < c.size(); i++){
    if(c[i].candidate.board == p.board)
      return true;
  }
}

Puzzle move_empty (Puzzle p, int next) {
  Puzzle help1 ;
  help1.board = p.board ;
  if(p.pos == next+1 || p.pos+1 == next || p.pos+10 == next || p.pos == next+10){
    help1.board[next] = help1.board[p.pos] ;
    help1.board[p.pos] = p.board[next] ;
    help1.pos = next ;
  }
  else if(p.pos == next+2 || p.pos+2 == next || p.pos+20 == next || p.pos == next+20){
    help1.board[p.pos+(next/2)] = p.board[p.pos] ;
    help1.board[p.pos+next] = p.board[p.pos+(next/2)] ;
    help1.board[p.pos] = p.board[p.pos+next] ;
    help1.pos = (next/2) ;
  }
  return help1 ;
}

void show_path (vector<Candidate>& c, int i){
  show_puzzle(c[i].candidate) ;
  cout << c[i].parent_candidate << endl;

}

int north (Puzzle p) {
  int hnorth ;
  for(int i = 0; i < p.board.size(); i++){
    if(p.board[i] == worker || p.board[i] == worker_dest){
      hnorth = i-10 ;
    }
  }
  return hnorth ;
}

bool can_go_north (Puzzle p) {
  if(p.board[p.pos-10] == wall)
    return false ;
  else if(p.board[p.pos-10] == box){
    if(p.board[p.pos-20] == empty)
      return true;
    else
      return false;
  }
  else if(p.board[p.pos-10] == empty)
    return true;
}

int south (Puzzle p) {
  int hsouth ;
  for(int i = 0; i < p.board.size(); i++){
    if(p.board[i] == worker || p.board[i] == worker_dest){
      hsouth = i+10 ;
    }
  }
  return hsouth ;
}

bool can_go_south (Puzzle p) {
  if(p.board[p.pos+10] == wall)
    return false ;
  else if(p.board[p.pos+10] == box){
    if(p.board[p.pos+20] == empty)
      return true;
    else
      return false;
  }
  else if(p.board[p.pos+10] == empty)
    return true;
}

int west (Puzzle p) {
  int hwest ;
  for(int i = 0; i < p.board.size(); i++){
    if(p.board[i] == worker || p.board[i] == worker_dest){
      hwest = i+1 ;
    }
  }
  return hwest ;
}

bool can_go_west (Puzzle p) {
  if(p.board[p.pos-1] == wall)
    return false ;
  else if(p.board[p.pos-1] == box){
    if(p.board[p.pos-2] == empty)
      return true;
    else
      return false;
  }
  else if(p.board[p.pos-1] == empty)
    return true;
}

int east (Puzzle p) {
  int heast ;
  for(int i = 0; i < p.board.size(); i++){
    if(p.board[i] == worker || p.board[i] == worker_dest){
      heast = i-1 ;
    }
  }
  return heast ;
}

bool can_go_east (Puzzle p) {
  if(p.board[p.pos+1] == wall)
    return false ;
  else if(p.board[p.pos+1] == box){
    if(p.board[p.pos+2] == empty)
      return true;
    else
      return false;
  }
  else if(p.board[p.pos+1] == empty)
    return true;
}

void tries (vector<Candidate>& c, int i, int next) {
  Puzzle p = c[i].candidate ;
  Puzzle newp = move_empty (p, next) ;
  Candidate newc = {newp, i} ;
  if(!puzzle_present (c, i, newp))
    c.push_back (newc) ;
}

void solve (Puzzle start) {
  vector<Candidate> c = {{start, -1}} ;
  int i = 0 ;
  while (i < c.size() && !puzzle_ready (c[i].candidate)){
    Puzzle p = c[i].candidate ;
    if (can_go_north(p)) tries(c, i, north(p)) ;
    if (can_go_south(p)) tries(c, i, south(p)) ;
    if (can_go_west(p)) tries(c, i, west(p)) ;
    if (can_go_east(p)) tries(c, i, east(p)) ;
    i++;
  }
  if (i < c.size()) show_path (c, i) ;
}

int main () {
    int worker;
    worker = 23;
    Puzzle p {puzzle, worker};
    solve(p);
    return 0 ;
}

