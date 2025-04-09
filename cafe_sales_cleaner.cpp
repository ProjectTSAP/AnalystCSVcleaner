#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

bool isValidDouble(const std::string& s) {
    try {
    std::stod(s);
    return true;
} catch (...) {
    return false;
}
}

int main() {
    std::ifstream inFile("dirty_cafe_sales.csv");
    std::ofstream outFile("cleaned_cafe_sales.csv");
    std::string line;

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cout << "Error opening files.\n";
        return 1;
    }

    if (getline(inFile, line)) {
        outFile << line << "\n";
    }

    if (getline(inFile, line)) {
        outFile << line << "\n";
    }
    while (getline(inFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (getline(ss, cell, ',')) {
            if (cell.empty() || cell == "ERROR" || cell == "UNKNOWN") {
                row.push_back("N/A");
            } else {
            row.push_back(cell);    
            }
        }
        if (row.size() != 8) continue;

        std::string totalSpent = row[4];
        std::string paymentMethod = row[5];
        std::string location = row[6];

        if (isValidDouble(totalSpent) && paymentMethod != "UNKNOWN" && location != "UNKNOWN") {
            for (size_t i = 0; i < row.size(); i++){
            outFile << row[i];
            if (i != row.size() - 1) outFile << ",";   
            }
        outFile << "\n";    
        }
    }
    inFile.close();
    outFile.close();
    std::cout << "Cafe file cleaned successfully.\n";
    return 0;
}