/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:06:30 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/07 16:18:18 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
    //test form constructor exceptions
    try { Form("bad", 0, 10); 
    } catch(std::exception& e) { std::cout << e.what() << std::endl; }
    
    Form form1("Contract", 50, 30);
    std::cout << form1 << std::endl;  // Contract, sign 50, exec 30, signed no.
    
    Bureaucrat high("High", 40);
    Bureaucrat low("Low", 60);
    
    std::cout << high << std::endl;
    high.signForm(form1);  // Success: High signs Contract
    
    std::cout << form1 << std::endl;  // Now signed yes
    low.signForm(form1);   // Fail: Low cannot sign because grade too low
    return (0);
}
