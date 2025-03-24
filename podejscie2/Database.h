#pragma once
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>
#include <mutex>
#include <iostream>

class Database {
private:
    soci::session sql;
    static std::mutex mutex; 

    Database() try
        : sql(soci::sqlite3, "database.db")
    {
        std::cout << "Po��czono z baz� danych!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "B��d po��czenia z baz� danych: " << e.what() << std::endl;
        throw;
    }

public:
    static Database& getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        static Database instance;
        return instance;
    }

    soci::session& getSession() {
        return sql;
    }

    ~Database() {
        if (sql.is_connected()) {
            sql.close();
            std::cout << "Zamkni�to po��czenie z baz� danych." << std::endl;
        }
    }

    Database(const Database&) = delete;
    void operator=(const Database&) = delete;
};

std::mutex Database::mutex;
