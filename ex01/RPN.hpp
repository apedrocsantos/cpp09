/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:08:51 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/17 23:19:25 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

/*
8 9 * 9 - 9 - 9 - 4 - 1 -> 42
7 7 * 7 - -> 42
"1 2 * 2 / 2 * 2 4 - + -> 42
(1 + 1) -> error
*/

class RPN
{
    std::stack<float>_stack;
    
    public:
    RPN();
    RPN(RPN const &that);
    RPN &operator=(RPN const &that);
    ~RPN();
    template<typename T> T &add(T const & n1, T const & n2);
    template<typename T> T &subtract(T const & n1, T const & n2);
    template<typename T> T &multiply(T const & n1, T const & n2);
    template<typename T> T &divide(T const & n1, T const & n2);
};

#endif