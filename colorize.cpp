#include <iostream>
#include <string>
#include <fstream>
#include <stack>

void coloredPrint(std::string input, int color, int contrast){
    const std::string colorEnd = "\033[0m";

    for(int i = 0; i < input.length(); i++){
        std::string colorBegin = "\033[38;5;";
        
        if(input.at(i) == '(' || input.at(i) == '[' || input.at(i) == '{'){
            color+=contrast;
            if(color == 0)color = 1;
            colorBegin += std::to_string(color);
            colorBegin += "m";
            input.insert((i), colorBegin);
            i += colorBegin.length();
        }
        else if(input.at(i) == ')' || input.at(i) == ']' || input.at(i) == '}'){

            if(input.find(")", i + 1) == std::string::npos && input.find("]", i + 1) == std::string::npos && input.find("}", i + 1) == std::string::npos){
                input.insert(i + 1, colorEnd);
                i = input.length();
            }
            else{
                input.insert(i + 1, colorEnd);
                std::string newColorBegin = "\033[38;5;";
                color -= contrast;
                if(color <= 0)color = -1;
                newColorBegin += std::to_string(color);
                newColorBegin += "m";
                input.insert(i + 1 + colorEnd.length(), newColorBegin);
                i += colorEnd.length() + newColorBegin.length();
            }
        }
    }
    input.insert(input.length() , colorEnd);
    std::cout << input << std::endl;
}

bool validate(std::string input){
    std::stack<char> brackets;

    for (int i = 0; i < input.length(); i++){
        char a = input.at(i);
        switch (a)
        {
        case '(':
            brackets.push(')');
            break;
        case '[':
            brackets.push(']');
            break;
        case '{':
            brackets.push('}');
            break;
        case ')':
        case ']':
        case '}':
                {
                if(brackets.empty() || brackets.top() != a) return false;
                else brackets.pop();
            }
        default:
            break;
        }
    }
    return brackets.empty();
}

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "Example usage: ./colorize \"q\\/(p -> t)\"" << std::endl;
        return 1;
    }
    std::string input = argv[1];
    char letter = 'A';
    std::ifstream inputFile;
    inputFile.open(input);

    if (!inputFile.fail()) {
        input = "";
        while(inputFile.get(letter)){
            input.push_back(letter);
        }
    }
    if(!validate(input)) std::cerr << "Warning! unbalanced brackets" << std::endl;
    int color = 0;
    int contrast = 1;
    if (argc >= 3)color = std::stoi(argv[2]);
    if (argc >= 4)contrast = std::stoi(argv[3]);
    coloredPrint(input, color, contrast);
    return 0;
}
