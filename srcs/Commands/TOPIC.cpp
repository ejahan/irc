#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

void    topic(Command &command, Server &server)
{
    User                            *user = server.findUser(command.getClientSfd());
    Channel                         *channel;
    std::string                     channelName;
    std::vector<int>::size_type     size = command.getChannels().size();

    if (size == 0)                                                                                                                              //si pas de channel précisé
        server.sendMsg(ERR_NEEDMOREPARAMS(user->getHostname(), user->getUserSfd()), command.getClientSfd());
    else
    {
        channelName = command.getChannels()[0];
        if ((channel = server.findChannel(channelName)) == NULL){                                                                               // si le channel n'existe pas
            server.sendMsg(ERR_NOSUCHCHANNEL(user->getHostname(), user->getNickname(), channelName), command.getClientSfd());
        }
        else if (command.getMessage().size() == 0){                                                                                             // si pas de mess de topic, demande d'affichage du topic
            std::cout << "TOPIC: " << channel->getTopic() << std::endl;
            if (channel->getTopic() != "")                                                                                                      // renvoyer le topic
                server.sendMsg(RPL_TOPIC(user->getHostname(), channel->getName(), channel->getTopic()), command.getClientSfd());
            if (channel->getTopic() == "")                                                                                                      // renvoyer msg précisant qu'il n'y a pas de topic assigné
                server.sendMsg(RPL_NOTOPIC(user->getHostname(), channel->getName()), command.getClientSfd());
        }
        else                                                                                                                                    // si argument de topic
        {                                                                                                                                       // si mode topic et user est pas operateur :
            if ((channel->getModes() & TOPIC_MODE) || (channel->findUser(command.getClientSfd(), channel->getOperatorsMap()) == NULL))          // si le mode topic +t est activé
                server.sendMsg(ERR_CHANOPRIVSNEEDED(user->getHostname(), user->getNickname(), channel->getName()), command.getClientSfd());
            else                                                                                                                                // si pas de mode topic ou que mode topic et l'user est operateur:
            {
                channel->setTopic(command.getMessage()[0]);                                                                                     // rajouter le topic
                channel->sendAllUsers(TOPIC(user->getHostname(), channel->getName(), channel->getTopic()));                                     // renvoyer le topic
            }
        }
    }
}
