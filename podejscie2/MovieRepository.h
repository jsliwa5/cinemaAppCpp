#pragma once
#include "Database.h"
#include "Movie.h"
#include <optional>


class MovieRepository
{
private:
	soci::session& sql = Database::getInstance().getSession();

public:

    void saveMovie(Movie& movie) {
        sql << "INSERT INTO Movies (title, description, director, yearOfRelease, duration, genre) "
            "VALUES (:title, :description, :director, :yearOfRelease, :duration, :genre)",
            soci::use(movie);

        int id;
        sql << "SELECT last_insert_rowid()", soci::into(id);
        movie.setId(id); // <- bez tego nie bêdzie ID

    }

    std::optional<Movie> findMovieById(int id) {
        try {
            Movie m;
            sql << "SELECT * FROM Movies WHERE id_movie = :id", soci::use(id), soci::into(m);
            return m;
        }
        catch (const std::exception& _) {
            return std::nullopt;
        }
    }

    void updateMovieById(int id, const Movie& movie) {
        sql << "UPDATE Movies SET title = :title, description = :description, director = :director, "
            "yearOfRelease = :yearOfRelease, duration = :duration, genre = :genre "
            "WHERE id_movie = :id",
            soci::use(movie), soci::use(id);
    }

    void deleteMovieById(int id) {
        sql << "DELETE FROM Movies WHERE id_movie = :id", soci::use(id);
    }

    std::optional<Movie> findMovieByTitle(const std::string& title) {
        try {
            Movie movie;
            sql << "SELECT * FROM Movies WHERE title = :title", soci::use(title), soci::into(movie);
            return movie;
        }
       catch (const std::exception& _) {
           return std::nullopt;
       }
        
    }

    bool existsById(int id) {
        int count = 0;
        sql << "SELECT COUNT(*) FROM Movies WHERE id_movie = :id", soci::use(id), soci::into(count);
        return count > 0;
    }

};

