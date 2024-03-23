/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:08:51 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/23 14:17:56 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>

/*
8 9 * 9 - 9 - 9 - 4 - 1 -> 42
7 7 * 7 - -> 42
"1 2 * 2 / 2 * 2 4 - + -> 42
(1 + 1) -> error
*/

class RPN
{
    std::stack<float>_stack;
    std::stack<float> const &getStack() const {return this->_stack;};
    RPN() {};
    
    public:
    RPN(RPN const &that);
    RPN &operator=(RPN const &that);
    ~RPN() {};
    void run(std::string list);
};

#endif