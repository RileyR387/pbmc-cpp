# Powerball Monte Carlo in C++ with boost
c++ environment tester first, CPU stresser second, and a few million reasons not to play the powerball.

Recently built with boost-1.72.0 on OSX and boost-1.65.1 on ubuntu-18.04

**WARNING**: Read the license, there's no warrenty and this thing will use some juice.

### Dependencies

Requires libboost-dev >=1.48.0 for includes and libboost >=1.48.0 libs for shared objects

OSX:
```sh
brew install boost
```

ubuntu >= 18.04:

```sh
apt-get install libboost-all-dev
```

RH/Centos:

```sh
yum install boost boost-devel
```

## Build and Run

```sh
git clone https://github.com/RileyR387/pbmc-cpp.git
cd pbmc-cpp
make && ./bin/pbmc --help
```

### Program Options

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

