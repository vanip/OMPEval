import pyomp

if __name__ == '__main__':
    he = pyomp.HandEvaluator()
    h = pyomp.Hand.empty() # Final hand must include empty() exactly once!
    h += pyomp.Hand(51) + pyomp.Hand(48) + pyomp.Hand(0) + pyomp.Hand(1) + pyomp.Hand(2) # AdAs2s2h2c
    print(he.evaluate(h)) # 28684 = 7 * 4096 + 12
