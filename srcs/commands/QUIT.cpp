/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naziha <naziha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:31:18 by naziha            #+#    #+#             */
/*   Updated: 2026/01/20 22:47:37 by naziha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

//QUIT \r\n
// QUIT :<message>\r\n
//QUIT mot\r\n

void QUIT(Client &client, std::string &commands)
{
    std::string quitMessage;

    size_t pos=commands.find(':');
    if (pos != std::string::npos)
        quitMessage = commands.substr(pos + 1);
    else
        quitMessage = "Client Quit";

    if (client.getConfigured())
    {
        std::string finalMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost" + " QUIT :" + quitMessage + "\r\n";
        
        std::vector<Chanel*>& allChannels = client.getServer().getChanels();
        for (size_t i = 0; i < allChannels.size(); i++)
        {
            Chanel* channel = allChannels[i];
            if (channel->isUserInChanel(client))
            {
                channel->sendMessageToAllQuit(client, finalMessage);
                channel->removeClient(client);
            }
        }
    }

    std::string confirmMessage = "ERROR :Closing Link: localhost (Quit: " + quitMessage + ")\r\n";
    send(client.getFd(), confirmMessage.c_str(), confirmMessage.length(), 0);
    
    client.getServer().removeClient(client);

    close(client.getFd());
}
