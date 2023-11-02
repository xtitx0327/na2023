g++ -o interpolation.h.gch interpolation.h
for problem in {b..e}; do
	echo "Compiling problem_$problem"
	g++ -o "problem_$problem" "./problem_$problem/problem_$problem.cpp"
done