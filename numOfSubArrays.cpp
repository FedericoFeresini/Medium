    long MOD=1000000007;

    int numOfSubarrays(vector<int>& arr) 
    {
        long result = 0;
        
        /*
        *   previousStepAddedEvenNumbers: how many even numbers we added during the previous step
        *   previousStepAddedOddNumbers: how many odd numbers we added during the previous step
        *   (It's the green rectangle)
        */
        int previousStepAddedEvenNumbers=0;
        int previousStepAddedOddNumbers=0;
        
        /*
        *   recentlyAddedEvenNumbers: how many even numbers we've added during the current cycle
        *   recentlyAddedEvenNumbers: how many odd numbers we've added during the current cycle
        *   (It's the orange rectangle)
        */
        int recentlyAddedEvenNumbers=0;
        int recentlyAddedOddNumbers=0;
        
        for(int i=0; i<arr.size(); ++i)
        {
            if(arr[i]%2==0)
            {
                /*
                *   When an even number gets added to an even number, the result is still an even number.
                *   For this reason, adding arr[i] to any of the previousEvenNumbers numbers, will keep them even.
                *   Example:    arr[i]=4   
                *               previousEvenNumbers = [[1,3],[1,3,2]] = [[4],[6]]           size:2
                *               -----------------------------------
                *               recentEvenNumbers=[[4],[1,3,4],[1,3,2,4]] = [[4],[8],[10]]  size:3
                */
                recentlyAddedEvenNumbers = 1 + previousStepAddedEvenNumbers;
                /*
                *   When an even number gets added to an odd number, the result is an odd number.
                *   For this reason, adding arr[i] to any of the previousOddNumbers numbers, will keep them odd.
                *   Example:    arr[i]=4   
                *               previousOddNumbers = [[1,2],[1,4,2]] = [[3],[7]]    size:2
                *               -----------------------------------
                *               recentOddNumbers=[[1,2,4],[1,4,2,4]] = [[7], [11]]  size:2
                */
                recentlyAddedOddNumbers = previousStepAddedOddNumbers;
            }
            else
            {
                /*
                *   When an odd number gets added to an odd number, the result is an even number.
                *   For this reason, adding arr[i] to any of the previousOddNumbers odd numbers, will turn them into even numbers.
                *   Example:    arr[i]=3   
                *               previousOddNumbers = [[1,2],[1,4,2]] = [[3],[7]]    size:2
                *               -----------------------------------
                *               recentEvenNumbers=[[1,2,3],[1,4,2,3]] = [[6],[10]]  size:2
                */
                recentlyAddedEvenNumbers = previousStepAddedOddNumbers;
                /*
                *   When an odd number gets added to an even number, the result is an odd number.
                *   For this reason, adding arr[i] to any of the previousEvenNumbers numbers, will turn them into odd numbers.
                *   Example:    arr[i]=3   
                *               previousEvenNumbers = [[1,3],[1,3,2]] = [[4],[6]]       size:2
                *               -----------------------------------
                *               recentOddNumbers=[[1,3,3],[1,3,2,3]] = [[3],[7],[9]]    size:3
                */
                recentlyAddedOddNumbers = 1 + previousStepAddedEvenNumbers;
            }
            
            /*
            *   Update the result adding up the new odd numbers we have found (don't forget about the module), 
            *   and set everything up for the next cycle by copying the "recentlyAdded__Numbers" into "previousStepAdded__Numbers"
            */
            result = result%MOD + recentlyAddedOddNumbers;
            
            previousStepAddedEvenNumbers = recentlyAddedEvenNumbers;
            previousStepAddedOddNumbers = recentlyAddedOddNumbers;
        }
        return result;
    }