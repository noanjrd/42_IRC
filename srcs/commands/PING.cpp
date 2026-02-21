/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:14:22 by naankour          #+#    #+#             */
/*   Updated: 2026/02/21 15:25:00 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

void PING(Client& client, std::vector<std::string>& commands)
{
	std::string pong = "PONG server :";
	if (commands.size() >= 2)
		pong += commands[1];
	pong += "\r\n";
	client.sendToClientMessage(pong);
}