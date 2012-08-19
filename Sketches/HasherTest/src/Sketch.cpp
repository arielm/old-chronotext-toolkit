#include "Sketch.h"
#include "Hasher.h"

using namespace std;
using namespace ci;

Sketch::Sketch()
{
    cout << chr::hash("hello") << endl;
    
    // ---
    
    vector<char> letters;
    letters.push_back('h');
    letters.push_back('e');
    letters.push_back('l');
    letters.push_back('l');
    letters.push_back('o');
    
    cout << chr::hash<char>(letters) << endl;
    
    // ---

    vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    
    cout << chr::hash<int>(numbers) << endl;
}
