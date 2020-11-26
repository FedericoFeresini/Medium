//https://leetcode.com/contest/weekly-contest-211/problems/best-team-with-no-conflicts/
struct player 
{ 
    int age; 
    int score; 
};

int bestTeamScore(vector<int>& scores, vector<int>& ages) 
{   
    vector<player> players;
    for(int i=0; i<scores.size(); ++i)
    {
        player p = {ages[i], scores[i]};
        players.push_back(p);
    }
            
    /*
    *   comparator will sort the players from younger to older.
    *   If two players are the same age, the player with an higher score comes first.
    */
    auto comparator = [](player& A, player& B){return  (A.age==B.age) ? (A.score < B.score) : (A.age < B.age);};
    sort(players.begin(), players.end(), comparator);
    
    /*
    *   bestScores[i] is the highest scores among all the possible scores obtained by the 
    *   teams where player[i] could play without any conflicts
    */
    vector<int> bestScores;
    int bestScore = 0;
        
    for(int i=0; i<players.size(); ++i)
    {
        auto currentPlayer = players[i];
        /*
        *   A player, at worst, can play alone.
        */
        bestScores.push_back(currentPlayer.score);
        
        /*
        *   Iterate over the previously visited players, and if currentPlayer's age and score dont conflict,
        *   add it to the team
        */
        for(int j=0; j<i; ++j)
        {
            /*
            *   currentPlayer doens't  conflict if is the same age or is older but has an bigger or equal score
            */
            if(currentPlayer.age == players[j].age || (currentPlayer.score >= players[j].score))
            {
                /*
                *   update the bestScore of the team with player[i] if better than before
                */
                bestScores[i] = max(bestScores[i], bestScores[j]+currentPlayer.score);
            }
        }
        /*
        *   If the highest score of the best of the teams with player[i] is the maximum seen so far, update the final solution.
        */
        if(bestScore < bestScores[i]) bestScore = bestScores[i];
        
    }
    return bestScore;
}