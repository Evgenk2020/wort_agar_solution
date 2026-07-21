[![Version](https://img.shields.io/badge/version-1.0.3-blue)](https://github.com/Evgenk2020/wort-agar-solution)
[![Latest Release](https://img.shields.io/github/v/release/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/releases)
[![License](https://img.shields.io/github/license/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/blob/main/LICENSE)
[![Last Commit](https://img.shields.io/github/last-commit/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/commits)
[![Repo Size](https://img.shields.io/github/repo-size/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution)
[![Stars](https://img.shields.io/github/stars/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/stargazers)
[![Forks](https://img.shields.io/github/forks/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/network/members)
[![Top Language](https://img.shields.io/github/languages/top/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution)


# 🧪 Nutrition medium dilution

Lab utility for determining the concentration of a wort agar medium solution via preparing from natural raw components

Run it in interactive mode

```

wort

```

or run it with specified keys

```

wort -s <src> -t <trg> -v <vol> [-o | -f | -j]

```

Using `-f` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/.img/screen.png)

Using `-j` key you may get output in JSON format

.sh file example to run in terminal

```SH

#!/bin/bash

echo "measurement 1"
wort -s 12 -t 4 -v 500 -o
echo "----------------"

echo "measurement 2"
wort -s 15 -t 5 -v 1000 -o
echo "----------------"

exec $SHELL

```

.sh file example for writing to `.csv`

```SH

#!/bin/bash

wort -s 12 -t 4 -v 500 -f
wort -s 15 -t 5 -v 1000 -f
wort -s 10 -t 3 -v 300 -f

exec $SHELL

```

.sh file example for JSON output

```SH

#!/bin/bash

wort -s 12 -t 4 -v 500 -j
wort -s 15 -t 5 -v 1000 -j

exec $SHELL

```
<hr>

## 🛠 Dependencies

To build the project from source, you will need:
* A compiler with full **C++23** support (GCC >= 14, verified with GCC 16)
* **CMake** (>= 3.31)
* **RapidJSON** - a fast, header-only JSON parser and generator library
* **rpm-build** - for Fedora/CentOS Stream

## On Fedora based systems run

```SH

sudo dnf group install development-tools
sudo dnf install cmake rpm-build rapidjson-devel

```

## On Debian based systems run

```SH

sudo apt update
sudo apt install build-essential cmake rapidjson-dev

```

On other systems see the details of your distro

<hr>

## To compile and run the utility (Fedora/CentOS Stream)

1. Clone the Repository

```SH

git clone https://github.com/Evgenk2020/wort-agar-solution
cd wort-agar-solution

```

2. Build the Project with `.rpm` setup package for Fedora/CentOS Stream by default

```SH

./build.sh
cd build

```

3. Install `.rpm` package from build folder

```SH

sudo dnf install *.rpm

```

4. Run the application in terminal directly

```SH

wort -h

```

<hr>

## If using other than Fedora/CentOS Stream

1. Clone the Repository

```SH

git clone https://github.com/Evgenk2020/wort-agar-solution
cd wort-agar-solution

```

2. Change the string `set(assemble_tgz OFF)` to `set(assemble_tgz ON)` in CMakeLists.txt

```SH

nano CMakeLists.txt

```

3. Build the Project

```SH

./build.sh

```

4. Move `.tar.gz` file from `build` folder to any folder and unpack it

5. Run the program to check it from unpacked folder

```SH

./wort -h

```

For more convenience add the application path into `.bashrc` file

```SH

export PATH="$PATH:/path/to/application/folder"

```

This will allow you to run the application in terminal directly

```SH

wort -h

```

<hr>

## 📑 Citation & Academic Use

If you use this utility or code in your scientific research, lab analysis, or publications, please cite it using the following format. 

GitHub automatically parses the `CITATION.cff` file, so you can easily copy the citation in **APA** or **BibTeX** format directly from the repository sidebar (look for the **"Cite this repository"** button).

### BibTeX Format
```bibtex
@software{wort_agar_solution_2026,
  author       = {Kopilov, Evheny},
  title        = {wort-agar-solution: Nutrition medium dilution for laboratory analysis},
  month        = may,
  year         = 2026,
  publisher    = {GitHub},
  version      = {1.0.3},
  url          = {https://github.com/Evgenk2020/wort-agar-solution}
}
