/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:08:42 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/20 15:19:29 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>
#include <chrono>
#include <ctime>    

PmergeMe::PmergeMe()
{
    this->_moves = 0;
}

void PmergeMe::init(std::string list)
{
    // Get Time
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    check_ordered(list, this->_deque);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    // // Get end time
    
    // // // Get time
    // store_list(list, this->_vector);
    // print_list(this->_vector);
    // // Get end time
}

template <typename T>
void PmergeMe::check_ordered(std::string list, T &container)
{
    std::deque<int> sorted;
    std::deque<int> pend;
    std::stringstream ss(list);
    std::string number;
    unsigned int nb = 0;
    unsigned int nb2 = 0;
    unsigned int comp = 0;
    bool ordered = 1;

    while (ss >> number)
    {
        if (number[0] == '-')
            throw(std::invalid_argument("Error: invalid argument."));
        nb = stoui(number);
        if (!(ss >> number))
        {
            ordered && comp <= stoui(number) == 1 ? ordered = 1 : ordered = 0;
            this->_lonely = stoui(number);
            break;
        }
        nb2 = stoui(number);
        if (nb <= nb2)
            container.push_back(std::make_pair(nb, nb2));
        else
            container.push_back(std::make_pair(nb2, nb));
        this->_moves++;
        ordered && nb < nb2 && comp <= nb == 1 ? ordered = 1 : ordered = 0;
        comp = nb2;
    }
    if (ordered)
                throw(std::invalid_argument("List is ordered."));
    recursive(container);
    // std::cout << "PRINGINT\n";
    // print_plist(container);
    calculate(container);
    // print_list(this->_deque);
}

template <typename T>
void PmergeMe::calculate(T &container)
{
    std::deque<unsigned int> ordered;
    typename T::iterator it = container.begin();
    typename std::deque<unsigned int>::iterator it_o;
    unsigned int i = 1;
    
    while (it != container.end())
        ordered.push_back(it++->second);
    container.push_back(std::make_pair(0, this->_lonely));
    ordered.push_front(container.begin()->first);
    while (i < container.size())
    {
        it_o = ordered.begin();
        i = jacobsthal();
        while (it_o != ordered.end())
        {
            if (container[i].first < *it_o)
            {
                ordered.insert(it_o, container[i].first);
                break;
            }
            it_o++;
        }
    }
    // print_list(ordered);
}

template <typename T>
void PmergeMe::recursive(T &container)
{
    static typename T::iterator it = container.begin();
    if (it->second > (it + 1)->second)
        std::iter_swap(it, it-- + 1);
    else
        it++;
    if (it + 1 != container.end())
        recursive(container);
}

unsigned int PmergeMe::jacobsthal()
{
    // {0, 1, 1, ..., a, b, c}
    static unsigned int a = 1;
    static unsigned int b = 1;
    static unsigned int c = 1;
    
    if (c > a)
    {
        c--;
        if (c > a)
            return (c);
    }
    c = b + 2 * a;
    a = b;
    b = c;
    return (c);
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
    for (it = container.begin(); it != container.end(); it++)
        std::cout << *it << std::endl;
}

template <typename T>
void PmergeMe::print_plist(T const &container)
{
    typename T::const_iterator it;
    for (it = container.begin(); it != container.end(); it++)
        std::cout << it->first << "," << it->second << std::endl;
}