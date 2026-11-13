#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
from src.ui import main_loop
from src.functions import run_all_tests

run_all_tests()
main_loop()