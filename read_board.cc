#include <iostream>
#include <sstream>
#include <fstream>

int main(){
    std::ifstream file{"layout.txt"};
    std::string line;
    while (getline(file, line)){
        std::string word;
        std::istringstream iss{line};
        while (iss >> word){
            std::cout << word << std::endl;
        }
        
    }
}