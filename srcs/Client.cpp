/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:19:27 by njard             #+#    #+#             */
/*   Updated: 2025/12/03 12:09:23 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.h"

Client::Client(int fdclient, Server &server) : chanel(NULL), server(server),fd(fdclient), configured(0), authenticated(0) {}

Client::~Client() {}

bool Client::getConfigured() const
{
	return this->configured;
}

bool Client::getAuthenticated() const
{
	return this->authenticated;
}

Server& Client::getServer() const
{
	return this->server;
}

void Client::authentication(std::string& commands)
{
	if (count_words(commands) != 2)
	{
		std::cerr << "Not enough words" << std::endl;
		return ;
	}
	std::string onlycommand = get_word(commands, 1);
	std::cout << "command : "  << onlycommand << std::endl;
	if (onlycommand != "PASS")
	{
		std::cerr << "Pas pass" << std::endl;
		return ;
	}
	else
	{
		std::string passwords = get_word(commands, 2);
		std::cout << "|" << passwords << "|" << std::endl;
		if (passwords == this->getServer().getPassword())
		{
			this->authenticated = 1;
			return ;
		}
		else
		{
			char buf[] = "Wrong pswd\n";
			send(this->fd, buf, strlen(buf),0);
		}
	}
	return ;
}

void Client::configure(std::string& commands)
{
	int words = count_words(commands);
	std::cout << "Words : " << words << std::endl;
	if (words < 2)
	{
		std::cerr << "Not enough words :(" << std::endl;
		return ;
	}
	std::string command = get_word(commands, 1);
	if (command == "NICK")
	{
		this->nickname = get_word(commands,2);
	}
	else if (command == "USER" && words >= 5)
	{
		std::string usernametemp = get_word(commands, 2);
		std::string mode = get_word(commands, 3);
		if (isstrdigit(mode) == false)
		{
			std::cerr << "Mode has to be a number" << std::endl;
			return ;
		}
		std::string realnametemp;
		int i = 5;
		while(i < words)
		{
			realnametemp += get_word(commands, i);
			i++;
		}
		if (realnametemp[0] != ':' || std::isspace(realnametemp[1]))
		{
			std::cerr << "Missing ':'" << std::endl;
			return ;
		}
		realnametemp.erase(0, 1); 
		if (usernameExist(this->server, usernametemp) == false)
		{
			this->username = usernametemp;
			this->realname = realnametemp;
		}
	}
	else
	{
		std::cerr << "Need NICK or USER" << std::endl;
	}
	if (!this->nickname.empty() && !this->username.empty())
	{
		this->configured = true;
	}
	return ;
}

void Client::JoinChanel(std::string& chanelname)
{
	Chanel newChanel(chanelname);
	this->getServer().getChanels().push_back(newChanel);
	this->chanel = &newChanel;
	return ;
}

bool usernameExist(Server& server, std::string& username)
{
	std::vector<std::string> usernames = server.getUsernames();
	std::vector<std::string>::iterator it = std::find(usernames.begin(),usernames.end(), username);
	if (it == usernames.end())
		return false;
	return true;
}