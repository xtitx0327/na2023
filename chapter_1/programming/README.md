# Programming Homework for Chapter 1

Xiaotong Wang, Oct. 1, 2023.

## Compiliation Guidelines

`Makefile` can help to compile the project. Simply run

```
make
```

in terminal and all executable file will appear in current folder. However, `bash` is required for this tiny script.

You can type

```
make clear
```

to clear files created by the above command.

## Programming report

So simple is the homework that $\LaTeX$ seems not necessary. The report is written below.

Code for problem A is written in `solver.h`. In addition to the requirements of the problem, I also write an abstract class `Function`, used as parameters of the solver classes.

For problem B, bisection method works perfectly for previous three functions, but fails for the last function since it has no root on $[0,4]$. The problem does give an output for it, but the result isn't a root for the function; it's given since `maxIteration` is reached. This fact emphasized that existence and uniqueness must be guaranteed before solving a numerical problem.

Newton's method and secant method also work well for problem C and problem D respectively. 

All three methods give almost the same result for problem E.

As for problem F, letting $x=\sin \alpha$, $\cos \alpha=\sqrt{1-x^2}$ converts the equation into an equation about $x$. Then question (a) and (b) are trivial. However, in question (c), if initial values such as $x_0=0$ and $x_1=0.1$ which are too far away from $\sin 33^{\circ}$ are given, the secant method will fail, with an error result $\alpha\approx -11.5^{\circ}$. This is because the iteration converges to another root of equation.