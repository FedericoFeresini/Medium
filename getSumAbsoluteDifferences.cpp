 vector<int> getSumAbsoluteDifferences(vector<int>& nums) 
    {
        vector<int> result(nums.size(),0);
        
        /*
        *   First off, we compute the sum of absolute distances for the first element.
        */
        for(int i=0; i<nums.size(); ++i)
            result[0] += nums[i]-nums[0];
        

        /*
        *   The sum of the absolute distances from an element [i] to all the others, can be
        *   computed from the result for [i-1]. 
        */
        for(int i=1; i<nums.size(); i++)
        {
            auto numberOfElementsBefore = i;
            auto numberOfElementsAfter = (nums.size()-i);
            
            result[i]+= result[i-1] + 
                    numberOfElementsBefore*(nums[i]-nums[i-1]) - 
                    numberOfElementsAfter*(nums[i]-nums[i-1]);
        }
        
        return result; 
    }