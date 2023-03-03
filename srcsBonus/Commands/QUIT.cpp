/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:01:03 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 23:56:51 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

void	quitCmd(Command &cmd, Server &ircServ)
{
	std::vector<Channel>				channels = ircServ.getIRCChannels();
	std::vector<Channel>::iterator		it = channels.begin();
	std::vector<Channel>::iterator		ite = channels.end();
	User								*user = ircServ.findUser(cmd.getClientSfd());
	std::string							msg = "";

	if (cmd.get_size_message() != 0)
		msg = cmd.getMessage()[0];

	std::string							message = QUIT(user->getHostname(), msg);

	while (it != ite)
	{
		if (it->findUser(cmd.getClientSfd(), it->getUsersMap()) != NULL)
			sendMsgChannelQuit(it->getUsersMap(), message, it->getName(), user->getHostname());
		it++;
	}
}

void	quitCmdNc(int client_fd, Server &ircServ)
{
	std::vector<Channel>				channels = ircServ.getIRCChannels();
	std::vector<Channel>::iterator		it = channels.begin();
	std::vector<Channel>::iterator		ite = channels.end();
	User								*user = ircServ.findUser(client_fd);

	if (user!=NULL)
	{
		it = channels.begin();
		while (it != ite)
		{
			it->getVoiceMap().erase(client_fd);
			it->getUsersMap().erase(client_fd);
			it->getOperatorsMap().erase(client_fd);
			it++;
		}
		user->setConnected(0);
		user->setPass(0);
	}
}
