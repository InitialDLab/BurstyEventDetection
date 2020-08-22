gran = 1400
tot = 1000000
a = [0] * 33
s = 0
with open("swimming.csv","r") as infile:
    for line in infile:
        tokens = line.strip().split(',')
        date = int(tokens[0].split('-')[-1])
        num = int(tokens[1])
        a[date] = num
        s += num
k = float(tot)/s
agg = 0
eps = 0
for i in range(32):
    for j in range(gran):
        t = i * gran + j
        n = a[i] + float(j) * (a[i+1] - a[i]) / gran 
        n = n * k / gran
        np = int(n)
        eps += n - np
        if eps >= 1:
            np += int(eps)
            eps -= int(eps)
        agg += np
        print t, np, agg

    


			
