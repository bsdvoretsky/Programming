#include <stdio.h>

struct Date {
    int Day, Month, Year;
};

int main(int argc, char **argv)
{
    int n;
    scanf("%d", &n);
    struct Date dates[n];
    for (int i = 0; i < n; ++i) {
    	scanf("%d %d %d", &dates[i].Year, &dates[i].Month, &dates[i].Day);
    }
    
    struct Date temp_dates[n];
    int k = 0;
    for (int i = 0; i < 3; ++i)  {
    	if (i == 0) {
	    	for (int d = 1; d <= 31; ++d) {
		    	for (int j = 0; j < n; ++j) {
		    		if (dates[j].Day == d) {
		    			temp_dates[k] = dates[j];
		    			k++;
		    		}
		    	}
		    }
    	}
    	else if (i == 1) {
	    	for (int m = 1; m <= 12; ++m) {
		    	for (int j = 0; j < n; ++j) {
		    		if (dates[j].Month == m) {
		    			temp_dates[k] = dates[j];
		    			k++;
		    		}
		    	}
		    }
    	}
    	else {
    		for (int y = 1970; y <= 2030; ++y) {
		    	for (int j = 0; j < n; ++j) {
		    		if (dates[j].Year == y) {
		    			temp_dates[k] = dates[j];
		    			k++;
		    		}
		    	}
		    }
    	}
    	for (int j = 0; j < n; ++j) {
				dates[j] = temp_dates[j];
			}
		k = 0;
    }
    for (int j = 0; j < n; ++j) {
    	printf("%04d %02d %02d\n", dates[j].Year, dates[j].Month, dates[j].Day);
    }
    return 0;
}