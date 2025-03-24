#pragma once
#include<string>
#include<soci/soci.h>
#include "MovieDto.h"

//also movieDao
class Movie
{
private:

	int id_movie;
	std::string title;
	std::string description;
	std::string director;
	int yearOfRelease;
	int duration; //in minutes
	std::string genre;

public:

	Movie() = default; //SOCI requires default construtctor

	Movie(std::string title, std::string description, std::string director, 
		int yearOfRelease, int duration, std::string genre, int id = -1) :

		id_movie(id), title(title), description(description),
		yearOfRelease(yearOfRelease), duration(duration), genre(genre) {
	}

	static Movie movieFromMovieDto(const MovieDto& mDto) {

		return Movie(mDto.title, mDto.description, mDto.director,
			mDto.yearOfRelease, mDto.duration, mDto.genre);

	}

    //getters
    int getId() {
        return id_movie;
    }

    std::string getTitle() {
        return title;
    }

    std::string getDescription() {
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
    }

    std::string getGenre() {
        return genre;
    }


};



namespace soci {
    template <>
    struct type_conversion<Movie> {
        typedef values base_type;

        static void from_base(const values& v, indicator ind, Movie& movie) {
            movie = Movie(
                v.get<std::string>("title"),
                v.get<std::string>("description"),
                v.get<std::string>("director"),
                v.get<int>("yearOfRelease"),
                v.get<int>("duration"),
                v.get<std::string>("genre"),
                v.get<int>("id_movie")
            );
        }

        static void to_base(Movie& movie, values& v, indicator& ind) {
            v.set("id_movie", movie.getId());  // Metoda getId() musi byæ dodana do klasy Movie
            v.set("title", movie.getTitle());
            v.set("description", movie.getDescription());
            v.set("director", movie.getDirector());
            v.set("yearOfRelease", movie.getYearOfRelease());
            v.set("duration", movie.getDuration());
            v.set("genre", movie.getGenre());
            ind = i_ok;
        }
    };
}


