    vector<int> pathInZigZagTree(int label) 
    {
        vector<int> result;
        result.push_back(label);
        
        int level = floor(log2(label));

        /*
        * totalNumberOfNodes is the total number of nodes in the tree from the root (node(1)) down to a given level
        */
        int totalNumberOfNodes = 1;
        for(int l=1; l<= level; ++l)
            totalNumberOfNodes += pow(2, l);
           
        /*
        * Let's iterate parent by parent until we reach node(1), the root 
        */
        while(label > 1)
        {
            /*
            * numberOfNodesSpecificLevel is the number of nodes on a specific level.
            * For example when level is 3, numberOfNodesSpecificLevel is 8
            */
            int numberOfNodesOnThisLevel = pow(2, level);
            /*
            * distanceToTheFirstElementInTheRow is the distance between label, which is the node we are considering,
            * and the first node of the row.
            */
            int distanceToTheFirstElementOnTheRow;
            
            //If level is odd
            if(level&1)
            {
                int firstElementOddLevel = totalNumberOfNodes;
                distanceToTheFirstElementOnTheRow = firstElementOddLevel - label;
                /*
                *   Let's break firstElementTwoLevelsAbove down:
                *       totalNumberOfNodes = The total number of nodes from the root node, down to the level of label
                *       numberOfNodesOnThisLevel = number of nodes on label's level
                *       pow(2, level-1) = number of nodes on the level above
                *       +1 = the first element on an even level is the biggest element of the level above + 1
                *   Example: In order to compute the first element of Level 6, 
                *            we want compute the total number of nodes from root to Level5 +1 
                */
                int firstElementTwoLevelsAbove = totalNumberOfNodes - numberOfNodesOnThisLevel - pow(2, level-1) + 1;
                /*
                *   We know that label's parent is distanceToTheFirstElementOnTheRow/2 from the first element on its row.
                *   Update label to its parent value.
                */
                label = firstElementTwoLevelsAbove + (distanceToTheFirstElementOnTheRow/2);
            }
            //If level is even
            else
            {
                /*
                *   Let's break firstElementEvenLevel down:
                *       totalNumberOfNodes = The total number of nodes from the root node, down to the level of label
                *       pow(2, level) = number of nodes on the level
                *       +1 = the first element on an even level is the biggest element of the level above + 1
                */
                int firstElementEvenLevel = totalNumberOfNodes - pow(2,level) +1;
                distanceToTheFirstElementOnTheRow = label - firstElementEvenLevel;
                int firstElementOnTheOddLevelAbove = totalNumberOfNodes - numberOfNodesOnThisLevel;
                label = firstElementOnTheOddLevelAbove - (distanceToTheFirstElementOnTheRow/2);
            }
            
            if(label >= 1) result.push_back(label);    
            
            /*
            *   We have moved one level above. Update the level variable and the counter of the total number of nodes
            *   by subtracting to the previous total number, all the nodes of the level we are moving off.
            */
            level--;
            totalNumberOfNodes -= numberOfNodesOnThisLevel;
        }
        
        reverse(result.begin(), result.end());
        return result;
        
    }