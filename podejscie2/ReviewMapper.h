#pragma once
#include "Review.h"
#include "RequestReviewDto.h"

class ReviewMapper {
public:
    ReviewMapper() = default;

    static Review mapFromDto(const RequestReviewDto& dto) {
        return Review(
            dto.rating,
            dto.comment,
            dto.dateOfAdding,
            dto.userId,
            dto.movieId
        );
    }
};

