// TODO: Check all of the TODO tags and add them

#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <vector>
#include "conio.h"

using std::cout;
using std::cin;
using std::cerr;

// Variables
const int mazeSize = 10;
char mazeArr[mazeSize][mazeSize] = {{0}};
bool isStarted = false;


//Functions
void makeFileToArray(std::ifstream& filename);
void showMaze();
void updateShowMaze(int selectedRow, int selectedCol, bool reccursive = false);
bool isValidStart(int row, int col);
void showMazeAll();
void showMazeAll(int selectedRow, int selectedCol); 
void handleUserInput();

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
    showMazeAll();

    //Start of input for Row and Col (MOVE TO handleUserInput())
    handleUserInput();




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

// DO NOT USE THIS FUNCTION, USE IT FOR REFERENCE ONLY
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

// DO NOT USE THIS FUNCTION, USE IT FOR REFERENCE ONLY
void updateShowMaze(int selectedRow, int selectedCol, bool reccursive) {
    //bool reccursive = false;
    //conio::clrscr();
    cout << "\033[2J\033[H";
    for(int i = 0; i < mazeSize; i++) {
        if(i == 0)  {
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
            if((i == selectedRow) && (j == selectedCol) && (!reccursive)) {
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
                        // INTO UPDATE SHOW MAZE (1st):
                        // reccursive = false
                        //

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





// Merging the 2 methods above
void showMazeAll() {
    // Clear Screen
    //cout << conio::clrscr();
    cout << "\033[2J\033[H";
    for(int i = 0; i < mazeSize; i++) {
        // Print out top numbers
        if(i == 0) {
            cout << "  ";

            for(int a = 0; a < mazeSize; a++) {
                cout << a;
            }

            cout << "\n";
        }

        for(int j = 0; j < mazeSize; j++) {
            // Print out top numbers
            if((j % 10 == 0) || (j == 0)) {
                cout << i << " ";
            } 
            cout << mazeArr[j][i];
        }
        
        cout << "\n";
    }
}


// Handle the validness outside of the loop first.
void showMazeAll(int selectedRow, int selectedCol) {
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
            
            //Selected Row and Col coloring
            if((i == selectedRow) && (j == selectedCol)) {
                cout << conio::bgColor(conio::BLUE);
                cout << mazeArr[j][i];
                cout << conio::resetAll();
            } else {
                cout << mazeArr[j][i];
            }
        }

        cout << "\n";
    }
}

//TODO Create a method to showMaze updating if there is already using the variable isStarted





// Maybe this will help ignore all above for now.
// RETURN false IF VALUE IS #
// RETURN true IF VALUE IS .
bool isValidStart(int row, int col) {
    char value = mazeArr[row][col];
    if(value == '#') {
        return false;
    } else if(value == '.') {
        return true;
    } else {
        return false;
    }
}

// Handle the Row Col input
void handleUserInput() {
    int sRow;
    int sCol;

    cout << "Please enter the starting point (Row Col): ";
    cin >> sRow;
    cin >> sCol;

    if(isValidStart(sRow, sCol)) {
        // Show the updated Maze
        showMazeAll(sRow, sCol);
    } else {
        // Get input for y/n
        char input;

        //cout << conio::clrscr();
        cout << "\033[2J\033[H";
        // Show maze for consistency
        showMazeAll();
        cout << "The starting point you slected is a wall, do you want to select a new Starting point (y/n): ";
        cin >> input;
        // User types y
        if((input == 'y') || (input == 'Y')) {
            cout << "\033[2J\033[H";
            showMazeAll();
            handleUserInput();
        }

    }
}


// TODO: Write a method to move.
//
// TODO: Write the Method to solve the maze

// Method to check where walls are
// Return where you CAN move (All points stuctured { {row, col}, {row2, col2} } -> can move to pos row, col and row2, col2) 
// return {{UpRow, upCol}, {rightRol, rightCol}, {downRow, downCol}, {leftRow, leftCol}};
// return {{-1, -1}} if it cant be moved.
// TODO: Make a function where you check to see if it is moving back
// TODO: write a method to see if you can move
std::vector<std::vector<int>> checkWallPosition(int currentArrPosRow, int currentArrPosCol) {
    std::vector<std::vector<int>> validSpaces;
    // Check the space above
    // Position: currentArrPosRow + 1
    if(mazeArr[currentArrPosRow + 1][currentArrPosCol] == '.') {
        validSpaces[0].push_back(currentArrPosRow + 1);
        validSpaces[0].push_back(currentArrPosCol);
    } else {
        validSpaces[0].push_back(-1);
        validSpaces[0].push_back(-1);
    }

    // Check space to Right
    // Position: currentArrPosCol + 1
    if(mazeArr[currentArrPosRow][currentArrPosCol + 1] == '.') {
        validSpaces[1].push_back(currentArrPosRow);
        validSpaces[1].push_back(currentArrPosCol + 1);
    } else {
        validSpaces[1].push_back(-1);
        validSpaces[1].push_back(-1);
    }

    // Check space below
    // Position: currentArrPosRow - 1
    if(mazeArr[currentArrPosRow - 1][currentArrPosCol] == '.') {
        validSpaces[2].push_back(currentArrPosRow - 1);
        validSpaces[2].push_back(currentArrPosCol);
    } else {
        validSpaces[2].push_back(-1);
        validSpaces[2].push_back(-1);
    }

    // Check space to Lefy
    // Position: currentArrPosCol - 1
    if(mazeArr[currentArrPosRow][currentArrPosCol - 1] == '.') {
        validSpaces[3].push_back(currentArrPosRow);
        validSpaces[3].push_back(currentArrPosCol - 1);
    } else {
        validSpaces[3].push_back(-1);
        validSpaces[3].push_back(-1);
    }

    return validSpaces;
}


