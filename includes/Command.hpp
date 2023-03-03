/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 02:37:53 by ejahan            #+#    #+#             */
/*   Updated: 2023/02/08 07:06:08 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "./Include.hpp"
#include "./Server.hpp"

class	Command
{
	private:

		std::vector<std::string>	channels;
		std::vector<std::string>	nick;
		std::vector<std::string>	server;
		std::vector<std::string>	message;
		int							client_fd;

	public:

		Command();
		~Command();
		Command(Command const &src);

		std::vector<std::string>	getChannels();
    	std::vector<std::string>	getNickname();
    	std::vector<std::string>	getServer();
    	std::vector<std::string>	getMessage();
		int							getClientSfd();

		int							get_size_channels();
		int							get_size_nick();
		int							get_size_server();
		int							get_size_message();

		void					 	add_channels(std::string channel);
		void					 	add_nick(std::string nick);
		void					 	add_server(std::string server);
		void					 	add_message(std::string message);
        void					 	add_client_fd(int client_fd);

		void					 	print_channels();
		void					 	print_nick();
		void					 	print_server();
		void					 	print_message();
		void					 	print_all();
};

#endif
