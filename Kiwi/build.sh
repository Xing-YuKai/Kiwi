rm -rf build
mkdir build
cd build
cmake ..
make
cd ..
for i in */*.h;do cp $i ../lib_release/header/$i; done;
