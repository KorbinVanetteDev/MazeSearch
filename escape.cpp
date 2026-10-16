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

//Variable
const int mazeSize = 10;
char mazeArr[mazeSize][mazeSize] = {{0}};
std::vector<std::vector<int>> path;
bool visited[mazeSize][mazeSize] = {{false}};

//Function
void makeFileToArray(std::ifstream& filename);
bool isValidStart(int row, int col);
void showMazeAll();
void showMazeAll(int selectedRow, int selectedCol, bool isStarted);
void handleUserInput();
std::vector<std::vector<int>> checkWallPosition(int currentArrPosRow, int currentArrPosCol);
void solveMaze(int startingRow, int startingCol);
bool isInPath(int row, int col);
bool move(int currentRow, int currentCol);

int main() {
    //Read File
    std::string filename;
    cout << "Please enter the Filename for the maze: ";
    cin >> filename;
    std::ifstream mazeFile(filename);
    if(!mazeFile) {
        cout << "That is an invalid file\n";
        return 0;
    }

    makeFileToArray(mazeFile);

    // Show the Array
    showMazeAll();

    //Easier way to loop and feel smart for using reccursion
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

//Show maze
void showMazeAll() {
    //Clear screen
    cout << "\033[2J\033[H";
    for(int i = 0; i < mazeSize; i++) {
        //Print top numbers
        if(i == 0) {
            cout << "  ";

            for(int a = 0; a < mazeSize; a++) {
                cout << a;
            }

            cout << "\n";
        }

        for(int j = 0; j < mazeSize; j++) {
            //Print out side numbers
            if((j % 10 == 0) || (j == 0)) {
                cout << i << " ";
            }

            cout << mazeArr[j][i];
        }

        cout << "\n";
    }
}

//Show maze + path
void showMazeAll(int selectedRow, int selectedCol, bool isStarted) {
    //Clear screen
    cout << "\033[2J\033[H";

    for(int i = 0; i < mazeSize; i++) {
        //Print top numbers
        if(i == 0) {
            cout << "  ";

            for(int a = 0; a < mazeSize; a++) {
                cout << a;
            }

            cout << "\n";
        }

        for(int j = 0; j < mazeSize; j++) {
            //Print Size Nmubers
            if((j % 10 == 0) || (j == 0)) {
                cout << i << " ";
            }

            if(isStarted) {
                if(((i == selectedRow) && (j == selectedCol)) || (isInPath(i, j))) {
                    if(mazeArr[j][i] == 'E') {
                        cout << conio::bgColor(conio::GREEN);
                    } else {
                        cout << conio::bgColor(conio::BLUE);
                    }

                    cout << mazeArr[j][i];
                    cout << conio::resetAll();
                } else {
                    cout << mazeArr[j][i];
                }
            } else {
                cout << mazeArr[j][i];
            }
        }

        cout << "\n";
    }
}

bool isValidStart(int row, int col) {
    if((row < 0) || (row >= mazeSize) || (col < 0) || (col >= mazeSize)) {
        return false;
    }

    char value = mazeArr[col][row];

    if(value == '#') {
        return false;
    } else if(value == '.') {
        return true;
    } else {
        return false;
    }
}

void handleUserInput() {
    int sRow;
    int sCol;

    cout << "Please enter the starting point (Row Col): ";
    cin >> sRow;
    cin >> sCol;

    if(isValidStart(sRow, sCol)) {
        solveMaze(sRow, sCol);
    } else {
        // get input for y/n
        char input;

        //Clear Screen
        cout << "\033[2J\033[H";

        showMazeAll();
        cout << "The starting point you selected is a wall, do you want to select a new starting point (y/n): ";
        cin >> input;

        if((input == 'y') || (input == 'Y')) {
            //Clear Screen
            cout << "\033[2J\033[H";
            showMazeAll();
            handleUserInput();
        }
    }
}

// Clear, then solve
void solveMaze(int startingRow, int startingCol) {
    path.clear();

    for(int i = 0; i < mazeSize; i++) {
        for(int j = 0; j < mazeSize; j++) {
            visited[i][j] = false;
        } 
    }

    if(move(startingRow, startingCol)) {
        cout << "Escaped!\n";
    } else {
        cout << "No escape path found.\n";
    }
}


// Method to check where walls are
// Return where you CAN move (All points structured { {row, col }, {row2, col2} })
// it return like this { {upRow, upCol}, {rightRow, rightCol}, {downRow, downCol}, {leftRow, leftCol} }
// also returns the end point
// -1, -1 means it cant move to that spot
std::vector<std::vector<int>> checkWallPosition(int currentArrPosRow, int currentArrPosCol) {
    std::vector<std::vector<int>> validSpaces;

    // Check the space above
    // Position: currentArrPosRow - 1
    if((currentArrPosRow > 0) && ((mazeArr[currentArrPosCol][currentArrPosRow - 1] == '.') || (mazeArr[currentArrPosCol][currentArrPosRow - 1] == 'E'))) {
        std::vector<int> up;

        up.push_back(currentArrPosRow - 1);
        up.push_back(currentArrPosCol);

        validSpaces.push_back(up);
    } else {
        std::vector<int> up;

        up.push_back(-1);
        up.push_back(-1);

        validSpaces.push_back(up);
    }

    // Check sapce to Right
    // Position: currentArrPosCol + 1
    if((currentArrPosCol < mazeSize - 1) && ((mazeArr[currentArrPosCol + 1][currentArrPosRow] == '.') || (mazeArr[currentArrPosCol + 1][currentArrPosRow] == 'E'))) {
        std::vector<int> right;

        right.push_back(currentArrPosRow);
        right.push_back(currentArrPosCol + 1);

        validSpaces.push_back(right);
    } else {
        std::vector<int> right;

        right.push_back(-1);
        right.push_back(-1);

        validSpaces.push_back(right);
    }

    // Check space below
    // Position: currentArrPosRow + 1
    if((currentArrPosRow < mazeSize - 1) && ((mazeArr[currentArrPosCol][currentArrPosRow + 1] == '.') || (mazeArr[currentArrPosCol][currentArrPosRow + 1] == 'E'))) {
        std::vector<int> down;

        down.push_back(currentArrPosRow + 1);
        down.push_back(currentArrPosCol);

        validSpaces.push_back(down);
    } else {
        std::vector<int> down;

        down.push_back(-1);
        down.push_back(-1);

        validSpaces.push_back(down);
    }

    // Check space to left
    // Position: xurrentArrPosCol - 1
    if((currentArrPosCol > 0) && ((mazeArr[currentArrPosCol - 1][currentArrPosRow] == '.') || (mazeArr[currentArrPosCol - 1][currentArrPosRow] == 'E'))) {
        std::vector<int> left;

        left.push_back(currentArrPosRow);
        left.push_back(currentArrPosCol - 1);

        validSpaces.push_back(left);
    } else {
        std::vector<int> left;

        left.push_back(-1);
        left.push_back(-1);

        validSpaces.push_back(left);
    }

    return validSpaces;
}

// Recursive move function (To solve the maze)
bool move(int currentRow, int currentCol) {
    if((currentRow < 0) || (currentRow >= mazeSize) || (currentCol < 0) || (currentCol >= mazeSize)) {
        return false;
    }

	if((mazeArr[currentCol][currentRow] != '.' && mazeArr[currentCol][currentRow] != 'E') || visited[currentRow][currentCol]) {
        return false;
    }

	visited[currentRow][currentCol] = true;
	path.push_back({currentRow, currentCol});

	showMazeAll(currentRow, currentCol, true);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	if(mazeArr[currentCol][currentRow] == 'E') {
		return true;
	}

    std::vector<std::vector<int>> movePoints = checkWallPosition(currentRow, currentCol);

    for(int i = 0; i < movePoints.size(); i++) {
        if((movePoints[i][0] >= 0) && (movePoints[i][1] >= 0)) {
            if(move(movePoints[i][0], movePoints[i][1])) {
                return true;
            }
        }
    }

    path.pop_back();

    if(!path.empty()) {
        showMazeAll(path[path.size() - 1][0], path[path.size() - 1][1], true);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } else {
        showMazeAll();
    }

    return false;
}

// Fucntion to see if there is a number in te=he path
// return true if a number is in path
bool isInPath(int row, int col) {
    if(path.empty()) return false;
    for(int i = 0; i < path.size(); i++) {
        if((path[i][0] == row) && (path[i][1] == col)) {
            return true;
        }
    }

    return false;
}
