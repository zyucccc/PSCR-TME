#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <algorithm>
#include "HashMap.h"

using namespace std;
using namespace std::chrono;
using namespace pr;
//print hashmap
void print_occurence_hash(const string & word,HashMap<string,int>& map){
    auto it = map.find(word);
    if(it != nullptr)
    {cout<< "Frequency : " <<it->key<<":"<<it->value<<endl; }
    else{
        cout<< "Word : " <<word<<" not found"<< endl;
    }
}

int main () {
    vector<pair<string,int>> unique;
    HashMap<string,int> map(2<<18);


	ifstream input = ifstream("../TME2/WarAndPeace.txt");
//    if (!input.is_open()) {
//        cout << "Failed to open WarAndPeace.txt" << endl;
//        return 1;
//    }

//obtenir le path of current working
//    std::__fs::filesystem::path current = std::__fs::filesystem::current_path();
//    std::cout << "Current working directory: " << current << std::endl;

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re(  "([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
        nombre_lu++;

        //unique - vector et pair
        auto element = (std::find_if(unique.begin(), unique.end(), [&word](const pair<string,int> &elt){return elt.first == word;}));
        if(element == unique.end()){
            unique.push_back({word,1});
        }else{
            element->second ++;
        }

        //HashMap
        if(!map.put(word,1)){};


	}
	input.close();

    //exo7:initialiser vector
    vector<pair<string,int>> entree = map.get_entree();
    vector<pair<string,int>> conver_map(entree.begin(),entree.end());

    //print occurence
    auto print_count = [&unique](const string& target){
        auto elt = (std::find_if(unique.begin(), unique.end(), [&target](const pair<string,int> &elt){return elt.first == target;}));
    if(elt != unique.end())
    {cout<< "Frequency : " <<target<<":"<<elt->second<< endl;}
    else{
        cout<< "Word : " <<target<<" not found"<< endl;
    }
    };
    //2
    //print occurence
    auto print_count_2 = [&conver_map](const string& target){
        auto elt = (std::find_if(conver_map.begin(), conver_map.end(), [&target](const pair<string,int> &elt){return elt.first == target;}));
        if(elt != conver_map.end())
        {cout<< "Frequency : " <<target<<":"<<elt->second<< endl;}
        else{
            cout<< "Word : " <<target<<" not found"<< endl;
        }
    };

	cout << "Finished Parsing War and Peace" << endl;

   //complexite:pour chaque element: O(n),pour parcourir le texte:O(n^2),on peut utiliser std::map,std::unordered_map
	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of -vector " << nombre_lu << " words." << endl;
    print_count("war");
    print_count("peace");
    print_count("toto");
//vector-2
    cout << "Found a total of -vector2 " << nombre_lu << " words." << endl;
    print_count_2("war");
    print_count_2("peace");
    print_count_2("toto");
//    print_occurence_hash
    cout << "Found a total of -hashmap " << nombre_lu << " words." << endl;
    print_occurence_hash("war",map);
    print_occurence_hash("peace",map);
    print_occurence_hash("toto",map);
    // trier decroissante
    sort(conver_map.begin(),conver_map.end(),[] (const pair<string,int> & a,const pair<string,int> & b){return  a.second > b.second;});
    //std::sort(entries.begin(),entries.end(), [] (auto a,auto b) { return a->value > b->value ;});
    int count =0;
    for(const auto & elt : conver_map){
        if(count < 10) {
            cout << "Frequency : " << elt.first << ":" << elt.second << endl;
            count ++;
        }
    }

    return 0;
}


