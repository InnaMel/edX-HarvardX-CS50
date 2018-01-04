import cs50
import sys
# from cs50 import * or like this (just get_int)

# for enter in cycle while
height = -1

while height < 0 or height > 23:
    print("Height: ", end=' ')
    height = cs50.get_int()

    # check entered - is the number positive?
    if height > 0 and height < 23:

        # "break" only for loop
        break

# sys.exit() - exit from program
if height == 0:
    sys.exit()
elif not height == 0:
    space = height - 1

    # painting 0.5 of pyramid
    for i in range(height):
        if height == 1:
            print("#" * 2)
        elif space == 0:
            print("#" * (i + 2))
        else:
            print('{0}{1}'.format(' ' * space, "#" * (i + 2)))
            space = space - 1