/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:00:26 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/16 11:22:56 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"
#include <string>

class Bureaucrat;

class AForm {
    private:
        std::string const _name;
        bool _signed;
        int const _signGrade;
        int const _executeGrade;

    public:
        AForm(std::string name, int signGrade, int executeGrade);
        AForm();
        AForm(AForm const& other);
        AForm& operator=(AForm const& other);
        virtual ~AForm();

        std::string getName() const;
        bool isSigned() const;
        int getSignGrade() const;
        int getExecuteGrade() const;

        void beSigned(Bureaucrat& bureaucrat);

        virtual void execute(Bureaucrat const& executor) const = 0;

        void checkCanExecute(Bureaucrat const& executor) const;
        
        class GradeTooHighException : public std::exception {
            public:
                virtual const char* what() const throw();
        };

        class GradeTooLowException : public std::exception {
            public:
                virtual const char* what() const throw();
        };

        class NotSignedException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

std::ostream& operator<<(std::ostream& os, AForm const& form);

#endif