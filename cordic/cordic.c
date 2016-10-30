#include <stdio.h>
#include <stdlib.h>

double my_atan2(double x, double y);
int my_atan5(int x, int y);
int main(void)
{
    double z = my_atan5(100, 200);
    printf("\n z = %f \n", z);

    return 0;
}

/*
proto
*/
double my_atan2(double x, double y)
{
    const double sine[] = { 0.7071067811865, 0.3826834323651, 0.1950903220161, 0.09801714032956,
        0.04906767432742, 0.02454122852291, 0.01227153828572, 0.006135884649154, 0.003067956762966
        , 0.001533980186285, 7.669903187427045e-4, 3.834951875713956e-4, 1.917475973107033e-4,
        9.587379909597735e-5, 4.793689960306688e-5, 2.396844980841822e-5
    };

    const double cosine[] = { 0.7071067811865, 0.9238795325113, 0.9807852804032, 0.9951847266722,
        0.9987954562052, 0.9996988186962, 0.9999247018391, 0.9999811752826, 0.9999952938096,
        0.9999988234517, 0.9999997058629, 0.9999999264657, 0.9999999816164, 0.9999999954041,
        0.999999998851, 0.9999999997128
    };


    int i = 0;
    double x_new, y_new;
    double angleSum = 0.0;
    double angle = 45.0;

    for (i = 0; i < 15; i++)
    {
        if (y > 0)
        {
            x_new = x * cosine[i] + y * sine[i];
            y_new = y * cosine[i] - x * sine[i];
            x = x_new;
            y = y_new;
            angleSum += angle;
        } else
        {
            x_new = x * cosine[i] - y * sine[i];
            y_new = y * cosine[i] + x * sine[i];
            x = x_new;
            y = y_new;
            angleSum -= angle;
        }
        printf("Debug: i = %d angleSum = %f, angle = %f\n", i, angleSum, angle);
        angle /= 2;
    }
    return angleSum;
}


/*
efficient
*/
int my_atan5(int x, int y)
{
    const int angle[] = { 11520, 6801, 3593, 1824, 916, 458, 229, 115, 57, 29, 14, 7, 4, 2, 1 };

    int i = 0;
    int x_new, y_new;
    int angleSum = 0;

    x *= 1024; // ? X Y ???????????
    y *= 1024;

    for (i = 0; i < 15; i++)
    {
        if (y > 0)
        {
            x_new = x + (y >> i);
            y_new = y - (x >> i);
            x = x_new;
            y = y_new;
            angleSum += angle[i];
        } else
        {
            x_new = x - (y >> i);
            y_new = y + (x >> i);
            x = x_new;
            y = y_new;
            angleSum -= angle[i];
        }
        printf("Debug: i = %d angleSum = %d, angle = %d\n", i, angleSum, angle[i]);
    }
    return angleSum; 
}
