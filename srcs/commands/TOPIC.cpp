/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:35:37 by njard             #+#    #+#             */
/*   Updated: 2025/12/24 18:36:26 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void TOPIC(Client &client, std::string& commands)
{
	int words = count_words(commands);
	if (words < 3)
	{
		std::cerr << "Not enough words" << std::endl;
		return ;
	}
	std::string chanelname;
	chanelname = get_word(commands, 2);
	
	if (chanelname[0] != '#')
	{
		std::cerr << "Missing #" << std::endl;
		return ;
	}
	chanelname = chanelname.substr(1);
	int i = 3;
	std::string topic;
	topic = get_word(commands, 2);
	while (i <= words)
	{
		topic += get_word(commands,i);
		i++;
	}
	Chanel* chaneltemp = strChaneltoChanelType(client.getServer(), chanelname);
	if (chaneltemp == NULL)
	{
		std::cerr << "Chanel not found" << std::endl;
		return ;
	}
	if (chaneltemp->isUserInChanel(client) == false)
	{
		std::cerr << "Client not in chanel" << std::endl;
		return ;
	}
	if (chaneltemp->getTopicForAll() == false and chaneltemp->isUserOperator(client) == false)
	{
		std::cerr << "User is not an operator." << std::endl;
		return ;
	}
	chaneltemp->setTopic(topic);
	return;
}

