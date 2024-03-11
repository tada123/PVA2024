

import os
import sys

lns = open(sys.argv[1]).read().splitlines()
crshelf = []
shelfs = []

crshoplist = []
shoplists = []
shopListIdx = -1
for ln in lns:
    if len(ln) == 0:
        if len(crshoplist) > 0:
            shoplists.append(crshoplist)
        shopListIdx += 1
        continue
    elif shopListIdx < 0:
        if(ln[0] == '#'):
            shelfs.append(crshelf)
            crshelf = []
        else:
            crshelf.append(ln)
    else:
        crshoplist.append(ln)

def lwIndexof(arr, itm):
    for i in range(len(arr)):
        e = arr[i]
        if e.lower() == itm.lower():
            return i
    return -1
    
for sl in shoplists:
    optimized = []
    for i in range(len(shelfs)):
        for itm in sl:
            idx = lwIndexof(shelfs[i], itm)
            if idx >= 0:
                optimized.append((itm, idx, shelfs[i][idx]))
                
    print("Optimalizovaný seznam: ")
    already = []
    counter = 0
    for o in optimized:
        if not o in already:
            already.append(o)
#            print('o', o)
            print(" %d. %s -> #%d %s" % (counter, o[0], o[1], o[2]))
            counter += 1
            







