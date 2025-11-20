from domain.assignment import Assignment


class AssignmentsRepo:
    def __init__(self,filename):
        self.__filename = filename
        self.__assignments = self.load()

    @property
    def get_assignments(self):
        return self.__assignments

    def load(self):
        assignments = []
        with open(self.__filename,'r') as f:
            lines = f.readlines()
            for line in lines:
                id,name,sol=line.split(',')
                id = int(id)
                sol = sol.strip()
                name = name.strip()
                asg=Assignment(id,name,sol)
                assignments.append(asg)
        return assignments

    def save(self):
        with open(self.__filename,'w') as f:
            for asg in self.get_assignments:
                f.write(f'{asg.get_id},{asg.get_name},{asg.get_solution}\n')

    def add(self,assignment):
        self.get_assignments.append(assignment)
        self.save()