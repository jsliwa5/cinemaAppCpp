#pragma once
#include "Movie.h"
#include "MovieRepository.h"
#include "MovieMapper.h"

class MovieService
{
private:

	MovieRepository movieRepository;
	MovieMapper mapper;

public:

	void saveMovie(RequestMovieDto dto) {

		auto movieToBeSaved = mapper.mapFromDto(dto);
		movieRepository.saveMovie(movieToBeSaved);

	}

	Movie findMovieByTitle(std::string title) {
		auto found = movieRepository.findMovieByTitle(title);

		if (found.has_value()) {
			return found.value();
		}

		std::cerr << "There is no movie with given title";
		return Movie();
	}

	Movie findMovieById(int id) {

		auto found = movieRepository.findMovieById(id);

		if (found.has_value()) {
			return found.value();
		}

		std::cerr << "There is no movie with given id";
		return Movie();

	}

	void updateMovieById(int id, RequestMovieDto dto) {
		
		if (!movieRepository.existsById(id)) {
			std::cerr << "There is no movie with given id";
			return;
		}

		Movie updateData = mapper.mapFromDto(dto);

		movieRepository.updateMovieById(id, updateData);

	}

	void deleteMovieById(int id) {

		if (!movieRepository.existsById(id)) {
			std::cerr << "There is no movie with given id";
			return;
		}

		movieRepository.deleteMovieById(id);

	}


};

