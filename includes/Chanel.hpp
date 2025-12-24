/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chanel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:29:30 by njard             #+#    #+#             */
/*   Updated: 2025/12/24 18:07:41 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include "Client.hpp"



class Chanel
{
private:
	std::string name;
	std::string topic;
	std::vector<std::pair<Client*, int> > clients;
	// int user_limit;
	std::string password;
	bool topicForAll;
	// int id;
	// Client tabclient[];

public:
	// Chanel();
	Chanel(std::string name, Client &client);
	~Chanel();

	std::string getName();
	std::vector<std::pair<Client*, int> >& getClients();
	bool getTopicForAll() const;

	void setTopic(std::string topic);

	bool isUserOperator(Client &client) const;
	bool isUserInChanel(Client&);
	void JoinChanel(Client &client);
};