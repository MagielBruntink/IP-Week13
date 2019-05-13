#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 6;

struct Pos
{
	int col, row;
};

struct Puzzle
{
	char board[WIDTH][HEIGHT];
	Pos worker;
};

struct Candidate
{
	Puzzle candidate;
	int parent_candidate;
};

int size(vector<Puzzle>& p)
{
	assert(true);
	//                                            
	return static_cast<int> (p.size());
}

bool operator==(const Pos& a, const Pos& b)
{
	return a.row == b.row && a.col == b.col;
}

bool operator==(const Puzzle& a, const Puzzle& b)
{
	return a.worker == b.worker && a.board == b.board;
}

bool puzzle_ready(Puzzle puzzle)
{
	assert(true);
	//                                    
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (puzzle.board[i][j] == 'W' || puzzle.board[i][j] == '.') {
				return false;
			}
		}
	}
	return true;
}

bool can_go_north(Puzzle p)
{
	assert(true);
	//                                                     
	return !(p.board[p.worker.col][p.worker.row - 1] == '*' || p.worker.row - 1 < 0 || ((p.board[p.worker.col][p.worker.row - 1] == 'b' || p.board[p.worker.col][p.worker.row - 1] == 'B') && (p.board[p.worker.col][p.worker.row - 2] == '*' || p.board[p.worker.col][p.worker.row - 2] == 'b' || p.board[p.worker.col][p.worker.row - 2] == 'B')));
}

bool can_go_south(Puzzle p)
{
	assert(true);
	//                                                     
	return !(p.board[p.worker.col][p.worker.row + 1] == '*' || p.worker.row + 1 >= HEIGHT || ((p.board[p.worker.col][p.worker.row + 1] == 'b' || p.board[p.worker.col][p.worker.row + 1] == 'B') && (p.board[p.worker.col][p.worker.row + 2] == '*' || p.board[p.worker.col][p.worker.row + 2] == 'b' || p.board[p.worker.col][p.worker.row + 2] == 'B')));
}

bool can_go_west(Puzzle p)
{
	assert(true);
	//                                                     
	return !(p.board[p.worker.col - 1][p.worker.row] == '*' || p.worker.col - 1 < 0 || ((p.board[p.worker.col - 1][p.worker.row] == 'b' || p.board[p.worker.col - 1][p.worker.row] == 'B') && (p.board[p.worker.col - 2][p.worker.row] == '*' || p.board[p.worker.col - 2][p.worker.row] == 'b' || p.board[p.worker.col - 2][p.worker.row] == 'B')));
}

bool can_go_east(Puzzle p)
{
	assert(true);
	//                                                     
	return !(p.board[p.worker.col + 1][p.worker.row] == '*' || p.worker.col + 1 >= WIDTH || ((p.board[p.worker.col + 1][p.worker.row] == 'b' || p.board[p.worker.col + 1][p.worker.row] == 'B') && (p.board[p.worker.col + 2][p.worker.row] == '*' || p.board[p.worker.col + 2][p.worker.row] == 'b' || p.board[p.worker.col + 2][p.worker.row] == 'B')));
}

Pos north(Puzzle p)
{
	assert(true);
	//                                             
	return { p.worker.col, p.worker.row - 1 };
}

Pos south(Puzzle p)
{
	assert(true);
	//                                             
	return { p.worker.col, p.worker.row + 1 };
}

Pos west(Puzzle p)
{
	assert(true);
	//                                            
	return { p.worker.col - 1, p.worker.row };
}

Pos east(Puzzle p)
{
	assert(true);
	//                                            
	return { p.worker.col + 1, p.worker.row };
}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle p)
{
	assert(true);
	//                           
	if (p == c[i].candidate) {
		return true;
	}
	else {
		return false;
	}
}

bool puzzle_present_depth(Puzzle p, vector<Puzzle>& c)
{
	assert(true);
	//                           
	for (int i = 0; i < c.size(); i++) {
		if (p == c[i]) {
			return true;
		}
	}
	return false;
}

void show_solution(vector<Candidate>& c)
{
	assert(true);
	//              
	for (int k = 0; k < c.size(); k++) {
		for (int i = 0; i < HEIGHT; i++) {
			cout << endl;
			for (int j = 0; j < WIDTH; j++) {
				cout << c[k].candidate.board[j][i];
			}
		}
	}
}

void show_solution_depth(vector<Puzzle>& c)
{
	assert(true);
	//              
	for (int k = 0; k < c.size(); k++) {
		for (int i = 0; i < HEIGHT; i++) {
			cout << endl;
			for (int j = 0; j < WIDTH; j++) {
				cout << c[k].board[j][i];
			}
		}
	}
}

void print_puzzle(Puzzle p)
{
	assert(true);
	//               
	for (int i = 0; i < HEIGHT; i++) {
		cout << endl;
		for (int j = 0; j < WIDTH; j++) {
			cout << p.board[j][i];
		}
	}
	cout << endl;
}

void print_puzzle_depth(vector<Puzzle>& p)
{
	assert(true);
	//               
	for (int i = 0; i < HEIGHT; i++) {
		cout << endl;
		for (int j = 0; j < WIDTH; j++) {
			cout << p[p.size() - 1].board[j][i];
		}
	}
	cout << endl;
}

unsigned long move_counter = 0;
Puzzle move_worker(Puzzle p, Pos next)
{
	assert(true);
	//                                                     

	/*                                                      
	                                              
	                                                                                                                      */
	Puzzle next_puzzle = p;
	move_counter++;

	if (move_counter % 100000 == 0) {
		cout << "Current move: " << move_counter << endl;
	}

	if (p.board[next.col][next.row] == 'b')
	{
		if (p.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] == '.')
		{
			if (p.board[p.worker.col][p.worker.row] == 'w')
			{
				next_puzzle.board[next.col][next.row] = 'w';
				next_puzzle.board[p.worker.col][p.worker.row] = ' ';
				next_puzzle.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] = 'B';
			}
			else
			{
				next_puzzle.board[next.col][next.row] = 'w';
				next_puzzle.board[p.worker.col][p.worker.row] = '.';
				next_puzzle.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] = 'B';
			}
		}
		else
		{
			if (p.board[p.worker.col][p.worker.row] == 'w')
			{
				next_puzzle.board[next.col][next.row] = 'w';
				next_puzzle.board[p.worker.col][p.worker.row] = ' ';
				next_puzzle.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] = 'b';
			}
			else
			{
				next_puzzle.board[next.col][next.row] = 'w';
				next_puzzle.board[p.worker.col][p.worker.row] = '.';
				next_puzzle.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] = 'b';
			}
		}
	}
	else if (p.board[next.col][next.row] == 'B')
	{
		if (p.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] == '.')
		{
			if (p.board[p.worker.col][p.worker.row] == 'w')
			{
				next_puzzle.board[next.col][next.row] = 'W';
				next_puzzle.board[p.worker.col][p.worker.row] = ' ';
				next_puzzle.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] = 'B';
			}
			else
			{
				next_puzzle.board[next.col][next.row] = 'W';
				next_puzzle.board[p.worker.col][p.worker.row] = '.';
				next_puzzle.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] = 'B';
			}
		}
		else
		{
			if (p.board[p.worker.col][p.worker.row] == 'w')
			{
				next_puzzle.board[next.col][next.row] = 'W';
				next_puzzle.board[p.worker.col][p.worker.row] = ' ';
				next_puzzle.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] = 'b';
			}
			else
			{
				next_puzzle.board[next.col][next.row] = 'W';
				next_puzzle.board[p.worker.col][p.worker.row] = '.';
				next_puzzle.board[p.worker.col + 2 * (next.col - p.worker.col)][p.worker.row + 2 * (next.row - p.worker.row)] = 'b';
			}
		}
	}
	else if (p.board[next.col][next.row] == ' ')
	{
		if (p.board[p.worker.col][p.worker.row] == 'w')
		{
			next_puzzle.board[next.col][next.row] = 'w';
			next_puzzle.board[p.worker.col][p.worker.row] = ' ';
		}
		else
		{
			next_puzzle.board[next.col][next.row] = 'w';
			next_puzzle.board[p.worker.col][p.worker.row] = '.';
		}
	}
	else
	{
		if (p.board[p.worker.col][p.worker.row] == 'w')
		{
			next_puzzle.board[next.col][next.row] = 'W';
			next_puzzle.board[p.worker.col][p.worker.row] = ' ';
		}
		else
		{
			next_puzzle.board[next.col][next.row] = 'W';
			next_puzzle.board[p.worker.col][p.worker.row] = '.';
		}
	}
	next_puzzle.worker = next;
	return next_puzzle;
}

void tries_breath(vector<Candidate>& c, int i, Pos next)
{
	assert(true);
	//                             
	Puzzle p = c[i].candidate;
	//                
	Puzzle newp = move_worker(p, next);
	//                   
	Candidate newc = { newp, i };
	if (!puzzle_present(c, i, newp))
		c.push_back(newc);
}

void solve_breath(Puzzle start)
{
	assert(true);
	//                              
	vector<Candidate> c = { {start, -1} };
	int i = 0;
	while (i < c.size() && !puzzle_ready(c[i].candidate))
	{

		Puzzle p = c[i].candidate;
		if (can_go_north(p))
			tries_breath(c, i, north(p));
		if (can_go_south(p))
			tries_breath(c, i, south(p));
		if (can_go_west(p))
			tries_breath(c, i, west(p));
		if (can_go_east(p))
			tries_breath(c, i, east(p));
		i++;
	}
	/*
	                  
		                 
	 
	*/
	if (puzzle_ready(c[i].candidate)) {
		show_solution(c);
	}
}

void solve_depth(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth);

void tries_depth(vector<Puzzle>& attempt, Pos next, vector<Puzzle>& shortest, int max_depth)
{
	assert(true);
	//                            
	Puzzle p = attempt[size(attempt) - 1];
	//                
	Puzzle newp = move_worker(p, next);
	//                   
	if (!puzzle_present_depth(newp, attempt)) {
		attempt.push_back(newp);
		solve_depth(attempt, shortest, max_depth);
		attempt.pop_back();
	}
}

void solve_depth(vector<Puzzle>& attempt, vector<Puzzle>& shortest, int max_depth)
{
	assert(true);
	//                             
	const int CURRENT = size(attempt);
	const int BEST = size(shortest);
	Puzzle p = attempt[CURRENT - 1];
	if (BEST > 0 && CURRENT >= BEST) {
		return;
	}
	else if (CURRENT > max_depth + 1) {
		return;
	}
	else if (puzzle_ready(p)) {
		shortest = attempt;
		return;
	}

	if (can_go_north(p))
		tries_depth(attempt, north(p), shortest, max_depth);
	if (can_go_south(p))
		tries_depth(attempt, south(p), shortest, max_depth);
	if (can_go_west(p))
		tries_depth(attempt, west(p), shortest, max_depth);
	if (can_go_east(p))
		tries_depth(attempt, east(p), shortest, max_depth);
}

int main()
{

	/*
	      
	                        
	                      
	*/
	
	Puzzle p1 = { {
						{'*','*','*','*','*','*'},
						{'*',' ',' ',' ',' ','*'},
						{'*',' ','.',' ',' ','*'},
						{'*',' ','b','*',' ','*'},
						{'*',' ','w','*',' ','*'},
						{'*',' ',' ','*',' ','*'},
						{'*',' ',' ','*',' ','*'},
						{'*',' ',' ',' ',' ','*'},
						{'*',' ',' ',' ',' ','*'},
						{'*','*','*','*','*','*'}},
				{4, 2} };
	/*
	                
						                          
						                          
						                          
						                          
						                          
						                          
						                           
				         

	                     
						                          
						                          
						                          
						                          
						                          
						                          
						                           
				         
				
	                
					                              
					                              
					                              
					                              
					                              
					                              
					                               
			         
			*/
	//                  
	vector<Puzzle> shortest;
	vector<Puzzle> attempt;
	attempt.push_back(p1);
	solve_depth(attempt, shortest, 32);
	print_puzzle_depth(shortest);
	cout << "Total attempts: " << move_counter << ". Best solution is " << size(shortest) << " moves" << endl;
	print_puzzle_depth(shortest);
	return 0;
}

