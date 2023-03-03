/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <grannou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 03:21:35 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/20 23:50:43 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "./Include.hpp"

enum	userModes
{
	INVISIBLE_MODE					= 1,	 									// 0000 0001   i invisible     1 si l'utilisateur est en mode invisible. Il n'apparait pas du tout dans le /WHO et /NAMES
	OPERATOR_MODE					= 4		 									// 0000 0100   o operator		1 si l'utilisateur est opérateur du serveur IRC il peut KILL.
}; 

// ajouter la liste des channels sur lesquels il est connecté?

class	User
{
	private:

		int							_sfd;
		std::string					_username;
		std::string					_nickname;
		std::string 				_hostname;
		std::string 				_realname;
		std::string					_servername;
		
		std::vector<std::string>	_channels;

		char						_userModes;
		std::string 				_userStatus;

		int							_pass;
		int							_nick;
		int							_connected;
		int							_fd;
		int							_chatbot;

		std::string					_buf;

	public:

		// CONSTRUCTOR / DESTRUCTOR
		User();
		User(int sfd, std::string username, std::string nickname, std::string hostname, std::string realname);
		User(int sfd, std::string username, std::string nickname, std::string hostname, std::string realname, char userModes);
		User(std::string nickname, std::string username, std::string hostname, std::string servername, std::string realname);
		~User(void);

		User(User const &rhs);
        User &operator=(User const &rhs);

		// SETTER
		void						setNickname(std::string nickname);
		void						setUsername(std::string username);
		void						setHostname(std::string hostname);
		void						setRealname(std::string realname);
		void						setServername(std::string servername);
		void						setUserModes(char userModes);				// modes de l'user sous format numérique
		void						setUserStatus();							// modes de l'user sous forme de lettres
		void						setPass(int i);
		void						setConnected(int i);
		void						setNick(int i);
		void						setClientFd(int i);
		void						setBuf(std::string str);
		void						setChat(int i);

		void						addMode(char to_add);
		void						removeMode(char to_rmv);
		
		void						addChannel(std::string name);
		int							removeChannel(std::string name);
		
		// GETTER
		std::string					getUserSfd() const;							//renvoie le sfd du User sous forme de string
		int							getUserSfdN() const;						//renvoie le sfd sous forme d'entier
		std::string					getUsername() const;
		std::string					getNickname() const;
		std::string 				getHostname() const;
		std::string					getLocalhost() const;
		std::string 				getRealname() const;
		char						getUserModes() const;
		std::string					getUserStatus() const;
		int							getPass();
		int							getConnected();
		int							getNick();
		int							getClientFd();
		std::string					getBuf();
		int							getChat();
		
		std::vector<std::string>	getChannels() const;
		int							findChannel(std::string name) const;
		void						printChannels() const;
};

std::ostream    &operator<<(std::ostream &out, User const &user);

#endif
