import subprocess
import csv

# run vuv.cpp RUNS times with trees from 1 to N_NODES nodes
RUNS = 50
N_NODES = 22
table = [[0 for i in range(1, N_NODES + 1)] for j in range(RUNS + 1)]
for j in range(RUNS):
	for i in range(1, N_NODES + 1):
		table[0][i - 1] = i
		command = "bash test.sh " + "A"*i
		print("Running command: " + command)
		out = subprocess.check_output(command, shell=True)
		cutted = out.decode()[2:-1]
		decoded = int(cutted)
		table[j + 1][i - 1] = cutted

with open("measure.csv", mode='w') as csv_file:
	csv_writer = csv.writer(csv_file, delimiter=';', quoting=csv.QUOTE_MINIMAL)
	for row in table:
		csv_writer.writerow(row)
