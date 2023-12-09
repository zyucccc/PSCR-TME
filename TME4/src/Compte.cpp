#include "Compte.h"

using namespace std;

namespace pr {
void Compte::crediter (unsigned int val) {
//	unique_lock<recursive_mutex> g(m);
    lock_guard<recursive_mutex> g(m);
	solde+=val ;
}
bool Compte::debiter (unsigned int val) {
//	unique_lock<recursive_mutex> g(m);
    lock_guard<recursive_mutex> g(m);
	bool doit = solde >= val;
	if (doit) {
		solde-=val ;
	}
	return doit;
}
int Compte::getSolde() const  {
//	unique_lock<recursive_mutex> g(m);
    lock_guard<recursive_mutex> g(m);
	return solde;
}
// NB : vector exige Copyable, mais mutex ne l'est pas...
Compte::Compte(const Compte & other) {
	other.m.lock();
	solde = other.solde;
	other.m.unlock();
}
    void Compte::lock() const {
        m.lock();
    }
    void Compte::unlock() const {
        m.unlock();
    }
    bool Compte::try_lock() const {
        m.try_lock();
    }


}
