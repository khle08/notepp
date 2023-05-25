
#include "test.h"


TestLibs::TestLibs()
{

}


TestLibs::~TestLibs()
{
    
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
