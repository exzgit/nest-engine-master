#!/bin/bash

if [ ! -d "../build" ]; then
    echo "📁 Build directory not found. Creating directory..."
    mkdir -p ../build || { echo "❌ Failed to create build directory!"; exit 1; }
fi

cd ./build || { echo "❌ Failed to enter build directory!"; exit 1; }

echo "📦 Running CMake configuration..."
cmake .. || { echo "❌ Configuration failed!"; exit 1; }

echo "🔨 Building nest-engine project..."
cmake --build . || { echo "❌ Build failed!"; exit 1; }

echo "✅ Build completed successfully!"
