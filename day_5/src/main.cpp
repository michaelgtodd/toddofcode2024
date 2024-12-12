#include <iostream>
#include <fstream>
#include <chrono>
#include <set>
#include <map>
#include <vector>
#include <list>

#include <nlohmann/json.hpp>

#include "main.hpp"

using namespace std;
using namespace nlohmann;

bool p1_validate_test(std::vector<int>& test, std::map<int, std::set<int>>& page_rules)
{
    for (size_t i = 0; i < test.size(); i++)
    {
        for (size_t j = i + 1; j < test.size(); j++)
        {
            if (page_rules[test[j]].find(test[i]) != page_rules[test[j]].end())
            {
                return false;
            }
        }
    }
    return true;
}

std::map<int, std::set<int>> p2_expand_page_rules (std::map<int, std::set<int>>& old_page_rules, std::vector<int>& relevant_numbers)
{
    std::map<int, std::set<int>> page_rules;

    for (auto i : relevant_numbers)
    {
        for (auto j : relevant_numbers)
        {
            if (old_page_rules[i].find(j) != old_page_rules[i].end())
            {
                page_rules[i].insert(j);
            }
        }
    }

    for (auto [k, v] : page_rules)
    {
        std::set<int> banned_pages;
        for (auto i : v)
        {
            banned_pages.insert(i);
        }
        int last_size = banned_pages.size();
        int new_size = banned_pages.size() + 1;
        while (last_size != new_size)
        {
            last_size = banned_pages.size();
            std::set<int> page_cycle = banned_pages;
            for (auto i : page_cycle)
            {
                for (auto j : page_rules[i])
                {
                    banned_pages.insert(j);
                }
            }
            new_size = banned_pages.size();
        }
        page_rules[k] = banned_pages;
    }

    return page_rules;
}

int main (int argc, char* argv[])
{
    std::ifstream input ("../input/massaged_input.txt");
    // std::ifstream input ("../input/small_massaged_input.txt");

    json js = json::parse(input);

    std::vector<std::vector<int>> page_orders = js["pages"];
    std::vector<std::vector<int>> test_vectors = js["runs"];

    auto total_begin = std::chrono::steady_clock::now();

    float part_one_seconds = 0;
    float part_two_seconds = 0;

    int p1_value = 0;
    int p2_value = 0;
    
    { // PART ONE

        auto part_one_begin = std::chrono::steady_clock::now();

        std::map<int, std::set<int>> page_rules;
        for (auto i : page_orders)
        {
            page_rules[i[0]].insert(i[1]);
        }

        int sum = 0;

        for (auto test : test_vectors)
        {
            if (p1_validate_test(test, page_rules))
            {
                sum += test[(test.size() / 2)];
            }
        }

        auto part_one_end = std::chrono::steady_clock::now();
        part_one_seconds = std::chrono::duration_cast<std::chrono::microseconds>(part_one_end - part_one_begin).count() / 1000000.0;

        p1_value = sum;

    } // END PART ONE

    { // PART TWO

        auto part_two_begin = std::chrono::steady_clock::now();

        std::map<int, std::set<int>> page_rules;
        for (auto i : page_orders)
        {
            page_rules[i[0]].insert(i[1]);
        }


        std::vector<std::list<int>> corrected_orders;
        int sum = 0;

        for (auto test : test_vectors)
        {
            if (p1_validate_test(test, page_rules))
            {
                continue;
            }
            else
            {
                std::map<int, std::set<int>> local_page_rules = p2_expand_page_rules(page_rules, test);

                std::list<int> corrected_test;

                for (auto i : test)
                {
                    std::list<int>::iterator index = corrected_test.begin();
                    while(index != corrected_test.end())
                    {
                        if (local_page_rules[i].find(*index) == local_page_rules[i].end())
                        {
                            index ++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    corrected_test.insert(index, i);
                }

                std::list<int>::iterator index = corrected_test.begin();
                for (size_t i = 0; i < corrected_test.size()/2; i++)
                {
                    index++;
                }
                sum += *index;
            }
        }
        
        auto part_two_end = std::chrono::steady_clock::now();
        part_two_seconds = std::chrono::duration_cast<std::chrono::microseconds>(part_two_end - part_two_begin).count() / 1000000.0;

        p2_value = sum;

    } // END PART TWO

    auto total_end = std::chrono::steady_clock::now();
    float total_seconds = std::chrono::duration_cast<std::chrono::microseconds>(total_end - total_begin).count() / 1000000.0;
    
    std::cout << "Part One:\t" << p1_value << std::endl;
    std::cout << "Part Two:\t" << p2_value << std::endl;

    std::cout << "Part One Time: " << part_one_seconds << "s" << std::endl;
    std::cout << "Part Two Time: " << part_two_seconds << "s" << std::endl;
    std::cout << "Total Time: " << total_seconds << "s" << std::endl;


}
