


if ((Get-ChildItem -Filter "build" -Attributes Directory).Length -eq 1)
{
    Remove-Item -Force -Recurse "build"
}

