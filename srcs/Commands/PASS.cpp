/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:54:15 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 23:55:42 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

void	passCmd(Command &cmd, Server &ircServ)
{
	std::vector<std::string>	pw = cmd.getMessage();
	User						*user = ircServ.findUser(cmd.getClientSfd());

	if (user->getPass() == 1)
	{
		std::string err = ERR_ALREADYREGISTRED(user->getHostname());
		send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
	}
	else if (pw[0] == ircServ.getPassword())
		user->setPass(1);
	else
	{
		user->setPass(2);
		std::string error = ERR_PASSWDMISMATCH(user->getHostname(), user->getNickname());
		send(cmd.getClientSfd(), error.c_str(), error.size(), 0);
	}
}
