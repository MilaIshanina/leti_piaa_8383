#include <iostream>
#include <vector>
#include <algorithm>


class Top
{//boron vertex class
public:
    std::vector <int> nextV;
    int numberString;
    bool isTerminal;//Boolean variable, which labels the terminal vertex
    int suffLink;
    std::vector <int> autoMove;
    int parent;
    char numberSymbol;
    std::vector <Top> bor;
    char name;//name of the edge to follow

    Top(int parent, char numberSymbol) : parent(parent), numberSymbol(numberSymbol)
    {
        nextV = { -1,-1,-1,-1,-1,-1 };
        autoMove = { -1,-1,-1,-1,-1,-1 };
        suffLink = -1;
        numberString = 0;
        isTerminal = false;

        if (numberSymbol == 0)
            name = 'A';
        else if (numberSymbol == 1)
            name = 'C';
        else if (numberSymbol == 2)
            name = 'G';
        else if (numberSymbol == 3)
            name = 'T';
        else if (numberSymbol == 4)
            name = 'N';
        else
            name = '#';
    }

    Top()//when a bor is created, this constructor is called
    {
        bor.emplace_back(Top(0, 0));
    }
};

void writeResponse(int vert, int ch, std::vector<std::pair<int, int>>* vectorAnswers, std::vector<Top>* bor, std::vector<std::string>* strings);
int getAutoMove(int vert, int ch, std::vector<Top>* bor);

void addString(std::vector<Top>* bor, std::string* string, int numberString)//function of adding a template to the bor
{
    std::cout << "The function of adding a template to the boron starts!" << std::endl;
    int num = 0;
    bool flag = false;
    for (int i = 0; i < string->length(); i++)
    {
        int token = ' ';
        if (string->at(i) == 'A')
            token = 0;
        else if (string->at(i) == 'C')
            token = 1;
        else if (string->at(i) == 'G')
            token = 2;
        else if (string->at(i) == 'T')
            token = 3;
        else if (string->at(i) == 'N')
            token = 4;
        else
            token = 5;
        std::cout << "The current character template = " << string->at(i) << std::endl;
        if (bor->at(num).nextV[token] == -1)
        {
            flag = true;
            std::cout << "Since the current boron vertex doesn't have a child = " << string->at(i) << "  ,we add this child to the boron" << std::endl;
            bor->emplace_back(Top(num, token));
            bor->at(num).nextV[token] = bor->size() - 1;

        }
        else if (!flag)
            std::cout << "Since the top of Bor already has a child " << string->at(i) << ", we just switch to it" << std::endl;
        num = bor->at(num).nextV[token];

    }
    std::cout << "The end of the template string was reached, so the last vertex is marked terminal." << std::endl;
    bor->at(num).isTerminal = true;
    std::cout << "The completed template is added to the template vector." << std::endl;
    bor->at(num).numberString = numberString;
    std::cout << "The function for adding a template to the boron terminates!" << std::endl;
}

int getSuff(int top, std::vector<Top>* bor)//function for getting and setting suffix links
{
    std::cout << "The function for getting and setting suffix links starts!" << std::endl;
    if (bor->at(top).suffLink == -1)
    {
        std::cout << "From vertex " << bor->at(top).name << " a suffix link has not been made yet!" << std::endl;
        if (top == 0 || bor->at(top).parent == 0)
        {
            std::cout << "For the current vertex set a suffix reference to the beginning of the boron." << std::endl;
            bor->at(top).suffLink = 0;
        }
        else
        {
            if (bor->at(top).isTerminal)
            {
                std::cout << "Since the vertex " << bor->at(top).name << " is a terminal vertex, a suffix reference to the beginning of the boron will be set for it!" << std::endl;
                bor->at(top).suffLink = 0;
            }
            else
            {
                std::cout << "For the current vertex " << bor->at(top).name << " setting the suffix reference NOT to the beginning of the boron, but to ..." << std::endl;
                bor->at(top).suffLink = getAutoMove(getSuff(bor->at(top).parent, bor), bor->at(top).numberSymbol, bor);
                std::cout << "... on top " << bor->at(bor->at(top).suffLink).name << std::endl;
            }

        }
    }
    return bor->at(top).suffLink;
}

int getAutoMove(int top, int token, std::vector<Top>* bor)
{
    std::cout << "The transition function starts!" << std::endl;
    if (bor->at(top).autoMove[token] == -1)
    {
        if (bor->at(top).nextV[token] != -1)
        {
            std::cout << "If there is a transition on the current vertex " << int(bor->at(top).numberSymbol) << ", then we switch to it" << std::endl;
            bor->at(top).autoMove[token] = bor->at(top).nextV[token];
        }
        else if (top == 0)
        {
            std::cout << "If there is no transition to the current vertex and the current vertex in the collection is the initial one, then we remain at the beginning of the boron." << std::endl;
            bor->at(top).autoMove[token] = 0;
        }
        else
        {
            std::cout << "If there is no click on the current vertex, click on the suffix link" << std::endl;
            bor->at(top).autoMove[token] = getAutoMove(getSuff(top, bor), token, bor);
        }
    }
    std::cout << "The transition function shuts down!" << std::endl;
    return bor->at(top).autoMove[token];
}

void function(std::string& text, std::vector<std::pair<int, int>>* vectorAnswers, std::vector<Top>* bor, std::vector<std::string>* strings)
{
    std::cout << "The function for searching for a template in the text starts!" << std::endl;
    int t = 0;
    for (int i = 0; i < text.length(); i++)
    {
        int token;
        if (text[i] == 'A')
            token = 0;
        else if (text[i] == 'C')
            token = 1;
        else if (text[i] == 'G')
            token = 2;
        else if (text[i] == 'T')
            token = 3;
        else if (text[i] == 'N')
            token = 4;
        else
        {
            token = 5;
            std::cout << "Error!" << std::endl;
            break;
        }
        

        t = getAutoMove(t, token, bor);
        writeResponse(t, i + 1, vectorAnswers, bor, strings);
    }
}

void writeResponse(int vert, int token, std::vector<std::pair<int, int>>* vectorAnswers, std::vector<Top>* bor, std::vector<std::string>* strings)
{

    for (int i = vert; i != 0; i = getSuff(i, bor))
    {
        if (bor->at(i).isTerminal)
        {
            std::cout << "The response vector records the found occurrence of the template!" << std::endl;
            vectorAnswers->emplace_back(std::make_pair(token - strings->at(bor->at(i).numberString).length() + 1, bor->at(i).numberString + 1));

        }
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    std::string text;
    std::vector<std::string> strings;
    strings.resize(0);
    int countStrings = 0;
    int depth = 0;
    std::cout << "Hello! Please enter the text!" << std::endl;
    std::cin >> text;
    std::cout << "Please enter the number of templates!" << std::endl;
    std::cin >> countStrings;
    for (int i = 0; i < countStrings; ++i) {
        std::string string;
        std::cout << "Please enter " << i + 1 << " template!" << std::endl;
        std::cin >> string;
        strings.emplace_back(string);
    }

    std::vector <Top> bor;
    bor.resize(0);
    bor.emplace_back(Top(0, 0));


    std::vector<std::pair<int, int>> vectorAnswers;
    vectorAnswers.resize(0);

    for (int j = 0; j < countStrings; ++j) {
        addString(&bor, &strings[j], j);
    }

    function(text, &vectorAnswers, &bor, &strings);
    //Sorting of the response vector is started
    std::sort(vectorAnswers.begin(), vectorAnswers.end(),
        [](std::pair<int, int> a, std::pair<int, int> b)
        {
            if (a.first == b.first) {
                return a.second < b.second;
            }
            else {
                return a.first < b.first;
            }
        });

    //std::sort(vectorAnswers.begin(), vectorAnswers.end(), comp);
    for (auto answer : vectorAnswers) {
        std::cout << answer.first << " " << answer.second << std::endl;
    }
}