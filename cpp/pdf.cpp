
#include <cmath>      // For exp() and sqrt()
#include <iomanip>    // For std::setprecision
#include <iostream>


// Function to compute the PDF of a normal distribution
double normal_pdf(double x, double mu, double sigma) {
    // Constant factor of the normal distribution
    const double pi = 3.14159265358979323846;
    double coefficient = 1.0 / (sigma * std::sqrt(2 * pi));
    
    // Exponent factor of the normal distribution
    double exponent = -0.5 * std::pow((x - mu) / sigma, 2);
    
    // Return the PDF value
    return coefficient * std::exp(exponent);
}


int main() {
    double x, mu, sigma;

    // Input values
    std::cout << "Enter x (the point for PDF calculation): ";
    std::cin >> x;
    std::cout << "Enter mu (mean of the distribution): ";
    std::cin >> mu;
    std::cout << "Enter sigma (standard deviation of the distribution): ";
    std::cin >> sigma;

    // Calculate and display the PDF
    double result = normal_pdf(x, mu, sigma);
    std::cout << std::fixed << std::setprecision(6); // Set precision for output
    std::cout << "The PDF of N(" << mu << ", " << sigma << "^2) at x = " << x << " is " << result << std::endl;

    return 0;
}
