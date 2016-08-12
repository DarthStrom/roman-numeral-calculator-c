# Roman Numeral Calculator Kata

A library which allows the addition and subtraction of Roman numerals.

Requires the Check unit testing framework.

Run `make` to build and run the tests.

You can also run `make clean` to remove build artifacts or
`make build/libroman_calculator.a` to just build the library.

## Some considerations

- The romans had no way of representing negative numbers, however I felt it would be more useful for the library to handle this by appending a `-` than to give some sort of error.
- In the `int_to_char` function, there is an `assert`.  This is there to guard against potential changes to `base_values` and `glyphs` so that they are guaranteed to have the same number of elements.  I could not think of an external way to test this.
