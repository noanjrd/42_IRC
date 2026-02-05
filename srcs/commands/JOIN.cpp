/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naziha <naziha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:00:12 by njard             #+#    #+#             */
/*   Updated: 2026/02/03 19:48:53 by naziha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void JOIN(Client &client, std::string &commands)
{
	int words = count_words(commands);
	if (words < 2)
	{
		std::cerr << "461 JOIN :Not enough parameters" << std::endl;
		return ;
	}
	
	std::string chanelname = get_word(commands,2);
	if (chanelname[0] != '#')
	{
		std::cerr << "403 :Missing # in channel name";
		return ;
	}
	chanelname = chanelname.substr(1);

	std::string password;
	if (words >= 3)
		password = get_word(commands, 3);

	Chanel * chaneltemp = strChaneltoChanelType(client.getServer() ,chanelname);
	if (chaneltemp == NULL)
	{
		Chanel* newchannel = new Chanel(chanelname, client);
		if (!password.empty())
		{
			newchannel->sethasPassword(true);
			newchannel->setPassword(password);
		}
		client.getServer().getChanels().push_back(newchannel);
		client.getServer().getUChanelsName().push_back(chanelname);
		return ;
	}
	if ((chaneltemp->isInviteOnly() == true) && (chaneltemp->isInvited(client.getNickname()) == false))
	{
		std::cerr << "473 " << chanelname << " :Cannot join channel (+i)" << std::endl;
		return;
	}
	if ((chaneltemp->isHasPassword() == true) && (chaneltemp->checkPassword(password)== false))
	{
		std::cerr << "475 " << chanelname << " :Cannot join channel (+k)" << std::endl;
		return;
	}
	if (chaneltemp->ishasAUserLimit() == true)
	{
		if (chaneltemp->getClients().size() >= chaneltemp->getUserLimit())
		{
			std::cerr << "471 " << chanelname << " :Cannot join channel (+l)" << std::endl;
			return;
		}
	}
	try
	{
		chaneltemp->JoinChanel(client);
		if (chaneltemp->isInvited(client.getNickname()))
			chaneltemp->removeInvite(client.getNickname());
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}