#pragma once
#include <string>

class RequestReviewDto
{

private:

	int userId;
	int movieId;
	int rating; //1-5
	std::string comment;
	std::string dateOfAdding;

public:

	RequestReviewDto(int rating, std::string comment, std::string dateOfAdding,
		int userId, int movieId) :

		rating(rating), comment(comment), dateOfAdding(dateOfAdding),
		userId(userId), movieId(movieId) {
	}

	friend class ReviewMapper;
};

