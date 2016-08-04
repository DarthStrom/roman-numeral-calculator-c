CFLAGS=-g -O2 -Wall -Wextra

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/check_*.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/calculator.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))


# Target Build
all: $(TARGET) $(SO_TARGET) test

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# Tests
test: CFLAGS += $(TARGET)
test: $(TESTS)
	@for file in $(TESTS) ; do \
		$$file ; \
	done

# Cleaning
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
