/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:44:38 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 09:51:19 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.hpp"

Parsing::Parsing(Server &_ircServ, std::string _buffer, int _client_fd, std::vector<std::string> _vect) : ircServ(_ircServ)
{
	buffer = _buffer;
	client_fd = _client_fd;
	vect = _vect;

	tab[0] = "INVITE";
	tab[1] = "JOIN";
	tab[2] = "KICK";
	tab[3] = "kill";
	tab[4] = "LIST";
	tab[5] = "MODE";
	tab[6] = "motd";
	tab[7] = "NAMES";
	tab[8] = "NICK";
	tab[9] = "NOTICE";
	tab[10] = "OPER";
	tab[11] = "PART";
	tab[12] = "PASS";
	tab[13] = "PING";
	tab[14] = "PRIVMSG";
	tab[15] = "QUIT";
	tab[16] = "TOPIC";
	tab[17] = "USER";

	functptr[0] = &Parsing::invitePars;
	functptr[1] = &Parsing::joinPars;
	functptr[2] = &Parsing::kickPars;
	functptr[3] = &Parsing::killPars;
	functptr[4] = &Parsing::listPars;
	functptr[5] = &Parsing::modePars;
	functptr[6] = &Parsing::motdPars;
	functptr[7] = &Parsing::namesPars;
	functptr[8] = &Parsing::nickPars;
	functptr[9] = &Parsing::noticePars;
	functptr[10] = &Parsing::operPars;
	functptr[11] = &Parsing::partPars;
	functptr[12] = &Parsing::passPars;
	functptr[13] = &Parsing::pingPars;
	functptr[14] = &Parsing::privmsgPars;
	functptr[15] = &Parsing::quitPars;
	functptr[16] = &Parsing::topicPars;
	functptr[17] = &Parsing::userPars;
	functptr[18] = &Parsing::error;
}

void	Parsing::parser(std::string level)
{
	int	i;

	i = 0;
	while (i < 18)
	{
		if (tab[i].compare(level) == 0)
		{
			(this->*functptr[i])();
			return ;
		}
		i++;
	}
	this->error();
}

void	Parsing::error()
{
	if (ircServ.findUser(client_fd)->getConnected() == 0)
		return ;
	std::string	error = vect.front();
	error += " :Unknown command\r\n";
	send(client_fd, error.c_str(), static_cast<std::string::size_type>(error.length()), 0);
}

void	Parsing::invitePars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() < 3)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "INVITE");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else if (checkChannel(2, vect) == 1)
		std::cout << "error: channel: wrong syntaxe" << std::endl;
	else
	{
		cmd.add_nick(vect[1]);
		cmd.add_channels(vect[2]);
		cmd.add_client_fd(client_fd);
		invite(cmd, ircServ);
	}
}

void	Parsing::joinPars()
{
	std::string	message;
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() < 2)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "JOIN");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else if (checkChannel(1, vect) == 1)
		std::cout << "Error: channel: wrong syntaxe" << std::endl;
	else 
	{
		if (vect.size() > 2)
		{
			message = joinMessage(buffer);
			if (message.size() != buffer.size())
				cmd.add_message(message);
		}
		cmd.add_channels(vect[1]);
		cmd.add_client_fd(client_fd);
		join(&cmd, &ircServ);
		printVector(ircServ.findUser(client_fd)->getChannels());
	}
}

void	Parsing::kickPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() < 3)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "KICK");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else if (checkChannel(1, vect) == 1)
		std::cout << "Error: channel: wrong syntaxe" << std::endl;
	else 
	{
		if (vect.size() > 3)
		{
			std::string message = joinMessage(buffer);
			if (message.size() != buffer.size())
				cmd.add_message(message);
		}
		cmd.add_channels(vect[1]);
		cmd.add_nick(vect[2]);
		cmd.add_client_fd(client_fd);
		kickCmd(cmd, ircServ);
	}
}

void	Parsing::killPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() < 2)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "KILL");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else
	{
		if (vect.size() > 2)
		{
			std::string message = joinMessage(buffer);
			if (message.size() != buffer.size())
				cmd.add_message(message);
		}
		cmd.add_nick(vect[1]);
		cmd.add_client_fd(client_fd);
		killCmd(cmd, ircServ);
	}
}

void	Parsing::listPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	cmd.add_client_fd(client_fd);

	if (vect.size() > 1)
	{
		std::string channels = vect[1];
		std::istringstream iss(channels);
		std::string token;

		while (std::getline(iss, token, ','))
		{
			channels = token;
			if (channels[0] != '#')
			{
				std::cout << "Error: channel: wrong syntaxe" << std::endl;
				return ;
			}
			cmd.add_channels(channels);
		}
		cmd.print_all();
	}
	listCmd(cmd, ircServ);
}

void	Parsing::modePars()
{
	Command cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() < 3)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "MODE");
		// send(client_fd, err.c_str(), err.size(), 0);
	}
	else
	{
		if (vect[1][0] == '#')
			cmd.add_channels(vect[1]);
		else
			cmd.add_nick(vect[1]);

		std::vector<std::string>::iterator	it = vect.begin() + 2;
		std::vector<std::string>::iterator	ite = vect.end();

		while (it != ite)
		{
			cmd.add_message(*it);
			it++;
		}

		cmd.add_client_fd(client_fd);
		cmd.print_all();
		mode(cmd, ircServ);
	}
}

void	Parsing::motdPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() == 2)
		cmd.add_server(vect[1]);
	cmd.add_client_fd(client_fd);
	motdCmd(cmd, ircServ);
}

void	Parsing::namesPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	else if (vect.size() == 2 && checkChannel(1, vect) == 1)
		std::cout << "Error: channel: wrong syntaxe" << std::endl;
	else
	{
		if (vect.size() >= 2)
			cmd.add_channels(vect[1]);
		cmd.add_client_fd(client_fd);
		names(cmd, ircServ);
	}
}

void	Parsing::nickPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getPass() != 1)
	{
		if (ircServ.findUser(client_fd)->getPass() == 0)
		{
			std::string err = ERR_PASSWDMISMATCH(ircServ.findUser(client_fd)->getHostname(), ircServ.findUser(client_fd)->getNickname());
			send(client_fd, err.c_str(), err.size(), 0);
		}
		return ;
	}
	else
	{
		if (vect.size() > 1)
			cmd.add_nick(vect[1]);
		cmd.add_client_fd(client_fd);
		nick(cmd, ircServ);
	}
}

void	Parsing::noticePars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect[1][0] == ':')
	{
		std::string err = ERR_NORECIPIENT(ircServ.findUser(client_fd)->getHostname(), "NOTICE");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else
	{
		std::string message = joinMessage(buffer);
		if (vect[1][0] == '#')
			cmd.add_channels(vect[1]);
		else
			cmd.add_nick(vect[1]);
		if (message.size() == buffer.size())
		{
			std::string err = ERR_NOTEXTTOSEND(ircServ.findUser(client_fd)->getHostname());
			send(client_fd, err.c_str(), err.size(), 0);
			return ;
		}
		cmd.add_message(message);
		cmd.add_client_fd(client_fd);
		noticeCmd(cmd, ircServ);
	}
}

void	Parsing::operPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() < 3)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "OPER");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else
	{
		cmd.add_nick(vect[1]);
		cmd.add_message(vect[2]);
		cmd.add_client_fd(client_fd);
		operCmd(cmd, ircServ);
	}
}

void	Parsing::partPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() < 2)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "PART");
		send(client_fd, err.c_str(), err.size(), 0);
		return ;
	}

	std::string channels = vect[1];
	std::istringstream iss(channels);
	std::string token;

	while (std::getline(iss, token, ','))
	{
		channels = token;
		if (channels[0] != '#')
		{
			std::cout << "Error: channel: wrong syntaxe" << std::endl;
			return ;
		}
		cmd.add_channels(channels);
	}

	cmd.add_client_fd(client_fd);
	part(cmd, ircServ);
}

void	Parsing::passPars()
{
	Command	cmd;

	if (vect.size() < 2)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getLocalhost(), "PASS");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else
	{
		cmd.add_message(vect[1]);
		cmd.add_client_fd(client_fd);
		passCmd(cmd, ircServ);
	}
}

void	Parsing::pingPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() < 2)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "PING");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else
	{
		if (vect[1][0] == '#')
			cmd.add_channels(vect[1]);
		else
			cmd.add_nick(vect[1]);
		cmd.add_client_fd(client_fd);
		pingCmd(cmd, ircServ);
	}
}

void	Parsing::privmsgPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect[1][0] == ':')
	{
		std::string err = ERR_NORECIPIENT(ircServ.findUser(client_fd)->getHostname(), "PRIVMSG");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else
	{
		std::string message = joinMessage(buffer);
		if (vect[1][0] == '#')
			cmd.add_channels(vect[1]);
		else
			cmd.add_nick(vect[1]);
		if (message.size() == buffer.size())
		{
			std::string err = ERR_NOTEXTTOSEND(ircServ.findUser(client_fd)->getHostname());
			send(client_fd, err.c_str(), err.size(), 0);
			return ;
		}
		cmd.add_message(message);
		cmd.add_client_fd(client_fd);
		privmsgCmd(cmd, ircServ);
	}
}

void	Parsing::quitPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() > 1)
	{
		std::string message = joinMessage(buffer);
		if (message.size() != buffer.size())
			cmd.add_message(message);
	}
	cmd.add_client_fd(client_fd);
	quitCmd(cmd, ircServ);
}

void	Parsing::topicPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getConnected() == 0)
	{
		std::cout << "client not connected" << std::endl;
		return ;
	}
	if (vect.size() < 2)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "TOPIC");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else if (checkChannel(1, vect) == 1)
		std::cout << "Error: channel: wrong syntaxe" << std::endl;
	else
	{
		if (vect.size() > 2)
		{
			std::string message = joinMessage(buffer);
			if (message.size() != buffer.size())
				cmd.add_message(message);
		}
		cmd.add_channels(vect[1]);
		cmd.add_client_fd(client_fd);
		topic(cmd, ircServ);
	}
}

void	Parsing::userPars()
{
	Command	cmd;

	if (ircServ.findUser(client_fd)->getNick() == 0)
	{
		std::cout << "no nickname set" << std::endl;
		return ;
	}
	if (vect.size() < 5)
	{
		std::string err = ERR_NEEDMOREPARAMS(ircServ.findUser(client_fd)->getHostname(), "USER");
		send(client_fd, err.c_str(), err.size(), 0);
	}
	else
	{
		std::string message = joinMessage(buffer);
		if (message.size() == buffer.size())
			message = vect[4];
		cmd.add_message(message);
		cmd.add_server(vect[3]);
		cmd.add_nick(vect[1]);
		cmd.add_client_fd(client_fd);
		userCmd(vect[2], ircServ.findUser(client_fd)->getNickname(), cmd, ircServ);
	}
}
