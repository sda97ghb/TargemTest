#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
#include <vector>

#include "String.h"

using namespace std;
using namespace utils;

class Input {
public:
    Input() {
        cout << "Enter lines (empty line to finish):" << endl;
        strcpy(m_buff, "");
    }

    bool hasNext() {
        cin.getline(m_buff, 256);
        return strcmp(m_buff, "") != 0;
    }

    String getNext() {
        return String(m_buff);
    }

private:
    char m_buff[256];
};

/**
 * @brief Первый пример, показывающий работу со строками
 *
 * Получает несколько строк с input (консоль в текущей реализации),
 * сортирует их и выводит в консоль.
 *
 * Показаны два примера с list и vector.
 */
void runDemoCase1() {
    cout << "# Demo case 1" << endl;
    {
        cout << "## vector" << endl;

        vector<String> strings;

        Input input;
        while (input.hasNext())
            strings.push_back(input.getNext());

        std::sort(begin(strings), end(strings), greater<String>());

        for (String& str : strings)
            cout << str << endl;
    }
    {
        cout << "## list" << endl;

        list<String> strings;

        Input input;
        while (input.hasNext())
            strings.push_back(input.getNext());

        strings.sort(greater<String>());

        for (String& str : strings)
            cout << str << endl;
    }
    cout << endl;
}

/**
 * @brief Второй пример, демонстрирующий внутренние особенности работы строк
 *
 * Показывает, что строки стараются по возможности ссылаться на одни и теже данные,
 * копируя их только при необходимости.
 *
 * @note Перед его запуском крайне рекомендуется в файле Log.h выставить Log = ConsoleLog.
 */
void runDemoCase2() {
    cout << "# Demo case 2" << endl;
    auto printString = [](String str) {
        cout << str << endl;
    };
    String s1 = "Jack Sparrow"; // Создание новой строки
    String s2 = s1; // Использует теже данные, что и s1
    String s3 = s2; // Использует теже данные, что и s1
    printString(s3);
    String s4 = "Captain " + s1; // Создание новой строки из литерала и создание новой строки для суммы
    printString(s4);
    cout << endl;
}

int main() {
    runDemoCase1();
    runDemoCase2();

    cout << "Success" << endl;

    return 0;
}
