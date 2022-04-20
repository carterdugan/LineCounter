# LineCounter
Count your lines of code using this small python script

Not an avid python user, so the code is probably not very pythonic.

## Usage
#### `linecounter [OPTIONS] <EXTENSIONS> <PATH>`

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
    * Extensions can be specified individually or in collections. To list an extension individually, list it anywhere in the arguments before the path (include the period prefix). To create a collection of extensions, type the collection name, an equals sign, then all extensions separated by a comma. Two extensions are required for a collection. Collection syntax is as follows: `COLLECTION_NAME=.ex1,.ex2,.ex3,...` 

## Examples
`linecounter -t -f -d .c,.h,.cpp,.hpp /PATH/TO/DIRECTORY/OR/FILE`

`linecounter -tf --verbose-directory .py C=.c,.h /PATH/TO/DIRECTORY/OR/FILE`

(Note: This example assumes the script has been added to PATH)

[Video Demonstration](https://www.youtube.com/watch?v=Cy2LZVbd6bY)
