/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:21:32 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/14 23:24:19 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <vector>

class BitcoinExchange
{
    int _year;
    int _month;
    int _day;
    float _value;
    std::vector<std::string> _lst;
    public:
    BitcoinExchange();
    BitcoinExchange(BitcoinExchange const &that);
    BitcoinExchange &operator=(BitcoinExchange const &that);
    ~BitcoinExchange();
    void addToList(std::string string);
    void getList();
    float stof(std::string string);
    void checkDate(std::string date);
    void checkValue(std::string value);
    bool leapYear(int year);
    void calculate();
    void getLine();
};

#endif