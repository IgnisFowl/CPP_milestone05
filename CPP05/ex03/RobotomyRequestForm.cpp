/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:49:19 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/17 11:22:39 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string const& target) : AForm("robotomy request", 72, 45), _target(target) {
    std::srand(std::time(NULL)); //seed random once
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const& other) : AForm(other), _target(other._target) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(RobotomyRequestForm const& other)
{
    if (this != &other)
    {
        AForm::operator=(other);
        _target = other._target;
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::execute(Bureaucrat const& executor) const {
    this->checkCanExecute(executor);

    std::cout << "* Drilling loud BRRRRRRRRRRRRRRRRRRR * " << std::endl;

    if (std::rand() % 2) {
        std::cout << _target << " has been robotomized successfully" << std::endl;
    }
    else {
        std::cout << _target << " robotomy failed" << std::endl;
    }
}