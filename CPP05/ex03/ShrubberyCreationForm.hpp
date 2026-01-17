/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:12:49 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/17 11:22:48 by aarie-c2         ###   ########.fr       */
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