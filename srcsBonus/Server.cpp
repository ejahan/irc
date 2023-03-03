/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 02:15:43 by grannou           #+#    #+#             */
/*   Updated: 2023/03/02 15:03:21 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Parsing.hpp"

// Default Constructor
Server::Server(void):_port("6667"), _password(""), _fd(-1), _time(std::time(NULL))
{
    std::cout << GREEN "Default Constructor " RESET "of Class " GREEN "Server " RESET "called" << std::endl;
}

// Constructor with parameters
Server::Server(std::string port, std::string password): _port(port), _password(password), _fd(-1), _time(std::time(NULL))
{

    std::cout << GREEN "Constructor " RESET "of Class " GREEN "Server " RESET "called" << std::endl;  

    // Bonus part
    _chatBotName = "norminet";

    _answers[0] = "According to the bocal it is certain";
    _answers[1] = "The legend says yes when the intra v3 is here";
    _answers[2] = "42";
    _answers[3] = "Without a (no)doubt says Gwen Stefani";
    _answers[4] = "Yes definitely";
    _answers[5] = "You may rely on it";
    _answers[6] = "We're all mad here... but yes";
    _answers[7] = "Most likely";
    _answers[8] = "My whiskers say yes";
    _answers[9] = "Yes, oui, da, hai, si";
    _answers[10] = "Puuurfectly yes";
    _answers[11] = "Puuur-haps, that's a paw-sibility";
    _answers[12] = "Are you serious? Ask again later";
    _answers[13] = "Better not tell you meow";
    _answers[14] = "Cannot predict meow";
    _answers[15] = "Read The Feline Manual!";
    _answers[16] = "Don't malloc on it";
    _answers[17] = "Are you kitten me? Don't ask that again!";
    _answers[18] = "Norminette says no";
    _answers[19] = "Fur real? absolutely not";
}

// Copy Constructor
Server::Server(Server const &rhs)
{
	*this = rhs;
	return ;
}

// Copy Constructor
Server &Server::operator=(Server const &rhs)
{
    std::cout << YELLOW "Copy Assignment Operator called" RESET << std::endl;
    
    if (this != &rhs)
    {
        this->_port = rhs.getPort();
        this->_password = rhs.getPassword();
        this->_fd = rhs.getFd();
        this->_time = rhs.getTime();
        this->_channels = rhs._channels;
        this->_users = rhs._users;
    }
    return (*this);
}

// Destructor
Server::~Server()
{
    std::cout << RED "Destructor " RESET "of Class " RED "Server " RESET "on port " << RED << _port << RESET << " is destroyed" << std::endl;
    close(_fd);
}

// Accessor/Getter Member Functions
std::string Server::getPort(void) const
{
    return (this->_port);
}

std::string Server::getPassword(void) const
{
    return (this->_password);
}

int Server::getFd(void) const
{
    return (this->_fd);
}

std::time_t Server::getTime(void) const
{
    return (this->_time);
}

std::vector<Channel> Server::getIRCChannels() const
{
    return (this->_channels);
}

std::map<int, User>  Server::getIRCUsers() const
{
    return (this->_users);
}

std::string Server::getAnswer(int i)
{
    return (_answers[i]);
}

// Setter Member Functions
void    Server::setPort(std::string port)
{
    this->_port = port;
}

void    Server::setPassword(std::string password)
{
    this->_password = password;
}

void    Server::setFd(int fd)
{
    this->_fd = fd;
}

void    Server::setTime(std::time_t time)
{
    this->_time = time;
}

// Set up Server
int     Server::setup()
{
    int     optionValue = 1;
    int     serverPort = atoi(getPort().c_str());
    
    // Create a socket
    if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (printErrorMessage(CREATE_SOCKET_ERROR), 1);
    std::cout << GREEN << "Creating Server socket succeed" << RESET << std::endl;
    std::cout << CYAN << "Server Socket fd = " << RESET << _fd << std::endl;

    // Set socket options    
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optionValue, sizeof(optionValue)) < 0)
        return (printErrorMessage(SET_SOCKET_OPTION_ERROR), 1);

    // Set the socket to non-blocking
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
		return (printErrorMessage(NON_BLOCKING_SOCKET_ERROR), 1);
    std::cout << GREEN << "Setting non blocking socket succeed" << RESET << std::endl;
    
    // Binding socket to an IP address and port
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(serverPort);

    if (bind(_fd, (struct sockaddr*)&_address, sizeof(_address)) < 0)
        return (printErrorMessage(BIND_SOCKET_ERROR NON_AVAILABLE_PORT_ERROR), 1);
    std::cout << GREEN << "Binding socket succeed" << RESET << std::endl;

    // Listen for incoming connections
    if (listen(_fd, SOCKET_MAX_CONNECTIONS) < 0) 
    return (printErrorMessage(LISTEN_SOCKET_ERROR), 1);

    return (0);
}

// Launch and run Server
int    Server::run()
{
    // Create a event descriptor epoll
    int epoll_fd = epoll_create1(0);
    if (epoll_fd < 0)
        return (printErrorMessage(KYU BIE CREATE_EPOLL_FD_ERROR BIE KYU), 1);

    // Add the server socket to the event descriptor epoll
    struct epoll_event event;
    ft_memset(&event, 0, sizeof(event));
    
    event.data.fd = _fd;
    event.events = EPOLLIN | EPOLLET;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, _fd, &event) < 0)
        return (printErrorMessage(ADDING_SERVER_FD_EPOLL_ERROR), 1);

    // Events loop
    while (true)
    {
        struct epoll_event  events[MAX_EVENTS];
        
        int eventsNumber = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (eventsNumber == -1)
        {
            if (errno != EINTR)                                                 // EINTR -> interruption by a signal
                printErrorMessage(WAITING_EPOLL_ERROR);
            break;
        }
        
        for (int i = 0; i < eventsNumber; i++)
        {
            // Error handling
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
            {
                printErrorMessage(EPOLL_FD_ERROR);
                close(events[i].data.fd);
                continue;
            }
            // New incoming connection
            else if (events[i].data.fd == _fd)
            {

                struct sockaddr_in      clientAddress;
                socklen_t               clientAddressSize = sizeof(clientAddress);

                // POUR MULTICLIENT, APRES accept, new le client (qui a son buffer), mettre le message dedans et le parser
                int clientFd = accept(_fd, (struct sockaddr *)&clientAddress, &clientAddressSize);
                if (clientFd == -1)
                {
                    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))            // EAGAIN -> temporary lack of ressources EWOULDBLOCK -> caller shouldtry later
                        printErrorMessage(ACCEPTING_CONNECTION_ERROR);
                    break;
                }
                
                // Add the new client to the epoll event file descriptor
                event.data.fd = clientFd;
                event.events = EPOLLIN;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientFd, &event) == -1)
                {
                    printErrorMessage(ADDING_CLIENT_FD_EPOLL_ERROR);
                    continue;
                }
            }
            // Data from a client    
            else 
            {
                int                     clientFd = events[i].data.fd;
                char                    buffer[1024];
                ssize_t                 bytesReceived = recv(clientFd, buffer, sizeof(buffer), 0);
                std::string::size_type  sizeBytesReceived = static_cast<std::string::size_type>(bytesReceived);
                
                if (bytesReceived == -1)
                {
                    printErrorMessage(READING_CLIENT_DATA_ERROR);
                    continue;
                }
                if (bytesReceived == 0)
                {
                    // Disconnect client
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, clientFd, &event) == -1)
                        printErrorMessage(READING_CLIENT_DATA_ERROR);
                    std::cout << GREEN << "Closing connection of file descriptor " << RESET << clientFd << std::endl; 

                    quitCmdNc(clientFd, *this);

                    close(clientFd);
                    continue;
                }
                
                std::string     bufferClient(buffer, sizeBytesReceived);
                std::cout << GREEN << "Message from client with fd ("<< RESET << clientFd << GREEN << "): " << RESET << bufferClient << std::endl;

                parsing(bufferClient, *this, clientFd);
            }
        }
    }
    std::cout << GREEN << "Closing socket" RESET << std::endl;
    close(_fd);
    return (0);
}

// Set up chat bot
int     Server::chatBotSetup()
{
    int     optionValue = 1;
    int     chatBotPort = atoi(getPort().c_str()) + 1;
    
    // Create a socket
    if ((_chatBotFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (printErrorMessage(CREATE_SOCKET_ERROR), 1);
    std::cout << GREEN << "Creating Chatbot socket succeed" << RESET << std::endl;
    std::cout << CYAN << "Chatbot Socket fd = " << RESET << _chatBotFd << std::endl;

    // Set socket options    
	if (setsockopt(_chatBotFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optionValue, sizeof(optionValue)) < 0)
        return (printErrorMessage(SET_SOCKET_OPTION_ERROR), 1);

    // Set the socket to non-blocking
	if (fcntl(_chatBotFd, F_SETFL, O_NONBLOCK) < 0)
		return (printErrorMessage(NON_BLOCKING_SOCKET_ERROR), 1);
    std::cout << GREEN << "Setting non blocking socket succeed" << RESET << std::endl;
    
    // Binding socket to an IP address and port
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(chatBotPort);

    if (bind(_chatBotFd, (struct sockaddr*)&_address, sizeof(_address)) < 0)
        return (printErrorMessage(BIND_SOCKET_ERROR NON_AVAILABLE_PORT_ERROR), 1);
    std::cout << GREEN << "Binding socket succeed" << RESET << std::endl;

    // Listen for incoming connections
    if (listen(_chatBotFd, SOCKET_MAX_CONNECTIONS) < 0) 
    return (printErrorMessage(LISTEN_SOCKET_ERROR), 1);

	User	create_user;
	add_user(_chatBotFd, create_user);
	add_user(_chatBotName, _chatBotName, _chatBotName, "localhost", _chatBotName, _chatBotFd);

    return (0);
}

// Ajouter un utilisateur:
void    Server::addIRCUser(int sfd, std::string username, std::string nickname, std::string hostname, std::string realname)
{
    User user = User(sfd, username, nickname, hostname, realname);
    this->_users.insert(std::make_pair(sfd, user));
}

void    Server::add_user(int client_fd, User user)
{
    this->_users.insert(std::make_pair(client_fd, user));
}

void	Server::add_user(std::string nickname, std::string username, std::string hostname, std::string servername, std::string realname, int client_fd)
{
    User    *user = findUser(client_fd);

    user->setNickname(nickname);
    user->setUsername(username);
    user->setHostname(hostname);
    user->setRealname(realname);
    user->setServername(servername);
    user->setClientFd(client_fd);
}

void    Server::delete_user(int client_fd)
{
    this->_users.erase(client_fd);
}

void    Server::removeUser(int sfd)
{
    this->_users.erase(this->_users.find(sfd));
}

// Ajouter un channel:
void    Server::addIRCChannel(std::string name)
{
    if (name.c_str()[0] != '#')
        name = "#" + name;
    Channel channel = Channel(name);
	this->_channels.push_back(channel);
}

void    Server::addIRCChannel(std::string name, std::string password)
{
    if (name.c_str()[0] != '#')
        name = "#" + name;
    Channel channel = Channel(name, password);
	this->_channels.push_back(channel);
}

void     Server::removeIRCChannel(std::string name){
    
    std::vector<Channel>::iterator it = this->_channels.begin();
    std::vector<Channel>::iterator ite = this->_channels.end();

    for ( ; it != ite; it++){
        std::cout << name << std::endl;
    	if (it->getName() == name)
            this->_channels.erase(it);
    }
}

// Envoyer un message a un client: 
int     Server::sendMsg(std::string msg, int fd)
{
    ssize_t sendResult = send(fd, msg.c_str(), static_cast<std::string::size_type>(msg.length()), MSG_CONFIRM);

    if (sendResult < 0)
        return (printErrorMessage(SENDING_CLIENT_MSG_ERROR), -1);
    
    std::cout << GREEN << "Message send to client : " << RESET << msg.c_str() << std::endl;

    return (static_cast<int>(sendResult));
}

// envoyer un message à tous les users des channels de l'user.
void        Server::sendMsgInAllChannelsOfAnUser(User *user, std::string msg)
{
    std::vector<std::string>                channels = user->getChannels();
    std::vector<std::string>::iterator	    it = channels.begin();
    std::vector<std::string>::iterator	    ite = channels.end();
    Channel                                 *channel;
    std::string                             channelName;
    while (it != ite)
    {
        channelName = *it;
        std::cout << "[" << channelName << "]" << std::endl;
        if ((channel = findChannel(channelName)) != NULL)
        {
            channel->sendAllUsers(msg);
        }
        it++;
    }
}

// Retrouver un User ou savoir s'il existe à partir de son nickname:
User    *Server::findUser(std::string nickname)
{
    std::map<int, User>::iterator it;
    
    for (it = this->_users.begin();it != this->_users.end(); it++)
    {
    	if (it->second.getNickname() == nickname)
            return (&it->second);
    }
    return (NULL);
    // return (&it->second);    
}

// Retrouver un Channel ou savoir s'il existe à partir de son nom:
Channel				 *Server::findChannel(std::string name)
{
    std::vector<Channel>::iterator it;
    int     index = 0;

    for (it = this->_channels.begin(); it != this->_channels.end(); it++)
    {
    	if (it->getName() == name)
        {
            index = static_cast<int>(it - this->_channels.begin());
            return &(this->_channels[static_cast<std::vector<Channel>::size_type>(index)]);
        }
    }
    return (NULL);    
}

// Rechercher un User dans une map ou savoir s'il existe à partir de sa clé (socket file descriptor):
User        		 *Server::findUser(int fd)
{
    std::map<int, User>::iterator it = this->_users.find(fd);
    if (it != this->_users.end())
        return (&it->second);
    return (NULL);
}


// Operator << Overload
std::ostream    &operator<<(std::ostream &out, Server const &server)
{ 
    out << CYAN "Server Infos: " << RESET << "\n" 
        << MAGENTA << "Port     = " << RESET << server.getPort() << "\n" 
        << MAGENTA << "Password = " << RESET << server.getPassword() << "\n"
        << MAGENTA << "Fd       = " << RESET << server.getFd() << "\n"
        << MAGENTA << "Time     = " << RESET << server.getTime() << std::endl;
    return (out);
}
