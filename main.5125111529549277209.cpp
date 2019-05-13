#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                          
//                            
//                          

typedef char Cell;

struct Pos {
	int col, row;
};

struct Puzzle {
	vector<vector<Cell>> board;
};

struct Candidate {
	Puzzle candidate;
	int parent_candidate;
};

void print(Puzzle p)
{
	//             
	assert(true);
	//               
	//                                  
	for(vector<Cell> v : p.board)
	{
		for(Cell c : v)
		{
			cout << c;
		}
		cout << endl;
	}
}

bool open_file(ifstream& file)
{
	//             
	assert(true);
	//             
	//                                                                                            
	//                                                 

	while(!file.is_open())
	{
		cout << "Please enter the name of the file the puzzle is in, or enter 'stop' to terminate the program." << endl;
		string filename;
		cin >> filename;

		if(filename == "stop") return true;

		file.open(filename);

		if(!file.is_open())
		{
			cout << "Invalid file." << endl;
		}
	}
	cout << "File opened!" << endl;
	return false;
}

void load_puzzle(ifstream& file, Puzzle& puzzle)
{
	//             
	assert(file.is_open());
	//             
	//                                                             
	while(file)
	{
		string chars;
		getline(file, chars, '\n');

		if(chars.length() == 0) return;

		int length = chars.length();

		vector<Cell> char_vector;

		for(int i = 0; i < length; i++)
		{
			char c = chars[i];
			char_vector.push_back(c);
		}

		puzzle.board.push_back(char_vector);
	}
}

bool puzzle_ready(Puzzle p)
{
	//             
	assert(true);
	//             
	//                                                                      
	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell c = p.board[i][j];
			if(c == 'b') return false;
		}
	}
	return true;
}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle p)
{
	//             
	assert(i >= 0);
	//             
	//                                                                                    
	for(Candidate can : c)
	{
		bool same = true;
		Puzzle in = can.candidate;
		int size = p.board.size();
		for(int i = 0; i < size; i++)
		{
			int size2 = p.board[i].size();
			for(int j = 0; j < size2; j++)
			{
				if(p.board[i][j] != in.board[i][j]) same = false;
			}
		}
		if(same) return true;
	}
	return false;
}

bool puzzle_present(Puzzle p, vector<Puzzle>& c)
{
	//             
	assert(true);
	//             
	//                                                       
	for(Puzzle in : c)
		{
			bool same = true;
			int size = p.board.size();
			for(int i = 0; i < size; i++)
			{
				int size2 = p.board[i].size();
				for(int j = 0; j < size2; j++)
				{
					if(p.board[i][j] != in.board[i][j]) same = false;
				}
			}
			if(same) return true;
		}
		return false;
}

Puzzle move_worker(Puzzle p, Pos next)
{
	//             
	assert(true);
	//             
	//                                                                       
	//                                               

	//                                                                                              

	Puzzle new_p = p;

	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell wPos = p.board[i][j];
			Cell bPos = p.board[next.col][next.row];
			if(wPos == 'w')
			{
				new_p.board[i][j] = ' ';
				if(bPos == 'b')
				{
					new_p.board[next.col][next.row] = 'w';

					Cell bToPos = p.board[2 * next.col - i][2 * next.row - j];
					if(bToPos == ' ')
					{
						new_p.board[2 * next.col - i][2 * next.row - j] = 'b';
					}
					else if(bToPos == '.')
					{
						new_p.board[2 * next.col - i][2 * next.row - j] = 'B';
					}
				}
				else if(bPos == 'B')
				{
					new_p.board[next.col][next.row] = 'W';

					Cell bToPos = p.board[2 * next.col - i][2 * next.row - j];
					if(bToPos == ' ')
					{
						new_p.board[2 * next.col - i][2 * next.row - j] = 'b';
					}
					else if(bToPos == '.')
					{
						new_p.board[2 * next.col - i][2 * next.row - j] = 'B';
					}
				}
				else if(bPos == ' ')
				{
					new_p.board[next.col][next.row] = 'w';
				}
				else if(bPos == '.')
				{
					new_p.board[next.col][next.row] = 'W';
				}
			}
			else if(wPos == 'W')
			{
				new_p.board[i][j] = '.';
				if(bPos == 'b')
				{
					new_p.board[next.col][next.row] = 'w';

					Cell bToPos = p.board[2 * next.col - i][2 * next.row - j];
					if(bToPos == ' ')
					{
						new_p.board[2 * next.col - i][2 * next.row - j] = 'b';
					}
					else if(bToPos == '.')
					{
						new_p.board[2 * next.col - i][2 * next.row - j] = 'B';
					}
				}
				else if(bPos == 'B')
				{
					new_p.board[next.col][next.row] = 'W';

					Cell bToPos = p.board[2 * next.col - i][2 * next.row - j];
					if(bToPos == ' ')
					{
						new_p.board[2 * next.col - i][2 * next.row - j] = 'b';
					}
					else if(bToPos == '.')
					{
						new_p.board[2 * next.col - i][2 * next.row - j] = 'B';
					}
				}
				else if(bPos == ' ')
				{
					new_p.board[next.col][next.row] = 'w';
				}
				else if(bPos == '.')
				{
					new_p.board[next.col][next.row] = 'W';
				}
			}
		}
	}
	return new_p;
}

void show_path(vector<Candidate>& c, int i)
{
	//             
	assert(i >= 0 && i < c.size());
	//             
	//                                
	while(i >= 0)
	{
		Candidate can = c[i];
		print(can.candidate);
		cout << endl;
		i = can.parent_candidate;
	}
}

bool can_go_north(Puzzle p)
{
	//             
	assert(true);
	//             
	//                                            
	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell c = p.board[i][j];
			if((c == 'w' || c == 'W') && i > 0)
			{
				Cell to = p.board[i-1][j];
				if(to == ' ' || to == '.') return true;
				else if((to == 'b' || to == 'B') && i > 1)
				{
					Cell box_to = p.board[i - 2][j];
					if(box_to == ' ' || box_to == '.') return true;
					else return false;
				}
			}
		}
	}
	return false;
}

Pos north(Puzzle p)
{
	//             
	assert(true);
	//             
	//                                                          
	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell c = p.board[i][j];
			if(c == 'w' || c == 'W') return {i - 1, j};
		}
	}
	return {-1, -1};
}

bool can_go_east(Puzzle p)
{
	//             
	assert(true);
	//             
	//                                        
	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell c = p.board[i][j];
			if((c == 'w' || c == 'W') && j < size2 - 1)
			{
				Cell to = p.board[i][j + 1];
				if(to == ' ' || to == '.') return true;
				else if((to == 'b' || to == 'B') && j < size2 - 2)
				{
					Cell box_to = p.board[i][j + 2];
					if(box_to == ' ' || box_to == '.') return true;
					else return false;
				}
			}
		}
	}
	return false;
}

Pos east(Puzzle p)
{
	//             
	assert(true);
	//             
	//                                                         
	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell c = p.board[i][j];
			if(c == 'w' || c == 'W') return {i, j + 1};
		}
	}
	return {-1, -1};
}

bool can_go_south(Puzzle p)
{
	//             
	assert(true);
	//             
	//                                         
	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell c = p.board[i][j];
			if((c == 'w' || c == 'W') && i < size - 1)
			{
				Cell to = p.board[i+1][j];
				if(to == ' ' || to == '.') return true;
				else if((to == 'b' || to == 'B') && i < size - 2)
				{
					Cell box_to = p.board[i + 2][j];
					if(box_to == ' ' || box_to == '.') return true;
					else return false;
				}
			}
		}
	}
	return false;
}

Pos south(Puzzle p)
{
	//             
	assert(true);
	//             
	//                                                          
	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell c = p.board[i][j];
			if(c == 'w' || c == 'W') return {i + 1, j};
		}
	}
	return {-1, -1};
}

bool can_go_west(Puzzle p)
{
	//             
	assert(true);
	//             
	//                                    
	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell c = p.board[i][j];
			if((c == 'w' || c == 'W') && j > 0)
			{
				Cell to = p.board[i][j - 1];
				if(to == ' ' || to == '.') return true;
				else if((to == 'b' || to == 'B') && j > 1)
				{
					Cell box_to = p.board[i][j - 2];
					if(box_to == ' ' || box_to == '.') return true;
					else return false;
				}
			}
		}
	}
	return false;
}

Pos west(Puzzle p)
{
	//             
	assert(true);
	//             
	//                                                         
	int size = p.board.size();
	for(int i = 0; i < size; i++)
	{
		int size2 = p.board[i].size();
		for(int j = 0; j < size2; j++)
		{
			Cell c = p.board[i][j];
			if(c == 'w' || c == 'W') return {i, j - 1};
		}
	}
	return {-1, -1};
}

void tries_breadth_first (vector<Candidate>& c, int i, Pos next)
{
	//             
	assert(i >= 0 && i < c.size());
	//             
	//                                             
	Puzzle p = c[i].candidate;
	Puzzle newp = move_worker(p, next);
	Candidate newc = {newp, i};
	if(!puzzle_present(c, i, newp)) c.push_back(newc);
}

void solve_breadth_first(Puzzle start)
{
	//             
	assert(true);
	//             
	//                                                
	vector<Candidate> c = {{start, -1}};
	int i = 0;
	while(i < c.size() && !puzzle_ready(c[i].candidate))
	{
		Puzzle p = c[i].candidate;
		if (can_go_north(p)) tries_breadth_first (c, i, north(p));
		if (can_go_east(p)) tries_breadth_first (c, i, east(p));
		if (can_go_south(p)) tries_breadth_first (c, i, south(p));
		if (can_go_west(p)) tries_breadth_first (c, i, west(p));
		i++;
	}

	int size2 = c.size();
	if(i < size2) show_path(c, i);
}

void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void tries_depth_first (vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth)
{
	//             
	assert(max_depth >= 0);
	//             
	//                                             
	Puzzle p = attempt[attempt.size() - 1];
	Puzzle newp = move_worker(p, next);
	if (!puzzle_present(newp, attempt))
	{
		attempt.push_back(newp);
		solve_depth_first(attempt, shortest, max_depth);
		attempt.pop_back();
	}
}

void solve_depth_first(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
	//             
	assert(max_depth >= 0);
	//             
	//                                                                                                     
	const int CURRENT = attempt.size();
	const int BEST = shortest.size();
	Puzzle p = attempt[CURRENT - 1];
	if(BEST > 0 && CURRENT >= BEST) return;
	else if(CURRENT > max_depth + 1) return;
	else if(puzzle_ready (p))
	{
		shortest = attempt;
		return;
	}
	if (can_go_north(p)) tries_depth_first (attempt, north(p), shortest, max_depth);
	if (can_go_east(p)) tries_depth_first (attempt, east(p), shortest, max_depth);
	if (can_go_south(p)) tries_depth_first (attempt, south(p), shortest, max_depth);
	if (can_go_west(p)) tries_depth_first (attempt, west(p), shortest, max_depth);
}

void show_solution(vector<Puzzle> solution)
{
	//             
	assert(true);
	//             
	//                               
	for(Puzzle p : solution)
	{
		print(p);
		cout << endl;
	}
}

int main()
{
	//                                                       
	//                                                              

	while(true)
	{
		ifstream file;
		if(open_file(file)) return 0;

		Puzzle p = {};
		load_puzzle(file, p);

		cout << "Loaded the following puzzle:" << endl;
		print(p);
		cout << endl;
		cout << "Please select one of the following options:\n(1) Breadth-first-search\n(2) Depth-first-search" << endl;

		int mode;
		cin >> mode;

		if(mode == 1)
		{
			cout << "Solving the puzzle with algorithm 'Breadth first search'..." << endl;
			solve_breadth_first(p);
			cout << "Steps are shown bottom -> top." << endl;
		}
		else if(mode == 2)
		{
			cout << "Please enter the maximum depth you want to check (integer)" << endl;
			int depth;
			cin >> depth;

			cout << "Solving the puzzle with algorithm 'Depth first search'..." << endl;

			vector<Puzzle> attempt;
			attempt.push_back(p);
			vector<Puzzle> shortest;
			solve_depth_first(attempt, shortest, depth);
			show_solution(shortest);
			cout << "Steps are shown top -> bottom." << endl;
		}
	}
	return 0;
}

