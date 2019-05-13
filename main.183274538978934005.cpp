//                                   
//                                   

#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>
#include <ctime>

using namespace std;

//               

enum content { Empty, Wall, Waiter, Box };
enum Move { Up=0, Left, Down, Right };
struct Cell {
	bool IsDest;
	content Content;
};
struct Candidate {
	vector<vector<Cell>> Board;
	int parent_index;
};
bool operator== (const Candidate& c1, const Candidate& c2) {
	for (int i = 0; i < c1.Board.size(); i++) {
		for (int j = 0; j < c1.Board[i].size(); j++) {
			if (c1.Board[i][j].Content != c2.Board[i][j].Content) return false;
		}
	}
	return true;
}
 Cell char_to_cell(char c) {
	 assert(c == '*' || c == ' ' || c == '.' || c == 'w' || c == 'W' || c == 'b' || c == 'B' );
	 //              
	 //                                            
	Cell tempc;
	switch (c) {
	case '*':
		tempc.IsDest = false;
		tempc.Content = Wall;
		break;
	case ' ':
		tempc.IsDest = false;
		tempc.Content = Empty;
		break;
	case '.':
		tempc.IsDest = true;
		tempc.Content = Empty;
		break;
	case 'w':
		tempc.IsDest = false;
		tempc.Content = Waiter;
		break;
	case 'W':
		tempc.IsDest = true;
		tempc.Content = Waiter;
		break;
	case 'b':
		tempc.IsDest = false;
		tempc.Content = Box;
		break;
	case 'B':
		tempc.IsDest = true;
		tempc.Content = Box;
		break;
	}
	return tempc;
}
void ReadBoard(vector<vector<Cell>>& Board, string filename,bool& succes) {
	//            
	assert(filename != "");
	//              
	//                                                                       
	ifstream inpfile;
	char c;
	inpfile.open(filename);
	if (inpfile.is_open()) {
		succes = true;
		vector<Cell> currentline;
		while (inpfile.get(c)) {
			if (c != '\n') {
				currentline.push_back(char_to_cell(c));
			}
			else {
				Board.push_back(currentline);
				currentline.clear();
			}
			
		}
	}
	else {
		succes = false;
		cout << "File does not exist" << endl;
	}
}
void get_waiter_position(vector<vector<Cell>>& Board, int& row, int& column) {
	//             
	assert(Board.size() > 0);
	//              
	//                                                                               
	for (int i = 0; i < Board.size(); i++) {
		for (int j = 0; j < Board[i].size(); j++) {
			if (Board[i][j].Content == Waiter) {
				row = i;
				column = j;
				return;
			}
		}
	}
}
bool can_go_up(vector<vector<Cell>>& Board,int row,int column) {
	//            
	assert(Board.size() > 2 && row > 0 && column > 0);
	//              
	//                                                                        
	if (Board[row - 1][column].Content != Empty) {
		if (Board[row - 1][column].Content == Box && Board[row - 2][column].Content == Empty) {
			return true;
		}
		return false;
	}return true;
}
bool can_go_down(vector<vector<Cell>>& Board, int row, int column) {
	//            
	assert(Board.size() > 2 && row > 0 && column > 0);
	//              
	//                                                                            
	if (Board[row + 1][column].Content != Empty) {
		if (Board[row + 1][column].Content == Box && Board[row + 2][column].Content == Empty) {
			return true;
		}
		return false;
	}return true;
}
bool can_go_right(vector<vector<Cell>>& Board,int row, int column) {
	//            
	assert(Board.size() > 2 && row > 0 && column > 0);
	//              
	//                                                                              
	if (Board[row][column + 1].Content != Empty) {
		if (Board[row][column + 1].Content == Box && Board[row][column + 2].Content == Empty) {
			return true;
		}
		return false;
	}return true;
}
bool can_go_left(vector<vector<Cell>>& Board, int row, int column) {
	//            
	assert(Board.size() > 2 && row > 0 && column > 0);
	//              
	//                                                                            
	if (Board[row][column - 1].Content != Empty) {
		if (Board[row][column - 1].Content == Box && Board[row][column - 2].Content == Empty) {
			return true;
		}
		return false;
	}return true;
}
void print_board(vector<vector<Cell>> Board) {
	//            
	assert(Board.size() > 0);
	//              
	//                    
	int width = Board[0].size();
	int length = Board.size();

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (!Board[i][j].IsDest) {
				if (Board[i][j].Content == Empty)
					cout << ' ';
				if (Board[i][j].Content == Wall)
					cout << '*';
				if (Board[i][j].Content == Waiter)
					cout << 'w';
				if (Board[i][j].Content == Box)
					cout << 'b';
			}
			else {
				if (Board[i][j].Content == Empty)
					cout << '.';
				if (Board[i][j].Content == Waiter)
					cout << 'W';
				if (Board[i][j].Content == Box)
					cout << 'B';
			}
		}
		cout << '\n';
	}
}
bool board_ready(vector<vector<Cell>> Board) {
	//            
	assert(Board.size() >0);
	//              
	//                                           
	for (int i = 0; i < Board.size(); i++) {
		for (int j = 0; j < Board[i].size(); j++) {
			if (Board[i][j].Content == Box) {
				if (!Board[i][j].IsDest) {
					return false;
				}
			}

		}
	}
	return true;
}
void go_left(vector<vector<Cell>>& Board, int row, int column) {
	//           
	assert(can_go_left(Board, row, column));
	//             
	//                                                 

	//                                  
	if (Board[row][column - 1].Content == Box) {
		Board[row][column - 2].Content = Box;
		Board[row][column - 1].Content = Waiter;
		Board[row][column].Content = Empty;
	}//                        
	else {
		Board[row][column - 1].Content = Waiter;
		Board[row][column].Content = Empty;
	}

}
void go_right(vector<vector<Cell>>& Board, int row, int column) {
	//           
	assert(can_go_right(Board, row, column));
	//             
	//                                                  

	//                                   
	if (Board[row][column + 1].Content == Box) {
		Board[row][column + 2].Content = Box;
		Board[row][column + 1].Content = Waiter;
		Board[row][column].Content = Empty;
	}//                         
	else {
		Board[row][column + 1].Content = Waiter;
		Board[row][column].Content = Empty;
	}
}
void go_up(vector<vector<Cell>>& Board, int row, int column) {
	//           
	assert(can_go_up(Board, row, column));
	//             
	//                                               
	

	//                                    
	if (Board[row - 1][column].Content == Box) {
		Board[row - 2][column].Content = Box;
		Board[row - 1][column].Content = Waiter;
		Board[row][column].Content = Empty;
	}//                          
	else {
		Board[row - 1][column].Content = Waiter;
		Board[row][column].Content = Empty;
	}
}
void go_down(vector<vector<Cell>>& Board,int row, int column) {
	//           
	assert(can_go_down(Board,row,column));
	//             
	//                                                 

	//                                   
	if (Board[row + 1][column].Content == Box) {
		Board[row + 2][column].Content = Box;
		Board[row + 1][column].Content = Waiter;
		Board[row][column].Content = Empty;
	}//                         
	else {
		Board[row + 1][column].Content = Waiter;
		Board[row][column].Content = Empty;
	}
}
void move(Move m, vector<vector<Cell>>& Board, int row, int column) {
	//            
	assert(row > 0 && column > 0 && Board.size() > 0);
	//             
	//                                                               
	switch (m) {
	case(Up): go_up(Board,row,column); break;
	case(Down): go_down(Board,row,column); break;
	case(Left): go_left(Board,row,column); break;
	case(Right): go_right(Board,row,column); break;
	}
}
bool candidate_present(vector<Candidate>& queue, Candidate cand) {
	//             
	assert(queue.size() > 0);
	//              
	//                                   
	for (int i = 0; i < queue.size(); i++) {
		if (cand == queue[i])return true;
	}
	return false;
}
bool box_in_corner(vector<vector<Cell>>& Board) {
	//            
	assert(Board.size() > 0);
	//             
	//                                   
	for (int i = 0; i < Board.size(); i++) {
		for (int j = 0; j < Board[i].size(); j++) {
			if (Board[i][j].Content == Box && !Board[i][j].IsDest) {
				if (Board[i][j + 1].Content == Wall && Board[i + 1][j].Content == Wall ||
					Board[i][j + 1].Content == Wall && Board[i - 1][j].Content == Wall ||
					Board[i][j - 1].Content == Wall && Board[i + 1][j].Content == Wall ||
					Board[i][j - 1].Content == Wall && Board[i - 1][j].Content == Wall)
					return true;
			}
		}
	}
	return false;
}
void tries(vector<Candidate>& queue, int i, Move m,int row, int column) {
	//            
	assert(queue.size() > 0 && i >= 0 && row > 0 && column > 0);
	//             
	//                                           

	vector<vector<Cell>> p = queue[i].Board;
	vector<vector<Cell>> newp = p;
	move(m, newp, row, column);
	Candidate newc = { newp,i };
	//                                                         
	if (!candidate_present(queue, newc)) {
		//                                                                                           
		if (!box_in_corner(newp)) {
			queue.push_back(newc);
		}
	}
}

int step = 0;
void show_path(vector<Candidate>& queue, int i) {
	//            
	assert(i >= 0 && queue.size() >= 0);
	//             
	//                                                                         

	//                                                    
	//                                         

	if (i != 0) {
		show_path(queue, queue[i].parent_index);
	}
	cout << "Step: " << step << endl;
	step++;
	print_board(queue[i].Board);
}
void breadth_solve(vector<vector<Cell>> Startboard) {
	//            
	assert(Startboard.size() > 0);
	//              
	//                                                                      
	vector<Candidate> queue = { { Startboard,-1 } };
	int i = 0;
	int row, column;
	while (i < queue.size() && !board_ready(queue[i].Board)) {
		vector<vector<Cell>> p = queue[i].Board;
		get_waiter_position(p, row, column);
		if (can_go_up(p,row,column)) tries(queue, i, Up,row,column);
		if (can_go_down(p, row, column)) tries(queue, i, Down, row, column);
		if (can_go_left(p, row, column)) tries(queue, i, Left, row, column);
		if (can_go_right(p, row, column)) tries(queue, i, Right, row, column);
		i++;
	}
	if (i < queue.size()) {
		cout << "We are done..." << endl;
		cout << "proof that we are done: " << endl;
		print_board(queue[i].Board);
		cout << "\n\n" << endl;
		cout << "the steps:  " << endl;
		show_path(queue, i);
	}
	else {
		cout << "No solution was found..." << endl;
	}
}
void depth_tries(vector<Candidate>& Attempt, vector<Candidate>& Best, Move m, int row, int column, int max_depth);
void depth_solve(vector<Candidate>& Attempt, vector<Candidate>& Best,int max_depth) {
	//            
	assert(Attempt.size() >= 0 && Best.size() >= 0 && max_depth > 0);
	//             
	//                                                                                 
	const int CURRENT = Attempt.size();
	const int BEST = Best.size();
	vector<vector<Cell>> p = Attempt[(CURRENT - 1)].Board;
	if (BEST > 0 && CURRENT >= BEST) {
		return;
	}
	else if (CURRENT > max_depth + 1) {
		return;
	}
	else if (board_ready(p)) {
		Best = Attempt;
		cout << "I found a solution at depth " << Best.size()-1 << '\n';
		//                        
		return;
	}
	int row, column;
	get_waiter_position(p, row, column);
	//               
	if (can_go_up(p,row,column)) depth_tries(Attempt,Best,Up,row,column,max_depth);
	if (can_go_down(p,row,column)) depth_tries(Attempt, Best, Down, row, column, max_depth);
	if (can_go_left(p, row, column)) depth_tries(Attempt, Best, Left, row, column, max_depth);
	if (can_go_right(p, row, column)) depth_tries(Attempt, Best, Right, row, column, max_depth);

}
void depth_tries(vector<Candidate>& Attempt, vector<Candidate>& Best, Move m, int row, int column, int max_depth) {
	//            
	assert(Attempt.size() >= 0, Best.size() >= 0 && row > 0 && column > 0 && max_depth >= 0);
	//              
	//                                                        
	vector<vector<Cell>> p = Attempt[(Attempt.size() - 1)].Board;
	vector<vector<Cell>> newp = p;
	move(m, newp, row, column);
	Candidate newat = { newp,-1 };
	if (!candidate_present(Attempt, newat) && !box_in_corner(newp)) {
		Attempt.push_back(newat);
		depth_solve(Attempt, Best, max_depth);
		Attempt.pop_back();
	}
	if (Attempt.size() == 0) {
		cout << "We are done" << endl;
	}
}
void print_solution(vector<Candidate> solution) {
	//            
	assert(solution.size() >= 0);
	//              
	//                     
	for (int i = 0; i < solution.size(); i++) {
		print_board(solution[i].Board);
		cout << "\n";
	}
	if (solution.size() == 0) {
		cout << "We have not found a solution" << endl;
	}
}
int main(int argc, char* argv[]) {

	std::clock_t start;
	double duration;

	string filename = "challenge.31.txt";
	vector<vector<Cell>> Board;
	vector<Candidate> Best;
	bool read_succes = false;

	int max_depth = 35;
	cout << "Enter a filename ( include the .txt )" << endl;
	cin >> filename;

	ReadBoard(Board, filename, read_succes);
	if (read_succes) {
		vector<Candidate> Attempt = { { Board,-1 } };
		cout << "Would you like depth first search (0) or breadth first search (1)" << endl;
		int input;
		cin >> input;
		if (input == 1) {
			cout << "Computing BFS solution, be patient..." << endl;
			start = clock();
			breadth_solve(Board);
		}
		else {
			cout << "Computing DFS solution, be patient..." << endl;
			start = clock();
			depth_solve(Attempt, Best, max_depth);
			print_solution(Best);
		}
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		cout << "It took me " << duration << " seconds." << '\n';
	}

	//                                                                
	int x;
	cin >> x;
	return 0;
}

