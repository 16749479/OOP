#include <iostream>
#include <fstream>

using namespace std;

void generateInputFile(const string& filename) {
    ofstream inputFile(filename);
    if (!inputFile) {
        cerr << "Ошибка открытия файла для записи: " << filename << endl;
        return;
    }

    for (int i = 0; i < 100; ++i) {
        int number = rand() % 101 - 50; 
        inputFile << number << endl;
    }

    inputFile.close();
}

void processFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);

    if (!inputFile) {
        cerr << "Ошибка открытия входного файла: " << inputFilename << endl;
        return;
    }
    if (!outputFile) {
        cerr << "Ошибка открытия выходного файла: " << outputFilename << endl;
        return;
    }

    int num;
    int maxNumber = -50;  

    while (inputFile >> num) {
        maxNumber = max(maxNumber, num); 
    }

    if (maxNumber == 0) {
        cerr << "Максимальное число равно нулю. Деление невозможно." << endl;
        return;
    }

    double halfMax = static_cast<double>(maxNumber) / 2;

    inputFile.clear();  
    inputFile.seekg(0, ios::beg);  

    while (inputFile >> num) {
        outputFile << static_cast<double>(num) / halfMax << endl;
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    setlocale(LC_ALL, "ru");
    string inputFilename = "input.txt";
    string outputFilename = "output.txt";

    generateInputFile(inputFilename);

    processFile(inputFilename, outputFilename);

    cout << "Обработка завершена. Результаты записаны в " << outputFilename << endl;
    return 0;
}