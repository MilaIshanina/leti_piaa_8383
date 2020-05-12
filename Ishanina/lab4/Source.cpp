#include <iostream>
#include <vector>

void createPiArray(std::vector<int>* vector, std::string* string, int length) {

    int j = 0;
    int i = 1;

    vector->emplace_back(0);//for the first character of any image we always write 0

    while (length > i) {
        if (string->at(i) == string->at(j)) {
            vector->emplace_back(j + 1);
            i++;
            j++;
        }
        else {
            if (j == 0) {
                vector->emplace_back(0);
                i++;
            }
            else {
                j = vector->at(j - 1);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
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

    while (true) {
        std::cout << "A loop checking for the entry!" << std::endl;
        bool isCinActive = true;//flag required for reading

        if (c == string[l]) {//checks whether the current text character matches the sample string character
            std::cout << "c =  " << c << std::endl;
            l++;
            count++;
            if (l == n) {
                std::cout << "Occurrence of the string found!    " << count - n << std::endl;
                answer.emplace_back(count - n);
            }
        }
        else {
            if (l == 0) {
                std::cout << "c:  " << c << " != " << string[l] << std::endl;
                count++;
            }
            else {
                std::cout << "Moving the string." << std::endl;
                l = vector.at(l - 1);
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

    if (!answer.empty()) {
        for (size_t m = 0; m < answer.size(); ++m) {//output the response
            std::cout << answer[m];
            if (m != answer.size() - 1)
                std::cout << ",";
        }
    }
    else {
        std::cout << "Not a single occurrence of the image was found in the text." << std::endl;
    }


    return 0;
}