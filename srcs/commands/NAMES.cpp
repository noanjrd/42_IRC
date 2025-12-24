/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:41:16 by njard             #+#    #+#             */
/*   Updated: 2025/12/24 18:06:48 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void NAMES(Client& client, std::string& commands)
{
    int words = count_words(commands);
    if (words != 2)
    {
        std::cerr << "Need 1 parameter" << std::endl;
        return ;
    }
    std::string chanelname = get_word(commands, 2);
    if (chanelname[0] != '#')
    {
        std::cerr << "Missing #" << std::endl;
        return ;
    }
    chanelname = chanelname.substr(1);
    std::string message = ":localhost 353 " + client.getNickname() + " = #" + chanelname + " :";
    Chanel* chaneltemp = strChaneltoChanelType(client.getServer(), chanelname);
    if (chaneltemp == NULL)
    {
        std::cerr << "This chanel does not exist" << std::endl;
        return ;
    }
    std::vector<std::pair<Client *, int> >& clientstemp = chaneltemp->getClients();
    for (size_t index = 0; index < clientstemp.size(); index++)
    {
        std::string nametemp = "";
        if (index != 0)
        {
            nametemp += " ";
        }
        if (clientstemp[index].second == OPERATORS)
        {
            nametemp += "@" + clientstemp[index].first->getNickname();
        }
        else
        {
            nametemp += clientstemp[index].first->getNickname();
        }
        message += nametemp;
    }
    message += "\r\n";
    send(client.getFd(), message.c_str(), message.length(), 0);
    std::string endMessage = ":localhost 366 " + client.getNickname() + " #" + chanelname + " :End of /NAMES list.\r\n"; // a verifier pour le \n avec le client test
    send(client.getFd(), endMessage.c_str(), endMessage.length(), 0);
}

// :irc.localhost 335 user = #chaneelname : @
// :irc.localhost 366 user #chanelname