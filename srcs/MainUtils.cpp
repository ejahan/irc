/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:27:37 by grannou           #+#    #+#             */
/*   Updated: 2023/02/08 01:27:41 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

// Print error message with emoji frame
void     printErrorMessage(std::string msg)
{
    std::cerr << KYU BIE << msg << BIE KYU << std::endl;
}

// Print message with logtime
void    print_log(const std::string &message)
{
	time_t      secs = std::time(0);
	struct tm   *curr_time = localtime(&secs);
	std::cout << RED << "[" << curr_time->tm_hour << "h" << curr_time->tm_min << "m" << curr_time->tm_sec << "s] "  <<  RESET << message << std::endl;
}

// Check if a string is an integer
bool     isInteger(const char *str)
{
    char        *end;
    strtol(str, &end, 10);
    if (*end != '\0' || end == str)
        return (false);
    return (true);
}

// Parsing of program input
int     checkArguments(int argc, char **argv)
{
    try
    {
        if (argc != 3)
        {
            throw std::runtime_error(KYU BIE ARGS_ERROR PROGRAM_LAUNCH1 PROGRAM_LAUNCH2 BIE KYU);
        }
        if (!isInteger(argv[1]))
        {
            throw std::runtime_error(KYU BIE PORT_DIGIT_ERROR BIE KYU);
        }
        long int argv1 = std::atoll(argv[1]);
        if (argv1 <= 0 || argv1 > PORT_MAX)
        {
            throw std::runtime_error(KYU BIE PORT_RANGE_ERROR BIE KYU);
        }
        std::string argv2(argv[2]);
        if (argv2.length() > SERVER_PASSWORD_LENGTH)
        {
            throw std::runtime_error(KYU BIE PASSWORD_ERROR BIE KYU);
        }
        std::cout << KYU BIE VALID_INPUT BIE KYU << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}

// Initialise bytes with a given value
void    *ft_memset(void *ptr, int value, std::size_t len)
{
    while (len--)
        ((unsigned char *)ptr)[len] = (unsigned char)value;
    return (ptr);
}

// Clean free of everything
void    cleanExit(void)
{
    std::cout << GREEN << "THIS IS A CLEAN AND LEAK FREE PROGRAM EXIT" << RESET << std::endl;
}

