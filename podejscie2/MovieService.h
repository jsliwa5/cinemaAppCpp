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

		Movie movieToBeSaved = mapper.mapFromDto(dto);
		movieRepository.saveMovie(movieToBeSaved);

	}

	Movie findMovieByTitle(std::string title) {
		return movieRepository.findMovieByTitle(title).value();
	}


};

