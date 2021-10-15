# Filter

Implement the following image filters:

* Greyscale
* Reflection (mirroring)
* Blur
* Sobel Edge Detection

## Running

This program takes the following arguments as command line arguments.

* argv[0]: ./filter
* argv[1]: filter_to_apply from one of the following:
  * -g: greyscale
  * -r: for reflection (image mirroring on the x axis)
  * -b: blur
  * -e: Sobel edge detection
* argv[2]: input_file
* argv[3]: output_file

To run:
1. Make sure you've got a C compiler installed
2. Use the "./filter filter_to_apply input_file output_file" command.

## Technology stack

* The C library "math.h" was used to access the round function.