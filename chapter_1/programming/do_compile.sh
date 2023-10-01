g++ -o solver.h.gch solver.h
for problem in {b..f}; do
	echo "Compiling problem_$problem"
	g++ -o "problem_$problem" "./problem_$problem/problem_$problem.cpp"
done