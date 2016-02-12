# gtf2tab
[![Build Status](https://travis-ci.org/hebaishi/gtf2tab.svg?branch=master)](https://travis-ci.org/hebaishi/gtf2tab)

Simple command-line application to convert GTF fields + attributes to a simple tab-delimited format.

## Build Instructions

You need to install the appropriate CMake version for your platform. To build:

### On Mac OSX / Linux:

Clone the gtf2tab repository, and run the following commands to build and install gtf2tab:

```bash
cd gtf2tab
mkdir bin
cd bin
cmake ..
make
sudo make install
```

To build test executables, do:
```bash
cmake -DBUILD_TESTS=ON ..
make
cd tests
ctest
```

### On Windows

1. Download the zip file of the repository, and extract it to a folder of your choosing.
2. Create a new folder called ```bin ``` in the gtf2tab directory.
3. Open CMake-GUI, and point it to the source directory ```gtf2tab``` and the binary directory ```gtf2tab/bin```.
4. Click ```Configure```, select your build system, then click ```Generate```.
5. Navigate to the ```bin``` directory. You will then need to follow the instructions appropriate for your build system to build the binary.

## Usage Instructions

```
Usage: gtf2tab OPTIONS INPUT_FILE

Options:
    If no input file is specified, standard input is used

    -a ATTRIBUTE_LIST    Comma-separated list of attributes. Examples
                         for an Ensembl GTF are gene_id and gene_biotype.

    -f FIELDLIST         GTF fields to print, as a comma-separated list of
                         integers. Hyphens can also be used to specify a range
                         of values

    -t FEATURETYPE       Type of GTF feature to print.

    -o OUTPUTFILE        Output filename. Default is standard output

    -h                   Display help

Example:
     To extract columns 1-4 and gene_id, gene_biotype
     from file.gtf the command would be:

     gtf2tab -f 1-4 -a gene_id,gene_biotype file.gtf
```
