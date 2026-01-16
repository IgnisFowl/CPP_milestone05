/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:43:58 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/16 11:55:41 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Buraucrat;

class RobotomyRequestForm : public AForm {
    private:
        std::string _target;
    
    public:
        RobotomyRequestForm(std::string const& target);
        RobotomyRequestForm(RobotomyRequestForm const& other);
        RobotomyRequestForm& operator=(RobotomyRequestForm const& other);
        ~RobotomyRequestForm();
    
    void execute(Bureaucrat const& executor) const;
};

#endif