#include <iostream>
#include <string> 
#include <algorithm> 

class EncryptionStrategy {
public:
    virtual std::string encrypt(const std::string& data, const std::string& key) = 0;
    virtual std::string decrypt(const std::string& data, const std::string& key) = 0;
    virtual ~EncryptionStrategy() = default;
};

class XOREncryption : public EncryptionStrategy {
public:
    std::string encrypt(const std::string& data, const std::string& key) override {
        std::string result = data;
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] ^= key[i % key.size()];
        }
        return result;
    }

    std::string decrypt(const std::string& data, const std::string& key) override {
        return encrypt(data, key); 
    }
};

class ECBEncryption : public EncryptionStrategy {
public:
    static const size_t BLOCK_SIZE = 8; 

    std::string encrypt(const std::string& data, const std::string& key) override {
        std::string result = data;
        size_t numBlocks = (result.size() + BLOCK_SIZE - 1) / BLOCK_SIZE; 

        for (size_t i = 0; i < numBlocks; ++i) {
            size_t blockStart = i * BLOCK_SIZE;
            size_t blockEnd = std::min(blockStart + BLOCK_SIZE, result.size());
            for (size_t j = blockStart; j < blockEnd; ++j) {
                result[j] = ~result[j]; 
            }
        }

        return result;
    }

    std::string decrypt(const std::string& data, const std::string& key) override {
        return encrypt(data, key); 
    }
};


class Encryptor {
private:
    std::unique_ptr<EncryptionStrategy> strategy;

public:
    void setStrategy(EncryptionStrategy* newStrategy) {
        strategy.reset(newStrategy);
    }

    std::string encrypt(const std::string& data, const std::string& key) {
        if (!strategy) throw std::logic_error("Стратегия шифрования не установлена");
        return strategy->encrypt(data, key);
    }

    std::string decrypt(const std::string& data, const std::string& key) {
        if (!strategy) throw std::logic_error("Стратегия шифрования не установлена");
        return strategy->decrypt(data, key);
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    Encryptor encryptor;

    std::string originalText = "Hello, World!";
    std::string key = "key";

    std::cout << "\nТестирование XOR шифрования:" << std::endl;
    encryptor.setStrategy(new XOREncryption());
    std::string encryptedText = encryptor.encrypt(originalText, key);
    std::string decryptedText = encryptor.decrypt(encryptedText, key);

    std::cout << "Исходный текст: " << originalText << std::endl;
    std::cout << "Зашифрованный текст: " << encryptedText << std::endl;
    std::cout << "Расшифрованный текст: " << decryptedText << std::endl;

    std::cout << "\nТестирование ECB шифрования:" << std::endl;
    encryptor.setStrategy(new ECBEncryption());
    encryptedText = encryptor.encrypt(originalText, key);
    decryptedText = encryptor.decrypt(encryptedText, key);

    std::cout << "Исходный текст: " << originalText << std::endl;
    std::cout << "Зашифрованный текст: " << encryptedText << std::endl;
    std::cout << "Расшифрованный текст: " << decryptedText << std::endl;

    return 0;
}
