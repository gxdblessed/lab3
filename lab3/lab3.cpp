#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
};

struct List {
    int size = 0;
    int currentPosition = 0;
    Node* lastNode = nullptr;

    void toPreposition(int targetPosition) {
        int steps = targetPosition - currentPosition;
        if (steps < 0) {
            steps += size; 
        }
        for (int i = 0; i < steps; ++i) {
            lastNode = lastNode->next;
            currentPosition = (currentPosition + 1) % size; 
        }
    }


    void add(int newValue) {
        toPreposition(size);
        Node* newNode = new Node();
        newNode->value = newValue;
        if (size == 0) {
            lastNode = newNode;
            lastNode->next = newNode;
        }
        else {
            newNode->next = lastNode->next;
            lastNode->next = newNode;
            lastNode = newNode;
        }
        size++;
        currentPosition++;
    }

    void insert(int index, int newValue) {
        if (index == size) {
            add(newValue);
            return;
        }
        toPreposition(index);
        Node* newNode = new Node();
        newNode->value = newValue;
        newNode->next = lastNode->next;
        lastNode->next = newNode;
        if (index == size - 1) {
            lastNode = newNode;
        }
        size++;
    }

    int elementAt(int index) {
        toPreposition(index);
        return lastNode->next->value;
    }

    void removeAt(int index) {
        toPreposition(index);
        Node* toRemove = lastNode->next;
        lastNode->next = toRemove->next;
        delete toRemove;
        size--;
        if (index == size) { lastNode = nullptr; }
        if (currentPosition >= size) { currentPosition = 0; }
    }

    void insertBeforeNegative() {
        for (int i = 0; i < size; i++) {
            if (lastNode->next->value < 0) {
                insert(i, 1);
            }
            lastNode = lastNode->next;
        }
    }

    void removeNegative() {
        if (size == 0) { return; }
        for (int i = 0; i < size; i++) {
            if (lastNode->next->value < 0) {
                removeAt(i);
            }
            else {
                lastNode = lastNode->next;
            }
        }
    }

    int count(int targetValue) {
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (lastNode->value == targetValue) {
                count++;
            }
            lastNode = lastNode->next;
        }
        return count;
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            Node* toDelete = lastNode->next;
            lastNode->next = toDelete->next;
            delete toDelete;
        }
        lastNode = nullptr;
        size = 0;
        currentPosition = 0;
    }

    int count() {
        return size;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    List myList;
    int userCommand;

    do {
        cout << "1: Добавить элемент\n";
        cout << "2: Вставить значение в позицию\n";
        cout << "3: Удалить из позиции\n";
        cout << "4: Получить значение из позиции\n";
        cout << "5: Общее количество элементов\n";
        cout << "6: Вставить 1 перед отрицательными\n";
        cout << "7: Удалить отрицательные элементы\n";
        cout << "8: Посчитать количество определенного значения\n";
        cout << "9: Очистить список\n";
        cout << "0: Выйти из программы\n";
        cout << "Введите команду: ";
        cin >> userCommand;

        switch (userCommand) {
        case 1:
            int value;
            cout << "Введите число: ";
            cin >> value;
            myList.add(value);
            break;

        case 2:
            cout << "Введите позицию: ";
            int index;
            cin >> index;
            if (index >= myList.count() || index < 0) {
                cout << "Некорректная позиция!\n";
            }
            else {
                cout << "Введите значение: ";
                cin >> value;
                myList.insert(index, value);
            }
            break;

        case 3:
            cout << "Введите позицию: ";
            cin >> index;
            if (index >= myList.count() || index < 0) {
                cout << "Некорректная позиция!\n";
            }
            else {
                myList.removeAt(index);
            }
            break;

        case 4:
            cout << "Введите позицию: ";
            cin >> index;
            if (index >= myList.count() || index < 0) {
                cout << "Некорректная позиция!\n";
            }
            else {
                cout << "Значение: " << myList.elementAt(index) << endl;
            }
            break;

        case 5:
            cout << "Общее количество элементов: " << myList.count() << endl;
            break;

        case 6:
            myList.insertBeforeNegative();
            break;

        case 7:
            myList.removeNegative();
            break;

        case 8:
            cout << "Введите значение для подсчета: ";
            cin >> value;
            cout << "Количество: " << myList.count(value) << endl;
            break;

        case 9:
            myList.clear();
            cout << "Список очищен\n";
            break;

        case 0:
            cout << "Программа завершена\n";
            break;

        default:
            cout << "Неизвестная команда!\n";
            break;
        }
    } while (userCommand != 0);

    return 0;
}
