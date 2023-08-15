#include <iostream>
#include "../data_mgr/data_mgr.hxx"

using namespace std;

int main()
{
    cout << "ConsoleG5" << endl;

    data_mgr DM;
    DM.G5_console();
/**
    DM.ConsoleG5();
    bool socket_opened = DM.open_socket(PORT_G5,&DM.G5sockfd);
    if (!socket_opened) {
      printf("could not open socket to flightgear for G5 protocol\n");
      return 1;
    }
    printf("DM.G5sockfd %d\n",DM.G5sockfd);
    DM.sendG5Protocol = true;
    DM.OpenG5();
    DM.ReadOpenEagleG5();
    **/
    return 0;
}
