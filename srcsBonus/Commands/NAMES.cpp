#include "../../includes/Include.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Parsing.hpp"

void    names(Command &command, Server &server)
{
    User                            *user = server.findUser(command.getClientSfd());
    Channel                         *channel;
    std::string                     channelName;
    std::map<int, User*>	        users;
    std::vector<int>::size_type     size = command.getChannels().size();
    

    printVector(command.getChannels());
    if (size > 0)
    {
        for (std::vector<int>::size_type i = 0; i < command.getChannels().size(); i++)                                                                      // tant que des channels existent, lister tous les noms de chaque channel donné en argument
        {
            std::string channelName = command.getChannels()[i];
            if ((channel = server.findChannel(channelName)) != NULL){                                                                                       // si le channel existe 
                std::map<int, User*>	users = channel->getUsersMap();
                if (!(channel->getModes() & PRIVATE_MODE) && !(channel->getModes() & SECRET_MODE)){                                                         // et que ni le mode secret ni le mode privé n'est établi pour ce channel
                    users = channel->getUsersMap(); 
                    for (std::map<int, User*>::iterator	it = users.begin(); it != users.end(); it++)                                                        // parcourir la liste des users
                    { 
                        if (!(it->second->getUserModes() & INVISIBLE_MODE))                                                                                 // si l'user n'est pas en mode invisible
                            server.sendMsg(RPL_NAMREPLY(user->getLocalhost(), channel->getName(), it->second->getNickname()), command.getClientSfd());      // afficher son nom
                    }
                    server.sendMsg((RPL_ENDOFNAMES(user->getLocalhost(), user->getNickname(), channel->getName())), command.getClientSfd());                // une fois les noms du channel affiché, envoyer le message ENDOFNAME.
                }
            }
        }
    }
    else if (size == 0)                                                                                                                                     // si pas de channel précisés lister les users de tous les channels existants sur IRC server
    {
        std::vector<Channel>            channels = server.getIRCChannels();
        std::vector<Channel>::iterator  itChan;

        for (itChan = channels.begin(); itChan != channels.end(); itChan++)                                                                                 // itérer sur tous les channels existants de IRCServer
        {
            channel = &(*itChan);                                                                                                                           // definir le channel pris en compte a chaque iteration
            users = channel->getUsersMap();
            if (!(channel->getModes() & PRIVATE_MODE) && !(channel->getModes() & SECRET_MODE))                                                              // si le channel n'est ni privé ni secret
            {
                for (std::map<int, User*>::iterator	it = users.begin(); it != users.end(); it++)                                                            // parcourir la liste user de ce channel
                {
                    if (!(it->second->getUserModes() & INVISIBLE_MODE))                                                                                     // si l'user n'est pas en mode invisible
                        server.sendMsg(RPL_NAMREPLY(user->getLocalhost(), channel->getName(), it->second->getNickname()), command.getClientSfd());          // afficher son nom et le channel correspondant
                }
            }
            else if ((channel->getModes() & PRIVATE_MODE) || (channel->getModes() & SECRET_MODE))                                                           // si le channel est en mode privé ou secret
            { 
                for (std::map<int, User*>::iterator	it = users.begin(); it != users.end(); it++)                                                            // parcourir la liste des users
                {
                    if (!(it->second->getUserModes() & INVISIBLE_MODE))                                                                                     // si l'user n'est pas en mode invisible
                        server.sendMsg(RPL_NAMREPLY(user->getLocalhost(), "*", it->second->getNickname()), command.getClientSfd());                         // afficher son nom mais sans le nom du channel avant la EMDOFLIST
                }
            }
            server.sendMsg((RPL_ENDOFNAMES(user->getLocalhost(), user->getNickname(), channel->getName())), command.getClientSfd());                        // une fois les noms affichés, envoyer le message ENDOFNAME.
        }
    }
}
