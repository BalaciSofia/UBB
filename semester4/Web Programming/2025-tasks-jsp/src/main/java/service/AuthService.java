package service;
import domain.User;
import repository.UserRepo;

import java.sql.SQLException;

public class AuthService {
    private UserRepo userRepository;

    public AuthService(UserRepo userRepository) {
        this.userRepository = userRepository;
    }

    public User authenticate(String username) throws SQLException {
        User user = userRepository.findByUsername(username);
        return user;
    }

}
