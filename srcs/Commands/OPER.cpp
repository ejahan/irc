/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:25:19 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 23:03:00 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

void	operCmd(Command &cmd, Server &ircServ)
{
	std::string err;
	User	*user = ircServ.findUser(cmd.getClientSfd());

	if (cmd.getNickname()[0] != "oper_id")
	{
		err = ERR_NOOPERHOST(user->getHostname());
		send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
	}
	else if (cmd.getMessage()[0] != "oper_pw")
	{
		err = ERR_PASSWDMISMATCH(user->getHostname(), user->getNickname());
		send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
	}
	else
	{
		user->setUserModes(4);

		err = RPL_YOUREOPER(user->getHostname());
		send(cmd.getClientSfd(), err.c_str(), err.size(), 0);
	}
}
