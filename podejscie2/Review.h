#pragma once
#include <string>
#include <soci/soci.h>

class Review
{
private:

	int id_review;
	int rating; //scale 1-5
	std::string comment;
	std::string dateOfAdding;
	int id_user; //foreign key
	int id_movie; //foreign key

public:

	Review() = default; //SOCI requires default constructor

	Review(int rating, std::string comment, std::string date,
		int userId = 0, int movieId = 0, int reviewId = 0) :

		rating(rating), comment(comment), dateOfAdding(date),
		id_user(userId), id_movie(movieId), id_review(reviewId) {
	}

	//getters
	int getReviewId() const {
		return id_review;
	}

	int getRating() const {
		return rating;
	}

	std::string getComment() const {
		return comment;
	}

	std::string getDateOfAdding() const {
		return dateOfAdding;
	}

	int getUserId() const{
		return id_user;
	}

	int getMovieId() const{
		return id_user;
	}

	//setters
	void setReviewId(int newId) {
		id_review = newId;
	}

	void setRating(int newRating) {
		rating = newRating;
	}

	void setComment(int newComment) {
		comment = newComment;
	}

	void setDateOfAdding(std::string newDate) {
		dateOfAdding = newDate;
	}

	void setUserId(int newUserId) {
		id_user = newUserId;
	}

	void setMovieId(int newMovieId) {
		id_movie = newMovieId;
	}

};

namespace soci {
	template <>
	struct type_conversion<Review> {
		typedef values base_type;

		static void from_base(const values& v, indicator ind, Review& review) {
			review = Review(
				v.get<int>("rating"),
				v.get<std::string>("comment"),
				v.get<std::string>("dateOfAdding"),
				v.get<int>("id_user"),
				v.get<int>("id_movie"),
				v.get<int>("id_review")
			);
		}

		static void to_base(Review& review, values& v, indicator& ind) {
			v.set("id_review", review.getReviewId());
			v.set("rating", review.getRating());
			v.set("comment", review.getComment());
			v.set("dateOfAdding", review.getDateOfAdding());
			v.set("id_user", review.getUserId());
			v.set("id_movie", review.getMovieId());
			ind = i_ok;
		}
	};
}

