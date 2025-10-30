echo "Creating build directory..."
mkdir -p ../build
cd ../build || exit 1
echo "Running CMake..."
cmake ..
echo "CMake configuration complete."
