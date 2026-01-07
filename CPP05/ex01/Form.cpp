/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:08:03 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/07 16:22:23 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(std::string name, int signGrade, int executeGrade) : _name(name), _signed(false), _signGrade(signGrade), _executeGrade(executeGrade) {
    if (_signGrade < 1 || _executeGrade < 1)
        throw Form::GradeTooHighException();
    if (_signGrade > 150 || _executeGrade > 150)
        throw Form::GradeTooLowException();
}

Form::Form() : _name("Default"), _signed(false), _signGrade(150), _executeGrade(150) {}

Form::Form(Form const& other) : _name(other._name), _signed(other._signed), _signGrade(other._signGrade), _executeGrade(other._executeGrade) {}

Form& Form::operator=(Form const& other) {
    if (this != &other) {
        const_cast<bool&>(_signed) = other._signed; //mutable signed
    }
    return *this;
}

Form::~Form() {}

std::string Form::getName() const { return _name; }
bool Form::getSigned() const { return _signed; }
int Form::getSignGrade() const { return _signGrade; }
int Form::getExecuteGrade() const { return _executeGrade; }

void Form::beSigned(Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() <= _signGrade)
        _signed = true;
    else
        throw Form::GradeTooLowException();
}

const char* Form::GradeTooHighException::what() const throw() {
    return "Form grade too high";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Form grade too low";
}

std::ostream& operator<<(std::ostream& os, Form const& form) {
    os << form.getName() << ", form sign grade " << form.getSignGrade()
        << ", execute grade " << form.getExecuteGrade()
        << ", signed: " << (form.getSigned() ? "yes" : "no") << ".";
    return os;
}