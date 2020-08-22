ds = "swimming"
pbe1_st = {}
pbe1_err = {}
pbe2_st = {}
pbe2_err = {}
for line in open("pbe1_%s_st" % ds,"r"):
    t = line.strip().split()
    pbe1_st[int(t[1])] = int(t[0])
for line in open("pbe2_%s_st" % ds,"r"):
    t = line.strip().split()
    pbe2_st[int(t[1])] = int(t[0])	
for line in open("pbe1_%s_err" % ds,"r"):
    t = line.strip().split()
    pbe1_err[int(t[0])] = float(t[1])	
for line in open("pbe2_%s_err" % ds,"r"):
    t = line.strip().split()
    pbe2_err[int(t[0])] = float(t[1])		
for s1 in pbe1_st:
	ms2 = 999999
	for s2 in pbe2_st:
		if abs(s1-s2) < abs(s1-ms2):
			ms2 = s2
	if abs(s1-ms2)<500:
		print((s1+ms2)//2, pbe1_err[pbe1_st[s1]], pbe2_err[pbe2_st[ms2]])