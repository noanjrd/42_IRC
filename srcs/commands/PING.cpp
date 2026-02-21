/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:14:22 by naankour          #+#    #+#             */
/*   Updated: 2026/02/21 12:23:40 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

void PING(Client& client, std::vector<std::string>& commands)
{
	std::string pong = "PONG server :";
	if (commands.size() >= 2)
		pong += commands[1];
	pong += "\r\n";
	client.sendToClientMessage(pong);
}