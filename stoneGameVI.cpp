    enum Player {Alice=0, Bob=1};
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) 
    {
        int numberOfStones = aliceValues.size();
        int aliceScore = 0;
        int bobScore = 0;
        
        // Sort the stones by sum of bob and alice values
        auto cmp = [&](const int s1, const int s2){
            return aliceValues[s1]+bobValues[s1] > aliceValues[s2]+bobValues[s2];
        };
        
        // Create an array containing the stone indexes
        // stoned:= [0, 1, 2, ..., numberOfStones]
        vector<int> stones(numberOfStones);
        iota(stones.begin(), stones.end(), 0);
        
        // Sort the stones to have those with a bigger total value before
        sort(stones.begin(), stones.end(), cmp);
        
        // Alice starts first
        Player player = Alice;
        
        for(int i=0; i<stones.size(); ++i)
        {
            if(player==Alice) 
                aliceScore += aliceValues[stones[i]];
            else 
                bobScore += bobValues[stones[i]];
            
            player = (player==Alice)? Bob : Alice;
        }
        
        if(aliceScore == bobScore) 
            return 0; 
        
        return  aliceScore>bobScore ? 1 : -1;
    }