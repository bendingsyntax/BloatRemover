# BloatRemover
Bloatremover is a personal program i wrote to remove some of the bloat apps that come pre installed with windows.
  Specifically one run as administrator (probably wont work on windows if compilled with g++ on linux, will attempt to fix)
  first it will check if there is a file "NamesofApps.txt" in the same folder the one in this repo is a generic list (to include more apps simply add a new line with the app name)
  if not then the program will ask for a text file (it will attempt to auto add '.txt' on input if forgotten) third option is a built in list but iv yet to figure out how to do so.
  once it has a list it will create a small .ps1 file with the correct commands (Get-AppxPackage -AllUsers *" << sNames[y] << "* | Remove-AppxPackage -erroraction 'silentlycontinue')
  then it will set the current users restriction level to unrestricted, run the .ps1 file created and then once completed change from unrestricted to restricted as well as delete the created .ps1 file

Run as Admin and it should work on windows now (BloatRemover.exe and NamesofApps.txt) 

Added MD5 File and the BloatRemover.exe should provide this MD5: 54e52ce18c303375242df1f26d61265f

I did not include the windows store and screen sketch but they can be added to the "NamesofApps.txt" file

Microsoft.WindowsStore

**WindowsStore**
