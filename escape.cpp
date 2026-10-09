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
void showMazeNoNumbers();

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
    /*
    for(int i = 0; i < mazeSize; i++) {
        if(i == 0) {
            cout << " ";
            for(int a = 0; a < mazeSize; a++) {
                cout << a;
            }
        } else {
            for(int j = 0; j < mazeSize; j++) {
                if(j==0) {
                    cout << " ";
                }
                cout <<  mazeArr[j][i];
            }
        }
        cout << "\n";
    }*/
    showMaze();
    //showMazeNoNumbers();

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

void showMaze() {
    //conio::clrscr();
    for(int i = 0; i < mazeSize; i++) {
        if(i == 0) {
            cout << "  ";
            for(int a = 0; a < mazeSize; a++) {
                cout << a;
            }
            cout << "\n";
        }
        // ERROR HERE
        // TODO: show the first array
        for(int j = 0; j < mazeSize; j++) {
            if((j % 10 == 0) || (j == 0)) {
                cout << i << " ";
            } 
            cout << mazeArr[j][i];
        }
        
        cout << "\n";
    }
}

void showMazeNoNumbers() {
    for(int i = 0; i < mazeSize; i++) {
        for(int j = 0; j < mazeSize; j++) {
            cout << mazeArr[j][i];
        }
        cout << "\n";
    }
}
