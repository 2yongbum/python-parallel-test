# python-parallel-test
python parallel test (serial, python thread, multiprocess, c thread)

## Build
```
python3 setup.py build
```

## Run
```
cp build/lib.macosx-10.9-x86_64-3.8/c_reader.cpython-38-darwin.so .
python3 python_thread.py
```

## Output
```
[python] wirte time: 0.3109619617462158
[python] serial read time: 9.243072032928467
[python] threading read time: 8.948441982269287
[python] process read time: 5.112465858459473
[c] thread duration:0.128115s
[pyton] c thread read time: 0.12814998626708984
```
