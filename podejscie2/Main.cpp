#include <iostream>
#include "Database.h"
#include "Showing.h"
#include "User.h"
#include "Movie.h"
#include "Reservation.h"
#include "Review.h"
#include "MovieRepository.h"

int main() {
    try {
        soci::session& sql = Database::getInstance().getSession();

        sql << "CREATE TABLE IF NOT EXISTS Users ("
            "id_user INTEGER PRIMARY KEY AUTOINCREMENT, "
            "firstName TEXT, "
            "lastName TEXT, "
            "email TEXT, "
            "dateOfRegistration TEXT)";

        sql << "CREATE TABLE IF NOT EXISTS Movies ("
            "id_movie INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT, "
            "description TEXT, "
            "director TEXT, "
            "yearOfRelease INTEGER, "
            "duration INTEGER, "
            "genre TEXT)";

        sql << "CREATE TABLE IF NOT EXISTS Showings ("
            "id_showing INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_movie INTEGER, "
            "date TEXT, "
            "room TEXT, "
            "availableSits INTEGER, "
            "FOREIGN KEY(id_movie) REFERENCES Movies(id_movie))";

        sql << "CREATE TABLE IF NOT EXISTS Reservations ("
            "id_reservation INTEGER PRIMARY KEY AUTOINCREMENT, "
            "dateOfReservation TEXT, "
            "numberOfSits INTEGER, "
            "id_user INTEGER, "
            "id_showing INTEGER, "
            "FOREIGN KEY(id_user) REFERENCES Users(id_user), "
            "FOREIGN KEY(id_showing) REFERENCES Showings(id_showing))";

        sql << "CREATE TABLE IF NOT EXISTS Reviews ("
            "id_review INTEGER PRIMARY KEY AUTOINCREMENT, "
            "rating INTEGER, "
            "comment TEXT, "
            "dateOfAdding TEXT, "
            "id_user INTEGER, "
            "id_movie INTEGER, "
            "FOREIGN KEY(id_user) REFERENCES Users(id_user), "
            "FOREIGN KEY(id_movie) REFERENCES Movies(id_movie))";

        std::cout << "✅ Tabele utworzone.\n";

    
        MovieRepository movieRepo;

        // 3️⃣ Tworzenie i zapisywanie filmu
        auto found = movieRepo.findMovieById(7);
        if (found.has_value()) {
            std::cout << "🔍 Znaleziono film: " << found->getTitle()
                << " (ID: " << found->getId() << ")" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "❌ Błąd: " << e.what() << std::endl;
    }

    return 0;
}
