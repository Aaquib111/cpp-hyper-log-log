#include <iostream>
#include "hyperloglog.h"
#include <random>

int main() {
    HyperLogLog hll(64);
    int uniqueElements;
    int totalElements;

    std::cout << "Enter number of total elements: " << "\n";
    std::cin >> totalElements;
    std::cout << "Enter number of unique elements to estimate: " << "\n";
    std::cin >> uniqueElements;

    // Create dummy elements and add them to the HyperLogLog object
    for (int i = 0; i < totalElements; ++i) {
        // Generating dummy elements with some duplicates
        std::string value = "element" + std::to_string(i % uniqueElements);
        Element elem(value);
        hll.add(elem);
    }

    // Estimate the cardinality
    double estimatedCardinality = hll.estimateCardinality();
    double error = (estimatedCardinality - uniqueElements) / uniqueElements * 100;
    std::cout << "Total number of unique elements: " << uniqueElements << "\n";
    std::cout << "Estimated number of unique elements: " << estimatedCardinality << "\n";
    std::cout << "Percent Error: " << error << "%" << "\n";

    return 0;
}
