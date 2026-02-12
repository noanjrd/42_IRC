/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:31:18 by naziha            #+#    #+#             */
/*   Updated: 2026/02/12 14:51:02 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

// QUIT \r\n
// QUIT :<message>\r\n
// QUIT mot\r\n

void QUIT(Client &client, std::string &commands)
{
    int fd = client.getFd();

    std::string quitMessage;

    size_t pos = commands.find(':');
    
    if (pos != std::string::npos)
        quitMessage = commands.substr(pos + 1);
    else
        quitMessage = "Client Quit";

    quitMessage.erase(std::remove(quitMessage.begin(), quitMessage.end(), '\n'), quitMessage.end());
    quitMessage.erase(std::remove(quitMessage.begin(), quitMessage.end(), '\r'), quitMessage.end());

    if (quitMessage.empty())
        quitMessage = "Client Quit";

    if (client.getConfigured())
    {
        std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " QUIT :" + quitMessage + "\r\n";
        
        std::vector<Chanel*> toRemove;
        std::vector<Chanel*>& allChannels = client.getServer().getChanels();
        
        for (size_t i = 0; i < allChannels.size(); i++)
        {
            Chanel* channel = allChannels[i];
            if (channel->isUserInChanel(client))
            {
                channel->sendMessageToAllQuit(client, finalMessage);
                send(fd, finalMessage.c_str(), finalMessage.size(), 0);
                channel->removeClient(client);
                if (channel->getClients().empty())
                    toRemove.push_back(channel);
            }
        }
        for (size_t i = 0; i < toRemove.size(); i++)
            client.getServer().removeChannel(toRemove[i]);
    }

    std::string confirmMessage = "ERROR :Closing Link: localhost (Quit: " + quitMessage + ")\r\n";
    send(fd, confirmMessage.c_str(), confirmMessage.length(), 0);
    
    // client.getServer().removeClient(client);

    close(fd);
}
