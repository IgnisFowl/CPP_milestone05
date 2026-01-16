/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aline-arthur <aline-arthur@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:12:49 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/16 11:30:18 by aline-arthu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <string>
#include <fstream>

class Bureaucrat;

class ShrubberyCreationForm : public AForm {
    private:
        std::string _target;
    
    public:
        ShrubberyCreationForm(std::string const& target);
        ShrubberyCreationForm(ShrubberyCreationForm const& other);
        ShrubberyCreationForm& operator=(ShrubberyCreationForm const& other);
        ~ShrubberyCreationForm();
        
        void execute(Bureaucrat const& executor) const;
};


#endif