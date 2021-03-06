Name: Brice Allard

Date: February 26<sub>th</sub>

Assignment: Program 3

Description:
***Fun Part:*** <br>
>Were going to create crazy names similar to what github and repl.it do when suggesting names for repls or repos. Github suggests things like: `musical-journey` or `cautious-waffle` or `bug-free-succotash`. Whereas repl.it suggests things like:  `LikelyTatteredGreatwhiteshark` or `PepperySunnyMaggot` or `ClearcutLongtermCrocodile` or `RowdyWorthwhileBird`. I'm not sure what thier algorithm is, but I'm sure we can come up with something better (or at least similar). 

***Data Structures Part:*** <br>
>After we generate about 10000 names, we are going to compare the performance of a Binary Search Tree vs an AVL tree when it comes to finding those named components in each tree.

- Files:
    - `word_files`
        - `nouns.txt`
        - `adverbs.txt`
        - `animals.txt`
        - `adjectives.txt`
        - `verbs.txt`
    - `generate_words.cpp`
    - `README.md`
    - `tenthousandwords.txt`

**Output**
```
AVL Tree -
Adjectives loaded: 15571
Adverbs loaded: 3237
Animals loaded: 235
Nouns loaded: 53737
Verbs loaded: 12018
BS Tree -
Adjectives loaded: 15571
Adverbs loaded: 3237
Animals loaded: 235
Nouns loaded: 53737
Verbs loaded: 12018

Total Comparisons -
BST Comparisons = 685812
AVL Comparisons = 477774
Number of Adjectives = 10937
Number of Adverbs = 3650
Number of Nounds = 4409
Number of Verbs = 0
Elapsed time: 2290.63s
```
