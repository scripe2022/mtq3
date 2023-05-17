#!/usr/bin/python3
import random
import subprocess

n = 50
m = 90
pKey = 1
pDoor = 2
graph = subprocess.check_output(['./graph_gen', str(n), str(m)]).decode()

dot_file = "graph.dot"
input_file = "data.in"

def graphviz_dump():
    lines = graph.split('\n')
    output = "digraph {\n   "
    data = str(n) + " " + str(m) + " "
    keyV = []
    for i in range(n):
        output += " " + str(i)
        key = random.randint(0, pKey)
        if (key == 0):
            output += "[color=\"green\"]"
            keyV.append(i)
    data += str(len(keyV)) + "\n"
    for i in range(len(keyV)):
        data += str(keyV[i]) + " "
    if (len(keyV)): data += "\n"
    output += ";\n"
    for line in lines:
        if (line == ""): continue
        u, v = line.split(' ')
        door = random.randint(0, pDoor)
        door_str = ""
        data += line
        if (door == 0):
            door_str = "color=\"red\""
            data += " 1\n"
        else:
            data += " 0\n"
        output += "    " + str(u) + " -> " + str(v) + "[ " + door_str + "];\n"
    output += "}"
    with open(dot_file, 'w') as f:
        print(output, file=f)
    with open(input_file, 'w') as f:
        print(data, file=f)

graphviz_dump()