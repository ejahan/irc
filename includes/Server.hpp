/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 07:19:13 by grannou           #+#    #+#             */
/*   Updated: 2023/02/21 00:19:42 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

# define SERVER_HPP

// #pragma once is a preprocessor directive used to prevent header files 
// from being included multiple times. 
// The #pragma once directive, once present in a file, assures that the file 
// will not be included multiple times in the current project.
# pragma once

# include "Channel.hpp"
# include "User.hpp"
# include "Command.hpp"
# include "Include.hpp"

// Terminal color display
# define BLACK                          "\033[30m"
# define RED                            "\033[31m"
# define GREEN                          "\033[32m"
# define YELLOW                         "\033[33m"
# define BLUE                           "\033[34m"
# define MAGENTA                        "\033[35m"
# define CYAN                           "\033[36m"
# define WHITE                          "\033[37m"
# define RESET                          "\033[0m"

# define KYU                            "🔮🦋🧡🍁🐞🍄🍀🌇🌸🐹🌳🦊🐼🌿🧡🦊🧡🌿🐼🦊🌳🐹🌸🌇🍀🍄🐞🍁🧡🦋🔮\n"
# define BIE                            "🍀🌸🦊                                                  🦊🌸🍀\n"
# define ARGS_ERROR                     "🎑🌸🦊 " YELLOW "ERROR" RESET " : wrong number of arguments                🦊🌸🎑\n"
# define PROGRAM_LAUNCH1                "🎑🌸🦊 " CYAN "Launch" RESET " ./ircserv <port> <password>               🦊🌸🎑\n"
# define PROGRAM_LAUNCH2                "🎑🌸🦊 " CYAN "or make run" RESET " (./ircserv 6667 password)            🦊🌸🎑\n"
# define PORT_DIGIT_ERROR               "🎑🌸🦊 " YELLOW "ERROR" RESET " : port number is not a number              🦊🌸🎑\n"
# define PORT_RANGE_ERROR               "🎑🌸🦊 " YELLOW "ERROR" RESET " : port number is out of range              🦊🌸🎑\n"
# define PASSWORD_ERROR                 "🎑🌸🦊 " YELLOW "ERROR" RESET " : password is too long                     🦊🌸🎑\n"
# define VALID_INPUT                    "🎑🌸🦊                 " GREEN "VALID INPUT" RESET "                      🦊🌸🎑\n"

# define INIT_SERVER_ERROR              "🎑🌸🦊 " YELLOW "ERROR" RESET " : init server failed                       🦊🌸🎑\n"
# define INIT_CHATBOT_ERROR             "🎑🌸🦊 " YELLOW "ERROR" RESET " : init chatbot failed                      🦊🌸🎑\n"
# define CREATE_SOCKET_ERROR            "🎑🌸🦊 " YELLOW "ERROR" RESET " : creating socket failed                   🦊🌸🎑\n"
# define SET_SOCKET_OPTION_ERROR        "🎑🌸🦊 " YELLOW "ERROR" RESET " : setting socket options failed            🦊🌸🎑\n"
# define BIND_SOCKET_ERROR              "🎑🌸🦊 " YELLOW "ERROR" RESET " : binding socket failed                    🦊🌸🎑\n"
# define NON_AVAILABLE_PORT_ERROR       "🎑🌸🦊 " YELLOW "ERROR" RESET " : port is not available                    🦊🌸🎑\n"
# define NON_BLOCKING_SOCKET_ERROR      "🎑🌸🦊 " YELLOW "ERROR" RESET " : setting non blocking socket failed       🦊🌸🎑\n"
# define LISTEN_SOCKET_ERROR            "🎑🌸🦊 " YELLOW "ERROR" RESET " : listening on socket failed               🦊🌸🎑\n"
# define INITIALISE_SOCKET_ERROR        "🎑🌸🦊 " YELLOW "ERROR" RESET " : Initialising socket failed               🦊🌸🎑\n"

# define CREATE_EPOLL_FD_ERROR          "🎑🌸🦊 " YELLOW "ERROR" RESET " : creating epoll fd failed                 🦊🌸🎑\n"
# define EPOLL_FD_ERROR                 "🎑🌸🦊 " YELLOW "ERROR" RESET " : epoll err/hup/in                         🦊🌸🎑\n"
# define ADDING_SERVER_FD_EPOLL_ERROR   "🎑🌸🦊 " YELLOW "ERROR" RESET " : adding server fd to epoll failed         🦊🌸🎑\n"
# define ADDING_CLIENT_FD_EPOLL_ERROR   "🎑🌸🦊 " YELLOW "ERROR" RESET " : adding client fd to epoll failed         🦊🌸🎑\n"
# define READING_CLIENT_DATA_ERROR      "🎑🌸🦊 " YELLOW "ERROR" RESET " : reading data from client failed          🦊🌸🎑\n"
# define REMOVING_CLIENT_FD_EPOLL_ERROR "🎑🌸🦊 " YELLOW "ERROR" RESET " : removing client fd to epoll failed       🦊🌸🎑\n"
# define WAITING_EPOLL_ERROR            "🎑🌸🦊 " YELLOW "ERROR" RESET " : waiting epoll events failed              🦊🌸🎑\n"
# define ACCEPTING_CONNECTION_ERROR     "🎑🌸🦊 " YELLOW "ERROR" RESET " : accepting connection failed              🦊🌸🎑\n"

# define SENDING_CLIENT_MSG_ERROR       "🎑🌸🦊 " YELLOW "ERROR" RESET " : sending message to client failed         🦊🌸🎑\n"

// Clear terminal display
# define CLEARLINE                      "\033[2J\033[1;1H"

# define SERVER_PORT                    6667
# define SERVER_PASSWORD                "password"
# define SERVER_PASSWORD_LENGTH         12
# define TRUE                           1
# define FALSE                          0
# define PORT_MAX                       65535
# define SOCKET_MAX_CONNECTIONS         10
# define MAX_EVENTS                     64
# define PING_TIME                      15


class Server
{
    private:

        std::string             _port;
        std::string             _password;
        int                     _fd;
        std::time_t             _time;
        struct sockaddr_in      _address;
        
        // LISTE DE TOUS LES CHANNELS DU SERVER
        std::vector<Channel>	_channels;
        
        // LISTE DE TOUS LES USERS DU SERVER (associes a leur socket)
        std::map<int, User>		_users;

        // Bonus chat bot
        std::string             _chatBotName;
        int                     _chatBotFd;
        std::string             _answers[20];

    protected:

    public:

        // Default Constructor
        Server(void);

        // Constructor with parameter
        Server(std::string port, std::string password);

        // Copy Constructor
        Server (Server const &source);

        // Copy Assignment
        Server &operator=(Server const &rhs);

        // Destructor
        ~Server();

        // Getter Member Functions
        std::string                 getPort() const;
        std::string                 getPassword() const;
        int                         getFd() const;
        std::time_t                 getTime() const;
        std::vector<Channel>        getIRCChannels() const;
        std::map<int, User>         getIRCUsers() const;
        std::string                 getAnswer(int i);

        // Setter Member Functions
        void                        setPort(std::string port);
        void                        setPassword(std::string password);
        void                        setFd(int fd);
        void                        setTime(std::time_t time);
        
        // ajouter un utilisateur ou un channel : 
        void                        addIRCChannel(std::string name);
        void                        addIRCChannel(std::string name, std::string password);
        void                        addIRCUser(int sfd, std::string username, std::string nickname, std::string hostname, std::string realname);
        
        // supprimer un utilisateur ou un channel: 
        void                        removeIRCChannel(std::string name);
        void                        removeUser(int sfd);

        // Launch and run server
        int                         setup();
        int                         run();
        
        // Bonus chatbot create socket and user
        int                         chatBotSetup();

        // Send message with send(): 
        int                         sendMsg(std::string msg, int fd);                                           // envoyer un message en utilisant send();
        void				        sendMsgInAllChannelsOfAnUser(User *user, std::string msg);

        // Finder:
	    User				        *findUser(int fd);                                                          // retourner un pointeur d'une instance User a partir de son SFD
	    User				        *findUser(std::string nickname);                                            // retourner pointeur d'une instance User a partir de son nickname
        Channel				        *findChannel(std::string name);                                             // retourner pointeur d'une instance Channel a partir de son nom

		void                        add_user(int client_fd, User user);
		void                        add_user(std::string nickname, std::string username, std::string hostname, std::string servername, std::string realname, int client_fd);
		void                        delete_user(int client_fd);
};

// Operator << overload
std::ostream                        &operator<<(std::ostream &out, Server const &server);

// Utils.cpp
void                                printErrorMessage(std::string msg);
void	                            print_log(const std::string& message);
bool                                isInteger(const char *str);
int                                 checkArguments(int argc, char **argv);
void                                welcomeClient(int client_fd);
void                                *ft_memset(void *ptr, int value, std::size_t len);
void                                cleanExit(void);


#endif
