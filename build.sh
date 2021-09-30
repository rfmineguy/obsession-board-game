cd build
echo "Cmake running Unix Makefiles"
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

echo "Cmake building files"
cmake --build .
#clear
./obsession
