#pragma once
#include<string>
#include<soci/soci.h>

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

		id_movie(id), title(title), description(description), director(director),
		yearOfRelease(yearOfRelease), duration(duration), genre(genre) {
	}

    void setId(int newId) {
        id_movie = newId;
    }

    //getters
    int getId() const{
        return id_movie;
    }

    std::string getTitle( )const {
        return title;
    }

    std::string getDescription() const {
        return description;
    }

    std::string getDirector() const {
        return director;
    }

    int getYearOfRelease() const {
        return yearOfRelease;
    }

    int getDuration() const {
        return duration;
    }

    std::string getGenre() const {
        return genre;
    }

    Movie& operator=(const Movie& other) {
        if (this != &other) {
            id_movie = other.id_movie;
            title = other.title;
            description = other.description;
            director = other.director;
            yearOfRelease = other.yearOfRelease;
            duration = other.duration;
            genre = other.genre;
        }
        return *this;
    }

    friend class MobvieMapper;
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

        static void to_base(const Movie& movie, values& v, indicator& ind) {
            v.set("id_movie", movie.getId());  // Metoda getId() musi by� dodana do klasy Movie
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


