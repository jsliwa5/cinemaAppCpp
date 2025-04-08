#pragma once
#include "ShowingRepository.h"
#include "ShowingMapper.h"
#include "RequestShowingDto.h"

class ShowingService
{
private:
    ShowingRepository showingRepository;
    ShowingMapper mapper;

public:
    void saveShowing(const RequestShowingDto& dto) {
        Showing showingToBeSaved = mapper.mapFromDto(dto);
        showingRepository.saveShowing(showingToBeSaved);
    }

    Showing findShowingById(int id) {
        auto found = showingRepository.findShowingById(id);
        if (found.has_value()) {
            return found.value();
        }
        std::cerr << "There is no showing with the given id.\n";
        return Showing();
    }

    void updateShowingById(int id, const RequestShowingDto& dto) {
        if (!showingRepository.existsById(id)) {
            std::cerr << "There is no showing with the given id.\n";
            return;
        }

        Showing updateData = mapper.mapFromDto(dto);
        showingRepository.updateShowingById(id, updateData);
    }

    void deleteShowingById(int id) {
        if (!showingRepository.existsById(id)) {
            std::cerr << "There is no showing with the given id.\n";
            return;
        }

        showingRepository.deleteShowingById(id);
    }
};


