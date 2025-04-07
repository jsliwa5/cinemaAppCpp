#pragma once
#include<string>
#include<soci/soci.h>

class Reservation
{

private:

	int id_reservation;
	std::string dateOfReservation;
	int numberOfSits;
	int id_user; //foreign key
	int id_showing; //foreign key

public:

	Reservation() = default; //SOCI requires default constructor

	Reservation(std::string dateOfReservation, int numberOfSits,
		int userId = 0, int showingId = 0, int reservationId = 0) :

		dateOfReservation(dateOfReservation), numberOfSits(numberOfSits),
		id_user(userId), id_showing(showingId), id_reservation(reservationId) {
	}

	//getters
	int getReservationId() const {
		return id_reservation;
	}

	std::string getDateOfReservation() const {
		return dateOfReservation;
	}

	int getNumberOfSits() const {
		return numberOfSits;
	}

	int getUserId() const {
		return id_user;
	}

	int getShowingId() const {
		return id_showing;
	}

	//setters
	void setReservationId(int newId) {
		id_reservation = newId;
	}

	void setDateOfReservation(std::string newDate) {
		dateOfReservation = newDate;
	}

	void setNumberOfSits(int newNoOfSits) {
		numberOfSits = newNoOfSits;
	}

	void setUserId(int newUserId) {
		id_user = newUserId;
	}

	void setShowingId(int newShowingId) {
		id_showing = newShowingId;
	}

	friend class ReservationMapper;
};

namespace soci {
	template <>
	struct type_conversion<Reservation> {
		typedef values base_type;

		static void from_base(const values& v, indicator ind, Reservation& reservation) {
			reservation = Reservation(
				v.get<std::string>("dateOfReservation"),
				v.get<int>("numberOfSits"),
				v.get<int>("id_user"),
				v.get<int>("id_showing"),
				v.get<int>("id_reservation")
			);
		}

		static void to_base(Reservation& reservation, values& v, indicator& ind) {
			v.set("id_reservation", reservation.getReservationId());
			v.set("dateOfReservation", reservation.getDateOfReservation());
			v.set("numberOfSits", reservation.getNumberOfSits());
			v.set("id_user", reservation.getUserId());
			v.set("id_showing", reservation.getShowingId());
			ind = i_ok;
		}
	};
}