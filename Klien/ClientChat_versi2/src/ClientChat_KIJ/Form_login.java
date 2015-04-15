/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ClientChat_KIJ;

import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author Fandazky23
 */
public class Form_login extends javax.swing.JFrame {

    myEchoClient client;
    String username;
    

    public Form_login() {
        initComponents();
    }
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        ip_txt = new javax.swing.JTextField();
        port_txt = new javax.swing.JTextField();
        username_txt = new javax.swing.JTextField();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jButton1 = new javax.swing.JButton();
        jButton2 = new javax.swing.JButton();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        ip_txt.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        ip_txt.setText("10.181.1.120");
        ip_txt.setAutoscrolls(false);
        ip_txt.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ip_txtActionPerformed(evt);
            }
        });
        getContentPane().add(ip_txt, new org.netbeans.lib.awtextra.AbsoluteConstraints(190, 150, 210, 30));

        port_txt.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        port_txt.setText("9999");
        port_txt.setAutoscrolls(false);
        getContentPane().add(port_txt, new org.netbeans.lib.awtextra.AbsoluteConstraints(190, 220, 210, 30));

        username_txt.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        username_txt.setAutoscrolls(false);
        getContentPane().add(username_txt, new org.netbeans.lib.awtextra.AbsoluteConstraints(190, 290, 210, 30));

        jLabel1.setForeground(new java.awt.Color(255, 255, 255));
        jLabel1.setText("IP SERVER");
        jLabel1.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);
        getContentPane().add(jLabel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(220, 130, 100, -1));

        jLabel2.setForeground(new java.awt.Color(255, 255, 255));
        jLabel2.setText("PORT SERVER");
        jLabel2.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);
        getContentPane().add(jLabel2, new org.netbeans.lib.awtextra.AbsoluteConstraints(220, 200, 100, -1));

        jLabel3.setForeground(new java.awt.Color(255, 255, 255));
        jLabel3.setText("USERNAME");
        jLabel3.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);
        getContentPane().add(jLabel3, new org.netbeans.lib.awtextra.AbsoluteConstraints(220, 270, 100, -1));

        jButton1.setText("CONNECT");
        jButton1.setMaximumSize(new java.awt.Dimension(82, 23));
        jButton1.setMinimumSize(new java.awt.Dimension(82, 23));
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });
        getContentPane().add(jButton1, new org.netbeans.lib.awtextra.AbsoluteConstraints(310, 360, 88, -1));

        jButton2.setText("EXIT");
        jButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton2ActionPerformed(evt);
            }
        });
        getContentPane().add(jButton2, new org.netbeans.lib.awtextra.AbsoluteConstraints(190, 360, 88, -1));

        jLabel4.setIcon(new javax.swing.ImageIcon(getClass().getResource("/ClientChat_KIJ/login_icon.png"))); // NOI18N
        getContentPane().add(jLabel4, new org.netbeans.lib.awtextra.AbsoluteConstraints(250, 10, -1, -1));

        jLabel5.setIcon(new javax.swing.ImageIcon(getClass().getResource("/ClientChat_KIJ/black_background_wood-wallpaper-1366x768.jpg"))); // NOI18N
        jLabel5.setText("jLabel5");
        getContentPane().add(jLabel5, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 560, 440));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed

        String ip = ip_txt.getText().trim();
        if(ip.length() == 0) return;
        int port = (int) (Double.parseDouble(this.port_txt.getText()));
        
        username = this.username_txt.getText().trim();
        if(username.length() == 0) return;
        try {            
            //Main_client UIclient = new Main_client();
            client = new myEchoClient(InetAddress.getByName(ip),port,username,this);
            client.makeClient();
    
        } catch (UnknownHostException ex) {
            Logger.getLogger(Form_login.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Form_login.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        //Main_client UIclient = new Main_client();
        //UIclient.show();
        this.dispose();
    }//GEN-LAST:event_jButton1ActionPerformed

    private void jButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton2ActionPerformed
        // TODO add your handling code here:
        System.exit(0);
    }//GEN-LAST:event_jButton2ActionPerformed

    private void ip_txtActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ip_txtActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_ip_txtActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Form_login.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Form_login.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Form_login.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Form_login.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Form_login().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextField ip_txt;
    private javax.swing.JButton jButton1;
    private javax.swing.JButton jButton2;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JTextField port_txt;
    private javax.swing.JTextField username_txt;
    // End of variables declaration//GEN-END:variables
}
