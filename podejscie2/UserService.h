#pragma once
#include "UserRepository.h"
#include "UserMapper.h"
#include "RequestUserDto.h"

class UserService
{
private:
    UserRepository userRepository;
    UserMapper mapper;

public:
    void saveUser(const RequestUserDto& dto) {
        User userToBeSaved = mapper.mapFromDto(dto);
        userRepository.saveUser(userToBeSaved);
    }

    User findUserById(int id) {
        auto found = userRepository.findUserById(id);
        if (found.has_value()) {
            return found.value();
        }
        std::cerr << "There is no user with the given id.\n";
        return User();
    }

    User findUserByLastName(const std::string& lastName) {
        auto found = userRepository.findUserByLastName(lastName);
        if (found.has_value()) {
            return found.value();
        }
        std::cerr << "There is no user with the given last name.\n";
        return User();
    }

    void updateUserById(int id, const RequestUserDto& dto) {
        if (!userRepository.existsById(id)) {
            std::cerr << "There is no user with the given id.\n";
            return;
        }

        User updateData = mapper.mapFromDto(dto);
        userRepository.updateUserById(id, updateData);
    }

    void deleteUserById(int id) {
        if (!userRepository.existsById(id)) {
            std::cerr << "There is no user with the given id.\n";
            return;
        }

        userRepository.deleteUserById(id);
    }
};


