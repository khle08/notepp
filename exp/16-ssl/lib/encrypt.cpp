
#include <fstream>
#include <cstring>
#include <iostream>

#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include "encrypt.h"


ModelEncryptor::ModelEncryptor(const std::vector<std::string>& input_files, 
                               const std::string& output_file,
                               const std::string& output_dir,
                               const std::string& key_file)
    : input_files_(input_files), output_file_(output_file), 
      output_dir_(output_dir), key_file_(key_file)
{
    // 初始化密钥和 IV 为零
    std::memset(key_, 0, sizeof(key_));
    std::memset(iv_, 0, sizeof(iv_));
    std::memset(salt_, 0, sizeof(salt_));
}

void ModelEncryptor::handleErrors() {
    ERR_print_errors_fp(stderr);
    exit(1);
}

bool ModelEncryptor::deriveAndSaveKeyIV(const std::string& password) {
    const int ITERATIONS = 100000;
    const int SALT_LEN = 16;

    // 生成随机盐
    if (RAND_bytes(salt_, SALT_LEN) != 1) {
        handleErrors();
    }

    // 派生密钥 (32 字节) 和 IV (16 字节)
    unsigned char derived[32 + AES_BLOCK_SIZE];
    if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt_, SALT_LEN, 
                            ITERATIONS, EVP_sha256(), 32 + AES_BLOCK_SIZE, derived)) {
        std::cerr << "PBKDF2 derivation failed" << std::endl;
        return false;
    }

    // 分割密钥和 IV
    std::memcpy(key_, derived, 32);
    std::memcpy(iv_, derived + 32, AES_BLOCK_SIZE);

    // 保存盐、密钥和 IV 到 key.bin
    std::ofstream keyOut(key_file_, std::ios::binary);
    if (!keyOut) {
        std::cerr << "Cannot open key file: " << key_file_ << std::endl;
        return false;
    }
    keyOut.write(reinterpret_cast<const char*>(salt_), SALT_LEN);
    keyOut.write(reinterpret_cast<const char*>(key_), 32);
    keyOut.write(reinterpret_cast<const char*>(iv_), AES_BLOCK_SIZE);
    keyOut.close();

    return true;
}

bool ModelEncryptor::loadAndDeriveKeyIV(const std::string& password) {
    const int SALT_LEN = 16;
    const int ITERATIONS = 100000;

    // 读取 key.bin
    std::ifstream keyIn(key_file_, std::ios::binary);
    if (!keyIn) {
        std::cerr << "Cannot open key file: " << key_file_ << std::endl;
        return false;
    }

    // 读取盐
    keyIn.read(reinterpret_cast<char*>(salt_), SALT_LEN);
    if (keyIn.gcount() != SALT_LEN) {
        std::cerr << "Failed to read salt" << std::endl;
        keyIn.close();
        return false;
    }

    // 读取存储的密钥和 IV
    unsigned char storedKey[32];
    unsigned char storedIV[AES_BLOCK_SIZE];
    keyIn.read(reinterpret_cast<char*>(storedKey), 32);
    keyIn.read(reinterpret_cast<char*>(storedIV), AES_BLOCK_SIZE);
    if (keyIn.gcount() != AES_BLOCK_SIZE) {
        std::cerr << "Failed to read key or IV" << std::endl;
        keyIn.close();
        return false;
    }
    keyIn.close();

    // 基于密码和盐派生密钥和 IV
    unsigned char derived[32 + AES_BLOCK_SIZE];
    if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt_, SALT_LEN, 
                            ITERATIONS, EVP_sha256(), 32 + AES_BLOCK_SIZE, derived)) {
        std::cerr << "PBKDF2 derivation failed" << std::endl;
        return false;
    }

    // 复制派生结果
    std::memcpy(key_, derived, 32);
    std::memcpy(iv_, derived + 32, AES_BLOCK_SIZE);

    // 验证派生结果
    if (std::memcmp(key_, storedKey, 32) != 0 || std::memcmp(iv_, storedIV, AES_BLOCK_SIZE) != 0) {
        std::cerr << "Derived key/IV does not match stored values. Wrong password?" << std::endl;
        return false;
    }

    return true;
}

bool ModelEncryptor::loadOrGenerateFixedKeyIV(bool generate_new) {
    if (generate_new) {
        // 生成随机密钥和 IV
        if (RAND_bytes(key_, 32) != 1) {
            handleErrors();
        }
        if (RAND_bytes(iv_, AES_BLOCK_SIZE) != 1) {
            handleErrors();
        }

        // 保存到 key.bin
        std::ofstream keyOut(key_file_, std::ios::binary);
        if (!keyOut) {
            std::cerr << "Cannot open key file: " << key_file_ << std::endl;
            return false;
        }
        keyOut.write(reinterpret_cast<const char*>(key_), 32);
        keyOut.write(reinterpret_cast<const char*>(iv_), AES_BLOCK_SIZE);
        keyOut.close();

        // 打印生成的密钥和 IV（仅调试用）
        std::cout << "Generated Key (hex): ";
        for (int i = 0; i < 32; ++i) {
            printf("%02x", key_[i]);
        }
        std::cout << "\nGenerated IV (hex): ";
        for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
            printf("%02x", iv_[i]);
        }
        std::cout << std::endl;

        return true;
    } else {
        // 从 key.bin 加载密钥和 IV
        std::ifstream keyIn(key_file_, std::ios::binary);
        if (!keyIn) {
            std::cerr << "Cannot open key file: " << key_file_ << std::endl;
            return false;
        }
        keyIn.read(reinterpret_cast<char*>(key_), 32);
        keyIn.read(reinterpret_cast<char*>(iv_), AES_BLOCK_SIZE);
        if (keyIn.gcount() != AES_BLOCK_SIZE) {
            std::cerr << "Failed to read key or IV" << std::endl;
            keyIn.close();
            return false;
        }
        keyIn.close();
        return true;
    }
}

bool ModelEncryptor::encryptCore(const unsigned char* key, const unsigned char* iv) {
    std::ofstream outFile(output_file_, std::ios::binary);
    if (!outFile) {
        std::cerr << "Cannot open output file: " << output_file_ << std::endl;
        return false;
    }

    // 写入 IV
    outFile.write(reinterpret_cast<const char*>(iv), AES_BLOCK_SIZE);

    // 准备元数据和数据
    std::vector<FileMeta> fileMeta;
    std::vector<char> allData;
    uint64_t currentOffset = 0;

    for (const auto& inputFile : input_files_) {
        std::ifstream inFile(inputFile, std::ios::binary | std::ios::ate);
        if (!inFile) {
            std::cerr << "Cannot open input file: " << inputFile << std::endl;
            outFile.close();
            return false;
        }

        uint64_t fileSize = inFile.tellg();
        inFile.seekg(0, std::ios::beg);
        std::vector<char> fileData(fileSize);
        inFile.read(fileData.data(), fileSize);
        inFile.close();

        FileMeta meta;
        meta.filename = inputFile;
        meta.offset = currentOffset;
        meta.length = fileSize;
        fileMeta.push_back(meta);

        allData.insert(allData.end(), fileData.begin(), fileData.end());
        currentOffset += fileSize;
    }

    // 写入元数据
    uint32_t numFiles = static_cast<uint32_t>(fileMeta.size());
    outFile.write(reinterpret_cast<const char*>(&numFiles), sizeof(numFiles));
    for (const auto& meta : fileMeta) {
        uint32_t nameLen = static_cast<uint32_t>(meta.filename.size());
        outFile.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
        outFile.write(meta.filename.c_str(), nameLen);
        outFile.write(reinterpret_cast<const char*>(&meta.offset), sizeof(meta.offset));
        outFile.write(reinterpret_cast<const char*>(&meta.length), sizeof(meta.length));
    }

    // 加密数据
    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 256, &aesKey) < 0) {
        handleErrors();
    }

    const size_t BLOCK_SIZE = AES_BLOCK_SIZE;
    unsigned char currentIV[AES_BLOCK_SIZE];
    std::memcpy(currentIV, iv, AES_BLOCK_SIZE);

    size_t dataSize = allData.size();
    size_t paddedSize = ((dataSize + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    std::vector<unsigned char> paddedData(paddedSize, static_cast<unsigned char>(BLOCK_SIZE - (paddedSize - dataSize)));
    std::memcpy(paddedData.data(), allData.data(), dataSize);

    std::vector<unsigned char> encryptedData(paddedSize);
    for (size_t i = 0; i < paddedSize; i += BLOCK_SIZE) {
        AES_cbc_encrypt(paddedData.data() + i, encryptedData.data() + i, BLOCK_SIZE, 
                        &aesKey, currentIV, AES_ENCRYPT);
    }

    outFile.write(reinterpret_cast<const char*>(encryptedData.data()), encryptedData.size());
    outFile.close();
    return true;
}

bool ModelEncryptor::decryptCore(const unsigned char* key) {
    std::ifstream inFile(output_file_, std::ios::binary);
    if (!inFile) {
        std::cerr << "Cannot open input file: " << output_file_ << std::endl;
        return false;
    }

    unsigned char iv[AES_BLOCK_SIZE];
    inFile.read(reinterpret_cast<char*>(iv), AES_BLOCK_SIZE);
    if (inFile.gcount() != AES_BLOCK_SIZE) {
        std::cerr << "Failed to read IV" << std::endl;
        inFile.close();
        return false;
    }

    uint32_t numFiles;
    inFile.read(reinterpret_cast<char*>(&numFiles), sizeof(numFiles));
    std::vector<FileMeta> fileMeta(numFiles);
    for (uint32_t i = 0; i < numFiles; ++i) {
        uint32_t nameLen;
        inFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        std::vector<char> nameBuf(nameLen);
        inFile.read(nameBuf.data(), nameLen);
        fileMeta[i].filename = std::string(nameBuf.data(), nameLen);
        inFile.read(reinterpret_cast<char*>(&fileMeta[i].offset), sizeof(fileMeta[i].offset));
        inFile.read(reinterpret_cast<char*>(&fileMeta[i].length), sizeof(fileMeta[i].length));
    }

    inFile.seekg(0, std::ios::end);
    size_t fileSize = inFile.tellg();
    inFile.seekg(AES_BLOCK_SIZE + sizeof(numFiles) + numFiles * (sizeof(uint32_t) + sizeof(uint64_t) * 2));
    for (const auto& meta : fileMeta) {
        inFile.seekg(meta.filename.size(), std::ios::cur);
    }
    size_t encryptedDataSize = fileSize - inFile.tellg();
    std::vector<unsigned char> encryptedData(encryptedDataSize);
    inFile.read(reinterpret_cast<char*>(encryptedData.data()), encryptedDataSize);
    inFile.close();

    AES_KEY aesKey;
    if (AES_set_decrypt_key(key, 256, &aesKey) < 0) {
        handleErrors();
    }

    std::vector<unsigned char> decryptedData(encryptedDataSize);
    unsigned char currentIV[AES_BLOCK_SIZE];
    std::memcpy(currentIV, iv, AES_BLOCK_SIZE);
    for (size_t i = 0; i < encryptedDataSize; i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(encryptedData.data() + i, decryptedData.data() + i, AES_BLOCK_SIZE, 
                        &aesKey, currentIV, AES_DECRYPT);
    }

    unsigned char padding = decryptedData[encryptedDataSize - 1];
    if (padding > AES_BLOCK_SIZE || padding == 0) {
        std::cerr << "Invalid padding" << std::endl;
        return false;
    }
    size_t decryptedSize = encryptedDataSize - padding;

    for (const auto& meta : fileMeta) {
        std::string outputFile = output_dir_ + "/" + meta.filename;
        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile) {
            std::cerr << "Cannot open output file: " << outputFile << std::endl;
            return false;
        }
        outFile.write(reinterpret_cast<const char*>(decryptedData.data() + meta.offset), meta.length);
        outFile.close();
    }

    return true;
}

bool ModelEncryptor::encryptWithPassword(const std::string& password) {
    if (password.empty()) {
        std::cerr << "Password cannot be empty" << std::endl;
        return false;
    }

    ERR_load_crypto_strings();
    if (!deriveAndSaveKeyIV(password)) {
        ERR_free_strings();
        return false;
    }

    bool success = encryptCore(key_, iv_);
    ERR_free_strings();
    return success;
}

bool ModelEncryptor::decryptWithPassword(const std::string& password) {
    if (password.empty()) {
        std::cerr << "Password cannot be empty" << std::endl;
        return false;
    }

    ERR_load_crypto_strings();
    if (!loadAndDeriveKeyIV(password)) {
        ERR_free_strings();
        return false;
    }

    bool success = decryptCore(key_);
    ERR_free_strings();
    return success;
}

bool ModelEncryptor::encryptWithFixedKey(bool generate_new) {
    ERR_load_crypto_strings();
    if (!loadOrGenerateFixedKeyIV(generate_new)) {
        ERR_free_strings();
        return false;
    }

    bool success = encryptCore(key_, iv_);
    ERR_free_strings();
    return success;
}

bool ModelEncryptor::decryptWithFixedKey() {
    ERR_load_crypto_strings();
    if (!loadOrGenerateFixedKeyIV(false)) {
        ERR_free_strings();
        return false;
    }

    bool success = decryptCore(key_);
    ERR_free_strings();
    return success;
}