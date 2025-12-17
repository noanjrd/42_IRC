/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:02 by njard             #+#    #+#             */
/*   Updated: 2025/12/17 16:16:31 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRC.h"

Chanel::Chanel() {}

Chanel::Chanel(std::string name) : name(name) {}

Chanel::~Chanel() {}

std::string Chanel::getName()
{
    return this->name;
}

void Chanel::JoinChanel(Client &client)
{
    
    std::vector<std::string>::iterator it = find(this->clients_usernames.begin(), this->clients_usernames.end(), client.getUsername());
    (void)it;
    
}