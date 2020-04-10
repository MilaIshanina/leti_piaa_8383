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

bool comp(Path a, Path b) {//����������
    return a.getWeightPath() < b.getWeightPath();
}

bool func(std::vector<Path>* vector, char curChar, char endChar, std::vector<char>* answer, int depth) {
    depth++;

    std::cout << setw(depth + 1) << ' ' << "������������ �������:    " << curChar << std::endl;

    if (curChar == endChar) {    //����� �� ��������
        std::cout << setw(depth + 1) << ' ' << "����� �� ������� �������    " << endChar << ". ������� ���������� true � ��������� ������." << std::endl;
        return true;
    }

    //curChar - ������� �������
    
    std::cout << setw(depth + 1) << ' ' << "����� �����, ������� �� ���� �������." << std::endl;
    std::vector<Path> temporaryVector;
    temporaryVector.reserve(0);
    for (Path path : *vector) {// ����� �������� ��� ������� � �������
        if (path.getNameFrom() == curChar) {//�������� ��� ���� �� ������ �������
            std::cout << setw(depth + 1) << ' ' << "��� ��� �������   " << path.getNameOut() << "   ������� �� ������� �������, ���������� ���� ���� � �����" << std::endl;
            temporaryVector.emplace_back(path);//������������ � ������
        }
    }

    //� � ����� ����� ������� ���� �� ���������

    std::cout << setw(depth + 1) << ' ' << "���������� ������ �� ������������ ����." << std::endl;

    std::sort(temporaryVector.begin(), temporaryVector.end(), comp);


    for (Path path : temporaryVector) {//���������� �� ���� ��������
        if (func(vector, path.getNameOut(), endChar, answer, depth)) {//����� ���������� 
            depth--;
            std::cout << setw(depth + 1) << ' ' << "���������� �������    " << path.getNameOut() <<    "    � ������ ������" << std::endl;
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
    std::cout << "����������, ������� ��������� ������� � ��������, � ����� ����� ����� � ��������� ��� ����: " << std::endl;

    std::cin >> startChar;
    std::cin >> endChar;


    char start, end;
    double weight;

    
    while (std::cin >> start >> end >> weight) {
        vector.emplace_back(Path(start, end, weight));
    }

    std::cout << "����������� ������� ������� ���������" << std::endl;

    if (!func(&vector, startChar, endChar, &answer, depth))
    {
        std::cout << "Error!" << std::endl;
        flag = 0;
    }

    if (flag)
    {
        std::cout << "������� ������� ��������� ��������� �������" << std::endl;
        std::cout << "����������� � ������ ������ ��������� �������." << std::endl;
        answer.emplace_back(startChar);
        std::cout << "����������� ������ ������." << std::endl;
        std::reverse(answer.begin(), answer.end());

        std::cout << "�����:    " << std::endl;
        for (char sym : answer) {
            std::cout << sym;
        }
    }


    return 0;
}