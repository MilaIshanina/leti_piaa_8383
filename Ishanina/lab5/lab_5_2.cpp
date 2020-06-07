#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>

class Top {

private:
    char name;
    std::vector<Top*> childs;
    Top* sufLink;
    Top* parent;
    bool isTerminal;
    bool isFirstElement;
    std::vector<int> numberStrings;

public:

    Top(char name, Top* parent) : name(name), parent(parent) {
        sufLink = nullptr;
        childs.resize(0);
        numberStrings.resize(0);
        isTerminal = false;
        isFirstElement = false;
    }

    Top() {
        name = '&';
        parent = nullptr;
        sufLink = this;
        childs.resize(0);
        numberStrings.resize(0);
        isTerminal = false;
        isFirstElement = true;
    }

    void addChild(Top* child) {
        childs.emplace_back(child);
    }

    void setTerminal(int numberString) {
        isTerminal = true;
        numberStrings.emplace_back(numberString);
    }

    const std::vector<Top*>& getChilds() const {
        return childs;
    }

    char getName() const {
        return name;
    }

    Top* getSufLink() const {
        return sufLink;
    }

    Top* getParent() const {
        return parent;
    }

    void setSufLink(Top* sufLink) {
        Top::sufLink = sufLink;
    }

    bool isFirstElement1() const {
        return isFirstElement;
    }

    bool isTerminal1() const {
        return isTerminal;
    }

    const std::vector<int>& getNumberStrings() const {
        return numberStrings;
    }


};

Top* createTop(Top* parent, std::string* string, int countElement, int numberString) {//this function creates a child for the current vertex
    std::cout << "Run the function to create the vertices!" << std::endl;
    auto* element = new Top(string->at(countElement), parent);
    if (countElement == string->length() - 1) {
        std::cout << "Since the vertex " << element->getName() << " if it is the end of a template string, it is marked as terminal!" << std::endl;
        element->setTerminal(numberString);
    }
    parent->addChild(element);
    std::cout << "The vertex creation function shuts down!" << std::endl;
    return element;//returns the child
}

void addString(Top* top, std::string* string, int numberString) {//the function adds a string to the boron
    std::cout << "The function for adding a row to the boron is started!" << std::endl;
    int count = 0;
    Top* cur = top;//initially cur indicates the beginning of boron
    while (count < string->length()) {
        char name = cur->getName();
        std::cout << "Current vertex: " << name << std::endl;
        bool isFind = false;
        std::vector<Top*> childs = cur->getChilds();
        for (auto child : childs) {
            std::cout << "Since at the top " << name << " if there is already a child, then a pass is performed for all children:" << std::endl;
            if (child->getName() == string->at(count)) {
                std::cout << "So what's the baby's name " << child->getName() << " equals the current character of the template string " << string->at(count) << " , then go to the child!" << std::endl;
                cur = child;
                count++;
                isFind = true;
                if (count == string->length()) {
                    std::cout << "Since the count counter (" << count << ") equal to the end of the template string (" << string->length() << "), that";
                    std::cout << " adding the current vertex " << cur->getName() << " to the terminal." << std::endl;
                    cur->setTerminal(numberString);
                }
                break;
            }
        }

        if (!isFind) {
            std::cout << "Since the current vertex doesn't have a child equal to the vertex " << string->at(count) << " then the function for adding this child to it is called." << std::endl;
            cur = createTop(cur, string, count, numberString);
            count++;
        }
    }
    char name = cur->getName();
    std::cout << "The function for adding a row to the boron terminates!" << std::endl;
}


std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {//cuts the string of the Joker
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (item.length() > 0) {
            elems.push_back(item);
        }
    }
    return elems;
}

std::vector<std::string> split(const std::string& s, char delim) {//generates a string vector
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void createAnswer(Top* bor, std::string text, std::vector<std::string>* strings,
    std::vector<std::pair<int, int>>* vectorAnswers) {

    int count = 0;
    Top* cur = bor;
    while (count < text.length()) {
        bool isExistX = false;
        for (auto child : cur->getChilds()) {
            if (child->getName() == text[count]) {
                cur = child;
                isExistX = true;
                count++;
                if (cur->isTerminal1()) {

                    for (auto numberString : cur->getNumberStrings()) {
                        vectorAnswers->emplace_back(
                            std::make_pair(count - strings->at(numberString).length() + 1, numberString));
                    }
                }
                break;
            }
        }
        if (!isExistX) {
            if (cur->isFirstElement1()) {
                count++;
            }
            cur = cur->getSufLink();
        }
    }

}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string text;
    std::vector<std::string> strings;
    strings.resize(0);
    int countStrings = 0;


    std::string my_str;
    char symbol;

    std::cout << "Hello! Please enter the text!" << std::endl;
    std::cin >> text;
    std::cout << "Please enter a template!" << std::endl;
    std::cin >> my_str;
    std::cout << "Please enter the symbol of the Joker!" << std::endl;
    std::cin >> symbol;
    std::cout << "The template splitting function starts!" << std::endl;
    strings = split(my_str, symbol);//dividing the line
    std::cout << "The string AFTER splitting: " << std::endl;

    countStrings = strings.size();
    for (int j = 0; j < countStrings; ++j) {
        std::cout << strings[j] << std::endl;
    }
    auto* bor = new Top;

    for (int j = 0; j < countStrings; ++j) {
        addString(bor, &strings[j], j);
    }

    std::queue<Top*> queue;//creating a queue
    for (auto local : bor->getChilds()) {//passage through all the children of Bor
        local->setSufLink(bor);//putting a suffix link to the beginning of the boron(&)
        for (auto local2 : local->getChilds()) {
            std::cout << "Top: " << local2->getName() << " now in the queue!" << std::endl;
            queue.push(local2);
        }

    }

    while (!queue.empty()) {
        char name = queue.front()->getName();
        std::cout << "Current vertex: " << name << std::endl;
        Top* element = queue.front()->getParent();
        bool isExistX = false;//end of pass flag

        while (!isExistX) {
            element = element->getSufLink();//take a step back(move to the previous vertex)
            for (auto child : element->getChilds()) {//walking through the children.
                if (child->getName() == name) {//if there is a match with the current vertex from the queue
                    isExistX = true;
                    element = child;
                    break;
                }
            }
            if (element->isFirstElement1() && !isExistX) {//if there were no matches with a vertex from the queue
                isExistX = true;
            }



        }
        queue.front()->setSufLink(element);//putting a suffix link to element
        std::cout << "Set the suffix link of vertex: " << name << " on top: " << element->getName() << std::endl;
        if (queue.front()->getSufLink()->isTerminal1()) {//проверка если она терминальная
            for (int numberString : queue.front()->getSufLink()->getNumberStrings()) {

                queue.front()->setTerminal(numberString);
            }
        }

        for (auto child : queue.front()->getChilds()) {//if there is a child at the current vertex from the queue, we write it to it
            std::cout << "Adding a vertex " << child->getName() << " to the queue!" << std::endl;
            queue.push(child);
        }
        std::cout << "Deleting the top vertex " << name << " from the queue!" << std::endl;
        queue.pop();
    }


    std::vector<std::pair<int, int>> vectorAnswers;
    vectorAnswers.resize(0);

    std::vector<std::pair<int, int>> vectorAnswers2;
    vectorAnswers.resize(0);

    int count2 = 0;

    for (int i = 0; i < my_str.length(); ++i) {//finding the occurrence of a substring in the template
        if (my_str[i] == strings[count2][0]) {
            int count = 0;
            for (int j = 0; j < strings[count2].length(); ++j) {
                if (strings[count2][j] == my_str[i + count]) {
                    count++;
                }
            }
            if (count == strings[count2].length()) {
                vectorAnswers2.emplace_back(i, count2);//write to the vector
                i = i + count;
                if (count2 < strings.size() - 1) {
                    count2++;
                }
            }
        }
    }

    createAnswer(bor, text, &strings, &vectorAnswers);



    int* array = new int[text.size()];
    for (int i = 0; i < text.size(); ++i) {
        array[i] = 0;
    }

    for (auto answer : vectorAnswers) {

        int number = answer.first - vectorAnswers2[answer.second].first - 1;
        if (number >= 0) {
            array[number]++;
        }
    }

    std::vector<int> finalAnswers;
    for (int i = 0; i < text.size(); ++i) {
        if (array[i] == strings.size()) {
            if (i + my_str.size() <= text.size()) {
                //std::cout << i + 1;
                finalAnswers.emplace_back(i + 1);//an array of the occurrences of the text patterns
            }
        }

    }

    int cur = 0;//number of the current occurrence
    int lenghtPatt = my_str.size();//the length of the template
    for (int k = 1; k < finalAnswers.size(); k++)
    {
        if ((finalAnswers[cur] + lenghtPatt - 1 >= finalAnswers[k]) && finalAnswers[k] != -1)
            finalAnswers[k] = -1;
        else
        {
            cur = k;
        }

    }


    std::cout << "Output the response:" << std::endl;

    for (int h = 0; h < finalAnswers.size(); h++)
    {
        if (finalAnswers[h] != -1)
        {
            std::cout << finalAnswers[h] << std::endl;
        }

    }

    delete[] array;

    return 0;
}