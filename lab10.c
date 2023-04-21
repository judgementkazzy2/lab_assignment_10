#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie
{
    int count;
    struct Trie *children[26];
};

void insert(struct Trie **ppTrie, char *word)
{
    struct Trie *trie = *ppTrie;
    
    if(trie == NULL)
    {
        trie = calloc(1, sizeof(struct Trie));
        *ppTrie = trie;
    }

    for (int i = 0; word[i] != '\0'; i++)
    {
        int n = word[i] - 'a';
        if(trie->children[n] == NULL)
        {
            trie->children[n] = calloc(1, sizeof(struct Trie));
        }
        
        trie = trie->children[n];
    }

    trie->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *trie = pTrie;
    int n;

    for(int i = 0; word[i] != '\0'; i++)
    {
        n = word[i] - 'a';
        if(trie->children[n] == NULL)
        {
            return 0;
        }

        trie = trie->children[n];
    }

    return trie->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL)
    {
        return NULL;
    }

    for(int i = 0; i < 26; i++)
    {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
    return NULL;
}

int main(void)
{
    // read the number of the words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    struct Trie *trie = NULL;
    
    for (int i = 0; i < 5; i++)
    {
        insert(&trie, pWords[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        int num = numberOfOccurances(trie, pWords[i]);
        if (num > 0)
        {
            printf("\t%s : %d\n", pWords[i], num);
            struct Trie *pTrie = trie;
            for(int j = 0; pWords[i][j] != '\0'; j++)
            {
                int n = pWords[i][j] - 'a';
                pTrie = pTrie->children[n];
            }
            
            pTrie->count = 0;
        }
    }

    trie = deallocateTrie(trie);
    if(trie != NULL)
    {
        printf("There is an error in this program\n");
    }

    return 0;
}
