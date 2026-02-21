/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientConnexion.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:46:49 by njard             #+#    #+#             */
/*   Updated: 2026/02/21 15:25:00 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.hpp"

ClientConnexion::ClientConnexion(Client client, pollfd pfd) : client(client), pfd(pfd)  {}

ClientConnexion::~ClientConnexion() {}

Client& ClientConnexion::getClient()
{
	return this->client;
}

pollfd& ClientConnexion::getPollfd()
{
	return this->pfd;
}
