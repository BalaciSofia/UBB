create database company
use company

create table taskTypes(
	taskTypeID int primary key identity(1,1),
	name varchar(20) CHECK (name IN('technical', 'bug', 'improvement'))
);

create table taskPriorities(
	taskPriorityID int primary key identity(1,1),
	name varchar(20) CHECK (name IN('critical', 'show-stopper', 'minor','trivial'))
);

create table status(
	statusID int primary key identity(1,1),
	name varchar(20) CHECK (name IN('started', 'in progress', 'closed'))
);

create table developers(
	devID int primary key identity(1,1),
	firstName varchar(20),
	lastname varchar(20)
);
create table projects(
	projectID int primary key identity(1,1),
	startdate date,
	enddate date
);
create table tasks(
	projectID int,
	taskID int primary key identity(1,1),
	title varchar(20),
	descriptiom varchar(20),
	taskTypeID int,
	taskPriorityID int,
	taskStatusID int,
	FOREIGN KEY (taskTypeID) REFERENCES taskTypes(taskTypeID) on UPDATE CASCADE on DELETE CASCADE,
	FOREIGN KEY (taskPriorityID) REFERENCES taskPriorities(taskPriorityID) on UPDATE CASCADE on DELETE CASCADE,
	FOREIGN KEY (taskStatusID) REFERENCES status(statusID) on UPDATE CASCADE on DELETE CASCADE,
	FOREIGN KEY (projectID) REFERENCES projects(projectID) on UPDATE CASCADE on DELETE CASCADE,
);

create table devHasTask(
	assignTask int primary key identity(1,1),
	taskID int,
	devID int,
	FOREIGN KEY (taskID) REFERENCES tasks(taskID) on UPDATE CASCADE on DELETE CASCADE,
	FOREIGN KEY (devID) REFERENCES developers(devID) on UPDATE CASCADE on DELETE CASCADE,
)


insert into taskTypes (name) values ('technical'),('bug'),('improvement');

