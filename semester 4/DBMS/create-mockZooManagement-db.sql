use mockZooManagement

 CREATE TABLE Habitats (
    HabitatID INT IDENTITY(1,1) PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Climate VARCHAR(50) NOT NULL,        
    AreaSize DECIMAL(10,2) CHECK (AreaSize >= 50) 
);CREATE TABLE Staff (
    StaffID INT IDENTITY(1,1) PRIMARY KEY,
    FirstName VARCHAR(50) NOT NULL,
    LastName VARCHAR(50) NOT NULL,
    Role VARCHAR(50) NOT NULL,  
    HireDate DATE 
);
CREATE TABLE StaffHabitat (
    StaffID INT,
    HabitatID INT,
    AssignedDate DATE,
    PRIMARY KEY (StaffID, HabitatID),
    FOREIGN KEY (StaffID) REFERENCES Staff(StaffID) on UPDATE CASCADE on DELETE CASCADE,
    FOREIGN KEY (HabitatID) REFERENCES Habitats(HabitatID) on UPDATE CASCADE on DELETE CASCADE
);

