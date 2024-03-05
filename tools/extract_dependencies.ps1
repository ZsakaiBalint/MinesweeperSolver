# Define the path to the dependencies.zip file
$zipFilePath = ".\dependencies.zip"

# Define the path where you want to extract the contents
$extractPath = "..\"

# If the extract path doesn't exist, create it
if (-not (Test-Path $extractPath)) {
    New-Item -ItemType Directory -Path $extractPath | Out-Null
}

# Expand the ZIP file to the extract path
Expand-Archive -Path $zipFilePath -DestinationPath $extractPath -Force