#include <iostream>
#include "../data_mgr/data_mgr.hxx"

using namespace std;

int main()
{
    cout << "ConsoleGPS" << endl;

    data_mgr DM;

   /// DM.GPS_initGPS();
 ///   DM.ConsoleGPS();
    DM.GPS_send_GPS_protocol = true;
    DM.GPS_console();
    /**
    bool socket_opened = DM.open_socket(PORT_GPS,&DM.GPSsockfd);
    if (!socket_opened) {
      printf("could not open socket to flightgear for GPS protocol\n");
      return 1;
    }
    else {
      printf("DM.GPSsockfd %d\n",DM.GPSsockfd);
    }
    DM.sendGPSProtocol = true;
    DM.OpenGPS();
    DM.ReadOpenEagleGPS();
    **/
    return 0;
}
