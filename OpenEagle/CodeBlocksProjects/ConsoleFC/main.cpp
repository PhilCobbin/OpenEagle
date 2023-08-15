#include <iostream>
#include "../data_mgr/data_mgr.hxx"

using namespace std;

int main()
{
    cout << "ConsoleFC" << endl;

    data_mgr DM;
    DM.FC_console();
//    DM.ConsoleFC();
/**
    bool socket_opened = DM.open_socket(PORT_FC,&DM.FCsockfd);
    if (!socket_opened) {
      printf("could not open socket to flightgear for FC protocol\n");
      return 1;
    }
//    printf("DM.FCsockfd %d\n",DM.FCsockfd);
    DM.sendFCProtocol = true;
    DM.OpenFC();
    DM.ReadOpenEagleFC();
    **/
    return 0;
}
