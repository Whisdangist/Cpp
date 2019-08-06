#!/usr/bin/python2
# coding=utf-8
from random import random, shuffle

# 不得不吐槽我自己 这代码写得又臭又长 生成数据用的脚本写起来比写算法本身还费劲
# 这丫辣鸡代码耗了我两个半小时，有这时间都能再刷两道题了

V = 100
E = int(((V-1)*V/2))
K = int(V / 10)

all_edges = []
selected_edges = []
for i in range(V):
    for j in range(V):
        if i != j:
            all_edges.append((i, j))
shuffle(all_edges)

p = [0] * V
for num in range(V):
    index = 0
    while index == 0 or index == V:
        index = int(random()*V)
    tag = 0
    while tag == 0 or tag == K+1:
        tag = int(random()*(K+1))
    tmp_p = random()
    selected_edges.append((num, (num+index) % V, tag, tmp_p))
    all_edges.remove((num, (num+index) % V))
    p[num] = tmp_p

for num in range(E-V):
    (i, j) = all_edges.pop()
    tag = 0
    while tag == 0 or tag == K+1:
        tag = int(random()*(K+1))
    tmp_p = random()
    p[i] += tmp_p
    edge = (i, j, tag, tmp_p)
    selected_edges.append(edge)

p1 = []
assert len(selected_edges) == E
for i in range(E):
    edge = selected_edges[i]
    p1.append(round(edge[3] / p[edge[0]], 2))

check_sum = [0] * V
for i in range(E):
    check_sum[selected_edges[i][0]] += p1[i]

for i in range(V):
    if abs(check_sum[i] - 1) > 1e-3:
        # process1
        delta = 1 - check_sum[i]
        for j in range(E):
            edge = selected_edges[j]
            if edge[0] == i:
                p2 = p1[j] + delta
                if 0+1e-3 <= p2 <= 1-1e-3:
                    p1[j] = p2
                    check_sum[i] += delta
                    break
        # process2
        while abs(check_sum[i] - 1) > 1e-3:
            for j in range(E):
                edge = selected_edges[j]
                a1 = edge[0]
                if a1 == i:
                    if delta < -1e-3:
                        a = p1[j]
                        while p1[j] - 0.01 > 1e-3 and abs(delta) > 1e-3:
                            p1[j] = p1[j] - 0.01
                            check_sum[i] -= 0.01
                            delta = delta + 0.01
                    if delta > 1e-3:
                        while p1[j] + 0.01 > 0.01+1e-3 and abs(delta) > 1e-3:
                            p1[j] = p1[j] + 0.01
                            check_sum[i] += 0.01
                            delta = delta - 0.01

# final check
for s in check_sum:
    assert abs(s-1) < 1e-3

with open("input.txt", "w") as fo:
    fo.write("%d %d %d\n" % (V, E, K/2))
    for i in range(E):
        edge = selected_edges[i]
        fo.write("%d\t%d\t%d\t%.2f\n" % (edge[0], edge[1], edge[2], p1[i]))
    s = range(1, K+1)
    shuffle(s)
    for i in range(K/2):
    	fo.write("%d " % s[i])
    fo.write("\n")

pass
