#ifndef EXITWMSG_CPP_INCLUDED
#define EXITWMSG_CPP_INCLUDED

using namespace std;

void exitwmsg(string msg = "", int exitCode = 0) {
    cout << "\n" << msg << "\n";
    cout << "Press RETURN key to exit...";
    cin.get();
    exit(exitCode);
}

#endif // EXITWMSG_CPP_INCLUDED
