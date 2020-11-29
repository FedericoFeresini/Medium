int waysToMakeFair(vector<int>& nums) 
{
    if(nums.size() <= 1) return 1;
    
    vector<int> Even_Indexed_Value_Sum_After(nums.size(),0);
    vector<int> Odd_Indexed_Value_Sum_After(nums.size(),0);
    vector<int> Even_Indexed_Value_Sum_Before(nums.size(),0);
    vector<int> Odd_Indexed_Value_Sum_Before(nums.size(),0);
    int result = 0;
    
    /*
    *   Populate the four arrays such that for each element of nums we know the sums 
    *   of the Odd-indexed and Even-indexed values before and after it.
    */
    for(int i=0, j=nums.size()-1; i<nums.size(); ++i, --j)
    {
        if(i%2!=0)
        {
            Odd_Indexed_Value_Sum_Before[i] = i==0? nums[i] : Odd_Indexed_Value_Sum_Before[i-1]+nums[i];
            Even_Indexed_Value_Sum_Before[i] = i==0? 0 : Even_Indexed_Value_Sum_Before[i-1];
        }
        else
        {
            Odd_Indexed_Value_Sum_Before[i] = i==0? 0 : Odd_Indexed_Value_Sum_Before[i-1];
            Even_Indexed_Value_Sum_Before[i] = i==0? nums[i] : Even_Indexed_Value_Sum_Before[i-1] + nums[i];
        }
        if(j%2!=0)
        {
            Odd_Indexed_Value_Sum_After[j] = j == nums.size()-1 ? nums[j] : Odd_Indexed_Value_Sum_After[j+1]+nums[j];
            Even_Indexed_Value_Sum_After[j] = j == nums.size()-1? 0 : Even_Indexed_Value_Sum_After[j+1];
        }
        else if(j%2==0)
        {
            Odd_Indexed_Value_Sum_After[j] = j == nums.size()-1? 0 : Odd_Indexed_Value_Sum_After[j+1];
            Even_Indexed_Value_Sum_After[j] = j == nums.size()-1 ? nums[j] : Even_Indexed_Value_Sum_After[j+1]+nums[j];
        }
    }
    
    /*
    *   For each element, we compute the two sums after removing it 
    */
    for(int i=0; i<nums.size(); ++i)
    {
        /*
        *   For the first element, we need to check only the sums of the elements coming after it.
        *   There's no element before the first one.
        */
        if(i==0)
        {
            if(Odd_Indexed_Value_Sum_After[i+1] == Even_Indexed_Value_Sum_After[i+1]) result++;
        }
        /*
        *   For the last element, we need to check only the sums of the elements coming before it.
        *   There's no element after the last one.
        */
        else if(i==nums.size()-1)
        {
            if(Odd_Indexed_Value_Sum_Before[i-1] == Even_Indexed_Value_Sum_Before[i-1]) result++;
        }
        /*
        *   For the any element which is neither the first one not the last one, 
        *   we need to check the sums of the elements sitting before and after it.
        */
        else (Even_Indexed_Value_Sum_Before[i-1]+ Odd_Indexed_Value_Sum_After[i+1] == 
           Odd_Indexed_Value_Sum_Before[i-1]+Even_Indexed_Value_Sum_After[i+1]) 
        {
            result++;
        }
    }
    
    return result;
    
}