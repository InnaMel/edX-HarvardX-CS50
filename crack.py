import cs50
import crypt
import sys


# taking hash
def main():
    global oldHash
    if not len(sys.argv) == 2:
        print('Give me some hash')
        sys.exit()
    elif len(sys.argv) == 2:
        oldHash = sys.argv[1]

    # take salt from hash (first two characters)
    global salt
    salt = []
    for i in range(2):
        salt.append(oldHash[i])
    #print('salt is ', salt)

    # now salt is string = '50' - we need is string because cryp(string, string)
    salt = salt[0] + salt[1]

    if checkKey0() == True:
        sys.exit()
    if checkKey1() == True:
        sys.exit()
    if checkKey2() == True:
        sys.exit()
    if checkKey3() == True:
        sys.exit()


def checkNewHash(myKey):
    myKey = ''.join(myKey)
    newCheck = True
    newHash = crypt.crypt(myKey, salt)
    if oldHash == newHash:
        print(myKey)
        newCheck = True
    else:
        newCheck = False
    return newCheck

# check by 1 letter ****************************************************************


def checkKey0():
    check = False
    myKey = ['a']
    for i in range(97, 123):
        #cheking in lowercase
        myKey[0] = chr(i)
        check = checkNewHash(myKey)
        if check == True:
            break

        #cheking in uppercase
        myKey[0] = myKey[0].upper()
        check = checkNewHash(myKey)
        if check == True:
            break
    return check

# check by 2 letter ****************************************************************


def checkKey1():
    check = False
    myKey = ['a', 'b']
    for i in range(97, 123):
        for j in range(97, 123):

            # cheking both in lowercase
            myKey[0] = chr(i)
            myKey[1] = chr(j)

            check = checkNewHash(myKey)
            if check == True:
                break

            # cheking in aB uppercase
            myKey[0] = chr(i)
            myKey[1] = chr(j).upper()
            check = checkNewHash(myKey)
            if check == True:
                break

            # cheking in Ab uppercase
            myKey[0] = chr(i).upper()
            myKey[1] = chr(j)
            check = checkNewHash(myKey)
            if check == True:
                break

            # cheking in AB uppercase
            myKey[0] = chr(i).upper()
            myKey[1] = chr(j).upper()
            check = checkNewHash(myKey)
            if check == True:
                break

        if check == True:
            break
    return check

# check by 3 letter ****************************************************************


def checkKey2():
    check = False
    myKey = ['a', 'b', 'c']
    for i in range(97, 123):
        for j in range(97, 123):
            for k in range(97, 123):
                # cheking both in lowercase
                myKey[0] = chr(i)
                myKey[1] = chr(j)
                myKey[2] = chr(k)
                check = checkNewHash(myKey)
                if check == True:
                    break

                # cheking in Abc
                myKey[0] = chr(i).upper()
                myKey[1] = chr(j)
                myKey[2] = chr(k)
                check = checkNewHash(myKey)
                if check == True:
                    break

                # cheking in aBc
                myKey[0] = chr(i)
                myKey[1] = chr(j).upper()
                myKey[2] = chr(k)
                check = checkNewHash(myKey)
                if check == True:
                    break

                # cheking in abC
                myKey[0] = chr(i)
                myKey[1] = chr(j)
                myKey[2] = chr(k).upper()
                check = checkNewHash(myKey)
                if check == True:
                    break

                # cheking both in ABC
                myKey[0] = chr(i).upper()
                myKey[1] = chr(j).upper()
                myKey[2] = chr(k).upper()
                check = checkNewHash(myKey)
                if check == True:
                    break

                # cheking ABc
                myKey[0] = chr(i).upper()
                myKey[1] = chr(j).upper()
                myKey[2] = chr(k)
                check = checkNewHash(myKey)
                if check == True:
                    break

                # cheking AbC
                myKey[0] = chr(i).upper()
                myKey[1] = chr(j)
                myKey[2] = chr(k).upper()
                check = checkNewHash(myKey)
                if check == True:
                    break

                # cheking aBC
                myKey[0] = chr(i)
                myKey[1] = chr(j).upper()
                myKey[2] = chr(k).upper()
                check = checkNewHash(myKey)
                if check == True:
                    break

            if check == True:
                break
        if check == True:
            break

    return check

# check by 4 letter ****************************************************************


def checkKey3():
    check = False
    myKey = ['a', 'b', 'c', 'd']
    for i in range(97, 123):
        for j in range(97, 123):
            for k in range(97, 123):
                for t in range(97, 123):
                    # cheking abcd - all of them in lowercase
                    myKey[0] = chr(i)
                    myKey[1] = chr(j)
                    myKey[2] = chr(k)
                    myKey[3] = chr(t)
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking Abcd
                    myKey[0] = chr(i).upper()
                    myKey[1] = chr(j)
                    myKey[2] = chr(k)
                    myKey[3] = chr(t)
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking aBcd
                    myKey[0] = chr(i)
                    myKey[1] = chr(j).upper()
                    myKey[2] = chr(k)
                    myKey[3] = chr(t)
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking abCd
                    myKey[0] = chr(i)
                    myKey[1] = chr(j)
                    myKey[2] = chr(k).upper()
                    myKey[3] = chr(t)
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking abcD
                    myKey[0] = chr(i)
                    myKey[1] = chr(j)
                    myKey[2] = chr(k)
                    myKey[3] = chr(t).upper()
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking ABCD
                    myKey[0] = chr(i).upper()
                    myKey[1] = chr(j).upper()
                    myKey[2] = chr(k).upper()
                    myKey[3] = chr(t).upper()
                    check = checkNewHash(myKey)
                    if check == True:
                        break
#**********************************************************
                    # cheking ABcd
                    myKey[0] = chr(i).upper()
                    myKey[1] = chr(j).upper()
                    myKey[2] = chr(k)
                    myKey[3] = chr(t)
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking AbCd
                    myKey[0] = chr(i).upper()
                    myKey[1] = chr(j)
                    myKey[2] = chr(k).upper()
                    myKey[3] = chr(t)
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking AbcD
                    myKey[0] = chr(i).upper()
                    myKey[1] = chr(j)
                    myKey[2] = chr(k)
                    myKey[3] = chr(t).upper()
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking aBCd
                    myKey[0] = chr(i)
                    myKey[1] = chr(j).upper()
                    myKey[2] = chr(k).upper()
                    myKey[3] = chr(t)
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking aBcD
                    myKey[0] = chr(i)
                    myKey[1] = chr(j).upper()
                    myKey[2] = chr(k)
                    myKey[3] = chr(t).upper()
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking abCD
                    myKey[0] = chr(i)
                    myKey[1] = chr(j)
                    myKey[2] = chr(k).upper()
                    myKey[3] = chr(t).upper()
                    check = checkNewHash(myKey)
                    if check == True:
                        break
#************
                    # cheking ABCd
                    myKey[0] = chr(i).upper()
                    myKey[1] = chr(j).upper()
                    myKey[2] = chr(k).upper()
                    myKey[3] = chr(t)
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking aBCD
                    myKey[0] = chr(i)
                    myKey[1] = chr(j).upper()
                    myKey[2] = chr(k).upper()
                    myKey[3] = chr(t).upper()
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                    # cheking AbCD
                    myKey[0] = chr(i).upper()
                    myKey[1] = chr(j)
                    myKey[2] = chr(k).upper()
                    myKey[3] = chr(t).upper()
                    check = checkNewHash(myKey)
                    if check == True:
                        break

                if check == True:
                    break
            if check == True:
                break
        if check == True:
            break

    return check


if __name__ == "__main__":
    main()
