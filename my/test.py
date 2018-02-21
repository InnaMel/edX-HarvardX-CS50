from cs50 import *
from datetime import datetime

print('date and time right now', datetime.now())

numeric = get_string()
#if type(numeric) == int:
if not numeric.isalpha():
    print('that is int')
else:
    print('this is not digits')