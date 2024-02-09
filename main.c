#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Org_struct {
    char name[20];
    int* prey; //dynamic array of indices  
    int numPrey;
} Org;

/*manually malloc space for a new array with modified size, copy over necessary data, 
free the old array, update the array pointer, and update the size variable*/

/*Returns the max height of any prey in a given prey array*/
int maxPreyHeight(int heights[], int prey[], int size){
    int max = 0;

    for(int i = 0; i < size; i++){
        if(heights[prey[i]] > max)
            max = heights[prey[i]];
    }

    return max;
}

/*Returns a new array with more size and all original elements copied over*/
int* fakeRealloc(int* ptr, int* size, int newSize){ 
    int* newPtr = (int*)malloc(newSize*sizeof(int)); //Mallocs space for new array

    for(int i = 0; i < *size; i++){ //Copies over data
        newPtr[i] = ptr[i];
    }

    *size = newSize; //Updates size

    free(ptr); //Frees old array
    return newPtr; 
}

/*Adds prey to a predator's prey array*/
void buildWeb(Org* web, int numOrg, int predInd, int preyInd) { //DONE
    if(web[predInd].numPrey == 0){ //If predator had no prey, mallocs for a one size array
        web[predInd].prey = (int*)malloc(sizeof(int));
        web[predInd].prey[0] = preyInd;
        web[predInd].numPrey = 1;
    }
    else{
        int lastIndex = web[predInd].numPrey;
        web[predInd].prey = fakeRealloc(web[predInd].prey, &web[predInd].numPrey, (web[predInd].numPrey + 1)); //Calls my realloc function to make room and copy elements
        web[predInd].prey[lastIndex] = preyInd;
    }
}

/*Doesnt work :(*/
void extinction(Org** web, int* numOrgs, int index){ 
    /*if((*numOrgs) == 1 && index == 0){
        free((*web)[0].prey);
        (*web)[0].prey = NULL;

        free(*web);
        *web = NULL;
        return;
    }

    Org* newWeb = (Org*)malloc((*numOrgs - 1)*sizeof(Org));

    for(int i = 0; i < *numOrgs; i++){
        if(i < index)
            newWeb[i] = (*web)[i];
        else if(i > index)
            newWeb[i - 1] = (*web)[i];  
    }

    for(int i = 0; i < (*numOrgs); i++){
        free((*web)[i].prey);
    }
    free(*web);

    *web = newWeb;
    *numOrgs--;

    for(int i = 0; i < (*numOrgs); i++){
        bool found = false;
        
        for(int j = 0; j < newWeb[i].numPrey; j++){
            if(newWeb[i].prey[j] == index)
                found = true;
        }

        if(found){
            int* newPrey = (int*)malloc((newWeb[i].numPrey - 1)*sizeof(int));
            
            for(int k = 0; k < newWeb[i].numPrey; k++){
                if(k < index)
                    newPrey[k] = newWeb[i].prey[k];
                else if(k > index)
                    newPrey[k - 1] = newWeb[i].prey[k];  
            }

            free(newWeb[i].prey);
            newWeb[i].prey = newPrey;
            newWeb[i].numPrey--;
        }

        for(int i = 0; i < (*numOrgs); i++){
            for(int j = 0; j < newWeb[i].numPrey; j++){
                if(newWeb[i].prey[j] > index)
                    newWeb[i].prey[j]--;
            }
        }
    }*/

    //      Outputs:
    //          web - pointer passed-by-pointer; memory address of web array changes due to reallocation
    //          numOrgs - passed-by-pointer; must be decremented since web[] loses an organism
    //      1. remove organism at index from web[] - DO NOT use realloc(), instead...
    //          (a) free any malloc'd memory associated with organism at index; i.e. its prey[] subitem
    //          (b) malloc new space for the array with the new number of Orgs
    //          (c) copy all but one of the old array elements to the new array, 
    //              some require shifting forward to overwrite the organism at index
    //          (d) free the old array
    //          (e) update the array pointer to the new array
    //          (f) update numOrgs
    //      2. remove index from all organisms' prey[] array subitems - DO NOT use realloc(), instead...
    //          (a) search for index in all organisms' prey[] arrays; when index is found:
    //                [i] malloc new space for the array with the new number of ints
    //               [ii] copy all but one of the old array elements to the new array, 
    //                    keeping the same order some require shifting forward
    //              [iii] free the old array
    //               [iv] update the array pointer to the new array
    //                [v] update the numPrey subitem accordingly
    //          (b) update all organisms' prey[] elements that are greater than index, 
    //              which have been shifted forward in the web array
    //          Edge case: check the size array being malloc'ed; 
    //                     for a web with only one organism and 
    //                     that orgranism goes extinct, 
    //                     instead of malloc'ing an empty array, 
    //                     explicitly set the pointer to NULL;
    //                     see the web[] allocation in main() as an example

}

/*Prints every predator ptrey relationship*/
void printPredPrey(Org* web, int numOrgs){
    int preyArray[20];

    for(int i = 0; i < numOrgs; i++){
        if(web[i].numPrey == 0)
            printf("  %s\n", web[i].name);
        else{
            printf("  %s eats ", web[i].name);
            for(int k = 0; k < (web[i].numPrey - 1); k++){
                printf("%s, ", web[web[i].prey[k]].name);
            }
            printf("%s\n", web[web[i].prey[web[i].numPrey - 1]].name);
        }
    }
}

/*Prints every predator which is not anyone's prey*/
void printApex(Org* web, int numOrgs){ 
    int apexOrgs[numOrgs];

    for(int i = 0; i < numOrgs; i++){ //Creates array of apex predators with assumption every index is apex predator
        apexOrgs[i] = i; 
    }

    for(int j = 0; j < numOrgs; j++){ //If any animal is someone's prey, marks that index in array with -1
        for(int k = 0; k < web[j].numPrey; k++){
            for(int i = 0; i < numOrgs; i++){
                if(web[j].prey[k] == apexOrgs[i])
                    apexOrgs[i] = -1;
            }
        }
    }

    for(int i = 0; i < numOrgs; i++){
        if(apexOrgs[i] != -1)
            printf("  %s\n", web[i].name);
    }
}

/*Prints every producer, or web member with no prey*/
void printProducers(Org* web, int numOrgs){ 
    for(int i = 0; i < numOrgs; i++){
        if(web[i].numPrey == 0)
            printf("  %s\n", web[i].name);
    }
}

/*Prints the organism(s) which eat the most different organisms*/
void printEaters(Org* web, int numOrgs){ 
    int eaters[2] = {-1, -1}, max = 0;

    for(int i = 0; i < numOrgs; i++){ //find(s) the organisms with the most prey
        if(web[i].numPrey > max){
            max = web[i].numPrey;
            eaters[0] = i;
        }
        else if(web[i].numPrey == max)
            eaters[1] = i;
    }

    printf("  %s\n", web[eaters[0]].name);

    if(eaters[1] != -1)
        printf("  %s\n", web[eaters[1]].name);
}

/*Prints organism(s) which get eatten by the most different organisms*/
void printTastiest(Org* web, int numOrgs){ 
    int predatorAmt[numOrgs], max = 0, tastiest[2] = {-1, -1};

    for(int i = 0; i < numOrgs; i++){
        predatorAmt[i] = 0;
    }

    for(int i = 0; i < numOrgs; i++){ //Counts the amount of predators for each organism
        for(int j = 0; j < web[i].numPrey; j++){
            predatorAmt[web[i].prey[j]]++;
        }
    }

    for(int i = 0; i < numOrgs; i++){ //Finds the organism(s) with the most predators
        if(predatorAmt[i] > max){
            tastiest[0] = i;
            max = predatorAmt[i];
        }
        else if(predatorAmt[i] == max)
            tastiest[1] = i;
    }

    printf("  %s\n", web[tastiest[0]].name);
    if(predatorAmt[1] != -1)
        printf("  %s\n", web[tastiest[1]].name);
}

/*Prints the height of each organism's food web*/
void printHeight(Org* web, int numOrgs){ 
    int heights[numOrgs];
    bool changed = true;

    for(int i = 0; i < numOrgs; i++){
        heights[i] = 0;
    }

    do{ //While the web is changed at least once, makes the height of each organism 1 higher than the greatest height of it's prey
        changed = false;
        for(int i = 0; i < numOrgs; i++){
            if(web[i].numPrey == 0)
                continue;

            int temp = heights[i];
            heights[i] = maxPreyHeight(heights, web[i].prey, web[i].numPrey) + 1;

            if(heights[i] != temp){
                changed = true;
            }
        }
    }while(changed == true);

    for(int i = 0; i < numOrgs; i++){
        printf("  %s: %d\n", web[i].name, heights[i]);
    }
}

/*Prints which organisms belong to each dietary group*/
void printVoreTypes(Org* web, int numOrgs){ //DONE
    printf("  Producers:\n"); //Prints every producer, which eats no organism
    for(int i = 0; i < numOrgs; i++){
        if(web[i].numPrey == 0)
            printf("    %s\n", web[i].name);
    }

    printf("  Herbivores:\n"); //Prints every herbivore, which eats only producers
    for(int i = 0; i < numOrgs; i++){
        bool onlyProducers = true;
        for(int j = 0; j < web[i].numPrey; j++){
            if(web[web[i].prey[j]].numPrey != 0)
                onlyProducers = false;
        }

        if(onlyProducers && web[i].numPrey != 0)
            printf("    %s\n", web[i].name);
    }

    printf("  Omnivores:\n"); //Prints every omnivore, which eats producers and non-producers
    for(int i = 0; i < numOrgs; i++){
        bool producers = false;
        bool nonproducers = false;

        for(int j = 0; j < web[i].numPrey; j++){
            if(web[web[i].prey[j]].numPrey == 0)
                producers = true;
            else
                nonproducers = true;
        }

        if(producers && nonproducers)
            printf("   %s\n", web[i].name);
    }

    printf("  Carnivores:\n"); //Prints every carnivore, which only eats non-producers
    for(int i = 0; i < numOrgs; i++){
        bool anyProducers = false;

        for(int j = 0; j < web[i].numPrey; j++){
            if(web[web[i].prey[j]].numPrey == 0)
                anyProducers = true;
        }

        if(!anyProducers && web[i].numPrey != 0)
            printf("    %s\n", web[i].name);
    }
}

int main(int argc, char* argv[]) {

    bool quietMode = false;
    bool extinctMode = true;

    char *onOrOff[] = {"OFF", "ON"}; 

    if(argc > 3){
        printf("Invalid command-line argument. Terminating program...");
        return 0;
    }

    for(int i = 0; i < argc; i++){ //Checks for valid command line arguments and updates modes accordingly
        if(i != 0){
            if(argv[i][0] == '-' && argv[i][1] == 'q' && quietMode == false){
                quietMode = true;
            }
            else if(argv[i][0] == '-' && argv[i][1] == 'x' && extinctMode == true){
                extinctMode = false;
            }
            else{
                printf("Invalid command-line argument. Terminating program...");
                return 0;
            }
        }
    }

    printf("Program Settings:\n  quiet mode = %s\n  extinction mode = %s\n", onOrOff[quietMode], onOrOff[extinctMode]);

    int numOrgs;
    printf("\nWelcome to the Food Web Application\n");
    printf("--------------------------------\n");
    /*Gets number of organisms from user*/
    if (!quietMode) printf("Enter number of organisms:\n");
    scanf("%d",&numOrgs);

    Org* web = NULL;
    if(numOrgs > 0) { //Do not malloc an empty array, leave it pointing to NULL
        web = (Org*)malloc(numOrgs*sizeof(Org));
    }
    
    /*Allows user to input organism names*/
    if (!quietMode) printf("Enter names for %d organisms:\n", numOrgs);
    for (int i = 0; i < numOrgs; ++i) {
        scanf("%s",web[i].name);
        web[i].prey = NULL;
        web[i].numPrey = 0;
    }

    /*If not in quiet mode, gets predator prey relationships and builds webs for those*/
    if (!quietMode) printf("Enter number of predator/prey relations:\n");
    int numRels;
    scanf("%d",&numRels);

    if (!quietMode) printf("Enter the pair of indices for the %d predator/prey relations\n",numRels);
    if (!quietMode) printf("the format is [predator index] [prey index]:\n");
    
    int predInd, preyInd;
    for (int i = 0; i < numRels; ++i) {
        scanf("%d %d",&predInd, &preyInd);
        buildWeb(web,numOrgs,predInd,preyInd);
    }
    if (!quietMode) printf("--------------------------------\n\n");

    printf("Food Web Predators & Prey:\n"); 
    printPredPrey(web, numOrgs);
    printf("\n");

    printf("Apex Predators:\n");
    printApex(web, numOrgs);
    printf("\n");

    printf("Producers:\n");
    printProducers(web, numOrgs);
    printf("\n");

    printf("Most Flexible Eaters:\n");
    printEaters(web, numOrgs);
    printf("\n");

    printf("Tastiest Food:\n");
    printTastiest(web, numOrgs);
    printf("\n");

    printf("Food Web Heights:\n");
    printHeight(web, numOrgs);
    printf("\n");

    printf("Vore Types:\n");
    printVoreTypes(web, numOrgs);
    printf("\n");

    if (extinctMode) {
        printf("--------------------------------\n");
        int extInd;
        printf("Enter extinct species index:\n");
        scanf("%d",&extInd);
        printf("Species Extinction: %s\n", web[extInd].name);
        extinction(&web,&numOrgs,extInd);
        printf("--------------------------------\n\n");

        printf("UPDATED Food Web Predators & Prey:\n");
        printPredPrey(web, numOrgs);
        printf("\n");

        printf("UPDATED Apex Predators:\n");
        printApex(web, numOrgs);
        printf("\n");

        printf("UPDATED Producers:\n");
        printProducers(web, numOrgs);
        printf("\n");

        printf("UPDATED Most Flexible Eaters:\n");
        printEaters(web, numOrgs);
        printf("\n");

        printf("UPDATED Tastiest Food:\n");
        printTastiest(web, numOrgs);
        printf("\n");

        printf("UPDATED Food Web Heights:\n");
        printHeight(web, numOrgs);
        printf("\n");

        printf("UPDATED Vore Types:\n");
        printVoreTypes(web, numOrgs);
        printf("\n");
        printf("--------------------------------\n");
    }

    
    //Frees malloced prey arrays and web
    for(int i = 0; i < numOrgs; i++){
        free(web[i].prey);
    }
    free(web);
    return 0;
}
