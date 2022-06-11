import random

t = random.randint(1, 10)
print(t)
while t> 0:
    o = random.randint(10, 50)
    n = o
    l = 1
    print(o, n, l)
    list1 = random.sample(range(1, n+1), n)
    for i in list1:
        print('push', i, 0)
    list2 = random.sample(range(1, n+1), n)
    num = 0
    for i in list2:
        print(i, end = ' ')
        num += 1
        if(num == len(list2)):
            print('')
    t = t - 1 

