#pragma once
#include "Movie.h"
#include "RequestMovieDto.h"
#include <string>

class MovieMapper
{
public:

	MovieMapper() = default;

	static Movie mapFromDto(const RequestMovieDto& dto) {

		return Movie(dto.title, dto.description, dto.director,
			dto.yearOfRelease, dto.duration, dto.genre);

	}

};

