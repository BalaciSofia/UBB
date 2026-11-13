create database labtest
go

create table RentalCompany(
	companyid int primary key
)

create table Warehouse(
	warehouseid int primary key,
	Wname varchar(50),
	loc varchar(50),
	companyid int foreign key references RentalCompany(companyid)
)

create table Customers(
	customerid int primary key,
	taxid int,
	balance decimal(10,2)
)

create table Contracts(
	contractId int primary key,
    customerId int foreign key references Customers(customerId),
    warehouseId int foreign key references Warehouse(warehouseId),
    monthlyFee decimal(10,2) ,
    isActive int --
)
go

create proc p2 (@customerId int)
as
begin
    select noContracts = count(*),sumMonthlyFees=sum(monthlyFee)
    from Contracts 
    where customerId=@customerId;
end
go


create view p3
as
    select c.taxId,c.balance,w.wName,ct.monthlyFee
    from Customers c
    inner join Contracts ct on ct.customerId = c.customerId
    inner join Warehouse w on w.warehouseId = ct.warehouseId
go

create function p4(@companyId int)
returns table as return
(
    select c.taxId,w.loc,activeContractCount = count(*)
    from Contracts ct
    inner join Customers c on c.customerId = ct.customerId
    inner join Warehouse w on w.warehouseId = ct.warehouseId
    where w.companyId = @companyId and ct.isActive = 1
    group by c.taxId, w.loc
);
go
