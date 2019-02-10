

#include "Doodlebug.hpp"
#include "Group4Utils.hpp"
#include <iostream>

using std::cout;
using std::endl;

Doodlebug::Doodlebug(int x_pos, int y_pos):Critter()
{
   this->x_pos = x_pos;
   this->y_pos = y_pos;
   this->age = 0;
   this->hunger = 0;
   this->symbol = 'X';
   this->moveSuccess = 0;
}

void Doodlebug::move(Critter*** &boardIn)
{
   int random = randIntRange(0,3);
   bool antNear = false;
   bool inBounds = false;
   bool cellFree = false;

   int new_x, new_y;
   int attempts = 0;

   //check if ant is in an adjacent cell
   switch (random) 
   {
      case 0: new_x = this->x_pos - 1;
              new_y = this->y_pos;
              inBounds = checkBounds(new_x, new_y);
              if(inBounds && boardIn[new_x][new_y] != NULL && boardIn[new_x][new_y]->getSymbol() == 'O')
              {
                 antNear = true;   
	         break;
              }
              else if(attempts >= 4)
                 break;
              else
              {
                 attempts++; 
                 random = 1;
              }
      case 1: new_x = this->x_pos;
              new_y = this->y_pos + 1;
              inBounds = checkBounds(new_x, new_y);
              if(inBounds && boardIn[new_x][new_y] != NULL && boardIn[new_x][new_y]->getSymbol() == 'O')
              {
                 antNear = true;
	         break;
              }
              else if(attempts >= 4)
                 break;
              else 
              {
                 attempts++; 
                 random = 2;
              }
      case 2: new_x = this->x_pos + 1;
              new_y = this->y_pos;
              inBounds = checkBounds(new_x, new_y);
              if(inBounds && boardIn[new_x][new_y] != NULL && boardIn[new_x][new_y]->getSymbol() == 'O')
              {
                 antNear = true;
	         break;
              }
              else if(attempts >= 4)
                 break;
              else
              {
                 attempts++; 
                 random = 3;
              }
      case 3: new_x = this->x_pos;
              new_y = this->y_pos - 1;
              inBounds = checkBounds(new_x, new_y);
              if(inBounds && boardIn[new_x][new_y] != NULL && boardIn[new_x][new_y]->getSymbol() == 'O')
              {
                 antNear = true;
	         break;
              }
              else if(attempts >= 4)
                 break;
              else
              {
                 attempts++;
                 random = 0;
              }
   }

   if(antNear == true)
   {
      delete boardIn[new_x][new_y]; //delete Ant at the new x,y position
      //set pointer at new x,y position equal to the Doodlebug point that is moving
      boardIn[new_x][new_y] = boardIn[this->x_pos][this->y_pos];      
      //reset the pointer at the old position to NULL to signify that the space is empty
      boardIn[this->x_pos][this->y_pos] = NULL;
      //update x and y position for the Doodlebug
      this->x_pos = new_x;
      this->y_pos = new_y;
      this->hunger = 0;
      this->moveSuccess = 1;
   }
 
   else //if antNear == false
   {
      attempts = 0;
      this->hunger += 1;
      random = randIntRange(0,3);
      switch (random) 
      {
         case 0: new_x = this->x_pos - 1;
                 new_y = this->y_pos;
                 inBounds = checkBounds(new_x, new_y);
                 if(inBounds && boardIn[new_x][new_y] == NULL)
                 {
                    cellFree = true;   
	            break;
                 }
                 else if(attempts >= 4)
                    break;
                 else
                 {  
                    attempts++;
                    random = 1;
                 }
         case 1: new_x = this->x_pos;
                 new_y = this->y_pos + 1;
                 inBounds = checkBounds(new_x, new_y);
                 if(inBounds && boardIn[new_x][new_y] == NULL)
                 {
                    cellFree = true;
      	            break;
                 }
                 else if(attempts >= 4)
                    break;
                 else
                 {
                    attempts++;
                    random = 2;
                 }  
         case 2: new_x = this->x_pos + 1;
                 new_y = this->y_pos;
                 inBounds = checkBounds(new_x, new_y);
                 if(inBounds && boardIn[new_x][new_y] == NULL)
                 {
                    cellFree = true;
	            break;
                 }
                 else if(attempts >= 4)
                    break;
                 else
                 {
                    attempts++;
                    random = 3;
                 }
         case 3: new_x = this->x_pos;
                 new_y = this->y_pos - 1;
                 inBounds = checkBounds(new_x, new_y);
                 if(inBounds && boardIn[new_x][new_y] == NULL)
                 {
                    cellFree = true;
	            break;
                 }
                 else if(attempts >= 4)
                    break;
                 else
                 {
                    attempts++;
                    random = 0;
                 }
      }

      if(cellFree == true)
      {
         delete  boardIn[new_x][new_y];
         boardIn[new_x][new_y] = boardIn[this->x_pos][this->y_pos];
         boardIn[this->x_pos][this->y_pos] = NULL;
         this->x_pos = new_x;
         this->y_pos = new_y;
	 this->moveSuccess = 1;
      }

      else
      {
         this->moveSuccess = 1;
         return;
      }
   }
}


void Doodlebug::breed(const Critter *** &boardIn)
{
   bool cellFree = false;
   int new_x, new_y;
   int direction = randIntRange(0,3);
   int randIterator = 0;
   //check that adjacent cell is free, i.e. printSymbol() of the object of that cell returns ' '
   if(this->age == 8)
   {
     while(cellFree == false && randIterator != 3)
     {
  	   if(direction == 1 && boardIn[this->x_pos + 1][this->y_pos]==NULL)
  	   {
  	      new_x = x_pos + 1;
  	      new_y = y_pos;
  	      cellFree = true;
          cout << "New doodlebug born at row " << new_x << "and col " << new_y;
                break;
  	   }
  	   if(direction == 0 && boardIn[this->x_pos - 1][this->y_pos]==NULL)
  	   {
  	      new_x = x_pos - 1;
  	      new_y = y_pos;
  	      cellFree = true;
          cout << "New doodlebug born at row " << new_x << "and col " << new_y;
                break;
  	   }
  	   if(direction == 2 && boardIn[this->x_pos][this->y_pos + 1]==NULL)
  	   {
  	      new_x = x_pos;
  	      new_y = y_pos + 1;
  	      cellFree = true;
          cout << "New doodlebug born at row " << new_x << "and col " << new_y;
                break;
  	   }
  	   if(direction == 3 && boardIn[this->x_pos][this->y_pos - 1]==NULL)
  	   {
  	      new_x = x_pos;
  	      new_y = y_pos - 1;
  	      cellFree = true;
          cout << "New doodlebug born at row " << new_x << "and col " << new_y;
                break;
  	   }
       if(direction != 3 && randIterator <3)
       {
         direction = direction + 1;
         randIterator ++;
       }
       else if (direction==3 && randIterator <3)
       {
         direction = 0;
         randIterator++;
       }
       else
       {
         return;
       }
     }
     if(cellFree == true)
     {
       cout << new_x << " " << new_y <<endl;
       delete boardIn[new_x][new_y];
       Doodlebug *doodle = new Doodlebug(new_x, new_y);
       boardIn[new_x][new_y] = doodle;
     }
     else
     {
       return;
     }


  }
}

//helper function for breed test
void Doodlebug::setAge(int ageIn)
{
  this->age = ageIn;
}
