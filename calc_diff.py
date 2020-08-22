ans = {}
par = {}
for line in open("gt_swimming","r"):
    t = line.strip().split()
    ans[int(t[0])] = int(t[1])
for line in open("pbe1_swimming_val","r"):
    t = line.strip().split()
    p = int(t[0])
    i = int(t[1])
    j = int(float(t[2]))
    if not p in par:
            par[p] = [0, 0]
    par[p][0] += abs(j-ans[i])
    par[p][1] += 1
for p in par:
	print(p, float(par[p][0])/par[p][1])


			
