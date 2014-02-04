import random
class Piece():
    def __init__(self):
        self.V = -1
        self.T = 0
    def __init__(self,t,v):
        self.V = v
        self.T = t
    def name(self):
        p = ["Spade","Heart","Club","Diamond"]
        m = str(self.V)
        if self.V == 11:
            m = "J"
        elif self.V == 12:
            m = "Q"
        elif self.V == 13:
            m = "K"
        elif self.V == 14:
            m = "A"
        return p[self.T] + " " + m

class Poker():
    def __init__(self):
        self.mPieces = []
        for t in range(4):
            for v in range(2,15):
                self.mPieces.append(Piece(t,v))
    def giveOne(self):
        l = len(self.mPieces)
        if l == 0:
            return None
        ind = random.randint(0,l-1)
        res = self.mPieces[ind]
        self.mPieces[ind] = self.mPieces[l-1]
        del self.mPieces[l-1]
        return res
    def remain(self):
        return len(self.mPieces)
    def remove(self,t,v):
        for i in range(len(self.mPieces)):
            if self.mPieces[i].T == t and self.mPieces[i].V == v:
                del self.mPieces[i]
                return True
        return False
class Texas():
    def getValue(self,ps):
        ps = sorted(ps,key = lambda x: x.V)
    def isFlush(self,ps):
        for i in range(1,len(ps)):
            if ps[i-1].T != ps[i].T:
                return False
        return True
    def isStraight(self,ps):
        ps = sorted(ps,key = lambda x: x.V)
        for i in range(1,len(ps)-1):
            if ps[i-1].V+1 != ps[i].V:
                return False
        i = len(ps) - 1
        if ps[i-1].V+1 != ps[i].V and (ps[i].V != 14 or ps[0].V != 2):
            return False
        return True

a = Poker()
print a.remove(0,4)
print a.giveOne().name()
print a.remain()
t = Texas()
print "isFlush"
print t.isFlush([Piece(0,4),Piece(0,3),Piece(0,5)])
print t.isFlush([Piece(1,4),Piece(0,3),Piece(0,5)])
print "isStraight"
print t.isStraight([Piece(0,4),Piece(0,2),Piece(0,5)])
print t.isStraight([Piece(0,3),Piece(0,4),Piece(0,5)])
print t.isStraight([Piece(0,2),Piece(0,3),Piece(0,4),Piece(0,5),Piece(0,14)])
