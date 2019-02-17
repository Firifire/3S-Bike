using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.IO;
using UnityEngine;


public class Client : MonoBehaviour {

    private TcpClient client;
    private StreamWriter writer;

    // Use this for initialization
    void Start () {
        try
        {
            client = new TcpClient(AddressFamily.InterNetwork);
            IPAddress ipAddress = IPAddress.Parse("52.15.62.13");
            Debug.Log(ipAddress.ToString());
            client.Connect(ipAddress, 12453);
            writer = new StreamWriter(client.GetStream());
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
        writer.WriteLine("asdasdasd");
        writer.Flush();
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
