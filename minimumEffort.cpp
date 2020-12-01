int minimumEffort(vector<vector<int>>& tasks) 
{
    /*
    *   Sort the tasks by descending difference between the minimum and the actual value
    */
    sort(tasks.begin(), 
         tasks.end(), 
         [](vector<int>& A, vector<int>& B){
             return (A[1]-A[0]) > (B[1]-B[0]);
         });
    
    int totalEnergy = 0;
    int totalActual = 0;
    for(auto& task : tasks)
    {
        /*
        *   When the energy is not enough to pick the next task, we add extra energy.
        */
        if(totalActual + task[1] > totalEnergy)
        {
            totalEnergy += actual+task[1]-totalEnergy;
        }
        totalActual += task[0];
    }
    
    return energy;
}