/* 
 * File:   main.c
 * Author: hicksj
 * Project #2
 *
 * Created on June 6, 2013, 7:34 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LIMIT 20
#define INPUT_FILE "C:/Users/hicksj/Documents/NetBeansProjects/Project2/pigwords.txt"
#define OUTPUT_FILE "C:/Users/hicksj/Documents/NetBeansProjects/Project2/output.txt"
#define READ_MODE       "r"
#define WRITE_MODE      "w"

/*
 * 
 */
int main(void) {
    
    /* declare and initialize variables */
    FILE *fileIn;       //File in pointer
    FILE *fileOut;      //File out pointer
    
    char eWord[STRING_LIMIT] = "";
    char splWord[STRING_LIMIT] = "";
    char aplWord[STRING_LIMIT] = "";
    char startWord[STRING_LIMIT] = "";
    char endWord1[STRING_LIMIT] = "";
    char endWord2[STRING_LIMIT] = "";
    
    /* function prototypes */
    void simplePigLatin(char eWord1[], char splWord[]);
    void advancedPigLatin(char eWord[], char aplWord[]);
    
    /* open read-in file */
    fileIn = fopen(INPUT_FILE, READ_MODE);
    
    /* open output file */
    fileOut = fopen(OUTPUT_FILE, WRITE_MODE);
    
    /* setup header for output file */
    fprintf(fileOut, "English Word\t\tSimple Pig Latin\t\tAdvanced Pig Latin\n");
    
    /* if input file is empty, print error to screen */
    if(fileIn == NULL){
        printf("Error opening input file \n");
    }
    else{
        
        /* continue to read from the file until EOF is reached */
        while((fscanf(fileIn, "%s", startWord)) == 1){
            
            /* print input to file */
            fprintf(fileOut, "%s", startWord);
            
            /* invoke simplePigLatin function */
            simplePigLatin(startWord, endWord1);
            
            /* print output to file */
            fprintf(fileOut, "\t\t\t%s", endWord1);
            
            /* invoke simplePigLatin function */
            advancedPigLatin(startWord, endWord2);
            
            /* print output to file */
            fprintf(fileOut, "\t\t\t\t\t%s\n", endWord2);
            
        }//while
        
    }//else
    
    /* close input file */
    fclose(fileIn);
    
    /* end of program */
    fprintf(fileOut, "\nEnd of program.\n");
    printf("\nProgram Execution Finished... \n");
    
    /* close output file */
    fclose(fileOut);
    
    return(0);
    
}//main

int isAVowel(char c){
    switch(c){
        
        /* test to see if character is a vowel */
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'i':
        case 'I':
        case 'o':
        case 'O':
        case 'u':
        case 'U':
            return 0; //return 0 if character c is a vowel
            break;
        default:
            return 1; //return 1 if character is not a vowel
            break;
            
    }//switch
    
}//isAVowel

void simplePigLatin(char eWord[], char splWord[]){
    
    /* function prototype */
    int isAVowel(char c);
    
    char *str1 = eWord;
    int strLength;
    
    /* Simple Pig Latin: if the first character is a vowel, do nothing */
    if(isAVowel(eWord[0]) == 0){
        
        /* copy eWord contents to aplWord */
        strcpy(splWord,eWord);
    }
    else{
        
        /* copy NULL contents to splWord */
        strcpy(splWord,"");
        
        /* keep track of string length */
        strLength = strlen(eWord);
        
        strncat(splWord,str1+1,strLength-1); //place everything after first letter in storage
        strncat(splWord,str1,1); //add first letter to end
        strcat(splWord,"ay"); //add "ay" to the end
        
    }//else
    
    return;
    
}//simplePigLatin
    
void advancedPigLatin(char eWord[], char aplWord[]){
    
    /* declare variables */
    char *str1 = eWord;
    char t[] = "aeiouAEIOU"; //string of all vowels
    char *position; //position pointer
    int index; 
    int strLength;
    
    /* function prototype */
    int isAVowel(char c);
    
    /* Advanced Pig Latin: if first letter is a vowel, 
       or if the word has no vowels, add "way" to the end 
       else
       if neither is true, move all characters before first 
       vowel to end of the word and add "ay"                */
    
    if((isAVowel(eWord[0]) == 0) || strpbrk(eWord,t) == NULL){
        
        /* copy eWord contents to aplWord */
        strcpy(aplWord,eWord);
        
        /* add "way" */
        aplWord = strcat(aplWord,"way");        
    }
    else{
        /* copy eWord to aplWord */
        strcpy(aplWord,"");
        
        /* Length of string */
        strLength = strlen(eWord);
        
        /* search for first occurrence of a vowel */
        position = strpbrk(eWord, t);
        
        /* pointer arithmetic to work out index */
        index = eWord - position;
        
        /* in case index is negative */
        if(index<0){           
            index *= -1; //take absolute value
        }//if
        
        /* add everything after first vowel to storage string */
        aplWord = strncat(aplWord,str1+index,(strLength-index));
        
        /* add everything until first vowel to end of string */
        aplWord = strncat(aplWord,str1,index);
        
        /* add "ay" to end of string */
        aplWord = strcat(aplWord,"ay");
        
    }//else
    
    return;
}
      
    

