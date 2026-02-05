/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naziha <naziha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:35:37 by njard             #+#    #+#             */
/*   Updated: 2026/02/03 16:09:41 by naziha           ###   ########.fr       */
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

	std::string topic;
	for (int i = 3; i <=words; i++)
	{
		if (!topic.empty())
			topic += " ";
		topic += get_word(commands,i);
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

	if (chaneltemp->getTopicProtected() == true && chaneltemp->isUserOperator(client) == false)
	{
		std::cerr << "User is not an operator." << std::endl;
		return ;
	}
	chaneltemp->setTopic(topic);
	return;
}

