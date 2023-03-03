/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:59:32 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 23:22:32 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

// Command: KICK
//    Parameters: <channel> <user> [<comment>]

void	kickCmd(Command &cmd, Server &ircServ)
{
	int	fd = cmd.getClientSfd();
	Channel	*channel = ircServ.findChannel(cmd.getChannels()[0]);
	User	*user = ircServ.findUser(cmd.getClientSfd());

	if (channel != NULL)
	{
		if (channel->findUser(fd, channel->getUsersMap()) != NULL)
		{
			if (channel->findUser(fd, channel->getOperatorsMap()) != NULL)
			{
				User *_user = ircServ.findUser(cmd.getNickname()[0]);
				if (_user != NULL)
				{
					if (_user != NULL && channel->findUser(_user->getUserSfdN(), channel->getUsersMap()) != NULL)
					{
						std::string msg = "";
						if (cmd.get_size_message() != 0)
							msg = cmd.getMessage()[0];
						std::string str = KICK(ircServ.findUser(cmd.getClientSfd())->getHostname(), channel->getName(), cmd.getNickname()[0]);
						str += " :";
						str += msg;
						str += "\r\n";
						sendMsgChannel(channel->getUsersMap(), str);
						channel->removeUserKick(_user->getUserSfdN(), channel->getUsersMap());
						channel->removeUserKick(_user->getUserSfdN(), channel->getOperatorsMap());
						channel->removeUserKick(_user->getUserSfdN(), channel->getVoiceMap());
						channel->removeUserKick(_user->getUserSfdN(), channel->getBanMap());
						channel->removeUserKick(_user->getUserSfdN(), channel->getInviteMap());
						_user->removeChannel(channel->getName());
					}
				}
				else
				{
					std::string	err = ERR_USERNOTINCHANNEL(user->getHostname(), cmd.getChannels()[0], cmd.getNickname()[0]);//, user->getNickname());
					send(fd, err.c_str(), err.size(), 0);
				}
			}
			else
			{
				std::string err = ERR_CHANOPRIVSNEEDED(user->getHostname(), user->getNickname(), cmd.getChannels()[0]);
				send(fd, err.c_str(), err.size(), 0);
			}
		}
		else
		{
			std::string	err = ERR_NOTONCHANNEL(user->getHostname(), cmd.getChannels()[0]);
			send(fd, err.c_str(), err.size(), 0);
		}
	}
	else
	{
		std::string err = ERR_NOSUCHCHANNEL(user->getHostname(), user->getNickname(), cmd.getChannels()[0]);
		send(fd, err.c_str(), err.size(), 0);
	}
}

