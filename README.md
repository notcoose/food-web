# Food Web

In this project, a dynamically allocated food web struct array is built using user input predator-prey relationships. An analysis is done of the food web and done again after a species goes extinct. Whenever a species goes extinct, all relationships and structs are reallocated and modified to erase all signs of the extinct species

**NOTE:** Extinction functionality is not fully working at the moment but the issue is known and will the fix will be implemented when I find free time

## Installation

To use this project, the only required file is main.c. 

It is recommended that you also download any of the formatted text files to test this project using file redirection

## Usage

To use the file, you can compile an output file like this: "g++/gcc main.c -o ./a.out"

This file takes two **optional** command-line arguments: "-q" and "-x"

**-q**: Will turn on quietMode, skippping user input prompts and ideal for file input redirection

**-x**: Will turn off extinctMode, skipping over the extinction process

Then run the output like this: "./a.out"

Or like this using file input redirection for the prompts: "./a.out < anyOfTheTxtFiles.txt"

## Sample Output

**From using file redirection on AquaticFoodWeb.txt**

Program Settings:

  quiet mode = OFF
  
  extinction mode = ON

Welcome to the Food Web Application

**--------------------------------**

Enter number of organisms:

Enter names for 11 organisms:

Enter number of predator/prey relations:

Enter the pair of indices for the 19 predator/prey relations

the format is [predator index] [prey index]:

**--------------------------------**

**Food Web Predators & Prey:**

  Bird eats Prawn, Whelk, Crab, Mussels, Limpets
  
  Crab eats Mussels, Limpets
  
  Fish eats Prawn
  
  Limpets eats Seaweed
  
  Lobster eats Crab, Limpets, Whelk, Mussels
  
  Mussels eats Phytoplankton, Zooplankton
  
  Phytoplankton
  
  Prawn eats Zooplankton
  
  Seaweed
  
  Whelk eats Mussels, Limpets
  
  Zooplankton eats Phytoplankton
  

**Apex Predators:**

  Bird
  
  Fish
  
  Lobster

**Producers:**

  Phytoplankton
  
  Seaweed

**Most Flexible Eaters:**

  Bird

**Tastiest Food:**

  Limpets
  
  Mussels

**Food Web Heights:**

  Bird: 4
  
  Crab: 3
  
  Fish: 3
  
  Limpets: 1
  
  Lobster: 4
  
  Mussels: 2
  
  Phytoplankton: 0
  
  Prawn: 2
  
  Seaweed: 0
  
  Whelk: 3
  
  Zooplankton: 1


**Vore Types:**

  **Producers:**
  
  Phytoplankton
    
  Seaweed
    
  **Herbivores:**
  
  Limpets
    
  Zooplankton
    
  Omnivores:
  
  Mussels
   
  **Carnivores:**
  
  Bird
    
  Crab
    
  Fish
    
  Lobster
    
  Prawn
    
  Whelk
    
**--------------------------------**

Enter extinct species index:

Species Extinction: Limpets

**--------------------------------**

**UPDATED Food Web Predators & Prey:**

  Bird eats Prawn, Whelk, Crab, Mussels, Limpets
  
  Crab eats Mussels, Limpets
  
  Fish eats Prawn
  
  Limpets eats Seaweed
  
  Lobster eats Crab, Limpets, Whelk, Mussels
  
  Mussels eats Phytoplankton, Zooplankton
  
  Phytoplankton
  
  Prawn eats Zooplankton
  
  Seaweed
  
  Whelk eats Mussels, Limpets
  
  Zooplankton eats Phytoplankton
  

**UPDATED Apex Predators:**

  Bird
  
  Fish
  
  Lobster
  

**UPDATED Producers:**

  Phytoplankton
  
  Seaweed

  
**UPDATED Most Flexible Eaters:**

  Bird
  

**UPDATED Tastiest Food:**

  Limpets
  
  Mussels
  

**UPDATED Food Web Heights:**

  Bird: 4
  
  Crab: 3
  
  Fish: 3
  
  Limpets: 1
  
  Lobster: 4
  
  Mussels: 2
  
  Phytoplankton: 0
  
  Prawn: 2
  
  Seaweed: 0
  
  Whelk: 3
  
  Zooplankton: 1
  

**UPDATED Vore Types:**

  **Producers:**
  
  Phytoplankton
    
  Seaweed
    
  **Herbivores:**
  
  Limpets
    
  Zooplankton
    
  **Omnivores:**
  
  Mussels
   
  **Carnivores:**
  
  Bird
    
  Crab
    
  Fish
    
  Lobster
    
  Prawn
    
  Whelk
    

**--------------------------------**
