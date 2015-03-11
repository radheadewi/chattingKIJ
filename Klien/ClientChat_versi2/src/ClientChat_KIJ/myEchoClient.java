package ClientChat_KIJ;
/**
 *
 * @author Fandazky23
 */
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
public class myEchoClient {
    public Form_login clientku= null;
    public Main_client mainClient=null;
    private int PORT;
    private InetAddress host;
    private BufferedReader buff_read;
    //DataInputStream inputS = null;
    //DataOutputStream outputS = null;
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
            buff_OS = new BufferedOutputStream(link.getOutputStream());    
        }
        catch(Exception ex)
        {
                    
        }
        String Protokol_conn = "LOGIN:"+ username +":";
        ClientListen listener = new ClientListen();
        listener.start();
        buff_OS.write(Protokol_conn.getBytes());
        buff_OS.flush();
    }
    
    public void sendMessage(String message)
    {
        
        try
        {
            buff_OS.write(message.getBytes());
            buff_OS.flush();
            mainClient.writelog(message);
        }
        catch(IOException e)
        {
            System.out.println("Sending message failed");
        }
    }
    
    public class ClientListen extends Thread{
        
        public void run()
        {
                try {
                    buff_read = new BufferedReader(new InputStreamReader(link.getInputStream()));
                } catch (NullPointerException e) {
                    
                } catch (IOException ex) {
                   
                }
                //String messageku = null;
                while(true){   
                    try
                    {
                        String messageku = buff_read.readLine();
                        if(messageku.contains("LISTUSER-"))
                        {

                            String[] userGabung = messageku.split("-");
                            String[] listUser = userGabung[1].split(":");
                            for(int i=0; i<listUser.length; i++)
                            {
                                mainClient.writeuser(listUser[i]+"\n");
                                System.out.println(listUser[i]);
                            }

                        }
                        else if(messageku.contains("FROM:"))
                        {
                            String[] pesan = messageku.split(":");
                            mainClient.writelog(pesan[1] + pesan[2]);
                        }
                        else if (messageku.equalsIgnoreCase("BYE"))
                        {
                            mainClient.dissco();
                        }

                        else
                        {
                            mainClient.writelog(messageku);
                        }
                    }
                    catch(IOException e)
                    {
                        System.out.println("Masalah pada Thread client");
                    }
                    
                    /*
                    try{
                        
                    }
                    catch(NullPointerException ex)
                    {
                        System.out.println("Pesan Null");
                    }
                    */
                }
        }
    }    
}
