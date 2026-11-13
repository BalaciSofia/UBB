class IdNotInteger(Exception):
    def __init__(self, msg):
        self.__msg = msg

    def get_msg(self):
        return self.__msg

class ServiceError(Exception):
    def __init__(self, msg):
        self.__msg = msg

    def get_msg(self):
        return self.__msg
