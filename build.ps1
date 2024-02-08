Write-Host "Starting build script."

gcc main.c lexer.c parser.c generate_code.c -o main -Wall -Wextra

if ($LastExitCode -eq 0) {
    Write-Host "Compilation successful."
} else {
    Write-Host "Compilation failed."
}

Write-Host "Completed build script."