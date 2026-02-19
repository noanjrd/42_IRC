/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:15:42 by njard             #+#    #+#             */
/*   Updated: 2026/02/19 17:10:57 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// PRIVMSG <user or channel> <message>

static void PRIVMSGToServer(Client &client, std::string& destination, std::string& message )
{
	destination = destination.substr(1);
	Chanel *channel = strChanneltoChannelType(client.getServer(), destination);
	if (channel == NULL)
	{
		std::string error = ":server 403 " + client.getNickname() + " #" + destination + " :No such channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	if (channel->isUserInChanel(client) == false)
	{
		std::string error = ":server 404 " + client.getNickname() + " #" + destination + " :Cannot send to channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	std::string entireMessage = ":" +  client.getNickname() + "!" + client.getUsername()+"@localhost PRIVMSG "  + channel->getName() + " :" + message + "\r\n"; 
	channel->sendMessageToAll(client,false, entireMessage);
}

static void PRIVMSGtoClient(Client &client, std::vector<std::string>& commands, std::string& destination, std::string& message)
{
	Client* receiver = client.getServer().getClientByNick(destination);
	if (receiver == NULL)
	{
		std::string error = ":server 401 " + client.getNickname() + " " + destination + " :No such nick/channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	// std::cout << "cmd 2 : [" << commands[2] << "]" << std::endl;
	// std::cout << "cmd 2 length: " << commands[2].length() << std::endl;
	// std::cout << "Expected length: " << std::string(":" + "\x01" + "DCC").length() << std::endl;
    std::string dccStart = ":";
    dccStart += '\x01';  // \x01 c ets le caractere 1 de la table ascii
    dccStart += "DCC";
	if (commands[2] == dccStart && commands[3] == "SEND" 
		&& commands.size() >= 8)
	{
		std::string fileName = commands[4];
		std::string ipAdress = commands[5];
		std::string port = commands[6];
		std::string size = commands[7];
		std::cout << "ca a marche" << std::endl;
		if (size.empty() || size[size.length() - 1] != '\x01')
		{
			std::cerr << "Error size format: missing terminating \\x01" << std::endl;
			return ;
		}
		size = size.substr(0, size.length()-1);
		int socketTemp = socket(AF_INET,SOCK_STREAM,0);
		struct sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(atoi(port.c_str()));
		bind(socketTemp, (struct sockaddr*)&address, sizeof(address));
		listen(socketTemp, 2);
	}
	std::string message_formatted = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost PRIVMSG " + receiver->getNickname() + " :"+ message + "\r\n";
	send(receiver->getFd(),message_formatted.c_str(),message_formatted.size(),0);
}

void PRIVMSG(Client &client, std::vector<std::string>& commands)
{
	std::cout << "coucou" << std::endl;
	int countWords = commands.size();
	if (countWords < 3)
	{
		std::string error = ":server 461 " + client.getNickname() + " PRIVMSG :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	int i = 2;
	std::string message;
	while (i < countWords)
	{
		message+= " " + commands[i];
		i++;
	}
	if (message[1] != ':')
	{
		std::cerr << "Error syntax message" << std::endl; // chck si c ets le bon message
		return ;
	}
	message = message.substr(2);
	std::string destination = commands[1];
	if (destination[0] == '#')
		return PRIVMSGToServer(client, destination, message);
	else
	{
		return PRIVMSGtoClient(client, commands, destination, message);
	}
}