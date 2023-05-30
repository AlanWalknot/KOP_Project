cd /d %windir%\syswow64

regsvr32 atl.dll
regsvr32 dispex.dll
regsvr32 jscript.dll
regsvr32 jscript9.dll
regsvr32 scrrun.dll
regsvr32 scrobj.dll
regsvr32 vbscript.dll
regsvr32 msxml3.dll
regsvr32 ole32.dll
regsvr32 oleaut32.dll
wscript /regserver