#pragma once
#include "Reservation.h"
#include "RequestReservationDto.h"

class ReservationMapper {
public:
    ReservationMapper() = default;

    static Reservation mapFromDto(const RequestReservationDto& dto) {
        return Reservation(
            dto.dateOfReservation,
            dto.numberOfSits,
            dto.userId,
            dto.showingId
        );
    }
};
