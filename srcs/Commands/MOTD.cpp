/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MOTD.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:23:37 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 23:53:38 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

void	motdCmd(Command &cmd, Server &ircServ)
{
	std::string	motd = "\n";
	std::ifstream file("./motd.txt");
	User *user = ircServ.findUser(cmd.getClientSfd());

	std::string	start = RPL_MOTDSTART(user->getHostname());
	send(cmd.getClientSfd(), start.c_str(), start.size(), 0);
	
	if(file)
	{
		std::string line;
		while (std::getline(file, line))
		{
			motd += line;
			motd += "\n";
		}
		std::string msg = RPL_MOTD(user->getHostname(), motd);
		send(cmd.getClientSfd(), msg.c_str(), msg.size(), 0);
		file.close();
	}
	else
	{
		std::string err = ERR_NOMOTD(user->getHostname());
		send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
	}
	std::string end = RPL_ENDOFMOTD(user->getHostname());
	send(cmd.getClientSfd(), end.c_str(), end.size(), 0);
}

std::string	chatMotd()
{
	std::string	motd = "\n";
	std::ifstream file("./chatBotMotd.txt");

	if(file)
	{
		std::string line;
		while (std::getline(file, line))
		{
			motd += line;
			motd += "\n";
		}
		file.close();
		return (motd);
	}
	return (NULL);
}
