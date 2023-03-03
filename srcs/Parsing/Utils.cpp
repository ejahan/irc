#include "../../includes/Parsing.hpp"

void	printVector(std::vector<std::string> vect)
{
	std::vector<std::string>::iterator	it = vect.begin();
	std::vector<std::string>::iterator	ite = vect.end();

	std::cout << RED << "_________________________" << RESET << std::endl;
	while (it != ite)
	{
		std::cout << "[" << *it << "]" << std::endl;
		it++;
	}
}

void	printMap(std::map<int, User*> map)
{
	std::map<int, User*>::iterator	it = map.begin();
	std::map<int, User*>::iterator	ite = map.end();

	std::cout << RED << "====================================================" << RESET << std::endl;
	while (it != ite)
	{
		std::cout << it->first << "	|	" << *it->second << std::endl;
		it++;
	}
}

void	printMapParsing(std::map<int, User> map)
{
	std::map<int, User>::iterator	it = map.begin();
	std::map<int, User>::iterator	ite = map.end();

	std::cout << RED << "====================================================" << RESET << std::endl;
	while (it != ite)
	{
		std::cout << it->first << "	|	" << it->second << std::endl;
		it++;
	}
}

std::string	joinMessage(std::string buffer)
{
	std::string	token = buffer;
	token = token.substr(token.find(':') + 1);

	return (token);
}

int	checkChannel(int i, std::vector<std::string> vect)
{
	std::vector<std::string>::iterator	it = (vect.begin() + i);
	std::string							str = *it;

	if (str[0] != '#')
		return (1);
	return (0);
}

void	sendMsgChannel(std::map<int, User*> channel, std::string message)
{
	std::map<int, User *>::iterator	it = channel.begin();
	std::map<int, User *>::iterator	ite = channel.end();

	int	fd;
	while (it != ite)
	{
		fd = it->first;
		sendMessage(fd, message);
		it++;
	}
}

void	sendMsgChannelQuit(std::map<int, User*> channel, std::string message, std::string name, std::string hostname)
{
	std::map<int, User *>::iterator	it = channel.begin();
	std::map<int, User *>::iterator	ite = channel.end();

	int	fd;
	while (it != ite)
	{
		fd = it->first;
		std::string	msg = PRIVMSG(hostname, name, message);
		sendMessage(fd, message);
		it++;
	}
}

void	sendMessage(int fd, std::string msg)
{
	msg += "\r\n";
	std::cout << msg << std::endl;
	send(fd, msg.c_str(), msg.size(), 0);
}

void	sendMessageNick(int fd, std::string nick, std::string begin, std::string end)
{
	begin += nick;
	begin += end;
	begin += "\r\n";
	send(fd, begin.c_str(), begin.size(), 0);
}

std::string itoa(int a)
{
    std::string	ss = "";

    while(a)
    {
        int	x = a % 10;
        a /= 10;
		char c = static_cast<char>('0');
        c += x;
        ss += c;
    }
    return ss;
}

std::string lowerCase(std::string str)
{
    std::string		ret;
    
	ret.reserve(str.size());

    for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
        ret.push_back(static_cast<char>(std::tolower(*it)));
    }

    return (ret);
}
