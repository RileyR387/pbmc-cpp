<h3>Dependencies</h3>

Requires libboost-dev >=1.48.0 for includes and libboost >=1.48.0 libs for shared objects

ubuntu 12.04: 

```sh
apt-get install libboost1.48-all-dev
```

ubuntu >= 16.04:

```sh
apt-get install libboost-all-dev
```

RH/Centos:

```sh
yum install boost boost-devel
```

<h3>Build and run:</h3>

```sh
git clone https://github.com/RileyR387/pbmc-cpp.git
cd pbmc-cpp
make && ./bin/pbmc --help
```

<h4>Program Options</h4>

```sh
Allowed options:
  -h [ --help ]         produce this message
  -l [ --lines ] arg    Lines to play
  -n [ --nCount ] arg   Number of regular balls
  -p [ --pCount ] arg   Number of power balls
  --nMax arg            Max value of the regular ball(s)
  --pMax arg            Max value of the power ball(s)
  -t [ --threads ] arg  Number of threads to create
  -g [ --generator ]    Use a unique generator for each thread. (Faster, no 
                        generator mutex lock wait), potentially less random
  -r [ --reseed ]       NOTE: Requires -g ; Reseed Every 1 million drawings per
                        thread, each thread is idealy offset by 3.14 seconds; 
                        potentially less random even more
```

