#include <iostream>
#include <fstream>
#include <string>
//#include <windows.h>
using namespace std;

//x86_64-w64-mingw32-c++ -static-libgcc -static-libstdc++ -mconsole -mdll -mnop-fun-dllimport -mthreads -municode -mwin32 -mwindows -fno-set-stack-executable -Wl,-V BloatremoverProgram.cpp -o BloatremoverProgram.exe

int main(int argc, char* argv[]) //allows for arguments to be passed in command execution.
{
	//ShowWindow(GetConsoleWindow(), SW_HIDE); //Runs cmd without being shown on screen AKA silent
	string sFile, sTemp, extFile = ".txt", sNames[500]; //creates a temporary string variable to hold the values in the file while itterating, This will also allow sFile to accept an argument in the CLI, sNames for a large enough array of strings.
	int x = 0, y = 0, z = 0, w = 0; // creates three place holder integer files
	string sList[] = { "Microsoft.XboxIdentityProvider", "Windows.CBSPreview", "Microsoft.XboxGameCallableUI", "Microsoft.Windows.NarratorQuickStart",
		"Microsoft.Windows.ParentalControls", "Microsoft.SkypeApp", "Microsoft.StorePurchaseApp", "Microsoft.People", "Microsoft.ZuneMusic",
		"Microsoft.XboxSpeechToTextOverlay", "Microsoft.XboxGameOverlay", "Microsoft.XboxApp", "Microsoft.Xbox.TCUI", "Microsoft.WindowsSoundRecorder",
		"Microsoft.WindowsMaps", "Microsoft.MixedReality.Portal", "Microsoft.MicrosoftOfficeHub", "Microsoft.Microsoft3DViewer", "Microsoft.GetHelp",
		"Microsoft.GamingApp", "Microsoft.BingWeather", "Microsoft.BingNews", "AppUp.IntelOptaneMemoryandStorageManagement", "MicrosoftTeams",
		"SpotifyAB.SpotifyMusic", "Disney.37853FC22B2CE", "Microsoft.WindowsAlarms", "microsoft.windowscommunicationsapps", "Microsoft.WindowsFeedbackHub",
		"Microsoft.WindowsStore", "Microsoft.Office.OneNote", "Microsoft.Getstarted", "Microsoft.MicrosoftSolitaireCollection", "Microsoft.YourPhone",
		"Microsoft.XboxGamingOverlay", "Microsoft.Todos", "Microsoft.ZuneVideo", "3dbuilder", "Wifi", "windowsalarms", "windowscommunicationsapps", "officehub"
		, "skypeapp", "getstarted", "zunemusic", "windowsmaps", "solitairecollection", "bingfinance", "zunevideo", "bingnews", "onenote", "people",
		"windowsphone", "bingsports", "soundrecorder", "bingweather", "xboxapp", "phone", "sway", "AdobePhotoshopExpress", "Candy", "Duolingo",
		"EclipseManager", "FarmVille", "Microsoft.3DBuilder", "Microsoft.BingNews", "Microsoft.BingTranslator", "Microsoft.BingWeather", "Microsoft.FreshPaint",
		"Microsoft.Getstarted", "Microsoft.Messaging", "Microsoft.MicrosoftOfficeHub", "Microsoft.MicrosoftSolitaireCollection", "Microsoft.NetworkSpeedTest",
		"Microsoft.Office.OneNote", "Microsoft.People", "Microsoft.SkypeApp", "Microsoft.WindowsAlarms", "Microsoft.WindowsFeedbackHub", "Microsoft.WindowsMaps",
		"Microsoft.XboxApp", "Microsoft.ZuneMusic", "Microsoft.ZuneVideo", "Netflix", "PandoraMediaInc", "PicsArt", "Twitter", "Wunderlist", "3dbuilder",
		"windowsalarms", "windowscommunicationsapps", "officehub", "skypeapp", "getstarted", "zunemusic", "windowsmaps", "solitairecollection",
		"bingfinance", "zunevideo", "bingnews", "onenote", "people", "windowsphone", "bingsports", "soundrecorder", "bingweather", "xboxapp",
		"phone", "sway", "Microsoft.XboxGamingOverlay", "Microsoft.MixedReality.Portal", "Microsoft.soundrecorder", "tiktok", "instagram", "spotify", "netflix", "windowsstore", "3dviewer" };

	ifstream xNames("NamesofApps.txt");
	if (xNames.is_open())
	{
		sFile = "NamesofApps.txt";
	}
	else if((argc != 2)) //checks if an argument was entered along with the program if not then it will run this asking for the name of the file.
	{
		cout << "This program will accept a text file list of apps to removed and remove them in windows 10/11. " << endl << endl;
		cout << "Please enter the name of the file to import: " << endl;
		cin.clear(); // clear cin buffer incase program run multiple times.
		sFile.clear();
		cin >> sFile; // puts name enters as the file name variable
	}
	else
		sFile = argv[1]; //if there was an argument passed along with the command puts the argument as the file name.

	w = sFile.length() - 4;
	while (!sFile.empty() && z <= 4) //this while loop will check if the last 4 charactes the user entered are the correct file extensiton .txt if not it will add it to the end
	{
		if (extFile[z] == sFile[w])
		{
			z++; w++;
		}
		else
		{
			sFile.append(".txt");
			break;
		}
	}
	
	ifstream fNames(sFile); // reopens the same file with corrected file extension
	if (!fNames.is_open()) // checks to make sure the file was actually opened
	{
		cout << "Error unable to open file\nPlease make sure the file is entered correctly or make sure file is in the same folder as this program." << endl; //reports error if not able to open
		cout << "closing program";
		system("pause");
		return 0;
	}

	while (getline(fNames, sTemp, '\n')) //gets each line in the file and puts them in the string array itterating the position each time
	{
		sNames[x] = sTemp;
		x++;
	}


	ofstream oNames("bloatremover.ps1"); //creates a file with the full string
	while (y < (x + 1)) // while loop to output the powershell command to the text file with the appropriate syntax and itterates for each value in the string array
	{
		oNames << "Get-AppxPackage -AllUsers *" << sNames[y] << "* | Remove-AppxPackage -erroraction 'silentlycontinue'" << endl;
		y++; // incrementes the position
		if (y == x) //tests that the value of 'y' does not meet the value of 'z' when it does it will break the loop
		{
			break;
		}
	}

	oNames.close();
	system("powershell Set-ExecutionPolicy -ExecutionPolicy Unrestricted -Scope CurrentUser"); //elevates the users restriction rights to unrestricted for powershell.
	system("powershell.exe -file bloatremover.ps1 -Verb RunAsUser"); //runs the powershell script as and admin
	system("powershell Set-ExecutionPolicy -ExecutionPolicy Restricted -Scope CurrentUser"); //re-enables restricted user rights for powershell
	remove("bloatremover.ps1"); //removes the powershell script once completed
	return 0; // end program
}



