package Arduino;

import java.io.*;
import java.net.*;

public class receive extends Thread{

	Socket s1;
	receive(Socket s) {s1 = s;}
	
	public void run()
	{
		try {
			DataInputStream dis = new DataInputStream(s1.getInputStream());
			System.out.println("<Sensor data will refresh every 5 seconds>\n");
			while(true)
			{
				System.out.print("Relative Humidity: " + (char)dis.readByte() + (char)dis.readByte() + "%\t\t");
				System.out.println("Temperature: " + (char)dis.readByte() + (char)dis.readByte() + "°C");
			}
		} catch (Exception e) {}
	}
	
}