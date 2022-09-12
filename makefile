build: test_compile

test_compile: main_compile
	gcc -Wall -Werror -std=c11 -o test_zstr test_zstr.c zstr.o	

main_compile: 
	gcc -Wall -Werror -std=c11 -c zstr.c

clean:
	rm zstr.o
	rm test_zstr
