/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:25:02 by ejahan            #+#    #+#             */
/*   Updated: 2023/03/02 15:01:17 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

std::string	check_str(std::vector<std::string> vect)
{
	std::vector<std::string>::iterator	it = vect.begin() + 1;

	if (it->find('#') == 0)
		return (vect[1]);
	return ("");
}

void	listCmd(Command &cmd, Server &ircServ)
{
	std::vector<Channel>	channels;
	std::string				msg;
	User					*user = ircServ.findUser(cmd.getClientSfd());
	std::string				start = RPL_LISTSTART(user->getHostname());
	std::string				end = RPL_LISTEND(user->getHostname());

	send(cmd.getClientSfd(), start.c_str(), start.size(), 0);
	if (cmd.get_size_channels() == 0)
	{
		channels = ircServ.getIRCChannels();
		std::vector<Channel>::iterator	it = channels.begin();
		std::vector<Channel>::iterator	ite = channels.end();

		while (it != ite)
		{
			if (it->getModes() != 16)
			{
				std::ostringstream oss;
				oss << static_cast<int>(it->getUsersMap().size());
				msg = RPL_LIST(user->getHostname(), it->getName(), oss.str(), it->getTopic());
				sendMessage(cmd.getClientSfd(), msg);
			}
			it++;
		}
	}
	else
	{
		std::vector<std::string>			channel = cmd.getChannels();
		std::vector<std::string>::iterator	it = channel.begin();
		std::vector<std::string>::iterator	ite = channel.end();
		
		while (it != ite)
		{
			if (ircServ.findChannel(*it) != NULL)
			{
				if (ircServ.findChannel(*it)->getModes() != 16)
				{
					std::stringstream iss;
					iss << ircServ.findChannel(*it)->getUsersMap().size();
					int size = 0;
					iss >> size;
					msg = RPL_LIST(user->getHostname(), *it, itoa(size), ircServ.findChannel(*it)->getTopic());
					sendMessage(cmd.getClientSfd(), msg);
				}
			}
			else
			{
				std::string	err = ERR_NOSUCHNICK(user->getHostname(), user->getNickname(), cmd.getChannels()[0]);
				send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
			}
			it++;
		}
	}

	send(cmd.getClientSfd(), end.c_str(), end.size(), 0);
}
