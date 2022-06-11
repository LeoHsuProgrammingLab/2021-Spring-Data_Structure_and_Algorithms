//ref:http://alrightchiu.github.io/SecondRound/comparison-sort-merge-sorthe-bing-pai-xu-fa.html
//https://math.stackexchange.com/questions/2352693/counting-intersections-of-secant-lines-in-a-circle#comment4871287_2362680
//https://courses.engr.illinois.edu/cs374/sp2020/B/hw/hw_05_extra.pdf
//I asked some questions on the forum and discuss with TA in TA Hour.(Especially thank TA, Lin Ting Feng. He gave me lots of inspiration.)

#include <stdio.h>
#include "generator.h"

int max_value = 3000001;//最大的數值為3000000
void Merge_RL1(int array[], int array1[], int array2[], int front, int mid, int tail){
    int left = mid-front+2;
    int left_p[left];
    int left_q[left-1];
    int left_r[left-1];
    left_p[left-1] = max_value;
    int right = tail-mid+1;
    int right_p[right];
    int right_q[right-1];
    int right_r[right-1];
    right_p[right-1] = max_value;
    int l, m, p;
    int right_id = 0 , left_id = 0;
    for(l = 0; l < left-1; l++){
        left_p[l] = array[front+l];
        left_q[l] = array1[front+l];
        left_r[l] = array2[front+l];
    }
    for (m = 0; m < right-1; m++){
        right_p[m] = array[mid+1+m];
        right_q[m] = array1[mid+1+m];
        right_r[m] = array2[mid+1+m];
    }
    for (p = front; p <= tail; p++){
        if(left_p[left_id] < right_p[right_id]){
            array[p] = left_p[left_id];
            array1[p] = left_q[left_id];
            array2[p] = left_r[left_id];
            left_id++;
        }
        else if(left_p[left_id] == right_p[right_id]){//若p點相同，把r比較大的排前面
            if(left_r[left_id] >= right_r[right_id]){
                array[p] = left_p[left_id];
                array1[p] = left_q[left_id];
                array2[p] = left_r[left_id];
                left_id++;
            }
            else{
                array[p] = right_p[right_id];
                array1[p] = right_q[right_id];
                array2[p] = right_r[right_id];
                right_id++;
            }
        }
        else{               
            array[p] = right_p[right_id];
            array1[p] = right_q[right_id];
            array2[p] = right_r[right_id];
            right_id++;
        }
    }
}

void MergeSort(int array[], int array1[], int array2[], int front, int tail){
    if(front < tail){
        int mid = (front + tail)/2;
        MergeSort(array, array1, array2, front, mid);
        MergeSort(array, array1, array2, mid+1, tail);
        Merge_RL1(array, array1, array2, front, mid, tail);
    }
}

void Merge_RL2(int arr0[], int arr1[], int arr2[], int front, int mid, int tail , long long *num){
    int left = mid-front+2;
    int left_p[left-1];
    int left_q[left];
    int left_r[left];
    left_q[left-1] = max_value;
    left_r[left-1] = max_value;
    int right = tail-mid+1;
    int right_p[right-1];
    int right_q[right];
    int right_r[right];
    right_q[right-1] = max_value;
    right_r[right-1] = max_value;
    int l, m, p;
    int right_id = 0 , left_id = 0;
    int right_id_r = 0, left_id_r = 0;
    int right_count = 0, left_count = 0;
    for(l = 0; l < left-1; l++){
        left_p[l] = arr0[front+l];
        left_q[l] = arr1[front+l];
        left_r[l] = arr2[front+l];
    }
    for (m = 0; m < right-1; m++){
        right_p[m] = arr0[mid+1+m];
        right_q[m] = arr1[mid+1+m];
        right_r[m] = arr2[mid+1+m];
    }
    for (p = front; p <= tail; p++){
            //比較大，右邊要往右推一個
        if( left_r[left_count] >= right_q[right_count]){//左邊第一個的r要大於右邊的第一個q
            if(left_count != left-1){
                *num += (left-1) - left_count;
                right_count++;
            }   
            //左邊的往右找，因為r>q，則右邊的的r也都大於q
        }
        else{//比較小，左邊要往右推一個
            left_count++;
        }
        //sort q
        if(left_q[left_id] <= right_q[right_id]){
            arr1[p] = left_q[left_id];
            left_id++;
        }
        else{               
            arr1[p] = right_q[right_id];
            right_id++;
        }
        //sort r
        if(left_r[left_id_r] <= right_r[right_id_r]){
            arr2[p] = left_r[left_id_r];
            left_id_r++;
        }
        else{               
            arr2[p] = right_r[right_id_r];
            right_id_r++;
        }
    }
}

void MergeCount(int arr0[], int arr1[], int arr2[], int front, int tail, long long *num){
    if(front < tail){
        int mid = (front + tail)/2;
        MergeCount(arr0, arr1, arr2, front, mid, num);
        MergeCount(arr0, arr1, arr2, mid+1, tail, num);
        Merge_RL2(arr0, arr1, arr2, front, mid, tail, num);
    }
}


int main() {
    generator.init();
    int t = generator.getT();
    while (t--) {
        int n, *p, *q, *r;
        generator.getData(&n, &p, &q, &r);
        int i, j, k;
        long long num = 0;//long long is needed
        for(j = 0; j < n; j++){//make every q<r
            if(q[j] > r[j]){
                k = q[j];
                q[j] = r[j];
                r[j] = k;
            }
        }
        MergeSort(p, q, r, 0, n-1);
    
        MergeCount(p, q, r, 0, n-1, &num);
    
        printf("%lld\n", num);
    }
}