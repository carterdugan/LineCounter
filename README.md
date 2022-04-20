# LineCounter
Count your lines of code using this small python script

Not an avid python user, so the code is probably not very pythonic.

## Usage
#### `linecounter [OPTIONS] <PATH> <EXTENSION_1>,[EXTENSION_2],...,[EXTENSION_N]`

  * Options

  `-p --exact-path` Specfies that the provided path is the exact path

  `-f --verbose-file` Output all files visited and their subtotal

  `-d --verbose-directory` Output all directories visited and their subtotal

  `-e --verbose-errors` Output all encountered errors

  `-s --subtotals` Output the subtotals of each specified extension

  `-t --tree` Recursively search down the directory tree

  `-g --include-git` Include git directories and files, you probably won't want to use this.

  `-w --whitespace` Include linebreak white space when counting lines of code

  * Path
    * Path may be either exact or relative. See `--help` for more details. Specified paths must use '/' separators regardless of operating system.

  * Extensions
    * Extensions for files you want to be counted should be listed at the end seperated by commas.
    * Each extension should consist of a period followed by the extension itself.

## Examples
`linecounter -t -f -vd /PATH/TO/DIRECTORY/OR/FILE .c,.h,.cpp,.hpp`

`linecounter -tf --verbose-directory /PATH/TO/DIRECTORY/OR/FILE .c,.h,.cpp,.hpp`

(Note: This example assumes the script has been added to PATH)

[Video Demonstration](https://www.youtube.com/watch?v=Cy2LZVbd6bY)
