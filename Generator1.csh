#!/bin/csh

rm -f core_*.csh

rm -f ./demp
g++ -o demp pimFermi.cxx `root-config --cflags --glibs`

set c=0
set d=10000000
while ( $c < 10 )

cp ../core1.csh core_$c.csh

sed -i -e 's/1111/'$d'/g' ./core_$c.csh

sed -i -e 's/2222/'$c'/g' ./core_$c.csh

chmod 777 ./core_$c.csh

gnome-terminal -e ./core_$c.csh

	@ c = $c + 1
end

