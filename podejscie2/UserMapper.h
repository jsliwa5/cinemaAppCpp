#pragma once
#include "User.h"
#include "RequestUserDto.h"

class UserMapper {
public:
    UserMapper() = default;

    static User mapFromDto(const RequestUserDto& dto) {
        return User(
            dto.firstName,
            dto.lastName,
            dto.email,
            dto.dateOfRegistration
        );
    }
};
