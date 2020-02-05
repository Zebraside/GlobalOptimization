cd Thirdparty || exit
unzip Qt.zip
cd ..

mkdir build || exit
cd build || return
cmake -DENABLE_GUI=OFF ..
make