file = open("linux32.asm")
data = file.read().split("\n")
file.close()

for line in data:
    datas = line.split("\t")
    rest = '\t'.join(datas[1:])
    print(f"%define {datas[1]}\t{datas[2]}\t ; {rest}")