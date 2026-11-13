USE mockZooManagement
GO

CREATE or ALTER PROCEDURE InsertStaffHabitatPartial
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
    DECLARE @NewHabitatID INT = NULL;
    DECLARE @NewStaffID   INT = NULL;

    --insert habitat
    BEGIN TRY
        BEGIN TRANSACTION;
            INSERT INTO Habitats (Name, Climate, AreaSize)
            VALUES (@HabitatName, @Climate, @AreaSize);
            SET @NewHabitatID = SCOPE_IDENTITY();
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
    END CATCH;

    --insert staff
    BEGIN TRY
        BEGIN TRANSACTION;
            INSERT INTO Staff (FirstName, LastName, Role, HireDate)
            VALUES (@FirstName, @LastName, @Role, @HireDate);
            SET @NewStaffID = SCOPE_IDENTITY();
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
    END CATCH;

    --if staff and habitat got inserted
    IF @NewHabitatID IS NOT NULL AND @NewStaffID IS NOT NULL
    BEGIN
        BEGIN TRY
            BEGIN TRANSACTION;
                INSERT INTO StaffHabitat (StaffID, HabitatID, AssignedDate)
                VALUES (@NewStaffID, @NewHabitatID, @AssignedDate);
            COMMIT TRANSACTION;
        END TRY
        BEGIN CATCH
            ROLLBACK TRANSACTION;
        END CATCH;
    END
END;

DELETE FROM Habitats;
DELETE FROM Staff;
DELETE FROM StaffHabitat;

--case 1: valid
EXEC InsertStaffHabitatPartial
    @HabitatName  = 'Savanna',
    @Climate      = 'Tropical',
    @AreaSize     = 300.00,        
    @FirstName    = 'Ana',
    @LastName     = 'Popescu',
    @Role         = 'Ranger',
    @HireDate     = '2024-01-10',
    @AssignedDate = '2024-02-01';

SELECT * FROM Habitats;
SELECT * FROM Staff;
SELECT * FROM StaffHabitat;

DELETE FROM Habitats;
DELETE FROM Staff;
DELETE FROM StaffHabitat;

--case 2: habitat fails(area>50), staff succedes, link is skiped

EXEC InsertStaffHabitatPartial
    @HabitatName  = 'Tiny Pond',
    @Climate      = 'Temperate',
    @AreaSize     = 10.00,         
    @FirstName    = 'Ion',
    @LastName     = 'Ionescu',
    @Role         = 'Biologist',
    @HireDate     = '2024-03-01',
    @AssignedDate = '2024-03-15';

SELECT * FROM Habitats;
SELECT * FROM Staff;
SELECT * FROM StaffHabitat;

DELETE FROM Habitats;
DELETE FROM Staff;
DELETE FROM StaffHabitat;
--case 3: habitat succeeds, staff fails(not null name), link is skiped

EXEC InsertStaffHabitatPartial
    @HabitatName  = 'Arctic Tundra',
    @Climate      = 'Polar',
    @AreaSize     = 500.00,        
    @FirstName    = NULL,          
    @LastName     = 'Gheorghe',
    @Role         = 'Vet',
    @HireDate     = '2024-05-01',
    @AssignedDate = '2024-06-01';

SELECT * FROM Habitats;
SELECT * FROM Staff;
SELECT * FROM StaffHabitat;

DELETE FROM Habitats;
DELETE FROM Staff;
DELETE FROM StaffHabitat;
--case 4: habitat fails, staff fails, link skiped

EXEC InsertStaffHabitatPartial
    @HabitatName  = 'Swamp',
    @Climate      = 'Humid',
    @AreaSize     = 5.00,         
    @FirstName    = NULL,          
    @LastName     = 'Popa',
    @Role         = 'Keeper',
    @HireDate     = '2024-07-01',
    @AssignedDate = '2024-08-01';

SELECT * FROM Habitats;
SELECT * FROM Staff;
SELECT * FROM StaffHabitat;

