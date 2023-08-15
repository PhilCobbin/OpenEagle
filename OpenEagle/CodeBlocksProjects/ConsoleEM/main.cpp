#include <iostream>
#include "../data_mgr/data_mgr.hxx"
using namespace std;

int main()
{
    cout << "ConsoleEM" << endl;

    data_mgr DM;
    DM.EM_console();
    /**
    bool socket_opened = DM.open_socket(PORT_EM,&DM.EMsockfd);
    if (!socket_opened) {
      printf("could not open socket to flightgear for EM protocol\n");
      return 1;
    }
    printf("DM.EMsockfd %d\n",DM.EMsockfd);
    DM.sendEMProtocol = true;
    DM.OpenEM();
    DM.ReadOpenEagleEM();
    **/
    return 0;
}
