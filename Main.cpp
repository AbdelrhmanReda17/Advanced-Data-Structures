#include "Suffix Tree/SuffixTree.h"
void SuffixTreeCases(){
    SuffixTree t1("bananabanaba$");
    // t1.traverseSuffixes(t1.getRoot(), 2);
    t1.Search("ana"); // Prints: 1 3 7
    cout << endl;
    t1.Search("naba"); // Prints: 4 8
    cout << endl;
    t1.Search("ban"); // Prints: 0 6
    cout << endl;
    SuffixTree t2("papatpapa$");
    // t2.traverseSuffixes(t2.getRoot(), 2);
    t2.Search("pa"); // Prints: 2 5 0 7
    cout << endl;
    t2.Search("papa"); // Prints: 5 0
    cout << endl;
    t2.Search("pat"); // Prints: 2
    cout << endl;
    SuffixTree t3("papatpapta$");
    // t3.traverseSuffixes(t3.getRoot(), 2);
    t3.Search("pa"); // Prints: 2 5 0
    cout << endl;
    t3.Search("papa"); // Prints: 0
    cout << endl;
    t3.Search("pat"); // Prints: 2
    cout << endl;
    SuffixTree t4("cattcat$");
    // t4.traverseSuffixes(t4.getRoot(), 2);
    t4.Search("cat"); // Prints: 0 4
    cout << endl;
    t4.Search("tcat"); // Prints: 3
    cout << endl;
    t4.Search("at"); // Prints: 1 5
    cout << endl;
    SuffixTree t5("mississippi$");
    // t5.traverseSuffixes(t5.getRoot(), 2);
    t5.Search("iss"); // Prints: 1 4
    cout << endl;
    t5.Search("ss"); // Prints: 2 5
    cout << endl;
    t5.Search("pi"); // Prints: 9
    cout << endl;
    SuffixTree t6("ababaa$");
    // t6.traverseSuffixes(t6.getRoot(), 2);
    t6.Search("aba"); // Prints: 0 2
    cout << endl;
    t6.Search("abaa"); // Prints: 2
    cout << endl;
    t6.Search("ba"); // Prints: 1 3 5
    cout << endl;
    SuffixTree t7("ratatat$");
    // t7.traverseSuffixes(t7.getRoot(), 2);
    t7.Search("rat"); // Prints: 0
    cout << endl;
    t7.Search("ta"); // Prints: 4 2
    cout << endl;
    t7.Search("tata"); // Prints: 2
    cout << endl;
    SuffixTree t8("aaaaaaa$");
    // t8.traverseSuffixes(t8.getRoot(), 2);
    t8.Search("a"); // Prints: 1 0 2 3 4 5 6
    cout << endl;
    t8.Search("aa"); // Prints: 1 0 2 3 4 5
    cout << endl;
    t8.Search("aaa"); // Prints: 1 0 2 3 4
    cout << endl;
    SuffixTree t9("gatagaca$");
    // t9.traverseSuffixes(t9.getRoot(), 2);
    t9.Search("gat"); // Prints: 0
    cout << endl;
    t9.Search("aga"); // Prints: 3
    cout << endl;
    t9.Search("ca"); // Prints: 6
    cout << endl;
    SuffixTree t10("nonsense$");
    // t10.traverseSuffixes(t10.getRoot(), 2);
    t10.Search("non"); // Prints: 0
    cout << endl;
    t10.Search("sen"); // Prints:3
    cout << endl;
    t10.Search("se"); // Prints: 6 3
    cout << endl;
}
int main()
{
    SuffixTreeCases();
    return 0;
}
