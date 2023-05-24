
#include <chrono>
#include <iostream>

#include "munkres.h"

#define print(x) std::cout << x << std::endl


int main()
{
    print("success");

    Matrix<double> mat{
        { 4.0,  2.0,  5.0,  7.0},
        { 8.0,  3.0, 10.0,  8.0},
        {12.0,  5.0,  4.0,  5.0},
        { 6.0,  3.0,  7.0, 12.0}
    };
    mat.show(1);

    // print("col: " << mat.columns() << ", row: " << mat.rows());
    // print("idx[0][1]: " << mat(0, 1));
    // print("idx[-1][-1]: " << mat(mat.columns() - 1, mat.rows() - 1));
    // print("max: " << mat.max() << ", min: " << mat.min());

    // print("\n===== resize mat =====\n");
    // // the matrix will be cropped into nxn and the values in the cropped area will remain
    // mat.resize(2, 2, 3.14);
    // mat.show(2);

    // print("col: " << mat.columns() << ", row: " << mat.rows());
    // print("idx[0][1]: " << mat(0, 1));
    // print("idx[-1][-1]: " << mat(mat.columns() - 1, mat.rows() - 1));
    // print("max: " << mat.max() << ", min: " << mat.min());

    // print("\n===== clear mat =====\n");
    // // the shape of the matrix will remain but all the values will be turned into 0
    // mat.clear();
    // mat.show(3);
    
    // print("col: " << mat.columns() << ", row: " << mat.rows());
    // print("idx[0][1]: " << mat(0, 1));
    // print("idx[-1][-1]: " << mat(mat.columns() - 1, mat.rows() - 1));
    // print("max: " << mat.max() << ", min: " << mat.min());


    print("\n===== assignment =====\n");

    Matrix<double> mat2 {
        {62, 75, 80, 93, 95, 97},
        {75, 80, 82, 85, 71, 97},
        {80, 75, 81, 98, 90, 97},
        {78, 82, 84, 80, 50, 98},
        {90, 85, 85, 80, 85, 99},
        {65, 75, 80, 75, 68, 96}
    };

    Munkres<double> munkres;

    auto t1 = std::chrono::high_resolution_clock::now();

    munkres.solve(mat2);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    print("proc: " << diff.count() << " s");

    mat2.show(3);
    return 0;
}



