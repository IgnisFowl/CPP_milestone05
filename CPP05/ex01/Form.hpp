/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:26 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/07 16:18:36 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"
#include <string>

class Bureaucrat;

class Form {
    private:
        std::string const _name;
        bool _signed;
        int const _signGrade;
        int const _executeGrade;

    public:
        Form(std::string name, int signGrade, int executeGrade);
        Form();
        Form(Form const& other);
        Form& operator=(Form const& other);
        ~Form();

        std::string getName() const;
        bool getSigned() const;
        int getSignGrade() const;
        int getExecuteGrade() const;

        void beSigned(Bureaucrat& bureaucrat);
        
        class GradeTooHighException : public std::exception {
            const char* what() const throw();
        };

        class GradeTooLowException : public std::exception {
            const char* what() const throw();
        };
};

std::ostream& operator<<(std::ostream& os, Form const& form);

#endif