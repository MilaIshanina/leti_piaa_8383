#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

using namespace std;

class Path {
private:
    char nameFrom;
    char nameOut;
    double weightPath;

public:
    Path(char nameFrom, char nameOut, double weightPath)
        : nameFrom(nameFrom), nameOut(nameOut), weightPath(weightPath) {}

    char getNameFrom() const {
        return nameFrom;
    }

    char getNameOut() const {
        return nameOut;
    }

    double getWeightPath() const {
        return weightPath;
    }
};

bool comp(Path a, Path b) {//компаратор
    return a.getWeightPath() < b.getWeightPath();
}

bool func(std::vector<Path>* vector, char curChar, char endChar, std::vector<char>* answer, int depth) {
    depth++;

    std::cout << setw(depth + 1) << ' ' << "Обрабатываем вершину:    " << curChar << std::endl;

    if (curChar == endChar) {    //выход из рекурсии
        std::cout << setw(depth + 1) << ' ' << "Дошли до искомой вершины    " << endChar << ". Функция возвращает true и завершает работу." << std::endl;
        return true;
    }

    //curChar - текущая вершина
    
    std::cout << setw(depth + 1) << ' ' << "Поиск путей, ведущих из этой вершины." << std::endl;
    std::vector<Path> temporaryVector;
    temporaryVector.reserve(0);
    for (Path path : *vector) {// будут пройдены все вершины в векторе
        if (path.getNameFrom() == curChar) {//отбирает все пути из нужной вершины
            std::cout << setw(depth + 1) << ' ' << "Так как вершина   " << path.getNameOut() << "   исходит из текущей вершины, записываем этот путь в векор" << std::endl;
            temporaryVector.emplace_back(path);//записывается в вектор
        }
    }

    //т к нужен самый дешевый путь то соитируем

    std::cout << setw(depth + 1) << ' ' << "Сортировка вершин по минимальному весу." << std::endl;

    std::sort(temporaryVector.begin(), temporaryVector.end(), comp);


    for (Path path : temporaryVector) {//проходимся по всем вершинам
        if (func(vector, path.getNameOut(), endChar, answer, depth)) {//новая переменная 
            depth--;
            std::cout << setw(depth + 1) << ' ' << "Записываем вершину    " << path.getNameOut() <<    "    в вектор ответа" << std::endl;
            answer->emplace_back(path.getNameOut());
            return true;
        }
    }

    return false;
}

int main() {
    setlocale(LC_ALL, "rus");
    int depth = 0;
    int flag = 1;

    std::vector<Path> vector;
    vector.reserve(0);

    std::vector<char> answer;
    answer.reserve(0);

    char startChar;
    char endChar;
    std::cout << "Пожалуйста, введите начальную вершину и конечную, а также ребра графа с указанием его веса: " << std::endl;

    std::cin >> startChar;
    std::cin >> endChar;


    char start, end;
    double weight;

    
    while (std::cin >> start >> end >> weight) {
        vector.emplace_back(Path(start, end, weight));
    }

    std::cout << "Запускается функция жадного алгоритма" << std::endl;

    if (!func(&vector, startChar, endChar, &answer, depth))
    {
        std::cout << "Error!" << std::endl;
        flag = 0;
    }

    if (flag)
    {
        std::cout << "Функция жадного алгоритма завершает работую" << std::endl;
        std::cout << "Добавляется в вектор ответа начальная вершина." << std::endl;
        answer.emplace_back(startChar);
        std::cout << "Реверсируем вектор ответа." << std::endl;
        std::reverse(answer.begin(), answer.end());

        std::cout << "Ответ:    " << std::endl;
        for (char sym : answer) {
            std::cout << sym;
        }
    }


    return 0;
}