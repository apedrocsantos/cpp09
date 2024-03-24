/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:08:48 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/24 15:50:35 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    PmergeMe pm;
    if (ac < 2)
    {
        std::cout << "Error: invalid command. Use ./PmergeMe [list of ints]\n";
        return 0;
    }
    try
    {
        pm.init(ac, ++av);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}