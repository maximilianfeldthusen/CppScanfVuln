```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class VulnerabilityScanner {
public:
    // List of unsafe functions to check against
    const std::vector<std::string> unsafeFunctions = {
        "strcpy", "strcat", "gets", "sprintf", "scanf"
    };

    void scanFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        std::string line;
        int lineNumber = 0;
        while (std::getline(file, line)) {
            lineNumber++;
            checkLineForVulnerabilities(line, lineNumber);
        }

        file.close();
    }

private:
    void checkLineForVulnerabilities(const std::string& line, int lineNumber) {
        for (const auto& func : unsafeFunctions) {
            if (line.find(func) != std::string::npos) {
                std::cout << "Potential vulnerability found in " << lineNumber << ": " 
                          << line << " (Unsafe function: " << func << ")" << std::endl;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file.cpp>" << std::endl;
        return 1;
    }

    VulnerabilityScanner scanner;
    scanner.scanFile(argv[1]);

    return 0;
}
```
