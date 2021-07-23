#include <iostream>
#include <iterator>
#include <vector>
#include "utils.h"
#include "round.h"

using namespace std;

int main()
{
    std::vector<int> input = Utils::readSystemInput();
    Round round = Round(input);
    round.makeAMove();
    return 0;
}
