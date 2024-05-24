// lession 10 https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/min_perimeter_rectangle/
//MinPerimeterRectangle coding task - Learn to Code - Codility
// you can use includes, for example:
#include <math.h>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(int N) {
    // Implement your solution here
    int sqroot = sqrt(N);
    if (sqroot * sqroot == N) {
        return 4 * sqroot;
    }
    for (int i = sqroot; i > 0; i--){
        int width = N/i;
        if (width * i == N) {
            return 2 * (width + i);
        }
    }
    return 2 * (N+1);
}
