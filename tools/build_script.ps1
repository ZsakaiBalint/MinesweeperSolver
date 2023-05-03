#go back to the project's build folder
Set-Location ../build

#build the program's and test's exe files
Write-Host "Building the project..."
cmake ../
cmake --build .
ctest -C Debug

#delete every file made by cmake
Write-Host "Deleting cmake files..."
Set-Location ../
mkdir temp
Copy-Item build/test/Debug/Tests.exe temp
Copy-Item build/Debug/MyExecutable.exe temp
Remove-Item -r build
Rename-Item "temp" "build"
