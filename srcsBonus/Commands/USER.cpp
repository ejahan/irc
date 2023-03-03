/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 02:07:37 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 23:57:08 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

void	userCmd(std::string hostname, std::string nickname, Command &cmd, Server &ircServ)
{
	if (ircServ.findUser(cmd.getClientSfd())->getConnected() == 0)
	{
		User *user;
		std::vector<std::string>	vect = cmd.getNickname();
		std::string					username = vect.front();
		vect = cmd.getServer();
		std::string					servername = vect.front();
		vect = cmd.getMessage();
		std::string					realname = vect.front();

		ircServ.add_user(nickname, username, hostname, servername, realname, cmd.getClientSfd());
		user = ircServ.findUser(cmd.getClientSfd());
		user->setConnected(1);
		user->setClientFd(cmd.getClientSfd());

		ircServ.sendMsg(RPL_WELCOME(user->getLocalhost(), user->getNickname()), cmd.getClientSfd());
		ircServ.sendMsg(RPL_YOURHOST(user->getLocalhost()), cmd.getClientSfd());
		ircServ.sendMsg(RPL_CREATED(user->getLocalhost()), cmd.getClientSfd());
		ircServ.sendMsg(RPL_MYINFO(user->getLocalhost()), cmd.getClientSfd());

		motdCmd(cmd, ircServ);
	}
	else
	{
		std::string error = ERR_ALREADYREGISTRED(ircServ.findUser(cmd.getClientSfd())->getHostname());
		send(cmd.getClientSfd(), error.c_str(), error.size(), 0);
	}
}
