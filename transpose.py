import sys

infilename = sys.argv[1]
outfilename = sys.argv[2]

with open(infilename,"r") as infile:
    data = [line.split() for line in infile]

assert len(data[0]) == len(data[1])

n_t = len(data)
n_x = len(data[0])

with open(outfilename,"w") as outfile:
    for i in range(n_x):
        for row in data:
            outfile.write("%s " % row[i])
        outfile.write("\n")
