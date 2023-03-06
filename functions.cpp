#include<iostream>
#include<fstream>
#include"functions.h"

struct TRAIN {
    char destination[20];
    int number;
    char time[6];
};

TRAIN* train;
extern int ammount=0;

extern int correct()
{
    bool IsCorrect;
    int number;
    do {
        IsCorrect = true;
        std::cin >> number;
        if (std::cin.fail()) {
            std::cin.clear();
            while (std::cin.get() != '\n');
            IsCorrect = false;
            std::cout << "Ошибка!\n";
        }
        if (IsCorrect && std::cin.get() != '\n') {
            std::cin.clear();
            while (std::cin.get() != '\n');

            std::cout << "Ошибка!\n";
            IsCorrect = false;
        }
    } while (!IsCorrect);
    return number;
}

TRAIN* addStruct(TRAIN* train, int ammount)
{
    if (ammount == 0) {
        train = new TRAIN[ammount + 1];
    }
    else {
        TRAIN* tempTrain = new TRAIN[ammount + 1];

        for (int i = 0; i < ammount; ++i) {
            tempTrain[i] = train[i];
        }
        delete[]train;
        train = tempTrain;
    }
    return train;
}

extern void addNew() {
    int choice = 0;
    do {
        train = addStruct(train, ammount);
        std::cout << "\nВведите пункт назначения: ";
        std::cin.getline(train[ammount].destination, 20);
        std::cout << "\nВведите номер поезда: ";
        train[ammount].number = correct();
        std::cout << "\nВведите время отправления: ";
        std::cin.getline(train[ammount].time, 6);
        ++ammount;
        std::cout << "Хотите продолжить добавлять элементы в массив?\n";
        std::cout << "1 - Да.\n";
        std::cout << "2 - Нет.\n";
        choice = correct();
        if (choice == 2) std::cout << "\nВы закончили добавлять элементы в массив.\n\n";
    } while (choice != 2);
}  

extern void output() {
    system("cls");
    if (ammount == 0) {
        std::cout << "Нет записей" << std::endl;
    }
    else {
        for (register int i = 0; i < ammount; i++) {
            std::cout << "Запись " << i + 1 << "\n";
            std::cout << train[i].destination << "\n";
            std::cout << train[i].number << "\n";
            std::cout << train[i].time << "\n\n";
        }
    }
}

extern void search() {
    system("cls");
    if (ammount == 0) {
        std::cout << "\nНет записей.\n\n";
    }

    std::cout << "Введите пункт назначения: ";
    char strToSearch[20];
    std::cin.getline(strToSearch, 20);
    bool search = false;
    for (register int i = 0; i < ammount; ++i) {
        if (!strcmp(train[i].destination, strToSearch)) {
            std::cout << "\nЗапись найдена!\n";
            std::cout << "Номер записи: " << i + 1 << "\n";
            std::cout << train[i].destination << "\n";
            std::cout << train[i].number << "\n";
            std::cout << train[i].time << "\n\n";
            search = true;
        }
    }
    if (!search) {
        std::cout << "\nЗаписи с таким параметром нет.\n";
    }
}

extern void sort() {
    if (ammount == 0) {
        std::cout << "Нет записей.\n\n";
    }
    else if (ammount == 1) {
        std::cout << "Одна запись.\n\n";
    }
    else {
        struct TRAIN vspom;
        for (int i = 0; i < ammount - 1; ++i) {
            for (int j = i + 1; j < ammount; ++j) {
                if (strcmp(train[i].destination, train[j].destination) > 0) {
                    vspom = train[i];
                    train[i] = train[j];
                    train[j] = vspom;
                }
            }
        }
    }
}

extern void saveInFile() {
    if (ammount == 0) {
        std::cout << "Нет записей\n";
    }
    else {
        std::ofstream fout("train.dat");
        if (!fout.is_open()) {
            std::cout << "Файл не открыт!\n";
            return;
        }
        for (int i = 0; i < ammount; i++) {
            fout << train[i].destination << "\n";
            fout << train[i].number << "\n";
            fout << train[i].time << "\n";
        }
        fout.close();
        std::cout << "Действие успешно завершено\n\n";
    }
}

extern void readFromFile() {
    std::fstream fin("train.dat");
    if (!fin.is_open()) {
        std::cout << "Файл не открыт!\n";
        return;
    }
    while (!fin.eof())
    {
        train = addStruct(train, ammount);
        fin >> train[ammount].destination;
        fin >> train[ammount].number;
        fin >> train[ammount].time;
        ammount++;
    }
    fin.close();
    std::cout << "Действие успешно завершено!\n\n";
}