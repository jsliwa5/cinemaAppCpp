#pragma once
#include "Database.h"
#include "User.h"
#include <optional>

class UserRepository
{
private:

	soci::session& sql = Database::getInstance().getSession();

public:

    void saveUser(const User& user) {
        sql << "INSERT INTO Users (firstName, lastName, email, dateOfRegistration) "
            "VALUES (:firstName, :lastName, :email, :dateOfRegistration)",
            soci::use(user);
    }

    std::optional<User> findUserById(int id) {
        try {
            User user;

            sql << "SELECT * FROM Users WHERE id_user = :id", soci::use(id), soci::into(user);

            return user;
        } 
        catch (const std::exception & _){
            return std::nullopt;
        }
    }

    void updateUserById(int id, const User& user) {
        sql << "UPDATE Users SET firstName = :firstName, lastName = :lastName, email = :email, "
            "dateOfRegistration = :dateOfRegistration WHERE id_user = :id",
            soci::use(user), soci::use(id, "id");
    }

    void deleteUserById(int id) {
        sql << "DELETE FROM Users WHERE id_user = :id", soci::use(id);
    }

    std::optional<User> findUserByLastName(const std::string& lastName) {

        try {
            User user;

            sql << "SELECT * FROM Users WHERE lastName = :lastName", soci::use(lastName), soci::into(user);

            return user;
        }
        catch(const std::exception & _){
            return std::nullopt;
        }
    }

    bool existsById(int id) {
        int count = 0;
        sql << "SELECT COUNT(*) FROM Users WHERE id_user = :id", soci::use(id), soci::into(count);
        return count > 0;
    }

};

