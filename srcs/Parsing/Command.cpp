/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:42:51 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 09:03:50 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Command.hpp"
#include "../../includes/Parsing.hpp"

Command::Command() {}

Command::~Command() {}

Command::Command(Command const &src)
{
	*this = src;
	return ;
}

///////////////////////////////////////////////
//	ADD
///////////////////////////////////////////////

void	Command::add_channels(std::string channel)
{
	if (channel.c_str()[0] != '#')
		channel = "#" + channel;
	this->channels.push_back(lowerCase(channel));
}

void	Command::add_nick(std::string nick)
{
	this->nick.push_back(lowerCase(nick));
}

void	Command::add_server(std::string server)
{
	this->server.push_back(server);
}

void	Command::add_message(std::string test_message)
{
	this->message.push_back(test_message);
}

void	Command::add_client_fd(int client_fd)
{
	this->client_fd = client_fd;
}

////////////////////////////////////////////
//	PRINT
////////////////////////////////////////////

void	Command::print_channels()
{
	std::vector<std::string>::iterator	it = channels.begin();
	std::vector<std::string>::iterator	ite = channels.end();

	std::cout << MAGENTA << "CHANNELS:" << RESET << std::endl;

	while (it != ite)
	{
		std::cout << "[" << *it << "]" << std::endl;
		it++;
	}
}

void	Command::print_nick()
{
	size_t	i = 0;

	std::cout << MAGENTA << "NICK:" << RESET << std::endl;
	while (i < this->nick.size())
	{
		std::cout << "[" << nick[i] << "]" << std::endl;
		i++;
	}
}

void	Command::print_server()
{
	size_t	i = 0;

	std::cout << MAGENTA << "SERVER:" << RESET << std::endl;
	while (i < this->server.size())
	{
		std::cout << "[" << server[i] << "]" << std::endl;
		i++;
	}
}

void	Command::print_message()
{
	std::vector<std::string>::iterator	it = message.begin();
	std::vector<std::string>::iterator	ite = message.end();

	std::cout << MAGENTA << "MESSAGE:" << RESET << std::endl;

	while (it != ite)
	{
		std::cout << "[" << *it << "]" << std::endl;
		it++;
	}
}

void	Command::print_all()
{
	std::cout << std::endl << CYAN << "NEW COMMAND" << RESET << std::endl;
	print_channels();
	print_nick();
	print_server();
	print_message();
}

////////////////////////////////////////
//	GET SIZE
////////////////////////////////////////

int	Command::get_size_channels()
{
	return static_cast<int>(static_cast<long int>(this->channels.size()));
}

int	Command::get_size_nick()
{
	return static_cast<int>(static_cast<long int>(this->nick.size()));

}

int	Command::get_size_server()
{
	return static_cast<int>(static_cast<long int>(this->server.size()));
}

int	Command::get_size_message()
{
	return static_cast<int>(static_cast<long int>(this->message.size()));
}

//////////////////////////////////////////
//	GET VECTOR
//////////////////////////////////////////

std::vector<std::string>	Command::getChannels()
{
	for (std::vector<std::string>::iterator it = this->channels.begin(); it != this->channels.end(); it++)
	{
		std::string str = *it;
		if (str.c_str()[0] != '#')
			*it = "#" + *it;
	}
	return (this->channels);
}

std::vector<std::string>	Command::getNickname()
{
	return (this->nick);
}

std::vector<std::string>	Command::getServer()
{
	return (this->server);
}

std::vector<std::string>	Command::getMessage()
{
	return (this->message);
}

int	Command::getClientSfd()
{
	return (this->client_fd);
}
