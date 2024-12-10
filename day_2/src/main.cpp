#include <iostream>
#include <fstream>
#include <set>
#include <list>

#include "main.hpp"
#include "nlohmann/json.hpp"

using namespace nlohmann;

std::list<int>::iterator next_with_skip (std::list<int>::iterator i, std::list<int>::iterator skip)
{
    std::list<int>::iterator next = std::next(i);
    if (next != skip)
    {
        return next;
    }
    return std::next(next);
}

std::list<int>::iterator prev_with_skip (std::list<int>::iterator i, std::list<int>::iterator skip)
{
    std::list<int>::iterator prev = std::prev(i);
    if (prev != skip)
    {
        return prev;
    }
    return std::prev(prev);
}

bool evaluate_report (std::list<int>::iterator begin, std::list<int>::iterator end, std::list<int>::iterator skip_iter = std::list<int>::iterator(NULL))
{
    bool passed = true;
    bool increasing = false;

    for (auto j = begin; j != end && passed == true; j = next_with_skip(j, skip_iter))
    {
        auto k = next_with_skip(j, skip_iter);

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
        
        auto l = prev_with_skip(j, skip_iter);

        if (*l == *j)
        {
            passed = false;
            continue;
        }

        if (std::abs(*l - *j) > 3)
        {
            passed = false;
            continue;
        }
        if (increasing && *l > *j)
        {
            passed = false;
            continue;
        }
        if (!increasing && *l < *j)
        {
            passed = false;
            continue;
        }
    }

    return passed;
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
            if (evaluate_report(i.begin(), i.end()))
            {
                passed_reports++;
            }
        }

        std::cout << "Part One: Passed reports:\t" << passed_reports << std::endl;

    }

    {
        int passed_reports = 0;

        for(auto i : list)
        {   
            if (evaluate_report(i.begin(), i.end()))
            {
                passed_reports++;
                continue;
            }
            else
            {
                for (auto skip_iter = i.begin(); skip_iter != i.end(); skip_iter++)
                {
                    if (skip_iter == i.begin())
                    {
                        if(evaluate_report(std::next(i.begin()), i.end()))
                        {
                            passed_reports ++;
                            break;
                        }
                    }
                    if(evaluate_report(i.begin(), i.end(), skip_iter))
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
