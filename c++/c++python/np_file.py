import numpy as np

def save_np(input_data, fn):
    a = np.array(input_data)
    print a
    a.tofile(fn)

def load_np(fn):
    b = np.fromfile(fn, dtype=np.float)
    print b.shape
    #s = ''
    #for i in b:
    #    s += "%1.1f "%i
    #print s
