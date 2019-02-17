using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace _3S_Bike_Server_C
{
    class Program
    {
        public class ServiceListener
        {
            public TcpListener Listener;

            public void StartListening()
            {
                IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
                IPAddress ipAddress = Array.Find<IPAddress>(ipHostInfo.AddressList, ipMatch => ipMatch.AddressFamily == AddressFamily.InterNetwork);
                 ipAddress = IPAddress.Parse("127.0.0.1");
                Listener = new TcpListener(ipAddress, 9111);
                Listener.Start();
            }

            public void StopListening()
            {
                Listener.Stop();
            }
        }

        static void Main()
        {
            ServiceListener currentListener = new ServiceListener();
            currentListener.StartListening();

            TcpClient currentClient = currentListener.Listener.AcceptTcpClient();
            StreamReader reader = new StreamReader(currentClient.GetStream());

            Console.WriteLine("Connected");

            while (true)
            {
                byte[] messageBytes = new byte[1024];


                if (!reader.EndOfStream)
                {

                    string message = reader.ReadLine();
                    string[] messageParts = message.Split('|');

                    int xOffset = int.Parse(messageParts[0]);
                    int yOffset = int.Parse(messageParts[1]);
                    bool leftClick = bool.Parse(messageParts[2]);
                    bool rightClick = bool.Parse(messageParts[3]);


                    Console.WriteLine(string.Format("x:{0},y:{1},left:{2},right:{3}", xOffset, yOffset, leftClick, rightClick));
                }
                else
                {
                    currentClient = currentListener.Listener.AcceptTcpClient();
                    reader = new StreamReader(currentClient.GetStream());
                }
            }
        }
    }
}
