#pragma once
#include <string>

class RequestUserDto
{

private:

	std::string firstName;
	std::string lastName;
	std::string email;
	std::string dateOfRegistration;
	
public:

	RequestUserDto(std::string firstName, std::string lastName,
		std::string email, std::string date):

		firstName(firstName), lastName(lastName), email(email), dateOfRegistration(date){
	}


	friend class UserMapper;
};

