# My Vigenere Cipher solver
import re
import sys
import string
import collections

# Bring in the ciphertext and format
a = sys.argv[1]
file = '../txt/' + a
with open(file) as f:
    text = f.read().replace('\n', '')
    text = text.replace(' ', '')

# First try to estimate the length of the key word (limit the length to 10)
keyLimit = 15
coincidences = []
currCoincidenceCount = 0
for shift in range(1, keyLimit):
    shifted = text[:-shift]
    for index, c in enumerate(shifted):
        if c == text[index + shift]:
            currCoincidenceCount = currCoincidenceCount + 1
    coincidences.append(currCoincidenceCount)
    currCoincidenceCount = 0

# For each letter in the target, take every nth character in the cipher text
keyLength = int(sys.argv[2])
selection = []
frequencies = {}
distribution = {}
distList = []
freqList = []
currSum = 0
max = 0
maxShift = 0

# Create a list of alphabetic characters
for c in list(string.ascii_uppercase):
    frequencies[c] = 0

# We need a table representing the frequency distribution of letters in the English language
distributionFile = '../txt/dist'
with open(distributionFile) as g:
    distributionList = g.read().splitlines()

for l in distributionList:
    pair = l.split()
    distribution[pair[0]] = float(pair[1])

for v in sorted(distribution.keys()):
    distList.append(distribution[v])

# A function which takes two lists and calculates the sum of products of their elements
def frequencySum(freqs, dst):
    productSum = float(0)
    for i in range(0, len(freqs)):
        productSum = productSum + (freqs[i] * dst[i])        
    return productSum

# A function which rotates an input list by a specified amount
def rotate(l, n):
    return l[n:] + l[:n]

# Use Vigere shift method to determine keyword of specified length
for shift in range(0, keyLength):
    selection = text[shift::keyLength]
    #print selection
    for c in selection:
        frequencies[c] = frequencies[c] + 1
    for k in sorted(frequencies.keys()):
        freqList.append(float(frequencies[k]))
    for index, n in enumerate(freqList):
        freqList[index] = freqList[index]/float(len(text))
    
    # Find the frequnecy sum for all possible rotations and get max
    for i in range(0, len(freqList)):
        currSum = frequencySum(rotate(freqList, i), distList)
        if currSum > max:
            max = currSum
            maxShift = i
    #print 'max is: ' + str(max) + ', maximal shift is: ' + str(maxShift)
    print 'Indicates: ' + list(string.ascii_uppercase)[maxShift]

    # Reset
    for c in list(string.ascii_uppercase):
        frequencies[c] = 0
    freqList = []
    max = 0

# Above method doesn't work - can we try another one?
print '\n' + 'Method 2'

def chunkstring(string, length):
    return (string[0+i:length+i] for i in range(0, len(string), length))

# Print chunks of ciphertext
for chunk in chunkstring(text, keyLength):
    print chunk

# Gather letters
letterGroups = [''] * keyLength

for chunk in chunkstring(text, keyLength):
    for i, c in enumerate(chunk):
        letterGroups[i] += c

# Function which wraps indicies into the English alphabet
def wrap(i):
    wrap = i - 4
    if wrap >= 0:
        return wrap
    else:
        return wrap + 26    

# Determine most frequent letter in each group
for g in letterGroups:
    print g
    commons = collections.Counter(g).most_common(3)[0:2]
    for l in commons:
        index = string.ascii_uppercase.index(l[0])
        w = wrap(int(index))
        mapLetter = string.ascii_uppercase[w]
        print str(l[1]) + ',' + str(l[0]) + ',' + str(index) + ' -> ' + str(w) + ',' + mapLetter
    