def add1(a):
    with a.get_lock():
        a.value += 1
