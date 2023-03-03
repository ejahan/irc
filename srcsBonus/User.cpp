/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 03:21:42 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/21 00:23:19 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parsing.hpp"
#include "../includes/User.hpp"

/*=====================================================*/
/* 				CONTRUCTOR / DESTRUCTOR				   */
/*=====================================================*/

User::User()
{
	this->_pass = 0;
	this->_connected = 0;
	this->_nick = 0;
	this->_chatbot = 0;
}

User::User(int sfd, std::string username, std::string nickname, std::string hostname, std::string realname):\
_sfd(sfd), _username(username), _nickname(nickname), _hostname(hostname), _realname(realname){
	this->_userModes = (char)0;
	this->_pass = 0;
	this->_connected = 0;
	this->_nick = 0;
	this->_chatbot = 0;
}

User::User(int sfd, std::string username, std::string nickname, std::string hostname, std::string realname, char userModes):\
_sfd(sfd), _username(username), _nickname(nickname), _hostname(hostname), _realname(realname), _userModes(userModes){
	this->_pass = 0;
	this->_connected = 0;
	this->_nick = 0;
	this->_chatbot = 0;
}

User::User(std::string nickname, std::string username, std::string hostname, std::string servername, std::string realname)
{
	this->_nickname = nickname;
	this->_username = username;
	this->_hostname = hostname;
	this->_servername = servername;
	this->_realname = realname;
	this->_pass = 0;
	this->_connected = 0;
	this->_nick = 0;
	this->_chatbot = 0;
}

User::User(User const &rhs)
{
	*this = rhs;
	return ;
}

User &User::operator=(User const &rhs)
{
	this->_username = rhs._username;
	this->_nickname = rhs._nickname;
	this->_hostname = rhs._hostname;
	this->_realname = rhs._realname;
	this->_servername = rhs._servername;
	this->_channels = rhs._channels;
	this->_userModes = rhs._userModes;
	this->_userStatus = rhs._userStatus;
	this->_chatbot = rhs._chatbot;
	this->_pass = rhs._pass;
	this->_connected = rhs._connected;
	this->_nick = rhs._nick;
	this->_buf = rhs._buf;
	this->_fd = rhs._fd;
	this->_sfd = rhs._sfd;

    return (*this);
}

User::~User(void)
{
}

/*=====================================================*/
/* 					     SETTER						   */
/*=====================================================*/

void		User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}

void		User::setUsername(std::string username)
{
	this->_username = username;
}

void		User::setHostname(std::string hostname)
{
	this->_hostname = hostname;
}

void		User::setRealname(std::string realname)
{
	this->_realname = realname;
}

void		User::setServername(std::string servername)
{
	this->_servername = servername;
}

void		User::setUserModes(char userModes)
{
	this->_userModes = userModes;
	this->setUserStatus();
}

void		User::setUserStatus()
{
	this->_userStatus = "";

	if (this->_userModes & INVISIBLE_MODE)
		this->_userStatus += "i";
	if (this->_userModes & OPERATOR_MODE)
		this->_userStatus += "o";
	if (this->_userStatus != "")
		this->_userStatus = "+" + this->_userStatus;
}

void	User::setPass(int i)
{
	this->_pass = i;
}

void	User::setConnected(int i)
{
	this->_connected = i;
}

void	User::setNick(int i)
{
	this->_nick = i;
}

void	User::setClientFd(int i)
{
	this->_fd = i;
	this->_sfd = i;
}

void	User::setBuf(std::string str)
{
	this->_buf = str;
}

void	User::setChat(int i)
{
	this->_chatbot = i;
}

//activer un mode (forme binaire):
void		User::addMode(char to_add)
{
	this->_userModes |= to_add;
	this->setUserStatus();
}

//désactiver un mode (forme binaire):
void		User::removeMode(char to_rmv)
{
	this->_userModes ^= to_rmv;
	this->setUserStatus();
}

void		User::addChannel(std::string name)
{
	this->_channels.push_back(name);
	std::cout << "name = " << name << std::endl;
}

// enlever un channel de la liste des channels actifs du user: 
int			User::removeChannel(std::string name){
	if (this->findChannel(name)){	
		this->_channels.erase(std::remove(this->_channels.begin(), this->_channels.end(), name), this->_channels.end());
		return (1);
	}
	return (0);
}

/*=====================================================*/
/* 					     GETTER						   */
/*=====================================================*/

std::string			User::getUserSfd() const
{
	std::stringstream ss;
	ss << this->_sfd;
	std::string str = ss.str();
	return (str);
}

int			User::getUserSfdN() const
{
	return (this->_sfd);
}

std::string	User::getUsername() const
{
	return (this->_username);
}

std::string	User::getNickname() const
{
	return (this->_nickname);
}

std::string	User::getHostname() const
{
	return (this->_nickname + "!" + this->_username + "@" + this->_hostname);
}

std::string	User::getLocalhost() const
{
	return (this->_nickname + "!~" + this->_username + "@" + "62.5017282");
}

std::string	User::getRealname() const
{
	return (this->_realname);
}

char		User::getUserModes() const
{
	return (this->_userModes);
}

std::string	User::getUserStatus() const
{
	return (this->_userStatus);
}

int	User::getPass()
{
	return (_pass);
}

int	User::getConnected()
{
	return (_connected);
}

int	User::getNick()
{
	return (_nick);
}

int	User::getClientFd()
{
	return (_fd);
}

std::string	User::getBuf()
{
	return (_buf);
}

int	User::getChat()
{
	return (this->_chatbot);
}

std::vector<std::string>	User::getChannels() const
{
	return (this->_channels);
}

void						User::printChannels() const
{
	std::vector<std::string>::iterator it;

	for (it = this->getChannels().begin(); it != this->getChannels().end(); it++)
	{
		std::cout << "[" << *it << "]" << std::endl;
	}
}

int							User::findChannel(std::string name) const
{
	std::vector<std::string>				channel = getChannels();
	std::vector<std::string>::iterator		it = channel.begin();
	std::vector<std::string>::iterator 		ite = channel.end();

	while (it != ite)
	{
		if (*it == name)
		{
			return (1);
		}
		it++;
	}
	return (0);
}

// Operator << Overload
std::ostream    &operator<<(std::ostream &out, User const &user)
{ 
    out << CYAN "User Infos: \n" 
		<< MAGENTA << "ClienFD   = " << RESET << user.getUserSfdN() << "\n"
        << MAGENTA << "Nickname  = " << RESET << user.getNickname() << "\n" 
        << MAGENTA << "Username  = " << RESET << user.getUsername() << "\n"
        << MAGENTA << "Hostname  = " << RESET << user.getHostname() << "\n"
        << MAGENTA << "Realname  = " << RESET << user.getRealname() << "\n";
    return (out);
}
