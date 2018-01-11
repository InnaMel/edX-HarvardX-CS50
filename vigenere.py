from cs50 import *
import crypt
import sys


# determine hashing letter
def vigenerecode(numLetterKey, numLettTxt):
    shiftLetter = ((numLetterKey + numLettTxt) % 26) + delta
    return chr(shiftLetter)


# determine digit of letter as ASCII
def fromLetterToNumAlphabet(letterCurrent):
    global delta
    delta = 0
    if letterCurrent.isupper():
        delta = 65
    else:
        delta = 97
    numAlphabet = ord(letterCurrent) - delta
    return numAlphabet


# checking character is digit
def checkKey(key):
    rez = True
    leng = len(key)
    for i in range(leng):
        if not key[i].isdigit() == 0:
            rez = False
    return rez


# taking word
def main():
    if not len(sys.argv) == 2 or checkKey(sys.argv[1]) == False:
        print('Usage: ./vigenere k')
        sys.exit(1)
    userKey = sys.argv[1]
    restKey = userKey
    # convert strint key into list (list())
    userKeyList = list(userKey)
    restKeyList = list(restKey)

    lengthKey = len(userKey)

    # ask some text for hashing
    print('plaintext: ', end='')
    plainTxt = get_string()

    ciphertext = ''

    # create empty temt lists
    currentKey = []
    tempList = []

    # divide string text into list - word by word (.split())
    plainTxtList = plainTxt.split()
    for i in plainTxtList:
        wordAsList = list(i)
        # magic with userKey: if length of word > userKey, we must add letter to userKey for equal length both. If length of word < userKey, we must add ending userKey (not using letter) to the front of new userkey!
        if len(i) > len(restKeyList):
            userKeyList = list(userKey)
            # extendet hash key. Letter by letter
            while len(i) > len(restKeyList):
                for lst in userKeyList:
                    restKeyList.extend(lst)
            # determine differens
            lk = len(restKeyList) - len(i)
            # divide all hash key for two part. First for current word, the second for next word
            # FIRST PART: zero currentKey and then fulling it the letters as much as length hashinh word
            currentKey = []
            for ffront in range(len(wordAsList)):
                currentKey.append(restKeyList[ffront])
            # SECOND PART: to do reverse twice
            restKeyList.reverse()
            tempList = []
            for fback in range(lk):
                tempList.append(restKeyList[fback])
            tempList.reverse()
            restKeyList = tempList
        elif len(i) < len(restKeyList):
            lk = len(restKeyList) - len(i)
            currentKey = []
            for ffront in range(len(wordAsList)):
                currentKey.append(restKeyList[ffront])
            restKeyList.reverse()
            tempList = []
            for fback in range(lk):
                tempList.append(restKeyList[fback])
            tempList.reverse()
            restKeyList = tempList
        elif len(i) == len(restKeyList):
            currentKey = restKeyList
            restKeyList = userKeyList
        # main work - sending each letter of word and each letter of hash key. Two iteration the same time through zip(). w in wordAsList and k in currentKey
        for (w, k) in zip(wordAsList, currentKey):
            if w.isalpha():
                if k.isupper:
                    k = k.lower()
                w = vigenerecode(fromLetterToNumAlphabet(k), fromLetterToNumAlphabet(w))
                ciphertext = ciphertext + w
            else:
                ciphertext = ciphertext + w
        if not len(ciphertext) == len(plainTxt):
            ciphertext = ciphertext + ' '

    print('ciphertext: {0}'.format(ciphertext))


if __name__ == "__main__":
    main()