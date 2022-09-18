#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int COMPCOUNT = 0;

std::vector<int> createVector(int size, const char* type);
void insertionSort(std::vector<int>& vec);

int main(int argc, char* argv[]) {
    std::string userInput;
    std::cout << "Would you like (f)ile or (m)anual input? ";
    getline(std::cin, userInput);

    if (userInput == "f" || userInput == "F") {
        // Read file from user
        std::cout << "Enter file: ";
        getline(std::cin, userInput);
        std::fstream file(userInput);
        if (file.is_open()) {
            while(!file.eof()) {
                // Read and transform data from a file to work with insertion sort
                getline(file, userInput);
                std::string size = userInput.substr(0, userInput.find(" "));
                const char* c_size = const_cast<char*>(size.c_str());
                std::string type = userInput.substr(userInput.find(" ") + 1, userInput.length());
                const char* c_type = type.c_str();

                std::cout << "Size: " << c_size << " Type: " << c_type << std::endl;

                // Data is transformed at this point, run the algorithm and print useful information
                std::vector<int> vec = createVector(atoi(c_size), c_type);
                if (vec.size() <= 50) {
                    std::cout << "Original Array: ";
                    for (int i = 0; i < vec.size(); i++) {
                        std::cout << vec.at(i) << " ";
                    }
                    std::cout << std::endl;
                }
                insertionSort(vec);
                if (vec.size() <= 50) {
                    std::cout << "Sorted Array:   ";
                    
                    for (int i = 0; i < vec.size(); i++) {
                        std::cout << vec.at(i) << " ";
                    }
                    std::cout << std::endl;
                }
                std::cout << "Key Comparisons: " << COMPCOUNT << std::endl;
                std::cout << std::endl;

                // Reset compcount after every trial
                COMPCOUNT = 0;
            }
        }
        else {
            std::cout << "Invalid file." << std::endl;
            exit(1);
        }
    }
    else if (userInput == "m" || userInput == "M") {
        // Read input from the user
        // std::vector<int> vec = createVector(10, 'w');
        // insertionSort(vec);
        // for (int i = 0; i < vec.size(); i++) {
        //     std::cout << vec.at(i) << " ";
        // }
        // std::cout << std::endl;
    }
    else {
        std::cout << "Invalid input." << std::endl;
        exit(1);
    }
}

std::vector<int> createVector(int size, const char* type) {
    std::vector<int> vec;
    srand(unsigned(time(NULL)));
    for (int i = 0; i < size; i++) {
        if (*type == 'w') {
            vec.push_back(size - (i + 1));
        }
        else if (*type == 'b')
            vec.push_back(i);
        else if (*type == 'r')
            vec.push_back(rand() % size);
    }
    return vec;
}

void insertionSort(std::vector<int>& vec) {
    int i = 1, j;
    while (i < vec.size()) {
        j = i;
        while (j > 0 && vec[j - 1] > vec[j]) {
            int x = vec[j];
            vec[j] = vec[j - 1];
            vec[j - 1] = x;
            j--;
            COMPCOUNT++;
        }
        i++;
    }
}