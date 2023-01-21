
#include <iostream>
#include <complex>
#include <valarray>
 
const double PI = 3.141592653589793238460;
 
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
 
// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;
 
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
 
    // conquer
    fft(even);
    fft(odd);
 
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
 
// inverse fft (in-place)
void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    fft( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}
 
int main()
{
    const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
    CArray data(test, 8);
 
    // forward fft
    fft(data);
 
    std::cout << "fft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
 
    // inverse fft
    ifft(data);
 
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    return 0;
}





#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

//recursive implementation of the FFT algorithm 
void fft(complex<double>* input, complex<double>* output, int N)
{
    if (N==1){
        output[0] = input[0];
        return;
    }

    complex<double> *even = new complex<double>[N/2];
    complex<double> *odd = new complex<double>[N/2];

    for (int i=0; i<N/2; i++){
        even[i] = input[2*i];
        odd[i] = input[2*i +1];
    }

    complex<double> *even_fft = new complex<double>[N/2];
    complex<double> *odd_fft = new complex<double>[N/2];

    fft(even, even_fft, N/2);
    fft(odd, odd_fft, N/2);

    for(int k=0; k<N/2; k++){
        double kth = -2 * k * M_PI / N;
        complex<double> w_k = {cos(kth), sin(kth)};
        output[k] = even_fft[k] + w_k * odd_fft[k];
        output[k + N/2] = even_fft[k] - w_k * odd_fft[k];
    }

    delete[] even;
    delete[] odd;
    delete[] even_fft;
    delete[] odd_fft;

}

int main()
{
    int N;
    cin >> N;
    complex<double> *input = new complex<double>[N];
    complex<double> *output = new complex<double>[N];

    for(int i=0; i<N; i++){
        double a, b;
        cin >> a >> b;
        input[i] = {a, b};
    }

    fft(input, output, N);

    for(int i=0; i<N; i++){
        cout << output[i] << endl;
    }

    delete[] input;
    delete[] output;

    return 0;
}