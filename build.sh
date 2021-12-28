#check if the build folder is not made yet
#  this would happen just after cloning the repository 'sfml-linux-staring-template'

if [ ! -d "${PWD}/build/" ]; then
    echo "Build folder doesn't exist, creating it."
    mkdir build
fi

cd build
echo "Cmake running Unix Makefiles"
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

echo "Cmake building files"
cmake --build .
#clear
./obsession
