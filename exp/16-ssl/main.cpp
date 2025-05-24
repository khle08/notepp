#include <iostream>
#include "encrypt.h"


int main()
{
    // 初始化文件路径
    std::vector<std::string> modelFiles = {"data/test.jpg", "data/test2.jpg"};
    std::string encryptedFile = "models.enc";
    std::string outputDir = "decrypted";
    std::string keyFile = "key.bin";

    // 创建加密器实例
    ModelEncryptor encryptor(modelFiles, encryptedFile, outputDir, keyFile);

    // 1. 测试密码派生密钥
    std::string password;
    std::cout << "Enter password for encryption: ";
    std::getline(std::cin, password);

    if (encryptor.encryptWithPassword(password)) {
        std::cout << "Models encrypted successfully with password to " << encryptedFile << std::endl;
    } else {
        std::cerr << "Password encryption failed" << std::endl;
        return 1;
    }

    std::cout << "Enter password for decryption: ";
    std::getline(std::cin, password);

    if (encryptor.decryptWithPassword(password)) {
        std::cout << "Models decrypted successfully with password to " << outputDir << std::endl;
    } else {
        std::cerr << "Password decryption failed" << std::endl;
        return 1;
    }

    // 2. 测试固定密钥（首次生成，之后加载）
    if (encryptor.encryptWithFixedKey(true)) { // 生成新的 key.bin
        std::cout << "Models encrypted successfully with fixed key to " << encryptedFile << std::endl;
    } else {
        std::cerr << "Fixed key encryption failed" << std::endl;
        return 1;
    }

    if (encryptor.decryptWithFixedKey()) { // 从 key.bin 加载
        std::cout << "Models decrypted successfully with fixed key to " << outputDir << std::endl;
    } else {
        std::cerr << "Fixed key decryption failed" << std::endl;
        return 1;
    }

    return 0;
}