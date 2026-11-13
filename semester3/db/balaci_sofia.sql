

CREATE TABLE Species (
	SpeciesID INT IDENTITY(1,1) PRIMARY KEY,
	Name VARCHAR(100),
	Classification VARCHAR(50), 
	DietType VARCHAR(50)
);

CREATE TABLE Animals (
	AnimalID INT IDENTITY(1,1) PRIMARY KEY,
	Name VARCHAR(100),
	Age INT,
	Gender VARCHAR(10),
	SpeciesID INT,
	CONSTRAINT FK_Animal_Species FOREIGN KEY (SpeciesID) REFERENCES Species(SpeciesID)
);
