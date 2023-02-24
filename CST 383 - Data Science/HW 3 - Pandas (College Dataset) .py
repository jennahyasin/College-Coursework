# -*- coding: utf-8 -*-
"""

CST 383, Homework 3.

In this homework we use Pandas to investigate a data set about 
college majors.  The data is from 2010-2012, and was derived
from US Census data by an Ben Casselman of fivethirtyeight.com

"""

"""

Info about the data set.

Here is the data:
https://github.com/fivethirtyeight/data/tree/master/college-majors

Here is Casselman's report:
https://fivethirtyeight.com/features/the-economic-guide-to-picking-a-college-major/

This data set concerns people under 28 who have
a bachelor's degree but no graduate degree.  The data comes
from the US Census PUMS data, which is a statistical sample of the 
US census data.  

Information about the columns in the data set can be found on the
github page listed above.  It's hard to interpret some of this data.  
For example, unemployed + employed does not equal total.  From the R 
script Casselman wrote to generate his data set, this is what I understand:
    
Total: total number of people for the major (in the census data)
  
Median: median yearly income for those in the major

Full_time_year_round: 50+ weeks/year, 35+ hours/week.
  
Employed:
    - employed means employment status code is either
       - civilian employed, at work
       - civilian employed, with a job but not at work
         (this means the person does not happen to be at work that day, for
          reasons including vacation, illness, bad weather, strike, etc.)
    - note that this can be part-time work, or even erratic work, I guess
    
Unemployed: census employment status code is 'unemployed'
    - Employed + Unemployed does give give the total for the major, because
      there are other categories, like 'not in labor force', and 'armed forces'

Full_time: avg hours/week > 35 in last 12 months 

Part-time: average hours/week over past 12 months was non-zero, but less than 35 hours.
   - Note that Full_time + Part_time gives total number of people who
     worked over the past 12 months, but does not give the same value
     as Employed.
         
College jobs, Non_college_jobs, Low_wage_jobs:  These are related to
  certain lists of jobs, and if you add the values together, you don't
  get all job.  Casselman doesn't show exactly which jobs these are.

"""

"""

Homework instructions:
    
PLEASE NOTE: your code will be graded automatically so please
follow these instructions carefully.  My grading script grades
each of your answers *independently*.  In other words, I do not
run all of your submitted code in order.  I take your code for
one problem, and run it in an environment where certain variables
or functions are defined.  For each problem I will list the 
variables you can assume to be defined in your answer.  Do not
assume that variables or functions that you defined earlier are
available.

In your code for a problem, you can define temporary methods and
variables before your final line of code, but you cannot assume
these temporary methods are available in later problems.
I will run your code on a modified version of the dataset to make
sure it gets the right answers if the data is a little different.

Also, please note that you should not use a loop anywhere in your code
for this homework.

"""

# note: do not import other packages; my test script uses only these
import numpy as np
import pandas as pd

# allow output to span multiple output lines in the console
pd.set_option('display.max_columns', 500)

#
# read the data
#

df = pd.read_csv("https://raw.githubusercontent.com/fivethirtyeight/data/master/college-majors/recent-grads.csv")

#
# series
#

# let's start with two series
# (without the copy, we are just getting a view of a column,
#  and it will cause problems later, for example in sorting)
unemp = df['Unemployment_rate'].copy()
major = df['Major'].copy()

#@ 1
# Compute the length of the 'major' series.  Your result should
# be a single integer.
# assume major is defined
major.size

#@ 2
# Compute the first 10 elements of the data in the unemp series.
# The result should be a NumPy array.
# assume unemp is defined
np.array(unemp[:10])

#@ 3
# Compute the maximum value of the unemp series (use a pandas method).
# The result should be a single value.
# assume unemp is defined
unemp.max()

#@ 4
# Set the index of unemp to be the data in the major series, then
# compute the first fives values of the index (do not use 'print').
# assume unemp and major are defined
# keep unemp as Series (not as a DataFrame)
# (modify unemp)
unemp.index = major.values
unemp.index[:5]

#@ 5
# Compute the 10 majors with the lowest unemployment rate, sorted 
# by increasing unemployment rate.
# Your output should be a series, and should begin like this:
# EDUCATIONAL ADMINISTRATION AND SUPERVISION    0.000000
# MILITARY TECHNOLOGIES                         0.000000
# BOTANY                                        0.000000
# MATHEMATICS AND COMPUTER SCIENCE              0.000000
# SOIL SCIENCE                                  0.000000
# ENGINEERING MECHANICS PHYSICS AND SCIENCE     0.006334
# assume unemp is defined, and is indexed by majors
unemp.sort_values(ascending = True)[:10]

#@ 6
# Compute the number of majors that have unemployment levels less than 0.05
# Your result should be a single number.
# assume unemp is defined
sum(unemp.values < 0.05)

#@ 7
# Compute the fraction of majors that have unemployment levels less than 0.06
# (note: 0.06, not 0.05)
# Your result will be a value between 0 and 1.
# assume unemp is defined
sum(unemp.values < 0.06) / unemp.size

#@ 8
# Compute the fraction of majors that have unemployment levels lower than the
# unemployment level of 'COMPUTER SCIENCE'.
# assume unemp is defined
sum(unemp.values < unemp['COMPUTER SCIENCE']) / unemp.size

#
# data frames
#

#
# preprocessing
#

# make the major the index, and remove the major column
# also, drop Major_code and Sample_size
#@
df.index = df['Major']
df.drop('Major', axis=1, inplace=True)
df.drop(['Major_code', 'Sample_size'], axis=1, inplace=True)

# any missing data?  (We haven't covered this yet.)
df.isna().sum(axis=1).sort_values(ascending=False)[:10]

# drop rows with NA
df.dropna(inplace=True)


###############################################################
# In your answers to all remaining problems you can assume
# that df is defined, and has the columns of the dataframe df
# just defined.
###############################################################


#@ 9
# Compute a series containing the values for major 'MICROBIOLOGY'.
df.loc['MICROBIOLOGY']

#@ 10
# Compute the total number of people represented in the
# data set (in other words, sum the values in the 'Total' column).
# Your result should be a single number.
sum(df['Total'])

#@ 11
# Compute the overall fraction of women
# Your result should be a number between 0.55 and 0.60
sum(df['Women']) / sum(df['Total'])

#@ 12
# Compute the major with the highest value of ShareWomen
# Your result should be a single string value.
df['ShareWomen'].idxmax()

#@ 13
# Compute the median earnings for all the majors with
# share of women > 90%.  Your result should be a series
# that begins like this:
# Major
# MEDICAL ASSISTING SERVICES                       42000
# SPECIAL NEEDS EDUCATION                          35000
# ELEMENTARY EDUCATION                             32000
df['Median'][df['ShareWomen'] > 0.9]

#@ 14
# Compute a series containing the median earnings for all the 
# majors with share of women < 15%.  Your result should begin
# like this:
# Major
# PETROLEUM ENGINEERING                          110000
# MINING AND MINERAL ENGINEERING                  75000
# NAVAL ARCHITECTURE AND MARINE ENGINEERING       70000
df['Median'][df['ShareWomen'] < 0.15]

#@ 15
# Compute the ratio of the median of the highest earning major
# to the median of the lowest earning major.  Your output should
# be a single number, and it should be close to 5.
df['Median'].max() / df['Median'].min()

#@ 16
# Compute the top 10 majors by median earnings.  For each of these
# majors, your result should contain the median, .25 percentile, and
# .75 percentile earnings.  Sort the result by median earnings, largest first.
# Your result should be a data frame that begins like this:
#                                            Median  P25th   P75th
# Major                                                           
# PETROLEUM ENGINEERING                      110000  95000  125000
# MINING AND MINERAL ENGINEERING              75000  55000   90000
# METALLURGICAL ENGINEERING                   73000  50000  105000
# NAVAL ARCHITECTURE AND MARINE ENGINEERING   70000  43000   80000
df[['Median', 'P25th', 'P75th']].sort_values(by = 'Median', ascending = False)[:10]

#@ 17
# Repeat the previous problem, but compute the 10 majors with the
# lowest median earnings, and sort with lowest meadian salary first
df[['Median', 'P25th', 'P75th']].sort_values(by = 'Median', ascending = True)[:10]

#@ 18
# For each major, compute the fraction of people who have a non-college
# job (in other words, a job not requiring a college degree).
# Your result should contain only the top 10 majors, 
# sorted in decreasing order by fraction of people.  Your result
# should be a series that begins like this:
# Major
# COSMETOLOGY SERVICES AND CULINARY ARTS                               0.702569
# NUCLEAR, INDUSTRIAL RADIOLOGY, AND BIOLOGICAL TECHNOLOGIES           0.697070
# ELECTRICAL, MECHANICAL, AND PRECISION TECHNOLOGIES AND PRODUCTION    0.681314
(df['Non_college_jobs'] / df['Total']).sort_values(ascending = False)[:10]

#@ 19
# For each major category, compute the total number of people
# in that category.  Your result should
# be sorted by number of people, in descending order.
# You will need the 'Total' column.
# Your result should be a series that begins like this:
# Major_category
# Business                               1302376.0
# Humanities & Liberal Arts               713468.0
df.groupby('Major_category')['Total'].sum().sort_values(ascending = False)

#@ 20
# For each major category, compute the fraction of people
# associated with that category.  Order your output by fraction
# of people, in decreasing order.
# Your result should be a series that begins like this:
# Major_category
# Business                               0.192328
# Humanities & Liberal Arts              0.105361
# Education                              0.082569
df.groupby('Major_category')['Total'].sum().sort_values(ascending = False) / df['Total'].sum()

#@ 21
# Compute the number of majors associated with each major
# category.  The first lines of your result should look like this:
# Engineering                            29
# Education                              16
# Humanities & Liberal Arts              15
# Biology & Life Science                 14
#
df['Major_category'].value_counts()

#@ 22
# Add a new variable 'HighShareWomen' to the data frame.
# This variable should be True if ShareWomen > 0.50, and
# False otherwise.  Then compute the first five values in
# the HishShareWoman column.
df['HighShareWomen'] = df['ShareWomen'] > 0.5
df['HighShareWomen'][:5]

###############################################################
# In the remaining problems you can assume that df additionally
# contains the column 'HighShareWomen'
###############################################################


#@ 23
# Compute the fraction of majors that have a high share of women.
# Your result should be a number close to 0.56
df['HighShareWomen'].sum() / df['Total'].count()

#@ 24
# For each major, compute the fraction of those working in
# low-end jobs.  Show the 10 majors with the most low wage
# jobs, ordered by decreasing fraction of low-end jobs.
# Your result should be a series that begins like this:
# Major
# COSMETOLOGY SERVICES AND CULINARY ARTS    0.300951
# DRAMA AND THEATER ARTS                    0.255913
# MISCELLANEOUS FINE ARTS                   0.226048
# CLINICAL PSYCHOLOGY                       0.219168
# STUDIO ARTS                               0.211227
(df['Low_wage_jobs'] / df['Total']).sort_values(ascending = False)[:10]


#@ 25
# For each major category, compute the maximum of the median
# salaries for majors within that category.  Sort by decreasing
# median salary.
# Your result should be a series that begins like this:
# Major_category
# Engineering                            110000
# Physical Sciences                       62000
# Business                                62000
df.groupby('Major_category')['Median'].max().sort_values(ascending = False)

#@ 26
# Compute the average median salary for each major category,
# sorted by increasing salary.
# Your result should be a series that begins like this:
# Major_category
# Psychology & Social Work               30100.000000
# Humanities & Liberal Arts              31913.333333
# Education                              32350.000000
df.groupby('Major_category')['Median'].mean().sort_values(ascending = True)

# The answer to the previous question does not accurately
# represent the median salary for a major category, because
# certain majors within a category may have a lot more students
# than other categories.  When combining the salaries of majors
# within a major category, we need to take into account the
# number of people in each major within the category. If a
# major has lots of people, the median salary for that major
# should have a bigger weight in get the median salary for
# the major category.

#@ 27
# Create a new column 'Major_share' that gives, for each major, the fraction of people 
# associated with the major, and then compute the first five values in the new
# column.
# The sum of the new column should be 1.0 or very close to 1.0.
df['Major_share'] = df['Total'] / df['Total'].sum()
df['Major_share'][:5]

###############################################################
# In the remaining problems you can assume that df additionally
# contains the column 'Major_share'
###############################################################


#@ 28
# Now compute the weighted median salary* for each major category,
# taking into account the number of people in each major
# You will probably want to use 'groupby' in conjunction with
# apply().  Don't forget the variable 'Major_share'.  You
# may want to define the function that gets applied.
# *Please see the hint provided on Canvas page for help. 
# A weighted mean formula is given in that hint.
#
# Your result should be a series that begins like this:
# Major_category
# Agriculture & Natural Resources        34951.719122
# Arts                                   31716.044578
# Biology & Life Science                 34446.722572
# Business                               40942.111188
def weighted_median(df):
    return sum(df['Major_share']*df['Median']) / sum(df['Major_share'])
df.groupby('Major_category').apply(weighted_median)
#@ 29
# Using the same idea as the last problem to compute
# the the weighted median unemployment rate for each major category.
# Your result should be a series that begins like this:
# Major_category
# Agriculture & Natural Resources        0.051505
# Arts                                   0.089105
# Biology & Life Science                 0.070219
def weighted_median_unemployment(df):
    return sum(df['Major_share']*df['Unemployment_rate']) / sum(df['Major_share'])
df.groupby('Major_category').apply(weighted_median_unemployment)
#@ 30
# Compute the share of women by major category.  to do this
# you need to find the total number of women and total number
# of people in each category.
# Your result should be a series that begins like this:
# Major_category
# Agriculture & Natural Resources        0.466318
# Arts                                   0.623694
# Biology & Life Science                 0.592566
# Business                               0.487205
df.groupby('Major_category').sum(['Women'])['Women']/df.groupby("Major_category").sum(['Total'])['Total']

#@ 31
# Compute the weighted-median median salary for majors with
# a high share of women and for majors without a high
# share of women.  You need to consider
# the number of students in each major to do this,
# because some majors have many fewer students than
# others.  Consider using the 'Major_share' column.
# Your result should be a series and should look like this:
# HighShareWomen
# False    43633.592490
# True     34692.752128
# dtype: float64
def weighted_median_HighShareWomen(df):
    return sum(df['Major_share']*df['Median']) / sum(df['Major_share'])
df.groupby('HighShareWomen').apply(weighted_median_HighShareWomen)

#@ 32
# Compute the fraction of low wage jobs by major category for all the people.
# Order your result from low to high values. Consider using the 'Total' column.
# Your result should be a series that begins like this:
# Major_category
# Engineering                            0.046651
# Computers & Mathematics                0.053965
# Health                                 0.067504
(df.groupby('Major_category').sum(['Low_wage_jobs'])['Low_wage_jobs']/df.groupby("Major_category").sum(['Total'])['Total']).sort_values()

#@ 33
# Compute the unemployment rate by major category.
# Sort your result by unemployment rate, descending.
# Use the 'Employed' and 'Unemployed' columns to compute the
# unemployment rate.
# Your result should be a series that begins like this.
# Major_category
# Social Science                         0.096689
# Arts                                   0.089233
# Humanities & Liberal Arts              0.085852
# Law & Public Policy                    0.085258
(df.groupby('Major_category').sum('Unemployed')['Unemployed']/ 
 (df.groupby('Major_category').sum('Unemployed')['Unemployed'] + 
  df.groupby('Major_category').sum('Employed')['Employed'])).sort_values(ascending = False)







