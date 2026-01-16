/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:06:30 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/16 11:59:27 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"


int main() {
    Bureaucrat president("President", 1);   // Can do everything
    Bureaucrat mid("Mid", 50);              // Some forms only
    
    // 1. Shrubbery (145/137)
    ShrubberyCreationForm tree("garden");
    president.signForm(tree);
    president.executeForm(tree);  // Creates garden_shrubbery
    
    // 2. Robotomy (72/45) 
    RobotomyRequestForm robot("Bender");
    president.signForm(robot);
    president.executeForm(robot);  // Drill + 50/50
    
    // 3. Presidential (25/5)
    PresidentialPardonForm pardon("Marvin");
    president.signForm(pardon);
    president.executeForm(pardon);  // Pardoned!
    
    // Test failures
    mid.signForm(pardon);  // Fail: 50 > 25
    mid.executeForm(tree); // Fail: unsigned or low grade
    return (0);
}
