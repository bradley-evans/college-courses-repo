#!/bin/bash
rm *_distance*
echo "INPUT FILE 1"
python3 nearest_neighbor.py -both input_10.txt
echo ""
echo "INPUT FILE 2"
python3 nearest_neighbor.py -both input_100.txt
echo ""
echo "INPUT FILE 3"
python3 nearest_neighbor.py -both input_10e5.txt
echo ""
echo "INPUT FILE 4"
python3 nearest_neighbor.py -both input_10e6.txt
echo ""