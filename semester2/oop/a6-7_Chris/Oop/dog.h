#pragma once
#include <string>

class Dog {
private:
    std::string breed;
    std::string name;
    int age;
    std::string photo_link;
public:
    Dog(const std::string& breed, const std::string& name, int age, const std::string& photo_link);
    Dog() = default;
    std::string get_breed();
    std::string get_name();
    int get_age() const;
    std::string get_photo_link();
    void set_breed(const std::string& breed);
    void set_name(const std::string& name);
    void set_age(int age);
    void set_photo_link(const std::string& photo_link);
    std::string to_string() const;
    bool operator==(const Dog& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
    friend std::istream& operator>>(std::istream& is, Dog& dog);
};

class ValidationError : public std::exception {
private:
    std::string message;
public:
    explicit ValidationError(const std::string& message_) : message{message_} {}
    const char* what() {
        return this->message.c_str();
    }
};

class Validator {
public:
    Validator() = default;
    void validate(Dog dog) const;
};