#include <iostream>
#include <string>

template<typename T>
class ShPtrArr {
private:
    T* ptr;
    size_t* ref_count;

    void release() {
        if (ref_count) {
            --(*ref_count);
            if (*ref_count == 0) {
                delete[] ptr;
                delete ref_count;
                std::cout << "Освобождаю память: " << ptr << "\n";
                ptr = nullptr;
                ref_count = nullptr;
            }
        }
    }

public:
    ShPtrArr() : ptr(nullptr), ref_count(new size_t(1)) {}
    explicit ShPtrArr(T* p) : ptr(p), ref_count(new size_t(1)) {}
    ShPtrArr(const ShPtrArr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            ++(*ref_count);
        }
    }
    ShPtrArr& operator=(const ShPtrArr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) {
                ++(*ref_count);
            }
        }
        return *this;
    }
    ~ShPtrArr() {
        release();
    }
    T* get() const {
        return ptr;
    }
    size_t getRefCount() const {
        return (ref_count ? *ref_count : 0);
    }
    void reset(T* p = nullptr) {
        release();
        if (p) {
            ptr = p;
            ref_count = new size_t(1);
        }
        else {
            ptr = nullptr;
            ref_count = nullptr;
        }
    }
    T& operator[](size_t index) {
        return ptr[index];
    }
    const T& operator[](size_t index) const {
        return ptr[index];
    }
};

template<typename T>
void demonstrateReset(ShPtrArr<T>& arr1, ShPtrArr<T>& arr2, size_t size) {
    std::cout << "\nМассив arr1: ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr1[i] << " ";
    }
    std::cout << "\nАдрес arr1: " << arr1.get() << " | Количество ссылок: " << arr1.getRefCount() << "\n\n";

    std::cout << "Создание arr2 как копии arr1...\n";
    arr2 = arr1;
    std::cout << "Массив arr2: ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr2[i] << " ";
    }
    std::cout << "\nАдрес arr2: " << arr2.get() << " | Количество ссылок: " << arr2.getRefCount() << "\n\n";

    std::cout << "Вызов reset() для arr2...\n";
    arr2.reset();
    std::cout << "После reset() arr2:\n";
    std::cout << "Адрес arr2: " << arr2.get() << " | Количество ссылок: " << arr2.getRefCount() << "\n";
    std::cout << "Адрес arr1: " << arr1.get() << " | Количество ссылок: " << arr1.getRefCount() << "\n\n";

    std::cout << "Вызов reset() для arr1...\n";
    arr1.reset();
    std::cout << "После reset() arr1:\n";
    std::cout << "Адрес arr1: " << arr1.get() << " | Количество ссылок: " << arr1.getRefCount() << "\n\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Демонстрация работы reset() и ref_count для int\n";
        std::cout << "2. Демонстрация работы reset() и ref_count для double\n";
        std::cout << "3. Демонстрация работы reset() и ref_count для string\n";
        std::cout << "4. Выход\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            size_t size = 0;
            std::cout << "\nВведите размер массива: ";
            std::cin >> size;
            ShPtrArr<int> arr1(new int[size]);
            ShPtrArr<int> arr2;
            std::cout << "\nВведите "<< size <<" значения для массива int: ";
            for (size_t i = 0; i < size; ++i) {
                std::cin >> arr1[i];
            }
            demonstrateReset(arr1, arr2, size);
            break;
        }
        case 2: {
            size_t size = 0;
            std::cout << "\nВведите размер массива: ";
            std::cin >> size;
            ShPtrArr<double> arr1(new double[size]);
            ShPtrArr<double> arr2;
            std::cout << "\nВведите " << size << " значения для массива double: ";
            for (size_t i = 0; i < size; ++i) {
                std::cin >> arr1[i];
            }
            demonstrateReset(arr1, arr2, size);
            break;
        }
        case 3: {
            size_t size = 0;
            std::cout << "\nВведите размер массива: ";
            std::cin >> size;
            ShPtrArr<std::string> arr1(new std::string[size]);
            ShPtrArr<std::string> arr2;
            std::cout << "\nВведите " << size << " значения для массива string: ";
            for (size_t i = 0; i < size; ++i) {
                std::cin >> arr1[i];
            }
            demonstrateReset(arr1, arr2, size);
            break;
        }
        case 4:
            std::cout << "Выход...\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 4);

    return 0;
}