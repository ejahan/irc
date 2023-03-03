=========================
LIENS UTILES / A REGARDER
=========================

	- creer un serveur:
	https://www.youtube.com/watch?v=cNdlrbZSkyQ&list=PLUJCSGGiox1Q-QvHfMMydtoyEa1IEzeLe&index=2

	- "tuto":
	https://github.com/GuillaumeOz/ft_irc/tree/main/note

	- commandes irc:
	https://linux.developpez.com/formation_debian/irc.html
	https://www.techbull.com/techbull/guide/internet/irccommande.html

	- specification irc:
	http://www.iprelax.fr/irc/irc_rfcfr2.php#:~:text=Les%20messages%20IRC%20sont%20toujours,compris%20le%20CR%2DLF%20final.


	- USER/PASS/NICK:
	https://stackoverflow.com/questions/31666247/what-is-the-difference-between-the-nick-username-and-real-name-in-irc-and-wha
	https://en.wikipedia.org/wiki/List_of_Internet_Relay_Chat_commands

	- REPLY:
	http://www.iprelax.fr/irc/irc_rfcfr4.php




=====
NOTES
=====

	operators:
	peut déconnecter de force les utilisateurs (Kill) et interdire les utilisateurs ( K-line ou G-line )
	"/stats o [servername]" permet de voir la liste des operateurs sur un serveur particulier
	Un utilisateur peut devenir un opérateur en envoyant la commande /oper au serveur irc sur lequel il se trouve actuellement en utilisant un nom d'utilisateur et un mot de passe présélectionnés comme paramètres (Syntaxe : /oper <userid> <password>)

	messages:
	Chaque message IRC peut contenir jusqu'à trois parties : le préfixe (optionnel), la commande, et les paramètre de la commande (il peut y en avoir jusqu'à 15). Le préfixe, la commande, et tous les paramètres sont séparés par un (ou plusieurs) caractère(s) ASCII espace (0x20).
	Les messages IRC sont toujours des lignes de caractères terminés par une paire CR-LF (retour chariot - saut de ligne), et ces messages ne doivent pas dépasser 512 caractères de long, en comptant tous les caractères y compris le CR-LF final.





==================
QUESTIONS (BETES?)
==================

gerer les modes pour les channels?

sujet:
Utiliser votre client de référence avec votre serveur devra être similaire à l’utiliser
avec un serveur IRC officiel. Cependant, seules les fonctionnalités suivantes sont
obligatoires :
	◦ Vous devez pouvoir vous authentifier, définir un nickname, un username, rejoindre un channel, envoyer et recevoir des messages privés, avec votre client
	de référence.
	◦ Tous les messages envoyés par un client dans un channel doivent être transmis
	à tous les clients ayant rejoint ce channel.
	◦ Vous devez avoir des operators et des utilisateurs basiques.
	◦ Vous devez donc implémenter les commandes spécifiques aux operators.



===================
DIFFERENTES CLASSES
===================

	- user:
		std::string         username
		std::string         nickname
		vector<channel>     channels
		bool                operator

	- channel:
		std::string         name
		vector<std::string> users

	- server:
		std::string         password
		int                 port    (utile?)
		autres infos a save
		vector<channel>     channels
		map<int, user>




CLASSES

	- server:
		infos liees au server
		vector<channel>     channels;
		map<int, user>      users;


	- channel:
		std::string         name;
		map<int, user>      users;
		map<int, user>      operators;
		map<int, user>      ban;
		mode?

	- user:   
		std::string         username
		std::string         nickname  









==============
A FAIRE / PLAN
==============

faire fonctionner un serveur basique
(bien comprendre comment utiliser les sockets)
recuperer les infos de chaque nouveau client dans des classes adaptées
gerer les channels, mp, etc...
gerer toutes les commandes (/join, /quit, etc...)
je sais pas trop apres



gaelle:
	server

moi?
	parsing messages:
		check si commande existe
		check options
		check arguments?
		gere les modes (booleens) (user + channel)

	quelques commandes:
		a voir avec elodie

	


modes
commandes












=========================
LANCER SERVER AVEC CLIENT
=========================

dans un premier terminal : lancer le server
	- soit "make run"
	- soit "./ircserv <port> <password>"

dams un deuxieme terminal : lancer le client
	- "irssi"
	- "/set nick ejahan" 
	- "/connect 127.0.0.1 <port> <password>
	- envoyer un message?






		#########################
		# make run              #
		# nc -C localhost 6667  #
		#########################







=======
PARSING
=======

- si commande existe pas -> fait rien					->	ok
- tant que message -> vector.push.back strtok			->	ok
- '#' devant channels									->	ok
- part													->	ok
- mettre les infos dans la classe commande				->	ok
- check espaces messages -> il faut les espaces.....	->	ok
- recup client_fd dans le main							->	ok
- messages erreur										->	mouais

- list
- mode?
- add client + client_fd (dans map) a chaque nouvelle connexion de quelqu'un
- checker leaks



send message:
int n = send(client_fd, buffer, std::strlen(buffer), 0);


















KICK	->	
LIST	->	
OPER	->	ok
KILL	->	ok
QUIT	->	ok
NOTICE	->	ok
INVITE	->	ok
JOIN	->	ok
MOTD	->	ok
NAMES	->	ok
NICK	->	ok
PART	->	ok
PASS	->	ok
PRIVMSG	->	ok
TOPIC	->	ok
USER	->	ok



=================
commandes a faire
=================
user (userhost?)			->	ok?
privmsg						->	ok (operator?)
motd						->	ok (autre serveur?)
quit						->	ok?
pass						->	ok?
list
kill						->	ok?





====
LIST
====
Usage: /QUOTE LIST parameters
Where parameters is a space or comma separated list of one or more of:
 <max_users    ; Show all channels with less than max_users.
 >min_users    ; Show all channels with more than min_users.
 C<max_minutes ; Channels that exist less than max_minutes.
 C>min_minutes ; Channels that exist more than min_minutes.
 T<max_minutes ; Channels with a topic last set less than max_minutes ago.
 T>min_minutes ; Channels with a topic last set more than min_minutes ago.
 pattern       ; Channels with names matching pattern. 
 !pattern      ; Channels with names not matching pattern. 
Note: Patterns may contain * and ?. You may only give one pattern match constraint.
Example: LIST <3,>1,C<10,T>0,#a*  ; 2 users, younger than 10 min., topic set., starts with #a













===============
LISTE COMMANDES
=============== 

<>	->	obligatoire
[]	->	optionnel

INVITE	->	INVITE <nicks> <channel>
JOIN	->	JOIN <channel> [clef]
KICK	->	KICK <channel> <nicks> [reason=message]
KILL	->	KILL <nick> [message]
LIST	->	LIST [#chaine] [-min #] [-max #]	Example: LIST #chez -min 10 -max 50 
MOTD	->	MOTD [nomserver]
NAMES	->	NAMES [channel]
NICK	->	NICK <nick>
NOTICE	->	NOTICE <nick_OU_channel> <message> 
OPER	->	OPER <userid> <password> 
PART	->	PART <channel1>,[channel2],[channel3],... 
PASS	->	PASS <motdepasse>
PING	->	PING <nick_OU_channel>
PRIVMSG	->	PRIVMSG <nick_ou_channel> <message>
_		->	IRC_OP	->	PRIVMSG $<nomserver_OU_hostname> <message>
QUIT	->	QUIT [message]
TOPIC	->	TOPIC <channel> [topic=message]
<!-- USERS	->	USER [nomserver] -->
USER	->	USER <username> <hostname> <servername> <realname>

<!-- nickname - name which appears for other users
username - name you use to login, allows system to identify you
password - sequence of symbols, which allows system to match you with your username
real name - this is just additional information about you -->




=============
PAS A GERER ?
=============
- CONNECT	->	CONNECT <server_src> <port> <server_dest> 
_			->	CONNECT <server>
- MODE



==========
USER MODES
==========
a : away
i : invisible
w : wallops
r : restricted
o : operator





!INVALID
Cas d'une commande invalide: 
    * cmd: /ouhiuj
        renvoie ERR_UNKNOWNCOMMAND: "<commande> :Unknown command" 









=========
COMMANDES
=========

################################################################################################
IRC COMMANDS					#				IRC MODES
################################################################################################
								#
	INVITE						#					USER MODES:
	JOIN -						#						a : away
	KICK -						#						i : invisible
	LIST -						#						w : wallops
	NAMES -						#						r : restricted
	PART -						#						o : operator
	TOPIC -						#
	MODE						#					CHANNEL MODES:
	NICK -						#						for users
	OPER -						#							O : channel creator
	QUIT -						#							o : channel operator
	USER -						#							v : voice
	KILL -						#						for channels
	PING -						#							i : invite only
	PONG -						#							m : moderated
	PASS -						#							n : outside privmsg disabled
	PRIVMSG -					#							p : private
	NOTICE -					#							t : topic locked
	MOTD -						#							k : key locked
								#							l : user limit





================
private messages
================

#	INVITE	
If you want to ask a user to join you in another channel, use the /invite command, which will send the user a message asking them if they want to join you in the indicated channel.
		Syntaxe : /Invite <user> <channel>
		Example : /Invite john #politics
#		Syntaxe : /invite <channelname> <nickname>
#		Example : /invite #cool MEAT

#	PRIVMSG
La commande /privmsg est identique à la commande /msg.

#	MSG
La commande /msg te permet d'envoyer un message en privé à un utilisateur ou un message normal sur un channel sur lequel tu es présent ou pas (dernier cas possible uniquement si le channel n'est pas en mode +n, pas de messages extérieures).
		Syntaxe : /msg <nick | channel> <message>
		Example : /msg MEAT Allo mec !!
		Example : /msg #cool Un tit bonjour vite fait à tout le channel #cool :)

#	MSG [IRCOperator] :
cette commande peut être utilisée pour envoyer un message à tous les utilisateurs qui sont sur le même serveur, le même réseau ou qui ont le même hostname (équivalent à la commande /wall)
		Syntaxe : /msg <$ nomserveur | hostname> <message>
		Example : /msg $* Message à tous les utilisateurs de tous les serveurs
		Example : /msg $Caen.Fr.Eu.Undernet.Org Le serveur Undernet de Caen va bientôt rebooter
		Example : /msg $*.unice.fr Un tit bonjour à tous les étudiants de l'IUT de Nice :)


==================================

#	CONNECT [IRCOperator]
La commande /connect permet de connecter deux serveurs ensemble. Le serveur destination doit être défini dans le serveur source.
		Syntaxe : /connect <serveursource> <port> <serveurdestination>
		Syntaxe : /connect <serveur>
		Exemple : /connect Caen.Fr.Eu.Undernet.Org 6668 London.Uk.Eu.Undernet.Org
		Exemple : /connect Caen.Fr.Eu.Undernet.Org

#	JOIN
La commande /join te permet d'aller sur un channel. Il ne faut pas oublier le # pour un channel du réseau, le & pour un channel du serveur, ou enfin le +. De plus si le channel est protégé par une clef (mode +k), vous devez spécifier la clef après le nom du channel. Si le channel n'existe pas, un channel de ce nom sera créé et tu deviendra automatiquement opérateur.
		Syntaxe : /join <channel> [clef]
		Example : /join #cool
		Example : /join #franco_cool COOLCLEF

#	KICK -
La commande /kick te permet de virer quelqu'un du channel.
		Syntaxe : /kick <channel> <nick> [message]
		Example : /kick #cool MEAT Tu l'as cherché, t'es kické !

#	LIST -
La commande /list te permet de lister tous les channels existant sur le réseau IRC. Tu peux spécifier un nombre minimum de personnes avec -min #, ainsi qu'un nombre maximum avec -max #. De plus tu peux faire une recherche d'une certaine chaine de caractère avec #chaine : le serveur cherchera cette chaine de caractère dans les topics de tous les channels, et t'enverra une liste. Sur Undernet, ne tapes jamais /list seul. Spécifies un nombre minimum d'utilisateurs d'au moins 5 (/list -min 5), sinon tu seras déconnecté pour flood. Les channels en mode +s (secret) ne sont pas listés, et le topic des channels en mode +p (private) ne peuvent être visualisé, excepté par un IRCOperator.
		Syntaxe : /list [#chaine] [-min #] [-max #]
		Example : /list #cool -min 10 -max 50

#	NAMES
La commande /names te permet d'afficher les nicks des utilisateurs du channel spécifié. Sans channel spécifié, cela retourne tous les nicks de tous les channels. Si l'utilisateur est en invisible (mode +i) ou si le channel est secret (mode +s), tu ne pourras pas voir partiellement ou entièrement les nicks du channel.
		Syntaxe : /names [channel]
		Example : /names
		Example : /names #cool

#	PART
La commande /part te permet de partir d'un ou de plusieurs channels. Tu peux également fermer la fenêtre des channels. Contrairement à la commande /quit (qui te déconnecte de IRC), tu ne peux pas mettre de message de fin.
		Syntaxe : /part <channel1>,[channel2],[channel3],...
		Example : /part #cool,#franco_cool,#france

#	TOPIC
La commande /topic te permet de changer le topic du channel (titre d'un maximum de 80 caractères). Le topic est là pour présenter le channel, ou montrer le sujet de discussion. Si le channel est en mode +t, seule les opérateurs peuvent changer le topic. Si tu ne spécifies pas de message de topic, le serveur te retournera le topic actuel du channel spécifié.
		Syntaxe : /topic <channel> [message]
		Example : /topic #cool Bienvenue sur #COOL =)
		Example : /topic #cool

#	MODE
La commande /mode te permet de définir les modes d'un channel ou d'un utilisateur. Attention, la commande /mode est l'une des plus complexes.
-  Utilisation de /MODE sur un channel :
	+b : bannit l'utilisateur spécifié
	+i : invite only, un utilisateur doit être invité avant de pouvoir rejoindre le channel.
	+k : key protect, place un mot de passe sur le channel. Les utilisateurs doivent indiquer ce mot de passe avec /JOIN #CHANNEL PASSWORD
	+l : limite le nombre maximal d'utilisateurs dans un channel
	+m : mode modéré, seules les opérateurs et utilisateurs disposant d'un + (voiced, mode +v), peuvent parler.
	+n : no external message, un utilisateur doit être sur le channel pour parler (/MSG #CHANNEL MESSAGE ne fonctionne plus hors du channel)
	+o : donne le status opérateur à un utilisateur (ChannelOperator)
	+p : private, rend le channel privé. Le topic du channel n'est pas affiché en utilisant /LIST
	+r : registered channel, channel enregistré protégé par un robot du serveur (ConferenceRoom).
	+s : secret, le channel n'apparait pas, ni en faisant /LIST, /NAMES ou /WHO. De plus en faisant un /WHOIS sur un utilisateur du channel, ce dernier ne sera pas indiqué.
	+t : topic protection, seuls les ChannelOperator peuvent changer le topic.
	+v : voiced, donne une voix à un utilisateur du channel. Ce dernier peut parler si le channel est en mode modéré (mode +m).
		Syntaxe : /mode <channel> <+ | -> <mode> [parametres]
		Example : /mode #cool +s (le channel devient secret)
		Example : /mode #cool +o MEAT (MEAT devient opérateur sur #cool)
		Example : /mode #cool +b MEAT (MEAT est banni du channel #cool)
		Example : /mode #cool +k COOLKEY (protège le channel par le mot de passe COOLKEY)
		Example : /mode #cool +l 20 (limite le channel #cool à 20 utilisateurs)
		Example : /mode #cool +tns (le channel est en mode +t, +n et +s)
		Example : /mode #cool -sk COOLKEY (enlève le mode secret et le mot de passe)
		Example : /mode #cool +kl AUTREKEY 100 (place un mot de passe, et limite le nombre d'utilisateurs à 100)
		Example : /mode #cool +v MEAT (donne une voix à MEAT)

#	NICK
La commande /nick te permet de changer de nickname. Bien évidemment, il ne faut pas que ton nick soit pris. Ton nick ne doit pas excéder 9 caractères (en tout cas pour les serveurs respectant la spécification RFC1459. Certains serveurs de type ConferenceRoom accepte des nicks de 30 caractères). Sur certains réseaux, on peut enregistrer des nicks. Tu es à ce moment en possession d'un mot de passe, qu'il faut envoyer au serveur via la commande /pass. Evites de prendre un nick enregistré car tu peux te faire déconnecté (Killed). Enfin, Undernet n'autorise qu'un certain nombre de changement de nickname en 10 secondes, afin d'éviter le flood par changement de nick.
		Syntaxe : /nick <nick>
		Example : /nick MEAT

#	OPER
La commande /oper permet de t'authentificier au près du serveur afin que ce dernier te donne le status de IRCOperator.
		Syntaxe : /oper <userid> <password>
		Example : /oper NiKoTeEn Nicop

#	QUIT
La commande /quit te permet de quitter IRC. Tu peux, de plus, laisser un message expliquant la raison de ton départ, ou tout autre message. Tous les utilisateurs qui sont sur les mêmes channels que toi, verront apparaitre ce message.
		Syntaxe : /quit [message]
		Example : /quit Bon allez bonne nuit !

#	USER
La commande /users te permet d'afficher pleins d'informations sur les connections des clients sur le serveur. Sans argument, les informations retournées ne concernent que le serveur sur lequel tu es connecté.
		Syntaxe : /users [nomserveur]
		Example : /users
		Example : /users Caen.Fr.Undernet.Org

#	KILL [ircOperator]
La commande /kill te permet de virer quelqu'un du serveur (Killed). L'utilisateur est déconnecté du serveur.
		Syntaxe : /kill <nick> [message]
		Example : /kill T}{emis Bots are not allowed in this server.

#	PASS
La commande /pass te permet d'indiquer le mot de passe de ton nickname au serveur. En effet, certains réseaux autorisent l'enregistrement de nickname, protégé par mot de passe. Si c'est toi qui as enregistré le nickname que tu utilises, utilises la commande /pass, sinon change de nickname via la commande /nick (sinon tu seras déconnecté du réseau au bout de quelques secondes, Killed).
		Syntaxe : /pass <motdepasse>
		Example : /pass COOLPASSWORD

#	NOTICE
La commande /notice te permet d'envoyer un message à un utilisateur ou sur un channel. Cette commande est généralement utilisée pour des messages importants car le message s'affiche en couleur et sur la fenêtre active du client. Elle peut-être réservée, sur certains channels, aux opérateurs.
		Syntaxe : /notice <nick | channel> <message>
		Example : /notice MEAT Heuuuu t'es mort ?
		Example : /notice #france L'utilisation des notices est exclusivement réservée aux opérateurs. Merci :)

#	MOTD
La commande /motd te permet d'afficher le Message Of The Day d'un serveur (Message du jour, informations sur le serveur), pas défaut le serveur sur lequel tu es connecté.
		Syntaxe : /motd [nomserveur]
		Exemple : /motd
		Exemple : /motd Caen.Fr.Eu.Undernet.Org

#	PING
ping un serveur (pas un nick)
https://www.livinginternet.com/r/ra_ping.htm
		Syntaxe : /ping <addresse serveur> 








=========
QUESTIONS
=========
- comment le client sait si le message est un message prive ou dans un channel?
- repartition travail (commandes, modes, parsing...)
- choisir quelles commandes on implemente
- nc ou irssi pour la correction?
- client qui gere l'affichage channel/messages prives automatiquement?





























!INVALID
Cas d'une commande invalide: 
    * cmd: /ouhiuj
        renvoie ERR_UNKNOWNCOMMAND: "<commande> :Unknown command" 


!NICK


!JOIN
    * cmd: /join
            - ERR_NEEDMOREPARAM: "<commande> : Not enough parameters" 


!PART
* Case 1 : pas de channel précisé:
    cmd: /part <arg manquant>
        message affiché dans le home: ERR_NEEDMOREPARAMS: <command> :Not enough parameters


!LIST
je sais pas 


!NAMES
/MOTD
/PASS
/KILL
/USER
/PING


!/INVITE
 * Il manque des paramètres:
        cmd: /invite
        home: ERR_NEEDMOREPARAMS: <command> :Not enough parameters given

/KICK : [<channel>] <nicks> [<reason>]
cmd: /kick
    ERR_NEEDMOREPARAMS : <command> :Not enough parameters given
cmd: /kick <username>



/TOPIC
Case 1 : Consulter le topic du channel : 
 * l'utilisateur écrit juste topic sur son home :
        cmd: /topic
        ERR_NEEDMOREPARAMS : <command> :Not enough parameters given


== /NOTICE
== /OPER
== /PRIVMSG

/QUIT























































// la commande KILL ferme la connection entre un client donne et le serveur auquel il est connecte 
// KILL est utilisable que par les operators 
// le message est envoye a tous les users y compris celui qui est KILL

// quand la commande KILL est utilisee, le client KILL recoit le KILL message et la <source> du message doit etre 
// l operator qui a fait la commande. tous les users qui partagent un channel avec lui recoivent un  message QUIT pour
// dire qu il a quitte le server. la <raison> de ce message QUIT a la forme : "Killed (<killer> (<reason>))" ou killer 
// est le nickname du killer. le user kill recoit le message ERROR, "Closing Link: <servername> (Killed (<killer> (<reason>)))"
// apres ca, la connection est close

















////////////////////////////////////////////////////////////
//					TEST search_channel					  //
////////////////////////////////////////////////////////////

	// std::vector<std::string>	vect_test;

	// vect_test.push_back("test");
	// vect_test.push_back("a");
	// vect_test.push_back("b");
	// vect_test.push_back("c");

	// std::vector<std::string>::iterator	it = vect.begin() + 1;
	// std::string test = *it;

	// if (search_channel(test, vect_test) == 0)
	// 	std::cout << "Unknow channel" << std::endl;

////////////////////////////////////////////////////////////





// #include "./includes/Parsing.hpp"

// int main(int ac, char **av)
// {
// 	Server ircServ;
// 	int	client_fd = 0;

// 	if (ac == 2)
// 		parsing(av[1], &ircServ, client_fd);
// 	return (0);
// }



















// std::string	join_message(std::string buffer, int i, std::vector<std::string> vect)

	// (void)vect;
	// std::string	trim = buffer;
	// std::istringstream iss(trim);
	// std::string token;

	// while (i > 0 && std::getline(iss, token, ' '))
	// 	i--;
	// std::getline(iss, token, '\r');
	// trim.erase(trim.find_first_not_of(" "));

	// size_t j = 0;
	// while (token[j] == ' ')
	// 	j++;
	// token = token.substr(j);


	//////////////////////////////////
	//		 	    TEST 			//
	//////////////////////////////////














