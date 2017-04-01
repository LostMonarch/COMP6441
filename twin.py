# My Twincidence calculator
import re
import sys

# Open the file and convert text to one line only
a = sys.argv[1]
file = '../txt/' + a
with open(file) as f:
    text = f.read().replace('\n', '')

# Remove all non-alphabetic characters in the text and convert to upper case
nonAlphaPattern = r"[^A-z]"
text = re.sub(nonAlphaPattern, "", text)
text = text.upper()
text = text.strip()

# Count number of Twincidences
numTwims = 0
lastChar = text[0]
for c in text[1:]:
    if c == lastChar:
        numTwims = numTwims + 1
    lastChar = c

# Divide by the length of the text
numChars = len(text)
q = numTwims / float(numChars)

# Multiply by number of members in the target alphabet
r = q * 26
print r