# LineCounter
Count your lines of code using this small python script

Not an avid python user, so the code is probably not very pythonic.

## Usage
#### `linecounter [OPTIONS] <PATH> <EXTENSION_1>,[EXTENSION_2],...,[EXTENSION_N]`

  * Options
    * There are currently options to specify different verbose outputs and recursively moving down
the directory tree. For a list of options, use 'linecounter --help'

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