/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 11:22:24 by aarie-c2          #+#    #+#             */
/*   Updated: 2026/01/17 11:39:00 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {}
Intern::Intern(Intern const& other) {
    (void)other;
}
Intern& Intern::operator=(Intern const& other) {
    (void)other;
    return *this;
}

Intern::~Intern() {}

static AForm* createShrubbery(std::string const& target) {
    return new ShrubberyCreationForm(target);
}

static AForm* createRobotomy(std::string const& target) {
    return new RobotomyRequestForm(target);
}

static AForm* createPardon(std::string const& target) {
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(std::string const& name, std::string const& target) const {
    typedef AForm* (*FormCreator)(std::string const&);
    
    // Estrutura: nome → ponteiro de função
    const struct {
        std::string name;
        FormCreator creator;
    } forms[] = {
        {"shrubbery creation", createShrubbery},
        {"robotomy request", createRobotomy},
        {"presidential pardon", createPardon},
        {"", 0}  // Sentinel
    };

    for (int i = 0; forms[i].name != ""; ++i) {
        if (name == forms[i].name) {
            AForm* form = (forms[i].creator)(target);
            std::cout << "Intern creates " << form->getName() << std::endl;
            return form;
        }
    }
    
    std::cout << "Intern cannot create form called \"" << name << "\"" << std::endl;
    return 0;
}
   
    