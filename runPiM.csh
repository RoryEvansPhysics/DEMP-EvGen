#!/bin/csh

rm -f ./demp
g++ -o demp pimFermi.cxx `root-config --cflags --glibs`

#!/bin/csh

<< EOF ./demp
1000
1
EOF

