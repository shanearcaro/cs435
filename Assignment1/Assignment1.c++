#include <iostream>
#include <vector>
#include <fstream>
#include <string>

// Global variable to keep track of the number of comparisons that take place per run of insertion sort
int COMPCOUNT = 0;

// Create a vector based on a size and type requirement.
std::vector<int> createVector(int size, const char* type);

// Run the Insertion Sort algorithm on a vector
void insertionSort(std::vector<int>& vec);

int main(int argc, char* argv[]) {
    // Get input from the user
    std::string userInput;
    std::cout << "Would you like (f)ile or (m)anual input? ";
    getline(std::cin, userInput);

    if (userInput == "f" || userInput == "F") {
        // Read file from user
        std::cout << "Enter file: ";
        getline(std::cin, userInput);
        std::fstream file(userInput);
        std::ofstream outFile(userInput.substr(0, userInput.find_last_of(".")) + "_output.txt");
        if (file.is_open()) {
            while(!file.eof()) {
                // Read and transform data from a file to work with insertion sort
                getline(file, userInput);
                const char* c_size = userInput.substr(0, userInput.find(" ")).c_str();
                const char* c_type = userInput.substr(userInput.find(" ") + 1, userInput.length()).c_str();
                outFile << "Size: " << c_size << " Type: " << c_type << std::endl;

                // Data is transformed at this point, run the algorithm and print useful information
                std::vector<int> vec = createVector(atoi(c_size), c_type);
                // Dont print the vector if above a certain size
                if (vec.size() <= 50) {
                    outFile << "Original Array: ";
                    for (int i = 0; i < vec.size(); i++) {
                        outFile << vec.at(i) << " ";
                    }
                    outFile << std::endl;
                }
                insertionSort(vec);
                // Dont print the vector if above a certain size
                if (vec.size() <= 50) {
                    outFile << "Sorted Array:   ";
                    
                    for (int i = 0; i < vec.size(); i++) {
                        outFile << vec.at(i) << " ";
                    }
                    outFile << std::endl;
                }
                outFile << "Key Comparisons: " << COMPCOUNT << std::endl;
                outFile << std::endl;

                // Reset compcount after every trial
                COMPCOUNT = 0;
            }
        }
        else {
            std::cout << "Invalid file." << std::endl;
            exit(1);
        }
    }
    // If user wants to enter data manually
    else if (userInput == "m" || userInput == "M") {
        // Read input from the user
        std::string userSize;
        std::cout << "Array size: ";
        getline(std::cin, userSize);
        const char* c_size = userSize.c_str();
        std::cout << "What is this: " << c_size << std::endl;

        std::cout << "Array (W)orst, (b)est, or (r)andom case: ";
        getline(std::cin, userInput);
        const char* c_type = userInput.c_str();

        std::cout << "Size: " << c_size << " Type: " << c_type << std::endl;
        std::vector<int> vec = createVector(atoi(c_size), c_type);
        // Dont print the vector if above a certain size
        if (vec.size() <= 50) {
            std::cout << "Original Array: ";
            for (int i = 0; i < vec.size(); i++) {
                std::cout << vec.at(i) << " ";
            }
            std::cout << std::endl;
        }
        insertionSort(vec);
        // Dont print the vector if above a certain size
        if (vec.size() <= 50) {
            std::cout << "Sorted Array:   ";
                    
            for (int i = 0; i < vec.size(); i++) {
                std::cout << vec.at(i) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Key Comparisons: " << COMPCOUNT << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cout << "Invalid input." << std::endl;
        exit(1);
    }
}

// Create a vector based on a size and type requirement.
std::vector<int> createVector(int size, const char* type) {
    std::vector<int> vec;
    switch(*type) {
        case 'w':
            for (int i = 0; i < size; i++) {
                vec.push_back(size - (i + 1));
            }
            break;
        case 'b':
            for (int i = 0; i < size; i++) {
                vec.push_back(i);
            }
            break;
        case 'r':
            srand(unsigned(time(NULL)));
            for (int i = 0; i < size; i++) {
                vec.push_back(rand() % size);
            }
            break;
    }
    return vec;
}

// Run the Insertion Sort algorithm on a vector
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