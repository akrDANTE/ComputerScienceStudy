### All about the Array

# Array Data Structure

Array is a collection of data items that are of same type sorted together in adjoining memory locations.
In most languages arrays are static but there are also dynamic variants of the array.

## Static Array Stats:

            * Retreival : O(1)
            * Search : O(n) unsorted
                       O(log(n)) sorted
            * Insertion: O(n) shifting required
            * Deletion: O(n) shifting required
            * Memory: Poor( if number of elements not known)

Array is the most fundamental of the data structures.

In C Programming language array is defined as follows:

            int arr[100];
            // int => data type of elements
            // arr => name of the variable
            // 100 => size of the array, number of elements array can hold

            arr[0] = 10; //access the first element of the array

            //Strings are also arrays, arrays of characters
            char str[10] = "hahahahah"; // last character is /0(null) character

## Array Coding Questions:
