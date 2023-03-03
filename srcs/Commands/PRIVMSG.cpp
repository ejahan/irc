/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:25:44 by ejahan            #+#    #+#             */
/*   Updated: 2023/03/01 18:21:54 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

void	privmsgNorminet(Command &cmd, Server &ircServ)
{
	User *user = ircServ.findUser(cmd.getClientSfd());
	std::string	msg = "> ";
	msg += cmd.getMessage()[0];
	sendMessageNick(cmd.getClientSfd(), ircServ.findUser(cmd.getClientSfd())->getNickname(), "<", msg);

	if (user->getChat() == 0 || cmd.getMessage()[0] == "MOTD")
	{
		msg = "<norminet> \n";
		msg += chatMotd();
		msg += "\r\n";
		send(cmd.getClientSfd(), msg.c_str(), msg.size(), 0);

		user->setChat(1);
	}
	else if (cmd.getMessage()[0] == "hi" || cmd.getMessage()[0] == "hello" || cmd.getMessage()[0] == "bonjour")
	{
		msg = " !";
		sendMessageNick(cmd.getClientSfd(), ircServ.findUser(cmd.getClientSfd())->getNickname(), "<norminet> Hello ", msg);
	}
	else
	{
		int i = (rand() % (19 + 1));

		msg = "<norminet> ";
		msg += ircServ.getAnswer(i);
		msg += "\r\n";
		send(cmd.getClientSfd(), msg.c_str(),msg.size(), 0);
	}
}

void	privmsgCmd(Command &cmd, Server &ircServ)
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
		if (user->findChannel(cmd.getChannels()[0]) == 0)
		{
			std::string err = ERR_NOTONCHANNEL(user->getHostname(), cmd.getChannels()[0]);
			send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
			return ;
		}
		std::map<int, User*>	users = channel->getUsersMap();

		std::map<int, User*>::iterator	it = users.begin();
		std::map<int, User*>::iterator	ite = users.end();
		while (it != ite)
		{
			std::string	msg = PRIVMSG(user->getHostname(), cmd.getChannels()[0], cmd.getMessage()[0]);
			if (it->first != cmd.getClientSfd())
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
		else if (cmd.getNickname()[0] == "norminet")
			privmsgNorminet(cmd, ircServ);
		else
		{
			int fd = _user->getClientFd();
			std::string	msg = "> ";
			msg += cmd.getMessage()[0];
			sendMessageNick(fd, ircServ.findUser(cmd.getClientSfd())->getNickname(), "<", msg);
			sendMessageNick(cmd.getClientSfd(), ircServ.findUser(cmd.getClientSfd())->getNickname(), "<", msg);
		}
	}
}

