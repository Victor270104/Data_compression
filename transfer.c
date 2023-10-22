#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void binary_to_text(const char* input_filename, const char* output_filename)
{
    FILE* input_file = fopen(input_filename, "rb"); // Open the input file in binary read mode
    FILE* output_file = fopen(output_filename, "w"); // Open the output file in text write mode

    if (input_file != NULL && output_file != NULL) {
        // Read the input file one byte at a time, and write the ASCII representation to the output file
        int c;
        while ((c = fgetc(input_file)) != EOF) {
            fprintf(output_file, "%02X ", c);
        }

        fclose(input_file); // Close the input file
        fclose(output_file); // Close the output file
    }
}

int main(int argc, char const *argv[])
{
    binary_to_text(argv[1], "output.txt");
    return 0;
}   