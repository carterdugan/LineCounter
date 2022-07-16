# LineCounter
A command line tool to count your lines of code written in C.
Any contributions are welcome and appreciated.

## Build

Clone the repo

`git clone https://www.github.com/carterdugan/LineCounter`

Navigate to the LineCounter directory and build with `make`

## Usage
#### `linecounter [OPTIONS] <EXTENSIONS> <PATH>`

  * Options


  `-f` Output all files visited and their subtotal

  `-d` Output all directories visited and their subtotal

  `-b` Recursively count through subdirectories

  `-s` Output the subtotals of each specified extension

## Example
`linecounter -bs c h  /PATH/TO/DIRECTORY/OR/FILE`
