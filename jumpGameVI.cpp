int maxResult(vector<int>& nums, int k) 
    {
        auto NumberOfElements = nums.size();
        /*
        *   MaxSumStartingAt[i] represents the maximum sum that we can obtain if we started from the element at index i.
        */
        vector<int> MaxSumStartingAt(nums.size());
        /*
        *   At each step, to compute MaxSumStartingAt[i], we need to know the maximum value among
        *   MaxSumStartingAt[i+1],...,MaxSumStartingAt[i+k]. Using a priority queue will speed up the search.
        *   The element stored in the queue is a pair<int,int> where the first element represent the value of MaxSumStartingAt[i] 
        *   and the second one is the index where i. 
        *   Example: {10, 3} means MaxSumStartinAt[3]=10;
        */
        priority_queue<pair<int,int>> q;
        
        /*
        *   The last element of MaxSumStartingAt is nothing short of the last element of nums itself.
        */
        MaxSumStartingAt.back() = nums[nums.size()-1];
        
        q.emplace(
            make_pair(nums.back(), NumberOfElements-1)
        );
        
        /*
        *   Moving backward, we fill MaxSumStartingAt up.
        */
        for(int i=MaxSumStartingAt.size()-2; i>=0; --i)
        {         
            
            /*
            *   We pick the max sum currently in MaxSumStartingAt.
            *   However, if the MaxSumStartingAt value is not reachable from index i, we drop it and pick another one.
            *
            *   Example:  
            *       MaxSumStartingAt:   [   ,   ,  7 , 0 , 10 ]
            *       q = [{10, 4}, {7, 2}, {0, 3}] 
            *      i=1 with  k=2
            *       MaxSumStartingAt[1] = nums[1]+MAX(MaxSumStartingAt[2],MaxSumStartingAt[3])
            *           -> maxSum={10, 5} => MaxSumStartingAt[4]=10 (NO NEEDED, GO TO THE NEXT ONE, q.pop())
            *           -> maxSum={7, 2} => MaxSumStartingAt[2]=7 (WE HAVE FOUND THE MAX VALUE)
            *       Consequently:
            *           MaxSumStartingAt[1] = nums[1]+MaxSumStartingAt[2]
            *           MaxSumStartingAt[1] = nums[1]+maxSum.first;
            */
            auto maxSum = q.top();
            /*
            *   As explained above, we pop the values of MaxSumStartingAt stored in the priority queue when 
            *   they are too far from the index i.
            */
            auto maxSumIndex = maxSum.second;
            while(maxSumIndex > i+k)
            {
                q.pop();
                maxSum = q.top(); 
                maxSumIndex = maxSum.second;
            }            
            
            /* 
            *   maxSumValue = MAX(MaxSumStartingAt[i+1], ... , MaxSumStartingAt[i+k]);
            */
            auto maxSumValue = maxSum.first;
            
            /*
            *   Once we have found MAX(MaxSumStartingAt[i+1], ... , MaxSumStartingAt[i+k]), we use it to compute MaxSumStartingAt[i]
            *   MaxSumStartingAt[i] = nums[i]+MAX(MaxSumStartingAt[i+1], ... , MaxSumStartingAt[i+k])
            */
            MaxSumStartingAt[i]=nums[i]+maxSumValue;
            
            /*
            *   Add to the queue {MaxSumStartingAt[i], i}, which might be used later on to compute other MaxSumStartingAt[j]
            */
            q.emplace(
                make_pair(MaxSumStartingAt[i], i)
            );
        }
        return MaxSumStartingAt[0];
    }