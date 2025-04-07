#pragma once
#include "Showing.h"
#include "RequestShowingDto.h"

class ShowingMapper {
public:
    ShowingMapper() = default;

    static Showing mapFromDto(const RequestShowingDto& dto) {
        return Showing(
            dto.date,
            dto.room,
            dto.availableSits,
            dto.movieId
        );
    }
};
