#include <lib.hpp>

// #include <fmt/format.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

constexpr int a_size = 100'000'000;

template <class S>
inline void rep_finish(S const& start, std::string in_what)
{
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finish - start;
    std::cout << "Elapsed Time (" 
        << in_what << "): "
        << elapsed.count() << " milli-seconds" << std::endl;
}

static std::vector<int> s_integers;
static std::vector<std::string> s_strings;

void test_int_1()
{
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i=0; i<a_size; ++i)
    {
        std::lower_bound(s_integers.begin(), s_integers.end(), i);
    }
    rep_finish(start, "std");

    start = std::chrono::high_resolution_clock::now();
    for (auto i=0; i<a_size; ++i)
    {
        tribl::lower_bound(s_integers.begin(), s_integers.end(), i);
    }
    rep_finish(start, "tribl");
}

void test_int_2()
{
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i : s_integers )
    {
        std::lower_bound(s_integers.begin(), s_integers.end(), i);
    }
    rep_finish(start, "std");

    start = std::chrono::high_resolution_clock::now();
    for (auto i : s_integers )
    {
        tribl::lower_bound(s_integers.begin(), s_integers.end(), i);
    }
    rep_finish(start, "tribl");
}

void test_str()
{
    auto start = std::chrono::high_resolution_clock::now();
    for (auto s : s_strings )
    {
        std::lower_bound(s_strings.begin(), s_strings.end(), s);
    }
    rep_finish(start, "std");

    start = std::chrono::high_resolution_clock::now();
    for (auto s : s_strings )
    {
        tribl::lower_bound(s_strings.begin(), s_strings.end(), s);
    }
    rep_finish(start, "tribl");
}

int main() {

    std::cout << "Filling up integers ..." << std::flush;
    s_integers.resize(a_size);
    for (auto i=0; i<a_size; ++i)
        s_integers.push_back(i);
    std::cout << "Done." << std::endl << std::flush;
    std::cout << "Filling up strings ..." << std::flush;
    s_strings.resize(a_size);
    for (auto i=a_size; i<a_size*2; ++i)
        s_strings.push_back(std::to_string(i));
    std::cout << "Done." << std::endl << std::flush;

    std::cout << "Integer's test 1" << std::endl;
    test_int_1();
    std::cout << "Integer's test 2" << std::endl;
    test_int_2();
    std::cout << "String's test" << std::endl;
    test_str();

    return 0;
}
