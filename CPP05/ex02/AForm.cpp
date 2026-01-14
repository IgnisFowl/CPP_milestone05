/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:08:03 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/14 09:51:31 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(std::string name, int signGrade, int executeGrade) : _name(name), _signed(false), _signGrade(signGrade), _executeGrade(executeGrade) {
    if (_signGrade < 1 || _executeGrade < 1)
        throw Form::GradeTooHighException();
    if (_signGrade > 150 || _executeGrade > 150)
        throw Form::GradeTooLowException();
}

AForm::AForm() : _name("Default"), _signed(false), _signGrade(150), _executeGrade(150) {}

AForm::AForm(Form const& other) : _name(other._name), _signed(other._signed), _signGrade(other._signGrade), _executeGrade(other._executeGrade) {}

AForm& AForm::operator=(Form const& other) {
    if (this != &other) {
        const_cast<bool&>(_signed) = other._signed; //mutable signed
    }
    return *this;
}

AForm::~AForm() {}

std::string AForm::getName() const { return _name; }
bool AForm::getSigned() const { return _signed; }
int AForm::getSignGrade() const { return _signGrade; }
int AForm::getExecuteGrade() const { return _executeGrade; }

void AForm::beSigned(Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() <= _signGrade)
        _signed = true;
    else
        throw AForm::GradeTooLowException();
}

void AForm::checkCanExecute(Bureaucrat const& executor) const {
    if (!_signed) 
    {
        throw AForm::NotSignedException();
    }
    if (executor.getGrade() > _executeGrade)
    {
        throw AForm::GradeTooLowException();
    }
}

const char* AForm::GradeTooHighException::what() const throw() {
    return "Form grade too high";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "Form grade too low";
}

const char* AForm::NotSignedException::what() const throw() {
    return "Form not signed";
}


std::ostream& operator<<(std::ostream& os, AForm const& form) {
    os << form.getName() << ", form sign grade " << form.getSignGrade()
        << ", execute grade " << form.getExecuteGrade()
        << ", signed: " << (form.getSigned() ? "yes" : "no") << ".";
    return os;
}