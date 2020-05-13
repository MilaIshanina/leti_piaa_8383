#include <iostream>
#include <vector>

void createPiArray(std::vector<int>* vector, std::string* string, int length) {

    int j = 0;
    int i = 1;

    vector->emplace_back(0);//for the first character of any image we always write 0

    while (length > i) {
        if (string->at(i) == string->at(j)) {//in the case of equality, the value j+1 is written to the vector and the indexes i and j are shifted
            vector->emplace_back(j + 1);
            i++;
            j++;
        }
        else {
            if (j == 0) {//if the characters of the image string are not equal, then 0 is written to the vector, and the index i is shifted
                vector->emplace_back(0);
                i++;
            }
            else {//if they are not equal and the index j has already shifted, then
                j = vector->at(j - 1);
            }
        }
    }
}

void function(char c, std::string string, int l, int n, int count, std::vector<int>* answer, std::vector<int>* vector)
{
    while (true) {
        std::cout << "A loop checking for the entry!" << std::endl;
        bool isCinActive = true;//flag required for reading

        if (c == string[l]) {//checks whether the current text character matches the sample string character
            std::cout << "c =  " << c << std::endl;
            l++;
            count++;
            if (l == n) {
                std::cout << "Occurrence of the string found!    " << count - n << std::endl;
                answer->emplace_back(count - n);
            }
        }
        else {
            if (l == 0) {
                std::cout << "c:  " << c << " != " << string[l] << std::endl;
                count++;
            }
            else {
                std::cout << "Moving the string-obraz." << std::endl;
                l = vector->at(l - 1);
                isCinActive = false;
            }
        }

        if (isCinActive) {
            std::cin.get(c);
        }

        if (c == '\n') {
            break;
        }
    }
}

int main() {
    //setlocale(LC_ALL, "Russian");
    std::string string;
    std::cout << "Hello! Please enter the sample string to search for!" << std::endl;
    std::cin >> string;

    std::vector<int> vector;
    vector.reserve(0);

    std::vector<int> answer;
    vector.reserve(0);
    std::cout << "A function is called to compose an array PI for the specified image!" << std::endl;
    createPiArray(&vector, &string, string.length());
    std::cout << "The function for composing the PI array for the specified image shuts down!" << std::endl;
    std::cout << "Please enter a text string to search it further!" << std::endl;
    char c;
    std::cin.get(c);//first time to count \n

    int l = 0;
    int n = string.size();

    int count = 0;
    std::cin.get(c);//reading the first character of the text string
    std::cout << "The symbol was read    " << c << std::endl;

    function(c, string, l, n, count, &answer, &vector);
    
    if (!answer.empty()) {
        for (size_t z = 0; z < answer.size(); ++z) {//output the response
            std::cout << answer[z];
            if (z != answer.size() - 1)
                std::cout << ",";
        }
    }
    else {
        std::cout << "Not a single occurrence of the image was found in the text." << std::endl;
        std::cout << -1 << std::endl;
    }


    return 0;
}