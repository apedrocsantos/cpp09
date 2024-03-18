/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:08:49 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/18 15:42:19 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

#include <sstream>

void RPN::run(std::string list)
{
    float a;
    float b;
    std::stringstream ss(list);
    std::string word;
    
    while (ss >> word)
    {
        if (word.length() != 1)
            throw(std::invalid_argument("Error: Invalid argument."));
        if (word[0] >= 48 && word[0] <= 57)
            this->_stack.push(word[0] - '0');
        else
        {
            if (this->_stack.size() == 1)
                throw(std::invalid_argument("Error: Invalid argument."));
            a = this->_stack.top();
            this->_stack.pop();
            b = this->_stack.top();
            this->_stack.pop();
            switch (word[0])
            {
                case ('+'):
                    this->_stack.push(b + a);
                    break;
                case ('-'):
                    this->_stack.push(b - a);
                    break;
                case ('*'):
                    this->_stack.push(b * a);
                    break;
                case ('/'):
                {
                    if (a == 0)
                        throw(std::invalid_argument("Error: can't divide by zero."));
                    this->_stack.push(b / a);
                    break;
                }
                default:
                    throw(std::invalid_argument("Error: Invalid argument."));
            }
        }
    }
    if (this->_stack.size() != 1)
        throw(std::invalid_argument("Error: Invalid argument."));
    std::cout << this->_stack.top() << std::endl;
}
