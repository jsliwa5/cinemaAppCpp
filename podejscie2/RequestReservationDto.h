#pragma once
#include <string>

class RequestReservationDto
{

private:

	int userId;
	int showingId;
	std::string dateOfReservation;
	int numberOfSits;

public:
	
	RequestReservationDto(std::string date, int sits,
		int userId, int showingId) :

		dateOfReservation(date), numberOfSits(sits),
		userId(userId), showingId(showingId) {
	}


	friend class ReservationMapper;
};

