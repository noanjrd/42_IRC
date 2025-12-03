/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processmessages.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:28:22 by njard             #+#    #+#             */
/*   Updated: 2025/12/03 12:03:59 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

int process_mess(std::string commands, Client &client)
{
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
	std::cout << "Configured" << std::endl;
	
	return 0;
}