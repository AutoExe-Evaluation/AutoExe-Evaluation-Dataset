def main():
    # PRE:
    # Input Format:
    # The first line of the input contains a single integer t (1 \le t \le 10^4)  — the number of test cases in the test.The following are descriptions of the input test cases.The first line of the description of each test case contains one integer n (1 \le n \le 50)  — the array a.The second line of the description of each test case contains n integers a_1, a_2, \dots, a_n (1 \le a_i \le 10^9)  — elements of the array a.
    # POST:
    # Program Description:
    # Polycarp got an array of integers a[1 \dots n] as a gift. Now he wants to perform a certain number of operations (possibly zero) so that all elements of the array become the same (that is, to become a_1=a_2=\dots=a_n). In one operation, he can take some indices in the array and increase the elements of the array at those indices by 1.For example, let a=[4,2,1,6,2]. He can perform the following operation: select indices 1, 2, and 4 and increase elements of the array in those indices by 1. As a result, in one operation, he can get a new state of the array a=[5,3,1,7,2].What is the minimum number of operations it can take so that all elements of the array become equal to each other (that is, to become a_1=a_2=\dots=a_n)?
    # Output Format:
    # For each test case, print one integer  — the minimum number of operations to make all elements of the array a equal.
    m = int(input())
    
    for _ in range(m):
        n = int(input())
        vals = list(map(int, input().split(' ')))
        print(max(vals) - min(vals))
