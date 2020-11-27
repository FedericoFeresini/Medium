bool isValidSplit(string& s, int split)
{  
    /*
    *   substrings contains all the substrings in the solution
    *   We use a set to make sure that they are unique. 
    *   If they weren't, we return false.
    */
    unordered_set<string> substrings;
    string substring(1, s[0]);
    
    /*
    *   Loop over the bits of split
    */
    for(int i=0; i<s.size()-1; i++)
    {
        /*
        *   if((split>>i)&1) <=> if(i-th bit is a 1)
        *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        *~~~~~~~~~~~~EX: split = 17  (010001)~~~~~~~~~~~~
        *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        *   010001 & (= split>>0)
        *   000001   (= 1)
        *   ---------
        *   0000001 TRUE -> bit at 0th position is a 1
        *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        *   001000 & (= split>>1)
        *   000001   (= 1)
        *   ---------
        *   000000 FALSE -> bit at 1st position is 0
        *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        *   000010 & (= split>>3)
        *   000001   (= 1)
        *   ---------
        *   000000 FALSE -> bit at 1st position is 0
        *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        *   000001 & (= split>>4)
        *   000001   (= 1)
        *   ---------
        *   000001 TRUE -> bit at 4th position is 1
        *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        */
        if((split>>i)&1)
        {
            /*
            *   If the i-th bit is a 1, insert the substring in the solution.
            *   If there was already another identical substring, this split is not valid
            */
            if(substrings.insert(substring).second == false)
                return false;
            
            /*
            *   Reset substring to the first next char
            */
            substring = s[i+1];
        }
        else 
        {
            /*
            *   If the bit is 0, we append another char
            */
            substring += s[i+1];
        }
    }
    /*
    *   If we still have a last substring to add to the solution, we check if unique or not.
    */
    if(substring.size()!=0 && substrings.find(substring)!=substrings.end()) 
        return false;
    
    return true;
}

int maxUniqueSplit(string s) 
{
    if(s.size()==1) return 1;
    int maximumSplits = 0;
    /*
    *   bars is a number binary representable by s.size() bits
    *   Ex: for s = "abcdef", bars = 32, whose binary representation is 100000.
    */
    int bars = pow(2, s.size()-1);
    /*
    *   We loop over all the possible splits: 
    *   bar=0  -> 000000  -> ['abcdef']
    *   bar=1  -> 000001  -> ['abcde', 'f']
    *   ...
    *   bar=17 -> 010001  -> ['a', 'bcde', 'f']
    *   ...
    *   bar=31 -> 011111  -> ['a','b','c','d','e','f']
    */
    for(int bar=0; bar<bars; bar++)
    {
        /*
        *   If the split is valid, update the result.
        *   __builtin_popcount() returns the number of 1 in the binary representation of bar
        */
        if(isValidSplit(s, bar))
            maximumSplits = max(maximumSplits, __builtin_popcount(bar));
    }   
    
    /*
    *   We return maximumSplits+1
    *   (3 splits means 4 substrings [ab|cd|e|f])
    */
    return maximumSplits+1;  
}