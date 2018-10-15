import func
import time
import ctypes
from multiprocessing import Process, current_process, Lock, Semaphore, Value, Array
from multiprocessing import sharedctypes

def func0(lock, a):
    lock.acquire()
    print a.value
    func.add1(a)
    #a.value += 1
    time.sleep(1)
    proc = current_process()
    print proc.name, proc.pid
    lock.release()

lock0 = Lock()
lock = Semaphore(2) # Semaphore(1) == Lock()
v = Value('f', 0.0)
a = Array('i', range(10))
sv = sharedctypes.Value('f', 0.0)
sa = sharedctypes.Array('i', range(10))
sub_proc0 = Process(target=func0, args=(lock, sa))
sub_proc1 = Process(target=func0, args=(lock, sa))
sub_proc2 = Process(target=func0, args=(lock, sa))

sub_proc0.start()
sub_proc1.start()
sub_proc2.start()

sub_proc0.join()
sub_proc1.join()
sub_proc2.join()

func0(lock, sa)
