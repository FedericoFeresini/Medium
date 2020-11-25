 //https://leetcode.com/contest/biweekly-contest-31/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/
 // FIRST APPROACH
 int findSmallestNumberFirstAttempt(vector<int>& arr, int start, int end)
    {
        int smallest = arr[start];
        int idx = start;
        for(int i=start; i<end; i++)
        {
            if(smallest > arr[i]){
                smallest = arr[i];
                idx = i;
            }
        }
        return idx;
    }
    
    int turnInAllOnes(vector<int>& subarray, int start, int end, int substraction)
    {
        if(start>=end) return 0;

        int idx = findSmallestNumber(subarray, start, end);
        if(start+1 == end)
            return subarray[start]-1-substraction;
        
        return turnInAllOnes(subarray, start, idx, substraction+subarray[idx]-1-substraction) +
            turnInAllOnes(subarray, idx+1, end, substraction+subarray[idx]-1-substraction) +
            subarray[idx]-1-substraction;
    }
    
    int minNumberOperations(vector<int>& target) 
    {
        int res = turnInAllOnes(target, 0, target.size(), 0);
    
        return res+1;
        
    }

    //[1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2.....] TLE