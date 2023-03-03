/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:26:58 by efinicke          #+#    #+#             */
/*   Updated: 2023/02/20 23:55:13 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/User.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Parsing.hpp"

void part(Command &command, Server &server)
{
    User                                *user = server.findUser(command.getClientSfd());
    Channel                             *channel;
    std::string                         channelName;
    std::map<int, User *>::iterator     it;
    std::vector<int>::size_type        size = command.getChannels().size();

    for (std::vector<int>::size_type i = 0; size && i < size; i++)
    {                                                                                                                                                   // traiter tous les channels précisés.
        channelName = command.getChannels()[static_cast<std::vector<int>::size_type>(i)];
        if ((channel = server.findChannel(channelName)) == NULL)                                                                                        // si le channel n'existe pas
        {
            server.sendMsg(ERR_NOSUCHCHANNEL(user->getLocalhost(), user->getNickname(), channelName), command.getClientSfd());
            return;
        }
        else if (user->findChannel(channelName) == 0)                                                                                                   // si l'utilisateur n'est pas sur le channel
            server.sendMsg(ERR_NOTONCHANNEL(user->getLocalhost(), channel->getName()), command.getClientSfd());
        else
        {
            channel->sendAllUsers(PART(user->getLocalhost(), channel->getName(), user->getNickname()));                                                 // informer tous les users du PART
            user->removeChannel(channelName);                                                                                                           // supprimer de la liste des channels de l'utilisateur
            
            channel->removeUserKick(command.getClientSfd(), channel->getUsersMap());                                                                    // supprimer l'utilisateur du channel.
            channel->removeUserKick(command.getClientSfd(), channel->getOperatorsMap());                                                                // supprimer de la liste des opérateurs.
            if ((channel->getUsersMap().size() == 0) || (channel->getUsersMap().size() == 1 && channel->findUser(4, channel->getUsersMap()) != NULL))
            {
                std::cout << "toto" << std::endl;
                server.removeIRCChannel(channelName);                                                                                                   // si la liste des users du channel est vide, supprimer le channel a partir du serveur.   
            }
        }
    }
}
