/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:42:20 by naziha            #+#    #+#             */
/*   Updated: 2026/02/18 15:52:45 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

//INVITE <nickname> <#channel>

void INVITE(Client& client, std::vector<std::string>& commands)
{
    int countWords = commands.size();
    if (countWords != 3)
    {
        std::string error = ":server 461 " + client.getNickname() + " INVITE :Not enough parameters\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return ;
    }

    std::string nickname = commands[1];
    if (client.getServer().isNicknameInServer(nickname) == false)
    {
        std::string error = ":server 401 " + client.getNickname() + " " + nickname + " :No such nick\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }

    std::string channelName = commands[2];
    if (channelName[0] != '#')
    {
        std::string error = ":server 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return ;
    }
    channelName = channelName.substr(1);

    Chanel* channel = strChanneltoChannelType(client.getServer(), channelName);
    if (!channel)
    {
        std::string error = ":server 403 " + client.getNickname() + " #" + channelName + " :No such channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return ;
    }
    if (!channel->isUserInChanel(client))
    {
        std::string error = ":server 442 " + client.getNickname() + " #" + channelName + " :You're not on that channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }
    if (channel->isInviteOnly() && !channel->isUserOperator(client))
    {
        std::string error = ":server 482 " + client.getNickname() + " #" + channelName + " :You're not channel operator\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }
    if (channel->isUserInChannelByNick(nickname))
    {
        std::string error = ":server 443 " + client.getNickname() + " " + nickname + " #" + channelName + " :is already on channel\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }

    Client* invitedClient = client.getServer().getClientByNick(nickname);
    if (!invitedClient)
    {
        std::string error = ":server 401 " + client.getNickname() + " " + nickname + " :No such nick\r\n";
        send(client.getFd(), error.c_str(), error.size(), 0);
        return;
    }
    channel->addInvite(nickname);


    std::string messageUser = ":server 341 " + client.getNickname() + " " + nickname + " #" + channelName + "\r\n";
    send(client.getFd(), messageUser.c_str(), messageUser.size(), 0);

    std::string messageInvite = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost INVITE " + nickname + " #" + channelName + "\r\n";
    send(invitedClient->getFd(), messageInvite.c_str(), messageInvite.length(), 0);
}