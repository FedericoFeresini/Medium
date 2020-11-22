int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) 
    {
        /* 
         * Representing a graph through an HashMap facilitates the search of the neighbors
         * graph[originNode][destinationNode]=cost_from_originNode_to_destinationNode
         */
        unordered_map<int,unordered_map<int,int>> graph;
        for(auto& flight : flights)
            graph[flight[0]][flight[1]]= flight[2];
        
        // This queue nodesToCheck will contain the nodes which got updated and need to be checked during the very next step
        queue<int> nodesToCheck;
        // The vector previousStepDistances contains the node costs computed during the previous step.
        vector<int> previousStepDistances(n, INT_MAX);
        
        // 1. Start from the source node setting its distance to [0]
        previousStepDistances[src]=0;
        nodesToCheck.push(src);
        
        for(int step=1; step<=K+1; ++k)
        {
            /* 
             * The queue nodesToCheckNextStep will contain the nodes which get updated diring this step, and
             * consequently to be checked the next one
             */
            queue<int> nodesToCheckNextStep;
            // The vector currentStepDistances contains the node costs computed during the current step.
            vector<int> currentStepDistances = previousStepDistances;
            
            while(!nodesToCheck.empty())
            {
                int node = nodesToCheck.front();
                nodesToCheck.pop();
                
                for(auto neighbour : graph[node])
                {
                    /*
                     * 2. Update the cost to get to a neighbor only when more convenient  
                     */
                    if(currentStepDistances[neighbour.first] > previousStepDistances[node]+graph[node][neighbour.first])
                    {
                        /*
                         * Update the cost to get to the neighbor by summing the cost to get to the node computed 
                         * during the previous step and the cost to go from the node to the neighbor 
                         */
                        currentStepDistances[neighbour.first] = previousStepDistances[node]+graph[node][neighbour.first];
                        
                        // Push the updated node into the queue containing the nodes which will be checked during the next step
                        nodesToCheckNextStep.push(neighbour.first);
                    }
                }
            }
            // Prepare the data for the next step
            nodesToCheck = nodesToCheckNextStep;
            previousStepDistances = currentStepDistances;
        }
        
        return previousStepDistances[dst]==INT_MAX? -1 : previousStepDistances[dst];

    }