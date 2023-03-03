/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:24:30 by ejahan            #+#    #+#             */
/*   Updated: 2023/03/02 15:00:18 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

// Command: KILL
//    Parameters: <nickname> <comment>

void	killCmd(Command &cmd, Server &ircServ)
{
	User	*user_to_kill = ircServ.findUser(cmd.getNickname()[0]);
	User	*killer = ircServ.findUser(cmd.getClientSfd());

	if (killer->getUserModes() != 4)
	{
		std::string	err = ERR_NOPRIVILEGES(killer->getHostname(), killer->getNickname());
		send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
	}
	else if (user_to_kill == NULL)
	{
		std::string	err = ERR_NOSUCHNICK(killer->getHostname(), killer->getNickname(), cmd.getNickname()[0]);
		send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
	}
	else
	{
		std::vector<Channel> channels = ircServ.getIRCChannels();
		std::vector<Channel>::iterator	it = channels.begin();
		std::vector<Channel>::iterator	ite = channels.end();

		std::string msg = "";
		if (cmd.get_size_message() > 0)
			msg = cmd.getMessage()[0];
		std::string message = QUIT(user_to_kill->getHostname(), KILL(killer->getNickname(), msg));
		while (it != ite)
		{
			if (it->findUser(user_to_kill->getClientFd(), it->getUsersMap()) != NULL)
				sendMsgChannel(it->getUsersMap(), message);
			it++;
		}

		std::string err = ERROR_MSG(killer->getNickname(), msg);
		send(user_to_kill->getClientFd(), err.c_str(), err.size(), 0);
		it = channels.begin();
		while (it != ite)
		{
			it->getVoiceMap().erase(user_to_kill->getClientFd());
			it->getUsersMap().erase(user_to_kill->getClientFd());
			it->getOperatorsMap().erase(user_to_kill->getClientFd());
			it++;
		}

		User	*user = ircServ.findUser(user_to_kill->getClientFd());
		user->setConnected(0);
		user->setPass(0);
	}
}
