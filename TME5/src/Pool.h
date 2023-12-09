#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

using namespace std;
namespace pr {

    void poolWorker(Queue<Job> * queue) {
        while (true) {
            Job * j = queue->pop();
            if (j == nullptr) {
                return;
            }
            j -> run();
            delete j;
        }

    }

class Pool {
	Queue<Job> queue;
	vector<std::thread> threads;
public:
    Pool(int qsize) : queue(qsize) {}
	void start (int nbthread){
        threads.reserve(nbthread);
        for (int i=0 ; i < nbthread ; i++) {
             threads.emplace_back(poolWorker, &queue);
             }
    }
	void submit (Job * job){queue.push(job);} ;
	void stop() {
        queue.setBlocking(false);
         for (auto & t : threads) {
             t.join();
             }
         threads.clear();
    };
	~Pool(){stop();} ;
};

}
