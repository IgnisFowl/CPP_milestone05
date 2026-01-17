/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:06:30 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/17 11:35:41 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"


int main() {
    Intern someRandomIntern;
    Bureaucrat boss("Boss", 1);

    AForm* f1 = someRandomIntern.makeForm("shrubbery creation", "home");
    AForm* f2 = someRandomIntern.makeForm("robotomy request", "Bender");
    AForm* f3 = someRandomIntern.makeForm("presidential pardon", "Marvin");

    (void)someRandomIntern.makeForm("unknown form", "Nobody");
      
    if (f1) {
        boss.signForm(*f1);
        boss.executeForm(*f1);
    }
    if (f2) {
        boss.signForm(*f2);
        boss.executeForm(*f2);
    }
    if (f3) {
        boss.signForm(*f3);
        boss.executeForm(*f3);
    }

    delete f1;
    delete f2;
    delete f3;
    // f4 is null, no delete
    return (0);
}
