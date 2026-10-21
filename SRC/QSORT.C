#include "qsort.h"
#include "tringl.h"

void quick_sort(cvec* triangles, int low, int high) {
    int i = low;
    int j = high;
    double pivot = ((triangle *)cv_at(triangles, low + ((high - low) >> 1)))->avg_depth;

    while (i <= j) {
        while (((triangle *)cv_at(triangles, i))->avg_depth < pivot)
            i++;

        while (((triangle *)cv_at(triangles, j))->avg_depth > pivot)
            j--;

        if (i <= j) {
            triangle *a = (triangle *)cv_at(triangles, i);
            triangle *b = (triangle *)cv_at(triangles, j);
            triangle tmp = *a;

            *a = *b;
            *b = tmp;

            i++;
            j--;
        }
    }

    if (low < j)
        quick_sort(triangles, low, j);

    if (i < high)
        quick_sort(triangles, i, high);
}