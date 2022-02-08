#include <iostream>
#include <string>
#include <fstream>

const int COLOR_CONTRAST = 1;

void coloredPrint(std::string input, int color){
    const std::string colorEnd = "\033[0m";

    for(int i = 0; i < input.length(); i++){
        std::string colorBegin = "\033[38;5;";
        
        if(input.at(i) == '('){
            color+=COLOR_CONTRAST;
            colorBegin += std::to_string(color);
            colorBegin += "m";
            input.insert((i), colorBegin);
            i += colorBegin.length();
        }
        else if(input.at(i) == ')'){

            if(input.find(")", i + 1) == std::string::npos){
                input.insert(i + 1, colorEnd);
                i = input.length();
            }
            else{
                input.insert(i + 1, colorEnd);
                std::string newColorBegin = "\033[38;5;";
                color -= COLOR_CONTRAST;
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

int main(int argc, char* argv[]){
    if (argc != 2){
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
    coloredPrint(input, 3);
    return 0;
}