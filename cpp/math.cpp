
#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <type_traits> // For std::enable_if


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
double computeVariance(std::vector<T>& vec, T mean) {
    double sumSquaredDiffs = 0;
    // double mean = computeMean(vec);

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


// Template function to calculate Gaussian PDF for a single value
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
gaussianPDF(T x, T mu, T sigma) {
    // Check that sigma is positive to avoid division by zero
    if (sigma <= 0) {
        throw std::invalid_argument("Standard deviation must be positive");
    }

    // Calculate the normalization factor (1 / (sigma * sqrt(2 * pi)))
    T normalization = 1.0 / (sigma * std::sqrt(2.0 * M_PI));

    // Calculate the exponent term
    T exponent = -0.5 * std::pow((x - mu) / sigma, 2);

    // Return the PDF value
    return normalization * std::exp(exponent);
}

// Template function to calculate Gaussian PDF for a vector of values
template <typename T>
std::vector<T> NormalPDF(const std::vector<T>& values, T mu, T sigma) {
    std::vector<T> pdfValues;
    pdfValues.reserve(values.size());

    // Calculate PDF for each value in the vector
    for (const auto& x : values) {
        pdfValues.push_back(gaussianPDF(x, mu, sigma));
    }

    return pdfValues;
}


template <typename T>
std::vector<T> normNumGenerator(std::vector<T>& values, size_t numSamples)
{
    // Calculate mean and standard deviation from the input vector
    T mean = computeMean(values);
    T var = computeStandardDeviation(values, mean);

    // Random number generator setup
    std::random_device rd;            // Seed
    std::mt19937 generator(rd());     // Mersenne Twister generator
    std::normal_distribution<T> distribution(mean, var);

    // Generate random numbers
    std::vector<T> randomNumbers;
    randomNumbers.reserve(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        randomNumbers.push_back(distribution(generator));
    }

    return randomNumbers;
}



int main() {
    std::vector<int> numbers = {58, 76, 77, 82, 85, 88, 90, 92, 92, 96, 99};

    double median = computeMedian(numbers);
    
    std::cout << "Median: " << median << std::endl;

    float power = pow(pow(-9.58, 2) + pow(5.36, 2), 0.5);
    std::cout << "power: " << power << std::endl;

    std::vector<float> values = {58.0, 76.0, 77.0};
    // std::vector<double> pdf = NormalPDF(values, 60.0, 1.0);
    // for (int i = 0; i < pdf.size(); i++) {
    //     std::cout << pdf[i] << std::endl;
    // }

    std::vector<float> samples = normNumGenerator(values, 1);
    for (int i = 0; i < samples.size(); i++) {
        std::cout << samples[i] << std::endl;
    }

    return 0;
}
