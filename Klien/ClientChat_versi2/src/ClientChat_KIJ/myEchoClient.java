/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ClientChat_KIJ;

/**
 *
 * @author Fandazky23
 */
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
public class myEchoClient {
    public Form_login clientku= null;
    public Main_client mainClient=null;
    private int PORT;
    private InetAddress host;
    private BufferedReader buff_read;
    DataInputStream inputS = null;
    DataOutputStream outputS = null;
    public BufferedOutputStream buff_OS;
    public Socket link = null;
    public String username;
    private String messageku;
    myEchoClient()
    {
        
    }
    myEchoClient(InetAddress host,int PORT, String nama, Form_login client)
    {
        this.clientku = client;
        this.host = host;
        this.PORT = PORT;
        this.username = nama;
    }
    public void makeClient() throws IOException
    {
        try
        {
            link = new Socket(host, PORT);
            inputS = new DataInputStream(link.getInputStream());
            outputS = new DataOutputStream(link.getOutputStream());
            buff_OS = new BufferedOutputStream(link.getOutputStream());
            
            //UIclient.writelog(infoClient.nama + " has been connected to server\n");
        }
        catch(Exception ex)
        {
                    
        }
        String Protokol_conn = "";
        ClientListen listener = new ClientListen();
        listener.start();
        buff_OS.write(Protokol_conn.getBytes());
        buff_OS.flush();
    }
    
    public class ClientListen extends Thread{
        
        public void run()
        {
            if(clientku!=null){ 
                try {
                    buff_read = new BufferedReader(new InputStreamReader(link.getInputStream()));
                } catch (IOException ex) {
                    
                }
                while(true){   
                    try
                    {
                        String messageku = buff_read.readLine();
                        //ser.sendToClient(message);
                    }
                        catch(IOException e)
                        {
                            System.out.println("Masalah pada Thread client");
                        }

                    if (messageku.equalsIgnoreCase("QUIT"))
                    {
                        mainClient.dissco();
                    }

                    else
                    {
                        mainClient.writelog(messageku);
                    }

                }
            }
        }
    }
    
    
    
   
}
