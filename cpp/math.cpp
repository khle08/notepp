
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>


template<typename T>
double computeMedian(std::vector<T> vec) {
    // Sort the vector
    std::sort(vec.begin(), vec.end());

    int size = vec.size();
    
    // Check if the vector is empty
    if (size == 0) {
        std::cerr << "Error: Empty vector\n";
        return -1;
    }
    
    // Check if the size of the vector is odd or even
    if (size % 2 == 0) { // Even
        return (vec[size / 2 - 1] + vec[size / 2]) / 2.0;
    } else { // Odd
        return vec[size / 2];
    }
}


template<typename T>
double computeMean(std::vector<T>& vec) {
    double sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    return sum / vec.size();
}


template<typename T>
double computeVariance(std::vector<T>& vec) {
    double sumSquaredDiffs = 0;
    double mean = computeMean(vec);

    for (int i = 0; i < vec.size(); i++) {
        double diff = vec[i] - mean;
        sumSquaredDiffs += diff * diff;
    }
    return sumSquaredDiffs / vec.size();
}


template<typename T>
double computeStandardDeviation(std::vector<T>& vec) {
    double res = computeVariance(vec);
    return std::sqrt(res);
}


int main() {
    std::vector<int> numbers = {58, 76, 77, 82, 85, 88, 90, 92, 92, 96, 99};

    double median = computeMedian(numbers);
    
    std::cout << "Median: " << median << std::endl;

    float power = pow(pow(-9.58, 2) + pow(5.36, 2), 0.5);
    std::cout << "power: " << power << std::endl;

    return 0;
}
