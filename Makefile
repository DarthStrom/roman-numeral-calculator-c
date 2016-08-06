CFLAGS=-g -O2 -Wall -Wextra -pthread
LDLIBS=-pthread -lcheck_pic -lrt -lm -lcheck

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/check_*.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libroman_calculator.a

# Target Build
all: $(TARGET) tests

$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

build:
	@mkdir -p build

# Tests
.PHONEY: tests
tests: LDLIBS += $(TARGET)
tests: $(TARGET) $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --leak-check=full --log-file=/tmp/valgrind-%p.log" $(MAKE)

# Cleaning
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
