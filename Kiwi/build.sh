rm -rf ../lib_release
rm -rf build
mkdir build
cd build
cmake ..
make
cd ..

mkdir -p ../lib_release/header/Base
mkdir -p ../lib_release/header/Network
mkdir -p ../lib_release/header/Reactor
mkdir -p ../lib_release/header/ThreadPool
for i in */*.h;do cp $i ../lib_release/header/$i; done;
