/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarie-c2 <aarie-c2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:06:30 by aline-arthu       #+#    #+#             */
/*   Updated: 2026/01/17 11:24:20 by aarie-c2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
    //valid
    try {
        Bureaucrat bob("Bob", 42);
        std::cout << bob << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    //too high
    try {
        Bureaucrat highest("Highest", 0);
    } catch (std::exception& e) {
        std::cout << e.what() <<std::endl;
    }
    //too low
    try {
        Bureaucrat lowest("Lowest", 151);
    } catch (std::exception& e) {
        std::cout << e.what() <<std::endl;
    }
    //increment/decrement
    try {
        Bureaucrat top("Top", 1);
        std::cout << top << std::endl;
        top.incrementGrade();
    } catch (std::exception& e) {
        std::cout << "Increment fail :( " << e.what() << std::endl;
    }
    try {
        Bureaucrat bottom("Bottom", 150);
        std::cout << bottom << std::endl;
        bottom.decrementGrade();
    } catch (std::exception& e) {
        std::cout << "Decrement fail :( " << e.what() << std::endl;
    }
    try {
        Bureaucrat john("John", 84);
        std::cout << john << std::endl;
        john.decrementGrade();
        std::cout << john << std::endl;
        john.incrementGrade();
        std::cout << john << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    //without try and catch, the alarm is sounded but the error is not handled (core dumped)
    /*
    Bureaucrat test("Test", 1);
    test.incrementGrade();
    std::cout << "Fail!";
    */
    return (0);
}
