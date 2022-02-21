#include "gameRuleGameOfLifeDefault.h"

bool gameRuleGameOfLifeClosedInTorus(std::vector<std::vector<bool> > &fields, int i, int j)
{
	int count{ 0 };
    if (i == 0)
    {
        int ii = fields.size() - 1;
        
        if (j == 0)
        {
            int jj = fields[0].size() - 1;

            if (fields[ii][jj])
                count++;
            if (fields[ii][j])
                count++;
            if (fields[ii][j+1])
                count++;
            if (fields[i][jj])
                count++;
            if (fields[i][j+1])
                count++;
            if (fields[i+1][jj])
                count++;
            if (fields[i+1][j])
                count++;
            if (fields[i+1][j+1])
                count++;
        }
        else if (j == fields[0].size() - 1)
        {
            int jj = 0;

            if (fields[ii][j-1])
                count++;
            if (fields[ii][j])
                count++;
            if (fields[ii][jj])
                count++;
            if (fields[i][j-1])
                count++;
            if (fields[i][jj])
                count++;
            if (fields[i+1][j-1])
                count++;
            if (fields[i+1][j])
                count++;
            if (fields[i+1][jj])
                count++;
        }
        else
        {
            if (fields[ii][j-1])
                count++;
            if (fields[ii][j])
                count++;
            if (fields[ii][j+1])
                count++;
            if (fields[i][j-1])
                count++;
            if (fields[i][j+1])
                count++;
            if (fields[i+1][j-1])
                count++;
            if (fields[i+1][j])
                count++;
            if (fields[i+1][j+1])
                count++;
        }
    }
    else if (i == fields.size() - 1)
    {
        int ii = 0;

         if (j == 0)
        {
            int jj = fields[0].size() - 1;

            if (fields[i-1][jj])
                count++;
            if (fields[i-1][j])
                count++;
            if (fields[i-1][j+1])
                count++;
            if (fields[i][jj])
                count++;
            if (fields[i][j+1])
                count++;
            if (fields[ii][jj])
                count++;
            if (fields[ii][j])
                count++;
            if (fields[ii][j+1])
                count++;
        }
        else if (j == fields[0].size() - 1)
        {
            int jj = 0;

            if (fields[i-1][j-1])
                count++;
            if (fields[i-1][j])
                count++;
            if (fields[i-1][jj])
                count++;
            if (fields[i][j-1])
                count++;
            if (fields[i][jj])
                count++;
            if (fields[ii][j-1])
                count++;
            if (fields[ii][j])
                count++;
            if (fields[ii][jj])
                count++;
        }
        else
        {
            if (fields[i-1][j-1])
                count++;
            if (fields[i-1][j])
                count++;
            if (fields[i-1][j+1])
                count++;
            if (fields[i][j-1])
                count++;
            if (fields[i][j+1])
                count++;
            if (fields[ii][j-1])
                count++;
            if (fields[ii][j])
                count++;
            if (fields[ii][j+1])
                count++;
        }
    }
    else
    {
         if (j == 0)
        {
            int jj = fields[0].size() - 1;

            if (fields[i-1][jj])
                count++;
            if (fields[i-1][j])
                count++;
            if (fields[i-1][j+1])
                count++;
            if (fields[i][jj])
                count++;
            if (fields[i][j+1])
                count++;
            if (fields[i+1][jj])
                count++;
            if (fields[i+1][j])
                count++;
            if (fields[i+1][j+1])
                count++;
        }
        else if (j == fields[0].size() - 1)
        {
            int jj = 0;

            if (fields[i-1][j-1])
                count++;
            if (fields[i-1][j])
                count++;
            if (fields[i-1][jj])
                count++;
            if (fields[i][j-1])
                count++;
            if (fields[i][jj])
                count++;
            if (fields[i+1][j-1])
                count++;
            if (fields[i+1][j])
                count++;
            if (fields[i+1][jj])
                count++;
        }
        else
        {
            if (fields[i-1][j-1])
                count++;
            if (fields[i-1][j])
                count++;
            if (fields[i-1][j+1])
                count++;
            if (fields[i][j-1])
                count++;
            if (fields[i][j+1])
                count++;
            if (fields[i+1][j-1])
                count++;
            if (fields[i+1][j])
                count++;
            if (fields[i+1][j+1])
                count++;
        }
    }

	if (fields[i][j])
	{
		if (count <= 1 || count >= 4)
			return false;
		return true;
	}
	else if (count == 3)
	{
		return true;
	}
	return false;
}