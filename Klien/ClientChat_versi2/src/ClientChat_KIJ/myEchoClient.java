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
import java.util.Random;
import java.lang.Math;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.logging.Level;
import java.util.logging.Logger;
public class myEchoClient {
    Form_login clientku= null;
    Main_client mainClient;
    private int PORT;
    private InetAddress host;
    private BufferedReader buff_read;
    //DataInputStream inputS = null;
    //DataOutputStream outputS = null;
    public BufferedOutputStream buff_OS;
    public Socket link = null;
    public String username;
    private String messageku;
    //Variabel Diffie Hellman
    public int q =929;
    public int alpha = 7;
    public int privateX;
    public BigInteger publicY;
    public RC4 InstanRc4;
    //BigInteger publicY;
    myEchoClient()
    {
        
    }
    myEchoClient(InetAddress host,int PORT, String nama, Form_login client)
    {
        this.clientku = client;
        this.host = host;
        this.PORT = PORT;
        this.username = nama;
        //this.mainClient = main;
    }
    public void makeClient() throws IOException
    {
        
        try
        {
            InstanRc4 = new RC4("testkey");
            mainClient = new Main_client(this, username);
            mainClient.show();
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
        //mainClient.writelog(message);
        try {
            if(message.contains("TALKTO:"))
            {
                String[] pecah = message.split(":");
                mainClient.writelog(username + " : " +pecah[2]);
                System.out.println("panjang pecah 2 >>" + pecah[2].length());
                System.out.println("isi pecah 2 >>" + pecah[2]);
                char[] pesanbaru = InstanRc4.encrypt(pecah[2].toCharArray());
                System.out.println("jumlah pesan >>" + pesanbaru.length);
                StringBuilder s = new StringBuilder(pesanbaru.length);
                for (char c : pesanbaru) {
                    s.append(c);
                }
                String pesanString = s.toString();//pesanbaru.toString();
                String totalPesan = "TALKTO" + ":" + pecah[1] + ":" + pesanString;;
                buff_OS.write(totalPesan.getBytes());
                buff_OS.flush();
            }
            else
            {
                buff_OS.write(message.getBytes());
                buff_OS.flush();
            }
  
        } catch (IOException ex) {
            Logger.getLogger(myEchoClient.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void diffie_hellman()
    {
        int min = 11;
        privateX = random(q, min);
        double coba = Math.pow((double)alpha, (double)privateX);
        publicY = new BigDecimal(coba).toBigInteger();
    }
    
    public BigInteger getKey(BigInteger kunci_lawan)
    {
        double main_key = Math.pow(kunci_lawan.doubleValue(), (double)privateX);
        BigInteger kunci = new BigDecimal(main_key).toBigInteger();
        BigInteger bigin = new BigInteger(String.valueOf(q));;
        return kunci.mod(bigin);
    }
    
    public int random(int max, int min)
    {
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;
        return randomNum;
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
                        //System.out.println("z");
                        String messageku = buff_read.readLine();
                        //System.out.println("ini message : " + messageku +"\n");
                        //System.out.println("q");
                        
                        if(messageku.contains("LISTUSER-"))
                        {
                            System.out.println("masuk List User >>");
                            String[] userGabung = messageku.split("-");
                            String[] listUser = userGabung[1].split(":");
                            System.out.println("User Gabung = " + listUser.length);
                            for(int i=0; i<listUser.length; i++)
                            {
                                try{
                                    System.out.println(listUser[i]+ " >> haha <<");
                                    mainClient.writeuser(listUser[i]+"\n"); 
                                    //System.out.println("cek mandek");
                                }
                                catch(NullPointerException e){
                                    
                                }   
                            }
                        }
                        else if(messageku.contains("FROM:"))
                        {
                            //System.out.println("masuk From>>");
                            String[] pesan = messageku.split(":");
                            //System.out.println(pesan[1] + pesan[2]);
                            try{
                                //char[] plain = InstanRc4.decrypt(pesan[2].toCharArray());
                                //System.out.println(plain.toString());
                                
                                char[] plain = InstanRc4.decrypt(pesan[2].toCharArray());
                                StringBuilder s = new StringBuilder(plain.length);
                                for (char c : plain) {
                                    s.append(c);
                                }
                                String plaintext = s.toString();
                                mainClient.writelog(pesan[1] + " : " +plaintext + "\n");
                                System.out.println("Sudah decrypt >> "+pesan[1] + " : " +plaintext);
                            }
                            catch(NullPointerException e)
                            {
                                
                            }
                            
                        }
                        else if (messageku.equalsIgnoreCase("BYE"))
                        {
                            mainClient.dissco();
                        }
                        
                        else 
                        {
                            System.out.println("Mlebu else ngisor");
                            try{
                                  mainClient.writelog(messageku);  
                            }
                            catch(NullPointerException e){
                                    
                            }
                            
                        }
                    }
                    catch(IOException e)
                    {
                        System.out.println("Masalah pada Thread client");
                    }
                    
                }
        }
    }    
}
