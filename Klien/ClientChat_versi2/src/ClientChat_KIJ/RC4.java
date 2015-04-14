/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ClientChat_KIJ;

/**
 *
 * @author Fandazky23
 */
public class RC4 {
    private char[] key;
    private int[] sbox;
    private static final int SBOX_LENGTH = 256;
    private static final int KEY_MIN_LENGTH = 5;
     
    public static void main(String[] args) {
        try {
            RC4 rc4 = new RC4("testkey");
            char[] result = rc4.encrypt("Hello there".toCharArray());
            System.out.println("encrypted string:\n" + new String(result));
            System.out.println("decrypted string:\n" + new String(rc4.decrypt(result)));
            System.out.println("encrypted string:\n" + new String(rc4.encrypt(rc4.decrypt(result))));
            } catch (InvalidKeyException e) {
                System.err.println(e.getMessage());
            }
        }
     
    public RC4(String key) throws InvalidKeyException {
        setKey(key);
    }
     
    public RC4() {
    }
     
    public char[] decrypt(final char[] msg) {
        return encrypt(msg);
    }
     
    public char[] encrypt(final char[] msg) {
        sbox = initSBox(key);
        //System.out.println("#panjangnya" + msg.length);
        char[] code = new char[msg.length];
        int i = 0;
        int j = 0;
        for (int n = 0; n < msg.length; n++) {
            i = (i + 1) % SBOX_LENGTH;
            j = (j + sbox[i]) % SBOX_LENGTH;
            swap(i, j, sbox);
            int rand = sbox[(sbox[i] + sbox[j]) % SBOX_LENGTH];
            code[n] = (char) (rand ^ (int) msg[n]);
        }
        return code;
    }
     
    private int[] initSBox(char[] key) {
        int[] sbox = new int[SBOX_LENGTH];
        int j = 0;
     
        for (int i = 0; i < SBOX_LENGTH; i++) {
            sbox[i] = i;
        }
     
        for (int i = 0; i < SBOX_LENGTH; i++) {
            j = (j + sbox[i] + key[i % key.length]) % SBOX_LENGTH;
            swap(i, j, sbox);
        }
        return sbox;
    }
     
    private void swap(int i, int j, int[] sbox) {
        int temp = sbox[i];
        sbox[i] = sbox[j];
        sbox[j] = temp;
    }
     
    public void setKey(String kunci) throws InvalidKeyException {
        if (!(kunci.length() >= KEY_MIN_LENGTH && kunci.length() < SBOX_LENGTH)) {
            throw new InvalidKeyException("Key length has to be between "
            + KEY_MIN_LENGTH + " and " + (SBOX_LENGTH - 1));
        }
        this.key = kunci.toCharArray();
    }
        
    public class InvalidKeyException extends Exception {
     
        private static final long serialVersionUID = 1L;
     
        public InvalidKeyException(String message) {
            super(message);
        } 
    }
     
}
     

