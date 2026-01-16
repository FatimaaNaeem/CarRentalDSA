project: main.cpp car.cpp customer.cpp transaction.cpp admin.cpp
	g++ "main.cpp" "car.cpp" "customer.cpp" "transaction.cpp" "admin.cpp" -o "project"

run: project
	./"project"
