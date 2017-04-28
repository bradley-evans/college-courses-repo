#!/usr/bin/python

import sys
import time
from random import randrange
from math import sqrt
import re
import timeit

class UsageError(Exception):
     pass

# Read the input file
def getfile(filename):
    i = 0
    try:
        file = open(filename, "r")
        raw_data = file.readlines()
        data=[0 for i in range(len(raw_data))]
        while i < len(raw_data):
            data[i] = raw_data[i].replace('\n','')
            i += 1
        file.close()
        return data;
    except FileNotFoundError:
        print("File", filename, "not found! Exiting...")
        exit()

# Turn data into an array of floats for the x and y axes.
def parseData(data):
    x = [0 for i in range(len(data))]
    y = [0 for i in range(len(data))]
    for i in range(len(data)):
        x[i] = float(data[i].rsplit(' ',1)[0])
        y[i] = float(data[i].rsplit(' ',1)[1])
    return x, y;

# Take in unsorted x, y arrays.
# Return sorted x, y arrays
# Uses QuickSort.
# Implementation credit: https://coderwall.com/p/temqxa/quicksort-in-python
# Modified to keep x, y in the same index.
# Quicksort Partition
def partition(x, y, start, end, pivot):
    x[pivot], x[end] = x[end], x[pivot]
    y[pivot], y[end] = y[end], y[pivot]
    store_index = start
    for i in range(start, end):
        if x[i] < x[end]:
            x[i], x[store_index] = x[store_index], x[i]
            y[i], y[store_index] = y[store_index], y[i]
            store_index += 1
    x[store_index], x[end] = x[end], x[store_index]
    y[store_index], y[end] = y[end], y[store_index]
    return store_index

# Quicksort
def quick_sort(x, y, start, end):
    if start >= end:
        return x, y
    pivot = randrange(start, end + 1)
    new_pivot = partition(x, y, start, end, pivot)
    quick_sort(x, y, start, new_pivot - 1)
    quick_sort(x, y, new_pivot + 1, end)

#Quicksort Initial Call
def sortPoints(x, y):
    quick_sort(x, y, 0, len(x) - 1)
    return x, y
    
def split(x,y):
    mid = len(x) // 2
    xl = []
    yl = []
    xr = []
    yr = []
    for i in range(0, mid - 1):
        xl.append(x[i])
        yl.append(y[i])
        if i < len(x):
            xr.append(x[i+mid])
            yr.append(y[i+mid])
    return xl, yl, xr, yr;

def dist(x1, y1, x2, y2):
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2))
    
def bruteforce(x,y):
    min = 10000
    for i in range(0,len(x)-1):
        for j in range(i+1,len(x)):
            distance = dist(x[i],y[i],x[j],y[j])
            if distance < min:
                min = distance
        if len(x) > 3:
            sys.stdout.write('\r')
            progress = (i/len(x))*100
            sys.stdout.write('Brute Force Progress: ')
            sys.stdout.write("%.2f" % progress)
            sys.stdout.write('% complete')
            sys.stdout.flush()
    if len(x) > 3:
        sys.stdout.write('\r')
        sys.stdout.write('                                        ')
        sys.stdout.write('\r')
        sys.stdout.flush()
    return min;

def divconq(x,y):
    # Base Case: When we get down to two objects,
    # simply return the shorter of the two distances.
    if len(x) < 3:
        return bruteforce(x,y)
    xl, yl, xr, yr = split(x,y)
    # if we aren't in the base case, recurse on each half
    minleft = divconq(xl,yl)
    minright = divconq(xr,yr)
    d = minleft
    if minright < d:
        d = minright
    minsplit = splitpair(x,y,d)
    if minsplit < d:
        d = minsplit
    return d

def splitpair(x,y,d):
    mid = len(x) // 2
    xs = []
    ys = []
    for i in range(0,len(x)-1):
        if x[i]>(x[mid]-d) and x[i]<(x[mid]+d):
            xs.append(x[i])
            ys.append(y[i])
    min = d
    for i in range(len(xs)-1):
        for j in range(i+1,len(xs)):
            curr_dist = dist(xs[i],ys[i],xs[j],ys[j])
            if curr_dist < min:
                min = curr_dist
    return min

def writeout(filename,solution):
    file = open(filename,"w")
    file.write(solution)
    file.close()
    

def main(filename,algorithm):
    algorithm=algorithm[1:]
    data = getfile(filename)
    outfile = filename.replace('.txt','_distance.txt')
    x, y = parseData(data)
    start = timeit.default_timer()
    x, y = sortPoints(x,y)
    stop = timeit.default_timer()
    print("Sorted in", stop-start)
    if algorithm =='dc':
        dcstart = timeit.default_timer()
        solution = str(divconq(x,y))
        print("Divide and Conquer: ", solution)
        dcstop = timeit.default_timer()
        print("Runtime (DC):", dcstop-dcstart)
    if algorithm == 'bf':
        start = timeit.default_timer()
        solution = str(bruteforce(x,y))
        print("Brute Force: ", solution)
        stop = timeit.default_timer()
        print("Runtime (BF):", stop-start)
    if algorithm == 'both':
        dcstart = timeit.default_timer()
        solution = str(divconq(x,y))
        print("Divide and Conquer: ", solution)
        dcstop = timeit.default_timer()
        print("Runtime (DC):", dcstop-dcstart)
        bfstart = timeit.default_timer()
        print("Brute Force: ", bruteforce(x,y))
        bfstop = timeit.default_timer()
        print("Runtime (BF):", bfstop-bfstart)
        print("Divide and conquer was", (bfstop-bfstart)/(dcstop-dcstart), "times faster.")
    writeout(outfile,solution)
     
if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("python assignment1.py -<dc|bf|both> <input_file>")
        quit(1)
    if len(sys.argv[1]) < 2:
        print("python assignment1.py -<dc|bf|both> <input_file>")
        quit(1)
    main(sys.argv[2],sys.argv[1])