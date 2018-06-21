#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;


class robot
{
public:
    //srand (time(NULL));
    char directions[4] = {'N','E','S','W'};
    int RandDir = rand() % 4; //generates a random number between 0 and 3
    char currentDirection = directions[RandDir];
    int currentLocation[2] = {0,0};
    string genes[24] = {"0222N", "1222N", "9222N", "2202S", "2212S", "2292S", "2022E", "2122E", "2922E", "2220W", "2220W", "2229W",
        				"0222N", "1222N", "9222N", "2202S", "2212S", "2292S", "2022E", "2122E", "2922E", "2220W", "2220W", "2229W"};

    // Specification 2a: Starting at power level 5
    int powerlvl = 5;
    char moves[4] = {'2','L','R','M'};
    void addmoves()
    {
        for(int i = 0; i <= 23; i++)
        {
            for(int x = 0; x < 4; x++)
            {
                int Randmove = rand() % 4; //generates a random number between 0 and 3
                char move = moves[Randmove];
                genes[i] += move;
            }
        }
    }

    // Specification 2b: Starting at a random location
    void setinitialLocation()
    {
        int row = rand() % 12;;
        int column = rand() % 12;;
        
        currentLocation[0] = row;
        currentLocation[1] = column;
    }

    void breed(robot father, robot mother)
    {
    	for(int b = 0; b < 12; b++)
    	{
    		genes[b] = father.genes[b];
    	}

    	for(int b = 12; b < 24; b++)
    	{
    		genes[b] = mother.genes[b];
    	}
    }
}r;


// Specification 3: Populate 40% of room with batteries 
void placebatteries(int room[12][12])
{
    int batteries = 57;
    for (int row = 0; row < 12; row++)
    {
        for (int column = 0; column < 12; column++)
        {
            if(batteries > 0)
            {
                int odds = rand()%100 ;
                
                if(odds > 60)
                {
                    room[row][column] = 1;
                    batteries--;
                }
                else
                {
                    room[row][column] = 0;
                }
            }
            else
            {
                room[row][column] = 0;
            }
            
        }
    }
}

int main()
{
	int generations = 0;
    string sensorReading;
    const int SIZE = 200;
    
    // Specification 6: Robot Population of 200
    robot r[200];

    for (int robots = 0; robots < SIZE; robots++)
    {
    	r[robots].addmoves();
   		r[robots].setinitialLocation();
    }

    newGen:
    	// Specification 1: 12x12 square room
    	int room[12][12];
   		placebatteries(room);
   		int totalFitness = 0;

   	// Display room of batteries 
   	for (int i = 0; i < 12; i++)
    {
      for(int j = 0; j < 12; j++)
      {
        cout << room[i][j] << "  ";
      }
      cout << endl;
    }

    for (int robots = 0; robots < SIZE; robots++)
    {
        
     	// robot r;
    	// r[robots].addmoves();
   		// r[robots].setinitialLocation();

    	// Specification 4: Each robot will move 25 times till it runs out of power
        for(int turns = 0; turns < 25; turns++)
        {
            int x = r[robots].currentLocation[0];
            int y = r[robots].currentLocation[1];

            if(room[x][y] == 1)
            {
                r[robots].powerlvl += 5;
                room[x][y] = 0;
            }
            
            if(r[robots].currentDirection == 'N')
            {
                if(r[robots].currentLocation[0] == 0)
                {
                    sensorReading = "9222";
                }
                else if(room[r[robots].currentLocation[0] - 1][r[robots].currentLocation[1]] == 1)
                {
                    sensorReading = "1222";
                }
                else
                {
                    sensorReading = "0222";
                }
            }
            else if(r[robots].currentDirection == 'S')
            {
                if(r[robots].currentLocation[0] == 11)
                {
                    sensorReading = "2292";
                }
                else if(room[r[robots].currentLocation[0] + 1][r[robots].currentLocation[1]] == 1)
                {
                    sensorReading = "2212";
                }
                else
                {
                    sensorReading = "2202";
                }
                
            }
            else if(r[robots].currentDirection == 'E')
            {
                if(r[robots].currentLocation[1] == 11)
                {
                    sensorReading = "2922";
                }
                else if(room[r[robots].currentLocation[0]][r[robots].currentLocation[1] + 1] == 1)
                {
                    sensorReading = "2122";
                }
                else
                {
                    sensorReading = "2022";
                }
                
            }
            else if(r[robots].currentDirection == 'W')
            {
                if(r[robots].currentLocation[1] == 0)
                {
                    sensorReading = "2229";
                }
                else if(room[r[robots].currentLocation[0]][r[robots].currentLocation[1] - 1] == 1)
                {
                    sensorReading = "2221";
                }
                else
                {
                    sensorReading = "2220";
                }
            }
            
            string currentMove;
            
            for(int i = 0; i < 24; i++)
            {
                if(r[robots].genes[i].substr(0,5) == (sensorReading + r[robots].currentDirection))
                {
                    currentMove = r[robots].genes[i].substr(5,4);
                    break;
                }
            }
            
            for(int i = 0; i < 4; i++)
            {
                if(currentMove[i] == 'M')
                {
                    if(r[robots].currentDirection == 'N')
                    {
                        if(sensorReading[0] == '9')
                        {
                            r[robots].powerlvl -= 1;
                        }
                        else
                        {
                            r[robots].currentLocation[0] -= 1;
                            r[robots].powerlvl -= 1;
                        }
                    }
                    else if(r[robots].currentDirection == 'E')
                    {
                        if(sensorReading[1] == '9')
                        {
                            r[robots].powerlvl -= 1;
                        }
                        else
                        {
                            r[robots].currentLocation[1] += 1;
                            r[robots].powerlvl -= 1;
                        }
                    }
                    else if(r[robots].currentDirection == 'S')
                    {
                        if(sensorReading[2] == '9')
                        {
                            r[robots].powerlvl -= 1;
                        }
                        else
                        {
                            r[robots].currentLocation[0] += 1;
                            r[robots].powerlvl -= 1;
                        }
                    }
                    else if(r[robots].currentDirection == 'W')
                    {
                        if(sensorReading[3] == '9')
                        {
                            r[robots].powerlvl -= 1;
                        }
                        else
                        {
                            r[robots].currentLocation[1] -= 1;
                            r[robots].powerlvl -= 1;
                        }
                    }
                }
                else if(currentMove[i] == '2')
                {
                    continue;
                }
                else if(currentMove[i] == 'R')
                {
                    if(r[robots].currentDirection == 'N')
                    {
                        r[robots].currentDirection = 'E';
                    }
                    else if(r[robots].currentDirection == 'E')
                    {
                        r[robots].currentDirection = 'S';
                    }
                    else if(r[robots].currentDirection == 'S')
                    {
                        r[robots].currentDirection = 'W';
                    }
                    else if(r[robots].currentDirection == 'W')
                    {
                        r[robots].currentDirection = 'N';
                    }
                }
                else if(currentMove[i] == 'L')
                {
                    
                    if(r[robots].currentDirection == 'N')
                    {
                        r[robots].currentDirection = 'W';
                    }
                    else if(r[robots].currentDirection == 'E')
                    {
                        r[robots].currentDirection = 'N';
                    }
                    else if(r[robots].currentDirection == 'S')
                    {
                        r[robots].currentDirection = 'E';
                    }
                    else if(r[robots].currentDirection == 'W')
                    {
                        r[robots].currentDirection = 'S';
                    }
                }
             	
             	// Specification 5: Robots will keep moving until they reach a power level of 0.
             	if(r[robots].powerlvl <= 0)
                {
                	break;
                }
            }

            if(r[robots].powerlvl <= 0)
                {
                	break;
                }
        }//turns bracket

        totalFitness += r[robots].powerlvl;
    }
    
    float averageFitness; 
    averageFitness = totalFitness / 200.0;
    
    // Average fitness level
    cout << "Average Fitness is " << averageFitness << endl;
    cout << endl;

    for (int i = 0; i < 200; ++i)
    {
    	for (int j = i + 1; j < 200; ++j)
    	{
    		if(r[i].powerlvl < r[j].powerlvl)
    		{
    			robot temp = r[i];
    			r[i] = r[j];
    			r[j] = temp;
    		}
    	}
    }

    // Breeding new generations of Robots.
    if(generations < 5)
    {
   		for(int i = 0; i < 100; i += 2)
    	{
    		r[i].powerlvl = 5;
   		 	r[i+1].powerlvl = 5;
   		 	robot r1;
   		 	robot r2;
   		 	r[i+100] = r1;
    		r[i+101] = r2;
   		 	r[i+100].breed(r[i],r[i+1]);
            r[i+101].breed(r[i+1],r[i]);

   		 	r[i+100].addmoves();
   			r[i+100].setinitialLocation();

   			r[i+101].addmoves();
   			r[i+101].setinitialLocation();
  	  	}

  	  	generations++;
  	  	goto newGen;
	}

    return 0;
}///main bracket






















