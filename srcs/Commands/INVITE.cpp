#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

// Command: INVITE
//    Parameters: <nickname> <channel>

void    invite(Command &command, Server &server)
{
    User                    *sender = server.findUser(command.getClientSfd());
    User                    *receiver = server.findUser(command.getNickname()[0]);
    Channel                 *channel;
    std::string             channelName;

    command.print_all();
    if (command.getChannels().size() == 0)
        return;
    channelName = command.getChannels()[0];
    if ((channel = server.findChannel(channelName)) == NULL)
        return;
    if (channel->findUser(command.getClientSfd(), channel->getUsersMap()) == NULL)                                                          // le sender ne peut pas inviter qq1 car il n'est pas sur le chan
        server.sendMsg(ERR_NOTONCHANNEL(sender->getLocalhost(), channel->getName()), command.getClientSfd());
    else if ((channel->findUser(command.getClientSfd(), channel->getOperatorsMap()) == NULL) && (channel->getModes() & INVITE_MODE))        // le sender n'est pas operator alors que le mode invite est acrivé
        server.sendMsg(ERR_CHANOPRIVSNEEDED(sender->getLocalhost(), sender->getNickname(), channel->getName()), command.getClientSfd());
    else if ((channel = server.findChannel(channelName)) == NULL)                                                                           // si le channel n'existe pas
        server.sendMsg(ERR_NOSUCHCHANNEL(sender->getLocalhost(), sender->getNickname(), channel->getName()), command.getClientSfd());
    else if (receiver == NULL)                                                                                                              // si le receiver n'existe pas sur le server
        server.sendMsg(ERR_NOSUCHNICK(sender->getHostname(), command.getNickname()[0], channel->getName()), command.getClientSfd());
    else if (channel->findUser(receiver->getClientFd(), channel->getUsersMap()) != NULL)                                                    // si le receiver de l'invite visé est déjà dans le channel
        server.sendMsg(ERR_USERONCHANNEL(sender->getHostname(), receiver->getNickname(), channel->getName()), command.getClientSfd());
    else
    {
        if ((channel->findUser(command.getClientSfd(), channel->getOperatorsMap()) != NULL))
        {
            server.sendMsg(RPL_INVITING(sender->getHostname(), channel->getName(), receiver->getNickname()), receiver->getClientFd());
            server.sendMsg(RPL_INVITING(sender->getHostname(), channel->getName(), receiver->getNickname()), sender->getClientFd());
        }
    }
}
