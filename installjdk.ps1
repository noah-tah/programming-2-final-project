# Adoptium Temurin OpenJDK Installation Script
# Run this script as Administrator

# Configuration
$jdkVersion = "17.0.8"
$jdkBuild = "7" # Specific build number
$downloadUrl = "https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.8%2B7/OpenJDK17U-jdk_x64_windows_hotspot_17.0.8_7.msi"
$downloadPath = "$env:TEMP\temurin-openjdk.msi" # Sets temp download path for installer
$installPath = "C:\Program Files\Eclipse Foundation\Temurin JDK" # Installation dir

Write-Host "Starting Adoptium Temurin OpenJDK $jdkVersion installation..." -ForegroundColor Green

# Create download directory if it doesn't exist
if (!(Test-Path $env:TEMP)) { # Check if TEMP directory exists
    New-Item -ItemType Directory -Path $env:TEMP -Force | Out-Null
}

# Download OpenJDK installer
Write-Host "Downloading Adoptium Temurin OpenJDK from $downloadUrl..." -ForegroundColor Yellow
try {
    Invoke-WebRequest -Uri $downloadUrl -OutFile $downloadPath -UseBasicParsing # Download JDK installer from $downloadURL, saves to temp path $downloadPath
    Write-Host "Download completed successfully." -ForegroundColor Green
}
catch {
    Write-Host "Failed to download OpenJDK: $_" -ForegroundColor Red
    exit 1
}

# Install OpenJDK
Write-Host "Installing Adoptium Temurin OpenJDK..." -ForegroundColor Yellow
try {
    # Run the installer silently into $installPath
    Start-Process -FilePath "msiexec.exe" -ArgumentList "/i", $downloadPath, "/qn", "INSTALLLEVEL=1", "INSTALLDIR=`"$installPath`"" -Wait
    Write-Host "Installation completed." -ForegroundColor Green
}
catch {
    Write-Host "Failed to install OpenJDK: $_" -ForegroundColor Red
    exit 1
}

# Set environment variables
Write-Host "Setting up environment variables..." -ForegroundColor Yellow

# Find the installed JDK path (it might include version in subfolder)
$jdkFolder = Get-ChildItem -Path $installPath -Directory | Where-Object { $_.Name -match "java" } | Select-Object -First 1
if ($jdkFolder) {
    $javaHome = $jdkFolder.FullName
} else {
    $javaHome = $installPath
}

# Set JAVA_HOME system environment variable
try {
    [System.Environment]::SetEnvironmentVariable("JAVA_HOME", $javaHome, [System.EnvironmentVariableTarget]::Machine)
    Write-Host "JAVA_HOME set to $javaHome" -ForegroundColor Green
}
catch {
    Write-Host "Failed to set JAVA_HOME: $_" -ForegroundColor Red
}

# Add Java bin to PATH system environment variable
try {
    $currentPath = [System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::Machine)
    $javaBinPath = Join-Path -Path $javaHome -ChildPath "bin"
    
    if ($currentPath -notlike "*$javaBinPath*") {
        $newPath = "$currentPath;$javaBinPath"
        [System.Environment]::SetEnvironmentVariable("PATH", $newPath, [System.EnvironmentVariableTarget]::Machine)
        Write-Host "Added Java to system PATH" -ForegroundColor Green
    } else {
        Write-Host "Java bin path already in PATH" -ForegroundColor Yellow
    }
}
catch {
    Write-Host "Failed to update PATH: $_" -ForegroundColor Red
}

# Clean up
Remove-Item -Path $downloadPath -Force

# Verify installation
Write-Host "Verifying Java installation..." -ForegroundColor Yellow
try {
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path", [System.EnvironmentVariableTarget]::Machine)
    $javaVersion = & java -version 2>&1
    Write-Host "Java installed successfully:" -ForegroundColor Green
    Write-Host $javaVersion -ForegroundColor Cyan
}
catch {
    Write-Host "Java verification failed: $_" -ForegroundColor Red
}

Write-Host "Installation and setup complete!" -ForegroundColor Green
Write-Host "Note: You might need to restart your terminal or computer for the environment variables to take effect." -ForegroundColor Yellow