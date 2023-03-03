/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:26:49 by efinicke          #+#    #+#             */
/*   Updated: 2023/02/20 23:22:24 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

// Command: JOIN
//    Parameters: <channel>{,<channel>} [<key>{,<key>}]

void    join(Command *command, Server *server)
{
    User                            *user = server->findUser(command->getClientSfd());
    Channel                         *channel;
    std::vector<int>::size_type     size = command->getChannels().size();
    std::string                     channelName;
    std::map<int, User*>	        users;
    
    if (size == 0){                                                                                                                                     // si pas assez d'arguments
        server->sendMsg(ERR_NEEDMOREPARAMS(user->getHostname(), user->getUserSfd()), command->getClientSfd());
    }
    else if (size > 0) //
    {
        for (std::vector<int>::size_type i = 0; i < command->getChannels().size(); i++)
        {
            channelName = command->getChannels()[static_cast<unsigned int>(i)];
            if ((channel = server->findChannel(channelName)) != NULL)
            {                               
                users = channel->getUsersMap(); 
                if ((channel->getModes() & LIMITED_MODE)                                                                                                // si mode l (nbre de users limités)
                    && ((channel->getUsersMap().size()) == channel->getMaxUsers())                                                                      // et que le maximum d'utilisateurs est atteind
                    && (channel->findUser(command->getClientSfd(), channel->getInviteMap()) == NULL))                                                   // et que l'user n'est pas invité
                    server->sendMsg(ERR_CHANNELISFULL(user->getHostname(), channel->getName()), command->getClientSfd());                               // error
                else if (user->getChannels().size() == 10)                                                                                              // si le user est déjà sur le nbre max de chan autorisés
                    server->sendMsg(ERR_TOOMANYCHANNELS(user->getHostname(), channel->getName()), command->getClientSfd());                             //error toomany chan
                else if (channel->findUser(command->getClientSfd(), channel->getBanMap()) != NULL)                                                      // s'il est banni
                    server->sendMsg(ERR_BANNEDFROMCHAN(user->getHostname(), channel->getName()), command->getClientSfd());
                else if ((channel->findUser(command->getClientSfd(), channel->getInviteMap()) == NULL)                                                  // s'il est pas invité
                    && (channel->getModes() & INVITE_MODE))                                                                                             // et que le mode invité est activé
                    server->sendMsg(ERR_INVITEONLYCHAN(user->getHostname(), channel->getName()), command->getClientSfd());                              //error
                else if ((channel->getModes() & KEY_MODE)                                                                                               // si un password est requis
                        && ((command->getMessage().size() == 0)                                                                                         // et que l'user n'a pas rentré de password
                        || (command->getMessage()[static_cast<unsigned int>(i)] != channel->getPassword())))                                            // ou à rentré un password érroné        
                        server->sendMsg(ERR_BADCHANNELKEY(user->getHostname(), channel->getName()), command->getClientSfd());                           //error
                else
                {
                    channel->addUser(command->getClientSfd(), user);                                                                                    // ajouter l'user sur la liste des utilisateurs du channel
                    user->addChannel(channelName);                                                                                                      // ajouter le channel a la liste de l'utilisateur
                    channel->sendAllUsers(JOIN(user->getHostname(), channelName));                                                                      // informer tous les users du join
                    for (std::map<int, User*>::iterator	it = users.begin(); it != users.end(); it++)
                            server->sendMsg(RPL_NAMREPLY(user->getHostname(), channel->getName(), it->second->getNickname()), command->getClientSfd()); // envoyer la liste de tous les noms des users
                    server->sendMsg(RPL_ENDOFNAMES(user->getHostname(), user->getNickname(), channel->getName()), command->getClientSfd());             //endofnames signal
                }
            }
            else                                                                                                                                        //si le chan n'existe pas
            {
                printVector(user->getChannels());
                if (command->getMessage().size() == 0)                                                                                                  // si pas de password entré
                {
                    server->addIRCChannel(channelName);                                                                                                 // créer un channel sans mot de passe
                    channel = server->findChannel(channelName);                                                                                         // l'attribuer au channel
                }
                else                                                                                                                                    // si mot de passe
                {
                    server->addIRCChannel(channelName, command->getMessage()[static_cast<unsigned int>(i)]);                                            // créer un channel avec un mot de passe
                    server->removeIRCChannel(channelName);
                    channel = server->findChannel(channelName);                                                                                         // l'attribuer au channel
                    if (channel != NULL)
                    {
                        channel->addMode(KEY_MODE);
                        channel->setPassword(command->getMessage()[static_cast<unsigned int>(i)]);
                    }
                }
                if (channel == NULL)
                {
                    server->sendMsg(ERR_UNAVAILRESOURCE(user->getHostname(), channelName), command->getClientSfd());              
                    return ;
                }
                users = channel->getUsersMap();
                
                channel->addUser(command->getClientSfd(), user);                                                                                        // ajouter l'user sur la liste des utilisateurs du channel
                channel->addOperator(command->getClientSfd(), user);                                                                                    // ajouter l'user sur la liste des opérateurs du channel, car il est le createur
                user->addChannel(channel->getName());                                                                                                   // ajouter le channel a la liste de l'utilisateur
                channel->sendAllUsers(JOIN(user->getHostname(), channel->getName()));                                                                    // informer tous les users du join


                std::string str = "@";
                str += user->getNickname();
                users = channel->getUsersMap();
                std::map<int, User*>::iterator	it = users.begin();
                std::map<int, User*>::iterator	ite = users.end();
        
                for (; it != ite; it++)                                                                                                                 // afficher la liste de tous les users du channel
                {
                    server->sendMsg(RPL_NAMREPLY(user->getHostname(), channel->getName(), str), command->getClientSfd());
                }
                server->sendMsg(RPL_ENDOFNAMES(user->getHostname(), user->getNickname(), channel->getName()), command->getClientSfd());                 //endofnames signal
            }
        }
    }
}

