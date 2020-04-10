#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Top {//класс вершины

public:

    char name;
    double pathToTop;//путь до текущей вершины - g
    double heuristicF;//эвристическая функция - f
    char nameFromT;
    std::vector<char> coupled;//вектор для исходящих из вершины вершин

    
    Top(char name)//конструктор1 - необходим для заполнения начальной вершины
        : name(name) {
        heuristicF = 0;
        pathToTop = -1;//будет использоваться для необработанных вершин вместо знака бесконечно
        nameFromT = '-';
    }

    Top() {			//конструктор2
        name = '!';		//
        heuristicF = 0;
        pathToTop = -1;	//
        nameFromT = '-';
    }

};

class Path {//класс пути - хранит только путь: откуда куда и сколько весит путь

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
    std::cout << "Запускается функция проверки на монотонность и допустимость  " << std::endl;
    if (abs(endTop - endTop) != 0) {
        std::cout << "Эвристическая оценка целевого состояния не равна нулю!" << std::endl;
        flagM = false;
        
    }

    for (unsigned int i = 0; i < vectorPath.size(); i++) {
         
        if ((abs(endTop - vectorPath[i].nameFromP) - abs(endTop - vectorPath[i].nameOutP)) > vectorPath[i].weightPath) {
            std::cout << "Монотонность нарушена. Функция возвращает false." << std::endl;
            flagM = false;
            
        }
    }
    //поверка на допустимость
    if (!flagM)
    {
        for (unsigned int i = 0; i < vectorTops.size(); i++) {


            if ((abs(endTop - vectorTops[i].name) > (vectorTops[vectorTops.size() - 1].pathToTop - vectorTops[i].pathToTop)))
            {
                std::cout << "Допустимость нарушена. Функция возвращает false." << std::endl;
                flagAd = false;
            }


        }
    }
    if (flagM)
    {
        std::cout << "Эвристика монотонна и допустима!" << std::endl;
        return true;
     }
    else if (!flagM && flagAd)
    {
        std::cout << "Эвристика допустима!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Эвристика не монотонна и не допустима!" << std::endl;
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

bool comp(Top a, Top b) {//компаратор, используется для сортировки в открытом списке
    return a.heuristicF < b.heuristicF;
}

void answer(std::vector<Top>& vectorTops, char startTop, char endTop)
{
    std::cout << "Запускается функция вывода ответа.  " << std::endl;
    std::vector<Top> answer;
    answer.reserve(0);
    Top temp = vectorTops[whatNumber(endTop, vectorTops)];
    std::cout << "Записываем в вектор ответа последнюю вершину  " << endTop << std::endl;
    answer.emplace_back(temp);
    while (temp.name != startTop) {
        temp = vectorTops[whatNumber(temp.nameFromT, vectorTops)];
        std::cout << "Записываем в вектор ответа вершину  " << temp.name << std::endl;
        answer.emplace_back(temp);
    }
    std::cout << "Реверсируем вектор ответа  " << std::endl;
    std::reverse(answer.begin(), answer.end());//т к он заполнился в обратном порядке, делаем reverse
    std::cout << "Ответ:  " << std::endl;
    for (Top ans : answer) {
        std::cout << ans.name;
    }
    std::cout << std::endl;
}

void changeInfo(std::vector<Top>& vectorTops, std::vector<Top>& openVertexes, char a, char name, double temp_G, char endTop )
{
    std::cout << "Обновляем информацию:  " << std::endl;

    vectorTops[whatNumber(a, vectorTops)].nameFromT = name;
    
    vectorTops[whatNumber(a, vectorTops)].pathToTop = temp_G;
    openVertexes[whatNumber(a, openVertexes)].nameFromT = name;
    openVertexes[whatNumber(a, openVertexes)].pathToTop = temp_G;
    openVertexes[whatNumber(a, openVertexes)].heuristicF = temp_G + abs(endTop - a);
    std::cout << "Вершина  " << a << "   устанавливаем, что исходит из   " << name << std::endl;
    std::cout << "Путь до вершины  " << a << "   равен   " << temp_G << std::endl;
    std::cout << "Эвристическая оценка для вершины  " << a << "   равна   " << temp_G + abs(endTop - a) << std::endl;
    std::cout << "Конец обновления информации.  " << std::endl;
}

bool A(std::vector<Path>& vectorPath, std::vector<Top>& vectorTops, char startTop, char endTop) {

    Top temp;
    double temp_G;
    std::vector<Top> closedVertexes;
    closedVertexes.reserve(0);
    std::vector<Top> openVertexes;
    openVertexes.reserve(0);

    std::cout << "В вектор открытых вершин добавляем вершину    " << vectorTops[0].name << std::endl;

    openVertexes.emplace_back(vectorTops[0]);

    while (!openVertexes.empty()) {
        Top min = openVertexes[0];
        std::cout << "Сортируем открытые вершины " << std::endl;
        std::sort(openVertexes.begin(), openVertexes.end(), comp);
        temp = openVertexes[0]; //минимальная f из openVertexes
        std::cout << "Текуущая вершина:    "<< temp.name << std::endl;

        if (temp.name == endTop) {
            std::cout << "Текущая вершина ровняется искомой, поэтому вызываем функцию вывода ответа." << std::endl;
            answer(vectorTops, startTop, endTop);
            return true;
        }
        std::cout << "Добавляем вершину    " << openVertexes[0].name << "    в вектор закрытых вершин. И удаляем её из вектора открытых вершин." << std::endl;
        closedVertexes.emplace_back(temp); //добавляем обработанную вершину
        openVertexes.erase(openVertexes.begin()); //удаляем обработанную вершину

        for (unsigned int i = 0; i < temp.coupled.size(); i++) { //для каждого соседа
            if (whatNumber(temp.coupled[i], closedVertexes) != -1) { //если сосед находится В closedVertexes (уже обработанном)
                continue;
            }
            int j = 0;
            while (true) {
                if (vectorPath[j].nameFromP == temp.name && vectorPath[j].nameOutP == temp.coupled[i]) {
                    std::cout << "Считаем значение кратчайшего пути до вершины    " << vectorPath[j].nameOutP << std::endl;
                    temp_G = vectorPath[j].weightPath + temp.pathToTop;
                    std::cout << "Кратчайший путь до вершины =  " << temp_G << std::endl;
                    break;
                }
                j++;
            }

            if (whatNumber(temp.coupled[i], openVertexes) == -1) { //если сосед не в openVertexes 
                std::cout << "Так как соседняя вершина    " << temp.coupled[i] << "    не находится в векторе открытых вершин, то добавляем её в него." << std::endl;
                openVertexes.emplace_back(vectorTops[whatNumber(temp.coupled[i], vectorTops)]); //добавляем соседа 
                std::cout << "Вызываем функцию обновления информации."  << std::endl;
                changeInfo(vectorTops, openVertexes, temp.coupled[i], temp.name, temp_G, endTop);
            }
            else {
                if (temp_G < openVertexes[whatNumber(temp.coupled[i], openVertexes)].pathToTop) {
                    std::cout << "Так как найден более короткий путь("   << temp_G <<   ") до вершины    " << temp.coupled[i] <<".  Обновляем информацию."<< std::endl;
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
    std::vector<Path> vectorPath;//вектор путей
    vectorPath.reserve(0);
    std::vector<Top> vectorTops;//вектор вершин
    vectorTops.reserve(0);

    char startTop;
    char endTop;
    std::cout << "Пожалуйста, введите начальную вершину и конечную, а также ребра графа с указанием его веса: " << std::endl;

    std::cin >> startTop;
    std::cin >> endTop;

    char start, end;
    double weight;


    while (std::cin >> start >> end >> weight) {
        vectorPath.emplace_back(Path(start, end, weight));
    }

    std::set<char> set;//

    set.insert(startTop);//вставляем первую вершину

    vectorTops.emplace_back(Top(startTop));//создаем вершину начальную и кладем в вектор

    int number;

    for (Path path : vectorPath) {//проход по вектору путей
        char from = path.getNameFromP();//
        char out = path.getNameOutP();

        if (set.find(from) == set.end()) {//проверяет что в множестве set нет from
            set.insert(from);
            vectorTops.emplace_back(Top(from));
        }
        if (set.find(out) == set.end()) {
            set.insert(out);
            vectorTops.emplace_back(Top(out));

        }
    }
    //вектор путей заполнен, но вектор соседей нет => 
    //выполняем проход по вектору путей снова
    for (Path path : vectorPath) {//проход по вектору путей
        char from = path.getNameFromP();//
        char out = path.getNameOutP();

        if (set.find(from) != set.end()) {//проверяет что в множестве set есть from
            number = whatNumber(from, vectorTops);
            vectorTops[number].coupled.emplace_back(out);//добавляем соседа вершины 
        }

    }

    vectorTops[0].pathToTop = 0; 
    vectorTops[0].heuristicF = abs(endTop - startTop); 
    std::cout << "Запускаем функцию алгоритма А*!" << std::endl;

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