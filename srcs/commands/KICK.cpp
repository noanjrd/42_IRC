/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:15:17 by njard             #+#    #+#             */
/*   Updated: 2026/02/12 14:23:44 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// KICK <#channel> <user> [<reason>]

void KICK(Client& client, std::string& commands)
{
	int words = count_words(commands);
	if (words < 3)
	{
		std::string error = ":server 461 " + client.getNickname() + " KICK :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}

	std::string channel = get_word(commands, 2);
	if (channel.empty() || channel[0] != '#')
	{
		std::string error = ":server 403 " + client.getNickname() + " " + channel + " :No such channel\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	channel = channel.substr(1);
	
	std::string username = get_word(commands, 3);
	if (username.empty())
	{
		std::string error = ":server 461 " + client.getNickname() + " KICK :Not enough parameters\r\n";
		send(client.getFd(), error.c_str(), error.size(), 0);
		return ;
	}
	
	std::string reason;
	size_t pos = commands.find(':');
	if (pos != std::string::npos)
		reason = commands.substr(pos + 1);
	else
		reason = "No reason";
	reason.erase(std::remove(reason.begin(), reason.end(), '\n'), reason.end());
	reason.erase(std::remove(reason.begin(), reason.end(), '\r'), reason.end());
	if (reason.empty())
		reason = "No reason";

	std::vector<Chanel*>& allChannels = client.getServer().getChanels();
	for (size_t i = 0; i < allChannels.size(); i++)
	{
		if (allChannels[i]->getName() == channel)
		{
			if (allChannels[i]->isUserInChanel(client) == false)
			{
				std::string error = ":server 442 " + client.getNickname() + " #" + channel + " :You're not on that channel\r\n";
				send(client.getFd(), error.c_str(), error.size(), 0);
				return ;
			}
			if (allChannels[i]->isUserOperator(client) == false)
			{
				std::string error = ":server 482 " + client.getNickname() + " #" + channel + " :You're not channel operator\r\n";
				send(client.getFd(), error.c_str(), error.size(), 0);
				return ;
			}
		
			std::vector<std::pair<Client*, int> >& clientsInChannel = allChannels[i]->getClients();
			for (size_t j = 0; j < clientsInChannel.size(); j++)
			{
				if (clientsInChannel[j].first->getNickname() == username)
				{
					std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " KICK #" + channel + " " + username + " :" + reason + "\r\n";
					allChannels[i]->sendMessageToAllQuit(client, finalMessage);
					send(clientsInChannel[j].first->getFd(), finalMessage.c_str(), finalMessage.size(), 0);
					allChannels[i]->removeClient(*(clientsInChannel[j].first));
					if (allChannels[i]->getClients().empty())
						client.getServer().removeChannel(allChannels[i]);
					return ;
				}
			}	
			std::string error = ":server 441 " + client.getNickname() + " " + username + " #" + channel + " :They aren't on that channel\r\n";
			send(client.getFd(), error.c_str(), error.size(), 0);
			return ;
		}
	}
	std::string error = ":server 403 " + client.getNickname() + " #" + channel + " :No such channel\r\n";
	send(client.getFd(), error.c_str(), error.size(), 0);
}