#!/usr/bin/python

import sys
from random import randrange
from math import sqrt
import re

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
    for i in range(len(x)):
        for j in range(i,len(x)):
            if j != i:
                distance = dist(x[i],y[i],x[j],y[j])
                if distance < min:
                    min = distance
    return min;

def divconq(x,y):
    # Base Case: When we get down to two objects,
    # simply return the shorter of the two distances.
    if len(x) < 3:
        return bruteforce(x,y)
    xl, yl, xr, yr = split(x,y)
    # if we aren't in the base case, recurse on each half
    minleft = bruteforce(xl,yl)
    minright = bruteforce(xr,yr)
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

def main():
    infile = ''
    outfile = ''
    i = 0
    try:
        if len(sys.argv) != 2:
            raise UsageError('Improper usage.')
        else:
            infile = sys.argv[1]
            data = getfile(infile)
            outfile = infile.replace('.txt','_distance.txt')
            x, y = parseData(data)
            x, y = sortPoints(x,y)
    except UsageError:
        print ("Usage: python3 nearest_neighbor.py <inputfile>.txt")
        exit()
    print("Divide and Conquer outcome:", divconq(x,y))
    print("Brute Force Nearest Neighbor outcome:", bruteforce(x,y))
    

main()