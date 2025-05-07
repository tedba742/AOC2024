#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

struct Reports {
    std::vector<int> data;
};

int validateReport(const std::vector<Reports>& allReports) {
    int validCount = 0;

    for (size_t i = 0; i < allReports.size(); ++i) {
        const Reports& report = allReports[i];

        if (report.data.size() < 2) {
            std::cout << "Report " << i + 1 << " has fewer than 2 levels, skipping validation." << std::endl;
            continue;
        }

        bool isIncreasing = true;
        bool isDecreasing = true;
        bool isValid = true;

        for (size_t j = 1; j < report.data.size(); ++j) {
            int diff = std::abs(report.data[j] - report.data[j - 1]);

            // Check if the difference between adjacent levels is between 1 and 3
            if (diff < 1 || diff > 3) {
                isValid = false;
                break;
            }

            if (report.data[j] <= report.data[j - 1]) {
                isIncreasing = false;
            }
            if (report.data[j] >= report.data[j - 1]) {
                isDecreasing = false;
            }
        }

        if (isValid && (isIncreasing || isDecreasing)) {
            validCount++;
        } else {
            std::cout << "Report " << i + 1 << " is either invalid or neither strictly increasing nor strictly decreasing." << std::endl;
        }
    }

    return validCount;
}

int main() {
    std::vector<Reports> allReports;
    std::ifstream inputFile{"input.txt"};

    if (!inputFile) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream linesAsSS{line};
        int number{};
        Reports report{};

        while (linesAsSS >> number) {
            report.data.push_back(number);
        }

        allReports.push_back(report);
    }

    inputFile.close();

    std::cout << "All Reports:" << std::endl;
    for (size_t i = 0; i < allReports.size(); ++i) {
        std::cout << "Report " << i + 1 << ": ";
        for (int num : allReports[i].data) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    int validReports = validateReport(allReports);
    std::cout << "Number of valid reports: " << validReports << std::endl;

    return 0;
}
