#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

enum Types {Wall=0, CellEmpty, CellDest, WorkerEmpty, WorkerDest, BoxEmpty, BoxDest};

 //                                     

struct Candidate {
    vector< vector<Types> > candidate;
    int parent_of_candidate;
};

bool open_file(ifstream& input_file, string file_name) {
    assert (true);
    //                                                                                                                                                   
    cout << endl;
    input_file.open(file_name);
    if (input_file.is_open()) {
        cout << "File opened successfully..." << endl;
        return true;
    }
    cout << "Error opening file!" << endl;
    return false;
}

void read_file (ifstream& input_file, vector< vector<Types> >& arrangement, string file_name, int max_row, int max_column) {
    assert (input_file.is_open() && max_row > 0 && max_column > 0 && "ERROR: check function read_file!");
    //                                                                                                                      
    input_file.close();
    input_file.open(file_name);
    char character = ' ';
    int row = 0;
    int column = 0;
    while (row <= max_row && column <= max_column + 1) {
        input_file.get(character);
        if (character == '*') {
            arrangement[row][column] =  Wall;
        }
        if (character == ' ') {
            arrangement[row][column] = CellEmpty;
        }
        if (character == '.') {
            arrangement[row][column] = CellDest;
        }
        if (character == 'w') {
            arrangement[row][column] = WorkerEmpty;
        }
        if (character == 'W') {
            arrangement[row][column] = WorkerDest;
        }
        if (character == 'b') {
            arrangement[row][column] = BoxEmpty;
        }
        if (character == 'B') {
            arrangement[row][column] = BoxDest;
        }
        column = column + 1;
        if (character == '\n') {
            column = 0;
            row = row + 1;
        }
    }

}

void find_dimensions (int& row, int& column_max, ifstream& input_file) {
    assert (input_file.is_open() && "ERROR: Check function find_dimensions!");
    //                                                                                                                       
    char character = ' ';
    int column = 1;
    while(input_file) {
        input_file.get(character);
        if (column > column_max) {
            column_max = column;
        }
        column = column + 1;
        if (character == '\n') {
            column = 1;
            row = row + 1;
        }
    }
    row = row - 2;
    column_max = column_max - 1;
}

void print_arrangement (vector< vector<Types> > arrangement, int row, int column) {
    assert (true);
    //                                                                             
    for (int i = 0; i < row; i ++) {
        for (int j = 0; j < column; j++) {
            if (arrangement [i][j] == Wall) {
                cout << '*';
            }
            if (arrangement [i][j] == CellEmpty) {
                cout << ' ';
            }
            if (arrangement [i][j] == CellDest) {
                cout << '.';
            }
            if (arrangement [i][j] == WorkerEmpty) {
                cout << 'w';
            }
            if (arrangement [i][j] == WorkerDest) {
                cout << 'W';
            }
            if (arrangement [i][j] == BoxEmpty) {
                cout << 'b';
            }
            if (arrangement [i][j] == BoxDest) {
                cout << 'B';
            }
        }
        cout << endl;
    }
    cout << endl << endl << endl;
}

bool is_solution (vector< vector<Types> >& candidate, int rows, int columns) {
    assert (true);
    //                                                                                                       
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (candidate[i][j] == BoxEmpty) {
                return false;
            }
        }
    }
    return true;
}

bool try_go_right_with_box (vector< vector<Types> >& vect, int rows, int columns) {
    assert (true);
    //                                                                                                                                                                
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((vect[i][j] == WorkerEmpty || vect[i][j] == WorkerDest) && (vect[i][j+1] == BoxEmpty || vect[i][j+1] == BoxEmpty) && (vect[i][j+2] != Wall) && (vect[i][j+2] != BoxDest) && (vect[i][j+2] != BoxEmpty)) {
                if (vect [i][j+2] == CellDest) {
                    vect [i][j+2] = BoxDest;
                } else {vect[i][j+2] = BoxEmpty;}
                if (vect[i][j+1] == BoxDest) {
                    vect [i][j+1] = WorkerDest;
                } else {vect[i][j+1] = WorkerEmpty;}
                if (vect[i][j] == WorkerDest) {
                    vect[i][j] = CellDest;
                } else {vect[i][j] = CellEmpty;}
                return true;
            }
        }
    }
    return false;
}

bool try_go_up_with_box (vector< vector<Types> >& vect, int rows, int columns) {
    assert (true);
    //                                                                                                                                                      
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((vect[i][j] == WorkerEmpty || vect[i][j] == WorkerDest) && (vect[i+1][j] == BoxEmpty || vect[i+1][j] == BoxEmpty) && (vect[i+2][j] != Wall) && (vect[i+2][j] != BoxDest) && (vect[i+2][j] != BoxEmpty)) {
                if (vect [i+2][j] == CellDest) {
                    vect [i+2][j] = BoxDest;
                } else {vect[i+2][j] = BoxEmpty;}
                if (vect[i+1][j] == BoxDest) {
                    vect [i+1][j] = WorkerDest;
                } else {vect[i+1][j] = WorkerEmpty;}
                if (vect[i][j] == WorkerDest) {
                    vect[i][j] = CellDest;
                } else {vect[i][j] = CellEmpty;}
                return true;
            }
        }
    }
}

bool try_go_down_with_box (vector< vector<Types> >& vect, int rows, int columns) {
    assert (true);
    //                                                                                                                                                        
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((vect[i][j] == WorkerEmpty || vect[i][j] == WorkerDest) && (vect[i-1][j] == BoxEmpty || vect[i-1][j] == BoxEmpty) && (vect[i-2][j] != Wall) && (vect[i-2][j] != BoxDest) && (vect[i-2][j] != BoxEmpty)) {
                if (vect [i-2][j] == CellDest) {
                    vect [i-2][j] = BoxDest;
                } else {vect[i-2][j] = BoxEmpty;}
                if (vect[i-1][j] == BoxDest) {
                    vect [i-1][j] = WorkerDest;
                } else {vect[i-1][j] = WorkerEmpty;}
                if (vect[i][j] == WorkerDest) {
                    vect[i][j] = CellDest;
                } else {vect[i][j] = CellEmpty;}
                return true;
            }
        }
    }
}

bool try_go_left_with_box (vector< vector<Types> >& vect, int rows, int columns) {
    assert (true);
    //                                                                                                                                                               
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((vect[i][j] == WorkerEmpty || vect[i][j] == WorkerDest) && (vect[i][j-1] == BoxEmpty || vect[i][j-1] == BoxEmpty) && (vect[i][j-2] != Wall) && (vect[i][j-2] != BoxDest) && (vect[i][j-2] != BoxEmpty)) {
                if (vect [i][j-2] == CellDest) {
                    vect [i][j-2] = BoxDest;
                } else {vect[i][j-2] = BoxEmpty;}
                if (vect[i][j-1] == BoxDest) {
                    vect [i][j-1] = WorkerDest;
                } else {vect[i][j-1] = WorkerEmpty;}
                if (vect[i][j] == WorkerDest) {
                    vect[i][j] = CellDest;
                } else {vect[i][j] = CellEmpty;}
                return true;
            }
        }
    }
    return false;
}

bool try_go_right_without_box (vector< vector<Types> >& vect, int rows, int columns) {
    assert (true);
    //                                                                                                                                          
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((vect[i][j] == WorkerEmpty || vect[i][j] == WorkerDest) && (vect[i][j+1] != Wall) && (vect[i][j+1] != BoxDest) && (vect[i][j+1] != BoxEmpty)) {
                if (vect[i][j+1] == CellDest) {
                    vect[i][j+1] = WorkerDest;
                } else {vect[i][j+1] = WorkerEmpty;}
                if (vect[i][j] == WorkerDest) {
                    vect[i][j] = CellDest;
                } else {vect[i][j] = CellEmpty;}
                return true;
            }
        }
    }
    return false;
}

bool try_go_up_without_box (vector< vector<Types> >& vect, int rows, int columns) {
    assert (true);
    //                                                                                                                                
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((vect[i][j] == WorkerEmpty || vect[i][j] == WorkerDest) && (vect[i+1][j] != Wall) && (vect[i+1][j] != BoxDest) && (vect[i+1][j] != BoxEmpty)) {
                if (vect[i+1][j] == CellDest) {
                    vect[i+1][j] = WorkerDest;
                } else {vect[i+1][j] = WorkerEmpty;}
                if (vect[i][j] == WorkerDest) {
                    vect[i][j] = CellDest;
                } else {vect[i][j] = CellEmpty;}
                return true;
            }
        }
    }
    return false;
}

bool try_go_down_without_box (vector< vector<Types> >& vect, int rows, int columns) {
    assert (true);
    //                                                                                                                                  
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((vect[i][j] == WorkerEmpty || vect[i][j] == WorkerDest) && (vect[i-1][j] != Wall) && (vect[i-1][j] != BoxDest) && (vect[i-1][j] != BoxEmpty)) {
                if (vect[i-1][j] == CellDest) {
                    vect[i-1][j] = WorkerDest;
                } else {vect[i-1][j] = WorkerEmpty;}
                if (vect[i][j] == WorkerDest) {
                    vect[i][j] = CellDest;
                } else {vect[i][j] = CellEmpty;}
                return true;
            }
        }
    }
    return false;
}

bool try_go_left_without_box (vector< vector<Types> >& vect, int rows, int columns) {
    assert (true);
    //                                                                                                                                         
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((vect[i][j] == WorkerEmpty || vect[i][j] == WorkerDest) && (vect[i][j-1] != Wall) && (vect[i][j-1] != BoxDest) && (vect[i][j-1] != BoxEmpty)) {
                if (vect[i][j-1] == CellDest) {
                    vect[i][j-1] = WorkerDest;
                } else {vect[i][j-1] = WorkerEmpty;}
                if (vect[i][j] == WorkerDest) {
                    vect[i][j] = CellDest;
                } else {vect[i][j] = CellEmpty;}
                return true;
            }
        }
    }
    return false;
}

void show_path(vector<Candidate>& cand, int i, int row, int column) {
    assert (true);
    //                                                                                  
    if (i != -1) {
        show_path(cand, cand[i].parent_of_candidate, row, column);
        print_arrangement(cand[i].candidate, row, column);
    }
}

bool is_this_a_duplicate_breadth_first (vector<Candidate> cand_vect, vector< vector<Types> > p) {
    assert (true);
    //                                                                                                               
    for (int i = 0; i < cand_vect.size(); i++) {
        if (cand_vect[i].candidate == p) {
            return true;
        }
    }
    return false;
}

bool is_this_a_duplicate_depth_first(vector < vector< vector<Types> > > vect_of_vects, vector< vector<Types> > p) {
    assert (true);
    //                                                                                                                   
    for (int i = 0; i < vect_of_vects.size(); i++) {
        if (vect_of_vects[i] == p) {
            return true;
        }
    }
    return false;
}

void breadth_first (vector< vector<Types> > start, int rows, int columns) {
    assert (rows > 0 && columns > 0 && "ERROR: Check function breadth_first!");
    //                                                                                                              
    vector<Candidate> cand = {{start, -1}};
    int i = 0;
    while (i < static_cast<int>(cand.size()) && !is_solution(cand[i].candidate, rows, columns)) {
        vector< vector<Types> > p = cand[i].candidate;
        //                                    
        if (try_go_right_with_box(p, rows, columns) && !is_this_a_duplicate_breadth_first(cand, p)){
            cand.push_back({p, i});
        }
        p = cand[i].candidate;
        if (try_go_up_with_box(p, rows, columns) && !is_this_a_duplicate_breadth_first(cand, p)){
            cand.push_back({p, i});
        }
        p = cand[i].candidate;
        if (try_go_down_with_box(p, rows, columns) && !is_this_a_duplicate_breadth_first(cand, p)){
            cand.push_back({p, i});
        }
        p = cand[i].candidate;
        if (try_go_left_with_box(p, rows, columns) && !is_this_a_duplicate_breadth_first(cand, p)){
            cand.push_back({p, i});
        }
        p = cand[i].candidate;
        if (try_go_right_without_box(p, rows, columns) && !is_this_a_duplicate_breadth_first(cand, p)){
            cand.push_back({p, i});
        }
        p = cand[i].candidate;
        if (try_go_up_without_box(p, rows, columns) && !is_this_a_duplicate_breadth_first(cand, p)) {
            cand.push_back({p, i});
        }
        p = cand[i].candidate;
        if (try_go_down_without_box(p, rows, columns) && !is_this_a_duplicate_breadth_first(cand, p)) {
            cand.push_back({p, i});
        }
        p = cand[i].candidate;
        if (try_go_left_without_box(p, rows, columns) && !is_this_a_duplicate_breadth_first(cand, p)) {
            cand.push_back({p, i});
        }
        p = cand[i].candidate;
        i = i + 1;
    }
    if (i < static_cast<int>(cand.size())) {
        show_path(cand, i, rows, columns);
    }
}

void depth_first (vector < vector< vector<Types> > >& attempt, vector < vector< vector<Types> > >&  shortest_attempt, int  max_depth, int rows, int columns){
    assert (rows > 0 && columns > 0 && max_depth > 0 && "ERROR: Check function depth_first!");
    //                                                                                                                        
    //                        
    /*                                          
                                                     
     
                                                       
                                                   
                                                              
     */
    const int SIZE_ATTEMPT = attempt.size();
    const int SIZE_SHORTEST_ATTEMPT = shortest_attempt.size();
    vector< vector<Types> > p = attempt[SIZE_ATTEMPT - 1];
    if (SIZE_SHORTEST_ATTEMPT > 0 && SIZE_ATTEMPT >= SIZE_SHORTEST_ATTEMPT) {
        return;
    } else if (SIZE_ATTEMPT > max_depth + 1) {
        return;
    } else if (is_solution(p, rows, columns)) {
        shortest_attempt = attempt;
        return;
    }

    if (try_go_right_with_box(p, rows, columns) && !is_this_a_duplicate_depth_first(attempt, p)){
        attempt.push_back(p);
        depth_first(attempt, shortest_attempt, max_depth, rows, columns);
        attempt.pop_back();
    }
    p = attempt[SIZE_ATTEMPT - 1];
    if (try_go_up_with_box(p, rows, columns) && !is_this_a_duplicate_depth_first(attempt, p)){
        attempt.push_back(p);
        depth_first(attempt, shortest_attempt, max_depth, rows, columns);
        attempt.pop_back();
    }
    p = attempt[SIZE_ATTEMPT - 1];
    if (try_go_down_with_box(p, rows, columns) && !is_this_a_duplicate_depth_first(attempt, p)){
        attempt.push_back(p);
        depth_first(attempt, shortest_attempt, max_depth, rows, columns);
        attempt.pop_back();
    }
    p = attempt[SIZE_ATTEMPT - 1];
    if (try_go_left_with_box(p, rows, columns) && !is_this_a_duplicate_depth_first(attempt, p)){
        attempt.push_back(p);
        depth_first(attempt, shortest_attempt, max_depth, rows, columns);
        attempt.pop_back();
    }
    p = attempt[SIZE_ATTEMPT - 1];
    if (try_go_right_without_box(p, rows, columns) && !is_this_a_duplicate_depth_first(attempt, p)){
        attempt.push_back(p);
        depth_first(attempt, shortest_attempt, max_depth, rows, columns);
        attempt.pop_back();
    }
    p = attempt[SIZE_ATTEMPT - 1];
    if (try_go_up_without_box(p, rows, columns) && !is_this_a_duplicate_depth_first(attempt, p)) {
        attempt.push_back(p);
        depth_first(attempt, shortest_attempt, max_depth, rows, columns);
        attempt.pop_back();
    }
    p = attempt[SIZE_ATTEMPT - 1];
    if (try_go_down_without_box(p, rows, columns) && !is_this_a_duplicate_depth_first(attempt, p)) {
        attempt.push_back(p);
        depth_first(attempt, shortest_attempt, max_depth, rows, columns);
        attempt.pop_back();
    }
    p = attempt[SIZE_ATTEMPT - 1];
    if (try_go_left_without_box(p, rows, columns) && !is_this_a_duplicate_depth_first(attempt, p)) {
        attempt.push_back(p);
        depth_first(attempt, shortest_attempt, max_depth, rows, columns);
        attempt.pop_back();
    }
    p = attempt[SIZE_ATTEMPT - 1];
}

int main()
{
    char choice = ' ';
    string file_name = " ";
    int row = 1;
    int column = 1;
    int max_depth = 0;
    ifstream infile;
    cout << "Enter file name: ";
    cin >> file_name;
    if (!open_file(infile, file_name)) {
        return -1;
    }
    find_dimensions(row, column, infile);
    cout << "rows: " << row  << "   columns: " << column << endl;
    cout << endl << "Challenge Layout:" << endl;
    vector< vector<Types> > arrangement (row, vector <Types>(column, Wall));
    read_file(infile, arrangement, file_name, row, column);
    cout << endl;
    print_arrangement(arrangement, row, column);
    cout << "Do you want to perform breadth-first search(b), or depth-first search(d)?" << endl << "choice: ";
    cin >> choice;
    cout << endl;
    if (choice == 'b' || choice == 'B') {
        cout << "Performing breadth-first search..." << endl << endl;
        breadth_first(arrangement, row, column);
    }
    if (choice == 'd' || choice == 'D') {
        cout << "What is the max depth? (larger than 0)" << endl;
        cout << "Max Depth: ";
        cin >> max_depth;
        cout << endl << endl;
        vector < vector< vector<Types> > > attempt_depth_first = {arrangement};
        vector < vector< vector<Types> > > shortest_attempt_depth_first;
        if (max_depth > 0) {
            cout << "Performing depth-first search..." << endl << endl;
            depth_first(attempt_depth_first, shortest_attempt_depth_first, max_depth, row, column);
            for (int i = 0; i < shortest_attempt_depth_first.size(); i++) {
                print_arrangement(shortest_attempt_depth_first[i], row, column);
            }
        } else {
            cout << "Invalid max depth!" << endl;
        }
    }
    return 0;
}

