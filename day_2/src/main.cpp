#include <iostream>
#include <fstream>
#include <set>
#include <list>

#include "main.hpp"
#include "nlohmann/json.hpp"

using namespace nlohmann;


std::list<int>::iterator evaluate_report (std::list<int>::iterator begin, std::list<int>::iterator end)
{
    auto bad_report = end;
    bool increasing = false;

    for (auto j = begin; j != end && bad_report == end; j++)
    {
        auto k = std::next(j);

        if (j == begin)
        {
            if (k == end)
            {
                continue;
            }
            else
            {
                if (*k < *j)
                {
                    increasing = false;
                }
                else if (*k > *j)
                {
                    increasing = true;
                }
            }
            continue;
        }
        
        auto l = std::prev(j);

        if (*l == *j)
        {
            bad_report = j;
            continue;
        }

        if (std::abs(*l - *j) > 3)
        {
            bad_report = j;
            continue;
        }
        if (increasing && *l > *j)
        {
            bad_report = j;
            continue;
        }
        if (!increasing && *l < *j)
        {
            bad_report = j;
            continue;
        }
    }

    return bad_report;
}

std::list<int> remove_iterator(std::list<int> &list, std::list<int>::iterator remove)
{
    std::list<int> result;
    for (auto i = list.begin(); i != list.end(); i++)
    {
        if (i != remove)
        {
            result.push_back(*i);
        }
    }
    return result;
}

int main (int argc, char* argv[])
{
    std::ifstream input ("../input/massaged_input.txt");
    // std::ifstream input ("../input/small_massaged_input.txt");

    json js = json::parse(input);

    std::vector<std::list<int>> list = js["List"];

    {
        int passed_reports = 0;

        for(auto i : list)
        {   
            if (evaluate_report(i.begin(), i.end()) == i.end())
            {
                passed_reports++;
            }
        }

        std::cout << "Part One: Passed reports:\t" << passed_reports << std::endl;

    }

    {
        int passed_reports = 0;
        int number = 0;

        for(auto i : list)
        {   
            number ++;
            auto bad_report = evaluate_report(i.begin(), i.end());
            if (bad_report == i.end())
            {
                passed_reports++;
                continue;
            }
            else
            {
                for (auto iter = i.begin(); iter != i.end(); iter++)
                {
                    std::list<int> temp = remove_iterator(i, iter);
                    if(evaluate_report(temp.begin(), temp.end()) == temp.end())
                    {
                        passed_reports ++;
                        break;
                    }
                }

            }
        }

        std::cout << "Part Two: Passed reports after dampener:\t" << passed_reports << std::endl;

    }
}
