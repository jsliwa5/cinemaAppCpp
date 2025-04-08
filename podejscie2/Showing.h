#pragma once
#include<string>
#include<soci/soci.h>
#include<iostream>

//also ShowingDao
class Showing
{

private:

	int id_showing;
	std::string date;
	std::string room;
	int availableSits;
	int id_movie; //foreign key

public:

	Showing() = default; //SOCI requires default constructor

	Showing(std::string date, std::string room,
		int availableSits, int mid = 0, int id = 0) :

		date(date), room(room), availableSits(availableSits),
		id_movie(mid), id_showing(id) {

	}

    //getters
    int getId() {
        return id_showing;
    }

    std::string getDate() const {
        return date;
    }

    std::string getRoom() const {
        return room;
    }

    int getAvailableSits() const {
        return availableSits;
    }

    int getIdMovie() const {
        return id_movie;
    } 

    //setters
    void setId(int id) {
        id_showing = id;
    }

    void setDate(std::string newDate) {
        date = newDate;
    }

    void setRoom(std::string newRoom) {
        room = newRoom;
    }

    void setAvailableSits(int newSits) {
        availableSits = newSits;
    }

    void setIdMovie(int movieId=-1) {
        id_movie = movieId;
    }

    //sits decrementation
    void decrementAvailableSits(int dec=1){
        if (availableSits > 0) {
            availableSits -= dec;
        }
        else {
            std::cout << "\nthere are no available sits left\n";
        }
    }

    Showing& operator=(const Showing& other) {
        if (this != &other) {
            id_showing = other.id_showing;
            date = other.date;
            room = other.room;
            availableSits = other.availableSits;
            id_movie = other.id_movie;
        }
        return *this;
    }

};


namespace soci {
    template <>
    struct type_conversion<Showing> {
        typedef values base_type;

        static void from_base(const values& v, indicator ind , Showing& showing) {
            showing.setId(v.get<int>("id_showing"));
            showing.setIdMovie(v.get<int>("id_movie"));
            showing.setDate(v.get<std::string>("date"));
            showing.setRoom(v.get<std::string>("room"));
            showing.setAvailableSits(v.get<int>("availableSits"));
        }

        static void to_base(Showing& showing, values& v, indicator& ind) {
            v.set("id_showing", showing.getId());
            v.set("id_movie", showing.getIdMovie());
            v.set("date", showing.getDate());
            v.set("room", showing.getRoom());
            v.set("availableSits", showing.getAvailableSits());
            ind = i_ok;
        }
    };
}

