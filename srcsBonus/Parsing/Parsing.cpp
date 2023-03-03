/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:49:51 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/21 00:06:53 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Command.hpp"
#include "../../includes/Parsing.hpp"

void	checkCommand(std::string buffer, std::vector<std::string> vect, Server &ircServ, int client_fd)
{
	Parsing	parsing(ircServ, buffer, client_fd, vect);

	parsing.parser(vect.front());
}

std::vector<std::string>	parseCmdString(std::string trim)
{
	std::vector<std::string> vect;

	if (trim == "\r\n")
		return (vect);
	
	std::istringstream		iss(trim);
	std::string				token;

	while (std::getline(iss, token, ' '))
	{
		trim = token;
		trim.erase(trim.find_last_not_of("\r\n")+1);
		if (trim != "")
			vect.push_back(trim);
	}
	return (vect);
}

std::vector<std::string>	parseCmdStringTest(std::string trim)
{
	std::vector<std::string> vect;

	if (trim == "\r\n")
		return (vect);
	std::istringstream		iss(trim);
	std::string				token;

	while (std::getline(iss, token, '\n'))
	{
		trim = token;
		trim.erase(trim.find_last_not_of("\r\n")+1);
		if (trim != "")
			vect.push_back(trim);
	}
	return (vect);
}

void	parsing(std::string buffer, Server &ircServ, int client_fd)
{
	std::vector<std::string>	vect;
	std::vector<std::string>	param;
	User						*user = ircServ.findUser(client_fd);

	if (user == NULL)
	{
		User					create_user;
		ircServ.add_user(client_fd, create_user);
		user = ircServ.findUser(client_fd);
	}

	std::string					buf = user->getBuf();
	buf += buffer;

	user->setBuf(buf);
	if (buf.find("\r\n") == buf.npos)
		return ;

	vect = parseCmdStringTest(buf);
	if (vect.size() == 0)
		return ;

	std::vector<std::string>::iterator	it = vect.begin();
	std::vector<std::string>::iterator	ite = vect.end();

	if (*it == "CAP LS" || *it == "WHOIS")
		it++;

	while (it != ite)
	{
		param = parseCmdString(*it);
		if (param.size() != 0 && param[0] != "WHOIS")
			checkCommand(*it, param, ircServ, client_fd);
		it++;
	}

	user->setBuf("");

	if (user->getPass() == 2 || user->getPass() == 0)
	{
		std::cout << "DELETE USER" << std::endl;
		ircServ.delete_user(client_fd);
	}
}
