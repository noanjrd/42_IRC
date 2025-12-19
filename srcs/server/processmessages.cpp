/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processmessages.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:28:22 by njard             #+#    #+#             */
/*   Updated: 2025/12/19 17:01:58 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void split_message(std::string commands, Client &client)
{
	int i = 0;
	std::string line;
	if (commands.length() == 0)
		return ;
	while (commands[i])
	{
		line+=commands[i];
		if (commands[i] ==  '\n' || commands[i] == '\r')
		{
			process_mess(line, client);
			while(commands[i] && (commands[i] ==  '\n' || commands[i] == '\r'))
			{
				if (!commands[i])
				{
					break;
				}
				i++;
			}
			line = "";
			continue;
		}
		i++;
	}
}

int process_mess(std::string commands, Client &client)
{
	std::cout << "entire command : " << commands << std::endl;
	std::string command = get_word(commands, 1);
	if (client.getAuthenticated() == false)
	{
		client.authentication(commands);
		return 0;
	}
	if (client.getConfigured() == false)
	{
		client.configure(commands);
		return 0;
	}
	if (command.empty())
	{
		std::cerr << "Empty input" << std::endl;
		return 0;
	}
	if (command == "JOIN")
	{
		JOIN(client, commands);
		return 0;
	}
	if (command == "NAMES")
	{
		NAMES(client, commands);
		return 0;	
	}
	if (command == "PRIVMSG")
	{
		
	}
	std::cout << "Configured" << std::endl;
	
	return 0;
}