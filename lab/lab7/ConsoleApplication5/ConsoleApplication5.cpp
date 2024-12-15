#include <iostream>
#include "Queue.h"

void menu() {
    std::cout << "Выберите действие:\n"
        << "1. Добавить элемент \n"
        << "2. Удалить элемент \n"
        << "3. Посмотреть первый элемент \n"
        << "4. Проверить, пуста ли очередь\n"
        << "5. Узнать размер очереди\n"
        << "6. Вывести положительные элементы\n"
        << "7. Вывести отрицательные элементы\n"
        << "8. Выйти\n";
}

template <typename T>
void testQueue() {
    Queue<T> queue;
    int choice;
    do {
        menu();
        std::cin >> choice;
        try {
            switch (choice) {
            case 1: {
                T value;
                std::cout << "Введите значение: ";
                std::cin >> value;
                queue.enqueue(value);
                std::cout << "Элемент добавлен.\n";
                break;
            }
            case 2: {
                T value = queue.dequeue();
                std::cout << "Удалённый элемент: " << value << "\n";
                break;
            }
            case 3: {
                std::cout << "Первый элемент: " << queue.front() << "\n";
                break;
            }
            case 4: {
                std::cout << (queue.isEmpty() ? "Очередь пуста.\n" : "Очередь не пуста.\n");
                break;
            }
            case 5: {
                std::cout << "Размер очереди: " << queue.size() << "\n";
                break;
            }
            case 6: {
                auto positiveIter = queue.positiveIterator();
                std::cout << "Положительные элементы:\n";
                while (positiveIter.hasNext()) {
                    std::cout << positiveIter.next() << "\n";
                }
                break;
            }
            case 7: {
                auto negativeIter = queue.negativeIterator();
                std::cout << "Отрицательные элементы:\n";
                while (negativeIter.hasNext()) {
                    std::cout << negativeIter.next() << "\n";
                }
                break;
            }
            case 8:
                std::cout << "Выход...\n";
                break;
            default:
                std::cout << "Неверный выбор.\n";
            }
        }
        catch (const QueueException& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    } while (choice != 8);
}

int main() {
    setlocale(LC_ALL, "ru");
    std::cout << "Выберите тип данных:\n"
        << "1. int\n"
        << "2. double\n"
        << "3. string\n";
    int typeChoice;
    std::cin >> typeChoice;

    switch (typeChoice) {
    case 1:
        testQueue<int>();
        break;
    case 2:
        testQueue<double>();
        break;
    case 3:
        testQueue<std::string>();
        break;
    default:
        std::cout << "Неверный тип данных.\n";
    }

    return 0;
}
