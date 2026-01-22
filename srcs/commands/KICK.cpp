/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:15:17 by njard             #+#    #+#             */
/*   Updated: 2026/01/22 15:50:11 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void KICK(Client& client, std::string& commands)
{
	int words = count_words(commands);
	if (words < 3)
	{
		std::cerr << "Not enough words" << std::endl;
		return ;
	}

	std::string chanel = get_word(commands, 2);
	if (chanel[0] != '#')
	{
		std::cerr << "Missing #" << std::endl;
		return ;
	}
	chanel = chanel.substr(1);
	
	std::string username = get_word(commands, 3);
	
	std::string reason;
	size_t pos = commands.find(':');
	if (pos != std::string::npos)
		reason = commands.substr(pos + 1);
	else
		reason = "No reason";
	reason.erase(std::remove(reason.begin(), reason.end(), '\n'), reason.end());
	reason.erase(std::remove(reason.begin(), reason.end(), '\r'), reason.end());

	if (client.getServer().isUserNameInServer(username) ==  false)
	{
		std::cerr << "User not in server" << std::endl;
		return ;
	}
	
	return ;
}