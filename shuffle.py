# My shuffle solver
import re

# Open the file and read lines into a list
with open('../txt/shuffle.txt') as f:
    lines = f.read().splitlines()

# Define regex patterns for identifying components of the line identifier
lineNumberPattern = r"::[0-9]+::"
semicolonsPattern = r"::"

# Separate lines into line number and artwork components, add them to a list
parsedLines = []
for s in lines:
	currLineNumber = re.search(lineNumberPattern, s).group(0)
	number = re.sub(semicolonsPattern, "", currLineNumber)
	art = re.sub(lineNumberPattern, "", s)
	tup = (int(number), art)
	parsedLines.append(tup)

# Sort the list of number-art tuples based on the line number and print the result!
sortedLines = sorted(parsedLines, key = lambda x: x[0])
for l in sortedLines:
	print str(l[0]) + "    " + l[1]