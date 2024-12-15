#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

class CustomException : public std::exception {
private:
    std::string message;
    double errorValue;
    int errorCode;

public:
    CustomException(const std::string& msg, double value, int code)
        : message(msg), errorValue(value), errorCode(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getValue() const {
        return errorValue;
    }

    int getCode() const {
        return errorCode;
    }
};

void calculateZ1(double x, double& z1) {
    try {
        if (x <= 0) {
            throw CustomException("Невалидное значение x: должно быть больше 0", x, 1);
        }

        double numerator = std::sqrt(std::pow(3 * x + 2, 2) - 24 * x);
        double denominator = 3 * std::sqrt(x) - (2 / std::sqrt(x));

        if (denominator == 0) {
            throw CustomException("Деление на ноль в знаменателе", denominator, 2);
        }

        z1 = numerator / denominator;
    }
    catch (const CustomException& e) {
        std::cerr << "Ошибка при вычислении z1: " << e.what() << "\n";
        std::cerr << "Проблемное значение: " << e.getValue() << "\n";
        std::cerr << "Код ошибки: " << e.getCode() << "\n";
        throw; 
    }
}

void calculateZ2(double x, double& z2) {
    try {
        if (x < 0) {
            throw CustomException("Невалидное значение x: должно быть неотрицательным", x, 3);
        }

        z2 = -std::sqrt(x);
    }
    catch (const CustomException& e) {
        std::cerr << "Ошибка при вычислении z2: " << e.what() << "\n";
        std::cerr << "Проблемное значение: " << e.getValue() << "\n";
        std::cerr << "Код ошибки: " << e.getCode() << "\n";
        throw; 
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    double x;
    std::cout << "Введите значение x: ";

    try {
        std::cin >> x;
        if (std::cin.fail()) {
            throw CustomException("Введено нечисловое значение", 0, 4);
        }

        double z1 = 0, z2 = 0;
        calculateZ1(x, z1);
        calculateZ2(x, z2);

        std::cout << "z1 = " << z1 << "\n";
        std::cout << "z2 = " << z2 << "\n";

        if (std::abs(z1 - z2) < 1e-6) {
            std::cout << "Значения z1 и z2 приблизительно равны.\n";
        }
        else {
            std::cout << "Значения z1 и z2 различаются.\n";
        }
    }
    catch (const CustomException& e) {
        std::cerr << "Произошло исключение: " << e.what() << "\n";
        if (e.getCode() == 4) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    return 0;
}