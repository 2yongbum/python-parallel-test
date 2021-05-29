import time
import threading
from multiprocessing import Process
import c_reader

def write_files():
    start = time.time()
    for x in range(4):
        f = open('%d.bmp'%(x), 'w')
        f.write('\0'*1024*1024*50)
        f.close()
    write_time = time.time() - start
    print('wirte time:', write_time)

def readfile(filename):
    a = open(filename).read()
    cnt = 0
    for x in a:
      cnt += 1

def serial_read():
    start = time.time()
    for x in range(4):
        # a = open('%d.bmp' % (x)).read()
        readfile('%d.bmp' % (x))
    read_time = time.time() - start
    print('serial read time:', read_time)

def thread_read():
    tr = []
    for x in range(4):
        fname = '%d.bmp' % (x)
        t = threading.Thread(target=readfile, args=(fname,))
        tr.append(t)

    start = time.time()
    for t in tr:
        t.start()

    for t in tr:
        t.join()
    read_time = time.time() - start
    print('threading read time:', read_time)

def process_read():
    pr = []
    for x in range(4):
        fname = '%d.bmp' % (x)
        p = Process(target=readfile, args=(fname,))
        pr.append(p)

    start = time.time()
    for t in pr:
        t.start()

    for t in pr:
        t.join()
    read_time = time.time() - start
    print('process read time:', read_time)

def c_thread():
    start = time.time()
    c_reader.c_thread()
    read_time = time.time() - start
    print('c thread read time:', read_time)

if __name__ == '__main__':
    write_files()
    serial_read()
    thread_read()
    process_read()
    c_thread()