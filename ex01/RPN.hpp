/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:08:51 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/18 15:37:23 by anda-cun         ###   ########.fr       */
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
    int _result;
    int _b;
    int add(int const a, int const b);
    int subtract(int const a, int const b);
    int multiply(int const a, int const b);
    int divide(int const a, int const b);
    void calculate();
    
    public:
    RPN() {};
    RPN(RPN const &that);
    RPN &operator=(RPN const &that);
    ~RPN() {};
    void run(std::string list);
};

#endif