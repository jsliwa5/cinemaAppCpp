#pragma once
#include "Database.h"
#include "Showing.h"
#include "MovieRepository.h"

class ShowingRepository
{

private:

	soci::session& sql = Database::getInstance().getSession();
	MovieRepository movieRepository;

public:

    void saveShowing(const Showing& showing) {
        if (!movieRepository.existsById(showing.getIdMovie())) {
            throw std::runtime_error("Movie with given ID does not exist.");
        }

        sql << "INSERT INTO Showings (date, room, availableSits, id_movie) "
            "VALUES (:date, :room, :availableSits, :id_movie)",
            soci::use(showing);
    }

    std::optional<Showing> findShowingById(int id) {
        Showing showing;
        soci::indicator ind;
        sql << "SELECT * FROM Showings WHERE id_showing = :id", soci::use(id), soci::into(showing, ind);

        if (ind == soci::i_ok) {
            return showing;
        }
        return std::nullopt;
    }

    void updateShowingById(int id, const Showing& showing) {
        if (!movieRepository.existsById(showing.getIdMovie())) {
            throw std::runtime_error("Movie with given ID does not exist.");
        }

        sql << "UPDATE Showings SET date = :date, room = :room, availableSits = :availableSits, "
            "id_movie = :id_movie WHERE id_showing = :id",
            soci::use(showing), soci::use(id);
    }

    void deleteShowingById(int id) {
        sql << "DELETE FROM Showings WHERE id_showing = :id", soci::use(id);
    }

    bool existsById(int id) {
        int count = 0;
        sql << "SELECT COUNT(*) FROM Showings WHERE id_showing = :id", soci::use(id), soci::into(count);
        return count > 0;
    }
};

