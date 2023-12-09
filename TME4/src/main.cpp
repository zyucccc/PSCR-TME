#include "Banque.h"
#include <iostream>
using namespace std;
using namespace pr;

const int NB_THREAD = 10;
void transfertjob (int index,Banque & banque){
    cout<< "start: "<<index<<" "<<endl;
    for(int i=0;i<1000;i++){
        int debite = rand()%banque.size();
        int credite = rand()%banque.size();
        int val = rand()%100;
        banque.transfert(debite,credite,val);
        this_thread::sleep_for(chrono::milliseconds(rand()%10));
    }
    cout<<"finished"<<index<<endl;

}


int main () {
	vector<thread> threads;
    threads.reserve(NB_THREAD);
    Banque b(200,100);

    for (int i = 0;i<NB_THREAD;i++) {
        threads.emplace_back(transfertjob,i,ref(b));
        cout<<"created: "<< i <<endl;
    }

	for (auto & t : threads) {
		t.join();
	}
    cout <<"all joined "<< endl;

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
