/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:08:30 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/22 20:49:19 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>

class PmergeMe
{
    size_t _moves;
    unsigned int _lonely;
    bool _pending;
    std::deque<std::pair<unsigned int, unsigned int> > _deque;
    std::vector<std::pair<unsigned int, unsigned int> > _vector;
    std::deque<unsigned int> _ordered_d;
    std::deque<unsigned int> _ordered_v;
    PmergeMe(PmergeMe const &that);
    PmergeMe &operator=(PmergeMe const &that);
    unsigned int stoui(std::string number);
    template <typename T>
    void store_list(std::string list, T &container);
    template <typename T>
    void print_list(T const &container);
    template <typename T>
    void print_plist(T const &container);
    template <typename T, typename U>
    void check_ordered(std::string lis, T &container, U &ordered);
    int jacobsthal(size_t size);
    template <typename T>
    void recursive(T &container, typename T::iterator it);
    template <typename T, typename U>
    void calculate(T &container, U &ordered);

    public:
    PmergeMe();
    ~PmergeMe() {};
    void init(std::string list);
};

#endif