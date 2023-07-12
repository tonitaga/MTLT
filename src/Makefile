CC = gcc -lstdc++
CFLAGS = -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage
TESTFLAGS = -lgtest
SRC = matrix_oop.cpp matrix_private.cpp matrix_operators.cpp
OBJ = matrix_oop.o matrix_private.o matrix_operators.o
TEST = test.cpp
LIB = matrix_oop.a
REPORT = GcovReport
OS := $(uname -s)



ifeq ($(OS), Darwin)
	CC+= -D OS_MAC
endif
ifeq ($(OS), Linux)
	CC+= -D OS_LINUX
	TESTFLAGS+= -lgmock -pthread
endif


all: clean matrix_oop.a

matrix_oop.a:
	$(CC) $(CFLAGS) $(SRC) -c
	ar rcs $(LIB) $(OBJ)

test: matrix_oop.a
	$(CC) $(CFLAGS) $(TEST) $(LIB) $(TESTFLAGS) -o test -g
	@./test
	@rm ./test

clean:
	@rm -rf *.{a,o,dSYM,out}
	@rm -rf leaks
	@rm -rf *.gch
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf gcov_report
	@rm -rf report



check: $(NAME)
	@echo -------------------CLANG_FORMAT------------------------
	@cppcheck $(SRC)
	@echo -------------------------------------------------------
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -style=file --dry-run --Werror $(SRC) $(TEST) *.cpp *.h
	@rm .clang-format
	@make leaks

leaks:
	@echo --------------------MEMORY_LEAKS-----------------------
	$(CC) $(CFLAGS) $(TEST) $(SRC) $(TESTFLAGS) -o leaks -g
	CK_FORK=no leaks --atExit -- ./leaks
	@rm ./leaks


gcov_report:
	$(CC) $(GCOVFLAGS) $(TEST) $(SRC) $(TESTFLAGS) -o $(REPORT)
	@chmod +x *
	@./GcovReport
	lcov --no-external -t "$(REPORT)" -o $(REPORT).info -c -d .
	genhtml -o report $(REPORT).info
	@rm -rf ./*.gcno ./*.gcda ./$(REPORT).*
	@open ./report/index.html
	@rm $(REPORT)
	@rm -rf *.dSYM

