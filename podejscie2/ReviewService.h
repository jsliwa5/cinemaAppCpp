#pragma once
#include "Review.h"
#include "ReviewRepository.h"
#include "ReviewMapper.h"
#include "RequestReviewDto.h"

class ReviewService
{
private:
    ReviewRepository reviewRepository;
    ReviewMapper mapper;

public:

    void saveReview(const RequestReviewDto& dto) {
        auto review = mapper.mapFromDto(dto);
        reviewRepository.saveReview(review);
    }

    Review findReviewById(int id) {
        auto found = reviewRepository.findReviewById(id);
        if (found.has_value()) {
            return found.value();
        }

        std::cerr << "There is no review with the given ID" << std::endl;
        return Review();
    }

    void updateReviewById(int id, const RequestReviewDto& dto) {
        if (!reviewRepository.existsById(id)) {
            std::cerr << "There is no review with the given ID" << std::endl;
            return;
        }

        Review updateData = mapper.mapFromDto(dto);
        reviewRepository.updateReviewById(id, updateData);
    }

    void deleteReviewById(int id) {
        if (!reviewRepository.existsById(id)) {
            std::cerr << "There is no review with the given ID" << std::endl;
            return;
        }

        reviewRepository.deleteReviewById(id);
    }
};
