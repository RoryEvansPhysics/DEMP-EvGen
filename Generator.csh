#!/bin/csh

rm -f ./core*.csh

rm -f ./demp
g++ -o demp pimFermi.cxx `root-config --cflags --glibs`

set c=0
set d
while ( $c < 10 )

cp ../core1.csh core$c.csh

sed -i -e 's/222/'$c'/g' ./core$c.csh

@ d = $c * 1

sed -i -e 's/111/'$d'/g' ./core$c.csh

gnome-terminal -e ./core$c.csh

	@ c = $c + 1
end

