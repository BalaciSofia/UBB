from domain.assignment import Assignment

class Service:
    def __init__(self, repo):
        self.__repo = repo

    @property
    def get_repo(self):
        return self.__repo

    def check_id(self,id):
        """
        check is id is unique
        :param id: id to check
        :return: false if already exists, true otherwise
        """
        for asg in self.get_repo.get_assignments:
            if asg.get_id == id:
                return False
        return True

    def check_name(self,name):
        """
        check if name is valid
        :param name: name to check
        :return: false if name is too short, true otherwise
        """
        if len(name)<3:
            return False
        return True

    def check_solution(self,solution):
        """
        check if solution is valid
        :param solution: solution to check
        :return:false if solution is empty, true otherwise
        """
        if type(solution)!=str or solution=='':
            return False
        return True

    def add_assignment(self,id,name,solution):
        """
        Add assignment to repository
        :param id: assignement id
        :param name:   assignement name
        :param solution: assignement solution
        """
        if not self.check_id(id):
            raise ValueError("Assignment id already exists")
        if not self.check_name(name):
            raise ValueError("Name is too short")
        if not self.check_solution(solution):
            raise ValueError("Solution is empty")
        self.get_repo.add(Assignment(id,name,solution))

    def sort_by_id(self):
        return sorted(self.get_repo.get_assignments,key=lambda x:x.get_id)

    def calculate_similarity(self,solution1: str, solution2: str) -> float:
        words1 = solution1.lower().split()
        words2 = solution2.lower().split()
        common_words = 0
        for w in words1:
            if w in words2:
                common_words+=1
        similarity_percentage = ( common_words/ len(words2)) * 100
        return similarity_percentage

    def dishonesty_check(self):
        list_dishonesty=[]
        for asg1 in self.get_repo.get_assignments:
            for asg2 in self.get_repo.get_assignments:
                if asg1.get_id != asg2.get_id:
                    similarity = self.calculate_similarity(asg1.get_solution, asg2.get_solution)
                    if similarity >= 20:
                        list_dishonesty.append([asg1.get_name, asg2.get_name, similarity])
        return list_dishonesty


