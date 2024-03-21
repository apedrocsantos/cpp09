/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:08:42 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/21 21:47:46 by anda-cun         ###   ########.fr       */
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
            this->_pending = 1;
            ordered && comp <= stoui(number) == 1 ? ordered = 1 : ordered = 0;
            this->_lonely = stoui(number);
            break;
        }
        nb2 = stoui(number);
        if (nb <= nb2)
            container.push_back(std::make_pair(nb, nb2));
        else
            container.push_back(std::make_pair(nb2, nb));
        ordered && nb < nb2 && comp <= nb == 1 ? ordered = 1 : ordered = 0;
        comp = nb2;
    }
    if (ordered)
                throw(std::invalid_argument("List is ordered."));
    recursive(container, container.begin());
    calculate(container);
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
    ordered.push_front(container.begin()->first);
    print_plist(container);
    while (true)
    {
        i = jacobsthal() - 1;
        if (i >= container.size())
        {
            i = jacobsthal() - 1;
            while (i >= container.size())
            {
                if (i > 10)
                {
                    std::cout << "BREAKING\n";
                    break;
                }
                std::cout << i << "\n";
                i = jacobsthal() - 1;
            }
            while (i < container.size())
            {
                std::cout << "HH\n";
                it_o = ordered.begin();
                while (it_o != ordered.end())
                {
                    if (container[i].first < *it_o)
                    {
                        ordered.insert(it_o, container[i].first);
                        break;
                    }
                    it_o++;
                }
                i = jacobsthal() - 1;
            }
            if (this->_pending)
            {
                print_list(ordered);
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
            break;
        }
        it_o = ordered.begin();
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
    print_list(ordered);
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