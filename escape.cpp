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
void updateShowMaze(int selectedRow, int selectedCol);

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
    updateShowMaze(sRow, sCol);



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
void updateShowMaze(int selectedRow, int selectedCol) {
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
