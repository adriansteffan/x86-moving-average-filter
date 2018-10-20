# x86 Moving Average Filter 

This is a filter for cleaning up noisy signals using a moving-average filter with free weighting. The main part of the filtern is implemented in x86 Assembler with a framework programm written in C. By using the rotation feature of the FPU Stack, this filter function saves on memory accesses and outperforms the standard c-library functions when calculating this specific filtering formula.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

At this point in time, the project only runs on 32-Bit Linux systems (tested on [Ubuntu](https://www.ubuntu.com/download/alternative-downloads)).
 
You will need the commandline tools nasm, make and gcc (also, gcc-multilib seems to solve some compatibility issues). Use the following command to install them:

```
sudo apt install nasm make gcc gcc-multilib 
```

### Building

After cloning the repository, simply run the following commands:

```
cd x86-moving-average-filter
make
```


## Usage

The filter uses the following formula to adjust the : 

g<sub>k</sub> = (alpha⋅g<sub>k-1</sub>+beta⋅f<sub>k</sub>)/(alpha+beta) with 
g<sub>0</sub> = s (starting value)

(f refers to the unfiltered value, while g is an already filtered value)


To use the filtering function, you first need to save your source signal in a textfile as integers seperated by newline characters. After that, you can call the function with your specified parameters:

```
./movafilter [float alpha] [float beta] [int starting value] [source filepath] [output filepath]
```


## Running the tests

There are built-in test cases to cross validate the asm routine with a c-function. 
Use the following command to run the tests:

```
movafilter runtest
```

Note: Small differences between the filtered values and the validation are not necessarily a sign of the filter malfunctioning.
They are probably be caused by differences in the handling of floating point between the c standard library and the assembler routine
(especially big floating-point values seem to be affected here). It is best to look at the actual output of the validation function when deciding if the asm filter is working correctly.


## Authors

* **Adrian Steffan** - *Coding* [adriansteffan](https://github.com/adriansteffan)
* **Vera Kowalczuk** - *Documentation and project structure* [verakowalczuk](https://github.com/verakowalczuk)
* **Uzay Gök** - *Testcase design*





	