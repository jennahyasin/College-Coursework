# -*- coding: utf-8 -*-
"""
Homework 1
"""

import numpy as np

# In this homework you will write Python and NumPy code, leading up
# to writing code that determines the part number of a machine part
# by looking at how similar it is to other, known parts.

# Each problem starts with a problem number line, like #@ 1 for
# problem 1, and also contains a problem description.  Enter
# your code right after the problem description.  I have provided
# an answer to problem 1 to show what you should do.

# Your answer can contain more than one line of code.  However,
# in almost every case your answer should end with an assignment
# state, or an expression, which is not an assignment statement.
# Each problem description ends by saying whether you should
# give an assignment statement or an expression.

# PLEASE NOTE: your code will be graded automatically so please
# follow these instructions carefully.  In answering a problem,
# you can use a variable defined in a previous problem, but only
# if it was the defined as the answer to a previous problem.  In
# other words, if you defined a variable as a temporary variable
# in a problem, do not use it in other problems.

# Please ask if anything is not clear!

#@ 1 
# assign the value of variable z to variable x
# assume z is defined
# (assignment to x)
x = z

#@ 2 
# assign 'hello' to variable msg
# (assignment to msg)
msg = 'hello'

#@ 3 
# check whether variable msg is a string
# Example: if msg = 5.0, the result should be False
# assume msg is defined
# (write an expression)
type(msg) == str

#@ 4 compute the result of squaring x
# Example: if x is 2.5, the result should be 6.25
# assume x is defined
# (write an expression)
x**2

#@ 5 
# compute the length of the string obtained by appending strings 
# s1 and s2, with a space between them
# Example: if s1 is 'foo', and s2 is 'bar', the result should be 7
# assume s1 and s2 are defined
# (write an expression)
len(s1 + ' ' + s2)

#@ 6 compute the substring consisting of the 2nd-4th characters of string s
# Example: if s is 'snorkel', the result should be 'nor'.
# assume s is defined
# (write an expression)
s[1:4]

#@ 7
# In one of the first lectures of class, we looked at creating a
# system to identify the part number of a transmission part, based on
# width and length measurements (the "features" of the part).  Here
# is data for some examples of three types of parts:
#
# part1: 3.1, 5.2
# part1: 3.0, 5.3
# part1: 3.0, 5.2
# part2: 3.1, 4.8
# part2: 3.2, 4.9
# part2: 3.2, 4.8
# part3: 3.4, 5.6
# part3: 3.4, 5.5
# part3: 3.3, 5.4
#
# Each row above represents 1 part. The first value in each row is the
# part number, the second value is the part width, and the
# third value is the part length (width and length are in inches).
# The width and length values for part 1 vary a little because
# of manufacturing and measuring variations.  Similarly for the other 
# parts.
#
# Create a NumPy array 'width' that contains the width values
# in the data, from top to bottom.  Use the values you see in
# the listing above as the source of the data.
# Example: width[8] should give 3.3 
# (assignment to width)
width = np.array([3.1, 3.0, 3.0, 3.1, 3.2, 3.2, 3.4, 3.4, 3.3])

#@ 8
# Repeat the previous problem, but create a NumPy array 'length'
# that contains the length values in the data.
# (assignment to length)
length = np.array([5.2, 5.3, 5.2, 4.8, 4.9, 4.8, 5.6, 5.5, 5.4])

#@ 9
# Compute a numpy array containing the square root of every element 
# in array 'length'.
# Do not use a loop.
# Example: the result should have 9 elements, and the last should be
# about 2.32
# assume 'length' is defined
# (write an expression)
np.sqrt(length)

#@ 10
# write an expression to compute the average value in the array 'width'
# You can assume 'width' is non-empty and numeric.
# assume 'width' is defined
# (write an expression)
np.average(width)

#@ 11
# write an expression to check that arrays 'width' and 'length' have
# the same number of elements
# assume 'width' and 'length' are defined
# (write an expression)
len(width) == len(length)

#@ 12
# write an expression to compute the maximum value in array 'length'
# assume length is defined
# (write an expression)
max(length)

#@ 13
# create a NumPy array 'part_num' containing the part numbers in
# the data set shown above, from top to bottom.  
# Example: part_num[3] should be 'part2'. 
# (assignment to part_num)
part_num = np.array(['part1', 'part1', 'part1', 'part2', 'part2', 'part2',
                     'part3', 'part3', 'part3'])

#@ 14
# create a Boolean array 'mask' that, for each element in array 'width',
# is True if the value is greater than 3.15, else False. 
# Example: mask[8] should be True
# assume array 'width' is defined
# (assignment to mask)
mask = width > 3.15
 
#@ 15
# using the variable 'mask' just defined, compute an array
# of the part numbers of the parts for which the value of mask is True
# assume array 'mask' and array 'part_num' are defined
# (write an expression)
part_num[mask]

#@ 16
# using 'mask' again, compute the fraction of values in mask
# that are True.  You code should work correctly as long as 'mask' 
# is a boolean array.
# Example: the result should be about 0.555 for the 'mask' array
# you defined above, because about 55% of values in array 'width'
# are greater than 3.15 
# assume array 'mask' is defined
# (write an expression)
np.sum(mask)/mask.size

#@ 17
# write an expression that gives the values in array 'width'
# that correspond to the values in array 'length' that are
# less than 5.0.  Your code should work for any numeric
# arrays 'width' and 'length' that are the same size.
# Example: for the 'width' and 'length' arrays you defined
# your result should be 3.1, 3.2, 3.2
# assume 'width' and 'length' are defined
# (write an expression)
width[length < 5.0]

#@ 18
# compute the mean-zeroed version of width by subtracting
# the average value of 'width' from each element of 'width'.
# Do not use a loop, and do not modify 'width'.
# Example: using the 'width' array you defined earlier, the result
# should have 9 elements and the first should be about -0.0889
# assume array 'width' is defined
# (write an expression)
width - np.average(width)

#@ 19
# compute a '0-1 scaled' version of array 'length' by subtracting
# the minimum value of length from each element, and then 
# dividing each element in the result by the difference between
# the maximum and minimum values of length.
# Your final result should have the same number of elements as
# 'length', and should have 0 as its min value and 1 as its max
# value.
# Do not use a loop, and do not modify 'length'.
# assume array length is defined
# (write an expression)
(length - np.min(length)) / (np.max(length) - np.min(length))

#@ 20
# create a 1D NumPy array 'parts' that contains the 'width'
# values followed by the 'length' values.  
# Example: The first values of 'parts' should be 3.1, 3.0, 3.0 
# and the last values should be 5.6, 5.5, 5.4.
# assume arrays length and width are defined
# (assignment to parts)
parts = np.hstack((width,length))

#@ 21
# reshape the parts array so that it is a 2D NumPy array, with
# width values in column 1 and length values in column 2.  You
# can assume that 'parts' has 18 elements in it.  Be careful
# to check that the first column has the width values, and
# check out the 'order' parameter of numpy.reshape().
# Example: parts[2,1] = 5.2
# assume array parts is defined
# (assignment to parts)
parts = parts.reshape(9, 2, order = 'F')

#@ 22
# write an expression to get the all rows of parts after
# the first two rows.
# Example: the first row of your output should be [3., 5.2]
# assume array parts is defined
# (write an expression)
parts[2:]

# Next we are going to think about how we could measure the
# similarity between parts.  One way to do it is to think
# of each part as being a point in two-dimensional space.
# The width value can be thought of as the value on the
# x axis, and the length value can be thought of as the
# value on the y axis.  Then two parts are very similar
# if the distance between them is small.

#@ 23
# compute the Euclidean distance between the
# first two rows of 'parts'.  Given two points (x1, y1) and
# (x2, y2), the Euclidean distance between them is the
# square root of (x1 - x2)**2 + (y1 - y2)**2.  Think of
# the width and length values in the first row as x1 and
# y1, and the width and length values in the second row
# as x2 and y2.
# Your code should return the value 0.141, and should also
# work correctly if array 'parts' contains different values.
# assume array 'parts' is defined
# (write an expression)
np.sqrt((parts[0][0] - parts[1][0])**2 + (parts[0][1] - parts[1][1])**2)

#@ 24
# Suppose we find a part and measure it. We find the width is 3.15 and
# the length is 5.35.  How similar is it to the parts given in the rows
# of 'parts'?  Define a function 'distance' that has three parameters:
# 'width', 'length', and parts.  The function should return a NumPy
# array that gives the distance from the point (width, length) to
# each of the rows in 2D array 'parts'.  I've started the code
# for you below.  
# After running your code, distance(3.0, 4.8, parts) should return
# an array of 9 values, the last being about 0.67
# 
# (define function distance)
def distance(width, length, parts):
    return np.sqrt((width - parts[:,0])**2 + (length - parts[:,1])**2)

#@ 25
# Define a function 'most_similar_part' that, given a width and a length
# of an unknown part, returns the part number of the part in array 'parts'
# that is most similar to it.  Sometimes multiple parts will have a 
# distance to the unknown part that is almost exactly the same.  So the
# function should return a list of the part numbers of parts that are
# either the minimum distance to the unknown part, or within 0.01 of
# that distance.  
# You can use function 'distance', and array 'part_num' in your code.
# Your function should not contain any duplicate part numbers.
# most_similar_part(3.0, 4.8, parts) should return the list ['part2']
# most_similar_part(3.2, 5.3, parts) should return the list ['part1', 'part3']
#
# (define function most_similar_part)
def most_similar_part(width, length, parts):
    upperDist = min(distance(width, length, parts)) + 0.01
    lowerDist = min(distance(width, length, parts)) - 0.01
    return part_num[(distance(width, length, parts) <= upperDist) 
                    & (distance(width, length, parts) >= lowerDist)]
