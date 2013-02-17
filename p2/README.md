### Compile

First-element pivot

    cc -DPIVOT_TYPE=1 main.c -o main

Last-element pivot

    cc -DPIVOT_TYPE=2 main.c -o main

Median-of-three pivot

    cc -DPIVOT_TYPE=3 main.c -o main

### Run

    ./main <input.txt> <input size>
