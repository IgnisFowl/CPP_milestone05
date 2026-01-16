/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:14:58 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/16 11:35:43 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string const& target) : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const& other) : AForm(other), _target(other._target) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(ShrubberyCreationForm const& other)
{
    if (this != &other) {
        AForm::operator=(other);
        _target = other._target;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
    this->checkCanExecute(executor);
    std::string filename = _target + "_shrubbery";
    std::ofstream file(filename.c_str());
 
    if (!file.is_open()) {
        std::cout << "Error: cannot create shruberry file" << std::endl;
        return;
    }

    file << "         /\\\n"
            "        /**\\\n"
            "       /****\\\n"
            "      /******\\\n"
            "     /********\\\n"
            "    /**********\\\n"
            "   /*****| *****\\\n"
            "  /*****|  |*****\\\n"
            " /*****| |  |*****\\\n"
            "      | | | | |\n"
            "      | | | | |\n"
            "      | | | | |\n";
    file.close();
}