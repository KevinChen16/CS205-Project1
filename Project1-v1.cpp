#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <chrono>

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
        for (int i=0; i<row; i++) {
            for (int j=0; j<column; j++) {
                values[i][j] = getRandData(1,50);
            }
        }
    }
    void print() {
        for (int i=0; i<row; i++) {
            for (int j=0; j<column; j++) {
                cout << left << setw(8) << values[i][j] << " ";
            }
            cout << endl;
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

matrix* product(matrix *a, matrix *b) {
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

vector<string> split(const string& str, const string& delim) {
    vector<string> res;
    if("" == str) return res;
    char * strs = new char[str.length() + 1] ;
    strcpy(strs, str.c_str());
    char * d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());
    char *p = strtok(strs, d);
    while(p) {
        string s = p;
        res.push_back(s);
        p = strtok(NULL, d);
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
//                if (((*ss)!='.') && (((*ss)<'0') || ((*ss)>'9')) && ((*ss)!=' ') && ((*ss)!='\0')) {
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
    matrix* res = product(a,b);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff1 = end1-start1;
    cout << "Time to fill and iterate a matrix of " << a->row << "*" << a->column << " and "
    << b->row << "*" << b->column << " using method 1 ints : " << diff1.count()*1000 << " ms\n";
//    res->print();
    delete a;
    delete b;
    return 0;
}
