#include <iostream>
#include <string>

int main()
{
	std::string stuNames[] = {"liubei", "guanyu", "zhangfei"};
	std::string courseNames[] = {"lang ", "math ", "eng "};
	const int ROW = 3;  // sizeof(stuNames) / sizeof(stuNames[0]);
	const int COL = 3;  // sizeof(courseNames) / sizeof(courseNames[0]);

	std::cout << stuNames << std::endl;
	double scores[ROW][COL];

	for (int i = 0; i < ROW; i++){
		for  (int j = 0; j < COL; j++){
			std::cout << stuNames[i] << "'s " << courseNames[j] << "grade: ";
			std::cin >> scores[i][j];
		}
	}
}