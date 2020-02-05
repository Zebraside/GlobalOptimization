mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=../Thirdparty/Qt/lib/cmake  -DENABLE_GUI=ON ..
make