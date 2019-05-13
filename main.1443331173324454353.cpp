//                    
//             

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <stdio.h>

using namespace std;

const int NO_OF_ROWS        = 10 ;
const int NO_OF_COLUMNS     = 20 ;

char attempt [NO_OF_ROWS][NO_OF_COLUMNS];
char game[NO_OF_ROWS][NO_OF_COLUMNS] {{'*','*','*','*','*','*','*','*','*','*'}
                                     ,{'*',' ',' ','w',' ',' ',' ',' ',' ','*'}
                                     ,{'*',' ',' ','b',' ',' ',' ',' ',' ','*'}
                                     ,{'*',' ',' ','.',' ',' ',' ',' ',' ','*'}
                                     ,{'*',' ',' ','*','*','*','*',' ',' ','*'}
                                     ,{'*',' ',' ',' ',' ',' ',' ',' ',' ','*'}
                                     ,{'*','*','*','*','*','*','*','*','*','*'}};

bool finished()
{
    for (int i =1; i< NO_OF_ROWS; i++){
        for (int j =1; j< NO_OF_COLUMNS; j++){
                if (game[i][j]!='b')
                    return true;
                else return false;
        }}
}

bool can_go_east(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS])
{
    if (game[i][j] == 'w')
        if (game[i][j+1] == ' ' || game[i][j+1] == '.')
            return true;
    else return false;

}

void east(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS], char attempt[NO_OF_ROWS][NO_OF_COLUMNS])
{

    if (game[i][j] == 'w')
        {
            if (game[i][j+1]== ' ')
            {game[i][j+1]= 'w';
            game[i][j] = ' ';}
            if (game[i][j+1]== '.')
            {game[i][j+1]= 'W';
            game[i][j] = ' ';}
    for (int i = 0; i< NO_OF_ROWS; i++){
        for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
            cout << endl;
        }
        }
    if (game[i][j] == 'W')
        {
            if (game[i][j+1]== ' ')
            {game[i][j+1]= 'w';
            game[i][j] = '.';}
            if (game[i][j+1]== '.')
            {game[i][j+1]= 'W';
            game[i][j] = '.';}
    for (int i = 0; i< NO_OF_ROWS; i++){
        for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

        }
        cout << endl;
        }
        }

   }

   bool can_go_south(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS])
{
    if (game[i][j] == 'w')
        if (game[i+1][j] == ' ' || game[i+1][j] == '.')
            return true;
    else return false;

}

void south(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS], char attempt[NO_OF_ROWS][NO_OF_COLUMNS])
{

    if (game[i][j] == 'w')
        {
            if (game[i+1][j]== ' ')
            {game[i+1][j]= 'w';
            game[i][j] = ' ';}
            if (game[i+1][j]== '.')
            {game[i+1][j]= 'W';
            game[i][j] = ' ';}
    for (int i = 0; i< NO_OF_ROWS; i++){
        for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
            cout << endl;
        }
        }
    if (game[i][j] == 'W')
        {
            if (game[i+1][j]== ' ')
            {game[i+1][j]= 'w';
            game[i][j] = '.';}
            if (game[i+1][j]== '.')
            {game[i+1][j]= 'W';
            game[i][j] = '.';}
    for (int i = 0; i< NO_OF_ROWS; i++){
        for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

        }
        cout << endl;
        }
        }

   }

bool can_go_west(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS])
{
    if (game[i][j] == 'w')
        if (game[i][j-1] == ' ' || game[i][j-1] == '.')
            return true;
    else return false;

}

void west(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS], char attempt[NO_OF_ROWS][NO_OF_COLUMNS])
{

    if (game[i][j] == 'w')
        {
            if (game[i][j-1]== ' ')
            {game[i][j-1]= 'w';
            game[i][j] = ' ';}
            if (game[i][j-1]== '.')
            {game[i][j-1]= 'W';
            game[i][j] = ' ';}
    for (int i = 0; i< NO_OF_ROWS; i++){
        for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
            cout << endl;
        }
        }
    if (game[i][j] == 'W')
        {
            if (game[i][j-1]== ' ')
            {game[i][j-1]= 'w';
            game[i][j] = '.';}
            if (game[i][j-1]== '.')
            {game[i][j-1]= 'W';
            game[i][j] = '.';}
    for (int i = 0; i< NO_OF_ROWS; i++){
        for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

        }
        cout << endl;
        }
        }

   }

  bool can_go_north(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS])
{
    if (game[i][j] == 'w')
        if (game[i-1][j] == ' ' || game[i-1][j] == '.')
            return true;
    else return false;

}

void north(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS], char attempt[NO_OF_ROWS][NO_OF_COLUMNS])
{

    if (game[i][j] == 'w')
        {
            if (game[i-1][j]== ' ')
            {game[i-1][j]= 'w';
            game[i][j] = ' ';}
            if (game[i-1][j]== '.')
            {game[i-1][j]= 'W';
            game[i][j] = ' ';}
    for (int i = 0; i< NO_OF_ROWS; i++){
        for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
            cout << endl;
        }
        }
    if (game[i][j] == 'W')
        {
            if (game[i-1][j]== ' ')
            {game[i-1][j]= 'w';
            game[i][j] = '.';}
            if (game[i-1][j]== '.')
            {game[i-1][j]= 'W';
            game[i][j] = '.';}
    for (int i = 0; i< NO_OF_ROWS; i++){
        for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

        }
        cout << endl;
        }
        }

   }

   bool can_push_east(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS])
{
    if (game[i][j] == 'w')
        if (game[i][j+1] == 'b' || game[i][j+1] == 'B')
            return true;
    else return false;

}

void push_east(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS], char attempt[NO_OF_ROWS][NO_OF_COLUMNS])
{
    assert(game[i][j+2]!='*' ||game[i][j+2]!='B' || game[i][j+2]!='b'  );
    if (game[i][j] == 'w')
        {
            if (game[i][j+1]== 'b'&&game[i][j+2]==' ')
            {
            game[i][j+2]= 'b';
            game[i][j+1]= 'w';
            game[i][j] = ' ';
            }

            if (game[i][j+1]== 'b'&&game[i][j+2]=='.')
            {
            game[i][j+2]= 'B';
            game[i][j+1]= 'w';
            game[i][j] = ' ';
            }

            if (game[i][j+1]== 'B'&&game[i][j+2]==' ')
            {
            game[i][j+2]= 'b';
            game[i][j+1]= 'W';
            game[i][j] = ' ';
            }

            if (game[i][j+1]== 'B'&&game[i][j+2]=='.')
            {
            game[i][j+2]= 'B';
            game[i][j+1]= 'W';
            game[i][j] = ' ';
            }
            for (int i = 0; i< NO_OF_ROWS; i++){
                for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
            cout << endl;
        }
        }
            if (game[i][j] == 'W')
        {
            if (game[i][j+1]== 'b'&&game[i][j+2]==' ')
            {
            game[i][j+2]= 'b';
            game[i][j+1]= 'w';
            game[i][j] = '.';
            }

            if (game[i][j+1]== 'b'&&game[i][j+2]=='.')
            {
            game[i][j+2]= 'B';
            game[i][j+1]= 'w';
            game[i][j] = '.';
            }

            if (game[i][j+1]== 'B'&&game[i][j+2]==' ')
            {
            game[i][j+2]= 'b';
            game[i][j+1]= 'W';
            game[i][j] = '.';
            }

            if (game[i][j+1]== 'B'&&game[i][j+2]=='.')
            {
            game[i][j+2]= 'B';
            game[i][j+1]= 'W';
            game[i][j] = '.';
            }
            for (int i = 0; i< NO_OF_ROWS; i++){
                for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
        cout << endl;
        }
        }

   }

   bool can_push_south(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS])
{
    if (game[i][j] == 'w')
        if (game[i+1][j] == 'b' || game[i+1][j] == 'B')
            return true;
    else return false;

}

void push_south(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS], char attempt[NO_OF_ROWS][NO_OF_COLUMNS])
{
    assert(game[i+2][j]!='*' ||game[i+2][j]!='B' || game[i+2][j]!='b'  );
    if (game[i][j] == 'w')
        {
            if (game[i+1][j]== 'b'&&game[i+2][j]==' ')
            {
            game[i+2][j]= 'b';
            game[i+1][j]= 'w';
            game[i][j] = ' ';
            }

            if (game[i+1][j]== 'b'&&game[i+2][j]=='.')
            {
            game[i+2][j]= 'B';
            game[i+1][j]= 'w';
            game[i][j] = ' ';
            }

            if (game[i+1][j]== 'B'&&game[i+2][j]==' ')
            {
            game[i+2][j]= 'b';
            game[i+1][j]= 'W';
            game[i][j] = ' ';
            }

            if (game[i+1][j]== 'B'&&game[i+2][j]=='.')
            {
            game[i+2][j]= 'B';
            game[i+1][j]= 'W';
            game[i][j] = ' ';
            }
            for (int i = 0; i< NO_OF_ROWS; i++){
                for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
            cout << endl;
        }
        }
            if (game[i][j] == 'W')
        {
            if (game[i+1][j]== 'b'&&game[i+2][j]==' ')
            {
            game[i+2][j]= 'b';
            game[i+1][j]= 'w';
            game[i][j] = '.';
            }

            if (game[i+1][j]== 'b'&&game[i+2][j]=='.')
            {
            game[i+2][j]= 'B';
            game[i+1][j]= 'w';
            game[i][j] = '.';
            }

            if (game[i+1][j]== 'B'&&game[i+2][j]==' ')
            {
            game[i+2][j]= 'b';
            game[i+1][j]= 'W';
            game[i][j] = '.';
            }

            if (game[i+1][j]== 'B'&&game[i+2][j]=='.')
            {
            game[i+2][j]= 'B';
            game[i+1][j]= 'W';
            game[i][j] = '.';
            }
            for (int i = 0; i< NO_OF_ROWS; i++){
                for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
        cout << endl;
        }
        }

   }

   bool can_push_west(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS])
{
    if (game[i][j] == 'w')
        if (game[i][j-1] == 'b' || game[i][j-1] == 'B')
            return true;
    else return false;

}

void push_west(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS], char attempt[NO_OF_ROWS][NO_OF_COLUMNS])
{
    assert(game[i][j-2]!='*' ||game[i][j-2]!='B' || game[i][j-2]!='b'  );
    if (game[i][j] == 'w')
        {
            if (game[i][j-1]== 'b'&&game[i][j-2]==' ')
            {
            game[i][j-2]= 'b';
            game[i][j-1]= 'w';
            game[i][j] = ' ';
            }

            if (game[i][j-1]== 'b'&&game[i][j-2]=='.')
            {
            game[i][j-2]= 'B';
            game[i][j-1]= 'w';
            game[i][j] = ' ';
            }

            if (game[i][j-1]== 'B'&&game[i][j-2]==' ')
            {
            game[i][j-2]= 'b';
            game[i][j-1]= 'W';
            game[i][j] = ' ';
            }

            if (game[i][j-1]== 'B'&&game[i][j-2]=='.')
            {
            game[i][j-2]= 'B';
            game[i][j-1]= 'W';
            game[i][j] = ' ';
            }
            for (int i = 0; i< NO_OF_ROWS; i++){
                for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
            cout << endl;
        }
        }
            if (game[i][j] == 'W')
        {
            if (game[i][j-1]== 'b'&&game[i][j-2]==' ')
            {
            game[i][j-2]= 'b';
            game[i][j-1]= 'w';
            game[i][j] = '.';
            }

            if (game[i][j-1]== 'b'&&game[i][j-2]=='.')
            {
            game[i][j-2]= 'B';
            game[i][j-1]= 'w';
            game[i][j] = '.';
            }

            if (game[i][j-1]== 'B'&&game[i][j-2]==' ')
            {
            game[i][j-2]= 'b';
            game[i][j-1]= 'W';
            game[i][j] = '.';
            }

            if (game[i][j-1]== 'B'&&game[i][j-2]=='.')
            {
            game[i][j-2]= 'B';
            game[i][j-1]= 'W';
            game[i][j] = '.';
            }
            for (int i = 0; i< NO_OF_ROWS; i++){
                for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
        cout << endl;
        }
        }

   }

bool can_push_north(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS])
{
    if (game[i][j] == 'w')
        if (game[i+1][j] == 'b' || game[i+1][j] == 'B')
            return true;
    else return false;

}

void push_north(int j, int i, char game[NO_OF_ROWS][NO_OF_COLUMNS], char attempt[NO_OF_ROWS][NO_OF_COLUMNS])
{
    assert(game[i-2][j]!='*' ||game[i-2][j]!='B' || game[i-2][j]!='b'  );
    if (game[i][j] == 'w')
        {
            if (game[i-1][j]== 'b'&&game[i-2][j]==' ')
            {
            game[i-2][j]= 'b';
            game[i-1][j]= 'w';
            game[i][j] = ' ';
            }

            if (game[i-1][j]== 'b'&&game[i-2][j]=='.')
            {
            game[i-2][j]= 'B';
            game[i-1][j]= 'w';
            game[i][j] = ' ';
            }

            if (game[i-1][j]== 'B'&&game[i-2][j]==' ')
            {
            game[i-2][j]= 'b';
            game[i-1][j]= 'W';
            game[i][j] = ' ';
            }

            if (game[i-1][j]== 'B'&&game[i-2][j]=='.')
            {
            game[i-2][j]= 'B';
            game[i-1][j]= 'W';
            game[i][j] = ' ';
            }
            for (int i = 0; i< NO_OF_ROWS; i++){
                for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
            cout << endl;
        }
        }
            if (game[i][j] == 'W')
        {
            if (game[i-1][j]== 'b'&&game[i-2][j]==' ')
            {
            game[i-2][j]= 'b';
            game[i-1][j]= 'w';
            game[i][j] = '.';
            }

            if (game[i-1][j]== 'b'&&game[i-2][j]=='.')
            {
            game[i-2][j]= 'B';
            game[i-1][j]= 'w';
            game[i][j] = '.';
            }

            if (game[i-1][j]== 'B'&&game[i-2][j]==' ')
            {
            game[i-2][j]= 'b';
            game[i-1][j]= 'W';
            game[i][j] = '.';
            }

            if (game[i-1][j]== 'B'&&game[i-2][j]=='.')
            {
            game[i-2][j]= 'B';
            game[i-1][j]= 'W';
            game[i][j] = '.';
            }
            for (int i = 0; i< NO_OF_ROWS; i++){
                for (int j = 0; j<NO_OF_COLUMNS; j++){
                attempt[i][j]=game[i][j];
                cout << attempt[i][j];

            }
        cout << endl;
        }
        }

   }

int read_file(int j, int i)
{
for (int i =0; i< NO_OF_ROWS; i++){
        for (int j =0; j< NO_OF_COLUMNS; j++){
                cout << game[i][j];
        }
        cout << endl;
}
}

int go_east(int j, int i){
for (int i =1; i< NO_OF_ROWS; i++){
        for (int j =1; j< NO_OF_COLUMNS; j++){
            if (game[i][j]=='w')
                if (can_go_east(j,i, game))
                    {east(j,i,game, attempt);
                    return game[i][j];}}}}

int go_south(int i, int j){
for (int i =1; i< NO_OF_ROWS; i++){
        for (int j =1; j< NO_OF_COLUMNS; j++){
            if (game[i][j]=='w')
                if (can_go_south(j,i, game))
                    {south(j,i,game, attempt);
                    return game[i][j];}}}}

int go_west(int i, int j){
for (int i =1; i< NO_OF_ROWS; i++){
        for (int j =1; j< NO_OF_COLUMNS; j++){
            if (game[i][j]=='w')
                if (can_go_west(j,i, game))
                    {west(j,i,game, attempt);
                    return game[i][j];}}}}

int go_north(int i, int j){
for (int i =1; i< NO_OF_ROWS; i++){
        for (int j =1; j< NO_OF_COLUMNS; j++){
            if (game[i][j]=='w')
                if (can_go_north(j,i, game))
                    {north(j,i,game, attempt);
                    return game[i][j];}}}}

int pushh_east(int i, int j){
for (int i =1; i< NO_OF_ROWS; i++){
        for (int j =1; j< NO_OF_COLUMNS; j++){
            if (game[i][j]=='w')
                if (can_push_east(j,i, game))
                    {push_east(j,i,game, attempt);
                    return game[i][j];}}}}

int pushh_south(int i, int j){
for (int i =1; i< NO_OF_ROWS; i++){
        for (int j =1; j< NO_OF_COLUMNS; j++){
            if (game[i][j]=='w')
                if (can_push_south(j,i, game))
                    {push_south(j,i,game, attempt);
                    return game[i][j];}}}}

int pushh_west(int i, int j){
for (int i =1; i< NO_OF_ROWS; i++){
        for (int j =1; j< NO_OF_COLUMNS; j++){
            if (game[i][j]=='w')
                if (can_push_west(j,i, game))
                    {push_west(j,i,game, attempt);
                    return game[i][j];}}}}

int pushh_north(int i, int j){
for (int i =1; i< NO_OF_ROWS; i++){
        for (int j =1; j< NO_OF_COLUMNS; j++){
            if (game[i][j]=='w')
                if (can_push_north(j,i, game))
                    {push_north(j,i,game, attempt);
                    return game[i][j];}}}}

int main()
{
    int j,i =0;
    read_file(i, j);
    pushh_south(j,i);
    if (finished){
        cout << "puzzle finished" << endl;
        return 0;
    }
    go_east(j,i);
    go_south(j,i);

}

