/*
Word Count reads a file and then returns its word frequencies.

Kevin Zhang
SoftSys Spring 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


/*
simple function used for printing a key/value pair

word: the key
dict: the dictionary we have populated and will search in using the key
*/
void print_item(gchar* word, GHashTable* dict){
    printf("%s: %ld\n", word, (gint64)g_hash_table_lookup(dict, word));
}

/*
compare function for custom sorting the dictionary's keys so we can print it in order

word1: the first key
word2: the second key
dictionary: the dictionary in which we search for the values for comparision
*/
gint compare_keys(gchar* word1, gchar* word2, GHashTable* dictionary){
    return ((gint64)g_hash_table_lookup(dictionary, word1)) - ((gint64)g_hash_table_lookup(dictionary, word2));
}

/*
finds the freuencies
goes over the entire file, and for each word in the file, strip it, check if it's in
the dictionary already, and if not then make a new entry and if so then update the value

text: the file reader
word: the variable that holds the incoming read word
sub: the substitution for stripping words
valid: the list of valid letters used in stripping
dictionary: the dictionary we're trying to populate
*/
void find_frequencies(FILE * text, gchar word[], gchar *sub, const gchar* valid, GHashTable *dictionary){
    while(fscanf(text, "%1023s", word) == 1){
        g_strcanon(word, valid, *sub);
        if (g_strcmp0(word, " ") != 0 && g_strcmp0(word, "") != 0){
            if (g_hash_table_contains(dictionary, word)){
                g_hash_table_replace(dictionary, g_strdup(word), (gpointer)(((gint64)g_hash_table_lookup(dictionary, word))+1));
            }
            else{
                g_hash_table_insert(dictionary, g_strdup(word), (gpointer)1);
            }
        }
    }
}

/*
The main function, which holds all variables and executes the population of the dictionary
*/
int main(int argc, char** argv){
    if (argc < 2){
        puts("Not enough arguments, please supply a file.");
        exit(2);
    }
    // the file reader
    FILE *text = fopen(argv[1], "r");
    if (!text){
        printf("No file found.");
        exit(1);
    }

    // making variables
    gchar word[1024];
    const gchar* valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    gchar *sub = "";
    GHashTable * dictionary = g_hash_table_new(g_str_hash, g_str_equal);

    // populates dictionary and then prints it out sorted
    find_frequencies(text, word, sub, valid, dictionary);
    g_list_foreach(g_list_sort_with_data(g_hash_table_get_keys(dictionary), (GCompareFunc)compare_keys, dictionary), (GFunc)print_item, dictionary);

    fclose(text);

    return 0;
}
