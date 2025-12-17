/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:10:44 by njard             #+#    #+#             */
/*   Updated: 2025/12/17 15:57:55 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void PRIVMSG(Client &client, std::string &commands)
{
	std::string destination = get_word(commands, 2);
	int words = count_words(commands);
	if (words < 3)
	{
		std::cerr << "Not enough words" << std::endl;
		return ;
	}
	if (destination[0] != '#')
	{
		std::vector<std::string> usernames = client.getServer().getUsernames();
		std::vector<std::string>::iterator it = find(usernames.begin(),usernames.end(), destination);
		
	}
	else
	{
		destination = destination.substr(1,destination.length()-1);
		std::cout << destination << std::endl;
	}
		
}

