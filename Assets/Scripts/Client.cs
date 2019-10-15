using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using TMPro;


public class Client : MonoBehaviour
{

    public TextMeshProUGUI windRPM, dynamoRPM;
    public TextMeshProUGUI windCurrent, dynamoCurrent, solarCurrent;
    public TextMeshProUGUI windEffieciency, dynamoEffieciency;

    private TcpClient client;
    private StreamWriter writer;
    private StreamReader reader;

    // Use this for initialization
    void Start()
    {
        StartCoroutine("updateValue");
    }

    // Update is called once per frame
    IEnumerator updateValue()
    {
        while (true)
        {

            try
            {
                client = new TcpClient(AddressFamily.InterNetwork);
                IPAddress ipAddress = IPAddress.Parse("52.15.62.13");
                Debug.Log(ipAddress.ToString());
                client.Connect(ipAddress, 12516);
                writer = new StreamWriter(client.GetStream());
                reader = new StreamReader(client.GetStream());
                Debug.Log("connected");
            }
            catch (ArgumentNullException ane)
            {
                Debug.Log(string.Format("ArgumentNullException : {0}", ane.ToString()));
            }
            catch (SocketException se)
            {
                Debug.Log(string.Format("SocketException : {0}", se.ToString()));
            }
            catch (Exception e)
            {
                Debug.Log(string.Format("Unexpected exception : {0}", e.ToString()));
            }
            writer.WriteLine("A<EOF>");
            writer.Flush();

            if (!reader.EndOfStream)
            {

                string message = reader.ReadLine();

                string valueHolder = "";
                int dataMode = 0;
                for (int i = 0; i < message.Length; i++)
                {
                    if (message[i] == '|')
                    {
                        switch (dataMode)
                        {
                            case 0:
                                windRPM.text = valueHolder;
                                break;
                            case 1:
                                dynamoRPM.text = valueHolder;
                                break;
                            case 2:
                                windCurrent.text = valueHolder;
                                break;
                            case 3:
                                dynamoCurrent.text = valueHolder;
                                break;
                            case 4:
                                solarCurrent.text = valueHolder;
                                break;
                        }
                        dataMode++;
                        valueHolder = "";
                        i++;
                    }
                    else if (message[i] == '<')
                        break;
                    valueHolder += message[i];
                }
            }

            yield return new WaitForSecondsRealtime(5);
        }
    }
}