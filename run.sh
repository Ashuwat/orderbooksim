EXECUTABLE=./build/Debug/myapp.exe

for SEED in {1..100}; do
    echo "Running with seed $SEED"
    $EXECUTABLE --seed "$SEED"
done