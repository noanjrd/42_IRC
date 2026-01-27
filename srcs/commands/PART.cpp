/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:45:53 by naankour          #+#    #+#             */
/*   Updated: 2026/01/27 15:50:28 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// KICK #CHANNEL1,#CHANNEL2.... :comm

void PART(Client& client, std::string& commands)
{
    int words = count_words(commands);
    if (words < 2)
    {
        std::cerr << "Not enough words" << std::endl;
        return;
    }

    std::string channels = get_word(commands, 2);
    if (channels.empty() || channels[0] != '#')
    {
        std::cerr << "'#' is missing" << std::endl;
        return;
    }

    std::vector<std::string> channelsList;
    size_t start = 0;
    size_t pos;

    while ((pos = channels.find(',', start)) != std::string::npos)
    {
        std::string channel = channels.substr(start, pos - start);
        if (!channel.empty() && channel[0] == '#')
            channelsList.push_back(channel.substr(1));

        start = pos + 1;
    }

    std::string lastChannel = channels.substr(start);
    if (!lastChannel.empty() && lastChannel[0] == '#')
        channelsList.push_back(lastChannel.substr(1));

    if (channelsList.empty())
    {
        std::cerr << "No valid channels" << std::endl;
        return;
    }

	for (size_t i = 0; i < channelsList.size(); i++)
	{
		std::string channelName = channelsList[i];
		
		Chanel* ch = NULL;
		ch = strChaneltoChanelType(client.getServer(), channelName);
		if (!ch)
		{
			std::cerr << "Channel does not exist" << std::endl;
			continue ;
		}
		if (ch->isUserInChanel(client) == false)
		{
			std::cerr << "Client is not in channel" << std::endl;
			continue ;
		}
		std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost PART #" + channelName + "\r\n";
		ch->sendMessageToAllQuit(client, finalMessage);
		ch->removeClient(client);
		if(ch->getClients().empty())
			client.getServer().removeChannel(ch);
		}
			
}

