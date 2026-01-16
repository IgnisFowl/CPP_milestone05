/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:58:49 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/16 11:59:02 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm(std::string const& target)
    : AForm("presidential pardon", 25, 5), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const& other)
    : AForm(other), _target(other._target) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(PresidentialPardonForm const& other) {
    if (this != &other) {
        AForm::operator=(other);
        _target = other._target;
    }
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {}

void PresidentialPardonForm::execute(Bureaucrat const& executor) const {
    this->checkCanExecute(executor);
    std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
