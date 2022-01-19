import numpy as np
import matplotlib.pyplot as plt

with open('mat118_1801042656_hw2/temp.txt', 'r') as readingFile: # r means read.
    # Reading line by line in while loop
    cases = []   #name of cases
    bar1 = []    #bar for cases
    bar2 = []    #bar for predicted cases
    line = readingFile.readline()  #reading first line
    while line != '':  # Until end of file.
        print(line, end='')
        split_string = line.split("\t") #File was splitted by tab character.
        cases.append( split_string[0] )
        bar1.append(  int(split_string[1]) ) #writing as int
        bar2.append(  int(split_string[2]) ) #writing as int
        line = readingFile.readline() #reading next line in file.

# Bar positions in x axis.
r1 = np.arange(len(bar1))   #getting length of bar1 for next bar.
r2 = [x + 0.2 for x in r1]

plt.bar(r1, bar1, width = 0.2, color = 'orange', edgecolor = 'gray', capsize=10, label='Cases')          #bar1
plt.bar(r2, bar2, width = 0.2, color = 'black', edgecolor = 'gray', capsize=10, label='Predicted Cases') #bar2

# general layout
plt.xticks( [i + 0.2 for i in range(len(bar1))], cases) # writing cases in graphic with 0.2 distance between bars.
plt.legend() # showing names in rectangle box.
plt.show()   # Show graphic