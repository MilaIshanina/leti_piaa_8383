#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Top {//����� �������

public:

    char name;
    double pathToTop;//���� �� ������� ������� - g
    double heuristicF;//������������� ������� - f
    char nameFromT;
    std::vector<char> coupled;//������ ��� ��������� �� ������� ������

    
    Top(char name)//�����������1 - ��������� ��� ���������� ��������� �������
        : name(name) {
        heuristicF = 0;
        pathToTop = -1;//����� �������������� ��� �������������� ������ ������ ����� ����������
        nameFromT = '-';
    }

    Top() {			//�����������2
        name = '!';		//
        heuristicF = 0;
        pathToTop = -1;	//
        nameFromT = '-';
    }

};

class Path {//����� ���� - ������ ������ ����: ������ ���� � ������� ����� ����

public:

    char nameFromP;
    char nameOutP;
    double weightPath;

    
    Path(char nameFromP, char nameOutP, double weightPath)
        : nameFromP(nameFromP), nameOutP(nameOutP), weightPath(weightPath) {}

 

    char getNameFromP() const {
        return nameFromP;
    }

    char getNameOutP() const {
        return nameOutP;
    }

    double getWeightPath() const {
        return weightPath;
    }
};

bool check(std::vector<Path>& vectorPath, std::vector<Top>& vectorTops, char endTop, bool flagM, bool flagAd)
{
    std::cout << "����������� ������� �������� �� ������������ � ������������  " << std::endl;
    if (abs(endTop - endTop) != 0) {
        std::cout << "������������� ������ �������� ��������� �� ����� ����!" << std::endl;
        flagM = false;
        
    }

    for (unsigned int i = 0; i < vectorPath.size(); i++) {
         
        if ((abs(endTop - vectorPath[i].nameFromP) - abs(endTop - vectorPath[i].nameOutP)) > vectorPath[i].weightPath) {
            std::cout << "������������ ��������. ������� ���������� false." << std::endl;
            flagM = false;
            
        }
    }
    //������� �� ������������
    if (!flagM)
    {
        for (unsigned int i = 0; i < vectorTops.size(); i++) {


            if ((abs(endTop - vectorTops[i].name) > (vectorTops[vectorTops.size() - 1].pathToTop - vectorTops[i].pathToTop)))
            {
                std::cout << "������������ ��������. ������� ���������� false." << std::endl;
                flagAd = false;
            }


        }
    }
    if (flagM)
    {
        std::cout << "��������� ��������� � ���������!" << std::endl;
        return true;
     }
    else if (!flagM && flagAd)
    {
        std::cout << "��������� ���������!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "��������� �� ��������� � �� ���������!" << std::endl;
        return false;
    }
    
}





int whatNumber(char a, std::vector<Top>& vectorTops) {
   
    for (unsigned int i = 0; i < vectorTops.size(); i++) {
        if (vectorTops[i].name == a) {
            return i;
        }
    }
    return -1;
}

bool comp(Top a, Top b) {//����������, ������������ ��� ���������� � �������� ������
    return a.heuristicF < b.heuristicF;
}

void answer(std::vector<Top>& vectorTops, char startTop, char endTop)
{
    std::cout << "����������� ������� ������ ������.  " << std::endl;
    std::vector<Top> answer;
    answer.reserve(0);
    Top temp = vectorTops[whatNumber(endTop, vectorTops)];
    std::cout << "���������� � ������ ������ ��������� �������  " << endTop << std::endl;
    answer.emplace_back(temp);
    while (temp.name != startTop) {
        temp = vectorTops[whatNumber(temp.nameFromT, vectorTops)];
        std::cout << "���������� � ������ ������ �������  " << temp.name << std::endl;
        answer.emplace_back(temp);
    }
    std::cout << "����������� ������ ������  " << std::endl;
    std::reverse(answer.begin(), answer.end());//� � �� ���������� � �������� �������, ������ reverse
    std::cout << "�����:  " << std::endl;
    for (Top ans : answer) {
        std::cout << ans.name;
    }
    std::cout << std::endl;
}

void changeInfo(std::vector<Top>& vectorTops, std::vector<Top>& openVertexes, char a, char name, double temp_G, char endTop )
{
    std::cout << "��������� ����������:  " << std::endl;

    vectorTops[whatNumber(a, vectorTops)].nameFromT = name;
    
    vectorTops[whatNumber(a, vectorTops)].pathToTop = temp_G;
    openVertexes[whatNumber(a, openVertexes)].nameFromT = name;
    openVertexes[whatNumber(a, openVertexes)].pathToTop = temp_G;
    openVertexes[whatNumber(a, openVertexes)].heuristicF = temp_G + abs(endTop - a);
    std::cout << "�������  " << a << "   �������������, ��� ������� ��   " << name << std::endl;
    std::cout << "���� �� �������  " << a << "   �����   " << temp_G << std::endl;
    std::cout << "������������� ������ ��� �������  " << a << "   �����   " << temp_G + abs(endTop - a) << std::endl;
    std::cout << "����� ���������� ����������.  " << std::endl;
}

bool A(std::vector<Path>& vectorPath, std::vector<Top>& vectorTops, char startTop, char endTop) {

    Top temp;
    double temp_G;
    std::vector<Top> closedVertexes;
    closedVertexes.reserve(0);
    std::vector<Top> openVertexes;
    openVertexes.reserve(0);

    std::cout << "� ������ �������� ������ ��������� �������    " << vectorTops[0].name << std::endl;

    openVertexes.emplace_back(vectorTops[0]);

    while (!openVertexes.empty()) {
        Top min = openVertexes[0];
        std::cout << "��������� �������� ������� " << std::endl;
        std::sort(openVertexes.begin(), openVertexes.end(), comp);
        temp = openVertexes[0]; //����������� f �� openVertexes
        std::cout << "�������� �������:    "<< temp.name << std::endl;

        if (temp.name == endTop) {
            std::cout << "������� ������� ��������� �������, ������� �������� ������� ������ ������." << std::endl;
            answer(vectorTops, startTop, endTop);
            return true;
        }
        std::cout << "��������� �������    " << openVertexes[0].name << "    � ������ �������� ������. � ������� � �� ������� �������� ������." << std::endl;
        closedVertexes.emplace_back(temp); //��������� ������������ �������
        openVertexes.erase(openVertexes.begin()); //������� ������������ �������

        for (unsigned int i = 0; i < temp.coupled.size(); i++) { //��� ������� ������
            if (whatNumber(temp.coupled[i], closedVertexes) != -1) { //���� ����� ��������� � closedVertexes (��� ������������)
                continue;
            }
            int j = 0;
            while (true) {
                if (vectorPath[j].nameFromP == temp.name && vectorPath[j].nameOutP == temp.coupled[i]) {
                    std::cout << "������� �������� ����������� ���� �� �������    " << vectorPath[j].nameOutP << std::endl;
                    temp_G = vectorPath[j].weightPath + temp.pathToTop;
                    std::cout << "���������� ���� �� ������� =  " << temp_G << std::endl;
                    break;
                }
                j++;
            }

            if (whatNumber(temp.coupled[i], openVertexes) == -1) { //���� ����� �� � openVertexes 
                std::cout << "��� ��� �������� �������    " << temp.coupled[i] << "    �� ��������� � ������� �������� ������, �� ��������� � � ����." << std::endl;
                openVertexes.emplace_back(vectorTops[whatNumber(temp.coupled[i], vectorTops)]); //��������� ������ 
                std::cout << "�������� ������� ���������� ����������."  << std::endl;
                changeInfo(vectorTops, openVertexes, temp.coupled[i], temp.name, temp_G, endTop);
            }
            else {
                if (temp_G < openVertexes[whatNumber(temp.coupled[i], openVertexes)].pathToTop) {
                    std::cout << "��� ��� ������ ����� �������� ����("   << temp_G <<   ") �� �������    " << temp.coupled[i] <<".  ��������� ����������."<< std::endl;
                    changeInfo(vectorTops, openVertexes, temp.coupled[i], temp.name, temp_G, endTop);
                }
            }

           
        }
    }
     return false;
 }


int main() {

    setlocale(LC_ALL, "Russian");
    bool flag = true;
    bool flagM = true;
    bool flagAd = true;
    std::vector<Path> vectorPath;//������ �����
    vectorPath.reserve(0);
    std::vector<Top> vectorTops;//������ ������
    vectorTops.reserve(0);

    char startTop;
    char endTop;
    std::cout << "����������, ������� ��������� ������� � ��������, � ����� ����� ����� � ��������� ��� ����: " << std::endl;

    std::cin >> startTop;
    std::cin >> endTop;

    char start, end;
    double weight;


    while (std::cin >> start >> end >> weight) {
        vectorPath.emplace_back(Path(start, end, weight));
    }

    std::set<char> set;//

    set.insert(startTop);//��������� ������ �������

    vectorTops.emplace_back(Top(startTop));//������� ������� ��������� � ������ � ������

    int number;

    for (Path path : vectorPath) {//������ �� ������� �����
        char from = path.getNameFromP();//
        char out = path.getNameOutP();

        if (set.find(from) == set.end()) {//��������� ��� � ��������� set ��� from
            set.insert(from);
            vectorTops.emplace_back(Top(from));
        }
        if (set.find(out) == set.end()) {
            set.insert(out);
            vectorTops.emplace_back(Top(out));

        }
    }
    //������ ����� ��������, �� ������ ������� ��� => 
    //��������� ������ �� ������� ����� �����
    for (Path path : vectorPath) {//������ �� ������� �����
        char from = path.getNameFromP();//
        char out = path.getNameOutP();

        if (set.find(from) != set.end()) {//��������� ��� � ��������� set ���� from
            number = whatNumber(from, vectorTops);
            vectorTops[number].coupled.emplace_back(out);//��������� ������ ������� 
        }

    }

    vectorTops[0].pathToTop = 0; 
    vectorTops[0].heuristicF = abs(endTop - startTop); 
    std::cout << "��������� ������� ��������� �*!" << std::endl;

    if (!A(vectorPath, vectorTops, startTop, endTop)) {
        flag = false;
        std::cout << "ERROR! ERROR! ERROR!" << std::endl;
    }

    //chekAd(vectorPath, vectorTops, endTop);
    if (flag)
    {
        check(vectorPath, vectorTops, endTop, flagM, flagAd);
    }
        
}