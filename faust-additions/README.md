
# Usage

```
add_faust_additions.tcsh  <path to root of faust installation>
       Once this script is run and the additions files are copied 
       to the faust installation, two
       "make installs" will need to be run.

       % cd <path to the root of faust installation>
       % sudo make -f Makefile.sam install
       % cd <path to the root of faust installation>/tools/faust2appls
       % sudo make -f Makefile.sam  install
```