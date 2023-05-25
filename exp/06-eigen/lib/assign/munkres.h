
// Bug remains when computing the following matrix:
// Array<int, 4, 4, RowMajor> m1;
// m1 <<  4,  2,  5,  7,
//        8,  3, 10,  8,
//       12,  5,  4,  5,
//        6,  3,  7, 12;

#ifndef _MUNKRES_H
#define _MUNKRES_H

#include <vector>
#include <climits>
#include <utility>
#include <iostream>
#include "Eigen/Dense"

using namespace Eigen;


class Munkres
{
public:
    //expecting a square matrix
    Munkres(const Array<int, Dynamic, Dynamic, RowMajor>&);
    std::vector< std::pair<int, int> > run();

private:
    int N_;
    Array<int, Dynamic, Dynamic, RowMajor> C_;
    std::vector<bool> row_cover_;
    std::vector<bool> col_cover_;
    std::pair<int, int> Z0_;
    Array<int, Dynamic, Dynamic, RowMajor> starred_;
    Array<int, Dynamic, 2, RowMajor> path_;

    int step1();
    int step2();
    int step3();
    int step4();
    int step5();
    int step6();
    void clear_covers();
    std::pair<int, int> find_a_zero();
    int find_star_in_row(int);
    int find_star_in_col(int);
    int find_prime_in_row(int);
    // void augment_path(const Array<int, Dynamic, 2, RowMajor>&, int);
    void augment_path(int);
    void erase_primes();
    int find_epsilon();
    void pad_matrix(const Array<int, Dynamic, Dynamic, RowMajor>&, Array<int, Dynamic, Dynamic, RowMajor>&);
};


#endif // _MUNKRES_H
