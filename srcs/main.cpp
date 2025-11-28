/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:04:17 by njard             #+#    #+#             */
/*   Updated: 2025/11/28 16:09:54 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <poll.h>

// AF_INET --> IPv4
// SOCK_STREAM --> TCP
// INADDR_ANY --> accepte la connexion depuis n importe quel adresse ip
// POLLIN --> constante de valeur 0b000001 qui veut dire que il y a des données disponibles à lire sur le socket

#include "../includes/Client.hpp"

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return 1;
	}
	(void)argv;
	int port = atoi(argv[1]);
	std::string passwd = argv[2];
	int server_fd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in address; // definition adresse du serveur
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	bind(server_fd, (struct sockaddr*)&address, sizeof(address)); // associce le socket a l adrsse
	listen(server_fd, 99); //socket ouvert pret a ecouter, 99 est le nb max de connections avant la file d attente

	std::vector<pollfd> watched_socket;
	pollfd server_poll;
	server_poll.fd = server_fd;
	server_poll.events = POLLIN;;
	watched_socket.push_back(server_poll);

	while(true)
	{
		int waiting_socket = poll(watched_socket.data(), watched_socket.size(), -1);
		if (waiting_socket < 0)
		{
				
			continue;
		}
		if (watched_socket[0].revents & POLLIN)
		{
			
		}
		
	}

	// close()
	return 0;
}
