# gtf2tab
[![Travis CI Shield](https://img.shields.io/travis/hebaishi/linter-gcc/master.svg?style=flat-square&label=Linux)](https://travis-ci.org/hebaishi/gtf2tab)
[![Travis CI Shield](https://img.shields.io/travis/hebaishi/linter-gcc/master.svg?style=flat-square&label=OSX)](https://travis-ci.org/hebaishi/gtf2tab)
[![AppVeyor CI](https://img.shields.io/appveyor/ci/hebaishi/gtf2tab/master.svg?style=flat-square&label=Windows)](https://ci.appveyor.com/project/hebaishi/gtf2tab)

Simple command-line application to convert GTF fields + attributes to a simple tab-delimited format.

## Installation instructions
The simplest method is to download the appropriate binary for your platform. Download the appropriate binary from [here](https://github.com/hebaishi/gtf2tab/releases/latest) and place it in the appropriate folder:

Platform | Path
------------ | -------------
Linux | `/usr/bin`
Mac OSX | `/usr/bin`
Windows | `C:\Windows`

If you're using cygwin on Windows, simply place the binary in the bin folder of your cygwin installation.

## **Important instructions for Windows users!!**
To run gtf2tab, you need to download the Visual C++ Redistributable package for Visual Studio 2015. You can get that from Microsoft's website by following [this link](https://www.microsoft.com/en-gb/download/details.aspx?id=48145).

## Build Instructions

Unless you really want to compile the program yourself, please ignore these instructions. It is much easier to simply download the pre-compiled binary by following the instructions above.
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
