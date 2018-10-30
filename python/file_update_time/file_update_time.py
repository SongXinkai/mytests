import os
import time

data_root = "training_data"
dir_sttime = {}
for f in os.listdir(data_root):
    dir_sttime[f] = os.stat(os.path.join(data_root, f)).st_mtime - time.time()
for f, t in sorted(dir_sttime.items(), key=lambda x: x[1], reverse=True):
    if t < 3600.0:
        print "file %s: update %.1f seconds ago"%(f,t)
    elif t/3600.0 < 24.0:
        print "file %s: update %.1f hours ago"%(f,t/3600.0)
    else :
        print "file %s: update %.1f days ago"%(f,t/3600.0/24.0)
