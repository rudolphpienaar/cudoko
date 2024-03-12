# cudoko 

_Simple word board solver_

[![Version](https://img.shields.io/docker/v/rudolphpienaar/cudoko?sort=semver)](https://hub.docker.com/r/rudolphpienaar/cudoko)
[![MIT License](https://img.shields.io/github/license/rudolphpienaar/cudoko)](https://github.com/FNNDSC/runj/blob/main/LICENSE)
[![ci](https://github.com/FNNDSC/runj/actions/workflows/ci.yml/badge.svg)](https://github.com/FNNDSC/runj/actions/workflows/ci.yml)

```

 ██████╗██╗   ██╗██████╗  ██████╗ ██╗  ██╗ ██████╗ 
██╔════╝██║   ██║██╔══██╗██╔═══██╗██║ ██╔╝██╔═══██╗
██║     ██║   ██║██║  ██║██║   ██║█████╔╝ ██║   ██║
██║     ██║   ██║██║  ██║██║   ██║██╔═██╗ ██║   ██║
╚██████╗╚██████╔╝██████╔╝╚██████╔╝██║  ██╗╚██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ 
                                                   

                - - - - - - - - - - - - -
                - o - - - - o - - - - o -
                - - k - - - k - - - k - -
                - - - o - - o - - o - - -
                - - - - d - d - d - - - -
                - - - - - u u u - - - - -
                - o k o d u c u d o k o -
                - - - - - u u u - - - - -
                - - - - d - d - d - - - -
                - - - o - - o - - o - - -
                - - k - - - k - - - k - -
                - o - - - - o - - - - o -
                - - - - - - - - - - - - -

```

## Abstract

`cudoko` is C++ rewrite of `wudoko` to explore the speed improvements of C++ over python.


## Notes

This project uses recursion to explore the board solution space. On python, this solution seems extremely slow.

## Installation

### Using ``make``

From the source root directory simply do:

```bash
make
```

which will build the `cudoko` executable.

### Usage 

For a given grid size, and a list of included/excluded words in separate files:

```bash
cudoko --gridSize 4x4 --wordInclude wordsInclude.txt --wordExclude wordsExclude.txt
```

## CLI Synopsis

```html

        --gridSize <Rows>x<Cols>
        The size of the board in rows, cols. This is a string and MUST have an 'x'
        separating the <rows> from <cols>, for example "10x7".

        --wordInclude <wordList>
        The file containing the list of words to include.

        [--wordExclude <wordList>]
        The file containing the list of words to exclude.

        [--version]
        If specified, print the version and exit.

        [--man]
        If specified, print a detail man page and exit.

        [--synopsis]
        If specified, print only an overview synposis and exit.

```

## Examples

_Watch this space!_

_-30-_
