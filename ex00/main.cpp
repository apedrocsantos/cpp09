/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:21:33 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/14 23:55:32 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int ac, char **av)
{
    std::string line;
    std::ifstream infile;
    BitcoinExchange be;
    if (ac < 2)
    {
        std::cerr << "Error: please select a file.\n";
        return (0);
    }
    infile.open(av[1]);
    if (!infile)
    {
        std::cerr << "Error: could not open file.\n";
        return (0);
    }
    std::getline(infile, line);
    while (std::getline(infile, line))
    {
        be.addToList(line);
        if ((infile >> std::ws).eof())
            break;
    }
    infile.close();
    // be.getList();
    be.calculate();
    return 0;
}