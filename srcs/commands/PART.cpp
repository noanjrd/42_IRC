/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:45:53 by naankour          #+#    #+#             */
/*   Updated: 2026/02/18 17:07:33 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// PART #CHANNEL1,#CHANNEL2.... :comm

void PART(Client& client, std::vector<std::string>& commands)
{
    int countWords = commands.size();
    if (countWords < 2)
    {
        std::string error = ":server 461 " + client.getNickname() + " PART :Not enough parameters\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }

    std::string channels = commands[1];
    if (channels.empty() || channels[0] != '#')
    {
        std::string error = ":server 403 " + client.getNickname() + " " + channels + " :No such channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }
    
    
    std::vector<std::string> channelsList;
    size_t start = 0;
    size_t position;
    
    while ((position = channels.find(',', start)) != std::string::npos)
    {
        std::string channel = channels.substr(start, position - start);
        if (!channel.empty() && channel[0] == '#')
        channelsList.push_back(channel.substr(1));
        start = position + 1;
    }
    
    std::string lastChannel = channels.substr(start);
    if (!lastChannel.empty() && lastChannel[0] == '#')
    channelsList.push_back(lastChannel.substr(1));
    
    if (channelsList.empty())
    {
        std::string error = ":server 403 " + client.getNickname() + " " + channels + " :No such channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }
    
	for (size_t i = 0; i < channelsList.size(); i++)
	{
        std::string channelName = channelsList[i];
		
		Chanel* channel = strChanneltoChannelType(client.getServer(), channelName);
		if (!channel)
		{
            std::string error = ":server 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
            send(client.getFd(), error.c_str(), error.size(), 0);
			continue ;
		}
		if (channel->isUserInChanel(client) == false)
		{
            std::string error = ":server 442 " + client.getNickname() + " #" + channelName + " :You're not on that channel\r\n";
            send(client.getFd(), error.c_str(), error.size(), 0);
			continue ;
		}

		std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost PART #" + channelName;
        std::string reason;
        if (countWords > 2 && commands[2][0] == ':')
        {
            for (int i = 2; i < countWords ;i++)
            {
                reason += " " + commands[i];
            }
            reason = reason.substr(2);
            reason.erase(std::remove(reason.begin(), reason.end(), '\n'), reason.end());
            reason.erase(std::remove(reason.begin(), reason.end(), '\r'), reason.end());
            if (!reason.empty())
                finalMessage += " :" + reason;
        }

        finalMessage += "\r\n";

        channel->sendMessageToAll(client,true, finalMessage);

		channel->removeClient(client);

        if (!channel->getClients().empty())
        {
            if (channel->channelHasOperator() == false)
                channel->giveOperator();
        }

		if(channel->getClients().empty())
			client.getServer().removeChannel(channel);
	}		
}
