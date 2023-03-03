#ifndef RPL_ANSWER_HPP

# define RPL_ANSWER_HPP

#include "Include.hpp"

#define SERVERNAME "IRCserv"

#define DATE "Fri Jan 20 08:57:00 2023"

#define AWAY_DEFAULT (":You have been marked as being away")

#define RPL_WELCOME(localhost, nick) (":" + localhost + " 001 " + nick + " :Welcome to the Internet Relay Network " + localhost + "\r\n")

#define RPL_YOURHOST(localhost) (":" + localhost + " 002 :Your host is 127.0.0.1, running version 1.00\r\n")

#define RPL_CREATED(localhost) (":" + localhost + " 003 :This server was created " DATE "\r\n")

#define RPL_MYINFO(localhost) (":" + localhost + " 004 :ircServ 1.00 aiwroOs OovaimnpsrtklbeI\r\n")

#define QUIT(localhost, msg) (localhost + " QUIT :" + msg + "\r\n")

#define PING(localhost) (std::string("PING :") + SERVER + "\r\n")

#define PONG() (std::string("PONG :") + SERVER + "\r\n")

#define NICK(localhost, nick) (":" + localhost + " NICK :" + nick + "\r\n")

#define PRIVMSG(localhost, dest, str) (":" + localhost + " PRIVMSG " + dest + " :" + str + "\r\n")

#define NOTICE(localhost, chan, str) (":" + localhost + " NOTICE " + chan + " :" + str + "\r\n")

#define PART(localhost, chan, str) (":" + localhost + " PART " + chan + " :" + str + "\r\n")

#define JOIN(localhost, chan) (":" + localhost + " JOIN " + chan + "\r\n")

#define KICK(localhost, chan, nick) (":" + localhost + " KICK " + chan + " " + nick)

#define TOPIC(localhost, chan, topic) (":" + localhost + " TOPIC " + chan + " :" + topic + "\r\n")

#define MODE(localhost, chan, str) (":" + localhost + " MODE " + chan + " " + str + "\r\n")

#define ERROR_MSG(user, reason) ("ERROR :Closing Link: <IRCserv> Killed by " + user + " :" + reason + "\r\n")

#define KILL(user, reason) ("Killed by " + user + " :" + reason + "\r\n")

#define RPL_AWAY(localhost, nick, msg) (":" + localhost + " 301 :" + nick + msg + "\r\n")

#define RPL_UNAWAY(localhost) (":" + localhost + " 305 :You are no longer marked as being away\r\n")

#define RPL_NOWAWAY(localhost) (":" + localhost + " 306 :You have been marked as being away\r\n")

#define RPL_UMODEIS(localhost, nick, mode, param) (":" + localhost + " 221 " + nick + " :+" + mode + "" + param + " \r\n")

#define RPL_WHOISUSER(localhost, nick, user, host, name) (":" + localhost + " 311 " + nick + " " + user + " " + host + " * :" + name + "\r\n")

#define RPL_WHOISSERVER(localhost, nick, server_info) (":" + localhost + " 312 " + nick + " " + SERVERNAME + " :" + server_info + "\r\n")

#define RPL_WHOISOPERATOR(localhost, nick) (":" + localhost + " 313 " + nick  + " :is an IRC operator\r\n")

#define RPL_ENDOFWHO(localhost, name) (":" + localhost + " 315 " + name + " :End of WHO list\r\n")

#define RPL_WHOISIDLE(localhost, nick, integer) (":" + localhost + " 317 " + nick + " " + integer " :seconds idle\r\n")

#define RPL_ENDOFWHOIS(localhost, nick) (":" + localhost + " 318 " + nick + " :End of WHOIS list\r\n")

#define RPL_WHOISCHANNELS(localhost, nick, channel) (":" + localhost + " 319 " + nick + " :*( ( "@" / "+" ) " + channel + " \r\n" )

#define RPL_LISTSTART(client) (":" + client + " 321 LIST Channel    :Users    Name\r\n")

#define RPL_LIST(localhost, channel, mode, topic) (":" + localhost + " 322 LIST " + channel + "      " +  mode + "        :" + topic + "\r\n")

#define RPL_LISTEND(localhost) (":" + localhost + "323 :End of LIST\r\n")

#define RPL_CHANNELMODEIS(localhost, channel, mode) (":" + localhost + " 324 " + mode + " " + channel + " :" + mode +  "\r\n")

#define RPL_NOTOPIC(localhost, channel) (":" + localhost + " 331 " + channel + " :No topic is set\r\n")

#define RPL_TOPIC(localhost, channel, topic) (":" + localhost + " 332 " + channel + " :" + topic + "\r\n")

#define RPL_INVITING(localhost, channel, nick) (":" + localhost + " 341 " + " INVITE " + nick + " " + channel + "\r\n")

#define RPL_INVITELIST(localhost, channel, invitemask) (":" + localhost + " 346 " + channel + " " + invitemask)

#define RPL_ENDOFINVITELIST(localhost, channel) (":" + localhost + " 347 " + channel + " :End of channel invite list")

#define RPL_WHOREPLY(localhost, channel, user, host, nick, name) (":" + localhost + " 352 " + channel + " " + user + " " + host + " " + SERVER + " " + nick + " : 0 " + name + "\r\n") // 352

#define RPL_NAMREPLY(localhost, channel, nick) (":" + localhost + " 353 " + nick + " = " + channel + " :" + nick + " @" + nick + "\r\n" )

#define RPL_ENDOFNAMES(localhost, nick, channel) (":" + localhost + " 366 " + nick + " " + channel + " :End of /NAMES list\r\n")

#define ERR_NOMOTD(client) (":" + client + " 422 :MOTD File is missing\r\n")

#define RPL_MOTD(localhost, text) (":" + localhost + " 372 :-" + text + "\r\n")

#define RPL_MOTDSTART(localhost) (":" + localhost + " 375 :- " + SERVERNAME + " Message of the day - \r\n")

#define RPL_ENDOFMOTD(localhost) (":" + localhost + " 376 : End of MOTD command\r\n")

#define RPL_YOUREOPER(localhost) (":" + localhost + " 381 : You are now an IRC operator\r\n")

#define ERR_NOSUCHNICK(localhost, nick, channel) (":" + localhost + " 401 " + nick + " " + channel + ": No such nick/channel\r\n")

#define ERR_NOSUCHSERVER(localhost, serv) (":" + localhost + " 402 " + serv + " :No such server\r\n")

#define ERR_NOSUCHCHANNEL(localhost, nick, channel) (":" + localhost + " 403 " + nick + " " + channel + " :No such channel\r\n")

#define ERR_CANNOTSENDTOCHAN(localhost, nick, channel) (":" + localhost + " 404 " + nick + " " + channel + " :Cannot send to channel\r\n")

#define ERR_TOOMANYCHANNELS(localhost, channel) (":" + localhost + " 405 " + channel + " :You have joined too many channels\r\n")

#define ERR_TOOMANYTARGETS(localhost, target) (":" + localhost + " 407 " + target + " :<error code> recipients. <abort message>\r\n")

#define ERR_NOORIGIN(localhost) (":" + localhost + " 409 :No origin specified")

#define ERR_NORECIPIENT(localhost, cmd) (":" + localhost + " 411 : No recipient given (" + cmd + ")\r\n")

#define ERR_NOTEXTTOSEND(localhost) (":" + localhost + " 412 :No text to send\r\n")

#define ERR_NOTOPLEVEL(localhost, mask) (":" + localhost + " 413 " + mask + " :No toplevel domain specified\r\n")

#define ERR_WILDTOPLEVEL(localhost, mask) (":" + localhost + " 414 " + mask + " :Wildcard in toplevel domain\r\n") 

#define ERR_NONICKNAMEGIVEN(localhost) (":" + localhost + " 431 :No nickname given\r\n") 

#define ERR_ERRONEUSNICKNAME(localhost, nick) (":" + localhost + " 432 " + nick + " :Erroneous nickname\r\n") 

#define ERR_NICKNAMEINUSE(localhost, nick) (":" + localhost + " 433 " + nick + " " + nick + " :Nickname is already in use\r\n")

#define ERR_NICKCOLLISION(localhost, nick, user, host) (":" + localhost + " 436 " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n") 

#define ERR_UNAVAILRESOURCE(localhost, nick_chan) (":" + localhost + " 437 " + nick_chan + " :Nick/channel is temporarily unavailable\r\n")

#define ERR_USERNOTINCHANNEL(localhost, user, nick) (":" + localhost + " 441 " + user + " " + nick + " :They aren't on that channel\r\n")

#define ERR_NOTONCHANNEL(localhost, channel) (":" + localhost + " 442 " + channel + " :You're not on that channel\r\n")

#define ERR_USERONCHANNEL(localhost, user, channel) (":" + localhost + " 443 " + user + " " + channel + " :is already on channel\r\n") 

#define ERR_NOTREGISTERED(localhost) (":" + localhost + " 451 :You have not registered\r\n")

#define ERR_NEEDMOREPARAMS(localhost, key) (":" + localhost + " 461 " + key + " :Not enough parameters\r\n")

#define ERR_ALREADYREGISTRED(localhost) (":" + localhost + " 462 :Unauthorized command (already registered)\r\n")

#define ERR_PASSWDMISMATCH(localhost, nick) (":" + localhost + " 464 " + nick + " :Password incorrect\r\n")

#define ERR_KEYSET(localhost, channel) (":" + localhost + " 467 " + channel + " :Channel key already set\r\n") 

#define ERR_CHANNELISFULL(localhost, channel) (":" + localhost + " 471 " + channel + " :Cannot join channel (+l)\r\n")

#define ERR_INVITEONLYCHAN(localhost, channel) (":" + localhost + " 473 " + channel + " :Cannot join channel (+i)\r\n")

#define ERR_BANNEDFROMCHAN(localhost, channel) (":" + localhost + " 474 " + channel + " :Cannot join channel (+b)\r\n")

#define ERR_BADCHANNELKEY(localhost, channel) (":" + localhost + " 475 " + channel + " :Cannot join channel (+k)\r\n") 

#define ERR_BADCHANMASK(localhost, channel) (":" + localhost + " 476 " + channel + " :Bad Channel Mask\r\n")

#define ERR_NOPRIVILEGES(localhost, user) (":" + localhost + "481" + user + " :Permission Denied- You're not an IRC operator\r\n")

#define ERR_CHANOPRIVSNEEDED(localhost, nick, channel) (":" + localhost + " 482 " + nick + " " + channel + " :You're not a channel operator\r\n")

#define ERR_CANTKILLSERVER(localhost) (":" + localhost + " 483 :You can't kill a server!\r\n")

#define ERR_RESTRICTED(localhost) (":" + localhost + " 484 :Your connection is restricted!\r\n")

#define ERR_NOOPERHOST(localhost) (":" + localhost + " 491 :No O-lines for your host\r\n")

#define ERR_UMODEUNKNOWNFLAG(localhost) (":" + localhost + " 501 :Unknown MODE flag\r\n")

#define ERR_USERSDONTMATCH(localhost, nick) (":" + localhost + " 502 " + nick + " :Cannot change mode for other users\r\n")

#endif
