#!/bin/bash

status=true

cat > AB.csv << EOF
2,1,-1,1
-3,-1,2,1
-2,1,2,6
EOF

cat > expected.csv << EOF
x
1
2
3
EOF

make release > /dev/null 2>&1

./gauss AB.csv > output.csv 2>/dev/null

if cmp -s expected.csv output.csv; then
    echo "Integration test PASSED"
else
    echo "Integration test FAILED"
    status=false
fi

rm -f AB.csv expected.csv output.csv

$status