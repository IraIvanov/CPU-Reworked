# That directory contains the program that emulates cpu called proc 

**That is the most briliant code for that type of problem that human been could ever seen**

The program is created as my student project


# How to build

```terminal
  $ git clone https://github.com/IraIvanov/Project_H    
  $ cd Project_H/Processor    
  $ make        
  ```
After building project you'll receive 2 executable files, compiler and proc.

compiler program is created for compilating code that is written on R_ASM, "unique" version of assembler language that my cpu uses.

Commands list:

```terminal
  IN
```
expects some input from keyboard

```terminal
  PUSH
```
push the number, or register into stack

```terminal
  POP
```
pop the number from stack into the register or RAM


```terminal
  ADD
  SUB
  MUL
  DIV
```
arithmetic operations


```terminal
  OUT
```
pop the number from stack and shows it 


```terminal
  HLT
```
terminates the programm

You can see some exampels, for example program factorial.txt counting factorial of input number

Also you can build your own code:

```terminal
  $ ./compiler example_code.txt        
  ```

After that you'll receive binary file called a.out, to execute it use:

```terminal
  $ ./proc a.out        
  ```

Multiple files :white_check_mark:       
Warnings :negative_squared_cross_mark:      

**Have fun!**     
![Alt-текст](https://derpicdn.net/img/2019/5/6/2032644/large.jpg)
