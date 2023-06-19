# Nutrition medium dilution
Lab utility for determining the concentration of a wort agar medium solution via preparing from natural raw components

Run it with specified keys

```

wort [-d|-df] [initial_concentration_%] [ultimate_concentration_%] [filtrate_volume_ml]

```

Using `-df` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/img/screen.png)

Use `build.sh` and `run.sh` from the `src` folder to compile and run the application

For more convenience you may add path to the application into `.bashrc` file

```

export PATH=$PATH:/%path_to_application_folder%/

```

and then use simple SH schemes e.g.

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

or for writing `wort-dada.csv` use

```SH

#!/bin/bash

wort -df 21 4.5 300 
wort -df 21 3 250
wort -df 15 4.5 200
wort -df 20 5 280
wort -df 20.5 4.5 250

exec $SHELL

```

This program runs with `uk_UA.utf8` locale. It can be changed in `output.cpp`

```C++

std::locale m_loc("uk_UA.utf8");

```

To see locale list use

```SH

locale -a

```
