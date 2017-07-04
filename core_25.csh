#!/bin/csh

source /home/zahmed/goGenerator.csh

<< EOF ./demp
200000
25
EOF

	@ c = $c + 1
end
