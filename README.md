# Description 
The following project is a calculator of the system of linear equations, which uses the Gauss Jordan elimination algorithm. The program also contains the implementation of the parses, which allows the user to input the equations in an original form, rather than typing the matrix of coefficients. 
# How to use the calculator
Let's say that we want to find the solution of system of linear equations listed below. 
> 2I1-I2+3I3+4I4=9 

>  I1-2I3+7I4=11

>  3I1-3I2+I3+5I4=8
 
 > 2I1+I2+4I3+4I4=10

Numbers placed after the I variable represent the indices.

To solve the equation with the calculator, the user first has to input the size of the system (number of equations in the system)
```
Type how many equations you have in your system:
4
```
Then to the user has to input each equation, one by one.
```
Type equation number 1:
2I1+I2+3I3+4I4=9
Type equation number 2:
I1-2I3+7I4=11
Type equation number 3:
3I1-3I2+I3+5I4=8
Type equation number 4:
2I1+I2+4I3+4I4=10
```
When the last equation is entered, the solution will be displayed.
```
I1=-1.000000
I2=0.000000
I3=1.000000
I4=2.000000
```
If the system has infinitely many solutions, the calculator will give the result in a parametric form.
```
Type how many equations you have in your system:
4
Type equation number 1:
x-y+2z-w=-1
Type equation number 2:
2x+y-2z-2w=-2
Type equation number 3:
-x+2y-4z+w=1
Type equation number 4:
3x-3w=-3

w=-1.000000+1.000000x
y=2.000000z
```
In the solution above the x term and z term are the parameters, which have user has to specify, in order to get the exact result. 
# Limitations 
The calculator cannot perform the arithmetic operations with terms within the equations. This means the calculator will not be able to find the correct solution for the system below: 
> 2x-2y=23-2x-1
  
> 6x=45-y

Instead, the user has to type the following system:
> 4x-2y=22

>  6x+y=45

Another limitation of the calculator is that it gives only gives the trivial solution for the homogeneous systems, even when they have parametric one. 