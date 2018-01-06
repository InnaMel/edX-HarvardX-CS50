from cs50 import *

# if number x2 more then 10, it must sum to achieve simple digit


def checkSummX2(check):
    while check >= 10:
        check = (check // 10) + (check % 10)
    return check


def main():
    num = -1
    quantEven = 0
    quantOdd = 0
    inchNum = 0
    even = False

    # ask user enter digits of the card
    while num < 0:
        print("Number:", end=' ')
        num = get_int()
        if num > 0:
            break

    # for future using
    numFull = num

    # sum odd and even digits separately
    while num > 0:
        if even == False:
            quantOdd = quantOdd + num % 10
            even = True
        else:
            quantEven = quantEven + checkSummX2((num % 10) * 2)
            even = False
        inchNum = inchNum + 1
        num = num // 10

    # checking for satisfaction of condition
    if inchNum < 13 or inchNum > 16 or (not ((quantOdd + quantEven) % 10) == 0):
        print("INVALID")
    elif (inchNum == 15) and (numFull // 10000000000000 == 34 or numFull // 10000000000000 == 37):
        print("AMEX")
    elif inchNum == 16 and (numFull // 100000000000000 == 51 or numFull // 100000000000000 == 52 or numFull // 100000000000000 == 53 or numFull // 100000000000000 == 54 or numFull // 100000000000000 == 55):
        print("MASTERCARD")
    elif (inchNum == 13 and numFull // 1000000000000 == 4) or (inchNum == 16 and numFull // 1000000000000000 == 4):
        print("VISA")


# delegate my method to master method
if __name__ == "__main__":
    main()