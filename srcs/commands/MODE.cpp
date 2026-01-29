/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:30:27 by naankour          #+#    #+#             */
/*   Updated: 2026/01/29 16:04:40 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void MODE(Client& client, std::string& commands)
{
	(void)client;
	int words = count_words(commands);

	if (words < 3)
	{
		std::cerr << "461 MODE :Not enough parameters" << std::endl;
		return ;
	}

	std::string channelName = get_word(commands, 2);
	if (channelName.empty() || channelName[0] != '#')
	{
		std::cerr << "403 :'#' is missing" << std::endl;
		return ;
	}
	channelName = channelName.substr(1);

	std::string modeT = get_word(commands, 3);
	if (modeT.size() != 2)
	{
		std::cerr << "format mode must be '-' or '-' then a letter" << std::endl;
		return;
	}
	if (modeT[0] != '+' && modeT[0] != '-')
	{
		std::cerr << "472 :mode must start with '-' or '+'" << std::endl;
		return ;
	}
	char sign = modeT[0];
	char mode = modeT[1];
	
	if (mode != 'i' && mode != 't' && mode != 'k' && mode != 'l' && mode != 'o')
	{
		std::cerr << "472 :Unkwown mode" << std::endl;
		return;
	}

	std::string param;
	if (mode == 'i' || mode == 't')
	{
		if (words >= 4)
		{
			std::cerr << "461 : no param needed for this mode" <<std::endl;
			return;
		}
	}
	else
	{	
		if (words < 4)
		{
			std::cerr << "461 MODE :Not enough parameters" << std::endl;
			return;
		}

		size_t pos = commands.find(modeT);
		if (pos != std::string::npos)
		{
			pos += modeT.size();
			param = commands.substr(pos);

			while (!param.empty() && param[0] == ' ')
				param.erase(0, 1);
			if (!param.empty() && param[0] == ':')
				param = param.substr(1);
			else
				param = get_word(commands, 4);
		}
	}
	std::cout << "Channel: " << channelName << "\n";
    std::cout << "Mode: " << sign << mode << "\n";
    if (!param.empty())
        std::cout << "Param: " << param << "\n";
}