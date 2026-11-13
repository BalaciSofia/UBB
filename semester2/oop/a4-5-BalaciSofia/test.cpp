
#include "test.h"
#include <cassert>
#include <typeinfo>
#include "domain.h"
#include "dynamicarray.h"
#include "repo.h"
#include "controller_admin.h"
#include "controller_user.h"


//test for domain-----------------------------------------------------------------------------------
void Test::test_constructor_dog() {
    // Test default constructor
    Dog dog;
    assert(typeid(dog) == typeid(Dog));
    assert(dog.get_breed() == " ");
    assert(dog.get_name() == " ");
    assert(dog.get_photograph() == " ");
    assert(dog.get_age() == 0);

    // Test constructor
    Dog dog2("dog", "mimi", 2, "no");
    assert(dog2.get_breed() == "dog");
    assert(dog2.get_name() == "mimi");
    assert(dog2.get_photograph() == "no");
    assert(dog2.get_age() == 2);
}

void Test::test_get_dog() {
    //test geters
    Dog dog("dog", "mimi", 2, "no");
    assert(dog.get_breed() == "dog");
    assert(dog.get_name() == "mimi");
    assert(dog.get_photograph() == "no");
    assert(dog.get_age() == 2);
}

void Test::test_set_dog() {
    //test seters
    Dog dog("dog", "mimi", 2, "no");
    dog.update_age(3);
    dog.update_name("titi");
    dog.update_photograph("photo");
    assert(dog.get_breed() == "dog");
    assert(dog.get_name() == "titi");
    assert(dog.get_photograph() == "photo");
    assert(dog.get_age() == 3);
}

void Test::test_operator() {
    //test operators
    Dog dog1("dog", "mimi", 2, "no");
    Dog dog2("dog", "mimi", 2, "no");
    Dog dog3("dog", "titi", 3, "photo");

    // Test equality operator
    assert(dog1 == dog2);
    assert(!(dog1 == dog3));

    // Test assignment operator
    Dog dog4 = dog1;
    assert(dog4 == dog1);
    dog3 = dog1;
    assert(dog3 == dog1);

    // Test self-assignment edge case
    dog1 = dog1;
    assert(dog1 == dog4); // Should remain unchanged
}

void Test:: test_dog() {
    test_constructor_dog();
    test_get_dog();
    test_set_dog();
    test_operator();
}


//test for dynamic array---------------------------------------------------------------------
void Test:: test_dynamic_array() {
    DynamicArray<int> a;
    assert(a.getSize()==0);
    assert(a.getCapacity()==1);
    //test append
    a.append(1);
    a.append(2);
    assert(a.getSize()==2);
    assert(a.getCapacity()==2);
    assert(a[0]==1);
    assert(a[1]==2);
    a.append(3);
    a.remove_index(0);
    assert(a.getSize()==2);
    assert(a.getCapacity()==4);
    assert(a[0]==2);
    assert(a[1]==3);
    a.remove_index(0);
    assert(a.getSize()==1);
    assert(a.getCapacity()==4);
    DynamicArray<int> b;
    b.append(100);
    b.append(200);
    b = a;
    assert(b.getSize() == a.getSize());
    assert(b.getCapacity() == a.getCapacity());
    assert(b[0] == a[0]);
    a = a;
    assert(a.getSize() == 1);
    assert(a.getCapacity() == 4);
}

//test repo-------------------------------------------------------------------------------
void Test::test_create_add_remove_repo() {
    //constructor
    Repository r;
    assert(r.get_dogs().getSize()==0);
    assert(r.get_dogs().getCapacity()==1);

    //adding dog
    r.add_dog(Dog("dog","mimi",2,"no"));
    assert(r.get_dogs().getSize()==1);
    assert(r.get_dogs().getCapacity()==1);
    r.add_dog(Dog("dog1","titi",2,"no"));
    assert(r.get_dogs().getSize()==2);
    assert(r.get_dogs().getCapacity()==2);

    //try adding dog that already exists
    try {
        r.add_dog(Dog("dog1","titi",2,"no"));
        assert(false);
    }
    catch (std::logic_error) {
        assert(true);
    }

    //remove dog
    r.remove_dog(Dog("dog1","titi",2,"no"));
    assert(r.get_dogs().getSize()==1);
    assert(r.get_dogs().getCapacity()==2);

    //try removing dog that does not exist
    try {
        r.remove_dog(Dog("dog1","titi",2,"no"));
        assert(false);
    }
    catch (const std::logic_error&) {
        assert(true);
    }
}

void Test::test_update_search_repo() {
    Repository r;
    r.add_dog(Dog("dog","mimi",2,"no"));
    r.add_dog(Dog("dog1","titi",2,"no"));
    r.add_dog(Dog("dog3","riri",3,"no"));
    assert(r.search_dog_name("titi")==1);
    assert(r.search_dog_name("r")==-1);
    assert(r.get_dogs().getSize()==3);
    assert(r.get_dogs().getCapacity()==4);
    assert(r.get_dogs()[0].get_name()=="mimi");
    assert(r.get_dogs()[1].get_name()=="titi");
    assert(r.get_dogs()[2].get_name()=="riri");
    r.update_dog_name(r.get_dogs()[0],"caca");
    assert(r.get_dogs()[0].get_name()=="caca");
    assert(r.get_dogs()[1].get_age()==2);
    r.update_dog_age(r.get_dogs()[1],6);
    assert(r.get_dogs()[1].get_age()==6);
    assert(r.get_dogs()[2].get_photograph()=="no");
    r.update_dog_photograph(r.get_dogs()[2],"yes");
    assert(r.get_dogs()[2].get_photograph()=="yes");
}
void Test::test_get_current_dog_repo() {
    Repository repo;
    Dog dog1("Golden Retriever","Buddy", 3, "no");
    Dog dog2("Beagle","Charlie", 2, "no");

    repo.add_dog(dog1);
    repo.add_dog(dog2);

    assert(repo.get_current_dog_repo(0).get_name() == "Buddy");
    assert(repo.get_current_dog_repo(1).get_name() == "Charlie");
}

void Test::test_add_dog_adopted_repo() {
    Repository repo;
    Dog dog1( "Labrador", "Max" ,4, "no");

    repo.add_dog_adopted(dog1);
    assert(repo.get_adopted_dogs().getSize() == 1);
    assert(repo.get_adopted_dogs()[0].get_name() == "Max");
}

void Test::test_get_adopted_dogs_repo() {
    Repository repo;
    Dog dog1("Bulldog","Rocky" , 5, "no");
    Dog dog2("Poodle","Bella" ,3, "no");

    repo.add_dog_adopted(dog1);
    repo.add_dog_adopted(dog2);

    DynamicArray<Dog>& adopted = repo.get_adopted_dogs();
    assert(adopted.getSize() == 2);
    assert(adopted[0].get_name() == "Rocky");
    assert(adopted[1].get_name() == "Bella");
}

void Test::test_repo() {
    test_create_add_remove_repo();
    test_update_search_repo();
    test_get_current_dog_repo();
    test_add_dog_adopted_repo();
    test_get_adopted_dogs_repo();
}


//test controller admin-------------------------------------------------------------------------
void Test::test_controller_admin() {
    Repository r;
    Controller_admin admin(r);

    //Test Add_Dog
    admin.Add_Dog(2, "mimi", "dog", "no");
    admin.Add_Dog(2, "titi", "dog", "no");
    assert(admin.get_dogs_controller()[0] == Dog("dog", "mimi", 2, "no"));
    assert(admin.get_dogs_controller()[1] == Dog("dog", "titi", 2, "no"));
    assert(admin.get_dogs_controller().getSize() == 2);

    //Test Remove_Dog
    admin.Remove_Dog("mimi");
    assert(admin.get_dogs_controller().getSize() == 1);

    //Test Remove_Dog with Nonexistent Dog (Exception)
    try {
        admin.Remove_Dog("mimi");
        assert(false);
    } catch (const std::logic_error &e) {
        assert(std::string(e.what()) == "Dog not found");
    }

    //Test Search_name
    assert(admin.Search_name("titi") != -1);
    assert(admin.Search_name("me") == -1);

    // Test Update_name
    admin.Update_name("titi", "rex");
    assert(admin.Search_name("titi") == -1);
    assert(admin.Search_name("rex") != -1);

    //Test Update_name with Nonexistent Dog (Exception)
    try {
        admin.Update_name("ghost", "new_name");
        assert(false);
    } catch (const std::logic_error &e) {
        assert(std::string(e.what()) == "Dog not found");
    }

    //Test Update_age
    admin.Update_age("rex", 5);
    assert(admin.get_dogs_controller()[0].get_age() == 5);

    //Test Update_age with Nonexistent Dog (Exception)
    try {
        admin.Update_age("ghost", 10);
        assert(false);
    } catch (const std::logic_error &e) {
        assert(std::string(e.what()) == "Dog not found");
    }

    //Test Update_photograph
    admin.Update_photograph("rex", "new_photo");
    assert(admin.get_dogs_controller()[0].get_photograph() == "new_photo");

    //Test Update_photograph with Nonexistent Dog (Exception)
    try {
        admin.Update_photograph("ghost", "new_photo");
        assert(false);
    } catch (const std::logic_error &e) {
        assert(std::string(e.what()) == "Dog not found");
    }

    //Test initial_data
    admin.initial_data();
    assert(admin.get_dogs_controller().getSize() == 20 + 1);
}
//test controller user-----------------------------------------------------------------------
void Test::test_get_current_dog_controller_user() {
    Repository repo;
    Controller_user controller(repo);
    Dog dog1("Bulldog", "Max", 3, "image1.jpg");
    repo.add_dog(dog1);
    assert(controller.get_current_dog_controller(0) == dog1);
}

void Test::test_get_adopted_dogs_controller_user() {
    Repository repo;
    Controller_user controller(repo);
    Dog dog1("Bulldog", "Max", 3, "image1.jpg");
    controller.add_dog_adoptedlist(dog1);
    assert(controller.get_adopted_dogs_controller().getSize() == 1);
}

void Test::test_add_dog_adoptedlist() {
    Repository repo;
    Controller_user controller(repo);
    Dog dog1("Bulldog", "Max", 3, "image1.jpg");
    controller.add_dog_adoptedlist(dog1);
    assert(controller.get_adopted_dogs_controller()[0] == dog1);
}

void Test::test_filter_breed() {
    Repository repo;
    Controller_user controller(repo);
    DynamicArray<Dog> dogs;
    dogs.append(Dog("Bulldog", "Max", 3, "image1.jpg"));
    dogs.append(Dog("Labrador", "Buddy", 2, "image2.jpg"));
    dogs.append(Dog("Bulldog", "Charlie", 4, "image3.jpg"));

    DynamicArray<Dog> filtered = controller.filter_breed(dogs, "Bulldog");
    assert(filtered.getSize() == 2);
    assert(filtered[0].get_name() == "Max");
    assert(filtered[1].get_name() == "Charlie");
}

void Test::test_filter_age() {
    Repository repo;
    Controller_user controller(repo);
    DynamicArray<Dog> dogs;
    dogs.append(Dog("Bulldog", "Max", 3, "image1.jpg"));
    dogs.append(Dog("Labrador", "Buddy", 2, "image2.jpg"));
    dogs.append(Dog("Bulldog", "Charlie", 4, "image3.jpg"));

    DynamicArray<Dog> filtered = controller.filter_age(dogs, 3);
    assert(filtered.getSize() == 2);
    assert(filtered[0].get_name() == "Max");
    assert(filtered[1].get_name() == "Buddy");
}

void Test::test_controller_user() {
    test_get_current_dog_controller_user();
    test_get_adopted_dogs_controller_user();
    test_add_dog_adoptedlist();
    test_filter_breed();
    test_filter_age();
}


////all tests////
void Test::test_all() {
    test_dog();
    test_dynamic_array();
    test_repo();
    test_controller_admin();
    test_controller_user();
}