#include <stdio.h>

void print_menu() {
    printf("\nMENU:\n");
    printf("1. Enter vector of numbers\n");
    printf("2. Find all numbers smaller than a given natural number n that are relatively prime to n\n");
    printf("3. Find longest contiguous subsequence with maximum sum\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

int read_vector(int v[]) {
    /*
     *Reads a vector
     *param:v[]-the vector we read
     *return:n-number of elem in v
     */
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    return n;
}

int gcd(int n, int x)
{
    /*
     *computes the greatest common divisor of two numbers
     *param:n and x the numbers
     *return:the greatest common divisor
     */
	if (x == 0)
		return n;
	return gcd(x, n % x);
}

int read_number() {
    int n;
    printf("Enter a natural and non-null number: ");
    scanf("%d", &n);
    return n;
}

void print_result(int res[],int n,int number) {
    printf("Numbers smaller than %d and relatively prime to %d: ", number,number );
    for (int i = 0; i < n; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");
}

void all_relative_primes()
{
    /*
     * Finds all numbers smaller than a given natural and non-null number n and that are relatively prime to n
     * it reads the number n and prints the required numbers
     */
    int n,res[100],j=0;
    n=read_number();
    for (int i = 2; i < n; i++) {
        if (gcd(n, i) == 1) {
            res[j++] = i;
        }
    }
    print_result(res,j-1,n);
}

void print_longest_subsequence(int v[],int s,int f) {
    /*
     *prints the longest subsequence with the bigest sum
     *param: v- the vector,s-starting index of subsequence,f-ending index of subsequence
     */
    printf("The longest contiguous subsequence is: ");
    for (int j = s;j <= f;j++)
    {
        printf("%d ", v[j]);
    }
    printf("\n");
}

void longest_subsequence_max_sum(int v[], int n)
{
    /*
     *finds the longest subsequence of maximum sum
     *param:v-the vector,n-number of elems in v
     */
    if (n == 0) {
        printf("No elements in the vector.\n");
        return;
    }
	int max_sum = 0, actual_sum = 0,start=0,final=0,i,s=0,f=0,all_negative=1,max=0;
    for (i = 0;i < n;i++)
    {
        actual_sum += v[i];
        if (actual_sum > max_sum) {
            max_sum = actual_sum;
            start = s;
            final = i;
        }
        if (actual_sum<0)
		{
			actual_sum = 0;
			s = i + 1;
            f = i + 1;
		}
        if (v[i]>0) {
            all_negative=0;
        }
        if (v[i]>v[max]) {
            max = i;
        }
    }
    if (all_negative) {
        start=max;
        final=max;
    }
    print_longest_subsequence(v,start,final);
}


int main() {
    int option, v[100], n = 0;
    while (1) {
        print_menu();
        scanf("%d", &option);
        switch (option) {
            case 1:
                n=read_vector(v);
            printf("Vector entered\n");
            printf("n: %d\n", n);
            printf("Elements: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", v[i]);
            }
            printf("\n");
            break;
            case 2:
                all_relative_primes();
            break;
            case 3:
                longest_subsequence_max_sum(v,n);
            break;
            case 4:
                printf("Exiting...\n");
            return 0;
            default:
                printf("Invalid option. Try again.\n");
            break;
        }
    }
}