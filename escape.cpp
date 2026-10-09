#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>

using std::cout;
using std::cin;
using std::cerr;

int main() {
    string filename;
    cout << "Please enter the filename for the maze: ";
    cin >> filename;
    fstream mazeFile(filename);


    mazeFile.close();
    return 0;
}
