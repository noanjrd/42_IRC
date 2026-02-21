/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:29:52 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 15:25:00 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

#include "Channel.hpp"
#include "ClientConnexion.hpp"
#include "IRC.hpp"

class Client;

class Server
{
	private:
		std::vector<std::string> usernames;
		std::vector<std::string> channelsName;
		std::vector<Channel*> channels;
		std::vector<ClientConnexion*> client_connexions; // Liste des clients
		std::string password;
		int sevrer_fd;
		int port;
	public:
		Server();
		Server(int fd, int port, std::string pswd);
		~Server();

		int getFd() const;
		int getPort() const;
		std::vector<std::string>& getUsernames();
		std::vector<std::string>& getUChannelsName();
		std::vector<Channel*>& getChannels();
		std::vector<ClientConnexion*>& getClient_connexions();
		Client* getClientByNick(const std::string& nickname);
		std::string& getPassword();
		
		bool isUserInServer(Client& client);
		void removeClient(Client& client);
		bool isNicknameInServer(const std::string& nickname);
		bool isChannelExist(const std::string& channel);
		void removeChannel(Channel* channelName);
};

