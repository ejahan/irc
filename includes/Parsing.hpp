/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 06:25:38 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 23:48:07 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include "./Include.hpp"
#include "./Server.hpp"
#include "./Command.hpp"

class	Parsing
{
	private:

		Server 						&ircServ;
		std::string					buffer;
		int							client_fd;
		std::vector<std::string>	vect;

		typedef void	(Parsing::*ptr)(void);

		std::string					tab[18];
		ptr							functptr[19];


	public:

		Parsing(Server &ircServ, std::string buffer, int client_fd, std::vector<std::string> vect);
		~Parsing() {};

		void				invitePars();
		void				joinPars();
		void				kickPars();
		void				killPars();
		void				listPars();
		void				modePars();
		void				motdPars();
		void				namesPars();
		void				nickPars();
		void				noticePars();
		void				operPars();
		void				partPars();
		void				passPars();
		void				pingPars();
		void				privmsgPars();
		void				quitPars();
		void				topicPars();
		void				userPars();
		void				error();
			
		void				parser(std::string str);

};

//////////////////////////////////////////////////////////////////////////////////
//	                                 PARSING                                    //
//////////////////////////////////////////////////////////////////////////////////

void						parsing(std::string buffer, Server &ircServ, int client_fd);

//////////////////////////////////////////////////////////////////////////////////
//									   UTILS									//
//////////////////////////////////////////////////////////////////////////////////

void						printVector(std::vector<std::string> vect);
void	        			printMap(std::map<int, User*> map);
void        				printMapParsing(std::map<int, User> map);
std::string	 				joinMessage(std::string buffer);
int							checkChannel(int i, std::vector<std::string> vect);
void						sendMessage(int fd, std::string msg);
void						sendMsgChannel(std::map<int, User*> channel, std::string message);
void						sendMsgChannelQuit(std::map<int, User*> channel, std::string message, std::string name, std::string hostname);
void						sendMessageNick(int fd, std::string nick, std::string begin, std::string end);
std::string					itoa(int a);
std::string					lowerCase(std::string str);


//////////////////////////////////////////////////////////////////////////////////
//								      COMMANDS								    //
//////////////////////////////////////////////////////////////////////////////////

void						kickCmd(Command &cmd, Server &ircServ);
void						killCmd(Command &cmd, Server &ircServ);
void						motdCmd(Command &cmd, Server &ircServ);
std::string					chatMotd();
void						noticeCmd(Command &cmd, Server &ircServ);
void						operCmd(Command &cmd, Server &ircServ);
void						passCmd(Command &cmd, Server &ircServ);
void						pingCmd(Command &cmd, Server &ircServ);
void						privmsgCmd(Command &cmd, Server &ircServ);
void						quitCmd(Command &cmd, Server &ircServ);
void	        			quitCmdNc(int client_fd, Server &ircServ);
void						userCmd(std::string nickname, std::string hostname, Command &cmd, Server &ircServ);

std::vector<std::string>	listCmdStr(std::string str, Server &ircServ);
int							check_min(std::vector<std::string> vect);
int							check_max(std::vector<std::string> vect);
std::string					check_str(std::vector<std::string> vect);
void						listCmd(Command &cmd, Server &ircServ);


void            			invite(Command &command, Server &server);
void            			join(Command *command, Server *server);
void            			names(Command &command, Server &server);
void            			nick(Command &command, Server &server);
void            			part(Command &command, Server &server);
void            			topic(Command &command, Server &server);
void						mode(Command &command, Server &server);

#endif
