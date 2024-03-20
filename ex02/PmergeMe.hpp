/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:08:30 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/20 15:48:15 by anda-cun         ###   ########.fr       */
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
    std::deque<std::pair<unsigned int, unsigned int> > _deque;
    std::vector<std::pair<unsigned int, unsigned int> > _vector;
    PmergeMe(PmergeMe const &that);
    PmergeMe &operator=(PmergeMe const &that);
    unsigned int stoui(std::string number);
    template <typename T>
    void store_list(std::string list, T &container);
    // void sort_vector(std::string list);
    template <typename T>
    void print_list(T const &container);
    template <typename T>
    void print_plist(T const &container);
    template <typename T>
    void check_ordered(std::string lis, T &container);
    unsigned int jacobsthal();
    template <typename T>
    void recursive(T &container, typename T::iterator it);
    template <typename T>
    void calculate(T &container);

    public:
    PmergeMe();
    ~PmergeMe() {};
    void checkNumber(std::string number);
    void init(std::string list);
};

#endif