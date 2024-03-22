/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:08:42 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/22 19:07:43 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>
#include <chrono>
#include <ctime>    

PmergeMe::PmergeMe()
{
    this->_moves = 0;
    this->_pending = 0;
}

void PmergeMe::init(std::string list)
{
    // int i = 0;
    // while (i != -1)
    // {
    //     i = jacobsthal(4);
    //     std::cout << i << std::endl;
    // }
    // exit(1);
    // Get Time
    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    clock_t deque_start = clock();
    check_ordered(list, this->_deque, this->_ordered_d);
    clock_t deque_end = clock();
    double deque_duration = double(deque_end - deque_start) / CLOCKS_PER_SEC * 1e6;
    std::cout << "Time to process: " << deque_duration << " us" << std::endl;
    clock_t vector_start = clock();
    check_ordered(list, this->_vector, this->_ordered_v);
    clock_t vector_end = clock();
    double vector_duration = double(vector_end - vector_start) / CLOCKS_PER_SEC * 1e6;
    std::cout << "Time to process: " << vector_duration << " us" << std::endl;
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    // // Get end time
    
    // // // Get time
    // store_list(list, this->_vector);
    // print_list(this->_vector);
    // // Get end time
}

template <typename T, typename U>
void PmergeMe::check_ordered(std::string list, T &container, U &ordered)
{
    std::deque<int> sorted;
    std::deque<int> pend;
    std::stringstream ss(list);
    std::string number;
    unsigned int nb = 0;
    unsigned int nb2 = 0;
    unsigned int comp = 0;
    bool is_ordered = 1;

    while (ss >> number)
    {
        if (number[0] == '-')
            throw(std::invalid_argument("Error: invalid argument."));
        nb = stoui(number);
        if (!(ss >> number))
        {
            this->_pending = 1;
            is_ordered && comp <= stoui(number) == 1 ? is_ordered = 1 : is_ordered = 0;
            this->_lonely = stoui(number);
            break;
        }
        nb2 = stoui(number);
        if (nb <= nb2)
            container.push_back(std::make_pair(nb, nb2));
        else
            container.push_back(std::make_pair(nb2, nb));
        is_ordered && nb < nb2 && comp <= nb == 1 ? is_ordered = 1 : is_ordered = 0;
        comp = nb2;
    }
    if (is_ordered)
                throw(std::invalid_argument("List is ordered."));
    recursive(container, container.begin());
    calculate(container, ordered);
}

template <typename T, typename U>
void PmergeMe::calculate(T &container, U &ordered)
{
    size_t size = container.size();
    typename T::iterator it = container.begin();
    typename std::deque<unsigned int>::iterator it_o = ordered.begin();
    int i = 1;
    
    while (it != container.end())
        ordered.push_back(it++->second);
    ordered.push_front(container.begin()->first);
    while (true)
    {
        i = jacobsthal(size);
        i--;
        if (i == -2)
            break;
        while (it_o != ordered.end())
        {
            if (container[i].first < *it_o)
            {
                ordered.insert(it_o, container[i].first);
                break;
            }
            if (*it_o > container[i].first)
                it_o++;
            else
                it_o--;
        }
    }
    if (this->_pending)
    {
        it_o = ordered.begin();
        while (it_o != ordered.end())
        {
            if (this->_lonely < *it_o)
            {
                ordered.insert(it_o, this->_lonely);
                break;
            }
            if ((it_o + 1) == ordered.end())
            {
                ordered.insert(it_o + 1, this->_lonely);
                break;
            }
            it_o++;
        }
    }
}

template <typename T>
void PmergeMe::recursive(T &container, typename T::iterator it)
{
    if (it != container.end() && it + 1 != container.end() && it->second > (it + 1)->second)
    {
        std::iter_swap(it, it + 1);
        if (it != container.begin())
            it--;
    }
    else if (it != container.end())
        it++;
    if (it != container.end() && it + 1 != container.end())
        recursive(container, it);
}

int PmergeMe::jacobsthal(size_t size)
{
    // {0, 1, 1, ..., a, b, c}
    static unsigned int a = 1;
    static unsigned int b = 1;
    static unsigned int c = 1;
    static bool flag = false;
    
    if (c > a)
    {
        c--;
        if (c > a)
            return (c);
    }
    if (!flag)
    {
        c = b + 2 * a;
        a = b;
        b = c;
        if (c >= size)
        {
            flag = 1;
            while (c > size)
                c--;
        }
        if (c > a)
            return (c);
    }
    a = 1;
    b = 1;
    c = 1;
    flag = false;
    return (-1);
}

unsigned int PmergeMe::stoui(std::string number)
{
    std::stringstream ss;
    unsigned int nb;
    int i = -1;

    ss << number;
    if (!(ss >> nb))
        throw(std::out_of_range("Error: invalid value."));
    while (number[++i])
        if (!isdigit(number[i]))
            throw(std::out_of_range("Error: invalid value."));
    return (nb);
}

template <typename T>
void PmergeMe::print_list(T const &container)
{
    typename T::const_iterator it;
    std::cout << "PRINTING\n";
    for (it = container.begin(); it != container.end(); it++)
        std::cout << *it << std::endl;
    std::cout << "FINISHED PRINTING\n";
}

template <typename T>
void PmergeMe::print_plist(T const &container)
{
    typename T::const_iterator it;
    for (it = container.begin(); it != container.end(); it++)
        std::cout << it->first << "," << it->second << std::endl;
}