#include "utils.h"

Utils::Utils()
{

}

Utils::~Utils()
{

}

std::vector<int> Utils::readSystemInput()
{
    vector<int> input;
    int current;
    int counter = 0;
    while(!cin.eof() && counter < INPUT_MAX_SIZE){
        cin >> current;
        input.push_back(current);
    }
    return input;
}
