USE mockZooManagement
GO
DROP PROCEDURE IF EXISTS InsertStaffHabitat;
go
CREATE OR ALTER PROCEDURE InsertStaffHabitat
    @HabitatName VARCHAR(100),
    @Climate VARCHAR(50),
    @AreaSize DECIMAL(10,2),

    @FirstName VARCHAR(50),
    @LastName VARCHAR(50),
    @Role VARCHAR(50),
    @HireDate DATE,

    @AssignedDate DATE
AS
BEGIN
    DECLARE @NewHabitatID INT;
    DECLARE @NewStaffID INT;

    BEGIN TRY
        BEGIN TRANSACTION;

            INSERT INTO Habitats (Name, Climate, AreaSize)
            VALUES (@HabitatName, @Climate, @AreaSize);
            SET @NewHabitatID = SCOPE_IDENTITY();

            INSERT INTO Staff (FirstName, LastName, Role, HireDate)
            VALUES (@FirstName, @LastName, @Role, @HireDate);
            SET @NewStaffID = SCOPE_IDENTITY();

            INSERT INTO StaffHabitat (StaffID, HabitatID, AssignedDate)
            VALUES (@NewStaffID, @NewHabitatID, @AssignedDate);

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
        THROW;
    END CATCH
END;

DELETE FROM Habitats;
DELETE FROM Staff;
DELETE FROM StaffHabitat;

----------------good case, no rollback
EXEC InsertStaffHabitat
    @HabitatName  = 'Amazon Rainforest',
    @Climate      = 'Tropical',
    @AreaSize     = 500.00,
    @FirstName    = 'Ana',
    @LastName     = 'Popescu',
    @Role         = 'Biologist',
    @HireDate     = '2026-03-15',
    @AssignedDate = '2026-04-01';
    
SELECT * FROM Habitats;
SELECT * FROM Staff;
SELECT * FROM StaffHabitat;

-----------------bad case, area must be >=50
EXEC InsertStaffHabitat
    @HabitatName  = 'Desert',
    @Climate      = 'Arid',
    @AreaSize     = 10.00,       
    @FirstName    = 'Ion',
    @LastName     = 'Ionescu',
    @Role         = 'Ranger',
    @HireDate     = '2026-01-01',
    @AssignedDate = '2026-02-01';

SELECT * FROM Habitats;
SELECT * FROM Staff;
SELECT * FROM StaffHabitat;