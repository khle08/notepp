#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

#include <string>
#include <vector>
#include <openssl/aes.h>


class ModelEncryptor {
public:
    // 构造函数：初始化文件路径
    ModelEncryptor(const std::vector<std::string>& input_files, 
                   const std::string& output_file,
                   const std::string& output_dir,
                   const std::string& key_file);

    // 使用密码派生密钥进行加密
    bool encryptWithPassword(const std::string& password);

    // 使用密码派生密钥进行解密
    bool decryptWithPassword(const std::string& password);

    // 使用固定密钥进行加密（从 key.bin 加载或生成）
    bool encryptWithFixedKey(bool generate_new = false);

    // 使用固定密钥进行解密（从 key.bin 加载）
    bool decryptWithFixedKey();

private:
    // 结构体：存储文件元数据
    struct FileMeta {
        std::string filename;
        uint64_t offset;
        uint64_t length;
    };

    // 从密码派生密钥和 IV，并保存到 key.bin
    bool deriveAndSaveKeyIV(const std::string& password);

    // 从 key.bin 加载盐，并基于密码派生密钥和 IV
    bool loadAndDeriveKeyIV(const std::string& password);

    // 加载或生成固定密钥和 IV
    bool loadOrGenerateFixedKeyIV(bool generate_new);

    // 核心加密函数
    bool encryptCore(const unsigned char* key, const unsigned char* iv);

    // 核心解密函数
    bool decryptCore(const unsigned char* key);

    // 处理 OpenSSL 错误
    void handleErrors();

    // 成员变量
    std::vector<std::string> input_files_; // 输入文件列表
    std::string output_file_;              // 加密输出文件 (models.enc)
    std::string output_dir_;               // 解密输出目录
    std::string key_file_;                 // 密钥文件 (key.bin)
    unsigned char key_[32];                // 32 字节密钥
    unsigned char iv_[AES_BLOCK_SIZE];     // 16 字节 IV
    unsigned char salt_[16];               // 16 字节盐
};


#endif  // _ENCRYPT_H_
