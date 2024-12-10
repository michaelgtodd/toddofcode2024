#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

#include "main.hpp"

using namespace std;
using namespace nlohmann;

int main (int argc, char* argv[])
{
    std::ifstream input ("../input/massaged_input.txt");
    // std::ifstream input ("../input/small_massaged_input.txt");

    json js = json::parse(input);

    std::cout << js << std::endl;
}
