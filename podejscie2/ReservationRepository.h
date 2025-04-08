#pragma once
#include "Database.h"
#include "Reservation.h"
#include "UserRepository.h"
#include "ShowingRepository.h"

class ReservationRepository
{

private:

	soci::session& sql = Database::getInstance().getSession();
	ShowingRepository showingRepository;
	UserRepository userRepository;

public:

    void saveReservation(const Reservation& reservation) {
        if (!userRepository.existsById(reservation.getUserId())) {
            throw std::runtime_error("User with given ID does not exist.");
        }
        if (!showingRepository.existsById(reservation.getShowingId())) {
            throw std::runtime_error("Showing with given ID does not exist.");
        }

        sql << "INSERT INTO Reservations (dateOfReservation, numberOfSits, id_user, id_showing) "
            "VALUES (:dateOfReservation, :numberOfSits, :id_user, :id_showing)",
            soci::use(reservation);
    }

    std::optional<Reservation> findReservationById(int id) {
        try {
            Reservation reservation;
            soci::indicator ind;
            sql << "SELECT * FROM Reservations WHERE id_reservation = :id",
                soci::use(id), soci::into(reservation);
            
            return reservation;
            
        }
        catch (const std::exception& _){
            return std::nullopt;
        }
    }

    void updateReservationById(int id, const Reservation& reservation) {
        if (!userRepository.existsById(reservation.getUserId())) {
            throw std::runtime_error("User with given ID does not exist.");
        }
        if (!showingRepository.existsById(reservation.getShowingId())) {
            throw std::runtime_error("Showing with given ID does not exist.");
        }

        sql << "UPDATE Reservations SET dateOfReservation = :dateOfReservation, "
            "numberOfSits = :numberOfSits, id_user = :id_user, id_showing = :id_showing "
            "WHERE id_reservation = :id",
            soci::use(reservation), soci::use(id);
    }

    void deleteReservationById(int id) {
        sql << "DELETE FROM Reservations WHERE id_reservation = :id", soci::use(id);
    }


};

