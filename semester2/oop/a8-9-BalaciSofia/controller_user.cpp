
#include "controller_user.h"

#include "controller_admin.h"
#include <fstream>
Controller_user::Controller_user(Repository &repo,std::string filename) : repo(repo) ,filename(filename){ }

std::string Controller_user::get_file() {
    return this->filename;
}
Dog Controller_user::get_current_dog_controller(int i) {
    return this->repo.get_current_dog_repo(i);
}

std::vector<Dog>& Controller_user::get_adopted_dogs_controller() {
    return this->repo.get_adopted_dogs();
}

void Controller_user::add_dog_adoptedlist(Dog d) {
    this->repo.add_dog_adopted(d);
    this->write_to_file();
}

std::vector<Dog> Controller_user::filter_breed(std::vector<Dog> &r, std::string breed) {
    std::vector<Dog> dogs;
    for (int i = 0; i < r.size(); i++) {
        if (r[i].get_breed() == breed) {
            dogs.push_back(r[i]);
        }
    }
    return dogs;
}


std::vector<Dog> Controller_user::filter_age(std::vector<Dog> &r, int age) {
    std::vector<Dog> dogs;
    for (int i = 0; i < r.size(); i++) {
        if (r[i].get_age() <= age) {
            dogs.push_back(r[i]);
        }
    }
    return dogs;
}

Controller_CSV::Controller_CSV(Repository &repo, const std::string &filename) : Controller_user(repo, filename) {
    std::ofstream g(filename);
    g.close();
}

void Controller_CSV::write_to_file() {
    /*
     * Writes the adoption list to a CSV file
     */
    std::ofstream file(this->get_file());
    for (auto d : this->repo.get_adopted_dogs()) {
        file << d.get_breed() << "," << d.get_name() << "," << d.get_age() << "," << d.get_photograph() << "\n";
    }
    file.close();
}

Controller_HTML::Controller_HTML(Repository &repo, const std::string &filename) : Controller_user(repo, filename) {
    std::ofstream f(filename);
    f.close();
}

void Controller_HTML::write_to_file() {
    /*
     * Writes the adoption list to an HTML file
     */
    std::ofstream file(this->get_file());
    file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Adoption List</title>\n</head>\n<body>\n";
    file << "<table border=\"1\">\n";
    file << "<tr><th>Breed</th><th>Name</th><th>Age</th><th>Photo</th></tr>\n";

    for (auto d : this->repo.get_adopted_dogs()) {
        file << "<tr>";
        file << "<td>" << d.get_breed() << "</td>";
        file << "<td>" << d.get_name() << "</td>";
        file << "<td>" << d.get_age() << "</td>";
        file << "<td><a href=\"" << d.get_photograph() << "\">Link</a></td>";
        file << "</tr>\n";
    }

    file << "</table>\n</body>\n</html>";
    file.close();
}
