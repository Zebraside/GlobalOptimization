cd Thirdparty || exit
unzip Qt.zip
cd ..

mkdir build || exit
cd build || return
cmake -DCMAKE_PREFIX_PATH=/home/runner/work/GlobalOptimization/GlobalOptimization/Thirdparty/Qt/lib/cmake  -DENABLE_GUI=ON ..
make