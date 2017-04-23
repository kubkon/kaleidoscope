# kaleidoscope

[![Build Status](https://travis-ci.org/kubkon/kaleidoscope.svg?branch=master)](https://travis-ci.org/kubkon/kaleidoscope)

My implementation of Kaleidoscope language as per the LLVM tutorial [here](http://llvm.org/docs/tutorial).

## Building
Make sure you have `cmake` (>=2.8.7) and `clang` (>=3.6) installed. Then simply navigate to the build folder and execute the following commands:

```
$ cd build
$ cmake ..
$ make
```

## Testing
The project uses GoogleTest framework for testing. After having successfully built the project, you can run the tests in two ways:

```
$ cd build
$ ./tests/tests
```

Or:

```
$ cd build
$ ctest
```

The former will run GoogleTest binary directly and will provide a more detailed output.

## License
MIT license, see [LICENSE](LICENSE).

