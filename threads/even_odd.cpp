#include <iostream>
#include <thread>
#include <semaphore>
using namespace std;


counting_semaphore<1>oddsem(1);
counting_semaphore<1>evensem(0);

void even(){

    for(int i=2;i<=10;i+=2){
        evensem.acquire();
        cout<<"even : "<<i<<endl;
        oddsem.release();
    }
}
void odd(){
    for(int i=1;i<=10;i+=2){
        oddsem.acquire();
        cout<<"even : "<<i<<endl;
        evensem.release();
    }
}

int main(){
    thread t1(even);
    thread t2(odd);

    t1.join();
    t2.join();

    cout<<"end"<<endl;
    return 0;
}