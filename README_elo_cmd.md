****************
SHORTCUTS IRSSI:
****************
Se balader entre les differents channels et le "home":
* ctrl + n
* ctrl + p
* Alt + 1 (home), Alt + 2 (chan1), Alt + 3 (chan2) ...


******************************************************
TESTER LA VALIDITE DES MESSAGES SERVEUR POUR LE CLIENT
******************************************************

* Ouvrir un terminal et utiliser netcat comme port d'écoute pour IRSSI:
cmd: nc -l (listen) <port>

* ouvrir un terminal et lancer IRSSI:
cmd: irssi

* connecter IRSSI à netcat, saisir dans IRSSI : 
cmd: /connect localhost <port>

Maintenant on peut envoyer des messages à IRSSI avec netcat pour voir si les messages
sont bien formatés si IRSSI renvoie la bonne info.
Et aussi comprendre ce que les messages serveur provoquent comme message a IRSSI si la requete est correcte.

*********
IRC MODES
*********

    USER MODES:
        a : away
        i : invisible
        w : wallops
        r : restricted
        o : operator
    
    CHANNEL MODES:
        for users
            O : channel creator
            o : channel operator
            v : voice
        for channels
            i : invite only
            m : moderated
            n : outside privmsg disabled
            p : private
            t : topic locked
            k : key locked
            l : user limit
            s : secret


*******************************
!DROITS DES CHANNEL OPERATEURS:
*******************************
- /MODE : définir les modes du channel
- /INVITE : inviter quelqu'un lorsque le mode +i (invite) est activé
- /KICK : virer un utilisateur du channel
- / : bannir un utilisateur
- /TOPIC : changer ou créer un sujet de topic pour le channel, uniquement droit opérateur si mode +t est activé.


*************************
!DROITS OPERATEUR SERVEUR
*************************
- /KILL : déconnecter quelqu'un du serveur
- /MODE +o name: se mettre en opérateur de n'importe quel channel
- /DIE : déconnecter le serveur


*********************
!FORMAT DES MESSAGES:
*********************
- 512 caractères maximum par message, incluant le délimiteur "\r\n". 
- tout message de plus de 510 caractères (sans compter le délimiteur) sera tronqué, les deux derniers caractères étant remplacés par "\r\n", conforme aux spec RFC.


*********
COMMANDES
*********
!! = obligatoire
>> = optionnel
?? = très optionnel?


!! /KILL
!! /DIE
>> /ADMIN
>> /USERS
>> /ISON
>> /INFO
>> /USERHOST
>> /LUSERS
>> /TIME
>> /VERSION
>> /WALLOPS
>> /WHO
>> /WHOIS
>> /WHOWAS
>> /HELP
>> /OP
?? /CAP
?? /REHASH
?? /STATS
?? /SUMMON
?? /KNOCK


!!CONNECT
* D'abord lancer le serveur:
    ./server <port> <password>
* Commande irssi pour se connecter au serveur: 
    /connect <server> <port> <password>
    exemple : /connect 127.0.0.1 6667 password


!!JOIN
* joindre un channel: 
    * cmd: /join
            - ERR_NEEDMOREPARAM: "<commande> : Not enough parameters" 
    * cmd: /join #<channel_name> [optionnel: <password>]
        * Case 1: Flow si le channel existe. 
            - parcourir le channel et verifier s'il existe
            - si le channel est full : 
                - ERR_CHANNELISFULL: "<canal> :Cannot join channel (+l) (You must be invited)"
            - si le nb max de channels est atteind pour l'user :
                - ERR_TOOMANYCHANNELS: "<nom de canal> :You have joined too many channels" 
            - s'il est banni du chan: 
                - ERR_BANNEDFROMCHAN "<canal> :Cannot join channel (+b)"
            - s'il est pas invité et que le chan est en mode invite : 
                - ERR_INVITEONLYCHAN: "<canal> :Cannot join channel (+i)" 
            - si password requis : 
                - password manquant : ERROR ci dessous.
                - password faux ou manquant : 
                    ERR_BADCHANNELKEY "<canal> :Cannot join channel (+k)" 
                - password OK :
                    - un message informe les users du chan de cette venue:
                    - Le serveur ajoute l'utilisateur au channel
                    - L'utilisateur reçoit le sujet du topic ... RPL_TOPIC
                    - ... ainsi que la liste des users sur le canal RPL_NAMREPLY
        * Case 2: Flow si le channel n'existe pas:
            - Parcourir les channels et vérifier s'il existe
            - si le nb max de channels est atteind pour l'user : 
                ERR_TOOMANYCHANNELS: "<nom de canal> :You have joined too many channels" 
            - création du channel : "channel <channel_name> created + Wed Jan 11 06:29:51 2023 [format date]"
            - Le serveur crée le channel
            - Le serveur ajoute l'utilisateur au channel
            - L'user est operateur
    * cmd: /join 0 (optionnel, ne fonctionne pas sur irc.geekshed.net)
        L'utilisateur quitte tous les channels sur lesquels il est actif


!!PART
* Case 1 : pas de channel précisé:
    cmd: /part <arg manquant>
        message affiché dans le home: ERR_NEEDMOREPARAMS: <command> :Not enough parameters
* channel précisé:
    cmd: /part <channel>
    * Case 2 : pas de channel de ce nom trouvé:
        ERR_NOSUCHCHANNEL: <channel name> :No such channel
    * Case 3 : le channel existe mais l'user n'est pas sur le chan
        ERR_NOTONCHANNEL: <channel> :You're not on that channel
    * Case 4 : le channel existe et l'utilisateur est dessus:
        - L'user est supprimé du channel.
        - Un message informe les users du chan que user a quitté le chan: <nickname> has left #<channel>
        - si il n'y a plus d'utilisateur dans ce channel, le channel est supprimé.


!!NICK
* Case 1: Pas de pseudo: 
  cmd: /nick <arg manquant>
        * msg affiché dans le home: "Your nickname is <nickname>"
* avec argument
  cmd: /nick <nouveau pseudo>
        * Case 2: Le pseudo existe déjà: 
            ERR_NICKNAMEINUSE : "Nickname is already in use".
        * Le pseudo n'existe pas:
            * Case 3: format correct:  
                - remplacer le pseudo de l'user
                - home: You are known as <nouveau nickname>
                - Afficher un message dans tous les channels de l'user pour alerter les participants du changement de nom.
            * Case 4: mauvais format:
                home: ERR_ERRONEUSNICKNAME : "<pseudo> :Erroneus nickname. Illegal character."
                Le format est mauvais : (verifier ces regles, pas plus de 9 chars, éviter les délimiteurs comme les ",", certains char speciaux et chiffres, 1er char doit etre une lettre)


/TOPIC
Case 1 : Consulter le topic du channel : 
 * l'utilisateur écrit juste topic sur son home :
        cmd: /topic
        ERR_NEEDMOREPARAMS : <command> :Not enough parameters given
 * l'utilisateur écrit /topic sur le chan : 
        cmd: /topic OU /topic #<channel_actif> 
        - pas de topic assigné :
            RPL_NOTOPIC : No topic set for #<channel>
        - topic assigné :
            RPL_TOPIC : topic for <channel> : <topic>
        - le channel n'existe pas : 
            home: ERRNOSUCHCHANNEL : "#<channel>: No such channel"

    Les messages RPL s'affichent dans le channel.
    Si l'user n'est pas dans le chan, il peut afficher les RPL dans le home en précisant le nom du chan.
    Sinon, meme si l'user est sur le home, s'il est dans le chan, les messages s'affichent sur le chan concerné et pas dans le home.

Case 2 : Créer ou modifier un sujet de topic : 
    cmd: /topic <sujet_du_topic> OU /topic #<channel_actif> <sujet_du_topic>
        *l'user n'est pas opérateur et le mode +t est activé:
            home: ERR_CHANOPRIVSNEEDED: "#<channel> "You're not the channel operator"
        *le channel n'existe pas : 
            home: ERRNOSUCHCHANNEL : "#<channel>: No such channel"
        *le channel existe et l'user a les droits:
            Le message suivant est envoyé sur le channel concerné à tous ses 
            utilisateurs : <username> changed the topic of #<channel> to: <topic subject>


!!LIST
* case 1: afficher la liste des channels visibles existants ainsi que leur topics: 
    cmd : /list
    format : #<channel> <visibles_users_nb> <[permissions du chan] ex: [+ntS] par defaut> <topic (sujet du chan si défini)>
* Case 2: afficher les channels selectionnés ainsi que leur topics
    cmd: /list #chan1 #chan2 ...
renvoie RPL_LIST: "<client> <channel> <client count> :<topic>"
renvoie RPL_LISTEND: "End of /LIST"
* mettre une condition: si le channel est en mode secret, il ne doit pas apparaitre dans la liste.


!!NAMES
* cmd: /names
    * L'utilisateur est dans un chan:
    liste tous les users visibles dans le channel si le user est dans le channel
        ex d'affichage sur le chan :
        RPL_NAMREPLY :
        [Users #<channel>]
        [@fifi] [loulou] 
        -!- Irssi: <channel>: Total of 2 nicks [1 ops, 0 halfops, 0 voices, 1 normal]
        RPL_ENDOFNAMES;
    * l'utilisateur n'est pas dans un chan :
        home: ERR_?? : Not joined any channel.
* cmd: /names #<channel_name> #<channel_name_2> ...
        liste tous les users visibles du channel concerné dans le chan concerné, meme si on est sur le home.
* mettre une condition: 


<!-- +m : mode modéré, seules les opérateurs et utilisateurs disposant d'un + (voiced, mode +v), peuvent parler.
!!/MODE
SEUL LE CHANNEL OPERATOR A LE DROIT DE CHANGER LE MODE DU CHAN
 Utilisation de /MODE sur un channel :
+i : invite only, un utilisateur doit être invité avant de pouvoir rejoindre le channel.
+s : secret mode
+p : private, rend le channel privé. Le topic du channel n'est pas affiché en utilisant /LIST
+t : topic
+k : key protect, place un mot de passe sur le channel. Les utilisateurs doivent indiquer ce mot de passe avec /JOIN #CHANNEL PASSWORD

+l : limite le nombre maximal d'utilisateurs dans un channel
+b : bannit l'utilisateur spécifié
+o : donne le status opérateur à un utilisateur (ChannelOperator)

<!-- +v : voiced, donne une voix à un utilisateur du channel. Ce dernier peut parler si le channel est en mode modéré (mode +m).******* -->

*****+s : secret, le channel n'apparait pas, ni en faisant /LIST, /NAMES ou /WHO. De plus en faisant un /WHOIS sur un utilisateur du channel, ce dernier ne sera pas indiqué.******
*******+t : topic protection, seuls les ChannelOperator peuvent changer le topic.

Syntaxe : /mode <channel> <+ | -> <mode> [parametres]
Example : /mode #cool +s (le channel devient secret)

Example : /mode #cool +o MEAT (MEAT devient opérateur sur #cool)
Example : /mode #cool +b MEAT (MEAT est banni du channel #cool)
Example : /mode #cool +k COOLKEY (protège le channel par le mot de passe COOLKEY)
Example : /mode #cool +l 20 (limite le channel #cool à 20 utilisateurs)

Example : /mode #cool +tns (le channel est en mode +t, +n et +s)
Example : /mode #cool -sk COOLKEY (enlève le mode secret et le mot de passe)
Example : /mode #cool +kl AUTREKEY 100 (place un mot de passe, et limite le nombre d'utilisateurs à 100)

Example:
/mode -st : on enlève le chan secret, on enleve le topic que pour les op
Lorsqu'un mode est défini, un message s'affiche dans le chan : 
mode/#<channel> [-s] by <nickname>
mode/#<channel> [-t] by <nickname>

ERR_NEEDMOREPARAMS              ERR_KEYSET
           ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
           ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
           RPL_CHANNELMODEIS
           RPL_BANLIST                     RPL_ENDOFBANLIST
           RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
           RPL_INVITELIST                  RPL_ENDOFINVITELIST
           RPL_UNIQOPIS


!!/MOTD
* cmd: motd 
- Affiche le message d'accueil du serveur IRC à son exécution.
- Revoir END_OF_MOTD : "end of MOTD command"


!!/USER
Le message USER est utilisé au début de la connexion pour spécifier le nom d'utilisateur, le nom d'hôte, le nom de serveur et le nom réel du nouvel utilisateur. Il est également utilisé dans la communication entre les serveurs pour indiquer un nouvel utilisateur arrivant sur IRC, car l'utilisateur est seulement enregistré après que USER et NICK aient été reçu d'un client.


!!/PING
* pas assez d'argument:
    cmd: /ping 
    ERR_NEEDMOREPARAMS: <command> :Not enough parameters
* nickname inexistant : 
    cmd: /ping <nickname>
* commande correcte : 
    cmd: /ping <nickname>
Permet à un client de demander un PING au serveur pour tester la présence d'un client actif à l'autre extrémité de la connection. 
Le message ping est envoyé à intervalles réguliers si aucune autre activité n'a été détectée. Si une connexion ne répond pas à PING avec PONG dans un délai défini de temps, la connexion est fermée. 
Le client qui reçoit un PING doit obligatoirement répondre au serveur qui a envoyé le message PING jusqu'à lui.
    ERR_NEEDMOREPARAMS: <command> :Not enough parameters
    ERR_NOORIGIN : :No origin specified (Message PING ou PONG manquant le paramètre d'origine.)
    ERR_NOSUCHSERVER : <server name> :No such server.


!!/PONG
Le message PONG est une réponse au message ping. Si le paramètre <daemon2> est donné ce message doit être transmis au démon donné. Le <démon> le paramètre est le nom du démon qui a répondu au message PING et a généré ce message.
    ERR_NOORIGIN : :No origin specified (Message PING ou PONG manquant le paramètre d'origine.)
    ERR_NOSUCHSERVER : <server name> :No such server


!!/INVITE
 * Il manque des paramètres:
        cmd: /invite
        home: ERR_NEEDMOREPARAMS: <command> :Not enough parameters given
 * Parametres corrects mais l'user n'est pas sur ce chan:
        home: ERR_NOTONCHANNEL : "<channel> :You're not on that channel" 
 * Les paramètres corrects mais l'utilisateur n'est pas opérateur:
    - si le mode invite est activé, il reçoit ce message : 
        home: ERR_CHANOPRIVSNEEDED: <channel> You're not the channel operator
    //- sinon il peut inviter qq1 mais pas de message d'info pour les users du chan //mode -i.
 * Le nom d'user n'existe pas:
        cmd: /invite <bad_user_name>
        home: ERR_NOSUCHNICK <unknow_user>: No such nick
 * L'user est sur son home irssi, mais n'a pas précisé de channel:
        cmd: /invite <user_name>
        home: ERR_NOTONCHANNEL : "<canal> :You're not on that channel" 
 * Le channel est précisé, mais n'existe pas:
        cmd: /invite <user_name> #<channel>
        home: ERR_NOSUCHNICK: <user>: No such nick/channel
 * Tout bon mais l'utilisateur invité est déjà sur le chan :
        cmd: /invite <user_name> #<channel>
        ERR_USERONCHANNEL : <user> <channel> :is already on channel
 * Le channel n'est pas précisé, mais c'est le chan où l'user est actif.
        cmd: /invite <user_name> + prend en compte le nom du chan actif
        - l'invitant reçoit un message :home: "Inviting <user_name> to #<channel_name>."
        - l'invité reçoit un message : "<invitant> invites you to #<channel>."
        - si mode invite activé: tous les users du channel concernés sont informés de l'invitation: "<nickname> invited <user_name> into the channel."
L'invitation a court tant que le client est connecté au serveur, s'il /QUIT il est supprimé de la liste.


/KICK : [<channel>] <nicks> [<reason>]

cmd: /kick
    ERR_NEEDMOREPARAMS : <command> :Not enough parameters given
cmd: /kick <username>


!!/NOTICE
    cmd: /notice <nickname> <texte>
    /notice ne doit pas renvoyer d'erreur au client. 
    Si la commande est correcte, le message texte addressé au user dans la ligne de commande doit parvenir à l'user défini.
    

!!/OPER 
Demander les droit d'un opérateur serveur (ils peuvent KILL les users du serveur).
    *Aucun mot de passe saisi:
        cmd: /oper <user>
        ERR_NEEDMOREPARAMS: <command> :Not enough parameters given.
    *mot de passe eroné :
        cmd: /oper <user><password>
        ERR_PASSWDMISMATCH :Password incorrect
    *le serveur n'a pas été configuré pour autoriser les connexions depuis l'hôte du client en tant qu'opérateur : 
        cmd: /oper <user><password>
        ERR_NOOPERHOST :No O-lines for your host


!!/QUIT
    cmd: /quit
    - un message informe les users des chans sur lequel l'user qui quitte est :
        <nickname> has quit.
    - l'user est déconnecté et supprimé de tous les channels, ainsi que supprimé des invites
    - l'user est déconnecté du serveur car il quitte le client
