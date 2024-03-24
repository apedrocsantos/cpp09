/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:08:30 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/24 15:54:50 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <sys/time.h>
#include <sstream>
#include <algorithm>

class PmergeMe
{
    size_t _list_size;
    unsigned int _lonely;
    bool _pending;
    std::vector<int> _init_list;
    std::deque<std::pair<unsigned int, unsigned int> > _deque;
    std::vector<std::pair<unsigned int, unsigned int> > _vector;
    std::deque<unsigned int> _ordered_d;
    std::deque<unsigned int> _ordered_v;
    suseconds_t _d_begin;
    suseconds_t _d_end;
    suseconds_t _v_begin;
    suseconds_t _v_end;
    PmergeMe(PmergeMe const &that);
    PmergeMe &operator=(PmergeMe const &that);
    unsigned int stoui(std::string number);
    template <typename T> void print_list(T const &container);
    template <typename T> void print_plist(T const &container);
    template <typename T, typename U> void check_ordered(int ac, char **av, T &container, U &ordered);
    int jacobsthal(size_t size);
    template <typename T> void sort_pairs(T &container);
    template <typename T, typename U> void calculate(T &container, U &ordered);
    suseconds_t get_cur_time();
    void print_data();
    template <typename T> void order1(char **av, T &container);
    template <typename T> void order2(char **av, T &container);

    public:
    PmergeMe();
    ~PmergeMe() {};
    void init(int ac, char **av);
};

#endif