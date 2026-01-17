/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:14:58 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/17 11:22:45 by aarie-c2         ###   ########.fr       */
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