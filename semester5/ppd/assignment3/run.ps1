param(
    [Parameter(Mandatory = $true)][string]$Exe,
    [Parameter(Mandatory = $true)][int]$Processes,
    [int]$Runs = 10
)

$mpiexec = "C:\Program Files\Microsoft MPI\Bin\mpiexec.exe"
$culture = [System.Globalization.CultureInfo]::InvariantCulture
$times = @()

for ($i = 1; $i -le $Runs; $i++) {
    if ($Processes -gt 0) {
        $output = & $mpiexec -n $Processes $Exe
    } else {
        $output = & $Exe
    }

    $line = $output | Where-Object { $_ -match 'Time:\s*([0-9.eE+-]+)' } | Select-Object -First 1
    if (-not $line) {
        Write-Host "Run ${i}: no 'Time:' line in output:"
        $output | ForEach-Object { Write-Host "  $_" }
        exit 1
    }
    $null = $line -match 'Time:\s*([0-9.eE+-]+)'
    $t = [double]::Parse($Matches[1], $culture)
    $times += $t

    $check = ""
    $resultLine = $output | Where-Object { $_ -match '^Result:' } | Select-Object -First 1
    if ($resultLine) {
        $check = if ($resultLine -match 'correct$' -and $resultLine -notmatch 'INCORRECT') { "  OK" } else { "  MISMATCH ($resultLine)" }
    }
    Write-Host ("Run {0,2}: {1} ms{2}" -f $i, $t.ToString($culture), $check)
}

$avg = ($times | Measure-Object -Average).Average
Write-Host ("Average over {0} runs: {1} ms" -f $Runs, $avg.ToString("0.###", $culture))
