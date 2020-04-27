rm -rf build
mkdir build
cmake . -B build
cd build
make
cd ..
for i in */*.h;do cp $i ../lib_release/header/$i; done;
