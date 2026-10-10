#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include "conio.h"

using std::cout;
using std::cin;
using std::cerr;

// Variables
const int mazeSize = 10;
char mazeArr[mazeSize][mazeSize] = {{0}};


//Functions
void makeFileToArray(std::ifstream& filename);
void showMaze();
void updateShowMaze(int selectedRow, int selectedCol, bool reccursive = false);

int main() {
    // Read the file
    std::string filename;
    cout << "Please enter the filename for the maze: ";
    cin >> filename;
    std::ifstream mazeFile(filename);
    if(!mazeFile) {
        cout << "That is an invalid file\n";
        return 0;
    }
    
    makeFileToArray(mazeFile);

    // Show the array
    showMaze();

    //Start of input for Row and Col
    int sRow;
    int sCol;
    cout << "Please enter the starting point (Row Col): ";
    cin >> sRow;
    cin >> sCol;
    updateShowMaze(sRow, sCol, false);



    mazeFile.close();
    return 0;
}

void makeFileToArray(std::ifstream& filename) {
    char temp;
    int row = 0;
    int col = 0;
    while(filename >> temp) {
        mazeArr[row][col] = temp;
        row++;
        if(row == mazeSize) {
            row = 0;
            col++;
        }

        if(col == mazeSize) {
            break;
        }
    }
}

// TODO: Make this have an update color too (make true or false and certain index to change color)
void showMaze() {
    //conio::clrscr();
    cout << "\033[2J\033[H";
    for(int i = 0; i < mazeSize; i++) {
        if(i == 0) {
            cout << "  ";
            for(int a = 0; a < mazeSize; a++) {
                cout << a;
            }
            cout << "\n";
        }
        for(int j = 0; j < mazeSize; j++) {
            if((j % 10 == 0) || (j == 0)) {
                cout << i << " ";
            } 
            cout << mazeArr[j][i];
        }
        
        cout << "\n";
    }
}


// right now just make bgcolor blue on selected row, col
// PROBLEM TODO: fix the chart showing up twice.
void updateShowMaze(int selectedRow, int selectedCol, bool reccursive) {
    //bool reccursive = false;
    //conio::clrscr();
    cout << "\033[2J\033[H";
    for(int i = 0; i < mazeSize; i++) {
        if((i == 0) && (!reccursive))  {
            cout << "  ";
            for(int a = 0; a < mazeSize; a++) {
                cout << a;
            }
            cout << "\n";
        }
        for(int j = 0; j < mazeSize; j++) {
            if(((j % 10 == 0) || (j == 0)) && (!reccursive))  {
                cout << i << " ";
            }
            if((i == selectedRow) && (j == selectedCol)) {
                // Handle if it is a tag
                if(mazeArr[j][i] == '#') {
                    // conio::clrscr();
                    cout << "\033[2J\033[H";
                    updateShowMaze(mazeSize + 1, mazeSize + 1, false);
                    char input;
                    cout << "The starting point you slected is a wall, do you want to select a new Starting point (y/n): ";
                    cin >> input;
                    if((input == 'y') || (input == 'Y')) {
                        //conio::clrscr();
                        cout << "\033[2J\033[H";
                        updateShowMaze(mazeSize + 1, mazeSize + 1, false);
                        

                        // What Happens:
                        // calls updateShowMaze(0, 0) reccursive = false
                        // clear screen
                        // INTO I FOR
                        // i = 0 if (0==0) and reccursive = false -> space and print numbers, then make new line
                        // INTO J FOR
                        // if j / 10 remaider 0 or j==0 AND reccursive == false
                        // cout number i which is 0
                        // if 0 == selectedRow WHICH IS TRUE and 0 == selectedCol WHICH IS ALSO TRUE if return true
                        // if mazeArr[j][i] == '#' WHICH IS DOES if return true
                        // clear screen, updateShowMaze(11, 11)
                        // INTO UPDATE SHOW MAZE:
                        // reccursive = 

                        int sRow;
                        int sCol;

                        cout << "Please enter the starting point (Row Col): ";
                        cin >> sRow;
                        cin >> sCol;
                        //Reccursion without a base case!??
                        updateShowMaze(sRow, sCol, true);
                        //reccursive = true;
                    }
                    
                }
                cout << conio::bgColor(conio::BLUE);
                cout << mazeArr[j][i];
                cout << conio::resetAll();
            } else if(!reccursive) {
                cout << mazeArr[j][i];
            }

        }
        cout << "\n";
    }
}
