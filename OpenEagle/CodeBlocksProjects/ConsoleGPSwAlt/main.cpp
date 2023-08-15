#include <iostream>
#include "../data_mgr/data_mgr.hxx"
using namespace std;



int main()
{
    cout << "ConsoleGPSwAlt" << endl;

    data_mgr DM;

    DM.GPSwAlt_console();
    /**
    bool socket_opened = DM.open_socket(PORT_GPS_ALT,&DM.GPSAltsockfd);
    if (!socket_opened) {
      printf("could not open socket to flightgear for GPSwAlt protocol\n");
      return 1;
    }
    printf("DM.GPSAltsockfd %d\n",DM.GPSAltsockfd);
    DM.sendGPSwAltProtocol = true;
    DM.OpenGPS();
    DM.ReadOpenEagleGPS();
    **/
    return 0;
}
