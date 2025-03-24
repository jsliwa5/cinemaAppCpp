#include <iostream>
#include "Database.h"
#include "Showing.h"

int main() {
    try {
        // Pobranie instancji bazy danych
        soci::session& sql = Database::getInstance().getSession();

        // 1️⃣ Tworzenie tabeli, jeśli nie istnieje
        sql << "CREATE TABLE IF NOT EXISTS Showings ("
            "id_showing INTEGER PRIMARY KEY AUTOINCREMENT, "
            "id_movie INTEGER, "
            "date TEXT, "
            "room TEXT, "
            "availableSits INTEGER)";

        // 2️⃣ Tworzenie obiektu Showing
        Showing s("2024-10-24", "Czerwona", 100, 2); // ID = -1, bo autoincrement

        // 3️⃣ Wstawienie obiektu do bazy
        sql << "INSERT INTO Showings (id_movie, date, room, availableSits) "
            "VALUES (:id_movie, :date, :room, :availableSits)",
            soci::use(s);

        std::cout << "Seans zapisany do bazy!" << std::endl;

        // 4️⃣ Pobranie ostatniego ID
        int lastId;
        sql << "SELECT last_insert_rowid()", soci::into(lastId);

        // 5️⃣ Odczytanie rekordu
        Showing s2;
        sql << "SELECT id_showing, id_movie, date, room, availableSits FROM Showings WHERE id_showing = :id",
            soci::use(lastId), soci::into(s2);

        // 6️⃣ Wyświetlenie pobranego obiektu
        std::cout << "Odczytano seans: "
            << "ID: " << s2.getId()
            << ", Film ID: " << s2.getIdMovie()
            << ", Data: " << s2.getDate()
            << ", Sala: " << s2.getRoom()
            << ", Dostępne miejsca: " << s2.getAvailableSits()
            << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }

    return 0;
}
