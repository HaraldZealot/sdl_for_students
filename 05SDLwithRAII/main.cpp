#include <iostream>
#include <exception>

using namespace std;

int main()
{
    try
    {

    }
    catch(exception &e)
    {
        cerr << "ERROR: " << e.what() << endl;
    }
    catch(...)
    {
        cerr << "ERROR: something happend\n";
    }

    return 0;
}

