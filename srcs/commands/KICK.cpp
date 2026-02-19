/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:15:17 by njard             #+#    #+#             */
/*   Updated: 2026/02/18 15:42:38 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// KICK <#channel> <user> [reason]

void KICK(Client& client, std::vector<std::string>& commands)
{
	int countWords = commands.size();
	if (countWords < 3)
	{
		std::string error = ":server 461 " + client.getNickname() + " KICK :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}

	std::string channelName = commands[1];
	if (channelName[0] != '#')
	{
		std::string error = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	channelName = channelName.substr(1);
	
	std::string nickname = commands[2];
	if (nickname.empty())
	{
		std::string error = ":server 461 " + client.getNickname() + " KICK :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	
	std::string reason;
	if (countWords > 3)
	{
		for (int i = 3; i < countWords; i++)
			reason +=  " " + commands[i];
		reason = reason.substr(2);	
	}
	else
		reason = "No reason";
	reason.erase(std::remove(reason.begin(), reason.end(), '\n'), reason.end());
	reason.erase(std::remove(reason.begin(), reason.end(), '\r'), reason.end());

	std::vector<Chanel*>& allChannels = client.getServer().getChanels();
	for (size_t i = 0; i < allChannels.size(); i++)
	{
		if (allChannels[i]->getName() == channelName)
		{
			if (allChannels[i]->isUserInChanel(client) == false)
			{
				std::string error = ":server 442 " + client.getNickname() + " #" + channelName + " :You're not on that channel\r\n";
				send(client.getFd(), error.c_str(), error.size(), 0);
				return ;
			}
			if (allChannels[i]->isUserOperator(client) == false)
			{
				std::string error = ":server 482 " + client.getNickname() + " #" + channelName + " :You're not channel operator\r\n";
				send(client.getFd(), error.c_str(), error.size(), 0);
				return ;
			}
		
			std::vector<std::pair<Client*, int> >& clientsInChannel = allChannels[i]->getClients();
			for (size_t j = 0; j < clientsInChannel.size(); j++)
			{
				if (clientsInChannel[j].first->getNickname() == nickname)
				{
					std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " KICK #" + channelName + " " + nickname + " :" + reason + "\r\n";
					allChannels[i]->sendMessageToAll(client, false,finalMessage);
					allChannels[i]->removeClient(*(clientsInChannel[j].first));
					if (allChannels[i]->getClients().empty())
						client.getServer().removeChannel(allChannels[i]);
					return ;
				}
			}	
			std::string error = ":server 441 " + client.getNickname() + " " + nickname + " #" + channelName + " :They aren't on that channel\r\n";
			send(client.getFd(), error.c_str(), error.size(), 0);
			return ;
		}
	}
	std::string error = ":server 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
	send(client.getFd(), error.c_str(), error.size(), 0);
}