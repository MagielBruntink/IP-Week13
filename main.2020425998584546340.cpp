//           
//
//                          
//                       
//
#include <cassert>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAP_MAX_X 12
#define MAP_MAX_Y 11
#define DF_MAX_DEPTH 35

enum Tile {Void=0, Empty, Wall, Dest, Box, FinalBox};

constexpr char repr(Tile tile) {
    switch (tile) {
        case Void:
            return 'X';
        case Empty:
            return ' ';
        case Wall:
            return '*';
        case Dest:
            return '.';
        case Box:
            return 'b';
        case FinalBox:
            return 'B';
        default:
            assert(false);
    }
}

ostream& operator<<(ostream& out, const Tile tile) {
    switch (tile) {
        case Void:
            break;
        default:
            out << repr(tile);
    }
    return out;
}

struct Worker {
    int x;
    int y;
};

bool operator==(const Worker a, const Worker b) {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Worker a, const Worker b) {
    return !(a == b);
}

bool fast_compare(Worker& a, Worker& b) {
    return a.x == b.x && a.y == b.y;
}

struct Direction {
    int delta_x;
    int delta_y;
};

const Direction Up    = { 0, -1};
const Direction Down  = { 0,  1};
const Direction Left  = {-1,  0};
const Direction Right = { 1,  0};

struct Puzzle {
    Tile map[MAP_MAX_Y][MAP_MAX_X];
    Worker worker;
};

bool operator==(const Puzzle a, const Puzzle b) {
    if (a.worker != b.worker) {
        return false;
    }

    for (int y=0; y < MAP_MAX_Y; y++) {
        for (int x=0; x < MAP_MAX_X; x++) {
            if (a.map[y][x] != b.map[y][x]) {
                return false;
            }
        }
    }

    return true;
}

bool fast_compare(Puzzle& a, Puzzle& b) {
    if (!fast_compare(a.worker, b.worker)) {
        return false;
    }

    for (int y=0; y < MAP_MAX_Y; y++) {
        for (int x=0; x < MAP_MAX_X; x++) {
            if (a.map[y][x] != b.map[y][x]) {
                return false;
            }
        }
    }

    return true;
}

int size(vector<Puzzle>& v) {
    return static_cast<int>(v.size());
}

struct Candidate {
    Puzzle candidate;
    int parent;
};

int size(vector<Candidate>& v) {
    return static_cast<int>(v.size());
}

int load_puzzle(Puzzle& p) {
    assert(true);
    char c;
    int x = 0, y = 0;

    cin.clear();
    if (!cin)
        return -EIO;

    while (cin) {
        cin.get(c);
        switch (c) {
            case '\r':
                break;
            case '\n':
                p.map[y][x] = Void;
                x = 0;
                y++;
                break;
            case 'w':
                p.worker.x = x;
                p.worker.y = y;
            case repr(Empty):
                p.map[y][x] = Empty;
                x++;
                break;
            case repr(Wall):
                p.map[y][x] = Wall;
                x++;
                break;
            case 'W':
                p.worker.x = x;
                p.worker.y = y;
            case repr(Dest):
                p.map[y][x] = Dest;
                x++;
                break;
            case repr(Box):
                p.map[y][x] = Box;
                x++;
                break;
            case repr(FinalBox):
                p.map[y][x] = FinalBox;
                x++;
                break;
            default:
                return -EINVAL;
        }
    }

    p.map[y][0] = Void;

    return 0;
}

void render_puzzle(Puzzle& p) {
    bool ybreak = false;
    for (int y=0; y < MAP_MAX_Y && !ybreak; y++) {
        bool xbreak = false;
        for (int x=0; x < MAP_MAX_X && !xbreak; x++) {
            if (p.map[y][x] == Void) {
                xbreak = true;
            } else if (p.worker.x == x && p.worker.y == y) {
                if (p.map[y][x] == Dest) {
                    cout << 'W';
                } else {
                    cout << 'w';
                }
            } else {
                cout << p.map[y][x];
            }
        }

        if (p.map[y][0] == Void) {
            ybreak = true;
        } else {
            cout << endl;
        }
    }
}

bool can_move(Puzzle& p, const Direction& dir) {
    if (p.worker.y + dir.delta_y < 0 || p.worker.y + dir.delta_y >= MAP_MAX_Y ||
        p.worker.x + dir.delta_x < 0 || p.worker.x + dir.delta_x >= MAP_MAX_X) {
        return false;
    }

    switch (p.map[p.worker.y + dir.delta_y][p.worker.x + dir.delta_x]) {
        case Void:
            assert(false);
        case Wall:
            return false;
        case Empty:
        case Dest:
            return true;
        case Box:
        case FinalBox:
            switch (p.map[p.worker.y + (dir.delta_y*2)][p.worker.x + (dir.delta_x*2)]) {
                case Void:
                    assert(false);
                case Wall:
                case Box:
                case FinalBox:
                    return false;
                case Empty:
                case Dest:
                    return true;
                default:
                    assert(false);
            }
        default:
            assert(false);
    }
}

bool puzzle_solved(Puzzle& p) {
    for (int y=0; y < MAP_MAX_Y; y++) {
        for (int x=0; x < MAP_MAX_X; x++) {
            if (p.map[y][x] == Dest) {
                return false;
            }
        }
    }

    return true;
}

Puzzle move(Puzzle p, const Direction& d) {
    if (p.map[p.worker.y + d.delta_y][p.worker.x + d.delta_x] == Box ||
        p.map[p.worker.y + d.delta_y][p.worker.x + d.delta_x] == FinalBox) {
        if (p.map[p.worker.y + (d.delta_y*2)][p.worker.x + (d.delta_x*2)] == Empty) {
            p.map[p.worker.y + (d.delta_y*2)][p.worker.x + (d.delta_x*2)] = Box;
        } else if (p.map[p.worker.y + (d.delta_y*2)][p.worker.x + (d.delta_x*2)] == Dest) {
            p.map[p.worker.y + (d.delta_y*2)][p.worker.x + (d.delta_x*2)] = FinalBox;
        } else {
            assert(false);
        }

        if (p.map[p.worker.y + d.delta_y][p.worker.x + d.delta_x] == Box) {
            p.map[p.worker.y + d.delta_y][p.worker.x + d.delta_x] = Empty;
        } else if (p.map[p.worker.y + d.delta_y][p.worker.x + d.delta_x] == FinalBox) {
            p.map[p.worker.y + d.delta_y][p.worker.x + d.delta_x] = Dest;
        }
    }

    p.worker.y += d.delta_y;
    p.worker.x += d.delta_x;

    return p;
}

bool puzzle_present(vector<Candidate>& c, int i, Puzzle& p) {
    while (i > 0) {
        if (fast_compare(c[i].candidate, p)) {
            return true;
        }
        i = c[i].parent;
    }

    return false;
}

bool puzzle_present(vector<Puzzle>& v, Puzzle& p) {
    for (int i=0; i < size(v); i++) {
        if (fast_compare(v[i], p)) {
            return true;
        }
    }

    return false;
}

int bfsolve(Puzzle p, vector<Puzzle>& solution) {
    vector<Candidate> c = {{p, -1}};
    int i = 0;

    for (; i < size(c) && !puzzle_solved(c[i].candidate); i++) {
        if (can_move(c[i].candidate, Left)) {
            Puzzle new_p = move(c[i].candidate, Left);
            if (!puzzle_present(c, i, new_p))
                    c.push_back({new_p, i});
        }
        if (can_move(c[i].candidate, Up)) {
            Puzzle new_p = move(c[i].candidate, Up);
            if (!puzzle_present(c, i, new_p))
                    c.push_back({new_p, i});
        }
        if (can_move(c[i].candidate, Right)) {
            Puzzle new_p = move(c[i].candidate, Right);
            if (!puzzle_present(c, i, new_p))
                    c.push_back({new_p, i});
        }
        if (can_move(c[i].candidate, Down)) {
            Puzzle new_p = move(c[i].candidate, Down);
            if (!puzzle_present(c, i, new_p))
                    c.push_back({new_p, i});
        }

        if (i % 1000 == 0) {
            cout << '.';
        }
    }
    if (i < size(c)) {
        int j = i;
        while (j > 0) {
            solution.push_back(c[j].candidate);
            j = c[j].parent;
        }
        return i;
    } else {
        return -1;
    }
}

void dfsolve(vector<Puzzle>& attempt, vector<Puzzle>& shortest) {
    const int CURRENT = size(attempt);
    const int BEST    = size(shortest);

    if (BEST > 0 && CURRENT >= BEST) {
        return;
    } else if (CURRENT > DF_MAX_DEPTH) {
        return;
    } else if (puzzle_solved(attempt[CURRENT-1])) {
        shortest = attempt;
        return;
    } else {
        if (can_move(attempt[CURRENT-1], Left)) {
            Puzzle new_p = move(attempt[CURRENT-1], Left);
            if (!puzzle_present(attempt, new_p)) {
                attempt.push_back(new_p);
                dfsolve(attempt, shortest);
                attempt.pop_back();
            }
        }
        if (can_move(attempt[CURRENT-1], Up)) {
            Puzzle new_p = move(attempt[CURRENT-1], Up);
            if (!puzzle_present(attempt, new_p)) {
                attempt.push_back(new_p);
                dfsolve(attempt, shortest);
                attempt.pop_back();
            }
        }
        if (can_move(attempt[CURRENT-1], Right)) {
            Puzzle new_p = move(attempt[CURRENT-1], Right);
            if (!puzzle_present(attempt, new_p)) {
                attempt.push_back(new_p);
                dfsolve(attempt, shortest);
                attempt.pop_back();
            }
        }
        if (can_move(attempt[CURRENT-1], Down)) {
            Puzzle new_p = move(attempt[CURRENT-1], Down);
            if (!puzzle_present(attempt, new_p)) {
                attempt.push_back(new_p);
                dfsolve(attempt, shortest);
                attempt.pop_back();
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int r = 0;
    Puzzle puzzle;
    vector<Puzzle> solution;
    bool bfsearch = false, dfsearch = false;

    if (string(argv[0]) ==  "./bfsearch" || string(argv[0]) == "bfsearch") {
        cerr << "Using breadth-first search" << endl;
        bfsearch = true;
    } else if (string(argv[0]) == "./dfsearch" || string(argv[0]) == "dfsearch") {
        cerr << "Using depth-first search" << endl;
        dfsearch = true;
    }

    if (bfsearch || dfsearch) {
        r = load_puzzle(puzzle);
        if (r < 0)
            return -r;
    } else {
        cerr << "Usage: Call the program as either bfsearch or dfsearch, "
            << "then give the sokoban map on stdin." << endl;
        return -1;
    }

    render_puzzle(puzzle);

    if (bfsearch) {
        cout << bfsolve(puzzle, solution);
        cout << endl;
        for (int i = size(solution) - 1; i >= 0; i--) {
            render_puzzle(solution[i]);
        }
    }

    if (dfsearch) {
        vector<Puzzle> attempt = {puzzle};
        dfsolve(attempt, solution);
        cout << size(solution) - 1;
        cout << endl;
        for (int i = 0; i < size(solution); i++) {
            render_puzzle(solution[i]);
        }
    }

    return r;
}

