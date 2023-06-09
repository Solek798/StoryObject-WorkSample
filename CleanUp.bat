echo Delete Temporary Directories
 rd .\Binaries /S/Q
 rd .\Debug /S/Q
 rd .\Intermediate /S/Q
 del .\Saved\AutoScreenshot.png
 rd .\Saved\Autosaves /S/Q
 rd .\Saved\Crashes /S/Q
 rd .\Saved\Logs /S/Q
 rd .\Saved\Collections /S/Q
 rd .\Saved\Cooked /S/Q
 rd .\Saved\Crashes /S/Q
 rd .\Saved\Screenshots /S/Q
 rd .\Saved\StagedBuilds /S/Q
 rd .\Saved\Temp /S/Q
 rd .\Saved\AssetData /S/Q
 rd .\Saved\Config\CrashReportClient /S/Q
 for %%i in (.\Saved\Config\Windows\*.*) do if not "%%i" == ".\Saved\Config\Windows\PlayerSpawnTool.ini" if not "%%i" == ".\Saved\Config\Windows\LevelLoader.ini" if not "%%i" == ".\Saved\Config\Windows\PIEGameUserSettings0.ini" if not "%%i" == ".\Saved\Config\Windows\ProfilerSettings.ini" if not "%%i" == ".\Saved\Config\Windows\EditorPerProjectUserSettings.ini" del /q "%%i"

# 

echo 3rd Delete Temporary Plugin Directories 
for /D %%s in (.\Plugins\*) do ( del %%s\Binaries\Win64\UE4Editor*.* )
for /D %%s in (.\Plugins\*) do ( rmdir %%s\Intermediate /s/q )

PAUSE
