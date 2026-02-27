use ZooManagement;

INSERT INTO Habitats (Name, Climate, AreaSize)
VALUES
( 'Savannah Plains', 'Dry', 500.00),
( 'Rainforest Dome', 'Humid', 650.00),
( 'Arctic Zone', 'Cold', 400.00),
( 'Desert Habitat', 'Arid', 550.00),
( 'Mountain Enclosure', 'Temperate', 480.00);

INSERT INTO Habitats (Name, Climate, AreaSize)
VALUES
( 'Ecuatorial Desert', 'Dry', 400.00);
select * from Habitats

INSERT INTO Species (Name, Classification, DietType, HabitatID)
VALUES
( 'African Lion', 'Mammal', 'carnivore', 15),
( 'Elephant', 'Mammal', 'herbivore', 15),
( 'Green Anaconda', 'Reptile', 'carnivore', 16),
( 'Polar Bear', 'Mammal', 'omnivore', 17),
( 'Camel', 'Mammal', 'herbivore', 18);

INSERT INTO Food ( Name, Type, QuantityInStock)
VALUES
( 'Meat Mix', 'Animal Protein', 5000),
( 'Fresh Fruits', 'Plant', 3000),
( 'Fish', 'Animal Protein', 4000),
( 'Leafy Greens', 'Plant', 2500),
( 'Dry Hay', 'Plant', 3500);

INSERT INTO Animals (Name, Age, Gender, SpeciesID, FoodID)
VALUES
( 'Leo', 8, 'M', 2, 11),
( 'Nala', 6, 'F', 2, 12),
( 'Dumbo', 15, 'M', 3, 12),
( 'Slyther', 4, 'F', 4, 13),
( 'Snow', 10, 'F', 5, 13),
( 'Humpie', 12, 'M', 6, 15);

INSERT INTO Staff (FirstName, LastName, Role, HireDate)
VALUES
( 'Alice', 'Johnson', 'Zookeeper', '2018-05-12'),
( 'Bob', 'Smith', 'Veterinarian', '2019-03-22'),
( 'Clara', 'Brown', 'Guide', '2020-07-15'),
( 'David', 'White', 'Cleaner', '2021-02-10'),
( 'Ella', 'Green', 'Feeding Manager', '2017-11-05');

INSERT INTO StaffHabitat (StaffID, HabitatID, AssignedDate)
VALUES
(11, 15, '2020-01-15'),
(11, 16, '2021-04-10'),
(12, 17, '2020-09-25'),
(13, 18, '2021-08-01'),
(15, 19, '2019-10-20');

INSERT INTO Visitors ( FirstName, LastName, Age)
VALUES
( 'Tom', 'Anderson', 25),
( 'Mia', 'Lopez', 30),
( 'Jake', 'Carter', 19),
( 'Sophia', 'Wong', 45),
( 'Oliver', 'King', 35);

INSERT INTO Visitors ( FirstName, LastName, Age)
Values( 'Chris','Jones',20);

INSERT INTO Donations ( VisitorID, Amount, DonationDate, Purpose)
VALUES
( 11, 50.00, '2024-06-12 10:30:00', 'Elephant Care'),
( 12, 100.00, '2024-06-14 12:00:00', 'Habitat Expansion'),
( 13, 25.00, '2024-06-15 15:00:00', 'Animal Feeding'),
( 14, 75.00, '2024-06-20 09:45:00', 'Zoo Maintenance'),
( 15, 120.00, '2024-07-01 11:20:00', 'Medical Supplies');

INSERT INTO Shop ( ProductName, Price, Stock, CustomerID)
VALUES
( 'Zoo T-shirt', 15.99, 200, 11),
( 'Animal Plush Toy', 25.50, 150,12),
( 'Zoo Mug', 12.75, 100, 13),
( 'Safari Hat', 18.00, 80,14),
( 'Postcard Pack', 5.00, 300, 15);

INSERT INTO Events ( Name, Description, EventDate, HabitatID)
VALUES
( 'Lion Feeding Show', 'Watch the lions enjoy their daily meal.', '2024-08-12 14:00:00', 15),
( 'Rainforest Adventure', 'Guided walk through tropical habitats.', '2024-09-05 11:00:00', 16),
( 'Polar Bear Playtime', 'Interactive event with zookeepers.', '2024-10-10 13:00:00', 17),
( 'Desert Wonders', 'Learn about desert animals.', '2024-10-22 15:00:00', 18),
( 'Mountain Trek', 'Discover high-altitude wildlife.', '2024-11-15 10:00:00', 19);

INSERT INTO Performs (AnimalID, EventID, duration)
VALUES
(2,2,10),
(3,2,10),
(6,4,25),
(7,5,15);

select * from Performs 