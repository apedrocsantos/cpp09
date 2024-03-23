/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:08:42 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/23 14:06:47 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Check if ordered with repeated numbers
// List without commas
// sort pairs

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    this->_pending = 0;
}

void PmergeMe::init(int ac, char **av)
{
    std::string list;
    if (ac == 2)
        list = av[1];
    // Get Time
    this->_d_begin = get_cur_time();
    check_ordered(list, this->_deque, this->_ordered_d);
    this->_d_end = get_cur_time();
    
    // Get Time
    this->_v_begin = get_cur_time();
    check_ordered(list, this->_vector, this->_ordered_v);
    this->_v_end = get_cur_time();

    print_data();
    // print_list(this->_ordered_d);
}

void PmergeMe::print_data()
{
    std::cout << "Before:\t";
    int i = 0;
    for (i = 0; i < 3 && i < (int)this->_deque.size(); i++)
    {
        if (i == 2 && this->_list_size > 5)
        {
            std::cout << "[...]";
            break;
        }
        else
            std::cout << this->_deque[i].first;
        if (i < 2)
            std::cout << " " << this->_deque[i].second << " ";
    }
    if (i < 3 && this->_pending)
        std::cout << this->_lonely << " ";
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
    std::cout << "Time to process a range of "  << this->_list_size << " elements with std::deque : " << this->_d_end - this->_d_begin << " us" << std::endl;
    std::cout << "Time to process a range of "  << this->_list_size << " elements with std::vector : " << this->_v_end - this->_v_begin << " us" << std::endl;
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
    
    this->_list_size = 0;
    while (ss >> number)
    {
        this->_list_size += 2;
        if (number[0] == '-')
            throw(std::invalid_argument("Error: invalid argument."));
        nb = stoui(number);
        if (!(ss >> number))
        {
            this->_list_size--;
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
    sort_pairs(container);
    calculate(container, ordered);
}

template <typename T, typename U>
void PmergeMe::calculate(T &container, U &ordered)
{
    size_t size = container.size();
    typename T::iterator it = container.begin();
    typename std::deque<unsigned int>::iterator it_o;
    int i = 1;
    
    while (it != container.end())
        ordered.push_back(it++->second);
    ordered.push_front(container.begin()->first);
    it_o = ordered.begin();
    while (true)
    {
        i = jacobsthal(size);
        i--;
        if (i == -2)
            break;
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
void PmergeMe::sort_pairs(T &container)
{
    // if (it != container.end() && it + 1 != container.end() && it->second > (it + 1)->second)
    // {
    //     std::iter_swap(it, it + 1);
    //     if (it != container.begin())
    //         it--;
    // }
    // else if (it != container.end())
    //     it++;
    // if (it != container.end() && it + 1 != container.end())
    //     sort_pairs(container, it);
    if (container.size() <= 1) {
        return; // Base case: Nothing to sort
    }

    // Divide the vector into two halves
    std::deque<std::pair<unsigned int, unsigned int> > leftHalf(container.begin(), container.begin() + container.size() / 2);
    std::deque<std::pair<unsigned int, unsigned int> > rightHalf(container.begin() + container.size() / 2, container.end());

    // Recursively sort the two halves
    sort_pairs(leftHalf);
    sort_pairs(rightHalf);

    // Merge the sorted halves
    size_t leftIdx = 0;
    size_t rightIdx = 0;
    size_t idx = 0;

    while (leftIdx < leftHalf.size() && rightIdx < rightHalf.size()) {
        container[idx++] = leftHalf[leftIdx].second < rightHalf[rightIdx].second ? leftHalf[leftIdx++] : rightHalf[rightIdx++];
    }

    while (leftIdx < leftHalf.size()) {
        container[idx++] = leftHalf[leftIdx++];
    }

    while (rightIdx < rightHalf.size()) {
        container[idx++] = rightHalf[rightIdx++];
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