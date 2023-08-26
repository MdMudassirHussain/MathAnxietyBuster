# Targets: Dependencies or prerequisites
# 	(tab) command

clean:
	rm -f ./build/*

compile:
	gcc -g -std=c17 -Wall -Wextra -Werror ./src/mathAnxietyBuster.c  -o ./build/mathAnxietyBuster.out

run:
	./build/mathAnxietyBuster.out 3d 112p

.PHONY: clean run