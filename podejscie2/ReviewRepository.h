#pragma once
#include "Database.h"
#include "UserRepository.h"
#include "MovieRepository.h"
#include "Review.h"

class ReviewRepository
{

private:

	soci::session& sql = Database::getInstance().getSession();
	UserRepository userRepository;
	MovieRepository movieRepository;

public:

    void saveReview(const Review& review) {
        if (!userRepository.existsById(review.getUserId())) {
            throw std::runtime_error("User with given ID does not exist.");
        }
        if (!movieRepository.existsById(review.getMovieId())) {
            throw std::runtime_error("Movie with given ID does not exist.");
        }

        sql << "INSERT INTO Reviews (rating, comment, dateOfAdding, id_user, id_movie) "
            "VALUES (:rating, :comment, :dateOfAdding, :id_user, :id_movie)",
            soci::use(review);
    }

    std::optional<Review> findReviewById(int id) {
        try {
            Review review;
            sql << "SELECT * FROM Reviews WHERE id_review = :id",
                soci::use(id), soci::into(review);

            return review;
        }
        
        catch(const std::exception & _){
            return std::nullopt;
        }
    }

    void updateReviewById(int id, const Review& review) {
        if (!userRepository.existsById(review.getUserId())) {
            throw std::runtime_error("User with given ID does not exist.");
        }
        if (!movieRepository.existsById(review.getMovieId())) {
            throw std::runtime_error("Movie with given ID does not exist.");
        }

        sql << "UPDATE Reviews SET rating = :rating, comment = :comment, "
            "dateOfAdding = :dateOfAdding, id_user = :id_user, id_movie = :id_movie "
            "WHERE id_review = :id",
            soci::use(review), soci::use(id, "id");
    }

    void deleteReviewById(int id) {
        sql << "DELETE FROM Reviews WHERE id_review = :id", soci::use(id);
    }

    bool existsById(int id) {
        int count = 0;
        sql << "SELECT COUNT(*) FROM Reviews WHERE id_review = :id", soci::use(id), soci::into(count);
        return count > 0;
    }


};

