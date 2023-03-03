/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:27:02 by efinicke          #+#    #+#             */
/*   Updated: 2023/02/20 23:54:06 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

int  isValidNickname(std::string nickname){
    int i = -1;
    char c = nickname.c_str()[0];
    char str[] = {',','\r','\n','\a','\0','#','&'};
    
    while(str[++i]){
        if (nickname.find(str[i])!= std::string::npos)
            return (0);
    }
    if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
        return (0);
    if (nickname.length() > 9)
        return (0);
    return (1);
}

void nick(Command &command, Server &server)
{
    User *user = server.findUser(command.getClientSfd());
    std::vector<std::string> channels = user->getChannels();

    if (command.getNickname().size() == 0)
        server.sendMsg(ERR_NONICKNAMEGIVEN(user->getLocalhost()), command.getClientSfd());
    else if (command.getNickname().size() > 0)
    {
        if (server.findUser(command.getNickname()[0]) != NULL)
            server.sendMsg(ERR_NICKNAMEINUSE(user->getLocalhost(), command.getNickname()[0]), command.getClientSfd());
        else if (!isValidNickname(command.getNickname()[0]))
            server.sendMsg(ERR_ERRONEUSNICKNAME(user->getLocalhost(), user->getNickname()), command.getClientSfd()); //fonctionne
        else
        {            
	        server.findUser(command.getClientSfd())->setNick(1);
            if (user->getChannels().size() == 0)
                server.sendMsg(NICK(user->getHostname(), command.getNickname()[0]), command.getClientSfd());
            else
                server.sendMsgInAllChannelsOfAnUser(user, NICK(user->getHostname(), command.getNickname()[0]));
            user->setNickname(command.getNickname()[0]);
        }
    }
}
