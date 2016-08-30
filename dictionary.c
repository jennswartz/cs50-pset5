/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "dictionary.h"

// Converts key current character into index using only 'a' through 'z' and lower case
#define CHAR_TO_INDEX (c - 'a')

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int length = strlen(word);
    
    // set traversial pointer check equal to root
    node* check = root;
    
    for (int i = 0; i < length; i++)
    {
        
        // change to lower case
        char c = tolower(word[i]);
        
        // check for apostrophe, which is assigned to location 127 in load()
        if (c == '\'')
            c = 127;
        
        // assign next free node
        next_free_node = check->children[CHAR_TO_INDEX];
        
        // if next free node is null, return false; else, assign traversal variable to next free node
        if (next_free_node == NULL)
            return false;
        else
            check = next_free_node;
    }
    
    // if it is a word in the dictionary, return true
    if (check->is_word == true)
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = calloc(1, sizeof(node));
    traverse = root;

    // load dictionary file
    FILE* dict = fopen(dictionary, "rb");
    
    // check to make sure file loaded
    if(dict == false) 
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    for (char c = tolower(fgetc(dict)); c != EOF; c = fgetc(dict))
    {
        if (c == '\n')
        {
            if (traverse != root)
            {
                words++;
                traverse->is_word = true;
                traverse = root;
            }
        }
        else
        {
            // assign apostrophe to ascii value 127 for ease of checking 
            if (c == '\'')
                c = 127;
        
            next_free_node = traverse->children[CHAR_TO_INDEX];
            if (next_free_node == NULL)
            {
                traverse->children[CHAR_TO_INDEX] = calloc(1, sizeof(node));
                traverse = traverse->children[CHAR_TO_INDEX];
            }
            else
                traverse = next_free_node;
        }
    } 
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    free(next_free_node);
    free(traverse);
    return true;
}
