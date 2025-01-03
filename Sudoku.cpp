#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
using namespace std;

class Sudoku{
    public:
    bool SolveSudoku(vector<vector<int>>&board){
        bool solved = backtrack(board);
        if(solved){
            PrintBoard(board);
        }else{
            cout << "no Solution!";
        }
        return solved;
    }
    bool backtrack(vector<vector<int>>&board){
        //board contains a sudoku board where 0 means it is blank
        int rows = board.size();
        int cols = board[0].size();
        
        for(int i =0; i<rows; i++){
            for(int j =0; j<cols; j++){
                if(board[i][j] == 0){
                    for(int val=1; val<=9; val++){
                        //check column and row and its box
                        if(CheckLine(board,i,j,val) && CheckGrid(board, i,j,val)){
                            board[i][j] = val;
                            if(backtrack(board)){
                                return true;
                            }
                            board[i][j] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    bool CheckLine(vector<vector<int>>&board, int i, int j, int placeholder){
        vector<pair<int,int>>directions = {{-1,0},{0,-1},{1,0},{0,1}};
        for(pair<int,int> dir : directions){
            int x = i;
            int y = j;
            while(x>=0 && x<9 && y>=0 && y<9){
                x += dir.first;
                y += dir.second;
                if (x >= 0 && x < 9 && y >= 0 && y < 9 && board[x][y] == placeholder) { 
                    return false;
                }
                if (x < 0 || x >= 9 || y < 0 || y >= 9){
                    break;
                }
            }
        }
        return true;
    }

    bool CheckGrid(vector<vector<int>>&board, int i, int j, int placeholder){
        unordered_map<int,pair<int,int>>BoxPos = {
            {0,{0,0}}, {1,{0,3}}, {2,{0,6}}, {3,{3,0}},
            {4,{3,3}}, {5,{3,6}}, {6,{6,0}}, {7,{6,3}}, {8,{6,6}}
            };
        int boxIndx = (i/3)*3 + (j/3);
        //iterate through the 3x3 grid
        pair<int,int>coord = BoxPos[boxIndx];
        int x = coord.first;
        int y = coord.second;
        
        for(int row=x; row<x+3; row++){
            for(int col=y; col<y+3; col++){
                if(board[row][col] == placeholder){
                    return false;
                }
            }
        }
        return true;
    }

    void PrintBoard(vector<vector<int>>&board){
        for(const auto& row: board){
            for(int num: row){
                cout << num << " ";
            }
            cout << endl;
        }
    }
};


