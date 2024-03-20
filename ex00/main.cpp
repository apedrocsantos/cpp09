/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:21:33 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/18 21:09:12 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: please select a file.\n";
        return (0);
    }
    BitcoinExchange be(av[1]);
    return 0;
}