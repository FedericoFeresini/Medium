    long MOD = 1000000007;
    long MaxPowOfTwo = 1048576;
    int countPairs(vector<int>& deliciousness) 
    {
        /*
        * pastFoodDeliciousness containes the deliciousness of the already visited food. 
        * Ex: pastFoodDeliciousness[4]=3 means that we have already visited 3 food with deliciousness=4
        */
        unordered_map<int, int> pastFoodDeliciousness;
        long result = 0;
        
        /*
        * powOfTwoNumbers containes all the power-of-two numbers, which represent the deliciousness to reach 
        * by summing two elements up in order to have a good meal
        */
        vector<int> powOfTwoNumbers = {0, 1};
        int powOfTwoNumber = 2;
        while(powOfTwoNumbers.back() != MaxPowOfTwo)
        {
            powOfTwoNumbers.push_back(powOfTwoNumber);   
            powOfTwoNumber *= 2;
        }
        powOfTwoNumbers.push_back(powOfTwoNumber);
        
        /*
        * Sort deliciousness, so that food with lower deliciousness are considered first
        */
        sort(deliciousness.begin(), deliciousness.end());
        
        for(auto& foodDeliciousness : deliciousness)
        {
            /*
            * To create a good meal starting from foodDeliciousness=0, we need another food whose deliciousness is a power of two.
            * However, as the deliciousness array is sorted, we are sure that foodDeliciousness=0 are the first elements to be analyzed 
            * in the loop, meaning that no other food with bigger deliciousness has already been visited. For these reasons, we just
            * want to count the frequency of foodDeliciousness=0.
            */
            if(foodDeliciousness == 0) 
            {
                pastFoodDeliciousness[foodDeliciousness]++;
                continue;
            }
            
            /*
            * Given a foodDeliciousness, we want to find what is the closest bigger deliciousness that we can reach.
            * Examples: 
            *   foodDeliciousness=3 -> closestDeliciousnessToReachForAGoodMeal=4 (2^2)
            *   foodDeliciousness=25 -> closestDeliciousnessToReachForAGoodMeal=32 (2^5)
            * 
            */ 
            auto closestDeliciousnessToReachForAGoodMeal = lower_bound(powOfTwoNumbers.begin(), powOfTwoNumbers.end(), foodDeliciousness);
            
            /*
            * This if condition is verified if foodDeliciousness is already a power of two. As a matter of fact,
            * if foodDeliciousness is power of two, the closestDeliciousnessToReachForAGoodMeal is 0 or itself.
            * Example:
            *   foodDeliciousness=4, the already visited food that we are looking for are those whose deliciousness is 0 or 4.
            *   (NOTE: Also a food with deliciousness = 12 would make a good meal, but rememeber that deliciousness is sorted, 
            *       meaning that we cannot have already visited a food with a deliciousness bigger than foodDeliciousness)
            */
            if(*closestDeliciousnessToReachForAGoodMeal == foodDeliciousness) 
            {
                /*
                * Add up to the result the already visited food with same deliciousness or with deliciousness=0 
                */
                result += pastFoodDeliciousness[foodDeliciousness]+pastFoodDeliciousness[0];
                /*
                * Add ingredient to already visited food
                */
                pastFoodDeliciousness[foodDeliciousness]++;
                continue;
            }
            
            /*
            * neededDeliciousness is the needed deliciousness we need to add to the current foodDeliciousness in order to
            * have a good meal
            */
            auto neededDeliciousness = *closestDeliciousnessToReachForAGoodMeal - foodDeliciousness;
            
            /*
            * previousFoodWithNeededDeliciousness is the number of already visited food that has the deliciousness we are looking for
            * to create a good meal
            */
            auto previousFoodWithNeededDeliciousness = pastFoodDeliciousness[neededDeliciousness];
                        
            /*
            * Add the food deliciousness to the already visited ones
            */
            pastFoodDeliciousness[foodDeliciousness]++;
            
            /*
            * Add up to the result the number of already visited food that can create a good meal if paired with foodDeliciousness 
            */
            if(previousFoodWithNeededDeliciousness != 0) 
                result += previousFoodWithNeededDeliciousness;
            
        }
        
        return result%MOD;
    }