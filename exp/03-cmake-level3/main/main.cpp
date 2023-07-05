#include <iostream>

#include "src/say-hello/hello.hpp"


std::string getDBData(std::string recvData) {
    // 确保函数要5秒才能执行完成
    std::this_thread::sleep_for(std::chrono::seconds(3));
 
    // 处理创建数据库连接、获取数据等事情
    return "DB_" + recvData;
}

 
std::string getFileData(std::string recvData) {
    // 确保函数要5秒才能执行完成
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    // 处理获取文件数据
    return "File_" + recvData;
}


int main() {
	hello::say_hello();

	TestAsync* async = new TestAsync();
	async->env();

	chtime t1, t2;
	t1 = std::chrono::high_resolution_clock::now();
	// =================================================================
	// ref: https://blog.csdn.net/lijinqi1987/article/details/78909479

	std::future<std::string> resultFromDB = std::async(std::launch::async, 
		                                               getDBData, "Data");
	std::string fileData = getFileData("Data");

	//数据在 std::future<std::string> 对象中可获取之前，将一直阻塞 (等待)
	std::string dbData = resultFromDB.get();

	// =================================================================
	t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = t2 - t1;

	std::cout << "[main] use: " << diff.count() << std::endl;
	return 0;
}