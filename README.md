
# welcome to alphaCode
### alpha code is a verry simple programming language based on the prorgamming language "BASIC"

#### its syntax is based on commands and arguments, every command you write down has a predefined number of arguments it needs, and the arguments can either be:

- a string
- a number
- a variable

#### here is a list of all commands that are currently available

<hr>

-  `print`
print needs 1 argument, wich is the thing that will be printed to the console. this can either be a variable or a string litteral
```
print "hello world"
```

<hr>

-  `get`
get needs 1 argument, wich is the string variable, the input will be stored in
```
get str
print str
```

<hr>

- `let`
let is a command to define variables, it needs 2 arguments.<br>
the first one is a variable name, where the value will be stored<br>
and the second one is the value to be stored, wich can either be a string or a number
```
let num 69420
let str "spam and eggs"

print str
```

<hr>

- `exit`
exit, will exit the program. it needs 1 number as argument, wich will be used to return as the exit code of the program
```
print "hello world"
exit 0
```

<hr>

- `more/less`
the more and less commands will increment and decrement a numeric variable
```
let age 1

more age
print age
print "\n"

less age
print age
exit 0
```

<hr>

- `goto`
the goto command will go to a previously defined "marker" and continue running from there. a marker is define with a ':' followed by the name of the marker. the goto command will go to the marker name given as its first and only argument
```
let age 1

:loop
more age
print age
goto loop
exit 0
```

<hr>

- `gotoifis`
the gotoifis command needs 3 arguments: num1, num2 and marker. it will go to marker, if num1 and num2 are the same, num1 and num2 must be either of type number or variable
```
let age 1

:loop
more age
print age
gotoifis age 2 loop
exit 0
```

<hr>

- `gotoifisnt`
the gotoifisnt command needs 3 arguments: num1, num2 and marker. it will go to marker, if num1 and num2 are NOT the same, num1 and num2 must be either of type number or variable
```
let age 1

:loop
more age
print age
gotoifisnt age 500 loop
exit 0
```

<hr>

- `gotoifisgtr`
the gotoifisgtr command needs 3 arguments: num1, num2 and marker. it will go to marker, if num1 > num2, num1 and num2 must be either of type number or variable
```
let age 1

:loop
more age
print age
gotoifisgtr 500 age loop
exit 0
```

<hr>

- `gotoifislss`
the gotoifislss command needs 3 arguments: num1, num2 and marker. it will go to marker, if num1 < num2, num1 and num2 must be either of type number or variable
```
let age 1

:loop
more age
print age
gotoifislss age 500 loop
exit 0
```

<hr>

- `add`
the add command needs 2 arguments, the first one needs to be a variable, and the second one can be a variable or a number.
it will add the second argument to the first argument
```
let num1 69
let num2 420

add num1 num2
print num1

exit 0
```

<hr>

- `sub`
the sub command needs 2 arguments, the first one needs to be a variable, and the second one can be a variable or a number.
it will subtract the second argument from the first argument
```
let num1 69
let num2 420

sub num1 num2
print num1

exit 0
```

<hr>

- `div`
the div command needs 2 arguments, the first one needs to be a variable, and the second one can be a variable or a number.
it will divide the second argument by the first argument
```
let num1 69
let num2 420

div num1 num2
print num1

exit 0
```

<hr>

- `mul`
the mul command needs 2 arguments, the first one needs to be a variable, and the second one can be a variable or a number.
it will multiply the second argument with the first argument
```
let num1 69
let num2 420

mul num1 num2
print num1

exit 0
```

<hr>

- `pow`
the pow command needs 2 arguments, the first one needs to be a variable, and the second one can be a variable or a number.
it will take the power of the first argument raised to the second argument, and store it in the first argument
```
let num1 69
let num2 420

pow num1 num2
print num1

exit 0
```

<hr>

- `mod`
the mod command needs 2 arguments, the first one needs to be a variable, and the second one can be a variable or a number.
it will take the mod of the first argument with the second argument, and store it in the first argument
```
let num1 69
let num2 420

mod num1 num2
print num1

exit 0
```

<hr>

- `debug`
the debug command will go trough the memory, and display all the variable that have already defined
```
let num1 69
let num2 420

debug
exit 0
```