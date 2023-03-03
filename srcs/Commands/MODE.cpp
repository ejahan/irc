/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:26:54 by efinicke          #+#    #+#             */
/*   Updated: 2023/03/02 15:01:49 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

// CHANNEL MODES:
// Parameters: <channel> {[+|-]|i|o|p|k|s|l|t|n} [<limit>] [<user>]
            //    [<ban mask>]
// USER MODES: 
// Parameters: <nickname> {[+|-]|i|w|s|o}

enum	FlagMode
{
    DEL_FLAG    =  0, 
	ADD_FLAG    =  1,
    NO_FLAG     =  2
};

int    checkFlag(std::string mode)
{
    if (mode.c_str()[0] == '-')
        return (0);
    else if (mode.c_str()[0] == '+')
        return (1);
    else
        return (2);
}

std::string addChanOptions(Channel *channel, User *user, Server *server, Command &command)
{
    std::vector<std::string> args = command.getMessage();
    std::string mode = args[0];
    std::string add = "+";
    size_t i = 1;

    if (mode.find('i') != std::string::npos && !(channel->getModes() & !INVITE_MODE)){
        // channel->addMode(INVITE_MODE);
        add = add + "i";
    }
    if (mode.find('m') != std::string::npos && !(channel->getModes() & !MODERATE_MODE)){
        // channel->addMode(MODERATE_MODE);
        add += "m";
    }
    if (mode.find('p') != std::string::npos && !(channel->getModes() & !PRIVATE_MODE)){
        // channel->addMode(PRIVATE_MODE);
        add += "p";
    }
    if (mode.find('k') != std::string::npos)
    {
        if (args.size() < (i + 1))
            server->sendMsg(ERR_NEEDMOREPARAMS(user->getLocalhost(), user->getNickname() + " MODE + k"), user->getUserSfdN());
        else if (channel->getModes() & KEY_MODE)
            server->sendMsg(ERR_KEYSET(user->getLocalhost(), channel->getName()), user->getUserSfdN());
        else
        {
            // channel->addMode(KEY_MODE);
            // channel->setPassword(args[i]);
            add += "k";
            i++;
        }
    }
    if (mode.find('s') != std::string::npos && !(channel->getModes() & !SECRET_MODE)){
        // channel->addMode(SECRET_MODE);
        add += "s";
    }
    if (mode.find("l") != std::string::npos && !(channel->getModes() & !LIMITED_MODE))
    {
        if (args.size() < (i + 1))
            server->sendMsg(ERR_NEEDMOREPARAMS(user->getLocalhost(), user->getNickname() + " MODE + l"), user->getUserSfdN());
        else
        {
           //channel->setMaxUsers(atol(args[i].c_str()));
           channel->setMaxUsers(static_cast<int>(atol(args[i].c_str())));
           if (channel->getMaxUsers() != 0)
           {
            //    channel->addMode(LIMITED_MODE);
               add += "l";
               i++;
           }
        }
    }
    if (mode.find('t') != std::string::npos && !(channel->getModes() & !TOPIC_MODE)){
        // channel->addMode(TOPIC_MODE);
        add += "t";
    }
    return (add);
}

std::string     delChanOptions(Channel *channel, Command *command)
{
    std::vector<std::string> args = command->getMessage();
    std::string mode = args[0];
    std::string del = "-";

    if (mode.find('i') != std::string::npos && (channel->getModes() & INVITE_MODE)){
        // channel->removeMode(INVITE_MODE);
        del += "i";
    }
    if (mode.find('m') != std::string::npos && (channel->getModes() & MODERATE_MODE)){
        // channel->removeMode(MODERATE_MODE);
        del += "m";
    }
    if (mode.find('p') != std::string::npos && (channel->getModes() & PRIVATE_MODE)){
        // channel->removeMode(PRIVATE_MODE);
        del += "p";
    }
    if (mode.find('k') != std::string::npos && (channel->getModes() & KEY_MODE)){
        // channel->removeMode(KEY_MODE);
        del += "k";
    }
    if (mode.find('s') != std::string::npos && (channel->getModes() & SECRET_MODE)){
        // channel->removeMode(SECRET_MODE);
        del += "s";
    }
    if (mode.find('l') != std::string::npos && (channel->getModes() & LIMITED_MODE)){
        // channel->removeMode(LIMITED_MODE);
        del += "l";
    }
    if (mode.find('t') != std::string::npos && (channel->getModes() & TOPIC_MODE)){
        // channel->removeMode(TOPIC_MODE);
        del += "t";
    }
    return (del);
}

void    mode(Command &command, Server &server)
{
    User                            *sender = server.findUser(command.getClientSfd());
    Channel                         *channel;
    std::string                     channelName;
    int                             flag;
    std::vector<int>::size_type     size = command.getChannels().size();
    std::vector<int>::size_type     userMode = command.getNickname().size();
    std::vector<int>::size_type     modes = command.getMessage().size();
    std::string                 rights = "+";

    std::cout << "MODE: " << std::endl;
    command.print_all();
    if (sender)
    {
        if ((!size && !userMode) || !modes)                                                                                                             // si pas de chan et pas de user précisé, ou pas de modes précisés
            server.sendMsg(ERR_NEEDMOREPARAMS(sender->getHostname(), sender->getUserSfd()), command.getClientSfd());                                    // alors il manque des arguments
        else if ((flag = checkFlag(command.getMessage()[0])) == NO_FLAG)                                                                                // si pas de flag de mode précisé dans les options
            server.sendMsg(ERR_UMODEUNKNOWNFLAG(sender->getLocalhost()), command.getClientSfd());                                                       // erreur pas de flag de mode reconnu
        else if (size > 0)                                                                                                                              // si c'est un mode channel
        {
            channelName = command.getChannels()[0];
            if ((channel = server.findChannel(channelName)) == NULL)                                                                                    // si le channel n'existe pas
                server.sendMsg(ERR_NOSUCHCHANNEL(sender->getLocalhost(), sender->getNickname(), channelName), command.getClientSfd());                  // erreur no such channel
            else if (channel->findUser(command.getClientSfd(), channel->getUsersMap()) == NULL)                                                         // si le channel existe et que l'utilisateur ne s'y trouve pas
                server.sendMsg(ERR_NOTONCHANNEL(sender->getLocalhost(), channel->getName()), command.getClientSfd());                                   // erreur user pas sur le channel
            else if (channel && channel->findUser(command.getClientSfd(), channel->getOperatorsMap()) == NULL)                                          // si le channel existe et que l'user n'est pas operator
                server.sendMsg(ERR_CHANOPRIVSNEEDED(sender->getLocalhost(), sender->getNickname(), channel->getName()), command.getClientSfd());        // erreur l'user n'est pas opérateur
            if (size && !userMode)
            {
                if (flag == ADD_FLAG)
                    rights = addChanOptions(channel, sender, &server, command);
                else if (flag == DEL_FLAG)
                    rights = delChanOptions(channel, &command);
                if (rights != "")
                    server.sendMsg(MODE(sender->getLocalhost(), channel->getName(), rights), command.getClientSfd());
            }
        }
    }
} 
