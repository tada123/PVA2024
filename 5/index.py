
import os
import sys

planes = []
pcoords = []

for x in open(sys.argv[1]).read().splitlines():
    sp = x.split(":")
    planes.append(sp[1].strip())
    csp = sp[0].split(",")
    pcoords.append([float(csp[0]), float(csp[1])])



def cdelta(a, b):
    return (((b[0] - a[0]) **2) + ((b[1] - b[0]) ** 2)) ** (1 / 2)

deltas = []
planeindexes = []
lowestDelta = None

for i in range(len(planes)):
    for j in range(len(planes)):
        if i == j:
            break
        src = pcoords[i]
        dst = pcoords[j]
        d = cdelta(src, dst)
        planeindexes.append([i, j])
        deltas.append(d)
        print("d: ", d)
        if (lowestDelta == None) or (d < lowestDelta):
            lowestDelta = d


print("Pozice letadel:")
print("Vzdalenost nejblizsich letadel: %f" % lowestDelta)

pairs = []
for i in range(len(deltas)):
    if deltas[i] == lowestDelta:
        pairs.append([planes[planeindexes[i][0]], planes[planeindexes[i][1]]])
    
        
    
print("Nalezenych dvojic: %d" % len(pairs))
for p in pairs:
    print("%s - %s" % (p[0], p[1]))
    
    
    





