/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:08:38 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 23:55:51 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

void	pingCmd(Command &cmd, Server &ircServ)
{
	(void)ircServ;

	sendMessageNick(cmd.getClientSfd(), cmd.getNickname()[0], "PONG :", "");
}
