#pragma once
#include <string>

class MovieDto
{
private:

	std::string title;
	std::string description;
	std::string director;
	int yearOfRelease;
	int duration; //in minutes
	std::string genre;

public:

	MovieDto(std::string title, std::string description,
		std::string director, int yearOfRelease,
		int duration, std::string genre) :

		title(title), description(description),
		director(director), yearOfRelease(yearOfRelease),
		duration(duration), genre(genre) {
	}

	/*std::string getTitle() {
		return title;
	}

	std::string getDescritption() {
		return description;
	}

	std::string getDirector() {
		return director;
	}

	int getYearOfRelease() {
		return yearOfRelease;
	}

	int getDuration() {
		return duration;
	}*/

	friend class Movie;
};

