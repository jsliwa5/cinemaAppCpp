#pragma once
#include <string>

class RequestShowingDto
{

private:

	int movieId;
	int availableSits;
	std::string date;
	std::string room;

public:

	RequestShowingDto(std::string date, int availableSits,
		std::string room, int movieId) :

		date(date), availableSits(availableSits), room(room), movieId(movieId) {
	}


	friend class ShowingMapper;
};

