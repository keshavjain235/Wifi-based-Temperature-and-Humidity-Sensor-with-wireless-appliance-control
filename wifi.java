package Arduino;

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class wifi {

	public static void main(String[] args) throws Exception {
		
		Scanner scan = new Scanner(System.in);
		
		Socket s = new Socket("192.168.4.1", 1883);
		receive T1 = new receive(s);
		T1.start();
		
		DataOutputStream dos = new DataOutputStream(s.getOutputStream());
		String d = "";
		while(true)
		{
			d = scan.nextLine();
			dos.write(d.getBytes());
		}

	}
}