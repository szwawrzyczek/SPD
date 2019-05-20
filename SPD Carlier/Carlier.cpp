#pragma once
#include "Carlier.hpp"

void Carlier::loadData(string fileName)
{
    ifstream plik(fileName.c_str(), ios::in);

    Task obiektTmp; //obiekt tymczasowy do wrzucania danych do wektora
    plik >> n;      //odczytuje z pliki pierwsza linijke - ile zadan
    cout << "Wczytywanie w toku... " << endl;
    for (int i = 0; i < n; i++)
    {
        obiektTmp.n = i;               //przypisanie numery Task_vec
        plik >> obiektTmp.r;           //wczytanie r
        plik >> obiektTmp.p;           //wczytanie p
        plik >> obiektTmp.q;           //wczytanie q --- drugie zad
        Task_vec.push_back(obiektTmp); //wrzucenie calego obiektu na koniec
    }
    cout << "Wczytano plik z danymi : " << fileName.c_str() << "\t";
    cout << "Liczba zadan: " << n << endl;
    plik.close();
}

int Carlier::Schrage_S()
{
    int t = 0;     //chwila czasowa
    int C_max = 0; //maksymalny z terminow dostarczenia zadan
    Task e;

    priority_queue<Task, vector<Task>, sortowanie_r> NOT_READY_tasks; //zbior zadan nieuszeregowanych
    priority_queue<Task, vector<Task>, sortowanie_q> READY_tasks; //zbior zadan gotowych do realizacji

    for (int i = 0; i < Task_vec.size(); i++)
    {
        NOT_READY_tasks.push(Task_vec[i]);
    }
    while ((!READY_tasks.empty()) || (!NOT_READY_tasks.empty()))
    {
        while ((!NOT_READY_tasks.empty()) && (NOT_READY_tasks.top().r <= t))
        {
            e = NOT_READY_tasks.top();
            READY_tasks.push(e);
            NOT_READY_tasks.pop();
        }
        if (READY_tasks.empty())
        {
            t = NOT_READY_tasks.top().r;
        }
        else
        {
            e = READY_tasks.top();
            READY_tasks.pop();
            Sequence_vec.push_back(e.n);
            t = t + e.p;
            C_max = max(C_max, t + e.q);
            TimeTask_vec.push_back(t);
        }
    }
    return C_max;
}

int Carlier::Schrage_PTMN()
{
    Task namaszynie;
    namaszynie.q = 10000000; //some great value
    int t = 0;               //chwila czasowa
    int C_max = 0;
    Task e;

    priority_queue<Task, vector<Task>, Sort_R> NOT_READY_tasks; //zbior zadan nieuszeregowanych
    priority_queue<Task, vector<Task>, Sort_Q> READY_tasks; //zbior zadan gotowych do realizacji

    for (int i = 0; i < Task_vec.size(); i++)
    {
        NOT_READY_tasks.push(Task_vec[i]);
    }
    while (!(READY_tasks.empty()) || !(NOT_READY_tasks.empty()))
    {
        while (!(NOT_READY_tasks.empty()) && (NOT_READY_tasks.top().r <= t))
        {
            e = NOT_READY_tasks.top();
            READY_tasks.push(e);
            NOT_READY_tasks.pop();
            if (e.q > namaszynie.q)
            {
                namaszynie.p = t - e.r;
                t = e.r;
                if (namaszynie.p > 0)
                {
                    READY_tasks.push(namaszynie);
                }
            }
        }
        if (READY_tasks.empty())
        {
            t = NOT_READY_tasks.top().r;
        }
        else
        {
            e = READY_tasks.top();
            READY_tasks.pop();
            namaszynie = e;
            t = t + e.p;
            C_max = max(C_max, t + e.q);
        }
    }
    return C_max;
}

void Carlier::get_b(int C_max)
{

    for (int j = 0; j < n; j++)
    {
        if (C_max == TimeTask_vec[j] + Task_vec[Sequence_vec[j]].q)
        {
            b = j;
        }
    }
}
void Carlier::get_a(int C_max)
{
    for (int j = 0; j < n; j++)
    {
        int sum_p = 0;
        for (int iter = j; iter <= b; iter++)
        {
            sum_p += Task_vec[Sequence_vec[iter]].p;
        }

        if (C_max == Task_vec[Sequence_vec[j]].r + sum_p + Task_vec[Sequence_vec[b]].q)
        {
            a = j;
            break;
        }
    }
}
void Carlier::get_c()
{
    for (int j = a; j <= b; j++)
    {
        if (Task_vec[Sequence_vec[j]].q < Task_vec[Sequence_vec[b]].q)
        {
            c = j;
        }
    }
}

int Carlier::find_Rprim()
{
    int minR = 10000000; //some great value
    for (int j = c + 1; j <= b; j++)
    {
        if (Task_vec[Sequence_vec[j]].r < minR)
            minR = Task_vec[Sequence_vec[j]].r;
    }
    return minR;
}

int Carlier::find_Qprim()
{
    int minQ = 10000000; //some great value
    for (int j = c + 1; j <= b; j++)
    {
        if (Task_vec[Sequence_vec[j]].q < minQ)
            minQ = Task_vec[Sequence_vec[j]].q;
    }
    return minQ;
}

int Carlier::find_Pprim()
{
    int p = 0;
    for (int j = c + 1; j <= b; j++)
    {
        p += Task_vec[Sequence_vec[j]].p;
    }
    return p;
}

int Carlier::Carlier_Algorithm(int UB_param)
{
    int U, LB, C_max = 0, UB = UB_param;
    int rprim, qprim, pprim;
    int rpic, qpic;
    U = Schrage_S(); //krok 1
    if (U < UB)    //krok 2
    {
        UB = U;
    }
    //krok 3 WYZNACZENIE BLOKU
    
    
    get_b(U);
    get_a(U);
    get_c();

    if (c == -1)
    { //jesli c nie istnieje    
        cout<<"Algorytm zakonczyl dzialanie, sekwencja wynikowa zadań: "<<endl;
    	for (int i=0; i<n; i++)
        {
            int seq=this->getSequence_vec(i);
            cout<<" --> "<<seq<<"\t-->"<<endl;
        }                        //krok 4
        cout << "C_max dla algorytmu Carliera : " << U << endl;
        exit(0);
        return UB;
    }
    //krok 5
    rprim = find_Rprim();
    qprim = find_Qprim();
    pprim = find_Pprim();

    rpic = Task_vec[Sequence_vec[c]].r; //zapamietujemy rpic aby potem odtworzyc w kroku 10

    Task_vec[Sequence_vec[c]].r = max(Task_vec[Sequence_vec[c]].r, rprim + pprim); //krok 6

    LB = Schrage_PTMN(); //krok 7
    if (LB < UB)
    { //krok 8  =>  //krok 9
 
        Carlier nowyCarlier;
        nowyCarlier.loadData(Task_vec);
        C_max = nowyCarlier.Carlier_Algorithm(UB);
    }
    Task_vec[Sequence_vec[c]].r = rpic; //krok 10

    qpic = Task_vec[Sequence_vec[c]].q;

    Task_vec[Sequence_vec[c]].q = max(Task_vec[Sequence_vec[c]].q, qprim + pprim);

    LB = Schrage_PTMN(); //krok 12
    if (LB < UB)
    { //krok 13  =>  //krok 14
        Carlier nowyCarlier;
        nowyCarlier.loadData(Task_vec);
        C_max = nowyCarlier.Carlier_Algorithm(UB);
        
    }

    Task_vec[Sequence_vec[c]].q = qpic; //krok 15

    return C_max;
}