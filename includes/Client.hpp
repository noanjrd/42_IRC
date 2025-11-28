/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:27:17 by njard             #+#    #+#             */
/*   Updated: 2025/11/28 14:16:50 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>

class Client
{
private:
	std::string nickname;
	std::string username;
	std::string password;
	int id;
	int authenticated;
	char message[1024];
	bool administrators;

public:
	Client();
	~Client();
};