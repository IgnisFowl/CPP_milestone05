/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:19:02 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/14 09:34:13 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>
#include "Aform.hpp"

class Aform;

class Bureaucrat {
    private: 
        std::string const _name;
        int _grade;

    public:
        Bureaucrat(std::string name, int grade);
        Bureaucrat(); //default
        Bureaucrat (Bureaucrat const& other); //copy
        Bureaucrat& operator=(Bureaucrat const& other); //assign
        ~Bureaucrat();
    
    std::string getName() const;
    int getGrade() const;
    void incrementGrade();
    void decrementGrade();
    void signForm(Aform& aform);

    class GradeTooHighException : public std::exception {
        public:
            const char* what() const throw();
    };

    class GradeTooLowException : public std::exception  {
        public:
            const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& os, Bureaucrat const& bureaucrat);

#endif