#pragma once
#include "Reservation.h"
#include "ReservationRepository.h"
#include "ReservationMapper.h"
#include "RequestReservationDto.h"

class ReservationService
{
private:
    ReservationRepository reservationRepository;
    ReservationMapper mapper;

public:

    void saveReservation(const RequestReservationDto& dto) {
        auto reservation = mapper.mapFromDto(dto);
        reservationRepository.saveReservation(reservation);
    }

    Reservation findReservationById(int id) {
        auto found = reservationRepository.findReservationById(id);
        if (found.has_value()) {
            return found.value();
        }

        std::cerr << "There is no reservation with the given ID" << std::endl;
        return Reservation();
    }

    void updateReservationById(int id, const RequestReservationDto& dto) {
        if (!reservationRepository.existsById(id)) {
            std::cerr << "There is no reservation with the given ID" << std::endl;
            return;
        }

        Reservation updateData = mapper.mapFromDto(dto);
        reservationRepository.updateReservationById(id, updateData);
    }

    void deleteReservationById(int id) {
        if (!reservationRepository.existsById(id)) {
            std::cerr << "There is no reservation with the given ID" << std::endl;
            return;
        }

        reservationRepository.deleteReservationById(id);
    }

    
};
