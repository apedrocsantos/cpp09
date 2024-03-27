/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:08:42 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/27 15:50:41 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// List without commas
// sort pairs
// ./PmergeMe "2 1" -> Before: list error
// Crash it_o ???

#include "PmergeMe.hpp"
#include <ctime>
#include <iomanip>

PmergeMe::PmergeMe() : _pending(0) {}

PmergeMe::~PmergeMe() {}

void PmergeMe::init(int ac, char **av)
{
    this->_d_begin = get_cur_time();
    get_list(ac, av, this->_deque, this->_ordered_d);
    this->_d_end = get_cur_time();
    
    this->_v_begin = get_cur_time();
    get_list(ac, av, this->_vector, this->_ordered_v);
    this->_v_end = get_cur_time();
    
    print_data();
    // print_list(this->_ordered_v);
}

template <typename T, typename U>
void PmergeMe::get_list(int ac, char **av, T &container, U &ordered)
{
    (void) ac;
    (void) av;
    get_vals(av, container);
    sort_pairs(container);
    calculate(container, ordered);
}

template <typename T>
void PmergeMe::get_vals(char **av, T &container)
{
    unsigned int nb = 0;
    unsigned int nb2 = 0;
    unsigned int comp = 0;
    bool is_ordered = 1;
    int i = 0;
    int counter = -1;
    
    this->_list_size = 0;
    while (av[i])
    {
        this->_list_size += 2;
        if (av[i][0] == '-')
            throw(std::invalid_argument("Error: invalid argument."));
        nb = stoui(av[i]);
        if (++counter < 6)
            this->_init_list.push_back(nb);
        if (!av[i + 1])
        {
            this->_list_size--;
            this->_pending = 1;
            is_ordered && comp <= stoui(av[i]) == 1 ? is_ordered = 1 : is_ordered = 0;
            this->_lonely = stoui(av[i]);
            break;
        }
        nb2 = stoui(av[i + 1]);
        if (++counter < 6)
            this->_init_list.push_back(nb2);
        if (nb <= nb2)
            container.push_back(std::make_pair(nb, nb2));
        else
            container.push_back(std::make_pair(nb2, nb));
        is_ordered && nb <= nb2 && comp <= nb == 1 ? is_ordered = 1 : is_ordered = 0;
        comp = nb2;
        i += 2;
    }
    if (is_ordered)
                throw(std::invalid_argument("List is ordered."));
}

template <typename T>
void PmergeMe::sort_pairs(T &container)
{
    static int j = 1;
    if (container.size() <= 1 || j >= (int)container.size())
        return;
    size_t i;
    for (i = 0; i < container.size() - 1; i++)
        if (container[i].second > container[j].second)
			std::swap(container[i], container[j]);
    j++;
    sort_pairs(container);
}



template <typename T, typename U>
void PmergeMe::calculate(T &container, U &ordered)
{
    size_t size = container.size();
    typename T::iterator it = container.begin();
    typename U::iterator it_o;
    int i = 1;
    
    while (it != container.end())
        ordered.push_back(it++->second);
    ordered.insert(ordered.begin(), container.begin()->first);
    it_o = ordered.begin();
    while (true)
    {
        i = jacobsthal(size);
        if (i == -1)
            break;
        i--;
        while (it_o != ordered.end())
        {
            while (container[i].first > *it_o && it_o != ordered.end())
                it_o++;
            if (container[i].first <= *it_o || it_o == ordered.end())
            {
                ordered.insert(it_o, container[i].first);
                it_o = ordered.begin();
                if(it_o != ordered.begin())
                    it_o--;
                break;
            }
        }
    }
    if (this->_pending)
    {
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
        std::cout << *it << " ";
    std::cout << std::endl << "FINISHED PRINTING\n";
}

template <typename T>
void PmergeMe::print_plist(T const &container)
{
    typename T::const_iterator it;
    for (it = container.begin(); it != container.end(); it++)
        std::cout << it->first << "," << it->second << std::endl;
}

suseconds_t PmergeMe::get_cur_time()
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void PmergeMe::print_data()
{
    std::cout << "Before:\t";
    for (int i = 0; i < 5 && i < (int)this->_list_size; i++)
    {
        if (i == 4 && this->_list_size > 5)
        {
            std::cout << "[...]";
            break;
        }
        std::cout << this->_init_list[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "After:\t";
    for (int i = 0; i < 5 && i < (int)this->_list_size; i++)
    {
        if (i == 4 && this->_list_size > 5)
        {
            std::cout << "[...]";
            break;
        }
        std::cout << this->_ordered_d[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Time to process a range of "  << this->_list_size << " elements with std::vector : " <<this->_v_end - this->_v_begin << " us" << std::endl;
    std::cout << "Time to process a range of "  << this->_list_size << " elements with std::deque : " <<this->_d_end - this->_d_begin << " us" << std::endl;
}
