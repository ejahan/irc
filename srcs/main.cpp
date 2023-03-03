/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 03:28:17 by grannou           #+#    #+#             */
/*   Updated: 2023/02/16 12:26:16 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

// Global variable to to handle signal interruption
int    serverIsRunning = 1;

// Function to handle interruption signal
void    signalHandler(int signalNumber)
{
    ssize_t ret = write(1, "\b\b", 2);
    if (ret < 0)
        std::cout << "\b\b" << std::endl;
    std::cout << YELLOW << "Interrupt signal (" << RESET << signalNumber << YELLOW << ") received" << RESET << std::endl;
    serverIsRunning = 0;
}

int main(int argc, char **argv)
{
    if (checkArguments(argc, argv))
        return (1);

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    Server      ircServ = Server(argv[1], argv[2]);

    if (ircServ.setup())
        return (printErrorMessage(INIT_SERVER_ERROR), 1);

    if (ircServ.chatBotSetup())
        return (printErrorMessage(INIT_CHATBOT_ERROR), 1);

    std::cout << ircServ << std::endl;
    print_log("The server started successfully");

    while (serverIsRunning)
    {
        ircServ.run();
    }
    print_log("Shutting down server");
    
    return (0);
}
