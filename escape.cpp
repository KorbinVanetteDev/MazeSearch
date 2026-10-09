#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>

using std::cout;
using std::cin;
using std::cerr;

int main() {
    // Read the file
    std::string filename;
    cout << "Please enter the filename for the maze: ";
    cin >> filename;
    std::fstream mazeFile(filename);
    if(!mazeFile) {
        cout << "That is an invalid file\n";
        return 0;
    }


    mazeFile.close();
    return 0;
}
