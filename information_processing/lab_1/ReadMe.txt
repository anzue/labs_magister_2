this file is about how lab 2 works
this lab contains 2 separate modules

for both of this modules we using vocabulary from class IndexVocabulary
this class provides indexes for words and allows us to save on our map operations and allows to get indexing by words
it uses Map so each request takes O(|words|)

IncendencyMatrix - naive method, just save matric where m[i][j] == 1 when j-th document contains i-th word and 0 otherwise.

InvertIndex - better method, saves only non-zero elements of IncendencyMatrix.
When we have a lot of documents and amount of zeros in IncendencyMatrix growths InvertIndex allows to save the same information and keep the size of structure reasonable at the same time.
Searching for a certain value here is O(log |documents|) instead of O(1) for IncendencyMatrix but in general case time will be close.
Merging info about 2 words in boolean search for both methods is O(|documents|) but for IncendencyMatrix it's guaranteed and InvertIndex can have much better results depending on data structure.
