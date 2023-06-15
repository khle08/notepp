
#include "test.h"

typedef Eigen::Matrix<float, 1, 10, Eigen::RowMajor> FEATURE;


TestLibs::TestLibs()
{

}


TestLibs::~TestLibs()
{
    
}


int TestLibs::matrixTest()
{
    // ref: https://www.cnblogs.com/dzw2017/p/8427677.html
    
    // Matrix initialization
    MatrixXd mat_xd66(6, 6);
    // Matrix<int, 6, 6, RowMajor> m;

    mat_xd66 << 11, 12, 13, 14, 15, 16,
                21, 22, 23, 24, 25, 26,
                31, 32, 33, 34, 35, 36,
                41, 42, 43, 44, 45, 46,
                51, 52, 53, 54, 55, 56,
                61, 62, 63, 64, 65, 66;

    MatrixXd mat_rand = MatrixXd::Random(3,3);
    MatrixXd mat_cont = MatrixXd::Constant(3, 3, 1.2);
    MatrixXd mat_idnt = MatrixXd::Identity(3, 3);
    MatrixXd mat_zero = MatrixXd::Zero(3, 3);
    MatrixXd mat_ones = MatrixXd::Ones(6, 2);

    print(mat_xd66);
    print("idx[0][3]: " << mat_xd66(0, 3) << "\n");
    print("size: " << mat_xd66.size());  // 36
    print("row: " << mat_xd66.rows() << ", col: " << mat_xd66.cols() << "\n");
    print("row[2]:\n" << mat_xd66.row(2) << "\n");
    print("col[3]:\n" << mat_xd66.col(3) << "\n");

    // The value that saved in matrix can be modified
    mat_xd66.row(2)[3] = 999;
    print(mat_xd66 << "\n");
    print("row[2]:\n" << mat_xd66.row(2) << "\n");

    // MatrixXd mat_prod = mat_xd66 * mat_ones;  // dot product
    // print(mat_prod);

    // VectorXf v(10);
    // v.fill(0);
    // print(v);

    // m.resize(3, 12);
    // print(m);

    FEATURE ft;
    float f[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11};

    for (int i = 0; i < sizeof(f) / 4; i++) {
        ft[i] = f[i];
    }

    print(ft);

    return 0;
}


int TestLibs::munkres()
{
    // MatrixXd m1(4, 4);
    Array<int, 4, 4, RowMajor> m1;
    // m1 << 1, 1, 1, 1,
    //       1, 1, 1, 1,
    //       1, 1, 1, 1,
    //       1, 1, 1, 1;
    m1 <<  4,  2,  5,  7,
           8,  3, 10,  8,
          12,  5,  4,  5,
           6,  3,  7, 12;

    // MatrixXd m2(6, 6);
    Array<int, 6, 6, RowMajor> m2;
    m2 << 62, 75, 80, 93, 95, 97,
          75, 80, 82, 85, 71, 97,
          80, 75, 81, 98, 90, 97,
          78, 82, 84, 80, 50, 98,
          90, 85, 85, 80, 85, 99,
          65, 75, 80, 75, 68, 96;

    // print(m2);

    Munkres m = Munkres(m2);  // Error when input is m1

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<int, int>> res = m.run();
    auto t2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < res.size(); i++) {
        print(res[i].first << " " << res[i].second);
    }


    std::chrono::duration<double> diff = t2 - t1;
    print("proc: " << diff.count() << " s");
    return 0;
}
