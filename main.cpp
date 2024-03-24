#include <map>
#include <iostream>

template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
    
    //  begin = 5, end = 11, val = 9
    //  [ 5, 11 ]
    //  [ 9, init ]
    //
    
    //  itr <- 5, editr <- 13
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        if(!(keyBegin < keyEnd)) return;
        
        typename std::map<K,V>::iterator it = m_map.lower_bound(keyEnd);
        V pvalue = it == m_map.begin() ? m_valBegin : (--it)->second;
        
        m_map[keyBegin] = val;
        m_map[keyEnd] = pvalue;
        
        typename std::map<K,V>::iterator st = m_map.lower_bound(keyBegin);
        typename std::map<K,V>::iterator ed = m_map.lower_bound(keyEnd);
        // erase slot
        for(++ st; st != ed; )
            st = m_map.erase(st);
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.
// 1 11 7
// [1,  9, 11]
// [7, 10, 10]

int main() {
    interval_map<int, int> mp(0);
    
    mp.assign(1, 10, 1);
    mp.assign(2, 8, 2);
    mp.assign(3, 5, 3);
    mp.assign(4, 7, 4);
    
    for(int i = 0; i < 12; i ++)
        std::cout << i << ' ' << mp[i] << std::endl;
    
    
    /*
    interval_map<string, char> mp('w');
    mp.assign("anti", "lus", 'a');
    
    const string values[] = {"abcd", "ewefa"};
    
    for(const string& it: values)
        cout << it << ' ' << mp[it] << endl;
        
    */
    return -1;
}