/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:24:09 by ejahan            #+#    #+#             */
/*   Updated: 2023/03/02 15:42:27 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

// #define NOTICE(localhost, chan, str) (":" + localhost + " NOTICE " + chan + " :" + str + "\r\n")

void    noticeCmd(Command &cmd, Server &ircServ)
{
	User	*user = ircServ.findUser(cmd.getClientSfd());

	if (cmd.get_size_channels() >= 1)
	{
		Channel	*channel = ircServ.findChannel(cmd.getChannels()[0]);
		if (channel == NULL)
		{
			std::string	err = ERR_NOSUCHCHANNEL(user->getHostname(), user->getNickname(), cmd.getChannels()[0]);
			send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
		}
		std::map<int, User*>	users = channel->getUsersMap();

		std::map<int, User*>::iterator	it = users.begin();
		std::map<int, User*>::iterator	ite = users.end();
		while (it != ite)
		{
			std::string	msg = NOTICE(user->getHostname(), cmd.getChannels()[0], cmd.getMessage()[0]);
			sendMessage(it->first, msg);
			it++;
		}
	}
	else
	{
		User	*_user = ircServ.findUser(cmd.getNickname()[0]);
		if (_user == NULL)
		{
			std::string	err = ERR_NOSUCHNICK(user->getHostname(), user->getNickname(), cmd.getNickname()[0]);
			send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
		}
		else
		{
			int fd = _user->getClientFd();
			std::string msg;
			if (cmd.get_size_channels() > 0)
				msg = NOTICE(user->getHostname(), cmd.getChannels()[0], cmd.getMessage()[0]);
			else
				msg = NOTICE(user->getHostname(), cmd.getNickname()[0], cmd.getMessage()[0]);
			send(cmd.getClientSfd(), msg.c_str(), msg.size(), 0);
			send(fd, msg.c_str(), msg.size(), 0);
		}
	}
}
