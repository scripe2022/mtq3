#!/usr/bin/bash
g++ -o graph_gen graph_gen.cpp -O3 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2 -DLOCAL
g++ -o data data.cpp -O3 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2 -DLOCAL
g++ -o brute brute.cpp -O3 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2 -DLOCAL
for i in $(seq 1 1 1000)
do
    if [[ $(($i % 1)) -eq 0 ]]; then
        echo $i
    fi
    python3 gen.py > data.in
    ./data < data.in > data.out
    if [[ $? -ne 0 ]]; then
        echo "RE!!"
        break
    fi
    ./brute < data.in > data.ans
    diff data.out data.ans
    if [[ $? -ne 0 ]]; then
        break
    fi
done