#pragma once
#include <string>
#include<soci/soci.h>
class User
{
private:

	int id_user;
	std::string firstName;
	std::string lastName;
	std::string email;
	std::string dateOfRegistration;

public:

	User() = default; //SOCI requires default constructor

	User(std::string firstName, std::string lastName,
		std::string email, std::string dateOfRegistration,
		int id = 0) :

		firstName(firstName), lastName(lastName), email(email),
		dateOfRegistration(dateOfRegistration), id_user(id){
	}

	//getters
	int getId() const { 
		return id_user; 
	}

	std::string getFirstName() const {
		return firstName; 
	}

	std::string getLastName() const { 
		return lastName; 
	}
	std::string getEmail() const { 
		return email;
	}
	std::string getDateOfRegistration() const {
		return dateOfRegistration; 
	}

};

namespace soci {
	template <>
	struct type_conversion<User> {
		typedef values base_type;

		static void from_base(const values& v, indicator ind, User& user) {
			user = User(
				v.get<std::string>("firstName"),
				v.get<std::string>("lastName"),
				v.get<std::string>("email"),
				v.get<std::string>("dateOfRegistration"),
				v.get<int>("id_user")
			);
		}

		static void to_base(const User& user, values& v, indicator& ind) {
			v.set("id_user", user.getId());  // Metoda getId() musi byæ dodana do klasy User
			v.set("firstName", user.getFirstName());
			v.set("lastName", user.getLastName());
			v.set("email", user.getEmail());
			v.set("dateOfRegistration", user.getDateOfRegistration());
			ind = i_ok;
		}
	};
}

