#include "LoadMap.h"

void loadMap(int level, char MapArray[50][150], char FogArray[50][150])
{
	string mapname = " ";
	switch (level)
	{
		case 0:
			mapname = "Maps_Text/Splash_Screen.txt";
			break;
		case 1:
			mapname = "Maps_Text/Main_Menu.txt";
			break;
		case 2:
			mapname = "Maps_Text/Instructions.txt";
			break;
		case 3:
			mapname = "Maps_Levels/Tutorial.txt"; 
			break;
		case 4: 
			mapname = "Maps_Levels/Levers.txt"; //Level 1 Map
			break;
		case 5: 
			mapname = "Maps_Levels/Questions.txt"; //Level 2 Map
			break;
		case 6:
			mapname = "Maps_Levels/Boxes.txt"; //Level 3 Map
			break;
		case 7:
			mapname = "Maps_Levels/Teleportal.txt"; //Level 4 Map
			break;
		case 8:
			mapname = "Maps_Text/Story/Start.txt";
			break;
		case 9:
			mapname = "Maps_Text/Story/Tutorial.txt";
			break;
		case 10:
			mapname = "Maps_Text/Story/Levers.txt";
			break;
		case 11:
			mapname = "Maps_Text/Story/Questions.txt";
			break;
		case 12:
			mapname = "Maps_Text/Story/Boxes.txt";
			break;
		case 13:
			mapname = "Maps_Text/Story/Teleporters.txt";
			break;
		case 14:
			mapname = "Maps_Text/Story/Succeded.txt";
			break;
		case 15:
			mapname = "Maps_Text/Story/Failed.txt";
			break;
		case 16:
			mapname = "Maps_Text/Best_Time.txt";
			break;
		case 17:
			mapname = "Maps_Text/Timings.csv";
			break;
		case 18:
			mapname = "Maps_Levels/Boss.txt";
			break;
		case 19: 
			mapname = "Maps_Text/Story/Boss.txt"; 
			break;
	}
	
	//Function use to store data from text file to 2d array
	string line = " ";
	//clear 2d array / portal locations
	memset(MapArray, '\0', sizeof(MapArray[0][0]) * 50 * 150);
	memset(FogArray, '\0', sizeof(FogArray[0][0]) * 50 * 150);

	//store to array
	if (level == 17)
	{
		ifstream file(mapname); //Opening the file
		int row = 0; //counting the number of rows
		string name;
		string time;
		string timings2[10][2];
		bool update = true;
		int point = 0;
		while (file >> name >> time) //Reading file by spaces
		{
			timing[row][0] = name;
			timing[row][1] = time;
			row++;
		}
		file.close(); //File closes
		if (boardUpdate == true)
		{
			for (int a = 0; a < row; a++)
			{
				if ((totalTime > 0.0) && (totalTime < stod(timing[a][1]))) //if total time is more than 0.0 and less than the times in the leaderboard. Prevent any unncessary storing od timings
				{
					stringstream time;
					time << totalTime; //Passing the time to stringstream
					time >> timings2[a][1]; //Passing time back to a new array
					timings2[a][0] = timing[a][0]; //New timing will take over the position of old timing
					a += 1;
					point = a; //Registering point as the exact point whereby the row was registerd till
					break;
				}
				else //If not, the new array will copy the same timings as the old array
				{
					timings2[a][0] = timing[a][0];
					timings2[a][1] = timing[a][1];
				}
			}
			if (point != 0) //Ensuring that the board must have had changes before
			{
				for (point; point < row; point++) //Continue where the copying left off
				{
					timings2[point][0] = timing[point][0];
					timings2[point][1] = timing[point - 1][1]; //Position will be pushed infront by 1
				}
			}

			ofstream file2("Maps_Text/Timings2.csv"); //Opening a new file
			for (int i = 0; i < row; i++)
			{
				file2 << timings2[i][0] << " " << timings2[i][1]; //Writing data into the new file
				file2 << endl;
			}
			remove("Maps_Text/Timings.csv"); //Removing old file
			file2.close(); 
			rename("Maps_Text/Timings2.csv", "Maps_Text/Timings.csv"); //Renaming new file's name as the old file's 
			totalTime = 0.0; //Resetting time 
			boardUpdate = false;
		}

	}
	else
	{
		ifstream myfile(mapname);
		int row = 0;
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				for (unsigned int i = 0; i <= line.length(); i++)
				{
					if (line[i] == '#')
						MapArray[row][i] = (char)219;
					else if (line[i] == 'D' && (level == 6 || level == 4 || level == 5 || level == 3 || level == 18)) //Level control printing if u want this on ur level change to (level == 5 || level == 6)
						MapArray[row][i] = (char)186;
					else if (line[i] == 'B' && (level == 6 || level == 3 || level == 18)) //Level control printing
						MapArray[row][i] = (char)254;
					else if (line[i] == '2' && (level == 2)) //Level control printing
						MapArray[row][i] = (char)234;
					else if (line[i] == '3' && (level == 2)) //Level control printing
						MapArray[row][i] = (char)3;
					else
						MapArray[row][i] = line[i]; //Print the rest as normal
					mapFog[row][i] = ' ';
				}
				row++;
			}
			myfile.close();
		}
		else
		{
			cout << "file cannot be opened" << endl;
		}
	}
	

	
	//Store to struct (Test)
	if (level == 7 || level == 3 || level == 18)
	{
		int portals = 0;
		memset(portalPos, 0, sizeof(portalPos));
		//Write code to start storing coordinates here
		//Store all teleport location here
		//Store location in array or struct
		//Run a double for loop if possible _Assignemt 2 common letter 
		for (int row = 0; row < 50; row++)//Finds the first row for first letter
		{
			if (MapArray[row] == '\0')
			{
				continue;
			}
			else
			{
				for (int col = 0; col < 150; col++) //Finds the colums for first letter
				{
					if (MapArray[row][col] == '\0')
					{
						continue; //Dont find any thing
					}
					else if ((MapArray[row][col] >= 65 && MapArray[row][col] <= 90) && (MapArray[row][col] != 'E') && (MapArray[row][col] != 'X')) //Check if its the letter i want
					{
						portalPos[portals].character = MapArray[row][col]; //Store the letter in the array / struct given in global variable
						for (int row2 = row+1; row2 < 50; row2++)
						{
							for (int col2 = 0; col2 < 150; col2++) //Runs another for loop to find the second letter
							{
								if (MapArray[row2][col2] == '\0')
								{
									continue;//Dont find any thing
								}
								else if ((portalPos[portals].character == MapArray[row2][col2]) && MapArray[row2][col2] != (char)64) //Found second letter
								{
									//Store both positions here (MAX. 26)
									MapArray[row2][col2] = (char)64;
									MapArray[row][col] = (char)64;
									portalPos[portals].Portal_1_X = row;
									portalPos[portals].Portal_1_Y = col;
									portalPos[portals].Portal_2_X = row2;
									portalPos[portals].Portal_2_Y = col2;
									portals+=1;
								}
							}
						}
					}
				}
			}
		}
	}

}
