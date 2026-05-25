[![License](https://img.shields.io/github/license/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/blob/main/LICENSE)
[![Last Commit](https://img.shields.io/github/last-commit/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/commits)
[![Repo Size](https://img.shields.io/github/repo-size/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution)
[![Stars](https://img.shields.io/github/stars/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/stargazers)
[![Forks](https://img.shields.io/github/forks/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/network/members)
[![Top Language](https://img.shields.io/github/languages/top/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution)
[![Release](https://img.shields.io/github/v/release/Evgenk2020/wort-agar-solution)](https://github.com/Evgenk2020/wort-agar-solution/releases)
[![Version](https://img.shields.io/badge/version-1.0.3-blue)](https://github.com/Evgenk2020/wort-agar-solution)

# Nutrition medium dilution

Lab utility for determining the concentration of a wort agar medium solution via preparing from natural raw components

Run it with specified keys

```

wort -d | -df [data...]

```

Using `-df` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/.img/screen.png)


.sh file example for running in terminal

```SH

#!/bin/bash

wort -d 21 4.5 300
echo "----------------"
wort -d 21 3 250
echo "----------------"
wort -d 15 4.5 200
echo "----------------"
wort -d 20 5 280
echo "----------------"
wort -d 20.5 4.5 250

exec $SHELL

```

.sh file example for writing to `.csv`

```SH

#!/bin/bash

wort -df 21 4.5 300 
wort -df 21 3 250
wort -df 15 4.5 200
wort -df 20 5 280
wort -df 20.5 4.5 250

exec $SHELL

```
<hr>

You need to be installed on your Linux system previously:

- GCC g++
- CMake

(Fedora/CentOS Stream)
- rpm-build

On Fedora based systems run
<br>

```SH

sudo dnf group install development-tools
sudo dnf install cmake
sudo dnf install rpm-build

```

On Debian based systems run
<br>

```SH

sudo apt update
sudo apt install build-essential
sudo apt install cmake

```

On other systems see the details of your distro

<hr>

<b>To compile and run the utility (Fedora/CentOS Stream)</b>

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

<b>If using either than Fedora/CentOS Stream</b>

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
@software{chlorophyll_linux_2026,
  author       = {Kopilov, Evheny},
  title        = {Lab chemical utility for determining the concentration of a wort agar medium solution},
  month        = may,
  year         = 2026,
  publisher    = {GitHub},
  version      = {1.0.3},
  url          = {[https://github.com/Evgenk2020/wort-agar-solution](https://github.com/Evgenk2020/wort-agar-solution)}
}