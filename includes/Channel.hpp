#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "./Include.hpp"
#include "./User.hpp"

enum	chanModes
{
	INVITE_MODE     				=  1,    											// 0000 0001,  i invite        1 si le chan est en mode invite only
	MODERATE_MODE   				=  2,    											// 0000 0010,  m moderated     1 si le mode est modéré, CAD que seuls les op et les users autorisés à parler (voiced, mode +v) pouvent parler sur le chan
	PRIVATE_MODE    				=  4,    											// 0000 0100,  p private       1 si le channel est en mode privé (le topic ne doit pas etre affiché)
	KEY_MODE        				=  8,    											// 0000 1000,  k key           1 si un password a été assigné au channel
	SECRET_MODE     				=  16,   											// 0001 0000,  s secret        1 si le le mode secret du chan est activé (/MODE +)
	LIMITED_MODE    				=  32,   											// 0010 0000,  l users limit   1 si nombre limite d'utilisateurs est défini(/MODE +l [nbr])
	TOPIC_MODE      				=  64	 											// 0100 0000,  t topic		    1 si seuls les ChannelOperator peuvent changer le topic
};

class	Channel
{
	private:
		
		std::string					_name;													// nom du channel
		std::string					_password;												// mot de passe du channel
		std::string					_topic;													// sujet du channel

		int							_maxUsers;												// nombre maximum d'utilisateurs autorisés à se connecter sur ce channel
		std::map<int, User *>		_usersMap;												// liste des utilisateurs connectés au channel
		std::map<int, User *>		_operatorsMap;											// liste des opérateurs connectés sur le channel
		std::map<int, User *>		_voiceMap;												// liste des users autorisés à parler sur le chan, en dehors des opérateurs
		std::map<int, User *>		_banMap;												// liste des users bannis
		std::map<int, User *>		_inviteMap;												// liste des users invités dans le chan

		int 						_chanModes;												// format binaire qui indique les modes du channel.
		std::string					_chanStatus;											// contient les modes du channel sous forme de string à afficher lors de /list
	

	public:

		// CONTRUCTORS / DESTRUCTOR
		Channel(std::string name);
		Channel(std::string name, std::string password);
		Channel(std::string name, std::map<int, User *> usersMap);
		Channel();
		~Channel();

		Channel(Channel const &rhs);
        Channel &operator=(Channel const &rhs);

		// *** GETTERS ***
		std::string					getName() const;
		int							getID() const;
		std::string					getPassword() const;
		std::string					getTopic() const;
		size_t						getMaxUsers() const;
		User						*getUser(std::string user);

		std::map<int, User *>		&getUsersMap();
		std::map<int, User *>		&getOperatorsMap();
		std::map<int, User *>		&getVoiceMap();
		std::map<int, User *>		&getBanMap();
		std::map<int, User *>		&getInviteMap();

		int 						&getModes(); 											// modes du channel (code numérique)
		std::string 				&getStatus(); 											// modes du channel (lettres)

		// AFFICHER LA LISTE DES USERS DANS UNE MAP :
		void			 			printUsersMap(std::map<int, User *> map);
		
		// VERIFIER LA PRESENCE D'UN UTILISATEUR DANS UNE MAP:
		User						*findUser(int sfd, std::map<int, User *> map);
		
		// ENVOYER UN MESSAGE A TOUS LES USERS: 
		void						sendAllUsers(std::string msg);


		// *** SETTERS ***

		//  AJOUTER OU MODIFIER LE PASSWORD:
		void						setPassword(std::string password);
		
		// 	AJOUTER UN USER A UNE LISTE:
		void						addUser(int sfd, User *user);
		void						addOperator(int sfd, User *user);
		void						addVoiced(int sfd, User *user);
		void						addBan(int sfd, User *user);
		void						addInvite(int sfd, User *user);

		// SUPPRIMER UN UTILISATEUR D'UNE LISTE: 
		void						removeUser(int sfd, std::map<int, User *> map);
		void						removeUserKick(int sfd, std::map<int, User *> &map);
		
		// DEFINIR DES PROPRIETES AU CHANNEL: 
		void						setTopic(std::string topic);
		void						setMaxUsers(int maxUsers);
		void						addMode(int to_add);
		void						removeMode(int to_rmv);
		void						setStatus();											// maj automatique avec addMode() et rmvMode()
};

#endif
