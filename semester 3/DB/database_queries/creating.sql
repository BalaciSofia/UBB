use ZooManagement;

-- Habitats 

CREATE TABLE Habitats (
    HabitatID INT IDENTITY(1,1) PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Climate VARCHAR(50) NOT NULL,        
    AreaSize DECIMAL(10,2) CHECK (AreaSize >= 50) 
);
select * from Habitats
-- Species (each species to one habitat)

CREATE TABLE Species (
    SpeciesID INT IDENTITY(1,1) PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Classification VARCHAR(50) NOT NULL,
    DietType VARCHAR(50) check (DietType='omnivore' OR DietType='carnivore' OR DietType='herbivore'),
    HabitatID INT,
    FOREIGN KEY (HabitatID) REFERENCES Habitats(HabitatID) on UPDATE CASCADE on DELETE CASCADE
);

-- Food 
CREATE TABLE Food (
    FoodID INT IDENTITY(1,1) PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Type VARCHAR(50) NOT NULL,
    QuantityInStock INT CHECK(QuantityInStock>=0)
);

-- Animals (each animal belongs to one species)
CREATE TABLE Animals (
    AnimalID INT IDENTITY(1,1) PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Age INT CHECK (Age >= 0),
    Gender VARCHAR(10) CHECK (Gender='M' OR Gender='F' OR Gender='N'),
    SpeciesID INT,
    FoodID INT,
    FOREIGN KEY (SpeciesID) REFERENCES Species(SpeciesID) on UPDATE CASCADE on DELETE CASCADE,
    FOREIGN KEY (FoodID) REFERENCES Food(FoodID) on UPDATE CASCADE on DELETE CASCADE
    );

-- Staff
CREATE TABLE Staff (
    StaffID INT IDENTITY(1,1) PRIMARY KEY,
    FirstName VARCHAR(50) NOT NULL,
    LastName VARCHAR(50) NOT NULL,
    Role VARCHAR(50) NOT NULL,  
    HireDate DATE 
);

-- StaffHabitat (many-to-many: staff <-> habitats)
CREATE TABLE StaffHabitat (
    StaffID INT,
    HabitatID INT,
    AssignedDate DATE,
    PRIMARY KEY (StaffID, HabitatID),
    FOREIGN KEY (StaffID) REFERENCES Staff(StaffID) on UPDATE CASCADE on DELETE CASCADE,
    FOREIGN KEY (HabitatID) REFERENCES Habitats(HabitatID) on UPDATE CASCADE on DELETE CASCADE
);


-- Visitors 
CREATE TABLE Visitors (
    VisitorID INT IDENTITY(1,1) PRIMARY KEY,
    FirstName VARCHAR(50) NOT NULL,
    LastName VARCHAR(50) NOT NULL,
    Age INT
);

-- Donations (visitor -> donations) (one visitor can make many donations)
CREATE TABLE Donations (
    DonationID INT IDENTITY(1,1) PRIMARY KEY,
    VisitorID INT,
    Amount DECIMAL(10,2),
    DonationDate DATETIME,
    Purpose VARCHAR(150) NOT NULL,
    FOREIGN KEY (VisitorID) REFERENCES Visitors(VisitorID) on UPDATE CASCADE on DELETE CASCADE
);

-- Shop 
CREATE TABLE Shop (
    ProductID INT IDENTITY(1,1) PRIMARY KEY,
    ProductName VARCHAR(150) NOT NULL,
    Price DECIMAL(10,2),
    Stock INT,
    CustomerID INT,
    FOREIGN KEY (CustomerID) REFERENCES Visitors(VisitorID) on UPDATE CASCADE on DELETE CASCADE
);

-- Events (linked to Habitat)

CREATE TABLE Events (
    EventID INT IDENTITY(1,1) PRIMARY KEY,
    Name VARCHAR(150) UNIQUE,
    Description VARCHAR(300) NOT NULL,
    EventDate DATETIME,
    HabitatID INT,
    FOREIGN KEY (HabitatID) REFERENCES Habitats(HabitatID) on UPDATE CASCADE on DELETE CASCADE
);

CREATE TABLE Performs (
    AnimalID INT,
    EventID INT,
    Duration INT,
    PRIMARY KEY (AnimalID, EventID),
    FOREIGN KEY (AnimalID) REFERENCES Animals(AnimalID) on UPDATE CASCADE on DELETE CASCADE,
    FOREIGN KEY (EventID) REFERENCES Events(EventID) on UPDATE CASCADE on DELETE CASCADE
);

drop table Performs

CREATE TABLE VersionHandler(
    versionNo INT NOT NULL
);

-- initial version 0
INSERT INTO VersionHandler VALUES (0);

