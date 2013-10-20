from random import randint
def SuperLotto():
    print("Blue Ball")
    for i in range(5):
        print(randint(1,35))
    print("Red Ball")
    print(randint(1,12))
    print(randint(1,12))
def DCB():
    print("Blue Balls")
    for i in range(6):
        print(randint(1,33))
    print("Red Ball")    
    print(randint(1,16))
#DCB()
SuperLotto()
