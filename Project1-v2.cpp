#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <immintrin.h>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <cblas.h>

using namespace std;

struct matrix {
    int column;
    int row;
    float** values;
    matrix(int r, int c) {
        row = r;
        column = c;
        values = new float*[row];
        for (int i=0; i<row; i++) {
            values[i] = new float[column];
        }
        srand(unsigned(time(0)));
        for (int i=0; i<row; i++) {
            for (int j=0; j<column; j++) {
                values[i][j] = getRandData(1,2);
            }
        }
    }
    void print() {
        for (int i=0; i<row; i++) {
            for (int j=0; j<column; j++) {
                std::cout << left << setw(8) << values[i][j] << " ";
            }
            std::cout << endl;
        }
    }
    static float getRandData(int min,int max)
    {
        float m1=(float)(rand()%101)/101;
        min++;
        float m2=(float)((rand()%(max-min+1))+min);
        m2=m2-1;
        return m1+m2;
    }
};

matrix* reverse(matrix* a) {
    matrix* res = new matrix(a->column,a->row);
    for (int i=0; i<a->row; i++) {
        for (int j=0; j<a->column; j++) {
            res->values[j][i]=a->values[i][j];
        }
    }
    return res;
}

matrix* product2(const matrix *a, const matrix* b)
{
    size_t bound = a->column;
    auto* res = new matrix(a->row,b->row);
    for (int i=0; i<a->row; i++) {
        for (int j=0; j<b->row; j++) {
            float sum[8] = {0};
            __m256 aa, bb;
            __m256 c = _mm256_setzero_ps();
            #pragma omp parallel for
            for (size_t k = 0; k < bound; k+=8) {
                aa = _mm256_load_ps(a->values[i] + k);
                bb = _mm256_load_ps(b->values[j] + k);
                c =  _mm256_add_ps(c, _mm256_mul_ps(aa, bb));
            }
            _mm256_store_ps(sum, c);
            res->values[i][j] = sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7];
        }
    }
    return res;
}

matrix* product1(matrix *a, matrix *b) {
    matrix* res = new matrix(a->row,b->column);
    float cal = 0;
    for (int i=0; i<a->row; i++) {
        for (int j=0; j<b->column; j++) {
            cal = 0;
            for (int k=0; k<a->column; k++) {
                cal+=a->values[i][k]*b->values[k][j];
            }
            res->values[i][j] = cal;
        }
    }
    return res;
}

float* mtof(matrix* a) {
    static long zz = a->row * a->column;
    float* res;
    res = new float[zz];
    int c=0;
    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < a->column; j++) {
            res[c] = a->values[i][j];
            c++;
        }
    }
    return res;
}

vector<string> split(const string& str, const string& delim) {
    vector<string> res;
    if("" == str) return res;
    char * strs = new char[str.length() + 1] ;
    strcpy_s(strs, strlen(str.c_str())+1, str.c_str());
    char * d = new char[delim.length() + 1];
    strcpy_s(d, strlen(delim.c_str()) + 1, delim.c_str());
    char * next_token = NULL;
    char *p = strtok_s(strs, d, &next_token);
    while(p) {
        string s = p;
        res.push_back(s);
        p = strtok_s(NULL, d, &next_token);
    }
    return res;
}

int main() {
    matrix* a; matrix* b;
    int ra,rb,ca,cb;
    while (true) {
        cin >> ra >> ca;
//        cin.get();
        a = new matrix(ra,ca);
//        string s;
//        const string ju = " ";
//        bool jj = true;
//        for (int i=0; i<ra; i++) {
//            getline(cin,s);
//            const char* ss = s.c_str();
//            while (*ss) {
//                if (((*ss)!='.') && ((*ss)<'0') && ((*ss)>'9') && ((*ss)!=' ') && ((*ss)!='\0')) {
//                    jj = false;
//                    break;
//                }
//                ss++;
//            }
//            if (!jj) break;
//            vector<string> sss = split(s,ju);
//            float rr;
//            int j = 0;
//            for (auto vs : sss) {
//                stringstream st;
//                st << vs;
//                st >> rr;
//                a->values[i][j++] = rr;
//            }
//        }
//        if (!jj) {
//            cout << "Wrong input!" << endl;
//            continue;
//        }
        cin >> rb >> cb;
//        cin.get();
        b = new matrix(rb,cb);
//        for (int i=0; i<rb; i++) {
//            getline(cin,s);
//            const char* ss = s.c_str();
//            while (*ss) {
//                if (((*ss)!='.') && ((*ss)<'0') && ((*ss)>'9') && ((*ss)!=' ')) {
//                    jj = false;
//                    break;
//                }
//                ss++;
//            }
//            if (!jj) break;
//            vector<string> sss = split(s,ju);
//            float rr;
//            int j = 0;
//            for (auto vs : sss) {
//                stringstream st;
//                st << vs;
//                st >> rr;
//                b->values[i][j++] = rr;
//            }
//        }
//        if ((ca==rb) && (jj)) break;
//        cout << "Wrong input!" << endl;
          break;
    }
    auto start1 = std::chrono::steady_clock::now();
    matrix* res1 = product1(a,b);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff1 = end1-start1;
    matrix* d = reverse(b);
    auto start2 = std::chrono::steady_clock::now();
    matrix* res2 = product2(a,d);
    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff2 = end2 - start2;
    const float xx = 1.0;
    const float yy = 0.0;
    static int zz = a->row * b->column;
    float* res;
    res = new float[zz];
    auto start3 = std::chrono::steady_clock::now();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a->row, b->column, a->column, xx, mtof(a), a->column, mtof(b), b->column, yy, res, b->column);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff3 = end3 - start3;
    std::cout << "Time to fill and iterate a matrix of " << a->row << "*" << a->column << " and "
         << b->row << "*" << b->column << " using method 1 ints : " << diff1.count()*1000 << " ms\n";
    std::cout << "Time to fill and iterate a matrix of " << a->row << "*" << a->column << " and "
         << b->row << "*" << b->column << " using method 2 ints : " << diff2.count()*1000 << " ms\n";
    std::cout << "Time to fill and iterate a matrix of " << a->row << "*" << a->column << " and "
        << b->row << "*" << b->column << " using openBLAS ints : " << diff3.count() * 1000 << " ms\n";
//    res1->print();
//    res2->print();
    delete a;
    delete b;
    return 0;
}